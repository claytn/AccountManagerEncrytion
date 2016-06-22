all: proj


proj:
	g++ -Wall -Werror -g -o run main.cpp User.cpp Root.cpp
