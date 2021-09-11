#include "Core/RaycastPCH.h"
#include "Event.h"

class KeyDownEvent : public Event
{
public:
	KeyDownEvent(int code) : m_KeyCode(code), Event(EventType::KeyDown) {}

	static EventType getStaticType() { return EventType::KeyDown; }
	int getKeyCode() { return m_KeyCode; }

private:
	int m_KeyCode;
};