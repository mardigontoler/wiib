
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

#include "misc.hpp"
#include <tuple>
#include <cstdlib>
#include <functional>
#include <ctime>

using std::tuple;
f32 calcDistance(f32 x1, f32 y1, f32 x2, f32 y2){
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}


// a unit vector in the direction of the line
// between (x1, y1) and (x2, y2)
// This is a gemoetric vector, not a container
tuple<f32, f32> calcUnitVector(f32 x1, f32 y1, f32 x2, f32 y2){
    f32 magnitude = calcDistance(x1, y1, x2, y2);
    f32 xcom = x2 - x1;
    f32 ycom = y2 - y1;

    // divide the x-component and y-component by magnitude
    xcom /= magnitude;
    ycom /= magnitude;

    return std::make_tuple(xcom, ycom);

}

// A function which generates a 2D vector (as a tuple) 
// of random amounts of noise between min and max and 
// then can randomly invert the components
tuple<f32, f32> noise(int max){
    f32 xcom, ycom;
    //srand(time(NULL));
    xcom = (rand() % max) * (rand() % 2 == 0 ? 1 : -1);
    ycom = (rand() % max) * (rand() % 2 == 0 ? 1 : -1);
    return std::make_tuple(xcom, ycom);
}

