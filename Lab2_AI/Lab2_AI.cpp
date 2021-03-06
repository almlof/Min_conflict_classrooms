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



void printTable(vector<vector<string>> &classRooms)
{
	cout << "H		" << "TP51" << "		SP34" << "		K3" << endl << endl;

	vector<int> timeSlots = { 9,10,11,12,1,2,3,4 };
	string width = "		";

	for (int i = 0;i < hour; i++)
	{
		int it = 0;

		cout << timeSlots[i];

		for (auto const& value : classRooms)
		{
			
			if (it == 0)
			{
				cout <<  width << value[i] ;
			}
			else if (it == 1)
			{
				cout << width  << value[i] ;
			}
			else if (it == 2)
			{
				cout << width << value[i] << endl;
			}

			it++;
		}


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



vector<conflictPoint> identifyConflicts(vector<vector<string>> &classRooms)
{
	//vector to store the all the conflicts found in the current configuration
	
	vector<conflictPoint> conflicts;


	for (int i = 0; i < hour; i++)
	{	//check condition 2 in the lab instructions
		if (!(classRooms[0][i]).empty() && !classRooms[1][i].empty())
		{
			if (classRooms[0][i][2] == classRooms[1][i][2] && classRooms[0][i][2] != 5)
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
		}
		if(!classRooms[0][i].empty() && !classRooms[2][i].empty() && classRooms[0][i][2] == classRooms[2][i][2] && classRooms[0][i][2] != 5)
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
		 if (!classRooms[1][i].empty() && !classRooms[2][i].empty() && classRooms[1][i][2] == classRooms[2][i][2] && classRooms[1][i][2] != 5)
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

void bestSwap(vector<vector<string>>  &classRooms, conflictPoint conflict)
{
	int column = conflict.column;
	int row = conflict.row;
	int weigth = 10;
	int rowIndex;

	for (int i = 0; i < hour; i++)
	{
		int currentWeigth = 0;

		if (i == row)
			continue;

		

		if (!classRooms[0][i].empty() && classRooms[column][row][2] == classRooms[0][i][2])
			{
				currentWeigth++;
			}
		if (!classRooms[1][i].empty() && classRooms[column][row][2] == classRooms[1][i][2])
			{
				currentWeigth++;
			}
		if (!classRooms[2][i].empty() && classRooms[column][row][2] == classRooms[2][i][2])
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
	// Swap the values of the vector...
	auto temp= classRooms[column][row];
	classRooms[column][row] = classRooms[column][rowIndex];
	classRooms[column][rowIndex] = temp;

}


// Max steps not implemented
void minConflict(vector<vector<string>> &classRooms)
{

	vector<conflictPoint> conflicts = identifyConflicts(classRooms);

	if (conflicts.empty())
		return;

	/*pick random flaw*/
	conflictPoint randomChosen;
	randomChosen = *select_randomly(conflicts.begin(), conflicts.end());
	
	bestSwap(classRooms, randomChosen);
	printTable(classRooms);

	minConflict(classRooms);

};


int main()
{
	vector<string> all_classes = { "MT101","MT102", "MT103", "MT104", "MT105","MT106","MT107","MT201","MT202","MT203","MT204","MT205","MT206","MT301","MT302","MT303","MT304","MT401","MT402","MT403","MT501","MT502" };

	/* Make the initial state of the schedule*/

	vector<string> TP51 = {  };
	vector<string> SP34 = {  };
	vector<string> K3 = {  };

	for (int i = 0; i < all_classes.size(); i++)
	{
		if (i % 3 == 0)
		{
			TP51.push_back(all_classes[i]);
		}
		else if (i % 3 == 1)
		{
			SP34.push_back(all_classes[i]);
		}
		else if (i % 3 == 2)
		{
			K3.push_back( all_classes[i]);
		}
	}
	SP34.push_back("");
	K3.push_back("");
	
	/*Couples up all the classrooms into one vector of vectors*/
	
	vector<vector<string>>  class_rooms;

	vector<vector<string>> &classRooms = class_rooms;


	classRooms.push_back(TP51);
	classRooms.push_back(SP34);
	classRooms.push_back(K3);
	cout << "Before the action" << endl;
	printTable(classRooms);
	



	
	/*recursive call*/
	minConflict(class_rooms);

	cout << "After the action" << endl;
	
	//printTable(class_rooms);
	
	

}
