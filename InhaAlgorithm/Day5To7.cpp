#include "Day5To7.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "SearchAlgorithm.h"
#include "Timer.h"
#include <cstdlib>

void Day5To7::FindDataBinarySearch()
{
	std::vector<float> list;
	std::cout << "Binary Search\n";
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

	// sort cheating :)
	std::sort( list.begin(), list.end() );

	// Search
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
		const auto dataPos = SearchAlgorithm<float>::BinarySearch( list, data );
		if ( dataPos != list.size() )
		{
			std::cout << "�ڷ� �� " << data << "��(��)" << dataPos << "�ڸ��� �ֽ��ϴ�." << std::endl;
		}
		else
		{
			std::cout << "�ڷ� �� " << data << "��(��)" << dataPos << "�ڸ��� �����ϴ�." << std::endl;
		}
		std::cout << "�ɸ��ð� = " << timer.GetTime() << std::endl;
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

void Day5To7::FindDataBinarySearchTable()
{
	std::vector<float> list;
	std::cout << "Binary Search\n";
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

	// sort cheating :)
	std::sort( list.begin(), list.end() );

	// Search
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
		const auto dataPos = PrintBinarySearch( list, data );
		if ( dataPos != -1 )
		{
			std::cout << "�ڷ� �� " << data << "��(��) �ֽ��ϴ�." << std::endl;
		}
		else
		{
			std::cout << "�ڷ� �� " << data << "��(��) �����ϴ�." << std::endl;
		}
		std::cout << "�ɸ��ð� = " << timer.GetTime() << std::endl;
		dataStr.clear();
	}
}

int intCmp( const int* a, const int* b )
{
	if ( *a < *b )
		return -1;
	else if ( *a > *b )
		return 1;
	else
		return 0;
};


void Day5To7::UseBinarySearchLib()
{
	int nx;

	std::cout << "bsearch �Լ� ����Ͽ� �˻�\n��� ���� : ";
	std::cin >> nx;
	int* x = (int*)calloc( nx, sizeof( int ) );
	
	std::cout << "������������ �Է� : ";
	std::cout << "x[0] : ";
	std::cin >> x[0];
	for ( int i = 1; i < nx; i++ )
	{
		do
		{
			std::cout << "x[" << i << "] : ";
			std::cin >> x[i];
		} while ( x[i] < x[i - 1] );
	}

	int key;
	std::cout << " �˻��� : ";
	std::cin >> key;

	int* p = (int*)SearchAlgorithm<int>::bsearch( &key, x, nx, sizeof( int ), (int(*)(const void*, const void*))intCmp );
	if ( p == nullptr )
	{
		std::cout << "�˻��� �����߽��ϴ�.\n";
	}
	else
	{
		printf( "%d�� x[%d]�� �ֽ��ϴ�\n", key, (int)(p - x) );
	}
	free( x );
}