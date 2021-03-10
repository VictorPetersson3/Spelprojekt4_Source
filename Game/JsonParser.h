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
	JsonParser();
	~JsonParser() = default;

    rapidjson::Document GetDocument(const char* aPath);
};


