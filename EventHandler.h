#pragma once
#include <iostream>
#include <wink/signal.hpp>
#include <wink/slot.hpp>
#include <vector>
#include <map>
#include <unordered_map>
#include "Event.h"
using namespace std;
using namespace wink;

namespace EventSystem
{
	class EventSlot;
	class EventHandler
	{
	private:
		// All Events
		unordered_map<string, signal<slot<void(Event*)>>> m_Events;
	public:
		
		// Cpp
		EventSlot RegisterCallback(string EventName, slot<void(Event*)> Callback);

		void UnRegisterCallback(string EventName, slot<void(Event*)> Event)
		{
			if (m_Events.find(EventName) == m_Events.end())
				return;

			m_Events[EventName].disconnect(Event);
		}
		void FireEvent(string EventName)
		{
			Event t_Event{};
			// Cpp Callback
			if (m_Events.find(EventName) != m_Events.end())
				m_Events[EventName].emit(&t_Event);
		}
		void FireEvent(const string &EventName, Event *Data)
		{
			// Cpp Callback
			if (m_Events.find(EventName) != m_Events.end())
				m_Events[EventName].emit(Data);
		}

		signal<slot<void(Event*)>> *GetEvent(const string &EventName)
		{
			if (m_Events.find(EventName) != m_Events.end())
				return &m_Events[EventName];
			return nullptr;
		}
	};

	template<typename T>
	slot<void(Event*)> CreateSlot(T Func)
	{
		return slot<void(Event*)>((void(*)(Event*)) Func);
	}
	template<typename T, typename Z>
	slot<void(Event*)> CreateSlot(Z *Obj, T Func)
	{
		return slot<void(Event*)>(Obj, (void(Z::*)(Event*))Func);
	}
}