#include "Core/RaycastPCH.h"
#include "System/Application.h"
#include "Scene.h"
#include "Renderer/WorldRenderer.h"
#include "Utils/Map.h"

void Scene::addEntity(const std::shared_ptr<Entity>& ent)
{
	auto it = std::find(m_Entities.begin(), m_Entities.end(), ent);

	if (it == m_Entities.end())
		m_Entities.push_back(ent);
}

void Scene::loadScene(const std::string filepath)
{
	m_Entities.clear();

	std::ifstream stream(filepath);

	std::string line;
	while (std::getline(stream, line))
	{
		std::stringstream streamLine(line);
		char symbol;
		streamLine >> symbol;
		std::string filepath;
		float x, y, width, height;

		switch (symbol)
		{
		case 'm':
			streamLine >> filepath;
			Map::Get()->loadMap(filepath);
			break;

		case 'p':
			float x, y;
			streamLine >> x >> y;
			Map::Get()->updatePlayerPosition({ x, y });
			break;

		case 'e':
			streamLine >> x >> y >> width >> height >> filepath;
			createEntity(x, y, width, height, filepath);
			break;

		case 'c':
			char mode;
			streamLine >> mode;

			switch (mode) {
			case 't':
				streamLine >> filepath;
				WorldRenderer::setCeilTexture(std::make_shared<Sprite>(filepath));
				break;

			case 'c':
				vec3 color;
				streamLine >> color.r >> color.g >> color.b;
				WorldRenderer::setCeilColor(color);
				break;

			case'g':
				vec3 color1, color2;
				float intens;
				streamLine >> color1.r >> color1.g >> color1.b;
				streamLine >> color2.r >> color2.g >> color2.b;
				streamLine >> intens;
				WorldRenderer::setCeilGradient(color1, color2, intens);
			}

			break;
		default:
			break;
		}
	}
	stream.close();
}

std::shared_ptr<Entity>& Scene::createEntity(const std::string& filepath)
{
	std::shared_ptr<Entity> newEnt = std::make_shared<Entity>(filepath);
	m_Entities.push_back(newEnt);
	return *(std::find(m_Entities.begin(), m_Entities.end(), newEnt));
}

std::shared_ptr<Entity>& Scene::createEntity(const std::shared_ptr<Sprite>& spr)
{
	std::shared_ptr<Entity> newEnt = std::make_shared<Entity>(spr);
	m_Entities.push_back(newEnt);
	return *(std::find(m_Entities.begin(), m_Entities.end(), newEnt));
}

std::shared_ptr<Entity>& Scene::createEntity(float x, float y, float width, float height, const std::string& spr)
{
	std::shared_ptr<Entity> newEnt = std::make_shared<Entity>(spr);
	newEnt->setPosition(x, y);
	newEnt->setWidth(width);
	newEnt->setHeight(height);
	m_Entities.push_back(newEnt);

	return *(std::find(m_Entities.begin(), m_Entities.end(), newEnt));
}

void Scene::deleteEntity(const std::shared_ptr<Entity>& ent)
{
	auto it = std::find(m_Entities.begin(), m_Entities.end(), ent);
	if (it != m_Entities.end())
		m_Entities.erase(it);
}

void Scene::updateEntites(float dt)
{
	if (!m_Entities.empty())
	{
		for (auto& ent : m_Entities)
		{
			if (ent->m_Initialized == false)
			{
				ent->onCreate();
				ent->m_Initialized = true;
			}

			ent->onUpdate(dt);
		}
	}
}
