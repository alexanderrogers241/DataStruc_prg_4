#pragma once
#include <string>
/*
Student Name: Alexander Rogers
Student NetID: abr241
Compiler Used: Visual Studio
Program Description: Program assignment 4
Assigned Oct 2020
*/
class Node
{


public:
//<task>[0] <priority>[0] <length>[2] <arrives>[3] 
std::string task_name;
int priority;
int length;
int elapsed_time;
int start_time;

void refresh()
{
	elapsed_time = 0;
}
	
	
	Node(): task_name("NA"), priority(0), length(0),start_time(0), elapsed_time(0) {};
	Node(std::string task_name, int priority, int length, int start_time, int elapsed_time = 0)
		: task_name(task_name), priority(priority), length(length), start_time(start_time),elapsed_time(elapsed_time) {};
};

