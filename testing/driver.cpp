#define CATCH_CONFIG_RUNNER// needs to be in the file with main()
#include "catch.hpp" // for unit testing
#include "../source/stateStack.hpp"

void testFunc(void){
	printf("Testing 123\n");
}

int main(int argc, char ** argv){
	
	stateStack mystack;
	mystack.pushState(testFunc);
	
	int result = Catch::Session().run( argc, argv );
	printf("Tests running ...\n");
	
	return result;
	
}

TEST_CASE("Testing struct stuff"){
	REQUIRE(true);
	
}
