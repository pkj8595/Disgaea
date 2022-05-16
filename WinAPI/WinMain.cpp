#include "Stdafx.h"
#include "MainGame.h"

//=======================
// # 전역변수 #
//=======================
HINSTANCE _hInstance;     
//윈도우 핸들
HWND _hWnd;
POINT _ptMouse = { 0,0 };
MainGame* _mg;
LPRECT _cameraRc;


//================
//#함수 전방 선언#
//================
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void SetWindowSize(int x, int y, int width, int height);


//! window main 함수 
int APIENTRY WinMain( HINSTANCE hInstance,
						HINSTANCE hPrevInstance,
						LPSTR    lpszCmdParam,
						int       nCmdShow)
{
	_mg = new MainGame();

	_hInstance = hInstance;

	//GDI+
	ULONG_PTR m_gdiplusToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	if (GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL) != Gdiplus::Ok)
	{
		MessageBox(NULL, TEXT("GDI+ 라이브러리를 초기화할 수 없습니다."),
		TEXT("알림"), MB_OK);
		return 0;
	}

	//1-1 윈도우창 구조체 선언 및 초기화
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;										//클래스 여분 메모리
	wndClass.cbWndExtra = 0;										//윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));	//백그라운드
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//마우스 커서
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//아이콘
	wndClass.hInstance = hInstance;									//윈도우를 소유한 식별자 정의
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//윈도우 프로시저
	wndClass.lpszClassName = WINNAME;							//클래스이음
	wndClass.lpszMenuName = NULL;									//메뉴이름
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//윈도우 스타일

	//1-2. 윈도우 클래스 등록
	RegisterClass(&wndClass);

#ifdef FULLSCREEN
	//디바이스 모드 구조체 (화면 디스플레이 관련 기능)
	DEVMODE dm;
	ZeroMemory(&dm, sizeof(DEVMODE));

	dm.dmBitsPerPel = 32;		//32비트 트루컬러
	dm.dmPelsWidth = 1980;		//가로해상도
	dm.dmPelsHeight = 1020;		//세로해상도
	dm.dmDisplayFrequency = 60;	//재생빈도

	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	//화면이 종료되면 자동으로 원래 화면의 해상도로 복구
	if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) 
	{
		ChangeDisplaySettings(&dm, 0);
	}

	_hWnd = CreateWindow
	(
		WINNAME,				//윈도우 클래스 식별자
		WINNAME,				//윈도우 타이틀 바 이름
		WINSTYLE,				//윈도우 스타일
		WINSTART_X,					//윈도우 화면 x좌표
		WINSTART_Y,					//윈도우 화면 Y좌표
		WINSIZE_X,					//윈도우 화면 가로크기
		WINSIZE_Y,					//윈도우 화면 세로크기
		NULL,					//부모 윈도우 GetDesktopWindow,
		(HMENU)NULL,			//메뉴핸들
		hInstance,				//인스턴스 지정
		NULL					//윈도우의 자식 윈도우를 생성하면 지정, 그렇지않으면 null
								// ㄴ 필요에 의해서 사용하지만 지금은 NULL
	);
	SetWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);


#else

	//1-3. 화면에 보여줄 윈도우 창 생성
	_hWnd = CreateWindow
	(
		WINNAME,				//윈도우 클래스 식별자
		WINNAME,				//윈도우 타이틀 바 이름
		WINSTYLE,				//윈도우 스타일
		WINSTART_X,					//윈도우 화면 x좌표
		WINSTART_Y,					//윈도우 화면 Y좌표
		WINSIZE_X,					//윈도우 화면 가로크기
		WINSIZE_Y,					//윈도우 화면 세로크기
		NULL,					//부모 윈도우 GetDesktopWindow,
		(HMENU)NULL,			//메뉴핸들
		hInstance,				//인스턴스 지정
		NULL					//윈도우의 자식 윈도우를 생성하면 지정, 그렇지않으면 null
								// ㄴ 필요에 의해서 사용하지만 지금은 NULL
	);
	SetWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

#endif

	//1-4. 화면에 윈도우 창 보여주기
	ShowWindow(_hWnd, nCmdShow);


	if (FAILED(_mg->init())) 
	{
		return 0;
	}

	//2. MSG : 운영체제에서 발생하는 메세지 정보를 저장하기 위한 구조체
	MSG message;

	
	
	while (true) 
	{
		
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) 
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else 
		{
			TIMEMANAGER->update(60.0f);
			_mg->update();
			_mg->render();
		}

	}

	_mg->release();
	SAFE_DELETE(_mg);
	//!윈도우 클래스 등록 해제
	UnregisterClass(WINNAME, hInstance);
	Gdiplus::GdiplusShutdown(m_gdiplusToken);

	return message.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	
	return _mg->MainProc(hWnd, iMessage, wParam, lParam);

}

//윈도우 화면 맞추기
void SetWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0,0,width,height };
	AdjustWindowRect(&rc, WINSTYLE, false);
	SetWindowPos(_hWnd, NULL, x, y, 
				(rc.right - rc.left),
				(rc.bottom - rc.top),
				SWP_NOZORDER | SWP_NOMOVE);

}
