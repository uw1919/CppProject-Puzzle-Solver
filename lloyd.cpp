// File: $Id: llyod.cpp v 1.0 2014/11/30 13:30:00  $
//
// Author  : uw1919 (Uday Wadhone)
// Finale 1.0
// Final version of the LLyods Problem
// Description: Simulates the Sam Llyods Puzzle and provides a solution 
// when the initial and final configuration is passed.
// classes and functions

//Including the desired libraries including the solver header file
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "solve.h"
#include <string>

using namespace std;

/* Name: LloydProblem
 * 
 * Description: Implements the Puzzle class 
 * Represents the Llyods Puzzle 
 */
class LloydProblem : public Puzzle<string>
{
	//Width and Height of the Llyods Box
	int width, height; 
	string target; //Final Configuratiopn
	ostream & os; // Output stream to write the output to the file 
public:
	//Constructor To Initialize the Puzzle class with the Initial Configuration
	/* Name: Constructor
	 * Arguments:	width : Width of the box
	 *				height : height of the box
	 *				initial : initial configuration
	 				target : final configuration
	 				ostream os : Output Stream to write the file				
	 */
	LloydProblem( int width, int height, string initial, string target, ostream &os)
	: Puzzle(initial), width(width), height(height), target(target), os(os)
	{

	}
	

	/* Name: getPossibleConfigurations
	 *
	 * Description:	get all the configurations that can be reached from 
	 * 				a given configuration. In this case will be the 
	 				configuration that can be obtained by moving the 
	 				blocks besides '.' whitespaced block. 
	 				
	 * Arguments:	string configuration which is the llyods blocks in a 
	 				string pattern
	 * Returns:	    vector<T> all the possible combinations by moving the 
	 				'.' whitespace block left, right , up and down.
	 */
	vector<string> getPossibleConfigurations(string configuration)
	{
		std::vector<string> configurations;
		
		for (int row = 0; row < height; ++row)	
		{
			for (int column = 0; column < width; ++column)
			{
				int place = row * width + column;
				if( configuration[place] == '.')
				{
					//Move the block one Step Left 
					if( (row - 1) >=  0)
					{
						string clone = configuration;
						int adjPlace = (row - 1) * width + column;
						swap(clone[adjPlace], clone[place]);
						configurations.push_back(clone);
				    }
				    //Move the block one Step Right 
				    if( (row + 1) <  height)
				    {
				    	string clone = configuration;
				    	int adjPlace = (row + 1) * width + column;
						swap(clone[adjPlace], clone[place]);
						configurations.push_back(clone);
				    }
				    //Move the block Up
				    if( (column + 1) <  width)
				    {
				    	string clone = configuration;
				    	int adjPlace = row  * width + (column + 1);
						swap(clone[adjPlace], clone[place]);
						configurations.push_back(clone);
				    }
				    //Move the block Down
				    if( (column - 1) >=  0)
				    {
                    	string clone = configuration;
				    	int adjPlace = row  * width + (column - 1);
						swap(clone[adjPlace], clone[place]);
						configurations.push_back(clone);
				    }

				}
				
			}

			
		}

		return configurations;
	}

	/* Name: solutionFound
	 *
	 * Description:	checks whether or not the passed configuration meets the goal
	 * 				of the puzzle
	 * Arguments:	string configuration is the current pattern
	 *    			that we want to check if meets the goal 
	 * Returns: a boolean indicating if the goal has been met or not
	 */
	bool solutionFound(string configuration)
	{
		return configuration == target;
	}
	

	/* Name: print
	 *
	 * Description:	display a configuration (state of the box) out on the screen
	 * Arguments:	string configuration (state of the box) is the configuration 
	 *				we want to 	display
	 */	
	void print(string configuration)
	{
		
		for (int row = 0; row < height; ++row)
		{
			for (int column = 0; column < width; ++column)
			{
				//Output the configuaration To Screen/File
				int place = row * width + column;
				os << configuration[place] << " ";
			}
			os << endl;
		}
		os << endl;
	}
};

//Constants to shore the value of input arguments
const char hyphen( '-' );
const char nullchar( '\0' );


int main(int argc, char const *argv[])
{
	//If Invalid argumentts
	if (argc != 3)
	{
		cerr << "Please use two arguments only" << endl;
    } 
    //Get Input is STD OUT or a File
    //Get Output is STD OUT or a File
    else 
    {
    	istream * istr;
    	ifstream ifstr;
    	ostream *ostr;
    	ofstream ofstr;


    	if( argv[1][0] == hyphen &&
    	    argv[1][1]== nullchar )
    	{
    		istr = &cin;
    	} 
    	else 
    	{
    		ifstr.open( argv[1] );
    		istr = &ifstr;
    	}

    	istream &is = *istr;

    	if( argv[2][0] == hyphen &&
    	    argv[2][1] == nullchar )
    	{
    		ostr = &cout;
    	} 
    	else 
    	{
    		ofstr.open( argv[2] );
    		ostr = &ofstr;
    	}

    	ostream &os = *ostr;



    	int  width, height;
    	is >> width >> height ;

    	string outcome;
    	string tmpstr;
    	
    	while (is >> tmpstr)
    	{
    		outcome += tmpstr;
    	}

    	//Store Initial Config
    	string initial = outcome.substr( 0, width * height );
    	//Store Final Config 
    	string target = outcome.substr( width * height, width * height );

    	//Initialize the Constructor with the width, height and 
    	//initial and final config
    	LloydProblem puzzle (width, height, initial, target, os);
    	//Sequence to store results that lead to the solution
    	list<string> sequenceOfSteps = compute(puzzle);

    	//Display the results of the solution
    	for (list<string>::iterator it = sequenceOfSteps.begin(); it != sequenceOfSteps.end(); ++it)
    	{
    		puzzle.print(*it);
    	}

    	// cout << start << endl;
    	// cout << final << endl;

    }
	
	return 0;
}