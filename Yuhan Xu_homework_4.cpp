/* ******************************************************
 * Name: Yuhan Xu
 * Wisc ID: 9075265950
 * OS: Windows
 * IDE (or text editor):Eclipse
 * Compiler: MinGW
 * How long did the assignment take you to complete in minutes: 5 hours
 * What other resources did you consult (copy and paste links below): None
 *
 */ // ******************************************************
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <time.h>

using namespace std;

// feel free to use this function if you wish
// purpose: generate random coordinates
// input: none
// output: a vector with 2 coordinates between 1,1 and 4,4
vector<int> Get_A_Random_Square() {
	return vector<int> { rand() % 4 + 1, rand() % 4 + 1 };
}

// feel free to use this function if you wish
// purpose: verifies if the coordinates of a square fall within the cave
// input: coordinates of a square
// output: true if the square is in the cave otherwise false
bool Is_Square_Valid(const vector<int> &square) {
	for (auto e : square)
		if (e < 1 || e > 4)
			return false;
	return true;
}

// don't change this function
// purpose: prints a map of the cave to the console
// input: the printable map a vector of strings
// output: none - console output of the cave diagram
void Print_Cave_Diagram(const vector<string> &cave_diagram) {
	for (auto s : cave_diagram)
		cout << s << endl;
}

// Implement these functions below
// Do not change the function prototpyes
void Initialize_Cave(map<vector<int>, set<string> > &cave);
void Print_Square(map<vector<int>, set<string> > &cave, const vector<int> &rc);
void Get_Cave_Diagram(map<vector<int>, set<string> > &cave,
		vector<string> &cave_diagram);

// sample main function
int main() {

	srand(time(NULL)); // seed the random generator

	// Declare the cave data structure to 'map' coordinates to a 'set' of strings describing the cell contents
	map<vector<int>, set<string> > cave;

	// Check this out! The cave data structure has a lot going on
	// Uncomment the block below to see a demo of how to use the cave map
	// use the [] to access the set contained in the map
	// insert puts the word "ladder" into the set
	// cave[rc] is the set of words at coordinates rc
	// cave[rc].begin() returns an iterator to the first element of the set
	// note your program will likely crash if the set is empty
	// I recommend checking for this.
	// use the * to dereference the pointer to get the first word stored in the set

	/*vector<int> rc{1, 1}; // row column
	 cave[rc].insert("ladder");
	 if (cave[rc].empty() == false)
	 cout<<"cave square (1,1) contains a "<<*cave[rc].begin()<<endl;
	 // */

	Initialize_Cave(cave);

	for (int r = 1; r <= 4; r++) {
		for (int c = 1; c <= 4; c++) {
			vector<int> rc {r,c};
			Print_Square(cave, rc);
		}
	}

	vector<string> cave_diagram;
	Get_Cave_Diagram(cave, cave_diagram);
	Print_Cave_Diagram(cave_diagram);

	return 0;
}

// add the player, ladder, wumpus, pits, gold, stench, breeze to the map
// input: map<vector<int>, set<string> > &cave
// output:
void Initialize_Cave(map<vector<int>, set<string> > &cave) {
	// place the "ladder" in row 1 column 1
	vector<int> cave_ladder {1,1};
	cave[cave_ladder].insert("ladder");
	// place the "player" at the same location as the ladder
	cave[cave_ladder].insert("player");
	// place the "wumpus" - can't be in the same square as the ladder
	vector<int> cave_wumpus(2);

	while (true) {

		// call Get_A_Random_Square() function to generate random coordinates
		cave_wumpus = Get_A_Random_Square();

		// if there is no ladder
		if (cave[cave_wumpus].count("ladder") == 0) {
			// put wumpus into this coordinate
			cave[cave_wumpus].insert("wumpus");
			break; // break while loop
		}

	}

	// place the 3 "pits" - can't be in the same square as the ladder, wumpus, or another pit
	int number_of_pit = 0; // create an int variable to count the number of pit
	vector<int> locations; // create a vector of locations
	while (true) {
		vector<int> cave_pit = Get_A_Random_Square(); //generate coordinates

		// if there is not a ladder, wumpus,or pit in this square
		if (cave[cave_pit].count("wumpus") == 0 & cave[cave_pit].count("ladder") == 0 & cave[cave_pit].count("pit") == 0) {
			// insert pit
			cave[cave_pit].insert("pit");
			locations.push_back(cave_pit[0]);
			locations.push_back(cave_pit[1]);
			number_of_pit ++;

		}

		// if there are 3 pits, break the loop
		if (number_of_pit == 3) break;

	}

	// place the "gold" - can't be in the same square as a pit or the ladder
	vector<int> cave_gold;
	while (true) {
		// generate random coordinates for rc_gold
		cave_gold = Get_A_Random_Square();
		if (cave[cave_gold].count("pit") == 0 & cave[cave_gold].count("ladder") == 0) {
			cave[cave_gold].insert("gold");
			break;
		}
	}

	// place the "stench" squares to the left, right, up, and down from the wumpus
	int row = cave_wumpus[0];
	int col = cave_wumpus[1];

	vector<int> down {row+1,col};

	vector<int> left {row,col-1};

	vector<int> right {row,col+1};

	vector<int> up {row-1,col};

	if (Is_Square_Valid(up))
		cave[up].insert("stench");

	if (Is_Square_Valid(down))
		cave[down].insert("stench");

	if (Is_Square_Valid(left))
		cave[left].insert("stench");

	if (Is_Square_Valid(right))
		cave[right].insert("stench");

	// place the "breeze" squares to the left, right, up, and down from the three pits
	vector<int> location_of_pit1 {locations[0],locations[1]};
	vector<int> location_of_pit2 {locations[2],locations[3]};
	vector<int> location_of_pit3 {locations[4],locations[5]};

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			vector<int> square{i,j};

			if (cave[square].count("pit") == 1) {
				// define and initialize row and col of pit
				int row_of_pit = square[0];
				int col_of_pit = square[1];

				// represent each direction of the pit
				vector<int> pit_down {row_of_pit + 1,col_of_pit};

				vector<int> pit_left {row_of_pit,col_of_pit - 1};

				vector<int> pit_right {row_of_pit,col_of_pit + 1};

				vector<int> pit_up {row_of_pit - 1,col_of_pit};

				if (Is_Square_Valid(pit_up) & cave[pit_up].count("breeze") == 0)
					cave[pit_up].insert("breeze");

				if (Is_Square_Valid(pit_down) & cave[pit_down].count("breeze") == 0)
					cave[pit_down].insert("breeze");

				if (Is_Square_Valid(pit_left) & cave[pit_left].count("breeze") == 0)
					cave[pit_left].insert("breeze");

				if (Is_Square_Valid(pit_right) & cave[pit_right].count("breeze") == 0)
					cave[pit_right].insert("breeze");

			}

		}
	}

}

// print the contents of the square
// input: map<vector<int>, set<string> > &cave, const vector<int> &rc
// output:
void Print_Square(map<vector<int>, set<string> > &cave, const vector<int> &rc) {
	cout << "This part of the cave contains" << endl;
	if(cave[rc].empty() == true){
		cout << "    nothing" << endl;
	}
	else {
		// for each element in cave[rc], print them out
		for (string s : cave[rc]) {
				cout << "    " << s << endl;
		}

	}

}

// build a vector of strings where each string in the vector represents one row of the cave output
// input: map<vector<int>, set<string> > &cave, vector<string> &cave_diagram
// output:
void Get_Cave_Diagram(map<vector<int>, set<string> > &cave, vector<string> &cave_diagram) {
	int cell_rows = 5;
	int cell_columns = 11;
	int total_rows = cell_rows * 4 + 1;
	int total_columns = cell_columns * 4 + 1;

	// fill in with vertical cell divisions
	for (int r = 0; r < total_rows; r++) {
		string row(total_columns, ' ');
		for (int c = 0; c < total_columns; c += cell_columns) {
			row[c] = '|';
		}
		cave_diagram.push_back(row);
	}

	// udpate horizontal rows with '-'
	for (int i = 0; i < total_rows; i += cell_rows) {
		cave_diagram[i] = string(total_columns, '-');
	}

	// update cell corners with '+'
	for (int r = 0; r < total_rows; r += cell_rows) {
		for (int c = 0; c < total_columns; c += cell_columns) {
			cave_diagram[r][c] = '+';
		}
	}

	// replace the part of the string with the cell contents

	for (int i = 1; i <= 4; i++) { //go through each square
		for (int j = 1; j <= 4; j++) {
			// create a vector of coordinates(i,j)
			vector<int> vec {i,j};

			int k = 1;
			for (string s : cave[vec]) {
				cave_diagram[5 * (i-1) + k ].replace(11 * (j-1) + 3, s.length(), s);
				k++;
			}
		}
	}

}

