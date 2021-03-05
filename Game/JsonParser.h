#pragma once
#include "rapidjson\rapidjson.h"
#include "rapidjson\document.h"
#include "rapidjson\filereadstream.h"
#include <fstream>
#include <sstream>
#include <string>


class JsonParser
{
public:
	JsonParser(const JsonParser&) = delete;

    static JsonParser& GetInstance();
	
    rapidjson::Document GetDocument(const char* aPath);

private:
	JsonParser();
	~JsonParser() = default;

	static JsonParser myInstance;

};


