# EventSystem
A C++11/14 lightweight abstraction built upon the https://github.com/miguelmartin75/Wink-Signals library for easier handling of Events.

## Classes
* EventHandler
  * Is the main hub class that stores all of the Events and handles calling of Events.
* EventSlot
  * A sort of ticket that stores a Wink-Signals slot inside of it which it can later use to automatically disconnect on destruction.
* EventSlotHandler
  * A class which simply stores all EventSlots in a vector with a small interface for management of them.

## Definining Events
```c++
// Event Definition
  struct MouseMove : public Event
  {
  };

// Event Function Definition with Parameter
  void FoobarCall(MouseMove *e)
  {
    // Runtime check for correct passed Event
    e->assertType(e);
    // Code...
  }

// Event Function Definition without Parameter
  void FooCall(Event)
  {
    // Code...
  }
```
## Registering Events
```c++
// Initializations
  EventHandler t_EventHandler{};
  EventSlotHandler t_SlotHandler{};
// Global Function
  t_SlotHandler += t_EventHandler.RegisterCallback("FoobarEvent", CreateSlot(FoobarCall));
// Member Function
  t_SlotHandler += t_EventHandler.RegisterCallback("FoobarEvent", CreateSlot(&FoobarInstance, &Foobar::FoobarCall));

// Manual Register
  auto t_EventSlot = t_EventHandler.RegisterCallback("FoobarEvent", CreateSlot(FoobarCall));
```
## Calling Events
```c++
// Fire Event without Parameter
  t_EventHandler.FireEvent("FoobarEvent");
// Fire Event with Parameter
  MouseMove t_MouseMove{}
  t_EventHandler.FireEvent("FoobarEvent", &t_MouseMove);
```
## Unregistering Events
```c++
// Disonnect a particular Event from this EventSlotHandler
  t_SlotHandler.Disconnect("FoobarEvent");
// Disconnects all slots associated with this EventSlotHandler
  t_SlotHandler.DisconnectAll();
// Slots are also disconnected on destruction
  {
    EventSlotHandler t_SlotHandler{};
    t_SlotHandler += ...
  } // Destruction due to ending of scope
```
