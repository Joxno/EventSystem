#include "EventHandler.h"
#include "EventSlot.h"

namespace EventSystem
{

	EventSlot::~EventSlot()
	{
		if (m_EventHandler != nullptr && !m_DisabledDisconnect)
			m_EventHandler->UnRegisterCallback(m_EventName, m_Slot);
	}

	void EventSlot::Disconnect()
	{
		if (m_EventHandler != nullptr)
			m_EventHandler->UnRegisterCallback(m_EventName, m_Slot);
	}

	EventSlot::EventSlot(string EventName, slot<void(Event*)> Slot, EventHandler *EventSystem)
	{
		m_Slot = Slot;
		m_EventHandler = EventSystem;
		m_EventName = EventName;
	}

	EventSlot::EventSlot(string EventName, slot<void(Event*)> Slot)
	{
		m_Slot = Slot;
		m_EventName = EventName;
	}
}