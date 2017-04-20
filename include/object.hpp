#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <string>
#include <vector>
#include "dot.hpp"

class Object {
private:
	std::string object_name;
	std::vector<Dot *> *dots;

public:
	Object(std::string object_name);
	~Object();
	
	std::string getName();
	std::vector<Dot *> *getDotsVector();
};

#endif
