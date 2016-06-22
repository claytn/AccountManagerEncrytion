#include <iostream>
#include <string>
#include "Root.h"


Root::Root(string username, string password): User(username, password){

}

Root::Root(string username, string password, string message): User(username, password, message){

}

Root::~Root(){}



