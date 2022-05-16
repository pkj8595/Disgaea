#pragma once
#pragma comment(lib,"gdiplus")


#include <SDKDDKVer.h>	

//===================================
//! Windows 헤더 파일
//===================================
#define WIN32_LEAN_AND_MEAN          
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>

//! 라이브러리
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#pragma comment(lib,"Winmm.lib")//win 멀티 미디어 (그래픽카드를 불러올때도 사용)
#pragma comment (lib, "msimg32.lib")//알파블렌드를 사용하기위한 라이브러리 추가

//================= x64 =====================
//fmod.lib obj있는 debug파일에 넣기
//#pragma comment (lib, "lib/x64/fmod_vc.lib")
//#pragma comment (lib, "Jsoncpp/json_vc71_libmtd.lib")
//===========================================


#pragma comment (lib, "lib/x86/fmod_vc.lib")
#pragma comment (lib, "jsoncpp/x86/json_vc71_libmtd.lib")

//외부 헤더
#include "inc/fmod.hpp"
#include "jsoncpp/include/json.h"
//#include <Jsoncpp.json.h> //정적의 경우


//===================================
//! C 런타임 헤더 파일
//===================================
//stdlib c언어 표준 라이브러리 함수 헤더 
#include <stdlib.h>
#include <time.h>
#include <tchar.h>
#include <mmsystem.h>
#include <mciapi.h>


//===================================
//! GDI+ connection
//===================================
#include <Ole2.h>//객체 연결 삽입
#include <gdiplus.h>
using namespace Gdiplus;


//===================================
//! C++ 런타임 헤더
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
//# 내가 만든 헤더파일을 이곳에 추가 #
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
//# 매크로 # (윈도우 초기화)
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
//# 매크로 # (기능 및 효율)
//===================================
#define CENTER_X	WINSIZE_X/2
#define CENTER_Y	WINSIZE_Y/2

//===================================
//# 매크로 함수 # (클래스에서 동적 할당된 부분 해제)
//===================================

#define SAFE_DELETE(p)			{if(p){delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p){delete[](p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p){(p)->release(); (p) = nullptr;} }


//각도표기 -> 라디안 표기 변환
#define PI	3.141592653f
#define DEGREE_RADIAN(_deg)			(M_PI * (_deg)/180.0f)
//===================================
//# 전역변수 #
//===================================

extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;	// 마우스 사용시 xy


