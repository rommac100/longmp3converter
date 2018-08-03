#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <timealt.h>
std::vector<int> getColonsPos(std::string tempLine)
{
    std::cout<<"line: "+tempLine<<std::endl;
    std::vector<int> tempList;
    std::string temp = tempLine;
    while (temp.find_first_of(":") != std::string::npos)
    {
        int index = temp.find_first_of(":");

        std::cout<<"index Unshifted: "+ std::to_string(index)<<std::endl;
        int tempIndex = index+1;
        temp = temp.substr(tempIndex, temp.length()-1);
        if (tempList.size() > 0)
        {
         index += tempList.at(tempList.size()-1)+1;
        }
        tempList.push_back(index);
        std::cout<<"temp: "+ temp<<std::endl;
        }

    return tempList;
}

bool checkIfNum(char tempChar)
{
    if (std::isdigit(tempChar))
    {
     return true;
    }
    return false;
}

std::vector<int> getColonNearDigits(std::string tempLine)
{
   std::vector<int> colonsIndexs = getColonsPos(tempLine);
   std::vector<int> parsedIndexs; //used for first indentifing if there is a 2 char gap on either side of the colon. This may need to be change to a different algorithm if the time stamp is format differently.
   std::vector<int> secondaryParse;
   std::cout<<"colonsIndex Parsed: "+ std::to_string(colonsIndexs.size())<<std::endl;
   for (int i : colonsIndexs)
   {
      if ((i-2 >0) && (i+2 < tempLine.length()))
      {
          parsedIndexs.push_back(i);
      }
   }

   for (int i : parsedIndexs)
   {
        if (checkIfNum(tempLine.at(i-1)) && checkIfNum(tempLine.at(i-2)) && checkIfNum(tempLine.at(i+1))&& checkIfNum(tempLine.at(i+2)))
        {
            secondaryParse.push_back(i);
        }
   }

   return secondaryParse;
}

//this assumes description's times are in the format - minutes::seconds only works with that format for now.
std::vector<TimeAlt> convertTimes(std::vector<int> indexs, std::string tempLine)
{
    std::vector<TimeAlt> tempTimes;
    for (int i : indexs)
    {
        std::string tempSMin = tempLine.substr(i-2,2);
        std::string tempSSec = tempLine.substr(i+1,2);
        tempTimes.push_back(TimeAlt(std::stoi(tempSMin),std::stoi(tempSSec)));
    }
    return tempTimes;
}

bool outputAudioConversion(std::string mp3file, std::vector<TimeAlt> timeStamps)
{
    for (int i =0; i < timeStamps.size()-1; i++)
    {
        std::string temp = "mp3splt "+ mp3file +" "+timeStamps.at(i).getCommandOut()+" "+timeStamps.at(i+1).getCommandOut();
        std::system(temp.c_str());
    }
}

int main()
{
    std::cout << "Hello World!" << std::endl;
    std::cout << "Getting Colons in file"<<std::endl;
    std::ifstream import("/home/rommac100/testingcolons/test.txt");
    std::string tempLine;
    std::vector<int> colonPos;
    std::vector<std::string> lines;
    if (import.is_open())
    {

        while (std::getline(import,tempLine))
        {
            std::cout<<tempLine<<std::endl;
            lines.push_back(tempLine);
        }

        //tempLine = ":::   ::: :::";d
        for (std::string i : lines)
        {
            std::cout<< "line in lines: "+ i<<std::endl;
        }
        std::cout<<"lines size: "+ std::to_string(lines.size())<<std::endl;

        std::vector<TimeAlt> tempTimes = convertTimes(getColonNearDigits(lines.at(0)),lines.at(0));
        for (TimeAlt i: tempTimes)
        {
            std::cout<<i.getCommandOut()<<std::endl;
        }
        bool success = outputAudioConversion("/home/rommac100/Downloads/One_Hour_of_Music_-_Soviet_Communist_Music[ListenVid.com].mp3",tempTimes);
        //colonPos = getColonsPos(lines.at(0));
        //colonPos = getColonNearDigits(lines.at(0));
        //std::cout<<"Num of Colons: "+ std::to_string(colonPos.size())<<std::endl;
        import.close();
    }
    else
    {
        std::cout<<"failed to openfile, check to see if it is the right"<<std::endl;
    }

}
