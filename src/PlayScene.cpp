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

	m_pMassLabel->setText("Mass = " + SIMA::getMass() + " kg");
	
	m_pRampRiseLabel->setText("Rise = " + SIMA::getRise() + " m");
	m_pRampRunLabel->setText("Run = " + SIMA::getRun() + " m");
	
	m_pAngleLabel->setText("Angle = " + SIMA::getAngle());

	m_pAcceleration->setText("Acceleration: " + SIMA::getAcceleration() + " m/s2");
	m_pTimeOnRampLabel->setText("Time on ramp: " + SIMA::getTime() + " s");
	m_pTimeToStopLabel->setText("Time to stop: " + SIMA::getStopTime() + " s");
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

		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_Q))
		{
			if (EventManager::Instance().KeyPressed(SDL_SCANCODE_Q))
			{
				SIMA::changeMass(-Config::CHANGE_MASS);
			}
			if (m_changeMass++ > HOLD_TIME)
			{
				SIMA::changeMass(-Config::CHANGE_MASS);
			}
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_E))
		{
			if (EventManager::Instance().KeyPressed(SDL_SCANCODE_E))
			{
				SIMA::changeMass(Config::CHANGE_MASS);
			}
			if (m_changeMass++ > HOLD_TIME)
			{
				SIMA::changeMass(Config::CHANGE_MASS);
			}
		}
		else
		{
			m_changeMass = 0;
		}
		
		if (EventManager::Instance().KeyPressed(SDL_SCANCODE_SPACE))
		{
			SIMA::launchSimulation();
		}

		if (EventManager::Instance().KeyPressed(SDL_SCANCODE_H))
		{
			m_instructionsEnabled = !m_instructionsEnabled;
		}

	}

	if (EventManager::Instance().KeyPressed(SDL_SCANCODE_R))
	{
		SIMA::reset();
	}
	
	if (EventManager::Instance().KeyPressed(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}
}

void PlayScene::start()
{
	m_instructionsEnabled = false;
	
	// Label
	m_pBackground = new Background();
	m_pBackground->getTransform()->position = glm::vec2(0.0f, 0.0f);
	addChild(m_pBackground);

	m_pBox = new Box();
	m_pBox->getTransform()->position = glm::vec2(120.0f, 120.0f);
	addChild(m_pBox);

	SIMA::setBox(m_pBox);

	const SDL_Color white = { 10, 10, 40, 255 };
	m_pMassLabel = new Label("Mass", "Tusj", 30, white, glm::vec2(190.0f, 40.0f));
	m_pMassLabel->setParent(this);
	addChild(m_pMassLabel);

	m_pRampRiseLabel = new Label("Rise", "Tusj", 30, white, glm::vec2(190.0f, 75.0f));
	m_pRampRiseLabel->setParent(this);
	addChild(m_pRampRiseLabel);

	m_pRampRunLabel = new Label("Run", "Tusj", 30, white, glm::vec2(190.0f, 110.0f));
	m_pRampRunLabel->setParent(this);
	addChild(m_pRampRunLabel);

	m_pAngleLabel = new Label("Angle", "Tusj", 30, white, glm::vec2(190.0f, 145.0f));
	m_pAngleLabel->setParent(this);
	addChild(m_pAngleLabel);

	m_pTimeOnRampLabel = new Label("Time:", "Tusj", 30, white, glm::vec2(750.0f, 55.0f));
	m_pTimeOnRampLabel->setParent(this);
	addChild(m_pTimeOnRampLabel);

	m_pTimeToStopLabel = new Label("Time:", "Tusj", 30, white, glm::vec2(750.0f, 90.0f));
	m_pTimeToStopLabel->setParent(this);
	addChild(m_pTimeToStopLabel);

	m_pAcceleration = new Label("Land x pos:", "Tusj", 30, white, glm::vec2(750.0f, 125.0f));
	m_pAcceleration->setParent(this);
	addChild(m_pAcceleration);

	const SDL_Color light_green = { 10, 30, 10, 255 };
	std::string instructions[] = { "H - close instructions", "R - reset" ,"A|D - change run", "W|S - change rise", "Q|E - change mass",
		"SPACE - Launch Simulation" };
	for (int i = 0; i < 6; i++)
	{
		Label* m_pInstuctionsLabel = new Label(instructions[i], "Tusj", 30, light_green, glm::vec2(750.0f, 200.0f + 35.0f * i));
		m_pInstuctionsLabel->setParent(this);
		m_instructions.push_back(m_pInstuctionsLabel);
	}

	m_pShowInstuctionsLabel = new Label("H - open instructions", "Tusj", 30, light_green, glm::vec2(750.0f, 200.0f));
	m_pAcceleration->setParent(this);
}
