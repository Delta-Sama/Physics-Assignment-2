#include "SimulationManager.h"

#include <iostream>
#include <glm/detail/func_trigonometric.inl>

#include "Config.h"
#include "EventManager.h"
#include "WayPoint.h"
#include "../Template/DebugManager.h"

float SIMA::m_cur_frame_time = 0.0f;
float SIMA::m_time = 0.0f;
float SIMA::m_curtime = 0.0f;

float SIMA::m_angle = Config::START_ANGLE;
float SIMA::m_mass = Config::START_MASS;
int SIMA::m_rise = Config::START_RISE;
int SIMA::m_run = Config::START_RUN;

bool SIMA::m_simulation = false;

float SIMA::m_acceleration = 0.0f;
float SIMA::m_velocity = 0.0f;
glm::vec2 SIMA::m_direction = { 0.0f,0.0f };
bool SIMA::m_frictionSurface = false;

Box* SIMA::m_pBox;

SimulationManager::SimulationManager() {}

SimulationManager::~SimulationManager() = default;

void SimulationManager::drawRamp()
{
	DebugManager::DrawWideLine(4, { Config::START_X,Config::START_Y }, { Config::START_X + m_run,Config::START_Y }, { 0,0,0,255 });
	DebugManager::DrawWideLine(4, { Config::START_X,Config::START_Y }, { Config::START_X,Config::START_Y - m_rise }, { 0,0,0,255 });
	DebugManager::DrawWideLine(4, { Config::START_X + m_run,Config::START_Y }, { Config::START_X,Config::START_Y - m_rise }, { 0,0,0,255 });
}

void SimulationManager::launchSimulation()
{
	if (!m_simulation)
	{
		m_simulation = true;

		m_time = m_cur_frame_time;
		
		m_curtime = 0.0f;
		//setup
		m_direction = { cos(m_angle), sin(m_angle) };
		m_velocity = 0.0f;
		m_frictionSurface = false;
	}
}

void SimulationManager::update()
{	
	if (!m_simulation)
	{
		m_cur_frame_time = calculateTime();
		
		float angle = atan2(m_rise, m_run);

		float size_x = m_pBox->getWidth() / 2;
		float size_y = m_pBox->getHeight() / 2;
		m_pBox->getTransform()->position = glm::vec2(Config::START_X + cos(angle) * size_x + sin(angle) * size_y,
			Config::START_Y - m_rise - (cos(angle) * size_y - sin(angle) * size_x));
		m_pBox->getTransform()->rotation = glm::vec2(glm::degrees(angle), 0.0f);

		m_angle = angle;

		m_acceleration = -Config::g * sin(m_angle);
	}
	else
	{
		if (m_curtime < m_time)
		{
			m_curtime += 1.0f / Config::FPS;

			m_velocity += m_acceleration / Config::FPS;
			
			m_pBox->getTransform()->position.x += m_velocity * m_direction.x * Config::MET_TO_PIX / Config::FPS;
			m_pBox->getTransform()->position.y += m_velocity * m_direction.y * Config::MET_TO_PIX / Config::FPS;
			
			if (m_curtime >= m_time && !m_frictionSurface)
			{
				m_frictionSurface = true;

				m_pBox->getTransform()->position.x = Config::START_X + m_run + m_pBox->getWidth() / 2;
				m_pBox->getTransform()->position.y = Config::START_Y - m_pBox->getHeight()/2;
				if (glm::degrees(m_angle) > 60.0f)
					m_pBox->getTransform()->rotation.x = 90.0f;
				else
					m_pBox->getTransform()->rotation.x = 0.0f;

				std::cout << glm::degrees(m_angle) << "\n";
				
				m_velocity = m_velocity * cos(m_angle);
				m_acceleration = Config::g * Config::FRICTION_COF;
				
				m_time = m_velocity / -m_acceleration;
				m_curtime = 0.0f;
				
				m_direction = { 1, 0 };
			}
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
	float S = sqrt(pow(m_run * Config::PIX_TO_MET, 2) + pow(m_rise * Config::PIX_TO_MET, 2));
	float t = sqrt(S * 2 / m_acceleration);
	return t;
}

void SimulationManager::reset()
{
	m_angle = Config::START_ANGLE;
	m_mass = Config::START_MASS;
	m_rise = Config::START_RISE;
	m_run = Config::START_RUN;
	
	m_simulation = false;
}

// GETTERS:

std::string SimulationManager::getAngle()
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(4) << glm::degrees(m_angle);
	std::string s = stream.str();
	return s;
}

std::string SimulationManager::getRise()
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << m_rise * Config::PIX_TO_MET;
	std::string s = stream.str();
	return s;
}

std::string SimulationManager::getRun()
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << m_run * Config::PIX_TO_MET;
	std::string s = stream.str();
	return s;
}

std::string SimulationManager::getAcceleration()
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(3) << m_acceleration;
	std::string s = stream.str();
	return s;
}

std::string SimulationManager::getMass()
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << m_mass;
	std::string s = stream.str();
	return s;
}

std::string SimulationManager::getTime()
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(4) << m_cur_frame_time;
	std::string s = stream.str();
	return s;
}

std::string SimulationManager::getStopTime()
{
	const float max_x_velocity = -Config::g * sin(m_angle) * m_cur_frame_time * cos(m_angle);

	std::stringstream stream;
	stream << std::fixed << std::setprecision(4) << max_x_velocity / (-Config::g * Config::FRICTION_COF);
	std::string s = stream.str();
	return s;
}