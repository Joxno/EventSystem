#include "EventSlot.h"
#include "EventHandler.h"

namespace EventSystem
{
	EventSlot EventHandler::RegisterCallback(string EventName, slot<void(Event*)> Callback)
	{
		// Check if Event exists
		if (m_Events.find(EventName) == m_Events.end())
			m_Events[EventName] = signal<slot<void(Event*)>>();

		// Connect slot to event
		m_Events[EventName].connect(Callback);

		return EventSlot(EventName, Callback, this);
	}

}