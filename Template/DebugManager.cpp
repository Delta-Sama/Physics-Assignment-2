#include "DebugManager.h"
#include "../src/Renderer.h"

void DebugManager::DrawLine(const SDL_Point start, const SDL_Point end, const SDL_Color col)
{
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), col.r, col.g, col.b, col.a);
	SDL_RenderDrawLine(Renderer::Instance()->getRenderer(), start.x, start.y, end.x, end.y);
}

void DebugManager::DrawWideLine(const int wide, const SDL_Point start, const SDL_Point end, const SDL_Color col)
{
	float angle = atan2(end.y - start.y, end.x - start.x);
	float cosx = cos(angle);
	float sinx = sin(angle);
	for (int i = 0; i < wide; i++)
	{
		SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), col.r, col.g, col.b, col.a);
		SDL_RenderDrawLine(Renderer::Instance()->getRenderer(), start.x - i * sinx, start.y + i * cosx, 
			end.x - i * sinx, end.y + i * cosx);
	}
}

void DebugManager::QueueLine(const SDL_Point start, const SDL_Point end, const SDL_Color col)
{
	s_points.push_back(start);
	s_points.push_back(end);
	s_colors.push_back(col);
}

void DebugManager::FlushLines()
{
	for (unsigned i = 0, j = 0; i < s_points.size(); i += 2, j++)
		DrawLine(s_points[i], s_points[i + 1], s_colors[j]);
	Quit(); // Clears out vectors.
}

void DebugManager::Quit()
{
	s_points.clear();
	s_colors.clear();
	s_points.shrink_to_fit();
	s_colors.shrink_to_fit();
}

int DebugManager::s_debugMode = 0;
std::vector<SDL_Point> DebugManager::s_points;
std::vector<SDL_Color> DebugManager::s_colors;