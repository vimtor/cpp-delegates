# CppDelegates
Approximation of [C# Delegates](https://docs.microsoft.com/en-us/dotnet/csharp/programming-guide/delegates/), Funcs and Actions on C++

## How to use it
Even though the three different classes (Delegate, Func and Action) store functions to use them in the future, they serve different purposes. Let's explain them one by one.

### Action
His purpose is to store functions whose return type is always void with 0 parameters.
``` C++
void foo() { std::cout << "Something funny"; }

Action action;
action += foo;
```
The operator `+=` adds the functions to later be called using the Invoke method.
``` C++
action.Invoke();
// Prints: Something funny
```

All of the three classes support function removal by using '-='
``` C++
action -= foo;
action.Invoke();

// Prints: Nothing.
```

### Func
His purpose is to store functions whose return type is always void with 0 or more parameters.
``` C++
void print(int x, char a) { std::cout << x << a; }

Func<int, char> func;
func += print;
func += print;

func.Invoke(5, 'A');
// Prints: 5A5A
```

### Delegate
His purpose is to store functions whose return type could be whatever, with 0 or more parameters.

``` C++
Delegate<int()> delegate;

delegate += []() { return 1; };
delegate += []() { return 2; };
delegate += []() { return 3; };
```

A nice feature of the _Delegate_ is that the Invoke method returns a std::vector storing the return values of the functions.
``` C++
for (const auto &item : delegate.Invoke()) std::cout << item;
// Prints: 123
```

As with _Funcs_, you can also pass parameters to the Invoke method.
``` C++
int square(int x) { return x * x; }

Delegate<int(int)> delegate;
delegate += square;

std::cout << delegate.Invoke(2)[0];
// Prints: 4
```

## Frequent questions
### Can I add member functions?
Yes! Perhaps is not in the most beautiful way, but still does the trick. You just need to use lambdas like this.
``` C++
Object obj;
action += [&]() { obj.something(); } // You can even instantiate the object inside the lambda.
```

### How do I pass parameters to the functions?
Again lambdas. Don't ask me, they do anything. You could use `std::bind` but [clang-tidy advices against it](https://clang.llvm.org/extra/clang-tidy/checks/modernize-avoid-bind.html).
``` C++
action += []() { print(5, 'A'); };
action += []() { print(6, 'B'); };

action.Invoke();
// Prints: 5A6B
```

### Something else you didn't mention?
Thanks for asking. The operator `+=` is overloaded to accept a vector.
``` C++
delegate += { foo, bar };
```
You can also reset or clear the delegate with `delegate.Clear()`

