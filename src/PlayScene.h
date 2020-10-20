#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Background.h"
#include "Box.h"
#include "Scene.h"
#include "WayPoint.h"
#include "Player.h"
#include "Button.h"
#include "Enemy.h"

const int HOLD_TIME = 10;

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	glm::vec2 m_mousePosition;

	bool m_instructionsEnabled;

	int m_changeRun;
	int m_changeRise;

	Box* m_pBox;
	
	Background* m_pBackground;
	
	Label* m_pMassLabel;
	Label* m_pRampRiseLabel;
	Label*  m_pRampRunLabel;
	Label* m_pAngleLabel;

	Label* m_pShowInstuctionsLabel;
	std::vector<Label*> m_instructions;
	
	Label* m_pTimeRequiredLabel;
	Label* m_pAcceleration;
	
};

#endif /* defined (__PLAY_SCENE__) */