#include <iostream>
#include <string>

#ifndef USER_H
#define USER_H

using namespace std;

class User{
	private: 
		std::string userName ;
		std::string passWord ;
		
	public:
		User();

		User(std::string, std::string);

		User(std::string, std::string, std::string);


		std::string message ;

		void getMessage();

		std::string getUsername();

		std::string getPassword();

		User & operator=(User &);

		friend ostream & operator<<(ostream &, User &);


};

#endif
