#pragma once
#pragma comment(lib,"gdiplus")


#include <SDKDDKVer.h>	

//===================================
//! Windows ��� ����
//===================================
#define WIN32_LEAN_AND_MEAN          
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>

//! ���̺귯��
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#pragma comment(lib,"Winmm.lib")//win ��Ƽ �̵�� (�׷���ī�带 �ҷ��ö��� ���)
#pragma comment (lib, "msimg32.lib")//���ĺ��带 ����ϱ����� ���̺귯�� �߰�

//================= x64 =====================
//fmod.lib obj�ִ� debug���Ͽ� �ֱ�
//#pragma comment (lib, "lib/x64/fmod_vc.lib")
//#pragma comment (lib, "Jsoncpp/json_vc71_libmtd.lib")
//===========================================


#pragma comment (lib, "lib/x86/fmod_vc.lib")
#pragma comment (lib, "jsoncpp/x86/json_vc71_libmtd.lib")

//�ܺ� ���
#include "inc/fmod.hpp"
#include "jsoncpp/include/json.h"
//#include <Jsoncpp.json.h> //������ ���


//===================================
//! C ��Ÿ�� ��� ����
//===================================
//stdlib c��� ǥ�� ���̺귯�� �Լ� ��� 
#include <stdlib.h>
#include <time.h>
#include <tchar.h>
#include <mmsystem.h>
#include <mciapi.h>


//===================================
//! GDI+ connection
//===================================
#include <Ole2.h>//��ü ���� ����
#include <gdiplus.h>
using namespace Gdiplus;


//===================================
//! C++ ��Ÿ�� ���
//===================================
#include <iostream>
#include <random>
#include <bitset>
#include <vector>
#include <map>
#include <cassert>
#include <typeinfo>
#include <algorithm> 
#include <filesystem>
#include <fstream>
#include <queue>
#include <functional> 

using namespace std;
typedef function<void(void)> CALLBACKFUNCTION;

//===================================
//# ���� ���� ��������� �̰��� �߰� #
//===================================
#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "TimeManager.h"
#include "Utils.h"
#include "TextDataManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "JsonSaveLoader.h"
#include "AnimationManager.h"
#include "Camera.h"
#include "GameManager.h"

using namespace MY_UTIL;
//===================================
//# custom #
//===================================

//===================================
//# SingleTon #
//===================================

#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER	FontManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define TEXTDATAMANAGER TextDataManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()
#define SOUNDMANAGER SoundManager::getSingleton()
#define JSONDATAMANAGER JsonSaveLoader::getSingleton()
#define ANIMATIONMANAGER AnimationManager::getSingleton()
#define CAMERA Camera::getSingleton()
#define GAMEMANAGER GameManager::getSingleton()

//===================================
//# ��ũ�� # (������ �ʱ�ȭ)
//===================================

#define WINNAME			(LPSTR)(TEXT("WindowAPI"))

#define FULLSCREEN

#ifdef FULLSCREEN

//#ifdef FULLSCREEN
#define WINSTART_X		0
#define WINSTART_Y		0
#define WINSIZE_X		GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y		GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE		WS_POPUPWINDOW | WS_MAXIMIZE

#else

#define WINSTART_X		300
#define WINSTART_Y		0
#define WINSIZE_X		600
#define WINSIZE_Y		330
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#endif 

//===================================
//# ��ũ�� # (��� �� ȿ��)
//===================================
#define CENTER_X	WINSIZE_X/2
#define CENTER_Y	WINSIZE_Y/2

//===================================
//# ��ũ�� �Լ� # (Ŭ�������� ���� �Ҵ�� �κ� ����)
//===================================

#define SAFE_DELETE(p)			{if(p){delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p){delete[](p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p){(p)->release(); (p) = nullptr;} }


//����ǥ�� -> ���� ǥ�� ��ȯ
#define PI	3.141592653f
#define DEGREE_RADIAN(_deg)			(M_PI * (_deg)/180.0f)
//===================================
//# �������� #
//===================================

extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;	// ���콺 ���� xy


