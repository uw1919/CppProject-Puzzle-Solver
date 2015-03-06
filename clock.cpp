//
// File: $Id: clock.cpp,v 1.0 2014/11/29 14:30:00  $
// Author  : uw1919 (Uday Wadhone)
// Finale 1.0
// Final version of the clock Problem
// Description: Defines the clock problem by taking input from the user

//Including the desired libraries including the solver header file
#include <queue>
#include <map>
#include <vector>
#include <list>
#include <iostream>
#include <cstdlib>
#include "solve.h" //Including the header file

using namespace std;

/* Name: ClockProblem
 * 
 * Description: Puzzle class implementation.
 * Represents the puzzle clock problem.
 */
class ClockProblem : public Puzzle<int>
{
    //total number of hours on the clock
	int totalHours;
    //target time to show on the clock
	int target;
public:
	/* Name: Constructor
	 * @param    int    totalHours       total number of hours on the clock
	 * @param    int    initial           current time on the clock
	 * @param    int    target           the actual time that we have to correct to
	 */
	ClockProblem(int totalHours, int initial, int target)
	: Puzzle(initial), totalHours(totalHours), target(target) {}

	/* Name: getPossibleConfigurations
	 *
	 * Description:	Override the function in header. This will obtain all possible 
     *              configurations the clock hand can obtain by moving forward or
     *              backward on the clock
     *
	 * @param       int     configuration      Represents present configuration of
     *                                         of the clock
     *
	 * @returns     vector<T>                  All possible configurations from
     *                                         current configuration
     *
	 */
	vector<int> getPossibleConfigurations(int configuration)
	{
		// represent hours that are followed by current configuration of the clock
		vector<int> outcome;
		// ensure the current configuration hour is not bigger than the
        // biggest number on the clock
		configuration = configuration % totalHours;
		
		// get the hour before and after the current configuration of the clock
	    int before = configuration - 1;
	    int after = configuration + 1;
	    
	    // ensure that the hour is 0 when going to negative values while
        // moving backward
	    if( before <= 0 )
	    {
	    	before = before + totalHours;
	    }

	    // ensure that the hour is 0 when moving forward
        if (after == 0)
	    {
	    	after = after + totalHours;
	    }

	    // Save the before and after values found
		outcome.push_back( before );
	    outcome.push_back( after );

		return outcome;
	}

	/* Name: solutionFound
	 *
	 * Description:	Override function in header file to check if the solution is found
     *
	 * @param      int      configuration   it is the current configuration we are
     *                                      looking at
	 *
	 * @returns    boolean value to indicate if solution is found
	 */	
	 bool solutionFound(int configuration)
	{
		return configuration == target;
	}

	/* Name: print
	 *
	 * Description:	Override print method to display current hour of solution on screen
	 * @param       int     configuration   current configuration hour we want to 
     *                                      print on the screen
	 *
	 */	
	void print( int configuration )
	{
		std::cout << configuration << " ";
	}
};

//number of arguments required for defintion of problem
const int numberOfArgumentsRequired( 4 );

// argument representing total number of hours on clock
const int hoursArgument( 1 );
// argument representing current configuration of clock
const int currentClockArgument( 2 );
// argument representing target configuration of clock
const int targetClockArgument( 3 );

int main(int argc, char const *argv[])
{
 	if ( argc != numberOfArgumentsRequired)
 	{
 		cout << "3 arguments expected: number of hours on dial, ";
 		cout << "current clock time, target time" << endl;
 		return -1;
 	}

    // Total number of hours on the clock
 	int totalNoOfHours = atoi( argv[hoursArgument] );
    // Initial clock configuration
 	int initClockConfig = atoi( argv[currentClockArgument] );
    // Target clock configuration
 	int targetClockConfig = atoi( argv[targetClockArgument] );
 
 	ClockProblem puzzle(totalNoOfHours, initClockConfig, targetClockConfig);
 
	list<int> sequenceOfSteps = compute( puzzle );
	if ( !sequenceOfSteps.empty() )
	{
		// Displaying the sequence of configurations that lead to the goal
		for (list<int>::iterator i = sequenceOfSteps.begin(); i != sequenceOfSteps.end(); ++i)
		{
			puzzle.print( *i );
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