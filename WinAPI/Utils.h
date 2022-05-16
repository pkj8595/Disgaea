#pragma once
//===================================
//# Utils # (간소화 시키고 싶은 로직,수학적 기능들을 모아둔 곳)
//===================================

#define DEG_TO_RAD		0.017453f
#define PI				3.141592653f
#define PI_2			6.283185308f

#define FLOAT_EPSILON	0.001f
#define FLOAT_TO_INT	static_cast<int>(f1+FLOAT_EPSILON)
#define FLOAT_EQUAL(f1,f2) (fabs(f1-f2)<= FLOAT_EPSILON)

namespace MY_UTIL 
{
	float getDistance(float startX,float startY, float endX,float endY);
	float getAngle(float startX, float startY, float endX, float endY);
	vector<string>  getFilesInDirectory(const string& _path, const string& _filter = "*.*");

	void testCallBack(void);

}
