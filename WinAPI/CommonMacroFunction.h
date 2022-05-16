#pragma once


inline POINT PointMake(int  x, int y)
{
	POINT pt = {(LONG)x, (LONG)y};
	return pt;
}

inline void LineMake(HDC hdc,int startX,int startY,int endX,int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}
	
inline RECT RectMake(int x, int y, int width, int height) 
{
	RECT rc = { (LONG)x, (LONG)y,(LONG)x + width,(LONG)y + height };
	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { (LONG)x - width / 2 , (LONG)y - height / 2,(LONG)x + width / 2 , (LONG)y + height / 2 };
	return rc;

}

inline void RectangleMake(HDC hdc, int x, int y, int width, int height) 
{
	Rectangle(hdc,x, y, x + width, y + height);
}

inline void RectangleMakeToRECT(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}


inline void EllipsMake(HDC hdc, int x, int y, int width, int height) 
{
	Ellipse(hdc, x, y, x + width, y + width);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height) 
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}


inline bool RectCollider(RECT rcA, RECT rcB)
{
	if (rcA.left <= rcB.right  &&
		rcA.top <= rcB.bottom &&
		rcA.right >= rcB.left &&
		rcA.bottom >= rcB.top)
	{
		return true;
	}
	return false;
}


inline bool RectCollider2(RECT rcA, RECT rcB)
{
	if (rcA.left < rcB.right  &&
		rcA.top < rcB.bottom &&
		rcA.right > rcB.left &&
		rcA.bottom > rcB.top)
	{
		return true;
	}
	return false;
}

inline int ChangeAlpha(int& alpha, int size)
{
	if (alpha < 0)
	{
		return 0;
	}
	else if (alpha > 255)
	{
		return 255;
	}
	alpha += size;

	return alpha;
}

inline float mRangeNum(float startNum, float smallEnd, float bigEnd, float size,bool &isinc )
{
	if (startNum < smallEnd )
	{
		isinc = true;
		startNum = smallEnd;
	}
	else if (startNum > bigEnd) 
	{
		isinc = false;
		startNum = bigEnd;
	}

	startNum += isinc?  size : -size;
	
	return startNum;
}

inline RectF GPRectFMakeCenter(REAL width, REAL height)
{
	RectF rc = {-width / 2 ,-height / 2, width, height };
	return rc;

}

inline RECT CollisionAreaResizing(RECT &rcDest, int width, int height) 
{
	RECT rc = { rcDest.left + width / 2,
				rcDest.top + height / 2,
				rcDest.right - width / 2,
				rcDest.bottom - height / 2 };
	return rc;
}

inline POINT LinearMovePoint(POINT start, POINT end, float splitCount, int count)
{
	float x = start.x + (((end.x - start.x) * (1 / splitCount)) *(float)count);
	float y = start.y + (((end.y - start.y) * (1 / splitCount)) *(float)count);

	return { (LONG)x,(LONG)y };
}

inline bool IsSamePoint(POINT pt1, POINT pt2)
{
	if (pt1.x == pt2.x && pt1.y == pt2.y) return true;
	else return false;
}