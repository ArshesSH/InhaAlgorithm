#include "Day19.h"

#include "StopWatch.h"
#include "StringSearcher.h"
#include "LinkedList.h"

void Day19::ExSearchString()
{
	const std::string str1 = "ABABDJNABABBEABGHABCABDAB";
	const std::string str2 = "ABCABD";

	StopWatch timer;
	
	timer.Start();
	FindSubStr_Brute( str1.c_str(), str2.c_str(), false );
	timer.Stop();
	const double elapsed1 = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	std::cout << "Brute Force Time : " << elapsed1 << std::endl;


	timer.Start();
	FindSubStr_KMP( str1.c_str(), str2.c_str(), str2.size(), false );
	timer.Stop();
	//FindSubStr_KMP( str1.c_str(), str2.c_str(), str2.size(), true );
	const double elapsed2 = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	std::cout << "KMP Time : " << elapsed2 << std::endl;

	timer.Start();
	//FindStr_BoyerMoore( str1.c_str(), str2.c_str(), str2.size(), false );
	timer.Stop();

	FindStr_BoyerMoore( str1.c_str(), str2.c_str(), str2.size(), true );
	const double elapsed3 = timer.GetElapsedTime<double, (int)StopWatch::TimeUnit::Milli>();
	std::cout << "BoyerMoore Time : " << elapsed3 << std::endl;
}

void Day19::UseCustomStack()
{
	class Student
	{
	public:
		Student( int id, const std::string& name )
			:
			id( id ),
			name( name )
		{}

	public:
		int id;
		std::string name;
	};

	LinkedList<Student> studentList;

	while ( true )
	{
		std::cout << "1.학생 추가, 2.학생 삭제, 3.출력, 4.검색\n";
		int input;
		std::cin >> input;

		switch ( input )
		{
		case 1:
			{
				std::cout << "대상 학생 번호 입력 : ";
				int id;
				std::cin >> id;
				std::cout << "대상 학생 이름 입력 : ";
				std::string name;
				std::cin >> name;
				Student s( id, name );

				int inputPos = studentList.Find( s,
					[]( Student a, Student b )
					{
						return a.id <= b.id;
					}
				);
				studentList.PushToPos( s, inputPos );
			}
			break;
		case 2:
			{
				std::cout << "대상 학생 번호 입력 : ";
				int id;
				std::cin >> id;
				int inputPos = studentList.Find( s,
					[]( Student a, Student b )
					{
						return a.id == b.id;
					}
				);
				if ( inputPos != -1 )
				{
					
				}
			}
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			break;
		}

	}
}

