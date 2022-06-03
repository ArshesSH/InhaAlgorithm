#include "Day8.h"

#include <iostream>
#include <cstdio>

namespace Stack
{

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
		s->max = max;
		s->stk = new int[max];
		return 0;
	}


	int Push( IntStack* s, int x )
	{
		if ( !IsFull( s ) )
		{
			s->stk[s->ptr] = x;
			++s->ptr;
			return 0;
		}
		return -1;
	}

	int Pop( IntStack* s, int* x )
	{
		if ( !IsEmpty( s ) )
		{
			(s->ptr)--;
			*x = s->stk[s->ptr];
			s->stk[s->ptr] = 0;
			return 0;
		}
		return -1;
	}

	int Peek( const IntStack* s, int* x )
	{
		if ( !IsEmpty( s ) )
		{
			*x = s->stk[s->ptr - 1];
			return 0;
		}
		return -1;
	}

	void Clear( IntStack* s )
	{
		int tmp;
		for ( int i = s->ptr - 1; i >= 0; --i )
		{
			Pop( s, &tmp );
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
		for ( int i = 0; i < s->ptr; ++i )
		{
			if ( s->stk[i] == x )
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
			std::cout << s->stk[i] << " ";
		}
		std::cout << std::endl;
	}

	void Terminate( IntStack* s )
	{
		Clear( s );
		delete[] s->stk;
		s->stk = nullptr;
	}
}


void Day8::CustomStack()
{
	using namespace Stack;
	IntStack s;
	if ( Initialize( &s, 3 ) == -1 )
	{
		std::cout << "���� ������ �����Ͽ����ϴ�.\n";
		exit( 1 );
	}
	int menu = 0;
	int x = 0;
	int searchResult;
	while ( true )
	{

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
			if ( Peek( &s, &x ) == -1 )
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
			printf( "������ : " );
			scanf_s( "%d", &x );
			searchResult = Search( &s, x );
			if ( searchResult == -1 )
			{
				puts( "\a���� : �˻��� �����Ͽ����ϴ�.\n" );
			}
			else
			{
				printf( "�˻� �����ʹ� �ε��� %d�� �ֽ��ϴ�.\n\n", searchResult );
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

namespace Queue
{
	struct IntQueue
	{
		int max;
		int num;
		int front;
		int rear;
		int* que;
	};
	int IsEmpty( const IntQueue* q )
	{
		return q->num == 0;
	}
	int IsFull( const IntQueue* q )
	{
		return q->num == q->max;
	}
	int Initialize( IntQueue* q, int max )
	{
		q->max = max;
		q->front = 0;
		q->rear = 0;
		q->num = 0;
		q->que = new int[max];
		return 0;
	}
	int Enque( IntQueue* q, int x )
	{
		if ( !IsFull( q ) )
		{
			q->que[q->rear] = x;
			++q->num;
			if ( ++q->rear == q->max )
			{
				q->rear = 0;
			}
			return 0;
		}
		return -1;
	}
	int Deque( IntQueue* q, int* x )
	{
		if ( !IsEmpty( q ) )
		{
			*x = q->que[q->front];
			--q->num;
			if ( ++q->front == q->max )
			{
				q->front = 0;
			}
			return 0;
		}
		return -1;
	}	
	int Peek( const IntQueue* q, int* x )
	{
		if ( !IsEmpty( q ) )
		{
			*x = q->que[q->front];
			return 0;
		}
		return -1;
	}
	void Clear( IntQueue* q )
	{
		q->front = 0;
		q->rear = 0;
		q->num = 0;
	}
	int Capacity( const IntQueue* q )
	{
		return q->max;
	}
	int Size( const IntQueue* q )
	{
		return q->num;
	}

	int Search( const IntQueue* q, int x )
	{
		if ( !IsEmpty( q ) )
		{
			const int distance = q->rear - q->front;
			if (distance > 0 )
			{
				for ( int i = q->front; i < q->rear; ++i )
				{
					if ( x == q->que[i] )
					{
						return i;
					}
				}
			}
			else if ( distance < 0 )
			{
				for ( int i = q->front; i < q->max; ++i )
				{
					if ( x == q->que[i] )
					{
						return i;
					}
				}
				for ( int i = 0; i < q->rear; ++i )
				{
					if ( x == q->que[i] )
					{
						return i;
					}
				}
			}
			else
			{
				for ( int i = 0; i < q->max; ++i )
				{
					if ( x == q->que[i] )
					{
						return i;
					}
				}
			}
		}
		else
		{
			return -1;
		}
	}
	void Print( const IntQueue* q )
	{
		const int distance = q->rear - q->front;

		if (distance > 0 )
		{
			for ( int i = q->front; i < q->rear; ++i )
			{
				printf( "%d ", q->que[i] );
			}
			printf( "\n\n" );
		}
		else if ( distance < 0 )
		{
			for ( int i = q->front; i < q->max; ++i )
			{
				printf( "%d ", q->que[i] );
			}
			for ( int i = 0; i < q->rear; ++i )
			{
				printf( "%d ", q->que[i] );
			}
			printf( "\n\n" );
		}
		else
		{
			for ( int i = 0; i < q->max; ++i )
			{
				printf( "%d ", q->que[i] );
			}
			printf( "\n\n" );
		}
	}
	void Terminate( IntQueue* q )
	{
		q->max = 0;
		q->front = 0;
		q->rear = 0;
		q->num = 0;
		delete[] q->que;
		q->que = nullptr;
	}
}


void Day8::CustomQueue()
{
	using namespace Queue;
	IntQueue que;

	if ( Initialize( &que, 3 ) == -1 )
	{
		puts( "ť ���� ����" );
		exit( 1 );
	}
	while ( true )
	{
		int m, x;

		printf( "���� ������ �� : %d / %d\n", Size( &que ), Capacity( &que ) );
		printf( "(1)Inque (2)Deque (3)Peek (4)Print (5)Search (6)Clear (0)Exit : " );
		scanf_s( "%d", &m );

		if ( m == 0 )
		{
			break;
		}
		int pos;
		switch ( m )
		{
		case 1:
			printf( "Data : " );
			scanf_s( "%d", &x );
			if ( Enque( &que, x ) == -1 )
			{
				puts( "\aError : Fail to Enque\n\n" );
			}
			break;
		case 2:
			if ( Deque( &que, &x ) == -1 )
			{
				puts( "\aError : Fail to Deque\n\n" );
			}
			else
			{
				printf( "Deque Data = %d\n\n", x );
			}
			break;
		case 3:
			if ( Peek( &que, &x ) == -1 )
			{
				puts( "\aError : Fail to Peek\n\n" );
			}
			else
			{
				printf( "Peeked Data = %d\n\n", x );
			}
			break;
		case 4:
			Print( &que );
			break;
		case 5:
			printf( "Data : " );
			scanf_s( "%d", &x );
			pos = Search( &que, x );
			if ( pos == -1 )
			{
				puts( "No Data!!!\n\n" );
			}
			else
			{
				printf( "Searched Data Index = %d\n\n", pos );
			}
			break;
		case 6:
			Clear( &que );
			printf( "Finished Clear\n\n" );
			break;
		}
	}
	Terminate( &que );
}