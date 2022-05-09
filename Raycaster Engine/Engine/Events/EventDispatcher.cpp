#include "Core/RaycastPCH.h"
#include "EventDispatcher.h"

#include "EventListener.h"
#include "System/Layer.h"

std::vector<EventListener*> EventDispatcher::m_Listeners;

void EventDispatcher::addListener(EventListener* l)
{
	m_Listeners.push_back(l);
}

void EventDispatcher::removeListener(EventListener* l)
{
	auto it = std::find(m_Listeners.begin(), m_Listeners.end(), l);

	if (it != m_Listeners.end())
		m_Listeners.erase(it);
}

void EventDispatcher::Dispatch(Event& event)
{
	for (int i = m_Listeners.size() - 1; i >= 0; i--)
	{
		if (!event.m_Handled)
		{
			if (m_Listeners[i]->m_Following[(int)event.getType()] == 1)
			{
					if (m_Listeners[i]->m_HandlesEvents == true)
						event.m_Handled = m_Listeners[i]->onEvent(event);
			}
		}
		else return;
	}
}

void EventDispatcher::clearListeners()
{
	m_Listeners.clear();
}
