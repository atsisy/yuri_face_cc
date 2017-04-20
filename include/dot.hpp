#ifndef DOT_HPP
#define DOT_HPP

#include <vector>

class Dot {
private:
	int x;
	int y;
	std::vector<Dot *> *connected;

public:
	Dot(int x, int y);
	~Dot();

	bool equals(Dot dot);
	int getX();
	int getY();
	std::vector<Dot *> *getConnectedDotsVector();

};

#endif
