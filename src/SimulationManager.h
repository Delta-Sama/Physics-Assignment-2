#pragma once
#ifndef __PROJECTILE_MANAGER_H__
#define __PROJECTILE_MANAGER_H__

#include <algorithm>
//#include <GLM/detail/func_trigonometric.inl>
#include <GLM/detail/type_vec2.hpp>

#include "Box.h"
#include "Config.h"

#include <iomanip>
#include <sstream>

class SimulationManager
{
public:
	static std::string getAngle();
	static std::string getRise();
	static std::string getRun();
	static std::string getAcceleration();
	static std::string getMass();
	
	static std::string getTime();
	static std::string getStopTime();
	
	static void launchSimulation();

	static bool getSimulation() { return m_simulation; }
	
	static void update();
	static void reset();

	static void changeRise(float num) { m_rise = std::clamp(m_rise + num, Config::MIN_RISE, Config::MAX_RISE); }
	static void changeRun(float num) { m_run = std::clamp(m_run + num, Config::MIN_RUN, Config::MAX_RUN); }
	static void changeMass(float num) { m_mass = std::clamp(m_mass + num, Config::MIN_MASS, Config::MAX_MASS); }
	static float calculateTime();

	static void setBox(Box* box) { m_pBox = box; }
	
private:
	SimulationManager();
	~SimulationManager();

	static void changeAngle(float num) { m_angle = std::clamp(m_angle + num, Config::MIN_RISE, Config::MAX_RISE); }
	static void drawRamp();
	
	static bool m_simulation;

	static float m_mass;
	static float m_angle;
	static int m_rise;
	static int m_run;

	static float m_cur_frame_time;
	static float m_time;
	static float m_curtime;

	static Box* m_pBox;

	// Simulation staff
	static bool m_frictionSurface;
	static float m_acceleration;
	static float m_velocity;
	static glm::vec2 m_direction;
};

typedef SimulationManager SIMA;

#endif