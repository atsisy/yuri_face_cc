#include "../include/object.hpp"

Object::Object(std::string object_name) {
	this->object_name = object_name;
	dots = new std::vector<Dot *>();
}

Object::~Object() {
	for (Dot *dot : *dots) {
		delete dot;
	}
	delete dots;
}

std::string Object::getName() {
	return object_name;
}

std::vector<Dot *> *Object::getDotsVector() {
	return dots;
}
