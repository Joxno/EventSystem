#pragma once
#include "EventSlot.h"
#include <vector>
using namespace std;

namespace EventSystem
{
	class EventSlotHandler
	{
	private:
		vector<EventSlot> m_Slots;
	public:

		~EventSlotHandler()
		{
			DisconnectAll();
		}

		void AddSlot(EventSlot &Slot)
		{
			m_Slots.emplace_back(Slot);
		}

		void Disconnect(const string &EventName)
		{
			auto t_Slot = find_if(m_Slots.begin(), m_Slots.end(), [&EventName](auto &s) { return s.GetEventName() == EventName; });
			if (t_Slot != m_Slots.end())
				m_Slots.erase(t_Slot);
		}

		void DisconnectAll()
		{
			for (auto &s : m_Slots)
				s.Disconnect();
			m_Slots.clear();
		}

		void operator+=(EventSlot &e)
		{
			e.SetDisableDisconnect(true);
			AddSlot(e);
		}
	};
}