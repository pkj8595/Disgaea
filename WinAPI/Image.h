#pragma once


class Animation;

namespace my {

class Image
{
public:

	enum IMAGE_LOAD_KIND 
	{
		LOAD_RESOURCE = 0,	//리소스
		LOAD_FILE,		//파일
		LOAD_EMPTY,		//빈 비트맵
		LOAD_END		//아무것도 정의하지 않는 것
	};
	
	typedef struct tagImage 
	{
		DWORD		resID;		//리소스 아이디
		HDC			hMemDc;		//메모리 디시 (맵)
		HBITMAP		hBit;		//비트맵
		HBITMAP		hOBit;		//올드 비트맵
		float		x;
		float		y;
		int			width;		//가로크기
		int			height;		//세로크기
		int			currentFrameX;
		int			currentFrameY;
		int			maxFrameX;
		int			maxFrameY;
		int			frameWidth;
		int			frameHeight;

		BYTE		loadType;	//이미지 타입

		tagImage()
		{
			resID = 0;
			hMemDc = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = y =0;
			width =0;
			height=0;
			loadType=0;
			currentFrameX=0;
			currentFrameY=0;
			maxFrameX=0;
			maxFrameY=0;
			frameWidth=0;
			frameHeight=0;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		
	CHAR*			_fileName;		
	BOOL			_isTrans;		
	COLORREF		_transColor;	

	BLENDFUNCTION	_blendFunc;		
	LPIMAGE_INFO	_blendImage;	//블랜드 이미지 

public:
	//빈 비트맵 초기화
	HRESULT init(int width, int height);

	//이미지 리소스 초기화
	HRESULT init(const DWORD resID, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	
	//이미지 파일로 초기화
	HRESULT init(const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//프레임 이미지 파일 초기화
	HRESULT init(const char* fileName,float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//좌표 x
	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	HRESULT init(const char* fileName, float x, float y, int width, int height,int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));


	//알파 블렌드 초기화
	HRESULT initForAlphaBlend(void);

	//투명 컬러키 셋팅(배경색 날릴건지, 어떤색깔)
	void setTransColor(BOOL isTrans, COLORREF transColor);

	//해제
	void release(void);

	//렌더 
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	//클리핑
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//알파 렌더(알파값은 BYTE로 사용 크기가 딱 맞음.)
	void alphaRender(HDC hdc, BYTE alpha);//배경
	void alphaRender(HDC hdc,int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc,int destX, int destY,int sourX, int sourY, int sourWidth,int sourHeight, BYTE alpha); //클리핑 알파렌더
	
	//프레임 렌더
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY,int currentFrameX, int currentFrameY);
	void alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY,BYTE alpha);
	
	//루프 렌더
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	void aniRender(HDC hdc, int destX, int destY, Animation* ani);

	//================
	//#인라인 함수#
	//================

	inline HDC getMemDC(void) { return _imageInfo->hMemDc; }

	//이미지 좌표
	inline float getX(void) { return _imageInfo->x; }
	inline float getY(void) { return _imageInfo->y; }


	inline void setX(float x) {_imageInfo->x = x; }
	inline void setY(float y) {_imageInfo->y = y; }

	inline void setCenter(float x, float y) 
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//이미지 가로 세로크기
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	//바운딩 박스 
	inline RECT boundingBox(void) 
	{
		RECT rc =
		{
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->width,
			(int)_imageInfo->y + _imageInfo->height,
		};
		return rc;
	}

	inline RECT boundingBoxWithFrame(void)
	{
		RECT rc =
		{
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->frameWidth,
			(int)_imageInfo->y + _imageInfo->frameHeight,
		};
		return rc;
	}

	//프레임 X
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX) 
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX) 
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	//프레임 Y
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY) 
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY) 
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}
	//이미지 1프레임 가로 세로 크기
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	//최대 프레임 xy갯수
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }


	Image();
	~Image() {}
};

}