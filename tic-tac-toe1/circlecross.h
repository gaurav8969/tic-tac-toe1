#pragma once
#include <vector>
#include <string>
class Circle {
public:
	Circle(const int&& radius= 0); //vs underlining Circle, fucking loitering lush of a parser
	const std::vector<std::string>& fetchvec() {return circle;}
	void display();
private:
	std::vector<std::string> circle;
};

class Cross {
public:
	Cross(const int&& height= 0);
	const std::vector<std::string>& fetchvec() {return cross;}
	void display();
private:
	std::vector<std::string> cross;
};