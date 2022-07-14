#include "Day19.h"

#include "StopWatch.h"
#include "StringSearcher.h"
#include "LinkedList.h"
#include "DoubleLinkedList.h"
#include "BinarySearchTree.h"
#include "HashMap.h"

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
		std::cout << "\n1.�л� �߰�, 2.�л� ����, 3.���, 4.�˻�\n";
		int input;
		std::cin >> input;

		switch ( input )
		{
		case 1:
			{
				std::cout << "��� �л� ��ȣ �Է� : ";
				int id;
				std::cin >> id;
				std::cout << "��� �л� �̸� �Է� : ";
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
				std::cout << "��� �л� ��ȣ �Է� : ";
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
						printf( "%3d�� %s\n", data->id, data->name.c_str() );
					}
				);
			}
			break;
		case 4:
			{
				std::cout << "1.��ȣ�� �˻� 2.�̸����� �˻�\n";
				int searchCase;
				std::cin >> searchCase;

				if ( searchCase == 1 )
				{
					std::cout << "��ȣ �Է� : ";
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
						printf( "%3d�� %s\n", data.id, data.name.c_str() );
					}
				}
				else if ( searchCase == 2 )
				{
					std::cout << "�̸� �Է� : ";
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
						printf( "%3d�� %s\n", data.id, data.name.c_str() );
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
		std::cout << "\n1.�л� �߰�, 2.�л� ����, 3.���, 4.�˻�, 5.�ݴ�� ���\n";
		int input;
		std::cin >> input;

		switch ( input )
		{
		case 1:
			{
				std::cout << "��� �л� ��ȣ �Է� : ";
				int id;
				std::cin >> id;
				std::cout << "��� �л� �̸� �Է� : ";
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
				std::cout << "��� �л� ��ȣ �Է� : ";
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
						printf( "%3d�� %s\n", data->id, data->name.c_str() );
					}
				);
			}
			break;
		case 4:
			{
				std::cout << "1.��ȣ�� �˻� 2.�̸����� �˻�\n";
				int searchCase;
				std::cin >> searchCase;

				if ( searchCase == 1 )
				{
					std::cout << "��ȣ �Է� : ";
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
						printf( "%3d�� %s\n", data.id, data.name.c_str() );
					}
				}
				else if ( searchCase == 2 )
				{
					std::cout << "�̸� �Է� : ";
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
						printf( "%3d�� %s\n", data.id, data.name.c_str() );
					}
				}
			}
			break;
		case 5:
			{
				studentList.do_loop_reverse(
					[]( Student* data )
					{
						printf( "%3d�� %s\n", data->id, data->name.c_str() );
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
	bool a = tree.Remove( 2 );

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
		std::cout << "\n1.�л� �߰�, 2.�л� ����, 3.���, 4.�˻�\n";
		int input;
		std::cin >> input;

		switch ( input )
		{
		case 1:
			{
				std::cout << "��� �л� ��ȣ �Է� : ";
				int id;
				std::cin >> id;
				std::cout << "��� �л� �̸� �Է� : ";
				std::string name;
				std::cin >> name;
				Student s( id, name );

				studentList.Add( id, name );
				studentList.DoAscendingLoop( Print );
			}
			break;
		case 2:
			{
				std::cout << "��� �л� ��ȣ �Է� : ";
				int id;
				std::cin >> id;

				if ( studentList.Remove( id ) )
				{
					std::cout << "�л� ���� �Ϸ�\n";
					studentList.DoAscendingLoop( Print );
				}
				else
				{
					std::cout << "�л� ���� ����\n";
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
				std::cout << "��ȣ �Է� : ";
				int id;
				std::cin >> id;
				const auto& pData = studentList.Search( id );
				if ( pData == nullptr )
				{
					printf( "�ش��ϴ� �����Ͱ� �������� �ʽ��ϴ�\n" );
				}
				else
				{
					printf( "%3d�� %s\n", pData->GetKey(), pData->GetValue().c_str() );
				}
			}
			break;
		default:
			break;
		}
	}
}

void Day19::TestHashMap()
{
	auto keyFunc = []( Student data )->int
	{
		return data.id;
	};

	auto isEqual = []( Student lhs, Student rhs )
	{
		return lhs.id == rhs.id;
	};

	auto printFunc = []( auto e, int i )
	{
		printf( "%02d :", i );
		for ( auto pCur = e[i]; pCur != nullptr; pCur = pCur->GetNext() )
		{
			printf( " ->%d(%s)", pCur->data.id, pCur->data.name.c_str() );
		}
		printf( "\n" );
	};

	HashMap<Student> map( 13, keyFunc );

	map.Add( {1, "hello"});
	map.Add( { 2, "hi" } );
	map.Add( { 3, "bye" } );
	map.Add( { 16, "hello" } );
	map.DoLoop( printFunc );
	auto a = map.SearchByKey( 3 );
	map.RemoveByData( { 3, "bye" }, isEqual );
	map.DoLoop( printFunc );
	auto b = map.SearchByKey( 3 );
}

void Day19::UseHashMap()
{
	auto keyFunc = []( Student data )->int
	{
		return data.id;
	};

	auto isEqual = []( Student lhs, Student rhs )
	{
		return lhs.id == rhs.id;
	};

	auto printFunc = []( auto e, int i )
	{
		printf( "%02d :", i );
		for ( auto pCur = e[i]; pCur != nullptr; pCur = pCur->GetNext() )
		{
			printf( " ->%d(%s)", pCur->data.id, pCur->data.name.c_str() );
		}
		printf( "\n" );
	};
	HashMap<Student> studentList(keyFunc);

	while ( true )
	{
		std::cout << "\n1.�л� �߰�, 2.�л� ����, 3.�˻�, 4.��λ���, 5.���� \n";
		int input;
		std::cin >> input;

		switch ( input )
		{
		case 1:
			{
				std::cout << "��� �л� ��ȣ �Է� : ";
				int id;
				std::cin >> id;
				std::cout << "��� �л� �̸� �Է� : ";
				std::string name;
				std::cin >> name;
				Student s( id, name );

				studentList.Add( {id, name} );
				//studentList.DoLoop( printFunc );
			}
			break;
		case 2:
			{
				std::cout << "��� �л� ��ȣ �Է� : ";
				int id;
				std::cin >> id;

				if ( studentList.RemoveByKey( id ) )
				{
					std::cout << "�л� ���� �Ϸ�\n";
					//studentList.DoLoop( printFunc );
				}
				else
				{
					std::cout << "�л� ���� ����\n";
				}

			}
			break;
		case 3:
			{
				std::cout << "��ȣ �Է� : ";
				int id;
				std::cin >> id;
				const auto& pData = studentList.SearchByKey( id );
				if ( pData == nullptr )
				{
					printf( "�ش��ϴ� �����Ͱ� �������� �ʽ��ϴ�\n" );
				}
				else
				{
					printf( "%3d�� %s\n", pData->data.id, pData->data.name.c_str() );
				}
			}
			break;

		case 4:
			studentList.RemoveAll();
			break;
		
		case 5:
			{
				studentList.DoLoop( printFunc );
			}
			break;

		default:
			break;
		}
	}
}

