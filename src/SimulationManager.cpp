#include "SimulationManager.h"

#include <iostream>
#include <glm/detail/func_trigonometric.inl>

#include "Config.h"
#include "EventManager.h"
#include "WayPoint.h"

float SIMA::m_time = 0.0f;
float SIMA::m_curtime = 0.0f;

float SIMA::m_angle = Config::START_ANGLE;
float SIMA::m_timeVar = 0.0f;
bool SIMA::m_simulation = false;

SimulationManager::SimulationManager() {}

SimulationManager::~SimulationManager() = default;

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
}

float SimulationManager::calculateTime()
{
	return 0.0f;
}

void SimulationManager::reset()
{
	
	m_simulation = false;
}

void SimulationManager::changeAngle(float num)
{
	m_angle = num;
	if (m_angle < Config::MIN_ANGLE)
	{
		m_angle = Config::MIN_ANGLE;
	}
	else if (m_angle > Config::MAX_ANGLE)
	{
		m_angle = Config::MAX_ANGLE;
	}
}