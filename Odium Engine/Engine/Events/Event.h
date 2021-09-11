#pragma once

enum class EventType : int
{
	MousePressed,
	MouseReleased,
	MouseMoved,

	KeyDown,
	KeyUp,
};

class Event
{
	friend class EventDispatcher;

public:
	Event(EventType type) : m_Type(type) {}
	virtual ~Event() = default;

	EventType getType() { return m_Type; }

private:
	EventType m_Type;
	bool m_Handled = false;

};