#include "Core/RaycastPCH.h"

#include "Utils/Random.h"
#include "Renderer/Renderer.h"

#include "ParticleSystem.h"
#include "Tools/Benchmark.h"

std::unordered_map<std::string, ParticleProps> ParticleManager::m_ParticleProps;

ParticleEmmiter::ParticleEmmiter(uint32 size)
{
	m_PoolSize = size;

	m_ParticlePool = new Particle[m_PoolSize];
	m_FirstAvailable = &m_ParticlePool[0];

	for (int i = 0; i != m_PoolSize - 1; i++)
		m_ParticlePool[i].m_NextParticle = &m_ParticlePool[i + 1];

	m_ParticlePool[m_PoolSize - 1].m_NextParticle = nullptr;
}

ParticleEmmiter::~ParticleEmmiter()
{
	delete[] m_ParticlePool;
}

void ParticleEmmiter::Emit(const ParticleProps& props, float deltaTime)
{
	if (m_LastEmission > m_EmissionTime)
	{
		for (int i = 0; i < m_EmissionRate; i++)
		{
			Particle* newParticle = m_FirstAvailable;
			m_FirstAvailable = newParticle->m_NextParticle;

			newParticle->m_Active = true;

			newParticle->m_Scale = props.m_Scale;
			newParticle->m_Radius = props.m_Radius;

			newParticle->m_LifeTime = props.m_LifeTime;
			newParticle->m_RemainingTime = newParticle->m_LifeTime;

			newParticle->m_BegColor = props.m_BegColor;
			newParticle->m_EndColor = props.m_EndColor;

			newParticle->m_Position = props.m_Position;

			newParticle->m_Velocity = props.m_Velocity;
			newParticle->m_Velocity.x += props.m_VelocityVariation.x * (Random::Float() - 0.5f);
			newParticle->m_Velocity.y += props.m_VelocityVariation.y * (Random::Float() - 0.5f);

			newParticle->m_Speed = props.m_Speed;
		}
		m_LastEmission = 0.0f;
	}

	m_LastEmission += deltaTime;
}

void ParticleEmmiter::Update(float deltaTime)
{
	for (unsigned int i = 0; i < m_PoolSize; i++)
	{
		if (m_ParticlePool[i].m_RemainingTime <= 0.0f)
			m_ParticlePool[i].m_Active = false;

		if (m_ParticlePool[i].m_Active == false)
		{
			m_ParticlePool[i].m_NextParticle = m_FirstAvailable;
			m_FirstAvailable = &m_ParticlePool[i];
			continue;
		}

		m_ParticlePool[i].m_Position = m_ParticlePool[i].m_Position + m_ParticlePool[i].m_Velocity * deltaTime * m_ParticlePool[i].m_Speed;
		m_ParticlePool[i].m_RemainingTime -= deltaTime;
	}
}

void ParticleEmmiter::Render()
{
	START_SCOPE_PROFILE("Particle Render");
	for (unsigned int i = 0; i < m_PoolSize; i++)
	{
		if (m_ParticlePool[i].m_Active == false)
			continue;

		float time = m_ParticlePool[i].m_RemainingTime / m_ParticlePool[i].m_LifeTime;
		if (time < 0.0f)
			time = -time;

		vec3 color = lerp(m_ParticlePool[i].m_EndColor, m_ParticlePool[i].m_BegColor, time);
		
		drawType(&m_ParticlePool[i], color);

	}
}

void ParticleEmmiter::drawType(const Particle* part, const vec3& color)
{
	switch (m_Type)
	{
	case ParticleType::QUAD:
		Renderer::drawQuad(part->m_Position, part->m_Scale, color);
		break;

	case ParticleType::CIRCLE:
		Renderer::drawCircle(part->m_Position, part->m_Radius, color);
		break;

	default:
		break;
	}
}

void ParticleManager::addParticleType(const std::string& name, const ParticleProps& prop)
{
	if (m_ParticleProps.find(name) == m_ParticleProps.end())
		m_ParticleProps[name] = prop;
}

ParticleProps& ParticleManager::getParticle(const std::string& name)
{
	return m_ParticleProps[name];
}

void ParticleManager::Remove(const std::string& name)
{
	m_ParticleProps.erase(name);
}

void ParticleManager::Clear()
{
	m_ParticleProps.clear();
}
