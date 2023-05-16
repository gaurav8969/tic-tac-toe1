/*demo comment for github
demo comment 2 for github
demo comment 3 for github
demo comment 4 for github*/
#include "circlecross.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using std::cout;
using std::vector;
using std::string;

Circle::Circle(const int&& radius) {
	if (radius > 0) {
		for (auto y = -radius; y <= radius; y++) {
			string a("");
			for (auto x = -radius; x <= radius; x++)
			{
				if (sqrt(x * x + y * y) <= radius)
					a = a + "*";
				else
					a = a + " ";
			}
			circle.push_back(a);
		}
	}
	else
		circle = { "" };
}
void Circle::display() { //not of use in this program for we are going to display
	//"Pic" objects using display function of the stated class
	for (string i : circle) {
		cout << i << "\n";
	}
}

Cross::Cross(const int&& height) {
	for (auto i = 1; i <= height; i++) {
		for (auto j = 0; j <= height; j++) {
			if (i == j || i == height - j + 1)
				cout << "*";
			else
				cout << " ";
		}
		cout << "\n";
	}
}
void Cross::display() {
	for (string i : cross) {
		cout << i << "\n";
	}
}
