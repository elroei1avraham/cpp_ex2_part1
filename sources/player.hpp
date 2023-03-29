#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>

using namespace std;

class Player{
        private:
        string name;
        public:
        Player(string name);
        Player();
        int stacksize();
        int cardesTaken();
};

#endif