//
// Created by Víctor Navarro on 2/26/2019.
//

#ifndef DELEGATE_H
#define DELEGATE_H

#include <functional>
#include <vector>
#include <algorithm>
#include <type_traits>

// Helper to get the address of a std::function.
template<typename T, typename... U>
static size_t getAddress(std::function<T(U...)> f)
{
	typedef T(fnType)(U...);
	auto fnPointer = f.template target<fnType *>();
	return (size_t) *fnPointer;
}

template<typename T>
struct function_traits;

template<typename R, typename ...Args>
struct function_traits<std::function<R(Args...)>>
{
	static const size_t nargs = sizeof...(Args);

	typedef R result_type;

	template<size_t i>
	struct arg
	{
		typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
	};
};

template<class T>
class Delegate
{
protected:
	using Function = std::function<T>;
	std::vector<Function> functions;

	using ResultType = typename Function::result_type;
	std::vector<ResultType> results;

public:
	Delegate() = default;

	~Delegate() = default;

	template<typename ... Params>
	auto Invoke(Params ... params)
	{
		results.clear();

		for (const auto &function : functions)
		{
			results.push_back(function(params...));
		}

		return results;
	}

	void operator+=(const Function &rhs)
	{
		functions.push_back(rhs);
	}

	void operator+=(const std::vector<Function> &rhs)
	{
		functions.insert(functions.end(), rhs.begin(), rhs.end());
	}

	void operator-=(const Function &rhs)
	{
		auto found = std::find_if(functions.begin(), functions.end(),
								  [rhs](auto function) { return getAddress(function) == getAddress(rhs); });

		if (found != functions.end()) functions.erase(found);
	}

	void Clear()
	{
		results.clear();
	}
};

template<class ... Args>
class Delegate<void(Args...)>
{
protected:
	using Function = std::function<void(Args...)>;
	std::vector<Function> functions;


public:
	Delegate() = default;

	~Delegate() = default;

	void Invoke(Args ... args)
	{
		for (const auto &function : functions)
		{
			function(args...);
		}
	}

	void operator+=(const Function &rhs)
	{
		functions.push_back(rhs);
	}

	void operator+=(const std::vector<Function> &rhs)
	{
		functions.insert(functions.end(), rhs.begin(), rhs.end());
	}

	void operator-=(const Function &rhs)
	{
		auto found = std::find_if(functions.begin(), functions.end(),
								  [rhs](auto function) { return getAddress(function) == getAddress(rhs); });

		if (found != functions.end()) functions.erase(found);
	}
};

#endif
