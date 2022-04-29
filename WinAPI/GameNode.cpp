#include "Stdafx.h"
#include "GameNode.h"



HRESULT GameNode::init(void)
{
	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if(managerInit)
	{
		setlocale(LC_ALL, "Korean");
		SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		RND->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		TEXTDATAMANAGER->init();
		SCENEMANAGER->init();
		SOUNDMANAGER->init();
		JSONDATAMANAGER->init();
		ANIMATIONMANAGER->init();
		CAMERA->init();
	}

	return S_OK;
}

void GameNode::release(void)
{
	if (_managerInit) 
	{
		//≈∏¿Ã∏” «ÿ¡¶ 
		KillTimer(_hWnd, 1);
		KEYMANAGER->releaseSingleton();

		RND->releaseSingleton();

		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		FONTMANAGER->releaseSingleton();

		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		TEXTDATAMANAGER->release();
		TEXTDATAMANAGER->releaseSingleton();

		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		JSONDATAMANAGER->release();
		JSONDATAMANAGER->releaseSingleton();
		
		ANIMATIONMANAGER->release();
		ANIMATIONMANAGER->releaseSingleton();

		CAMERA->release();
		CAMERA->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
}

void GameNode::update(void)
{
}

void GameNode::render(void)
{
}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_TIMER:
		break;
	case WM_CREATE:		
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_COMMAND:
		switch (wParam)
		{
		case 0x0001:
		{
			//≈∏¿Ã∆≤æ¿
			SetMapMode(getHDC(), MM_ISOTROPIC);
			RECT cameraRc = RectMake(0, 0, 0, 0);
			GetClientRect(_hWnd, &cameraRc);
			SetWindowExtEx(getHDC(), 600, 330, NULL);
			SetViewportExtEx(getHDC(), cameraRc.right, cameraRc.bottom, NULL);
		
			break;
		}
		case 0x0010:
		{
			//¿¸≈ıæ¿
			SetMapMode(getHDC(), MM_ISOTROPIC);
			RECT cameraRc = RectMake(0, 0, 0, 0);
			GetClientRect(_hWnd, &cameraRc);
			SetWindowExtEx(getHDC(), 410, 230, NULL);
			SetViewportExtEx(getHDC(), cameraRc.right, cameraRc.bottom, NULL);
			
			break;
		}
		case 0x0011:
		{
			//∏∂ø’º∫
			SetMapMode(getHDC(), MM_ISOTROPIC);
			RECT cameraRc = RectMake(0, 0, 0, 0);
			GetClientRect(_hWnd, &cameraRc);
			SetWindowExtEx(getHDC(), 485, 270, NULL);
			SetViewportExtEx(getHDC(), cameraRc.right, cameraRc.bottom, NULL);

			break;
		}
		case 0x1000:
		{
			SetMapMode(getHDC(), MM_ISOTROPIC);
			RECT cameraRc = RectMake(0, 0, 0, 0);
			GetClientRect(_hWnd, &cameraRc);
			SetWindowExtEx(getHDC(), LOWORD(lParam), HIWORD(lParam), NULL);
			SetViewportExtEx(getHDC(), cameraRc.right, cameraRc.bottom, NULL);
			break;
		}
		default:
			break;
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{

		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return( DefWindowProc(hWnd, iMessage, wParam, lParam));
}
