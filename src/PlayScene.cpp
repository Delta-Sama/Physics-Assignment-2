#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "SimulationManager.h"
#include "../Template/DebugManager.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();
	
	SIMA::update();

	if (m_instructionsEnabled)
	{
		for (Label* label : m_instructions)
		{
			label->draw();
		}
	}
	else
		m_pShowInstuctionsLabel->draw();
}

void PlayScene::update()
{
	updateDisplayList();

	m_pMassLabel->setText("Mass = " + std::to_string(SIMA::getMass()) + " kg");
	
	m_pRampRiseLabel->setText("Rise = " + std::to_string(static_cast<int>(SIMA::getRise()) * Config::PIX_TO_MET) + " m");
	m_pRampRunLabel->setText("Run = " + std::to_string(static_cast<int>(SIMA::getRun()) * Config::PIX_TO_MET) + " m");
	
	m_pAngleLabel->setText("Angle = " + std::to_string(SIMA::getAngle()));
	
	m_pTimeRequiredLabel->setText("Time required: " + std::to_string(SIMA::getTime()) + " s");
}

void PlayScene::clean()
{
	removeAllChildren();

	for (Label* label : m_instructions)
	{
		delete label;
	}
	delete m_pShowInstuctionsLabel;
	m_instructions.clear();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (!SIMA::getSimulation())
	{
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
			if (EventManager::Instance().KeyPressed(SDL_SCANCODE_A))
			{
				SIMA::changeRun(-Config::CHANGE_RUN);
			}
			if (m_changeRun++ > HOLD_TIME)
			{
				SIMA::changeRun(-Config::CHANGE_RUN);
			}
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			if (EventManager::Instance().KeyPressed(SDL_SCANCODE_D))
			{
				SIMA::changeRun(Config::CHANGE_RUN);
			}
			if (m_changeRun++ > HOLD_TIME)
			{
				SIMA::changeRun(Config::CHANGE_RUN);
			}
		}
		else
		{
			m_changeRun = 0;
		}
		
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
		{
			if (EventManager::Instance().KeyPressed(SDL_SCANCODE_W))
			{
				SIMA::changeRise(Config::CHANGE_RISE);
			}
			if (m_changeRise++ > HOLD_TIME)
			{
				SIMA::changeRise(Config::CHANGE_RISE);
			}
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
		{
			if (EventManager::Instance().KeyPressed(SDL_SCANCODE_S))
			{
				SIMA::changeRise(-Config::CHANGE_RISE);
			}
			if (m_changeRise++ > HOLD_TIME)
			{
				SIMA::changeRise(-Config::CHANGE_RISE);
			}
		}
		else
		{
			m_changeRise = 0;
		}

		

		if (EventManager::Instance().KeyPressed(SDL_SCANCODE_H))
		{
			m_instructionsEnabled = !m_instructionsEnabled;
		}

	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_R))
	{
		SIMA::reset();
	}
	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}
}

void PlayScene::start()
{
	m_instructionsEnabled = true;
	
	// Label
	m_pBackground = new Background();
	m_pBackground->getTransform()->position = glm::vec2(0.0f, 0.0f);
	addChild(m_pBackground);

	m_pBox = new Box();
	m_pBox->getTransform()->position = glm::vec2(120.0f, 120.0f);
	addChild(m_pBox);

	SIMA::setBox(m_pBox);

	const SDL_Color white = { 255, 255, 255, 255 };
	m_pMassLabel = new Label("Mass", "Tusj", 30, white, glm::vec2(160.0f, 40.0f));
	m_pMassLabel->setParent(this);
	addChild(m_pMassLabel);

	m_pRampRiseLabel = new Label("Rise", "Tusj", 30, white, glm::vec2(160.0f, 75.0f));
	m_pRampRiseLabel->setParent(this);
	addChild(m_pRampRiseLabel);

	m_pRampRunLabel = new Label("Run", "Tusj", 30, white, glm::vec2(160.0f, 110.0f));
	m_pRampRunLabel->setParent(this);
	addChild(m_pRampRunLabel);

	m_pAngleLabel = new Label("Angle", "Tusj", 30, white, glm::vec2(160.0f, 145.0f));
	m_pAngleLabel->setParent(this);
	addChild(m_pAngleLabel);

	m_pTimeRequiredLabel = new Label("Time:", "Tusj", 30, white, glm::vec2(750.0f, 20.0f));
	m_pTimeRequiredLabel->setParent(this);
	addChild(m_pTimeRequiredLabel);

	m_pCurrentLandPosLabel = new Label("Land x pos:", "Tusj", 30, white, glm::vec2(750.0f, 55.0f));
	m_pCurrentLandPosLabel->setParent(this);
	addChild(m_pCurrentLandPosLabel);

	const SDL_Color light_green = { 220, 255, 220, 255 };
	std::string instructions[] = { "H - close instructions", "R - reset" ,"A|D - change distance","W|S - change speed",
		"Mouse Click - Launch Simulation", "SPACE - target lock" };
	for (int i = 0; i < 6; i++)
	{
		Label* m_pInstuctionsLabel = new Label(instructions[i], "Tusj", 30, light_green, glm::vec2(750.0f, 140.0f + 35.0f * i));
		m_pInstuctionsLabel->setParent(this);
		m_instructions.push_back(m_pInstuctionsLabel);
	}

	m_pShowInstuctionsLabel = new Label("H - open instructions", "Tusj", 30, light_green, glm::vec2(750.0f, 140.0f));
	m_pCurrentLandPosLabel->setParent(this);
}
