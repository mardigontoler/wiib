#include <stack>
#include "stateStack.hpp"

void stateStack::pushState(void (*f)(void)){
	states.push(f);
	(*f)();
}

