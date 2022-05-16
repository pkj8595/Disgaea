#include "Stdafx.h"
#include "Image.h"
#include "Animation.h"


namespace my {


	Image::Image() : _imageInfo(NULL),
		_fileName(NULL),
		_isTrans(FALSE),
		_transColor(RGB(0, 0, 0)),
		_blendImage(NULL)
	{
	}

	HRESULT Image::init(int width, int height)
	{
		if (_imageInfo != NULL) this->release();

	
		// DC 가져오기
		HDC hdc = GetDC(_hWnd);

		//이미지 정보 새로 생성 후 초기화
		_imageInfo = new IMAGE_INFO;
		_imageInfo->loadType = LOAD_EMPTY;
		_imageInfo->resID = 0;
		_imageInfo->hMemDc = CreateCompatibleDC(hdc);
		_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
		_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
		_imageInfo->width = width;
		_imageInfo->height = height;

		//파일 이름
		_fileName = NULL;
		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);

		if (_imageInfo->hBit == 0)
		{
			release();
			return E_FAIL;
		}

		//DC 해제
		ReleaseDC(_hWnd, hdc);

		return S_OK;
	}

	HRESULT Image::init(const DWORD resID, int width, int height, BOOL isTrans, COLORREF transColor)
	{
		if (_imageInfo != NULL) this->release();

		HDC hdc = GetDC(_hWnd);

		//이미지 정보 새로 생성 후 초기화
		_imageInfo = new IMAGE_INFO;
		_imageInfo->loadType = LOAD_RESOURCE;
		_imageInfo->resID = resID;
		_imageInfo->hMemDc = CreateCompatibleDC(hdc);
		_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID));
		_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
		_imageInfo->width = width;
		_imageInfo->height = height;

		//파일 이름
		_fileName = NULL;
		_isTrans = isTrans;
		_transColor = transColor;

		if (_imageInfo->hBit == 0)
		{
			release();
			return E_FAIL;
		}
		//DC 해제
		ReleaseDC(_hWnd, hdc);

		return S_OK;
	}

	HRESULT Image::init(const char *fileName, int width, int height, BOOL isTrans, COLORREF transColor)
	{
		if (_imageInfo != NULL) this->release();

		HDC hdc = GetDC(_hWnd);

		//이미지 정보 새로 생성 후 초기화
		_imageInfo = new IMAGE_INFO;
		_imageInfo->loadType = LOAD_FILE;
		_imageInfo->resID = 0;
		_imageInfo->hMemDc = CreateCompatibleDC(hdc);

		_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE); //LR_LOADFROMFILE : 로드 리소스
		_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
		_imageInfo->width = width;
		_imageInfo->height = height;


		int len = strlen(fileName);
		//사이즈 +1하는 이유 띄어쓰기 실수 방지
		_fileName = new CHAR[len + 1];//크기 할당(동적)
		strcpy_s(_fileName, len + 1, fileName);

		//파일 이름
		_isTrans = isTrans;
		_transColor = transColor;

		// 리소스 얻어오는데 실패했다.
		if (_imageInfo->hBit == 0)
		{
			release();
			return E_FAIL;
		}
		//DC 해제
		ReleaseDC(_hWnd, hdc);

		return S_OK;
	}

	HRESULT Image::init(const char* fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
	{
		if (_imageInfo != NULL) this->release();

		HDC hdc = GetDC(_hWnd);

		_imageInfo = new IMAGE_INFO;
		_imageInfo->loadType = LOAD_FILE;
		_imageInfo->resID = 0;
		_imageInfo->hMemDc = CreateCompatibleDC(hdc);

		_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE); 
		_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
		_imageInfo->x = x;
		_imageInfo->y = y;
		_imageInfo->width = width;
		_imageInfo->height = height;


		int len = strlen(fileName);
		_fileName = new CHAR[len + 1];//크기 할당(동적)
		strcpy_s(_fileName, len + 1, fileName);

		//파일 이름
		_isTrans = isTrans;
		_transColor = transColor;

		if (_imageInfo->hBit == 0)
		{
			release();
			return E_FAIL;
		}
		//DC 해제
		ReleaseDC(_hWnd, hdc);

		return S_OK;
	}

	HRESULT Image::init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
	{
		if (_imageInfo != NULL) this->release();

		HDC hdc = GetDC(_hWnd);

		//이미지 정보 새로 생성 후 초기화
		_imageInfo = new IMAGE_INFO;
		_imageInfo->loadType = LOAD_FILE;
		_imageInfo->resID = 0;
		_imageInfo->hMemDc = CreateCompatibleDC(hdc);

		_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE); //LR_LOADFROMFILE : 로드 리소스
		_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
		_imageInfo->width = width;
		_imageInfo->height = height;
		_imageInfo->currentFrameX = 0;
		_imageInfo->currentFrameY = 0;
		_imageInfo->maxFrameX = maxFrameX - 1;
		_imageInfo->maxFrameY = maxFrameY - 1;
		_imageInfo->frameWidth = width / maxFrameX;
		_imageInfo->frameHeight = height / maxFrameY;


		int len = strlen(fileName);
		_fileName = new CHAR[len + 1];
		strcpy_s(_fileName, len + 1, fileName);

		//파일 이름
		_isTrans = isTrans;
		_transColor = transColor;

		// 리소스 얻어오는데 실패했다.
		if (_imageInfo->hBit == 0)
		{
			release();
			return E_FAIL;
		}
		//DC 해제
		ReleaseDC(_hWnd, hdc);

		return S_OK;
	}

	HRESULT Image::init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
	{
		if (_imageInfo != NULL) this->release();

		HDC hdc = GetDC(_hWnd);

		//이미지 정보 새로 생성 후 초기화
		_imageInfo = new IMAGE_INFO;
		_imageInfo->loadType = LOAD_FILE;
		_imageInfo->resID = 0;
		_imageInfo->hMemDc = CreateCompatibleDC(hdc);

		_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE); //LR_LOADFROMFILE : 로드 리소스
		_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
		_imageInfo->x = x;
		_imageInfo->y = y;
		_imageInfo->width = width;
		_imageInfo->height = height;
		_imageInfo->currentFrameX = 0;
		_imageInfo->currentFrameY = 0;
		_imageInfo->maxFrameX = maxFrameX - 1;
		_imageInfo->maxFrameY = maxFrameY - 1;
		_imageInfo->frameWidth = width / maxFrameX;
		_imageInfo->frameHeight = height / maxFrameY;


		int len = strlen(fileName);
		_fileName = new CHAR[len + 1];
		strcpy_s(_fileName, len + 1, fileName);

		//파일 이름
		_isTrans = isTrans;
		_transColor = transColor;

		// 리소스 얻어오는데 실패했다.
		if (_imageInfo->hBit == 0)
		{
			release();
			return E_FAIL;
		}
		//DC 해제
		ReleaseDC(_hWnd, hdc);

		return S_OK;
	}

	HRESULT Image::initForAlphaBlend(void)
	{
		// DC 가져오기
		HDC hdc = GetDC(_hWnd);

		_blendFunc.BlendFlags = 0;			
		_blendFunc.AlphaFormat = 0;			
		_blendFunc.BlendOp = AC_SRC_OVER;	


		//이미지 정보 새로 생성 후 초기화
		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_FILE;
		_blendImage->resID = 0;
		_blendImage->hMemDc = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDc, _blendImage->hBit);
		_blendImage->width = WINSIZE_X;
		_blendImage->height = WINSIZE_Y;

		//DC 해제
		ReleaseDC(_hWnd, hdc);

		return S_OK;
	}

	void Image::setTransColor(BOOL isTrans, COLORREF transColor)
	{
		_isTrans = isTrans;
		_transColor = transColor;
	}

	void Image::release(void)
	{
		if (_imageInfo)
		{
			//이미지 삭제
			SelectObject(_imageInfo->hMemDc, _imageInfo->hOBit);
			DeleteObject(_imageInfo->hBit);
			DeleteDC(_imageInfo->hMemDc);

			SAFE_DELETE(_imageInfo);
			SAFE_DELETE_ARRAY(_fileName);

			_isTrans = FALSE;
			_transColor = RGB(0, 0, 0);
		}

		if (_blendImage)
		{
			SelectObject(_blendImage->hMemDc, _blendImage->hOBit);
			DeleteObject(_blendImage->hBit);
			DeleteDC(_blendImage->hMemDc);

			SAFE_DELETE(_blendImage);
		}
	}

	//렌더 (0, 0 지점에 렌더)
	void Image::render(HDC hdc)
	{

		if (_isTrans)
		{	
			
			GdiTransparentBlt
			(
				hdc,					//복사할 장소의 DC(화면에 보여줄))
				0,						//복사될 시작 좌표 X
				0,						//복사될 시작 좌표 Y
				_imageInfo->width,		//복사될 이미지 가로 크기
				_imageInfo->height,		//복사될 이미지 세로 크기
				_imageInfo->hMemDc,		//복사될 대상 메모리 DC
				0, 0,					//복사 시작 지점
				_imageInfo->width,		//복사 영역 가로 크기
				_imageInfo->height,		//복사 영역 세로 크기
				_transColor				//복사할 때 제외할 색상

			);
		}

		else
		{
			BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDc, 0, 0, SRCCOPY);
		}
	}

	void Image::render(HDC hdc, int destX, int destY)
	{
		if (_isTrans)
		{
			GdiTransparentBlt
			(
				hdc,					//복사할 장소의 DC (화면 DC (화면에 보여줄))
				destX,					//복사될 시작 좌표 X
				destY,					//복사될 시작 좌표 Y
				_imageInfo->width,		//복사될 이미지 가로 크기
				_imageInfo->height,		//복사될 이미지 세로 크기
				_imageInfo->hMemDc,		//복사될 대상 메모리 DC
				0, 0,					//복사 시작 지점
				_imageInfo->width,		//복사 영역 가로 크기
				_imageInfo->height,		//복사 영역 세로 크기
				_transColor				//복사할 때 제외할 색상

			);
		}

		else
		{
			BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDc, 0, 0, SRCCOPY);
		}
	}

	//클리핑
	void Image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
	{
		if (_isTrans)
		{
			GdiTransparentBlt
			(
				hdc,					//복사할 장소의 DC (화면 DC (화면에 보여줄))
				destX,					//복사될 시작 좌표 X
				destY,					//복사될 시작 좌표 Y
				sourWidth,				//복사될 이미지 가로 크기
				sourHeight,				//복사될 이미지 세로 크기
				_imageInfo->hMemDc,		//복사될 대상 메모리 DC
				sourX,					//자를 좌표 x
				sourY,					//자를 좌표 y
				sourWidth,				//자를크기
				sourHeight,				//자를크기
				_transColor				//복사할 때 제외할 색상
			);
		}

		else
		{
			BitBlt(hdc, destX, destY, sourWidth, sourHeight, _imageInfo->hMemDc, sourX, sourY, SRCCOPY);
		}
	}

	void Image::alphaRender(HDC hdc, BYTE alpha)
	{
		//알파 블렌드를 처음 사용하는지?
		if (!_blendImage) initForAlphaBlend();

		_blendFunc.SourceConstantAlpha = alpha;

		if (_isTrans)
		{

			BitBlt
			(
				_blendImage->hMemDc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				hdc,
				0, 0,
				SRCCOPY
			);

			GdiTransparentBlt
			(
				_blendImage->hMemDc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_imageInfo->hMemDc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_transColor
			);
			AlphaBlend
			(
				hdc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_blendImage->hMemDc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_blendFunc
			);
		}
		else
		{
			AlphaBlend
			(
				hdc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_imageInfo->hMemDc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_blendFunc
			);
		}
	}

	void Image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
	{
		if (!_blendImage) initForAlphaBlend();

		_blendFunc.SourceConstantAlpha = alpha;

		if (_isTrans)
		{
			BitBlt
			(
				_blendImage->hMemDc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				hdc,
				destX, destY,
				SRCCOPY
			);
			GdiTransparentBlt
			(
				_blendImage->hMemDc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_imageInfo->hMemDc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_transColor
			);

			AlphaBlend
			(
				hdc,
				destX, destY,
				_imageInfo->width,
				_imageInfo->height,
				_blendImage->hMemDc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_blendFunc
			);
		}
		else
		{
			AlphaBlend
			(
				hdc,
				destX, destY,
				_imageInfo->width,
				_imageInfo->height,
				_imageInfo->hMemDc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_blendFunc
			);
		}
	}

	void Image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
	{
	}

	void Image::frameRender(HDC hdc, int destX, int destY)
	{
		if (_isTrans)
		{
			GdiTransparentBlt
			(
				hdc,					
				destX,					
				destY,					
				_imageInfo->frameWidth,	
				_imageInfo->frameHeight,
				_imageInfo->hMemDc,		
				_imageInfo->currentFrameX * _imageInfo->frameWidth,
				_imageInfo->currentFrameY * _imageInfo->frameHeight,
				_imageInfo->frameWidth,	
				_imageInfo->frameHeight,
				_transColor				

			);
		}

		else
		{
			BitBlt(hdc, destX, destY,
				_imageInfo->frameWidth,
				_imageInfo->frameHeight,
				_imageInfo->hMemDc,
				_imageInfo->currentFrameX * _imageInfo->frameWidth,
				_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
		}
	}

	void Image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
	{
		_imageInfo->currentFrameX = currentFrameX;
		_imageInfo->currentFrameY = currentFrameY;
		if (currentFrameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
		if (currentFrameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}

		if (_isTrans)
		{
			GdiTransparentBlt
			(
				hdc,
				destX,
				destY,
				_imageInfo->frameWidth,
				_imageInfo->frameHeight,
				_imageInfo->hMemDc,
				_imageInfo->currentFrameX * _imageInfo->frameWidth,
				_imageInfo->currentFrameY * _imageInfo->frameHeight,
				_imageInfo->frameWidth,	
				_imageInfo->frameHeight,
				_transColor				

			);
		}

		else
		{
			BitBlt(hdc, destX, destY,
				_imageInfo->frameWidth,
				_imageInfo->frameHeight,
				_imageInfo->hMemDc,
				_imageInfo->currentFrameX * _imageInfo->frameWidth,
				_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
		}
	}

	void Image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
	{
		_imageInfo->currentFrameX = currentFrameX;
		_imageInfo->currentFrameY = currentFrameY;
		if (currentFrameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
		if (currentFrameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}

		if (!_blendImage) initForAlphaBlend();

		_blendFunc.SourceConstantAlpha = alpha;

		if (_isTrans)
		{
			BitBlt(	
				_blendImage->hMemDc,
				0, 0,
				_imageInfo->frameWidth,
				_imageInfo->frameHeight,
				hdc,
				destX, destY,
				SRCCOPY
			);

			GdiTransparentBlt(
				_blendImage->hMemDc,
				0, 0,
				_imageInfo->frameWidth, 
				_imageInfo->frameHeight,
				_imageInfo->hMemDc,     
				_imageInfo->currentFrameX * _imageInfo->frameWidth,
				_imageInfo->currentFrameY * _imageInfo->frameHeight,      
				_imageInfo->frameWidth,      
				_imageInfo->frameHeight,   
				_transColor
			);         

			GdiAlphaBlend(
				hdc, 
				destX, destY,
				_imageInfo->frameWidth,
				_imageInfo->frameHeight,
				_blendImage->hMemDc,
				0, 0,
				_imageInfo->frameWidth,
				_imageInfo->frameHeight,
				_blendFunc);
		}
		else
		{
			GdiAlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
				_imageInfo->hMemDc, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
		}

	}

	void Image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
	{
		if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
		if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

		RECT rcSour;
		int sourWidth;
		int sourHeight;

		RECT rcDest;

		int drawAreaX = drawArea->left;
		int drawAreaY = drawArea->top;
		int drawAreaW = drawArea->right - drawArea->left;
		int drawAreaH = drawArea->bottom - drawArea->top;


		for (int y = 0; y < drawAreaH; y += sourHeight)
		{
			rcSour.top = (y + offsetY) % _imageInfo->height;
			rcSour.bottom = _imageInfo->height;
			sourHeight = rcSour.bottom - rcSour.top;

			if (y + sourHeight > drawAreaH)
			{
				rcSour.bottom -= (y + sourHeight) - drawAreaH;
				sourHeight = rcSour.bottom - rcSour.top;
			}

			rcDest.top = y + drawAreaY;
			rcDest.bottom = rcDest.top + sourHeight;

			for (int x = 0; x < drawAreaW; x += sourWidth)
			{
				rcSour.left = (x + offsetX) % _imageInfo->width;
				rcSour.right = _imageInfo->width;
				sourWidth = rcSour.right - rcSour.left;

				if (x + sourWidth > drawAreaW)
				{
					rcSour.right -= (x + sourWidth) - drawAreaW;
					sourWidth = rcSour.right - rcSour.left;
				}
				rcDest.left = x + drawAreaX;
				rcDest.right = rcDest.left + sourWidth;

				render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);

			}
		}


	}

	void Image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
	{

	}
	void Image::aniRender(HDC hdc, int destX, int destY, Animation* ani)
	{
		render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
	}
}