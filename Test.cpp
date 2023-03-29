#include "doctest.h"
#include <stdexcept>
#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"

using namespace ariel;

TEST_CASE("start game turn after turn and finally check throw if go playall()") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1,p2);
    
    while (p1.stacksize()!=0 && p2.stacksize()!=0)
    {
        CHECK_NOTHROW(game.playTurn());
    }

    CHECK_THROWS(game.playAll());
    if(p1.stacksize()==0){
        CHECK_NOTHROW(game.printWiner());
    }
    else if(p2.stacksize()==0){
        CHECK_NOTHROW(game.printWiner());
    }
}

TEST_CASE("start game playall() twice and want that the second throw") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1,p2);
    
    CHECK_NOTHROW(game.playAll());
    CHECK_THROWS(game.playAll());
    if(p1.stacksize()==0){
        CHECK_NOTHROW(game.printWiner());
    }
    else if(p2.stacksize()==0){
        CHECK_NOTHROW(game.printWiner());
    }
}

TEST_CASE("check player func") {
    Player p1("Alice");
    Player p2("Bob");
    CHECK(p1.stacksize() == 26);
    CHECK(p2.stacksize() == 26);
    CHECK(p1.cardesTaken() == 0);
    CHECK(p2.cardesTaken() == 0);
    Game game(p1,p2);
    CHECK_NOTHROW(game.playAll());
    CHECK(p1.stacksize() == 0);
    CHECK(p2.stacksize() == 0);
    CHECK(p1.cardesTaken()+p2.cardesTaken() == 52);
}

TEST_CASE("check throws when printLastTurn() action before the gmae start and not throw if the game start") { 
    Player p1("Alice");
    Player p2("Bob");

    Game game(p1,p2); 
    CHECK_THROWS(game.printLastTurn());
    for (int i=0;i<5;i++) {
        CHECK_NOTHROW(game.playTurn());
    }
    CHECK_NOTHROW(game.printLastTurn());
}

TEST_CASE("check throws when printWiner() action before the gmae over and not throw if the game over") { 
    Player p1("Alice");
    Player p2("Bob");

    Game game(p1,p2); 
    CHECK_THROWS(game.printWiner());
    CHECK_NOTHROW(game.playAll());
    CHECK_NOTHROW(game.printWiner());
}

TEST_CASE("check throws when playTurn() action after playAll()") { 
    Player p1("Alice");
    Player p2("Bob");

    Game game(p1,p2); 
    CHECK_NOTHROW(game.playAll());
    CHECK_THROWS(game.playTurn());
    CHECK_NOTHROW(game.printWiner());
}

TEST_CASE("check case the game over without winner and the result is draw") { 
    Player p1("Alice");
    Player p2("Bob");

    Game game(p1,p2); 
    CHECK(p1.stacksize() == 26);
    CHECK(p2.stacksize() == 26);
    CHECK(p1.cardesTaken() == 0);
    CHECK(p2.cardesTaken() == 0);
    CHECK_NOTHROW(game.playAll());
    CHECK_NOTHROW(game.printWiner());
    CHECK_NOTHROW(game.playAll());
    CHECK(p1.cardesTaken() == 26);
    CHECK(p2.cardesTaken() == 26);   
}