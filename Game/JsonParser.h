#pragma once
#include "rapidjson\rapidjson.h"
#include "rapidjson\document.h"


class JsonParser
{
public:
	JsonParser();
	~JsonParser() = default;

    rapidjson::Document GetDocument(const char* aPath);
};


