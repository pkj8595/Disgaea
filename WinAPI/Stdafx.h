#pragma once
#pragma comment(lib,"gdiplus")

/*
PreCompiled Header (PCH)
 - 필요한 이유는 cpp 하나당 컴파일러가 컴파일하여 .obj 파일을 만들고, obj 파일마다 코드 최적화를 매번 하기 힘들기 때문에 파일마다 파싱을 해줘야 한다.
												ㄴ컴파일 된 파일을

-최적화를 위해서, 실행속도 향상을 위해서 사용한다.
-컴파일 할때마다 올리기는 실행속도가 느리기 때문에 메모리에 미리 올려놓고 쓰겠다.
-자주 사용하지만 자주 바뀌지 않는 파일을 넣는게 좋다.
*/

//#include "targetver.h" // 윈도우 os 호환시 씀 근데 api에서는 
// 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

//프로그램에서 지원할 os에 따라 windows 헤더에서 
//코드에 포함될 함수 상수를 제어하는데 사용된다.
#include <SDKDDKVer.h>	//os마다 api한정으로 공통적인 함수들을 바꿔준다. 어뎁터?

//거의 사용되지 않는 내용은 windows헤더에서 제외
//ㄴGDI+를 사용하면 헤더파일 봉인해제 
//<ole.h>	GDI+ 를 쓸때 필요

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
//윈도우 내장 재생 라이브러리
//PlaySound()를 사용하기위해
#include <mmsystem.h>

//미디어 컨트롤 인터페이스 api
//mciSendString()를 사용하기위해 사용
//mci : media Control Interface
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
#include "TempSoundManager.h"
#include "TimeManager.h"
#include "Utils.h"
#include "CRectObserverManager.h"
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
#define TEMPSOUNDMANAGER TempSoundManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define TEXTDATAMANAGER TextDataManager::getSingleton()
#define RECTOBSERVERMANAGER CRectObserverManager::getSingleton()
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

//#define FULLSCREEN

#ifdef FULLSCREEN

//#ifdef FULLSCREEN
#define WINSTART_X		0
#define WINSTART_Y		0
//GetSystemMetrics() : 인자로 전달되는 시스템 설정정보 반환
//ㄴ SM_CXSCREEN : 현재 화면 해상도 X축반환
//ㄴ SM_CYSCREEN : 현재 화면 해상도 Y축반환
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
//헤더 cpp 에서 변수를 공유해서 쓰기 위함

extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;	// 마우스 사용시 xy
//extern mycustom::Image _CImage;  //깡통인데


