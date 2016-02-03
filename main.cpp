#include <iostream>
// System
#include "EventHandler.h"
#include "EventSlotHandler.h"
#include <memory>
// Tests
#include "TestEvents.h"

using namespace std;
using namespace EventSystem;

int main()
{
	EventHandler t_EventHandler{};
	
	{
		EventSlotHandler t_SlotHandler{};

		// Global Functions
			t_SlotHandler += t_EventHandler.RegisterCallback("OnMouseMove", CreateSlot(OnMouseMove));
			t_SlotHandler += t_EventHandler.RegisterCallback("OnMouseDown", CreateSlot(OnMouseDown));

		// Member Functions
			Foobar t_Instance{};
			t_SlotHandler += t_EventHandler.RegisterCallback("KeyDown", CreateSlot(&t_Instance, &Foobar::KeyDown));
			t_SlotHandler += t_EventHandler.RegisterCallback("KeyUp", CreateSlot(&t_Instance, &Foobar::KeyUp));
			t_SlotHandler += t_EventHandler.RegisterCallback("Initialize", CreateSlot(&t_Instance, &Foobar::Initialize));

		// Manual Slot Management
			{
				auto t_EventSlot = t_EventHandler.RegisterCallback("OnMouseMove", CreateSlot(OnMouseMove));
			}

		// Fire Events
			t_EventHandler.FireEvent("OnMouseMove", &MouseMove{ 5,5 });
			t_EventHandler.FireEvent("OnMouseDown", &MouseDown{ 5,5, 0 });

			t_EventHandler.FireEvent("KeyDown", &KeyDown{ 65 });
			t_EventHandler.FireEvent("KeyUp", &KeyUp{ 65 });

			t_EventHandler.FireEvent("Initialize");

		// Fire Incorrect Event
			try
			{
				t_EventHandler.FireEvent("OnMouseMove", &MouseDown{ 25,25, 3 });
			}
			catch (exception e)
			{
				cout << e.what() << endl;
			}
	} // Disconnects all Events

	// Fire Event after Disconnect
		t_EventHandler.FireEvent("OnMouseMove", &MouseMove{ 67,55 });

	return 0;
}