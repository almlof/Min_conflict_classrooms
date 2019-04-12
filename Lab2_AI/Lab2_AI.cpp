// Lab2_AI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <iterator>
#include <array>
#include <algorithm>


const int hour = 8;
using namespace std;
/*
class classRoom
{
public:
	classRoom(vector<string> _classes) 
	{
		classes = _classes;
	}
	vector<string> classes = {};
	
};
*/
struct conflictPoint
{
	int column;
	int row;
};



void printTable(vector<array<string,hour>> classRooms)
{
	vector<int> timeSlots = { 9,10,11,12,1,2,3,4 };

	cout << "H		" << "TP51" << "		SP34" << "		K3" << endl << endl;

	for (int i = 0; i < hour; i++)
	{
			cout << timeSlots[i] << "		" << classRooms[0][i];
		
			cout << "		" << classRooms[1][i];
		
			cout << "		" << classRooms[2][i]  << endl;
	}

}


template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
	std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
	std::advance(start, dis(g));
	return start;
}
template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	return select_randomly(start, end, gen);
}



vector<conflictPoint> identifyConflicts(vector<array<string, hour>> classRooms)
{
	//vector to store the all the conflicts found in the current confiuration

	vector<conflictPoint> conflicts;
	char five = (char)5;

	for (int i = 0; i < hour; i++)
	{	//check condition 2 in the lab instructions
		if (classRooms[0][i][3] == classRooms[1][i][3] && classRooms[0][i][3] != five)
		{
			conflictPoint temp;
			temp.column = 0;
			temp.row = i;
			conflicts.push_back(conflictPoint(temp));
			conflictPoint temp2;
			temp2.column = 1;
			temp2.row = i;
			conflicts.push_back(conflictPoint(temp2));

		}
		else if(classRooms[0][i][3] == classRooms[2][i][3] && classRooms[0][i][3] != five)
		{
			conflictPoint temp;
			temp.column = 0;
			temp.row = i;
			conflicts.push_back(conflictPoint(temp));
			conflictPoint temp2;
			temp2.column = 2;
			temp2.row = i;
			conflicts.push_back(conflictPoint(temp2));
		}
		else if (classRooms[1][i][3] == classRooms[2][i][3] && classRooms[1][i][3] != five)
		{
			conflictPoint temp;
			temp.column = 2;
			temp.row = i;
			conflicts.push_back(conflictPoint(temp));
			conflictPoint temp2;
			temp2.column = 1;
			temp2.row = i;
			conflicts.push_back(conflictPoint(temp2));
		}
		
	}
	return conflicts;
}

void bestSwap(vector<array<string, hour>> classRooms, conflictPoint conflict)
{
	int column = conflict.column;
	int row = conflict.row;
	int weigth = 10;
	char five = (char)5;
	int rowIndex;

	for (int i = 0; i < hour; i++)
	{
		int currentWeigth = 0;

		if (i == row)
			continue;

		if (classRooms[column][row][3] == classRooms[0][i][3] && classRooms[0][i][3] != five)
		{
			currentWeigth++;
		}
		if (classRooms[column][row][3] == classRooms[1][i][3] && classRooms[1][i][3] != five)
		{
			currentWeigth++;
		}
		if (classRooms[column][row][3] == classRooms[2][i][3] && classRooms[2][i][3] != five)
		{
			currentWeigth++;
		}
		if (currentWeigth == 0)
		{
			rowIndex = i;
			break;
		}
		if (currentWeigth < weigth)
		{
			weigth = currentWeigth;
			rowIndex = i;
		}
			
	}
	// Swap the calues of the vector...
	string temp = classRooms[column][row];
	classRooms[column][row] = classRooms[column][rowIndex];
	classRooms[column][rowIndex] = temp;

}


// Max steps not implemented
void minConflict(vector<array<string, hour>> classRooms)
{

	vector<conflictPoint> conflicts = identifyConflicts(classRooms);

	if (conflicts.empty())
		return;

	/*pick random flaw*/
	conflictPoint randomChosen;
	randomChosen = *select_randomly(conflicts.begin(), conflicts.end());
	
	bestSwap(classRooms, randomChosen);

	minConflict(classRooms);


};


int main()
{
	vector<string> all_classes = { "MT101","MT102", "MT103", "MT104", "MT105","MT106","MT107","MT201","MT202","MT203","MT204","MT205","MT206","MT301","MT302","MT303","MT304","MT401","MT402","MT403","MT501","MT502" };

	/* Make the initial state of the schedule*/

	
	
	array<string, hour> TP51 = {  };
	array<string, hour> SP34 = {  };
	array<string, hour> K3 = {  };
	
	
	//array<string, hour> SP34 = {  };
	//array<string, hour> K3 = {  };
	


	for (int i = 0; i < all_classes.size(); i++)
	{
		if (i % 3 == 0)
		{
			TP51[i%hour] = all_classes[i];
		}
		else if (i % 3 == 1)
		{
			SP34[i%hour] = all_classes[i];
		}
		else if (i % 3 == 2)
		{
			K3[i%hour] = all_classes[i];
		}
	}
	
	/*Couples up all the classrooms into one vector of vectors*/
	
	vector<array<string, hour>> class_rooms;
	class_rooms.push_back(TP51);
	class_rooms.push_back(SP34);
	class_rooms.push_back(K3);
	cout << "Before the action" << endl;
	printTable(class_rooms);
	

	/*
	/*recursive call*/
	minConflict(class_rooms);

	cout << "After the action" << endl;
	printTable(class_rooms);
	
	

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
