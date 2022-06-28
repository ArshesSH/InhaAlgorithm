#include "Day19.h"

#include "StringSercher.h"

void Day19::ExSearchString()
{
	const std::string str1 = "ABABCDEFGHA";
	const std::string str2 = "ABC";

	FindSubStr_Brute( str1.c_str(), str2.c_str(), true );
}
