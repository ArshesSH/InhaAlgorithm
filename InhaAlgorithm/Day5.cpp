#include "Day5.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "SearchAlgorithm.h"
#include "Timer.h"

void Day5::FindDataBinarySearch()
{
	std::vector<float> list;
	std::cout << "Binary Search\n";
	std::cout << "데이터 입력(한 줄로 입력) : ";

	// Input Data
	std::string dataStr;
	char c;
	for ( std::cin.get( c ); c != '\n'; std::cin.get( c ) )
	{
		if ( c != ' ' )
		{
			dataStr += c;
		}
		else
		{
			list.push_back( std::stof( dataStr ) );
			dataStr.clear();
		}
	}
	list.push_back( std::stof( dataStr ) );
	dataStr.clear();

	// sort cheating :)
	std::sort( list.begin(), list.end() );

	// Search
	while ( true )
	{
		std::cout << "\n검색 데이터 입력(exit 입력 시 종료):";
		std::cin >> dataStr;

		if ( dataStr == "exit" || dataStr == "EXIT" || dataStr == "Exit" )
		{
			break;
		}

		const float data = std::stof( dataStr );
		Timer timer;
		const auto dataPos = SearchAlgorithm<float>::BinarySearch( list, data );
		if ( dataPos != list.size() )
		{
			std::cout << "자료 중 " << data << "이(가)" << dataPos << "자리에 있습니다." << std::endl;
		}
		else
		{
			std::cout << "자료 중 " << data << "이(가)" << dataPos << "자리에 없습니다." << std::endl;
		}
		std::cout << "걸린시간 = " << timer.GetTime() << std::endl;
		dataStr.clear();
	}
}

int PrintBinarySearch( const std::vector<float>& list, float target )
{
	std::cout << " |";
	for ( size_t i = 0; i < list.size(); i++ )
	{
		std::cout << " " << i << " ";
	}
	std::cout << std::endl;

	std::cout << "-+";
	for ( size_t i = 0; i < list.size(); i++ )
	{
		std::cout << "---";
	}
	std::cout << std::endl;

	int startPos = 0;
	int endPos = (int)list.size() - 1;
	int midPos;

	bool isTarget = false;
	while ( startPos <= endPos )
	{
		midPos = ((endPos - startPos) / 2) + startPos;

		std::cout << " |";
		for ( int i = 0; i < (int)list.size(); i++ )
		{
			if ( i == startPos )
			{
				if (startPos == midPos)
				{
					std::cout << "<";
				}
				else
				{
					std::cout << "<- ";
				}
			}

			if (i == midPos)
			{
				std::cout << " + ";
			}

			if ( i == endPos )
			{
				if (startPos == midPos)
				{
					std::cout << ">";
				}
				else
				{
					std::cout << " ->";
				}
			}

			if( i != startPos && i!= midPos && i!=endPos )
			{
				std::cout << "   ";
			}
		}
		std::cout << std::endl;

		std::cout << midPos << "|";
		for ( int i = 0; i < list.size(); i++ )
		{
			std::cout << " " << list[i] <<" ";
		}
		std::cout << std::endl;
		std::cout << " |\n";


		if ( target < list[midPos] )
		{
			endPos = midPos - 1;

		}
		else if ( target > list[midPos] )
		{
			startPos = midPos + 1;
		}
		else
		{
			isTarget = true;
			break;
		}
	}

	return isTarget ? midPos : -1;

}

void Day5::FindDataBinarySearchTable()
{
	std::vector<float> list;
	std::cout << "Binary Search\n";
	std::cout << "데이터 입력(한 줄로 입력) : ";

	// Input Data
	std::string dataStr;
	char c;
	for ( std::cin.get( c ); c != '\n'; std::cin.get( c ) )
	{
		if ( c != ' ' )
		{
			dataStr += c;
		}
		else
		{
			list.push_back( std::stof( dataStr ) );
			dataStr.clear();
		}
	}
	list.push_back( std::stof( dataStr ) );
	dataStr.clear();

	// sort cheating :)
	std::sort( list.begin(), list.end() );

	// Search
		// Find Data
	while ( true )
	{
		std::cout << "\n검색 데이터 입력(exit 입력 시 종료):";
		std::cin >> dataStr;

		if ( dataStr == "exit" || dataStr == "EXIT" || dataStr == "Exit" )
		{
			break;
		}

		const float data = std::stof( dataStr );
		Timer timer;
		const auto dataPos = PrintBinarySearch( list, data );
		if ( dataPos != -1 )
		{
			std::cout << "자료 중 " << data << "가(이) 있습니다." << std::endl;
		}
		else
		{
			std::cout << "자료 중 " << data << "가(이) 없습니다." << std::endl;
		}
		std::cout << "걸린시간 = " << timer.GetTime() << std::endl;
		dataStr.clear();
	}
}
