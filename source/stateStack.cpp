#include <stack>
#include "stateStack.hpp"
#include <functional>

using namespace std;

void stateStack::pushState(function<void()> f){
	states.push(f);
}

void stateStack::popState(void){
	states.pop();
}

// maybe have the stack collapse down to the bottom-most
// identical state that's being pushed