#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int distanceBetweenTwoPoints(int x, int y, int a, int b){
return sqrt(pow(x - a, 2) + pow(y - b, 2));
}

int calculate_thrust(int x, int y, int opponent_x, int opponent_y,int* boost, int next_checkpoint_angle, int next_checkpoint_x, int next_checkpoint_y, int next_checkpoint_distance, int next_prev_checkpoint_distance,int CheckpointRadius){
    int thrust = 100;
    int dist = distanceBetweenTwoPoints(x, y,next_checkpoint_x, next_checkpoint_y);
    
    if (abs(next_checkpoint_angle) < 10){

        if (*boost == 0){ // is the boost available?

        // are we heading towards a checkpoint?
            if (next_checkpoint_distance>=4500){

                *boost = 1;
                return 101; // BOOST
            }
         
        }
    }
    else{
    
        thrust*= max(min((1 - abs(next_checkpoint_angle)/90), 1), 0);
        thrust*= max(min((next_checkpoint_distance/(CheckpointRadius*2)), 1), 0);
    }
        
    cerr << "Debug messages..." << endl;
    cerr << next_checkpoint_distance << endl;
    
    return thrust;
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{

    int BOOST = 0;
    

    int next_prev_checkpoint_dist = 0;

    // game loop
    while (1) {
        int x;
        int y;
        int next_checkpoint_x; // x position of the next check point
        int next_checkpoint_y; // y position of the next check point
        int next_checkpoint_dist; // distance to the next checkpoint
        int next_checkpoint_angle; // angle between your pod orientation and the direction of the next checkpoint
        cin >> x >> y >> next_checkpoint_x >> next_checkpoint_y >> next_checkpoint_dist >> next_checkpoint_angle; cin.ignore();
        int opponent_x;
        int opponent_y;
        cin >> opponent_x >> opponent_y; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;


        // You have to output the target position
        // followed by the power (0 <= thrust <= 100) or "BOOST"
        // i.e.: "x y thrust"
        
        int thrust = calculate_thrust(x,y, opponent_x, opponent_y, &BOOST, next_checkpoint_angle, next_checkpoint_x, next_checkpoint_y, next_checkpoint_dist, next_prev_checkpoint_dist, 600);
        next_prev_checkpoint_dist = next_checkpoint_dist;

        if (thrust == 101){
            cout << next_checkpoint_x << " " << next_checkpoint_y << " " << "BOOST" << endl;
        }
        else{
            cout << next_checkpoint_x << " " << next_checkpoint_y << " " << thrust << endl;
        }
    }
}