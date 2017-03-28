
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


#include "grrlib.h"
#include "ecs.h"
#include "GameObject.hpp"


GRRLIB_texImg* findTex(ecs::EntityManager& entities, std::string name){

    for(auto texPtrComp : entities.with<TexPointer>()){
        TexPointer& texPtr = texPtrComp.get<TexPointer>();
        if(texPtr.name.compare(name) == 0){
            return texPtr.ptexture;
        }
    }
    return NULL;
}
