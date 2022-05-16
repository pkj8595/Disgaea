#pragma once
#include "SingletonBase.h"


constexpr auto soundBuffer = 10;
//���� ä�� ���� (����)
constexpr auto extraSoundChannel = 5;
// �� ���� ����
constexpr auto totalSoundChannel = soundBuffer + extraSoundChannel;

using namespace FMOD;

class SoundManager:public SingletonBase<SoundManager>
{
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundsIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator arrChannelsIter;

	System* _system;
	Sound** _sound;			//���� ���� ������
	Channel** _channel;		//���� ä��

	arrSounds _mTotalSounds;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	void addSound(string keyName, string soundName, bool backGround, bool loop);

	//���� �÷���
	void play(string keyName, float volume);
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);

	int getSoundCount() { return _mTotalSounds.size(); }

	//sound ���� 
	unsigned int getLength(string keyName);
	//�÷��� ��ġ
	unsigned int getPosition(string keyName);
	void setPosition(string keyName, unsigned int position);

	float getVolume(string keyName);
	void setVolume(string keyName, float volume);
	void setAllVolume(float volume);

	SoundManager();
	~SoundManager();

};

