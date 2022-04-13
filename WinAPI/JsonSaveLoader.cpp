#include "Stdafx.h"
#include "JsonSaveLoader.h"

HRESULT JsonSaveLoader::init(void)
{
	//! Do Notting
	return S_OK;
}

void JsonSaveLoader::release(void)
{
	//! Do Notting
}

void JsonSaveLoader::saveString(char* fileName, string data)
{
	TCHAR* buf = (TCHAR*)data.c_str();
	HANDLE file;
	//BOM (바이트 오더 마크) : 바이트 순서 표식
	//파일이 열렸을때 바이트 오더 마크를 넣는다.
	//리틀엔디안 (오 >> 왼) 
	//빅엔디안 (왼 >> 오) 
	WORD BOM = 0xFEFF;
	DWORD dwBytes = 0;
	//DWORD dwRead;
	
	file = CreateFile(
		fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//INVALID_HANDLE_VALUE: 초기화를 위해 사용되며 값은 보통 -1
	if (file == INVALID_HANDLE_VALUE)
	{
		MessageBox(_hWnd, "생성 파일 에러", "에러", MB_OK);
	}
	else
	{
		//WriteFile(file, &BOM, 2, &dwBytes, NULL);
		WriteFile(file, buf, strlen(buf) * sizeof(TCHAR), &dwBytes, NULL);
		CloseHandle(file);
	}

}


string JsonSaveLoader::loadString(char* fileName)
{
	TCHAR buf[8193];
	ZeroMemory(buf, sizeof(buf));
	HANDLE file;
	DWORD dwBytes;

	file = CreateFile(
		fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file == INVALID_HANDLE_VALUE)
	{
		MessageBox(_hWnd, "생성 파일 에러", "에러", MB_OK);
		return "";
	}
	else
	{
		ReadFile(file, buf, 8192, &dwBytes, NULL);
		CloseHandle(file);
	}

	return string(buf);
}

void JsonSaveLoader::saveStringWithfilesStream(char* fileName, string data)
{
	ofstream outFile(fileName);
	outFile << data << endl;
	outFile.close();

}

string JsonSaveLoader::loadStringWithFileStream(char* fileName)
{
	ifstream fileIn;
	/*
	ios::in		파일 읽기만 가능한 모드로 개방
	ios::out	파일을 쓰기만 가능한 모드로 개방
	ios::ate	파일 개방이 될때 파일의 끝으로 파일포인터 이동
	ios::binary	바이너리 모드 개방
	ios::app	데이터를 맨 끝에서 부터 추가

	파일 입출력때는 재귀를 쓰면 안됨
	*/

	fileIn.open(fileName, ios::in);
	char data;
	string jsonStr;
	while (fileIn.get(data))
	{
		jsonStr += data;
	}
	fileIn.close();

	return jsonStr;
}


void JsonSaveLoader::saveJsonFile(char* fileName, Json::Value root)
{
	Json::StyledWriter writer;
	string outputConfig = writer.write(root);

	saveStringWithfilesStream(fileName, outputConfig);
}

Json::Value JsonSaveLoader::loadJsonFile(char* fileName)
{
	string jsonStr = loadStringWithFileStream(fileName);
	if (jsonStr == "")
	{
		MessageBox(_hWnd, "데이터가 없다.", "Warning", MB_OK);
		return NULL;
	}

	Json::Reader reader;
	Json::Value root;

	//파서 & 파싱
	//파싱 : 특정 문서를 읽어 들여서 이를 다른 프로그램이나 서브 루틴이 사용할 수 있는 내부의 표현방식으로 변환시켜주는것
	//파서 : 파싱을 해주는 프로세서

	bool parsingRet = reader.parse(jsonStr, root);
	if (!parsingRet)
	{
		//getFormatedErrorMessages외부라이브러리 에러난 곳을 상세하게 알려줌
		string errMessage = reader.getFormatedErrorMessages();
		MessageBox(_hWnd, errMessage.c_str(),"오류",MB_OK);
		PostQuitMessage(0);
	}

	return root;
}

