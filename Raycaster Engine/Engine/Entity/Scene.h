#pragma once

#include <memory>

#include "Entity.h"
#include "System/Application.h"
#include "Utils/Map.h"
#include "Renderer/Camera.h"

struct Light
{
	vec2 light_source;
	vec3 light_color;
	float light_radius;
	float light_intensity;

	Light(const vec2& l, const vec3& c, float r, float i) : light_source(l), light_color(c), light_radius(r), light_intensity(i) {}
};

class Scene
{
	friend class Renderer;
	friend class WorldRenderer;

public:
	Scene() : m_Map(std::make_shared<Map>()), m_Camera(std::make_shared<Camera>()) {}
	virtual ~Scene();

	void addEntity(const std::shared_ptr<Entity>& ent);
	void addLight(Light* light) {
		m_Lights.push_back(light);
	}
	void loadScene(const std::string filepath);
	Light* getLastLight() { return m_Lights[m_Lights.size() - 1]; }

	bool Update(float dt);

	std::shared_ptr<Entity>& createEntity(const std::string& filepath);
	std::shared_ptr<Entity>& createEntity(const std::shared_ptr<Sprite>& spr);
	std::shared_ptr<Entity>& createEntity(float x, float y, float width, float height, const std::string& spr);

	void deleteEntity(const std::shared_ptr<Entity>& ent);

	const std::vector<std::shared_ptr<Entity>>& getEntities() const { return m_Entities; }

	void updateEntites(float dt);
	const std::shared_ptr<Map>& getMap() const { return m_Map; }

	void setCameraProps(float fov, float speed) 
	{
		m_Camera->m_FOV = fov;
		m_Camera->m_Speed = speed;
		m_Camera->m_Sprint = speed + 3.0f;
	}

	const std::shared_ptr<Camera>& getCamera() const { return m_Camera; }
	const std::vector<Light*>& getLights() const { return m_Lights; }

private:
	std::vector<std::shared_ptr<Entity>> m_Entities;
	std::vector<Light*> m_Lights;
	std::shared_ptr<Map> m_Map;
	std::shared_ptr<Camera> m_Camera;
};
