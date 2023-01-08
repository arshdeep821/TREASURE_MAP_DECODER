#define CATCH_CONFIG_MAIN
#include <iostream>
#include "cs221util/catch.hpp"
#include "stack.h"
#include "queue.h"
#include "deque.h"
//using namespace cs221util;
using namespace std;

TEST_CASE("test::Deque Class Part 1") {

    Deque<int> array;

    //test pushR
    for (int i = 1; i<6; i++) {
        array.pushR(i);
    }

    //test peekL
    REQUIRE(array.peekL() == 1);
    //cout <<array.peekL() << " == " << "1" <<endl;

    //test peekR
    REQUIRE(array.peekR() == 5);
    //cout <<array.peekR() << " == " << "5" <<endl;

    //test popR
    int curr = array.popR();
    REQUIRE(curr == 5);
    //cout << "Element to get removed from popR: "<< curr << " == " << "5" << endl;
    REQUIRE(array.peekL() == 1);
    //cout << "peekL: " << array.peekL() << " == " << "1" << endl;
    REQUIRE(array.peekR() == 4);
    //cout << "peekR: " << array.peekR() << " == " << "4" << endl;

    
    // passes
    
    //test popL
    curr = array.popL();
    REQUIRE(curr == 1);
    //cout << "Element to get removed from popL: "<< curr << " == " << "1" << endl;
    REQUIRE(array.peekL() == 2);
    //cout << "peekL: " << array.peekL() << " == " << "2" << endl;
    REQUIRE(array.peekR() == 4);
    //cout << "peekR: " << array.peekR() << " == " << "4" << endl;

    // passes

    curr = array.popR();
    REQUIRE(curr == 4);
    //cout << "Element to get removed from popR: "<< curr << " == " << "4" << endl;
    REQUIRE(array.peekL() == 2);
    //cout << "peekL: " << array.peekL() << " == " << "2" << endl;
    REQUIRE(array.peekR() == 3);
    //cout << "peekR: " << array.peekR() << " == " << "3" << endl;

    // passes

    curr = array.popR();
    REQUIRE(curr == 3);
    //cout << "Element to get removed from popR: "<< curr << " == " << "3" << endl;
    REQUIRE(array.peekL() == 2);
    //cout << "peekL: " << array.peekL() << " == " << "2" << endl;
    REQUIRE(array.peekR() == 2);
    //cout << "peekR: " << array.peekR() << " == " << "2" << endl;

    // passes

    curr = array.popR();
    REQUIRE(curr == 2);
    //cout << "Element to get removed from popR: "<< curr << " == " << "2" << endl;
    //cout << array.isEmpty() << endl;
    REQUIRE(array.isEmpty() == 1);

}

TEST_CASE("test::Deque Class Part 2") {
    Deque<int> array;

    //test pushR
    for (int i = 1; i<6; i++) {
        array.pushR(i);
    }

    //test peekL
    REQUIRE(array.peekL() == 1);
    //cout <<array.peekL() << " == " << "1" <<endl;

    //test peekR
    REQUIRE(array.peekR() == 5);
    //cout <<array.peekR() << " == " << "5" <<endl;

    //test popL
    int curr = array.popL();
    REQUIRE(curr == 1);
    //cout << "Element to get removed from popL: "<< curr << " == " << "1" << endl;
    REQUIRE(array.peekL() == 2);
    //cout << "peekL: " << array.peekL() << " == " << "2" << endl;
    REQUIRE(array.peekR() == 5);
    //cout << "peekR: " << array.peekR() << " == " << "5" << endl;

    curr = array.popL();
    REQUIRE(curr == 2);
    //cout << "Element to get removed from popL: "<< curr << " == " << "2" << endl;
    REQUIRE(array.peekL() == 3);
    //cout << "peekL: " << array.peekL() << " == " << "3" << endl;
    REQUIRE(array.peekR() == 5);
    //cout << "peekR: " << array.peekR() << " == " << "5" << endl;

    curr = array.popL();
    REQUIRE(curr == 3);
    //cout << "Element to get removed from popL: "<< curr << " == " << "3" << endl;
    REQUIRE(array.peekL() == 4);
    //cout << "peekL: " << array.peekL() << " == " << "4" << endl;
    REQUIRE(array.peekR() == 5);
    //cout << "peekR: " << array.peekR() << " == " << "5" << endl;

    curr = array.popL();
    REQUIRE(curr == 4);
    //cout << "Element to get removed from popL: "<< curr << " == " << "4" << endl;
    REQUIRE(array.peekL() == 5);
    //cout << "peekL: " << array.peekL() << " == " << "5" << endl;
    REQUIRE(array.peekR() == 5);
    //cout << "peekR: " << array.peekR() << " == " << "5" << endl;

    curr = array.popL();
    REQUIRE(curr == 5);
    //cout << "Element to get removed from popL: "<< curr << " == " << "5" << endl;
    REQUIRE(array.isEmpty() == 1);
    //cout << array.isEmpty() << endl;
}

TEST_CASE("stack::basic functions","[weight=1][part=stack]"){
    //cout << "Testing Stack..." << endl;
    Stack<int> intStack;
    vector<int> result;
    vector<int> expected;
    for (int i = 10; i > 0; i--) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intStack.push(i);
    }
    while (!intStack.isEmpty()) {
        result.push_back(intStack.pop());
    }
    REQUIRE( result == expected);
}
TEST_CASE("queue::basic functions","[weight=1][part=queue]"){
    Queue<int> intQueue;
    vector<int> result;
    vector<int> expected;
    for (int i = 1; i <= 10; i++) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intQueue.enqueue(i);
    }
    while (!intQueue.isEmpty()) {
        result.push_back(intQueue.dequeue());
    }
    REQUIRE( result == expected);
}