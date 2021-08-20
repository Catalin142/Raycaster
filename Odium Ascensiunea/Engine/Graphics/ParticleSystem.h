#pragma once

#include "Utils/Maths.h"
#include "Utils/Types.h"
#include "Utils/Color.h"

struct ParticleProps
{
	vec2 m_Position = { 0.0f, 0.0f };
	vec2 m_Velocity = { 0.0f, 0.0f }, m_VelocityVariation = { 0.0f, 0.0f };
	vec2 m_Scale = { 1.0f, 1.0f };

	float m_Speed = 1.0f;

	float m_LifeTime = 1.0f;
};

class ParticleEmmiter
{
public:
	ParticleEmmiter(uint32 size);
	~ParticleEmmiter();

	void setEmissionRate(int rate) { m_EmissionRate = rate; }
	void setEmissionTime(float time) { m_EmissionTime = time; }

	void Emit(const ParticleProps& props, float deltaTime);
	void Update(float deltaTime);
	void Render();

	void setColor(vec3 color) { m_Color = createHex(color); }

private:
	struct Particle
	{
		vec2 m_Position;
		vec2 m_Velocity;
		vec2 m_Scale;
		
		float m_LifeTime;
		float m_RemainingTime;

		bool m_Active = false;

		float m_Speed;

		Particle* m_NextParticle;
	};

	Particle* m_FirstAvailable;
	Particle* m_ParticlePool;

	uint32 m_PoolSize;

	unsigned long m_Color = 0x0000000;
	float m_EmissionTime = 0.0f;
	float m_LastEmission = 0.0f;

	int m_EmissionRate = 1;
};

class ParticleManager
{
public:
	static void addParticleType(const std::string& name, const ParticleProps& prop);
	static ParticleProps& getParticle(const std::string& name);

	static void Remove(const std::string& name);
	static void Clear();

private:
	static std::unordered_map<std::string, ParticleProps> m_ParticleProps;

private:
	ParticleManager() = default;
	~ParticleManager() = default;
};