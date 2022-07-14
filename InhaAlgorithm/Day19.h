#pragma once

#include <string>
class Day19
{
public:
	class Student
	{
	public:
		Student()
			:
			id( -1 ),
			name( "" )
		{}
		Student( int id, const std::string& name )
			:
			id( id ),
			name( name )
		{}

	public:
		int id;
		std::string name;
	};
public:
	static void ExSearchString();
	static void UseCustomStack();
	static void TestDouble();
	static void TestBinaryTree();
	static void UseBinarySearchTree();
	static void TestHashMap();
	static void UseHashMap();
};

