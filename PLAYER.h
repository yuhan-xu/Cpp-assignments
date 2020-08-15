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

#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <time.h>
#include "CAVE.h"

using namespace std;

// define class PLAYER, including some public methods required in the instruction
class PLAYER {
 vector<int> Location_of_player = {1,1};
 vector<int> Slocation = {1,1};
 string Direction ="right";
 string status = "alive";
 string arrow = "yes";
 bool shoot_arrow = false;
 bool has_gold = false;
 bool updated_status = true;
 string eat = "no";
 string fall = "no";

public:
	vector<int> Get_Position();
    string Get_Facing();
	void Turn_Left();
	void Turn_Right();
	vector<int> Get_Next_Square();
	void Move_Forward();
	bool Pickup_Gold(CAVE &cave);
	bool Shoot_Arrow(CAVE cave);
	void Climb_Ladder();
	bool Has_Arrow();
	bool Has_Gold();
	bool Update_Player_Status(CAVE cave);
	bool Escaped();
	bool Eaten();
	bool Fell();
};


#endif /* PLAYER_H_ */
