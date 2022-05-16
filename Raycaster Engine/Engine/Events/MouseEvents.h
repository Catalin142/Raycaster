#include "Event.h"
#include "Utils/Input.h"

class MousePressedEvent : public Event
{
public:
	MousePressedEvent(int code, int x, int y) : m_MouseCode(code), m_MouseX(x), m_MouseY(y), Event(EventType::MousePressed) {}

	static EventType getStaticType() { return EventType::MousePressed; }

	int getX() { return m_MouseX; }
	int getY() { return m_MouseY; }

	int getMouseCode() { return m_MouseCode; }

private:
	int m_MouseX;
	int m_MouseY;

	int m_MouseCode;
};

class MouseReleasedEvent : public Event
{
public:
	MouseReleasedEvent(int code, int x, int y) : m_MouseCode(code), m_MouseX(x), m_MouseY(y), Event(EventType::MouseReleased) {}

	static EventType getStaticType() { return EventType::MouseReleased; }

	int getX() { return m_MouseX; }
	int getY() { return m_MouseY; }

	int getMouseCode() { return m_MouseCode; }

private:
	int m_MouseX;
	int m_MouseY;

	int m_MouseCode;
};

class MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(int x, int y) : m_MouseX(x), m_MouseY(y), Event(EventType::MouseMoved) {}

	static EventType getStaticType() { return EventType::MouseMoved; }

	int getX() { return m_MouseX; }
	int getY() { return m_MouseY; }

private:
	int m_MouseX;
	int m_MouseY;
};