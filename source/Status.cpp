#include "Status.hpp"

bool Status::alive(void){
    return hp >= 0;
}

// things that are grabbed cannot be grabbed by something else until they are dropped
// the grab will return its success
bool Status::grab(void){
    if(!grabbed){
        grabbed = true;
        return true;
    }
    return false;
}

// allow a thing to be grabbed again
void Status::drop(void){
    grabbed = false;
}