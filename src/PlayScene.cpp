#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "SimulationManager.h"

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

	m_pEnemies->getTransform()->position = glm::vec2(Config::START_POINT + SIMA::getDistance() * Config::MET_TO_PIX - m_pEnemies->getWidth(),
		Config::START_Y - m_pEnemies->getHeight() / 2);

	m_pMassLabel->setText("Mass = " + std::to_string(static_cast<int>(SIMA::getDistance())) + " m");
	m_pRampRiseLabel->setText("Angle = " + std::to_string(SIMA::getAngle()));
	if (SIMA::getAngle() == 0.0f && SIMA::getDistance() != 0)
	{
		m_pRampRiseLabel->setText("impossible to reach");
	}
	m_pRampRunLabel->setText("Speed = " + std::to_string(static_cast<int>(SIMA::getSpeed())) + " m\s");

	m_pTimeRequiredLabel->setText("Time required: " + std::to_string(SIMA::getTime()) + " s");
	m_pCurrentLandPosLabel->setText("Land pos.x: " + std::to_string(static_cast<int>(SIMA::getLandPos())) + " m");
	
	if (SIMA::getProjectile())
	{
		std::string pos = std::to_string(static_cast<int>((SIMA::getProjectile()->getTransform()->position.x - Config::START_X) * Config::PIX_TO_MET)) + ";"
           + std::to_string(static_cast<int>((Config::START_Y - SIMA::getProjectile()->getTransform()->position.y) * Config::PIX_TO_MET));
		m_pAngleLabel->setText("Proj: (" + pos + ")");
	}
	else
		m_pAngleLabel->setText(" ");
	
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
			SIMA::changeDistance(-Config::CHANGE_DIST);
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			SIMA::changeDistance(Config::CHANGE_DIST);
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
	
	m_pWookiee = new Player();
	m_pWookiee->getTransform()->position = glm::vec2(Config::START_X, Config::START_Y - m_pWookiee->getHeight()/2);
	addChild(m_pWookiee);

	m_pEnemies = new Enemy();
	m_pEnemies->getTransform()->position = glm::vec2(850.0f, Config::START_Y - m_pEnemies->getHeight() / 2);
	addChild(m_pEnemies);

	const SDL_Color white = { 255, 255, 255, 255 };
	m_pMassLabel = new Label("Maxx", "Tusj", 30, white, glm::vec2(160.0f, 40.0f));
	m_pMassLabel->setParent(this);
	addChild(m_pMassLabel);

	m_pRampRiseLabel = new Label("Rise", "Tusj", 30, white, glm::vec2(160.0f, 75.0f));
	m_pRampRiseLabel->setParent(this);
	addChild(m_pRampRiseLabel);

	m_pRampRunLabel = new Label("Run", "Tusj", 30, white, glm::vec2(160.0f, 110.0f));
	m_pRampRunLabel->setParent(this);
	addChild(m_pRampRunLabel);

	m_pAngleLabel = new Label("Angle", "Tusj", 30, white, glm::vec2(160.0f, 285.0f));
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
