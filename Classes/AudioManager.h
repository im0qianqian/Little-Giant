#ifndef __AUDIO_MANAGER_H__
#define __AUDIO_MANAGER_H__

#include "cocos2d.h"
#include "Weapons.h"

USING_NS_CC;

class AudioManager :public Ref
{
public:
	AudioManager();
	~AudioManager();
	virtual bool init();
	CREATE_FUNC(AudioManager);
};
#endif