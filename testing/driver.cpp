

    //Wiib - a Wii Homebrew multiplayer game
    //Copyright (C) 2017 Mardigon Toler

    //This program is free software: you can redistribute it and/or modify
    //it under the terms of the GNU General Public License as published by
    //the Free Software Foundation, either version 3 of the License, or
    //(at your option) any later version.

    //This program is distributed in the hope that it will be useful,
    //but WITHOUT ANY WARRANTY; without even the implied warranty of
    //MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    //GNU General Public License for more details.

    //You should have received a copy of the GNU General Public License
    //along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

TEST_CASE("Testing struct stuff"){	REQUIRE(true);
	
}
