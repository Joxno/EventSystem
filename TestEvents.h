#pragma once
#include <iostream>
#include "Event.h"
using namespace EventSystem;
using namespace std;

struct MouseMove : public Event
{
	float X, Y;
	MouseMove(float x, float y) : X(x), Y(y) {};
};

struct MouseDown : public Event
{
	float X, Y;
	int Key;
	MouseDown(float x, float y, int button) : X(x), Y(y), Key(button) {};
};

struct KeyDown : public Event
{
	int Key;
	KeyDown(int keycode) : Key(keycode) {};
};

struct KeyUp : public Event
{
	int Key;
	KeyUp(int keycode) : Key(keycode) {};
};


class Foobar
{
	private:
	public:
		void KeyDown(KeyDown *e)
		{
			e->assertType(e);
			cout << "KeyDown: " << e->Key << endl;
		}

		void KeyUp(KeyUp *e)
		{
			e->assertType(e);
			cout << "KeyUp: " << e->Key << endl;
		}

		void Initialize(Event)
		{
			cout << "Initializing Foobar." << endl;
		}
};

void OnMouseMove(MouseMove *e)
{
	e->assertType(e);
	cout << "MouseMove: " << e->X << "," << e->Y << endl;
}

void OnMouseDown(MouseDown *e)
{
	e->assertType(e);
	cout << "MouseDown: " << e->Key << " - " << e->X << "," << e->Y << endl;
}