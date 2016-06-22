#include <iostream>
#include <string>
#include "User.h"

using namespace std;

User::User(){

	this->userName = "";
	this->passWord = "";
	this->message = "";

}


User:: User(string userName, string passWord){

	this->userName = userName;
	this->passWord = passWord;
	message = "";

}

User :: User(string userName, string passWord, string message){

	this->userName = userName;
	this->passWord = passWord;
	this->message = message;
}
/*
   User::User(const User & another){

   this->userName = another.getUsername();
   this->passWord = another.getPassword();

   }
   */


void User::getMessage(){

	cout << message << endl;
}

string User:: getUsername(){

	return userName;
}

string User :: getPassword(){

	return passWord;
}

User & User::operator=(User & copy){

	this->userName = copy.getUsername();
	this->passWord = copy.getPassword();
	this->message = copy.message;

	return *this;


}

ostream & operator<<(ostream & lhs, User & rhs){

			lhs << "User Information" << endl
			<< "Username: "<< rhs.userName << endl
			<< "Password: "<< rhs.passWord << endl << "Messages: ";
			if(rhs.message == ""){
			cout << "No Messages.";
			}
			else{
			cout << rhs.message;

			}
			return (cout << endl);
			}
