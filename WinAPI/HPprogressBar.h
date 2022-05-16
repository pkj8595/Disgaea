#pragma once



class HPprogressBar
{
private:
	float _nHp;

	RECT _rectMaxHp;
	RECT _rectHp;
	float _nMaxHp;
	float temp;
public:
	HPprogressBar() {}
	HPprogressBar(int hp);
	void RenderHpbar(HDC hdc);

	void UpdateHpBar(RECT * tager, int nHp);

};

