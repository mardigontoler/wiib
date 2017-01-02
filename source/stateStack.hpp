
#pragma once
#include <stack>
#include <functional>
using namespace std;
class stateStack{
	public:
		stack<function<void()>> states; // pointers to functions
		void pushState(function<void()> f);
		function<void()> top(void){
			return states.top();
		};

		function<void()> popState(void);
	
	
};
