#include "SimulationManager.h"

#include <iostream>
#include <glm/detail/func_trigonometric.inl>

#include "Config.h"
#include "EventManager.h"
#include "WayPoint.h"
#include "../Template/DebugManager.h"

float SIMA::m_time = 0.0f;
float SIMA::m_curtime = 0.0f;

float SIMA::m_angle = Config::START_ANGLE;
float SIMA::m_mass = Config::START_MASS;
int SIMA::m_rise = Config::START_RISE;
int SIMA::m_run = Config::START_RUN;
float SIMA::m_timeVar = 0.0f;
bool SIMA::m_simulation = false;

Box* SIMA::m_pBox;

SimulationManager::SimulationManager() {}

SimulationManager::~SimulationManager() = default;

void SimulationManager::drawRamp()
{
	DebugManager::DrawWideLine(4, { Config::START_X,Config::START_Y }, { Config::START_X + m_run,Config::START_Y }, { 255,0,0,255 });
	DebugManager::DrawWideLine(4, { Config::START_X,Config::START_Y }, { Config::START_X,Config::START_Y - m_rise }, { 255,0,0,255 });
	DebugManager::DrawWideLine(4, { Config::START_X + m_run,Config::START_Y }, { Config::START_X,Config::START_Y - m_rise }, { 255,0,0,255 });

	float angle = atan2(m_rise,m_run);

	float size_x = m_pBox->getWidth() / 2;
	float size_y = m_pBox->getHeight() / 2;
	m_pBox->getTransform()->position = glm::vec2(Config::START_X + cos(angle) * size_x + sin(angle) * size_y,
		Config::START_Y - m_rise - (cos(angle) * size_y - sin(angle) * size_x));
	m_pBox->getTransform()->rotation = glm::vec2(glm::degrees(angle),0.0f);
}

void SimulationManager::launchSimulation()
{
	if (!m_simulation)
	{
		m_simulation = true;

		m_time = calculateTime();
		m_curtime = 0.0f;

	}
}

void SimulationManager::update()
{
	m_timeVar = calculateTime();
	
	if (!m_simulation)
	{
		
	}
	else
	{
		if (m_curtime < m_time)
		{
			m_curtime += 1.0f / Config::FPS;
			
		}
		else
		{
			
			m_simulation = false;
		}
	}

	drawRamp();
}

float SimulationManager::calculateTime()
{
	return 0.0f;
}

void SimulationManager::reset()
{
	
	m_simulation = false;
}