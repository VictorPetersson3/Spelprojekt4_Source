#include "stdafx.h"
#include "JsonParser.h"

JsonParser::JsonParser()
{

}

JsonParser& JsonParser::GetInstance()
{
	return myInstance;
}

rapidjson::Document JsonParser::GetDocument(const char* aPath)
{
    std::string text;
    std::fstream file;

    rapidjson::Document documentToReturn;

    file.open(aPath);
    {
        std::string line;
        while (std::getline(file, line))
        {
            text.append(line);
        }
    }
    file.close();
    documentToReturn.Parse(text.c_str());

    return documentToReturn;
}

JsonParser JsonParser::myInstance;

