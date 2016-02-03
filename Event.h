#pragma once
#include <string>
#include <assert.h>
#include <wink/signal.hpp>
#include <wink/slot.hpp>
using namespace wink;

namespace EventSystem
{
	class Event
	{
	public:
		virtual ~Event() {};

		template<typename T>
		bool assertType(T *e)
		{
			if (typeid(T) != typeid(*e))
				throw exception(("Type missmatch: "s + typeid(T).name() + " != "s + typeid(*e).name()).c_str());
			return true;
		}
	};
}