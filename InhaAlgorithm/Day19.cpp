#include "Day19.h"

#include "StopWatch.h"
#include "StringSearcher.h"

void Day19::ExSearchString()
{
	const std::string str1 = "ABABDJNABABBEABGHABCABDAB";
	const std::string str2 = "ABCABD";

	StopWatch timer;
	
	timer.Start();
	FindSubStr_Brute( str1.c_str(), str2.c_str(), false );
	timer.Stop();

	const double elapsed1 = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	std::cout << "걸린 시간 : " << elapsed1 << std::endl;


	timer.Start();
	//FindSubStr_KMP( str1.c_str(), str2.c_str(), str2.size(), false );
	timer.Stop();

	FindSubStr_KMP( str1.c_str(), str2.c_str(), str2.size(), true );
	const double elapsed2 = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	std::cout << "걸린 시간 : " << elapsed1 << std::endl;
}
