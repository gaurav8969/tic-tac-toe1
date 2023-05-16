#include <string>
#include <map>
#include <utility>
#include <vector>
#include "pichierarchy.h"
#include "circlecross.h"
using std::string;
using std::map;
using std::vector;
using std::string;
using std::vector;
using std::pair;
//some frequently used objects
enum Cell : char
{
	First = 1, Second, Third, Fourth, Fifth, Sixth, Seventh, Eigth, Ninth
};
Circle circle(2);
Cross cross(5);
map<int, Picture> framed_grid;

void nakedblankcell(vector<string>& ret,int height) {
	int looptemp = height;
	string a("");
	while (height--) {
		string a("");
		while (looptemp--)
			a = a + " ";
		ret.push_back(a);		
	}
}

void grid_initializer(map<int, int>& grid) {
	for (int cell =  First; cell <= Ninth; ++cell) {
		grid[cell] = -1;
	}
}
/*will take a naked grid instance and 
frame it in a new map, from which we shall choose pictures to concatenate, since 
we are using a reference handle for shared ownership, this will basically
incur no extra overhead while enabling us to clean up the interace.*/

void grid_frame(const map<int, int>&grid)
{
	for (const pair<int, int>& cell : grid) {
		if (cell.second == 0) { //circle
			Picture Cell(circle.fetchvec());
		}
	}
}