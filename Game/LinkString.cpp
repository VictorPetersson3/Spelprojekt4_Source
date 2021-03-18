#include "stdafx.h"
#include "LinkString.h"


LinkString::LinkString(const char* aString)
{
	assert(strlen(aString) <= 64 && "String can not exceed 64 characters");
	strcpy_s(myString, aString);
}

const char* LinkString::GetString() const
{
	return myString;
}

bool LinkString::operator<(const char* aString) const
{
	return (strcmp(myString, aString) < 0);
}

bool LinkString::operator<(const LinkString& aString) const
{
	return (strcmp(myString, aString.myString) < 0);
}

bool operator<(const char* aString1, const LinkString& aString2)
{
	return (strcmp(aString1, aString2.myString) < 0);
}


bool LinkString::operator>(const char* aString) const
{
	return (strcmp(myString, aString) > 0);
}
bool LinkString::operator>(const LinkString& aString) const
{
	return (strcmp(myString, aString.myString) > 0);
}

bool operator>(const char* aString1, const LinkString& aString2)
{
	return (strcmp(aString1, aString2.myString) > 0);
}


bool LinkString::operator==(const char* aString) const
{
	return (strcmp(myString, aString) == 0);
}

bool LinkString::operator==(const LinkString& aString) const
{
	return (strcmp(myString, aString.myString) == 0);
}

bool operator==(const char* aString1, const LinkString& aString2)
{
	return (strcmp(aString1, aString2.myString) == 0);
}
