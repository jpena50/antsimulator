
#include "simulator.h"
using namespace std;




int main()
{

    Simulator sim;
    sim.run();

    return EXIT_SUCCESS;


}



/*
////TODO

1) make window resize not affect ant image size and scaling.
   I guess we need to make use of mapPixelToCoords.
2) add levy flight behaviour.
3) add array of ants to simulator
4) update Ant::updateAnim to use constant numbers for sprite sheet length and width
   insead of hard coded numbers.



*/



































