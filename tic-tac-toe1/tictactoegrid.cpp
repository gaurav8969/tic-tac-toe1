#include <string>
#include <map>
#include <vector>
using std::string;
using std::map;
using std::vector;
void grid_initializer(map<int, string>& grid) {
	for (int i = 1; i < 10; i++) {
		grid[i] = "empty";
	}
}
void grid(map<int, string> grid) {
	grid_initializer(grid);
	
}