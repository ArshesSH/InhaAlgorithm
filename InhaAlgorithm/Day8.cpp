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
		std::cout << "���� ������ �����Ͽ����ϴ�.\n";
		exit(1);
	}

	while ( true )
	{
		int menu, x;
		printf( "���� ������ �� : %d / %d\n", Size( &s ), Capacity( &s ) );
		printf( "(1)Ǫ�� (2)�� (3)��ũ (4)��� (5)�˻� (6)���� (0)���� : " );
		scanf_s( "%d", &menu );

		if ( menu == 0 )
		{
			break;
		}

		switch ( menu )
		{
		case 1:
			printf( "������ : " );
			scanf_s( "%d", &x );
			if ( Push( &s, x ) == -1 )
			{
				puts( "\a���� : Ǫ�ÿ� �����Ͽ����ϴ�.\n" );
			}
			break;
		case 2:
			if ( Pop( &s, &x ) == -1 )
			{
				puts( "\a���� : �˿� �����Ͽ����ϴ�.\n" );
			}
			else
			{
				printf( "�� �����ʹ� %d�Դϴ�.\n\n", x );
			}
			break;
		case 3:
			if ( Peek( &s, &x) == -1 )
			{
				puts( "\a���� : ��ũ�� �����Ͽ����ϴ�.\n" );
			}
			else
			{
				printf( "��ũ �����ʹ� %d�Դϴ�.\n\n", x );
			}
			break;
		case 4:
			Print( &s );
			break;
		case 5:
			if ( Search( &s, x ) == -1 )
			{
				puts( "\a���� : �˻��� �����Ͽ����ϴ�.\n" );
			}
			else
			{
				printf( "�˻� �����ʹ� �ε��� %d�� �ֽ��ϴ�.\n\n", x );
			}
			break;
		case 6:
			Clear( &s );
			puts( "���� �Ϸ�!\n" );
			break;
		}

	}
	Terminate( &s );
	exit( 0 );
}
