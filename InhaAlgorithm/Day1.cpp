#include "Day1.h"


int Day1::max4( int a, int b, int c, int d )
{
    int max = a;
    max = GetMax( max, b );
    max = GetMax( max, c );
    max = GetMax( max, d );

    return max;
}

int Day1::med3( int a, int b, int c )
{
    int mid;
    if ( a < b )
    {
        if ( b < c )
        {
            mid = b;
        }
        else
        {
            mid = c;
        }
    }
    else if( b < c )
    {
        mid = b;
    }
    else if (a < c )
    {
        mid = c;
    }
    else
    {
        mid = a;
    }

    return mid;
}

int Day1::GetMax( int lhs, int rhs )
{
    return (lhs > rhs) ? lhs : rhs;
}

void Day1::Swap( int& lhs, int& rhs )
{
    int tmp = lhs;
    lhs = rhs;
    rhs = lhs;
}

