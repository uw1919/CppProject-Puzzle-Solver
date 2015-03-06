//
// File: $Id: solve.h,v 1.0 2014/11/29 12:30:00  $
// Author  : uw1919 (Uday Wadhone) 
// Finale 1.0
// Final version of header framework
// Description: Implements the solver for clock, water, and lloyd puzzles
// Revisions:


//Including the desired libraries
#include <queue>
#include <map>
#include <vector>
#include <list>
#include <iostream>

using namespace std;

/* Name: Puzzle
 * 
 * Description: A template class that is used to represent the water,clock, or lloyd problem
 *              and solve it using the algorithm provided
 */
template<class T>
class Puzzle
{

public:
    //starting configuration of the problem
	T startConfiguration;
	
	/* Name: Constructor
	 * @param	T start     it is the starting configuration of the problem;
	 */
	Puzzle(T start) :
    startConfiguration(start){}

	/* Name: getPossibleConfigurations
	 *
	 * Description:	get all the configurations that can be reached from 
	 * 				a given configuration
	 * @param       T configuration         it is the current configuration of the problem
     *                                      we have
	 * @returns     vector<T>               returns vector of all possible configurations from 
     *                                      current configuration
	 */
	virtual vector<T> getPossibleConfigurations(T configuration) = 0;


	 /* Name: solutionFound
	 *
	 * Description:	checks if the target configuration is achieved using the current possible 
     *              configuration
	 * @param       T configuration         the current configuration that we are testing
     *
	 * @returns     boolean value indicating if target configuration is reached
	 */	
	virtual bool solutionFound(T configuration) = 0;

	/* Name: print
	 *
	 * Description: Prints the current configuration on the screen
     * @param       T configuration         the current configuration that we want to print
     *                                      on screen
	 */	
	virtual void print(T configuration) = 0;
};


/* Name: compute
 * 
 * Description: Template of the function that will use breadth first implementation to go 
 *              through all possible configurations and find the solution
 * @param       Puzzle is the problem we are working on right now
 *
 * @returns     sequence    the sequence of steps which will help solve the problem
 *
 */
 template <class T>
list<T> compute(Puzzle<T>  & puzzle)
{
	// The steps to reach the goal of the particular problem
	list<T> sequenceOfSteps;
    //a queue to hold all possible configurations
	queue<T> possibleConfigurationsQueue;
	// a queue to hold configurations that we have already checked
	map<T, T> checkedConfigurations;
    //the target configuration
	T target;

	// Queue the starting configuration in possibleConfigurations queue
	possibleConfigurationsQueue.push( puzzle.startConfiguration );
	// put the start configuration in checkedConfigurations queue
	checkedConfigurations[ puzzle.startConfiguration ] = puzzle.startConfiguration;

	while( !possibleConfigurationsQueue.empty() &&
		    !puzzle.solutionFound( target = possibleConfigurationsQueue.front() ) )
	{
		// select the configuration from the queue
		T configuration = possibleConfigurationsQueue.front();
		possibleConfigurationsQueue.pop();

		//Obtain the next possible configurations
        vector<T> nextConfiguration = puzzle.getPossibleConfigurations( configuration );
		
		for (int i = 0; i < nextConfiguration.size(); ++i)
		{
			bool isTheNextConfigurationChecked = checkedConfigurations.find(nextConfiguration[i]) !=
											   checkedConfigurations.end();
			if (!isTheNextConfigurationChecked)
			{
				// queue the next configuration
				possibleConfigurationsQueue.push(nextConfiguration[i]);
				// mark configurations as checked
				checkedConfigurations[ nextConfiguration[i] ] = configuration;
			}
		}
	}

	
   /*
	*	Inserts the correct sequence of steps if a solution has been found
    *
	*/
	if ( puzzle.solutionFound( target ) )
	{
		T configuration = target;
		while( configuration != puzzle.startConfiguration )
		{
			sequenceOfSteps.push_front(configuration);
			configuration = checkedConfigurations[configuration];
		}
		sequenceOfSteps.push_front(puzzle.startConfiguration);
	}
	
	return sequenceOfSteps;
}

