#pragma once
#include "Quest.h"

/*
ť(queue)
ť�� ����Ʈ�� �������� ���ð� �ٸ��� ���� ó���� �� �����Ͱ� ó���� ������ FIFO �ڷᱸ�� 
������ �Ͼ�� ���� ��(rear),������ �Ͼ�� �κ� ��(front)��� �Ѵ�.
����Ʈ ť, CPU �����ٸ�, ������ ����, BFS(�ʺ� �켱 Ž��)���� ����غ��� �Ѵ�.

front()
back()
push()
size()
empty()
*/
class QuestSample
{
private:
	queue< Quest*> _quest;

public:
	void init(void);
	void questSetup(Quest* pQuest = nullptr);

	queue<Quest*>* getQuest() { return &this->_quest; }

	QuestSample() {}
	~QuestSample() {}
};

