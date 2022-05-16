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
	void loadScene(const std::string filepath);

	std::shared_ptr<Entity>& createEntity(const std::string& filepath);
	std::shared_ptr<Entity>& createEntity(const std::shared_ptr<Sprite>& spr);
	std::shared_ptr<Entity>& createEntity(float x, float y, float width, float height, const std::string& spr);

	void deleteEntity(const std::shared_ptr<Entity>& ent);

	const std::vector<std::shared_ptr<Entity>>& getEntities() const { return m_Entities; }

	void updateEntites(float dt);

protected:
	std::vector<std::shared_ptr<Entity>> m_Entities;
};
