#include "../include/dot.hpp"

Dot::Dot(int x, int y) {
	this->x = x;
	this->y = y;
	connected = new std::vector<Dot *>();
}

Dot::~Dot() {
	/*
	for (Dot *dot : *connected) {
		delete dot;
	}
	*/
	
	/*
	delete connected;
	*/
}

int Dot::getX() {
	return x;
}

int Dot::getY() {
	return y;
}

std::vector<Dot *> *Dot::getConnectedDotsVector() {
	return connected;
}

bool Dot::equals(Dot dot) {
	bool n = ((this->x == dot.getX()) && (this->y == dot.getY()));
	return n;
}
