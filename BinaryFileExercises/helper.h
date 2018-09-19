#pragma once

#include <string>

struct saveData
{
	std::string playerName;
	int deathCount;
	int deepestFloor;

	bool hasBeenBeatenGame;

	double timePlayed;  // given in seconds
};

struct monster
{
	char monsterID[50] = " ";
	char monsterName[50] = " ";
	char flavorText[50] = " ";
};

void ClearScreen();

void TableOfContents();

void CreateHelloWorld();

void SavePlayerData(saveData data);

saveData LoadPlayerData();

void MonsterCreatureQuest();

monster AddMonster();

void RemoveMonster(monster * list);

void ViewMonster(monster * list);

void BrowseMonsters(monster * list, size_t size);