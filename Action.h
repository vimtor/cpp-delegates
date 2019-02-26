//
// Created by Víctor Navarro on 2/26/2019.
//

#ifndef ACTION_H
#define ACTION_H

#include "Delegate.h"

class Action
{
private:
	using Function = std::function<void()>;
	std::vector<Function> functions;

	// Helper to get the address of a std::function.
	template<typename T, typename... U>
	static size_t getAddress(std::function<T(U...)> f)
	{
		typedef T(fnType)(U...);
		auto fnPointer = f.template target<fnType *>();
		return (size_t) *fnPointer;
	}

public:
	Action() = default;

	~Action() = default;

	void Invoke()
	{
		for (const auto &function : functions) function();
	}

	void operator+=(const Function &rhs)
	{
		functions.push_back(rhs);
	}

	void operator-=(const Function &rhs)
	{
		auto found = std::find_if(functions.begin(), functions.end(),
								  [rhs](auto function) { return getAddress(function) == getAddress(rhs); });

		if (found != functions.end()) functions.erase(found);
	}
};


#endif ACTION_H
