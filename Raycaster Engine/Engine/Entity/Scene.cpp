#include "Core/RaycastPCH.h"
#include "System/Application.h"
#include "Scene.h"

void Scene::addEntity(const std::shared_ptr<Entity>& ent)
{
	auto it = std::find(m_Entities.begin(), m_Entities.end(), ent);

	if (it == m_Entities.end())
		m_Entities.push_back(ent);
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
