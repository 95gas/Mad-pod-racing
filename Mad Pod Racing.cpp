#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;


/**
 * Class representing the Checkpoint object
 */
class Checkpoint {       
  public:             
    int x;        
    int y;  
    int dist;
    int angle;
    int radius = 600;
};


/**
 * Class representing the Pod object
 */
class Pod {       
  public:             
    int x;        
    int y;  
};


/**
 * BOOST MANAGER
 *
 * Compute the best moment when to boost the pod. The moment is between the checkpoints with greater distance. 
 *
 * @param list of the checkpoints
 * @param number of lap
 * @param Next checkpoint
 * @param First checkpoint
 * @return The best position where to boost
 */
Checkpoint CheckpointManager(std::vector< Checkpoint > & list, int& lap, Checkpoint nextCheckpoint, Checkpoint firstCheckpoint){
    
    Checkpoint best_check;
    bool newLap = false;        //keep track if a new lap has begun

    // Store the checkpoint information during the first lap
    if (lap == 0){

        if (list[list.size()-1].x != nextCheckpoint.x and nextCheckpoint.y != list[list.size()-1].y){
        
            if (nextCheckpoint.x != firstCheckpoint.x and firstCheckpoint.y != nextCheckpoint.y){
                list.push_back(nextCheckpoint);
            }
            else{
                newLap = true;
                lap = lap+1;
            }
        }
    }

    // After the first lap, we compute the best moment when to boost
    if (lap==1){

        int index_max = 0;
        int max=0;
        
        for(unsigned int i = 0; i < list.size(); i++){
            if (list[i].dist > max){
                index_max = i;
                max = list[i].dist;
            }
        }
        
        best_check = list[index_max];

        return best_check;
    }
    
    best_check.x=-1;
    best_check.y=-1;

    return best_check;
}


/**
 * THRUST MANAGER
 *
 * Compute the best thrust to use. The closer a pod is to a checkpoint the lower its thrust is going to be.
 *
 * @param Boost boolean variable keeping track whether boost has already been used
 * @param list of the checkpoints
 * @param number of lap
 * @param Current position of the pod
 * @param Next checkpoint
 * @return The best thrust value to use
 */
void calculate_thrust(bool& boost, std::vector< Checkpoint > & list, int & lap, Pod CurrPosition, Checkpoint landmark, Checkpoint first_checkpoint){
    
    double thrust = 100;
    int coefficient = 2;
    int safeAngle = 18;
    double constantAngle = 90;

    // Compute best thrust to use
    if (abs(landmark.angle) > safeAngle){
        thrust*= max(min((1 - (abs(landmark.angle)/constantAngle)), 1.0), 0.0);
        thrust*= max(min((landmark.dist/(double)(landmark.radius*coefficient)), 1.0), 0.0);
    }

    // Check best moment to boost 
    Checkpoint bestBoost = CheckpointManager(list, lap, landmark, first_checkpoint);

    if (bestBoost.x == landmark.x and landmark.y == bestBoost.y){
        if (boost == true){ 
            if (abs(landmark.angle) <= 1){
                cout << landmark.x << " " << landmark.y << " " << "BOOST" << endl;
                boost = false;
                cerr << "BOOST" << endl;
                return;
            }
        }
    }

    cout << landmark.x << " " << landmark.y << " " << int(thrust) << endl;

    return ;
}


int main()
{
    bool game_started = false;      // keep track if the game has just started
    bool boost = true;              // keep track if boost is available
    int lap = 0;                    // keep track of the number of laps

    std::vector< Checkpoint > list; // list of checkpoints

    Checkpoint first_checkpoint;   

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

        // update checkpoint
        Checkpoint nextLandmark;
        nextLandmark.x=next_checkpoint_x;
        nextLandmark.y=next_checkpoint_y;
        nextLandmark.dist = next_checkpoint_dist;
        nextLandmark.angle = next_checkpoint_angle;

        // Update pod's position
        Pod CurrPosition;
        CurrPosition.x = x;
        CurrPosition.y = y;

        // save first checkpoint at first iteraction of the game
        if (!game_started){
            game_started = true;
            first_checkpoint = nextLandmark;
            list.push_back(first_checkpoint);
        }

        // Move the pod
        calculate_thrust(boost, list, lap, CurrPosition, nextLandmark, first_checkpoint);
    }
}
