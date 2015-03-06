//
// File: $Id: water.cpp,v 1.0 2014/11/30 13:30:00  $
// Author  : uw1919 (Uday Wadhone)
// Finale 1.0
// Final version of the n Jugs water Problem
// Description: Defines the n jugs water problem


//Including the desired libraries including the solver header file
#include <vector>
#include <list>
#include <cstdlib>
#include <iostream>
#include "solve.h"

using namespace std;

/* Name: Jug
 * 
 * Description: Represents the water jug
 *				for the puzzle of water problem.
 */
struct Jug
{
	int volume;
	int full;

	/* Name: Constructor
	 *
	 * Description:	Create empty jug of desired volume
	 *				
	 * @param       int     volume   Desired volume of jug
	 */
	Jug(int volume)
	: volume(volume), full(0) {}

	/* Name: operator< (less than operator)
	 *
	 * Description:	Checks whether the current jug is smaller in volume than
     *              the other jug. If of the same volume then compares amount of
     *              water filled in it.
	 *				
	 * @param       Jug (second)       Represents the second jug to compare
     *                                 with the current one
	 *
	 * @returns		boolean value to represent if current jug is smaller than the second
	 */
	bool operator<(const Jug & second) const
	{
		return volume < second.volume ||
			   (volume == second.volume &&
			    full < second.full );
	}

	/* Name: operator== (equality operator)
	 *
	 * Description:	Check whether current jug is equal in volume to the second
     *              that is volume and amount of water filled is the same.
	 *				
     * @param       Jug (second)       Represents the second jug to compare
     *                                 with the current one
	 * @returns		boolean value to represent if both jugs are equal
	 */
	bool operator==(const Jug & second) const
	{
		return volume == second.volume &&
			   full == second.full;
	}

	/* Name: Remaining space
	 *
	 * Description:	represents remaining space in the jug
	 *				
	 * @returns		int     amount of water required to fill remaining space
	 */
	int remainingSpace()
	{
		return volume - full;
	}

	 // Prints representation on the screen for the jug
	 friend ostream& operator<<(ostream & s, const Jug & jug)
	{
		// [ Water Filled in Jug / Total Volume of the Jug ]
		s << "[" << jug.full << " / " << jug.volume << "]";
		return s;
	}
};


/* Name: WaterProblem
 * 
 * Description: defines the water problem
 *
 */
class WaterProblem : public Puzzle<vector<Jug> >
{
	//Creates initial configuration of the problem where jugs are initialised
    //and are empty at the start
	vector<Jug> setupStartConfiguration( vector<int> volumes )
	{
		vector<Jug> startConf;
		for (int i = 0; i < volumes.size(); ++i)
		{
			startConf.push_back( Jug( volumes[i] ) );
		}
		return startConf;
	}

	int requiredWater;


public:
	WaterProblem(int requiredWater, vector<int> volumes)
	:Puzzle( setupStartConfiguration( volumes ) ), requiredWater(requiredWater) {}

	/* Name: getPossibleConfigurations
	 *
	 * Description:	Override function in the header tailored to water problem. It gives all
     *              possible configurations that can be reached from the current configuration.
	 *				
	 * @param       vector<vector<Jug> > configuration     Represents current amount of water
	 *                                                     in each jug
	 * @returns     vector<vector<Jug> >             all possible configurations the jug
     *                                                     can be after making one adjustment
	 */
	 vector<vector<Jug> > getPossibleConfigurations( vector<Jug> configuration)
	 {
	 	vector<vector<Jug> >  nextConfiguration;

	 	//Fill the jugs one by one
	 	for (int i = 0; i < configuration.size(); ++i)
	 	{	
 			vector<Jug> copy = configuration;
 			copy[i].full = copy[i].volume;
 			if (copy != configuration )
 			{
 				nextConfiguration.push_back( copy );
 			}	
	 	}

	 	//Empty the jugs one by one
	 	for (int i = 0; i < configuration.size(); ++i)
	 	{	
 			vector<Jug> copy = configuration;
 			copy[i].full = 0;
 			if (copy != configuration)
 			{
 				nextConfiguration.push_back( copy );
 			}
	 	}
		
	 	//Transfer water from one jug to another
	 	for (int currentJug = 0; currentJug < configuration.size(); ++currentJug)
	 	{	
	 		for (int destJug = 0; destJug < configuration.size(); ++destJug)
		 	{	
		 		vector<Jug> copy = configuration;
	 			if ( 
	 				currentJug != destJug &&
	 				copy[destJug].remainingSpace() > 0
	 			)
	 			{
	 				int waterToTransfer = min(
	 					copy[currentJug].full,
	 					copy[destJug].remainingSpace()
	 				);

	 				// transfer water from current jug to destination jug
	 				copy[currentJug].full -= waterToTransfer;
	 				copy[destJug].full += waterToTransfer;

	 				if (copy != configuration)
					{
						nextConfiguration.push_back( copy );
					}
	 			}
		 	}
 			
	 	}
		
	 	return nextConfiguration;
	 }

	 /* Name: solutionFound
	 *
	 * Description:	Checks whether the current configuration is the solution to the problem
     *
	 * @param       vector<Jug> configuration     current configuration that we need to check
     *
     * @returns     boolean value representing if the solution is found
	 */	
	 bool solutionFound(vector <Jug> configuration)
	 {
	 	//Solution is reached when at least one jug contains the desired amount of water
	 	for(int i = 0 ; i < configuration.size(); ++i)
	 	{
	 		if( configuration[i].full == requiredWater ) return true;
	 	}
	 	return false;
	 }

	/* Name: print
	 *
	 * Description:	Print the current configuration of jugs on the screen
     *
	 * @param       vector<Jug> configuration     current jugs configuration that we want
     *                                                  to display
	 */	
	 void print(vector <Jug> configuration)
	 {
	 	  cout << "{ ";
	      for(int i = 0; i < configuration.size(); ++i)
	      {
	         cout << configuration[i] << " ";
	      }
	      cout << "}";
	 }
};
// Minimum number of the parameters expected by the program
// taking in consideration the program name
const int numberOfArgumentsRequired( 3 );
// index of the desired amount argument
const int desiredAmountArgument( 1 );
// capacities first argument index
const int givenVolumesArgument( 2 );

int main(int argc, char const *argv[])
{	
	if ( argc < numberOfArgumentsRequired)
 	{
 		cout << "Required arguments are: desired amount, ";
 		cout << "... Jugs capacity" << endl;
 		return -1;
 	}

    int requiredWater = atoi( argv[desiredAmountArgument] );
 	vector<int> volumes;

	for(int i = givenVolumesArgument; i < argc; i++)
	{
		volumes.push_back( atoi( argv[i] ) );
	}

    WaterProblem puzzle(requiredWater, volumes);
    //solving the puzzle using header solve.h
    list<vector<Jug> > sequenceOfSteps = compute(puzzle);

    if ( !sequenceOfSteps.empty() )
	{
		// display the sequence of steps required to get desired amount of water in jug
		cout << "Sequence of Steps : [  Amount in jugs  /  Total Volume of jug  ]" << endl;
		list<vector<Jug> >::iterator it = sequenceOfSteps.begin();
		for(; it != sequenceOfSteps.end(); ++it)
	    {
	    	puzzle.print(*it);
	    	cout << endl;
	    }
		cout << endl;
	}
	else
	{
        //if no solution is found
		cout << "No solutions exists" << endl;
	}

	return 0;
}