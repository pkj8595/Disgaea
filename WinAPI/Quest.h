#pragma once

enum QUEST_TYPE
{
	QUEST_STAGE_1,
};

class Quest
{
protected:
	int _exp;
	int _gold;
	int _monster;

	string _name;
	string _item;
	string _description;
	string _questCheck;
	string _monsterName;
	string _questStage;
	
	QUEST_TYPE _questType;

public:
	void init(string name, int gold, int exp, string description, string item, int monster, string questCheck, string monsterName, string questStage);

	string getName() { return this->_name; }
	int getGold() { return this->_gold; }
	int getExp() { return this->_exp; }
	int getMonster() { return this->_monster; }

	string getItem() { return this->_item; }
	string getDescription() { return this->_description; }
	string getQuestCheck() { return this->_questCheck; }
	string getMosterName() { return this->_monsterName; }
	string getQuestStage() { return this->_questStage; }
	QUEST_TYPE getQuestType() { return this->_questType; }

	Quest() {}
	~Quest() {}
};

