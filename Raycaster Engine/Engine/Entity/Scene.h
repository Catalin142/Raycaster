#pragma once

#include "Entity.h"
#include "System/Application.h"

class Scene
{
	friend class Renderer;

public:
	Scene() = default;
	virtual ~Scene() = default;

	void addEntity(const std::shared_ptr<Entity>& ent);

	std::shared_ptr<Entity>& createEntity(const std::string& filepath);
	std::shared_ptr<Entity>& createEntity(const std::shared_ptr<Sprite>& spr);

	void deleteEntity(const std::shared_ptr<Entity>& ent);

	const std::vector<std::shared_ptr<Entity>>& getEntities() const { return m_Entities; }

	void updateEntites(float dt);

protected:
	std::string m_MapPath;
	std::vector<std::shared_ptr<Entity>> m_Entities;
};
