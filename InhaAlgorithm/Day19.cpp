#include "Day19.h"

#include "StopWatch.h"
#include "StringSearcher.h"
#include "LinkedList.h"
#include "DoubleLinkedList.h"
#include "BinarySearchTree.h"

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

	LinkedList<Student> studentList;

	while ( true )
	{
		std::cout << "\n1.학생 추가, 2.학생 삭제, 3.출력, 4.검색\n";
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

				int inputPos = studentList.FindPos( s,
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
				
				int findPos = studentList.FindPos( {id,""},
					[]( Student a, Student b )
					{
						return a.id == b.id;
					}
				);
				studentList.DeleteNodeAtPos( findPos );
			}
			break;
		case 3:
			{
				studentList.DoListLoop(
					[]( Student* data )
					{
						printf( "%3d번 %s\n", data->id, data->name.c_str() );
					}
				);
			}
			break;
		case 4:
			{
				std::cout << "1.번호로 검색 2.이름으로 검색\n";
				int searchCase;
				std::cin >> searchCase;

				if ( searchCase == 1 )
				{
					std::cout << "번호 입력 : ";
					int id;
					std::cin >> id;
					Student data = studentList.FindIf( { id,"" },
						[]( Student a, Student b )
						{
							return a.id == b.id;
						}
					);
					if ( data.id != -1 )
					{
						printf( "%3d번 %s\n", data.id, data.name.c_str() );
					}
				}
				else if ( searchCase == 2 )
				{
					std::cout << "이름 입력 : ";
					std::string name;
					std::cin >> name;
					Student data = studentList.FindIf( { 0, name },
						[]( Student a, Student b )
						{
							return a.name == b.name;
						}
					);
					if ( data.id != -1 )
					{
						printf( "%3d번 %s\n", data.id, data.name.c_str() );
					}
				}
			}
			break;
		default:
			break;
		}
	}
}

void Day19::TestDouble()
{

	DoubleLinkedList<Student> studentList;

	while ( true )
	{
		std::cout << "\n1.학생 추가, 2.학생 삭제, 3.출력, 4.검색, 5.반대로 출력\n";
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

				int inputPos = studentList.find_pos( s,
					[]( Student a, Student b )
					{
						return a.id <= b.id;
					}
				);
				studentList.insert( s, inputPos );
			}
			break;
		case 2:
			{
				std::cout << "대상 학생 번호 입력 : ";
				int id;
				std::cin >> id;

				int findPos = studentList.find_pos( { id,"" },
					[]( Student a, Student b )
					{
						return a.id == b.id;
					}
				);
				studentList.remove( findPos );
			}
			break;
		case 3:
			{
				studentList.do_loop(
					[]( Student* data )
					{
						printf( "%3d번 %s\n", data->id, data->name.c_str() );
					}
				);
			}
			break;
		case 4:
			{
				std::cout << "1.번호로 검색 2.이름으로 검색\n";
				int searchCase;
				std::cin >> searchCase;

				if ( searchCase == 1 )
				{
					std::cout << "번호 입력 : ";
					int id;
					std::cin >> id;
					Student data = studentList.find_if( { id,"" },
						[]( Student a, Student b )
						{
							return a.id == b.id;
						}
					);
					if ( data.id != -1 )
					{
						printf( "%3d번 %s\n", data.id, data.name.c_str() );
					}
				}
				else if ( searchCase == 2 )
				{
					std::cout << "이름 입력 : ";
					std::string name;
					std::cin >> name;
					Student data = studentList.find_if( { 0, name },
						[]( Student a, Student b )
						{
							return a.name == b.name;
						}
					);
					if ( data.id != -1 )
					{
						printf( "%3d번 %s\n", data.id, data.name.c_str() );
					}
				}
			}
			break;
		case 5:
			{
				studentList.do_loop_reverse(
					[]( Student* data )
					{
						printf( "%3d번 %s\n", data->id, data->name.c_str() );
					}
				);
			}
			break;
		default:
			break;
		}
	}
}

void Day19::TestBinaryTree()
{
	BinarySearchTree<int> tree;
	
	tree.Add( 4 );
	tree.Add( 2 );
	tree.Add( 1 );
	tree.Add( 0 );
	tree.Add( 3 );
	tree.Add( 5 );
	bool a = tree.RemoveTarget( 2 );

	tree.DoAscendingLoop(
		[]( auto e )
		{
			std::cout << "key: " << e->GetKey() << " value: " << e->GetValue() << std::endl;
		}
	);

}

void Day19::UseBinarySearchTree()
{
	BinarySearchTree<int, std::string> studentList;

	auto Print = []( auto e )
	{
		std::cout << "key: " << e->GetKey() << " value: " << e->GetValue() << std::endl;
	};

	while ( true )
	{
		std::cout << "\n1.학생 추가, 2.학생 삭제, 3.출력, 4.검색\n";
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

				studentList.Add( id, name );
				studentList.DoAscendingLoop( Print );
			}
			break;
		case 2:
			{
				std::cout << "대상 학생 번호 입력 : ";
				int id;
				std::cin >> id;

				if ( studentList.RemoveTarget( id ) )
				{
					std::cout << "학생 삭제 완료\n";
					studentList.DoAscendingLoop( Print );
				}
				else
				{
					std::cout << "학생 삭제 실패\n";
				}

			}
			break;
		case 3:
			{
				studentList.DoAscendingLoop( Print );
			}
			break;
		case 4:
			{
				std::cout << "번호 입력 : ";
				int id;
				std::cin >> id;
				const auto& pData = studentList.Search( id );
				if ( pData == nullptr )
				{
					printf( "해당하는 데이터가 존재하지 않습니다\n" );
				}
				else
				{
					printf( "%3d번 %s\n", pData->GetKey(), pData->GetValue() );
				}
			}
			break;
		default:
			break;
		}
	}
}

