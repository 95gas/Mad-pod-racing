#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int distanceBetweenTwoPoints(int x, int y, int a, int b){
return sqrt(pow(x - a, 2) + pow(y - b, 2));
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
        
        if (next_checkpoint_angle > 60 or next_checkpoint_angle < -60)
            thrust = 20;
        if (next_checkpoint_angle > 90 or next_checkpoint_angle < -90)
            thrust = 10;
        else
            thrust = 100;


        // BOOST
        if (!BOOST){ // is the boost available?
            
            // are we heading towards a checkpoint?
            if (next_checkpoint_dist>=4000){
        
                // are the checkpoint far enough from us?
                if (next_checkpoint_angle <= 10 and next_checkpoint_angle >= -10){
                    BOOST = true;
                    cout << next_checkpoint_x << " " << next_checkpoint_y << " " << "BOOST" << endl;
                }
                else{
                 cout << next_checkpoint_x << " " << next_checkpoint_y << " " << thrust << endl;
                }
            }
            else{
                cout << next_checkpoint_x << " " << next_checkpoint_y << " " << thrust << endl;
            }
         }
        else{
            cout << next_checkpoint_x << " " << next_checkpoint_y << " " << thrust << endl;
        }
    }
}