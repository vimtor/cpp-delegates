#include <iostream>
#include "Delegate.h"
#include "Action.h"
#include "Func.h"


void foo() { std::cout << "I am foo!" << std::endl; }

void bar() { std::cout << "I am bar!" << std::endl; }

struct Object
{
	void something()
	{
		std::cout << "I am an object!" << std::endl;
	}
};

void foobar(int x, char y) { std::cout << x << y << std::endl; }

int main()
{
	// Delegate Example
	Delegate<int()> delegate;
	delegate += []() { return 1; };
	delegate += []() { return 2; };
	delegate += []() { return 3; };

	for (const auto &item : delegate.Invoke()) std::cout << item;


	// Func Example
	Func<int, char> func;
	func += foobar;

	func.Invoke(5, 'A');


	// Action Example
	Action action;
	action += foo;

	action.Invoke();


	return 0;
}