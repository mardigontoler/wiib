

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

#include "Status.hpp"

bool Status::alive(void)
{
    return hp >= 0;
}

// things that are grabbed cannot be grabbed by something else until they are dropped
// the grab will return its success
bool Status::grab(void)
{
    if (!grabbed)
    {
        grabbed = true;
        return true;
    }
    return false;
}

// allow a thing to be grabbed again
void Status::drop(void)
{
    grabbed = false;
}