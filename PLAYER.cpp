/* ******************************************************
 * Name: Yuhan Xu
 * Wisc ID: 9075265950
 * OS: Windows
 * IDE (or text editor):Eclipse
 * Compiler: MinGW
 * How long did the assignment take you to complete in minutes: 3 hours
 * What other resources did you consult (copy and paste links below): None
 *
 */ // ******************************************************
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "CAVE.h"
#include "PLAYER.h"
#include "PLAYER.h"

using namespace std;

// get the position and return the location of player
vector<int> PLAYER::Get_Position() {
	return Location_of_player;
}

// get the facing of player and return the Direction
string PLAYER::Get_Facing() {
	return Direction;
}

// let player turn left. It includes different situations depending on which direction the player is facing now
void PLAYER::Turn_Left() {
	if (Direction == "left") {
		Direction = "down";
	} else if (Direction == "right") {
		Direction = "up";
	} else if (Direction == "up") {
		Direction = "left";
	} else {
		Direction = "right";
	}
}
// let player turn right. It includes different situations depending on which direction the player is facing now
void PLAYER::Turn_Right() {
	if (Direction == "left") {
		Direction = "up";
	} else if (Direction == "right") {
		Direction = "down";
	} else if (Direction == "up") {
		Direction = "right";
	} else {
		Direction = "left";
	}
}

// get the location of next square, here we also separate into several cases depending on which direction the player is facing right now
vector<int> PLAYER::Get_Next_Square() {
	if (Direction == "left") {
		Slocation[1] = Location_of_player[1] - 1;
	} else if (Direction == "right") {
		Slocation[1] = Location_of_player[1] + 1;
	} else if (Direction == "up") {
		Slocation[0] = Location_of_player[0] - 1;
	} else {
		Slocation[0] = Location_of_player[0] + 1;
	}
	return Slocation;
}

// move the player forward depending on the direction the player is facing
void PLAYER::Move_Forward() {
	if (Direction == "left") {
		Location_of_player[1] -= 1;
	} else if (Direction == "right") {
		Location_of_player[1] += 1;
	} else if (Direction == "up") {
		Location_of_player[0] -= 1;
	} else {
		Location_of_player[0] += 1;
	}
}

// if player is at that location, set has_goal is true, we remove the gold at the location of the players (same as pick gold)
bool PLAYER::Pickup_Gold(CAVE &cave) {
	// if the location of player contains gold
	if (cave.Square_Contains_Gold(Location_of_player) == true) {
		has_gold = true; // set has_gold to true
		cave.Remove_Gold(Location_of_player); // remove the gold

	}
	return has_gold; // return has_gold
}

// Shoot_Arrow returns a boolean expression and decides if player shoots arrow. It also depends on the facing direction right now
bool PLAYER::Shoot_Arrow(CAVE cave) {
	if (Direction == "left") { // if the player faces left
		for (int i = Location_of_player[1]; i >= 1; i--) {

					if (cave.Square_Contains_Living_Wumpus( { Location_of_player[0], i }) == true) {

						if (cave.Is_Wumpus_Alive() == false) {
							shoot_arrow = true;
							break;
						} else {
							break;
						}

					}
				}

	} else if (Direction == "right") { // else if the player faces right
		for (int i = Location_of_player[1]; i <= cave.Get_A_Random_Square()[1]; i++) {

					if (cave.Square_Contains_Living_Wumpus( { Location_of_player[0], i }) == true) {

						if (cave.Is_Wumpus_Alive() == false) {
							shoot_arrow = true;
							break;
						} else {
							break;
						}

					}

				}
	} else if (Direction == "up") {
		for (int i = Location_of_player[0]; i >= 1; i--) {

			if (cave.Square_Contains_Living_Wumpus( { i, Location_of_player[1] }) == true) {

				if (cave.Is_Wumpus_Alive() == false) {
					shoot_arrow = true;
					break;
				} else {

					break;
				}
			}

		}
	} else {
		for (int i = Location_of_player[0]; i <= cave.Get_A_Random_Square()[0]; i++) {

			if (cave.Square_Contains_Living_Wumpus( { i, Location_of_player[1] }) == true) {

				if (cave.Is_Wumpus_Alive() == false) {
					shoot_arrow = true;
					break;
				} else {
					break;
				}
			}
		}
	}

	arrow = "no";

	return shoot_arrow; // return shoot_arrow
}

// set status to be "escaped"
void PLAYER::Climb_Ladder() {
	status = "escaped";
}

// if arrow is "yes", return true; otherwise, return false
bool PLAYER::Has_Arrow() {
	if (arrow == "yes") {
		return true;
	} else {
		return false;
	}
}

// if has_gold is "yes", return true; otherwise, return false
bool PLAYER::Has_Gold() {
	if (has_gold == true) {
		return true;
	} else {
		return false;
	}

}

// update the status of players at certain cave
bool PLAYER::Update_Player_Status(CAVE cave) {
	// if the cave contains pit at the location of player
	if (cave.Square_Contains_Pit(Location_of_player)) {
		fall = "yes"; // set fall to yes
		updated_status = false; //set updated_status to false
	} else if (cave.Square_Contains_Living_Wumpus(Location_of_player) == true) {
		// if there is a living wumpus at the location of player
		eat = "yes"; // set eat to yes
		updated_status = false; // set updated_status to false
	}
	return updated_status; // return updated_status

}

// This returns a boolean expression depending on the status of player
bool PLAYER::Escaped() {
	// if status is "escaped", return true; otherwise, return false
	if (status == "escaped") {
		return true;

	} else {
		return false;
	}
}

// This returns a boolean expression depending on whether the player is eaten
bool PLAYER::Eaten() {
	// if eat is "yes", return true; otherwise, return false
	if (eat == "yes") {
		return true;
	} else {
		return false;
	}
}

// This returns a boolean expression depending on whether the player is fell
bool PLAYER::Fell() {
	// if fall is "yes", return true; otherwise, return false
	if (fall == "yes") {
		return true;
	} else {
		return false;
	}

}

// main method
int main() {
	enum GAME_STATUS {
		BEGIN, QUITTER, END
	};
	enum INPUT_OPTION {
		INVALID, QUIT, MOVE, LEFT, RIGHT, SHOOT, PICKUP, CLIMB, MAP, POSITION
	};
	map<char, INPUT_OPTION> char_to_input;
	char_to_input['q'] = QUIT;
	char_to_input['m'] = MOVE;
	char_to_input['l'] = LEFT;
	char_to_input['r'] = RIGHT;
	char_to_input['s'] = SHOOT;
	char_to_input['p'] = PICKUP;
	char_to_input['c'] = CLIMB;
	char_to_input['z'] = MAP;
	char_to_input['x'] = POSITION;

	CAVE cave;
	PLAYER player;
	int turn_counter = 0;
	GAME_STATUS game_status = BEGIN;

	while (game_status == BEGIN) {
		// print the turn message
		cout << "Turn " << ++turn_counter << ". ";
		cave.Print_Square(player.Get_Position());
		cout
				<< "(q)uit, (m)ove forward, (l)eft, (r)ight, (s)hoot, (p)ickup gold, (c)limb ladder, (z)display map, (x)print player position and facing"
				<< endl;
		cout << "Enter your choice: ";

		// read the whole line but just use the first character
		string line;
		getline(cin, line);
		cout << endl;
		char c = *line.begin();
		INPUT_OPTION choice = INVALID;
		if (char_to_input.count(c))
			choice = char_to_input[c];

		// perform player action
		switch (choice) {
		case QUIT: {
			game_status = QUITTER;
		}
			break;
		case MAP: {
			cave.Print_Cave_Diagram();
		}
			break;
		case POSITION: {
			vector<int> position = player.Get_Position();
			string direction = player.Get_Facing();
			cout << "You are in square (" << position[0] << "," << position[1] << ") facing "
					<< direction << endl;
		}
			break;
		case LEFT: {
			player.Turn_Left();
		}
			break;
		case RIGHT: {
			player.Turn_Right();
		}
			break;
		case MOVE: {
			vector<int> next_square = player.Get_Next_Square();
			bool valid = cave.Is_Square_Valid(next_square);
			if (valid) {
				player.Move_Forward();
				cout << "You step forward into the next square!" << endl;
			} else
				cout << "Bump! You have walked into a wall!" << endl;

		}
			break;
		case SHOOT: {
			if (player.Has_Arrow()) {
				bool wumpus_killed = player.Shoot_Arrow(cave);
				if (wumpus_killed)
					cout << "You hear a terrible scream!" << endl;
				else
					cout << "The arrow missed the wumpus!" << endl;
			} else
				cout << "You don't have another arrow!" << endl;
		}
			break;
		case PICKUP: {
			if (player.Pickup_Gold(cave))
				cout << "You have picked up a piece of gold!" << endl;
			else
				cout << "There isn't any gold here!" << endl;
		}
			break;
		case CLIMB: {
			if (cave.Square_Contains_Ladder(player.Get_Position()))
				player.Climb_Ladder();
			else
				cout << "There isn't a ladder here!" << endl;
		}
			break;
		case INVALID: // fall through to default
		default:
			cout << "Invalid choice" << endl;
		}

		// update character status
		bool still_alive = player.Update_Player_Status(cave);
		if (still_alive == false)
			game_status = END;
		if (player.Escaped())
			game_status = END;

	} // end of game while loop

// compute the player score
	if (game_status == QUITTER) {
		cout << endl
				<< "   ### GAME OVER ###\n   You have decided to quit.\n   Your final score is 0."
				<< endl;
		return 0;
	}
	if (player.Eaten()) {
		cout << endl
				<< "   ### GAME OVER ###\n   You were eaten by the wumpus.\n   Your final score is 0."
				<< endl;
		return 0;
	}
	if (player.Fell()) {
		cout << endl << "   ### GAME OVER ###\n   You fell into a pit.\n   Your final score is 0."
				<< endl;
		return 0;
	}

	int score = 0;
	if (player.Has_Gold())
		score += 10;
	if (player.Has_Arrow() == false)
		score -= 5;
	if (cave.Is_Wumpus_Alive() == false)
		score += 5;
	if (player.Escaped() == false)
		score = 0;

	cout << endl << endl;
	cout << endl << "   ### GAME OVER ###\n   Your final score is " << score << "." << endl;
	if (player.Has_Gold())
		cout << "   You have found the gold!" << endl;
	else
		cout << "   You have escaped with your life!" << endl;
	if (cave.Is_Wumpus_Alive() == false)
		cout << "   You have killed the wumpus" << endl;

	return 0;

}

