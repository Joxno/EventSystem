#pragma once
#include <wink/signal.hpp>
#include <wink/slot.hpp>
#include "Event.h"
#include <functional>
using namespace std;
using namespace wink;

namespace EventSystem
{
	class EventHandler;
	class EventSlot
	{
	private:
		slot<void(Event*)> m_Slot;
		EventHandler *m_EventHandler = nullptr;
		string m_EventName = "";
		bool m_DisabledDisconnect = false;
	public:
		~EventSlot();
		EventSlot() {}
		EventSlot(string EventName, slot<void(Event*)> Slot, EventHandler *EventSystem);
		EventSlot(string EventName, slot<void(Event*)> Slot);
		void Disconnect();
		void Disconnect(signal<slot<void(Event*)>> Signal) { Signal.disconnect(m_Slot); }
		void SetDisableDisconnect(bool Disconnect) { m_DisabledDisconnect = Disconnect; }
		string GetEventName() const { return m_EventName; }

	};
}