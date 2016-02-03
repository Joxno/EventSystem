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

		// Event Data
			MouseMove t_MouseMove{ 5,5 };
			MouseDown t_MouseDown{ 5,5, 0 };
			KeyDown t_KeyDown { 65 };
			KeyUp t_KeyUp { 65 };
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
			t_EventHandler.FireEvent("OnMouseMove", &t_MouseMove);
			t_EventHandler.FireEvent("OnMouseDown", &t_MouseDown);

			t_EventHandler.FireEvent("KeyDown", &t_KeyDown);
			t_EventHandler.FireEvent("KeyUp", &t_KeyUp);

			t_EventHandler.FireEvent("Initialize");

		// Fire Incorrect Event
			try
			{
				t_EventHandler.FireEvent("OnMouseMove", &t_MouseDown);
			}
			catch (exception e)
			{
				cout << e.what() << endl;
			}
	} // Disconnects all Events

	// Fire Event after Disconnect
		MouseMove t_MouseMove{ 65, 65 };
		t_EventHandler.FireEvent("OnMouseMove", &t_MouseMove);

	return 0;
}