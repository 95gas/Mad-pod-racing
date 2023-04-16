#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;


class Checkpoint {       // The class
  public:             // Access specifier
    int x;        // Attribute (int variable)
    int y;  // Attribute (string variable)
};

int distanceBetweenTwoPoints(int x, int y, int a, int b){
    return sqrt(pow(x - a, 2) + pow(y - b, 2));
}


int calculate_thrust(std::vector< Checkpoint > & list, int lap, int x, int y, int prev_x, int prev_y, int next_checkpoint_angle, int next_checkpoint_x, int next_checkpoint_y, int next_checkpoint_distance, int next_prev_checkpoint_distance,int CheckpointRadius){
    double thrust = 100;

    if (abs(next_checkpoint_angle) > 18){
        thrust*= max(min((1 - (abs(next_checkpoint_angle)/90.0)), 1.0), 0.0);
        thrust*= max(min((next_checkpoint_distance/(double)(CheckpointRadius*2)), 1.0), 0.0);
    }

    // check drift
    int speed = sqrt((x - prev_x)*(x - prev_x) + (y - prev_y)*(y - prev_y));

    if ( speed*3 > next_checkpoint_distance and lap > 0 and -6 < next_checkpoint_angle < 6){

        int index_next = 0;

        for(unsigned int i = 0; i < list.size(); i++){

                    if (list[i].x == next_checkpoint_x and next_checkpoint_y == list[i].y){

                        if (i!=list.size()-1){
                            index_next = i++;
                        }
            
                    }
        }

        cout << list[index_next].x << " " << list[index_next].y << " " << 40 << endl;
        
        return -1;           
        }

                

    return int(thrust);
}


Checkpoint CheckpointManager(std::vector< Checkpoint > & list, std::vector< int > & dist, Checkpoint nextCheckpoint, Checkpoint firstCheckpoint, int next_checkpoint_dist, int& lap){
    
    Checkpoint best_check;
    bool newLap = false;

    cerr << "Run function\n" << endl;

    if (lap == 0){

        if (list[list.size()-1].x != nextCheckpoint.x and nextCheckpoint.y != list[list.size()-1].y){
        
            if (nextCheckpoint.x != firstCheckpoint.x and firstCheckpoint.y != nextCheckpoint.y){
                list.push_back(nextCheckpoint);
                dist.push_back(next_checkpoint_dist);
            }
            else{
                newLap = true;
                lap = lap+1;
                cerr << "NewLap\n" << endl;
            }
        
        }
    }

    if (lap==1){

        // find best checkpoint where to boost

        // compute distance

        // find best spot where to use BOOST

        int index_max = 0;
        int max=0;
        
         for(unsigned int i = 0; i < dist.size(); i++){

            if (dist[i]>max){
                index_max = i;
                max = dist[i];
            }
        }

        best_check = list[index_max];

        return best_check;
    }
    
    best_check.x=-1;
    best_check.y=-1;

    return best_check;
}


int main()
{

    bool boost = true;

    std::vector< Checkpoint > list;
    std::vector< int > dist;

    bool game_started = false;
    Checkpoint first_checkpoint;

    int lap = 0;

    int prev_x= 0;
    int prev_y = 0;
    
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

        // save first checkpoint
        if (!game_started){
            first_checkpoint.x=next_checkpoint_x;
            first_checkpoint.y=next_checkpoint_y;
            game_started = true;
            list.push_back(first_checkpoint);
            dist.push_back(next_checkpoint_dist);
        }

        

        int thrust = calculate_thrust(list, lap, x,y, prev_x, prev_y, next_checkpoint_angle, next_checkpoint_x, next_checkpoint_y, next_checkpoint_dist, next_prev_checkpoint_dist, 600);
        
        prev_x = x;
        prev_y=y;

        next_prev_checkpoint_dist = next_checkpoint_dist;

        
        Checkpoint nextChecpoint;
        nextChecpoint.x = next_checkpoint_x;
        nextChecpoint.y = next_checkpoint_y;
        
        Checkpoint best = CheckpointManager(list, dist, nextChecpoint, first_checkpoint, next_checkpoint_dist, lap);

        if (best.x == nextChecpoint.x and nextChecpoint.y == best.y){
            if (boost == true){ // is the boost available?
                if (abs(next_checkpoint_angle) <= 1){
                    cout << next_checkpoint_x << " " << next_checkpoint_y << " " << "BOOST" << endl;
                    cerr << "BOOST" << endl;
                    boost = false;
                }
                else
                    if (thrust!=-1)
                        cout << next_checkpoint_x << " " << next_checkpoint_y << " " << thrust << endl;
            }
            else{
                if (thrust!=-1)
                    cout << next_checkpoint_x << " " << next_checkpoint_y << " " << thrust << endl;
            }
        }
        else{
            if (thrust!=-1)
                cout << next_checkpoint_x << " " << next_checkpoint_y << " " << thrust << endl;
        }
    
    }
}