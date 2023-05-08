#pragma once
#include <vector>
#include <string>
class Circle {
public:
	Circle(const int&& = 0); //vs underlining Circle, fucking loitering lush of a parser
	void display();
private:
	std::vector<std::string> circle;
};

class Cross {
public:
	Cross(const int&& = 0);
	void display();
private:
	std::vector<std::string> cross;
};