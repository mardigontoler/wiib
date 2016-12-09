
#include <stack>

typedef void (* Funct)(void);

class stateStack{
	public:
		std::stack<void (*)(void)> states; // pointers to functions
		void pushState(void (*f)(void));
		Funct top(void){
			return states.top();
		};
	
	
};
