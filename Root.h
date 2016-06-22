#ifndef ROOT_H
#define ROOT_H
#include <string>
#include <vector>
#include "User.h"

class Root: public User{

	public:
		Root(std::string, std::string);
		Root(std::string, std::string, std::string);
		~Root();


};



#endif
