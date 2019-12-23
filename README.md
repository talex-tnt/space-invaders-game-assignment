# Space Invaders: C++ Assignment
Create a **Space Invaders** game clone in C++ by using the supplied library `sdl-engine-libs\src\SpaceInvadersEngine`.

![Space Invaders Game Clone](https://github.com/talex-tnt/space-invaders-game-assignment/blob/master/space-invaders.gif)





## **Game Design Document**



- ## Main Actors

  * ### *The Ship*
    It is controlled by the player; located at the bottom of the screen it can only move horizontally within the screen limits. 
    The ship can shoot rockets and can get hit by alien's bombs;
    a life is lost each time, the life counter decreases.

  * ### *Rockets*
    They are shoot by the ship and move vertically to the top of the screen.
    They can destroy aliens if hit but they'll get destroyed as well.

  * ### *Aliens fleet*
    A fleet of aliens appears at the top of the screen; it moves left to right until the rightmost alien reaches the screen edge. It then moves down a little and then starts moving back to the right edge. Once the right edge is reached, it goes downward again; then left and so forth until the **bottom edge of the screen is reached** or an **alien collides with the ship**.
    Aliens can drop bombs at random time intervals.

  * ### *Bombs*
    Dropped at random time interval by aliens, they move downward and can only collide with the ship. They get destroyed after hitting the ship and the player life counter is decreased.
    
    

- ## The Game Over
    Whenever the **player's life counter reaches 0**, the game is over.

    It's also game over if an alien reaches the **bottom edge of the screen is reached** or an **collides with the ship**.
    
    


## Additional information

- ### **Target Machine** 
  When designing your code keep in mind that the game is meant to be run on a machine with the following constraints: 

  - Low CPU clock frequency. 
  - Expensive cache misses and branches (branch prediction might not be supported at all).
  - Limited memory budget (virtual memory not available). 
  - Very expensive memory allocations.
  
  Some of these restrictions might be released in the future.

- ### **Further constraints**
  - Exceptions will be disabled; please avoid using `std`'s exception dependent headers.
  - Please avoiding using `std`'` string` and containers; they might not not longer be available in the future.

- ### **Working on the assignment** 
  Set yourself a week (~20 hours) to work on this assignment as you would work on some task given to you in a working environment.
  
  
  Add as many files as you need inside the folder [`space-invaders\SpaceInvaders\code\source\`](https://github.com/talex-tnt/space-invaders-game-assignment/tree/master/SpaceInvaders/code/source). 
  
  Please do not touch any another file.

- ### **Compiling** (Windows)
  Please follow the steps described in the `scripts` folder's [README](https://github.com/talex-tnt/space-invaders-game-assignment/blob/master/scripts/README.md)


