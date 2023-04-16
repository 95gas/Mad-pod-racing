# Mad-pod-racing
The code presented here is my attempt to get the highest possible rank in the game Coders Strike Back. This code let you achieve the bronze league. 

## Results
Current rank: Bronze 32,115 / 41,906

## Strategy
I implemented the following strategy:
- Boost manager. We are using a function for computing the best moment in terms of checkpoint position when to boost the pod. The boost manager collects the position of all the chekcpoints during the first lap, then at the second lap, it computes the one that is further from the previous one. This would be the best moment when to enable boost. 

- Thrust manager. We implemet a function for managing the thrust based on the distance and the angle between the pod and the checkpoint. The closer a pod is to a checkpoint the lower its thrust is going to be. Moreover, the more the position of the checkpoint is disaligned to the orientation of the pod, the slower the thrust is. This let the pod run a smoother path reducing a bit the drifting of the pod when it turns. 

## Possible improvements
To improve the current solution, it can be implemented a drift manager to get a smoother path. In particular, when two checkpoints are aligned along the same path, the pod could go directly to the second checkpoint passing through the first checkpoint. This would allow to speed up the run since the pod would not slow down when approaching the first checkpoint.

