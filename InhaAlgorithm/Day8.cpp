#include "Day8.h"

#include <iostream>
#include <cstdio>

struct IntStack
{
	int max;
	int ptr;
	int* stk;
};

int IsEmpty( const IntStack* s )
{
	return s->ptr == 0;
}

int IsFull( const IntStack* s )
{
	return s->ptr == s->max;
}

int Initialize( IntStack* s, int max )
{
	s->ptr = 0;
	s->stk = nullptr;
	s->max = max;
	s = new IntStack[max];
	return 0;
}


int Push( IntStack* s, int x )
{
	if ( s->ptr < s->max )
	{
		s[s->ptr].stk = new int;
		*s[s->ptr].stk = x;
		++s->ptr;
		return 0;
	}
	return -1;
}

int Pop( IntStack* s, int* x )
{
	if ( !IsEmpty( s ) )
	{
		--s->ptr;
		*x = *(s[s->ptr].stk);
		delete(s[s->ptr].stk);
		s[s->ptr].stk = nullptr;
		return 0;
	}
	return -1;
}

int Peek( const IntStack* s, int* x )
{
	if ( !IsEmpty( s ) )
	{
		*x = *(s[s->ptr - 1].stk);
		return 0;
	}
	return -1;
}

void Clear( IntStack* s )
{
	int* tmp = nullptr;
	for ( int i = s->max - 1; i >= 0; --i )
	{
	}
}

int Capacity( const IntStack* s )
{
	return s->max;
}

int Size( const IntStack* s )
{
	return s->ptr;
}

int Search( const IntStack* s, int x )
{
	for ( int i = 0; i < s->max; ++i )
	{
		if ( *s[s->ptr - 1].stk == x )
		{
			return i;
		}
	}
	return -1;
}

void Print( const IntStack* s )
{
	for ( int i = 0; i < s->ptr; ++i )
	{
		std::cout << *(s[i].stk) << " ";
	}
	std::cout << std::endl;
}

void Terminate( IntStack* s )
{
	Clear( s );
	delete[] s;
	s = nullptr;
}

void Day8::CustomStack()
{
	IntStack s;
	if ( Initialize( &s, 3 ) == -1 )
	{
		std::cout << "스택 생성에 실패하였습니다.\n";
		exit(1);
	}

	while ( true )
	{
		int menu, x;
		printf( "현재 데이터 수 : %d / %d\n", Size( &s ), Capacity( &s ) );
		printf( "(1)푸시 (2)팝 (3)피크 (4)출력 (5)검색 (6)비우기 (0)종료 : " );
		scanf_s( "%d", &menu );

		if ( menu == 0 )
		{
			break;
		}

		switch ( menu )
		{
		case 1:
			printf( "데이터 : " );
			scanf_s( "%d", &x );
			if ( Push( &s, x ) == -1 )
			{
				puts( "\a오류 : 푸시에 실패하였습니다.\n" );
			}
			break;
		case 2:
			if ( Pop( &s, &x ) == -1 )
			{
				puts( "\a오류 : 팝에 실패하였습니다.\n" );
			}
			else
			{
				printf( "팝 데이터는 %d입니다.\n\n", x );
			}
			break;
		case 3:
			if ( Peek( &s, &x) == -1 )
			{
				puts( "\a오류 : 피크에 실패하였습니다.\n" );
			}
			else
			{
				printf( "피크 데이터는 %d입니다.\n\n", x );
			}
			break;
		case 4:
			Print( &s );
			break;
		case 5:
			if ( Search( &s, x ) == -1 )
			{
				puts( "\a오류 : 검색에 실패하였습니다.\n" );
			}
			else
			{
				printf( "검색 데이터는 인덱스 %d에 있습니다.\n\n", x );
			}
			break;
		case 6:
			Clear( &s );
			puts( "비우기 완료!\n" );
			break;
		}

	}
	Terminate( &s );
	exit( 0 );
}
