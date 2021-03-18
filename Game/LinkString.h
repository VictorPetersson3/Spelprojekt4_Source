#pragma once
//Credit to Morgan
#include <string.h>

class LinkString
{
public:
	LinkString() = default;
	LinkString(const char* aString);
	~LinkString() = default;
	LinkString(LinkString&&) = delete;
	LinkString(const LinkString&) = delete;

	const char* GetString() const;

	LinkString& operator=(LinkString&) = delete;
	LinkString& operator=(const LinkString&) = delete;

	bool operator< (const char* aString) const;
	bool operator< (const LinkString& aString) const;
	friend bool operator< (const char* aString1, const LinkString& aString2);
	bool operator> (const char* aString) const;
	bool operator> (const LinkString& aString) const;
	friend bool operator> (const char* aString1, const LinkString& aString2);
	bool operator== (const char* aString) const;
	bool operator== (const LinkString& aString) const;
	friend bool operator== (const char* aString1, const LinkString& aString2);
private:
	char myString[64];
};