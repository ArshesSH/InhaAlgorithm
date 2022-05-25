#include "Day4.h"

#include <iostream>
#include <vector>
#include <string>
#include "SearchAlgorithm.h"
#include "Timer.h"

void Day4::FindDataByLinearSearch()
{
	std::vector<float> list;
	std::cout << "������ �Է�(�� �ٷ� �Է�) : ";

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

	// Find Data
	while ( true )
	{
		std::cout << "\n�˻� ������ �Է�(exit �Է� �� ����):";
		std::cin >> dataStr;

		if ( dataStr == "exit" || dataStr == "EXIT" || dataStr == "Exit" )
		{
			break;
		}

		const float data = std::stof( dataStr );
		Timer timer;
		const auto dataPos = SearchAlgorithm<float>::LinearSearch( list, data );
		if ( dataPos != list.size() )
		{
			std::cout << "�ڷ� �� " << data << "�� �ֽ��ϴ�." << std::endl;
		}
		else
		{
			std::cout << "�ڷ� �� " << data << "�� �����ϴ�." << std::endl;
		}
		std::cout << "�ɸ��ð� = " << timer.GetTime() << std::endl;
		dataStr.clear();
	}
}

void Day4::FindDataByLinearSearch2()
{
	std::vector<float> list;
	std::cout << "������ �Է�(�� �ٷ� �Է�) : ";

	// Input Data
	std::string dataStr;
	char c;
	for ( std::cin.get( c ); c != '\n'; std::cin.get(c) )
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

	// Find Data
	while ( true )
	{
		std::cout << "\n�˻� ������ �Է�(exit �Է� �� ����):";
		std::cin >> dataStr;

		if ( dataStr == "exit" || dataStr == "EXIT" || dataStr == "Exit" )
		{
			break;
		}

		const float data = std::stof( dataStr );
		Timer timer;
		const auto dataPos = SearchAlgorithm<float>::LinearSearchAlter( list, data );
		if ( dataPos != list.size() )
		{
			std::cout << "�ڷ� �� " << data << "�� �ֽ��ϴ�." << std::endl;
		}
		else
		{
			std::cout << "�ڷ� �� " << data << "�� �����ϴ�." << std::endl;
		}
		std::cout << "�ɸ��ð� = " << timer.GetTime() << std::endl;
		dataStr.clear();
	}
}

size_t PrintLinearSearch( std::vector<float> list, float target )
{
	std::cout << " |";
	for ( size_t i = 0; i < list.size(); i++ )
	{
		std::cout << " " << i;
	}
	std::cout << std::endl;

	std::cout << "-+";
	for ( size_t i = 0; i < list.size(); i++ )
	{
		std::cout << "--";
	}
	std::cout << std::endl;

	size_t pos;
	for ( pos = 0; pos < list.size(); pos++ )
	{
		std::cout << " |";
		for ( size_t i = 0; i < pos; i++ )
		{
			std::cout << "  ";
		}
		std::cout << " *\n";

		std::cout << pos << "|";
		for ( auto e : list )
		{
			std::cout << " " << e;
		}
		std::cout << "\n |\n";
		if ( list[pos] == target )
		{
			break;
		}
	}
	return pos;
}

size_t PrintLinearSearchAlter(std::vector<float> list, float target)
{
	std::cout << " |";
	for ( size_t i = 0; i < list.size(); i++ )
	{
		std::cout << " " << i;
	}
	std::cout << std::endl;

	std::cout << "-+";
	for ( size_t i = 0; i < list.size(); i++ )
	{
		std::cout << "--";
	}
	std::cout << std::endl;

	list.push_back( target );
	size_t pos;
	for ( pos = 0; ; pos++ )
	{
		std::cout << " |";
		for ( size_t i = 0; i < pos; i++ )
		{
			std::cout << "  ";
		}
		std::cout << " *\n";

		std::cout << pos << "|";
		for ( auto e : list )
		{
			std::cout << " " << e;
		}
		std::cout << "\n |\n";
		if ( list[pos] == target )
		{
			break;
		}
	}
	return pos;
}

void Day4::FindDataByLinearSearch3()
{
	std::vector<float> list;
	std::cout << "������ �Է�(�� �ٷ� �Է�) : ";

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

	// Find Data
	while ( true )
	{
		std::cout << "\n�˻� ������ �Է�(exit �Է� �� ����):";
		std::cin >> dataStr;

		if ( dataStr == "exit" || dataStr == "EXIT" || dataStr == "Exit" )
		{
			break;
		}

		const float data = std::stof( dataStr );
		Timer timer;
		const auto dataPos = PrintLinearSearch( list, data );
		if ( dataPos != list.size() )
		{
			std::cout << "�ڷ� �� " << data << "�� �ֽ��ϴ�." << std::endl;
		}
		else
		{
			std::cout << "�ڷ� �� " << data << "�� �����ϴ�." << std::endl;
		}
		std::cout << "�ɸ��ð� = " << timer.GetTime() << std::endl;
		dataStr.clear();

		timer.GetTime();
		const auto dataPos2 = PrintLinearSearchAlter( list, data );
		if ( dataPos2 != list.size() )
		{
			std::cout << "�ڷ� �� " << data << "�� �ֽ��ϴ�." << std::endl;
		}
		else
		{
			std::cout << "�ڷ� �� " << data << "�� �����ϴ�." << std::endl;
		}
		std::cout << "�ɸ��ð� = " << timer.GetTime() << std::endl;
	}
}
