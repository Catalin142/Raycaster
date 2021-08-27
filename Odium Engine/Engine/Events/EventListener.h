#pragma once

#include "EventDispatcher.h"
#include "Event.h"

class EventListener // layer
{
	friend class EventDispatcher;

public:
	EventListener() { EventDispatcher::addListener(this); }
	virtual ~EventListener() = default;
	virtual bool onEvent(Event& event) = 0;

	template<typename T>
	void Subscribe()
	{
		static_assert(std::is_base_of<Event, T>::value, "Trebuie sa fie event");
		m_Following[static_cast<int>(T::getStaticType())] = 1;
	}

	template <typename T>
	void Unsubscribe()
	{
		m_Following[T::getStaticType()] = 0;
	}

private:
	std::bitset<12> m_Following;
	bool m_HandlesEvents = true;


};