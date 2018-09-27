#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <string>
#include <fstream>
#include <time.h>
#include "helper.h"
using std::cout;
using std::endl;
using std::cin;
using std::getline;
using std::ios;
using std::string;
using std::fstream;
using namespace std::chrono_literals;
using namespace std::this_thread;

// Table of Contents
void TableOfContents()
{
	ClearScreen();
	int exerciseNum = 0;
	char num[] = "001";

	// Create variables for exercise 2 and 3
	saveData player1 = { "Boris",10,5,false,1000 };
	saveData player2;

	char contents[][50] = { "1. Hello World", "2. Save Player Data", "3. Load Player Data", "4. Monster Creature Quest" };

	// Print out list of exercises
	cout << "Please choose the exercise number:" << endl;
	cout << "----------------------------------" << endl;
	for (int i = 0; i < sizeof(contents) / sizeof(contents[0]); i++)
	{
		cout << contents[i] << endl;
	}
	cin >> exerciseNum;

	// Run exercise chosen by user
	switch (exerciseNum)
	{
	case 1:
		CreateHelloWorld();
		break;
	case 2:
		SavePlayerData(player1);
		break;
	case 3:
		LoadPlayerData();
		break;
	case 4:
		MonsterCreatureQuest();
		break;
	default:
		break;
	}
}

void CreateHelloWorld()
{
	fstream file;

	string name;
	char text[50] = {};

	cout << "What would you like to save the file as?" << endl;
	cin >> name;

	file.open(name, ios::out | ios::binary);

	// Check for failure to open
	if (file.fail())
	{
		cout << "File not found." << endl;
	}

	cout << "Please input what to add to the file: " << endl;
	cin.getline(text, 50);

	// Write to file
	file.write("Hello World!", strlen(text));
	file.flush();
	file.close();

	cout << "Thanks! Please check the file." << endl;
	sleep_for(1s);
	TableOfContents();
}

// Saving player data
void SavePlayerData(saveData player)
{
	fstream file;
	string name;

	cout << "Where would you like to save the data?" << endl;
	cout << "> ";

	cin >> name;
	cout << endl;

	file.open(name, ios::out | ios::binary);
	file << player.playerName << endl;
	file << player.deathCount << endl;
	file << player.deepestFloor << endl;
	file << player.hasBeenBeatenGame << endl;
	file << player.timePlayed << endl;

	file.flush();
	file.close();
	cout << "File saved successfully." << endl;
	sleep_for(1s);
	TableOfContents();
}

// Loading player data
saveData LoadPlayerData()
{
	fstream file;
	string name;
	saveData player;

	cout << "What file would you like to load?" << endl;
	cout << "> ";

	cin >> name;
	cout << endl;

	file.open(name, ios::in | ios::binary);

	// store data from file into a saveData variable
	string line;
	while (getline(file, line))
	{
		player.playerName = line;

		getline(file, line);
		player.deathCount = std::stoi(line);

		getline(file, line);
		player.deepestFloor = std::stoi(line);

		getline(file, line);
		player.hasBeenBeatenGame = std::stoi(line);

		getline(file, line);
		player.timePlayed = std::stof(line);
	}

	cout << "File loaded." << endl;
	return player;
}

// Monster Quest
void MonsterCreatureQuest()
{
	bool exit = false;
	int input = 0;
	fstream file;

	// Create a variable for new monsters that are added
	monster temp;

	// Create an array of monsters
	monster mList[50] = {};


	while (!exit)
	{
		cout << "Welcome to Monster Creature Quest." << endl << endl;
		cout << "What would you like to do?" << endl << endl;
		cout << "1) Add a monster by ID" << endl;
		cout << "2) Remove a monster by ID" << endl;
		cout << "3) View a monster by ID" << endl;
		cout << "4) Browse monsters" << endl;
		cout << "5) Exit" << endl << endl;
		cout << "> ";

		cin >> input;

		switch (input)
		{
		case 1:
		{
			int index = 0;
			// Define temp as a new monster
			temp = AddMonster();
			// Convert the monsterID char array into an integer to use as an index for mList
			index = atoi(temp.monsterID);
			mList[index - 1] = temp;
			input = 0;
		}
		break;
		case 2:
			RemoveMonster(mList);
			break;
		case 3:
			ViewMonster(mList);
			break;
		case 4:
			BrowseMonsters(mList, 50);
			break;
		case 5:
			exit = true;
			break;
		default:
			break;
		}
	}
	if (exit)
	{
		TableOfContents();
	}
}

monster AddMonster()
{
	fstream file;
	char name[50] = "bestiary\\";

	monster temp;

	// Ask for input
	cout << "What is the ID of the monster?" << endl;
	cin >> temp.monsterID;
	cout << "What is the name of the monster?" << endl;
	cin >> temp.monsterName;
	strcat_s(name, temp.monsterName);
	strcat_s(name, ".bin");

	cout << "What is its description?" << endl;
	cin >> temp.flavorText;

	std::ofstream fout(name, ios::out | ios::binary); // bestiary\\filename.bin
													  // Write info to file
	if (fout.is_open())
	{
		fout << temp.monsterID << '\n';
		fout << temp.monsterName << '\n';
		fout << temp.flavorText << '\n';
	}
	else
	{
		cout << "File not found." << endl;
	}
	fout.flush();
	fout.close();

	cout << "Thanks! Please check the file." << endl;
	sleep_for(1s);
	ClearScreen();

	return temp;
}

void RemoveMonster(monster * list)
{
	monster clearEntry = { " "," "," " };
	char id[50] = "";
	int index = 0;

	// Ask for input
	cout << "What is the ID of the monster you want to remove?" << endl;
	cin >> id;

	index = atoi(id);

	// Check if there is no monster at the chosen array position
	if (list[index].monsterID[index] == ' ')
	{
		cout << "There is no monster with that ID currently. Please try again with a different ID." << endl;
		sleep_for(1s);
		ClearScreen();
	}
	// Overwrite position with spaces
	else
	{
		list[index] = clearEntry;

		cout << "Monster has been removed." << endl;
		sleep_for(1s);
		ClearScreen();
	}

}

void ViewMonster(monster * list)
{
	char id[50] = "";
	int index = 0;

	// Ask for input
	cout << "What is the ID of the monster you want to view?" << endl;
	cin >> id;

	index = atoi(id);

	// Check if there is no monster at the chosen array position
	if (list[index - 1].monsterID[0] == ' ')
	{
		cout << "There is no monster with that ID. Please try again with a different ID." << endl;
		sleep_for(1s);
		ClearScreen();
	}
	else
	{
		cout << endl;
		cout << "ID: " << list[index - 1].monsterID << endl;
		cout << "Name: " << list[index - 1].monsterName << endl;
		cout << "Description: " << list[index - 1].flavorText << endl;

		cout << "Press enter to continue." << endl;
		getchar();
		getchar();
		ClearScreen();
	}
}

void BrowseMonsters(monster * list, size_t size)
{
	// Iterate through monster array and print out each monster's contents
	for (int i = 0; i < size; ++i)
	{
		if (list[i].monsterID[0] != ' ')
		{
			cout << "ID: " << list[i].monsterID << endl;
			cout << "Name: " << list[i].monsterName << endl;
			cout << "Description: " << list[i].flavorText << "\n" << endl;
		}
	}
	cout << "Press enter to continue." << endl;
	getchar();
	getchar();
	ClearScreen();
}