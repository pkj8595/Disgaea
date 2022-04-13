#pragma once
#include "SingletonBase.h"
/*
json �ڹٽ�ũ��Ʈ ������Ʈ �����̼�(JavaScript Object Notation)
-���ͳݿ��� �ڷḦ �ְ� ���� �� �� �ڷḦ ǥ���ϴ� ���
-�ڷ��� ������ ū ������ ������, Ư�� ��ǻ�� ���α׷��� ���� ���� ǥ���ϴµ� ���� ���� 
-�� ������ �ڹ� ��ũ��Ʈ�� ���� ������ ��������, ���α׷��� �� �÷����� "������"�̹Ƿ� C,C++�ڹ�,�ڹٽ�ũ��Ʈ ��,���̽� ��� ���� ��ü���� ���(+����)���� �̿��� �� �ִ�.

-XML, HTTP ���� "�밳"�� ��Ȳ���� �� ������.

*/
class JsonSaveLoader:public SingletonBase< JsonSaveLoader >
{
private:
	void saveString(char* fileName, string data);
	void saveStringWithfilesStream(char* fileName, string data);
	string loadString(char* fileName);
	string loadStringWithFileStream(char* fileName);

public:
	HRESULT init(void);
	void release(void);
	void saveJsonFile(char* fileName, Json::Value root);
	Json::Value loadJsonFile(char* fileName);

	JsonSaveLoader() {}
	~JsonSaveLoader() {}
};

