//
// Created by Víctor Navarro on 2/26/2019.
//

#ifndef DELEGATE_H
#define DELEGATE_H

#include <functional>
#include <vector>
#include <algorithm>
#include <type_traits>

template<class T>
class Delegate
{
private:
	using Function = std::function<T>;
	std::vector<Function> functions;

	using ResultType = typename Function::result_type;
	std::vector<ResultType> results;

	// Helper to get the address of a std::function.
	template<typename T, typename... U>
	static size_t getAddress(std::function<T(U...)> f)
	{
		typedef T(fnType)(U...);
		auto fnPointer = f.template target<fnType *>();
		return (size_t) *fnPointer;
	}

public:
	Delegate() = default;

	~Delegate() = default;

	auto Invoke()
	{
		results.clear();

		for (const auto &function : functions)
		{
			results.push_back(function());
		}

		return results;
	}

	template<class ... Args>
	auto Invoke(Args ... args)
	{
		results.clear();

		for (const auto &function : functions)
		{
			results.push_back(function(args...));
		}

		return results;
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

#endif
