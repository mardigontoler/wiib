#pragma once

class Status{
    private:
        int hp;
        bool grabbed;

    public:
        Status(int _hp = 100):
            hp(_hp),
            grabbed(false){
            }
        
        bool alive(void);
        bool grab(void);
        void drop(void);

};