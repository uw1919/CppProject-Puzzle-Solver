//
// File: $Id: solve.h,v 1.0 2014/12/12 02:30:00  $
// Author  : uw1919 (Uday Wadhone)
// Finale 1.0
// Final version of the revised clock problem
// Description: Defines the revised clock problem and solves it
// Revisions:


#include <queue>
#include <map>
#include <vector>
#include <list>
#include <iostream>
#include <cstdlib>
#include "solve.h" //Including the solver framework

using namespace std;

/* Name: ClockProblem
 *
 * Description: Defines the clock problem taking input from the user
 *
 */
class ClockProblem : public Puzzle<int>
{
    //variable to define the total number of hours on the clock
    int totalHours;
    //variables for the current time and the target time on the clock
    int initial, target;
    //vector to take in arguments for increments from the user
    vector<int> temp;
public:
    /* Name: Constructor
     * @param	int     number of hours on the clock
     * @param	int     current time on the clock
     * @param	int     target time required on the clock
     */
    ClockProblem(int totalHours, int initial, int target,vector<int> temp)
    : Puzzle(), totalHours(totalHours), initial(initial), target(target) ,temp(temp){}
    
    
    /* Name: getStartConfiguration
     *
     * Description:	Get the starting configuration of the problem to solve it
     *
     * @returns     int     returns the current time input by the user
     *
     */
    int getStartConfiguration()
    {
        return initial;
    }
    
    /* Name: getPossibleConfigurations
     *
     * Description:	Get all the possible configurations that can be reache from the current time
     *              using the vector of increments provided by the user
     *
     * @param       int         current time input by the user
     *
     * @returns     vector<T>   all configurations  that can be reached from current time
     */
    vector<int> getPossibleConfigurations(int configuration)
    {
        // will contain the result from trying all possibilities
        vector<int> outcome;
        // condition to prevent the possible configuration to be bigger than
        // the total number of hours
        configuration = configuration % totalHours;
        
        for(int i=0;i<temp.size();++i)
        {
            
            int before= configuration + temp[i];
            
            if(before <= 0)
            {
                before= before % totalHours;
                before = before + totalHours;
            }
            if(before == 0)
            {
                before = before + totalHours;
            }
            if(before > totalHours)
            {
                
                before = before %totalHours;
            }
            //cout<< back;
            outcome.push_back(before);
        }
        
        
        return outcome;
    }
    
    /* Name: solutionFound
     *
     * Description:	Function to check if a solution for the given problem is found
     *
     * @param       int     the configuration that we are presently considering
     *
     * @returns     boolean indicates if solution has been found or not
     */
    bool solutionFound(int configuration)
    {
        //compares if configuration matches target time
        return configuration == target;
    }
    
    /* Name: print
     *
     * Description:	Print intermediate configurations on to the screen
     *
     * @param       int     current configuration that we need to display
     *
     */
    void print(const int  & configuration, ostream & ostr)
    {
        ostr << configuration << " ";
    }
};

// number of arguments required for the problem definition
const int numberOfArgumentsRequired( 4 );
// define index of the total number of hours
const int hoursArgument( 1 );
// define index of current time on the clock
const int currentClockArgument( 2 );
// define index of the target time on the clock
const int targetClockArgument( 3 );

int main(int argc, char const *argv[])
{
    //total number of hours on the clock
    int totalNoOfHours = atoi( argv[hoursArgument] );
    //initial configuration of the clock
    int initClockConfig = atoi( argv[currentClockArgument] );
    // target configuration of the clock
    int targetClockConfig = atoi( argv[targetClockArgument] );
    int time = 4;
        vector<int> temp;
    for(int i= time ; i< argc; ++i)
    {
        temp.push_back(atoi(argv[i]));
    }
    ClockProblem puzzle(totalNoOfHours, initClockConfig, targetClockConfig,temp);
    
    list<int> sequenceOfSteps = compute( puzzle );
    if ( !sequenceOfSteps.empty() )
    {
        // print out intermediate steps to the solution
        list<int>::iterator i = sequenceOfSteps.begin();
        for (; i != sequenceOfSteps.end(); ++i)
        {
            puzzle.print( *i, cout );
        }
        
        cout << endl;
    }
    else
    {
        cout << "No solutions exists" << endl;
    }
    
    
    return 0;
}