===============================================================================
File : solve.h
Author's  : uw1919 (Uday Wadhone)
===============================================================================
The program provides the template for the abstract class. The Puzzle class in the 
solver file implements a generic solution to solve the puzzles using a BFS approach.
The program implements a standard BFS search which browses through the solution space 
for a particular problem and step by step traverses through the solution space till 
it reaches a goal if its Exists
1. The program implements the below methods
2. Initial Configuration 
    initialize the puzzle class with the intial configuration
3. Solve Method
	The solve method checks if the desired configuration meets the goal or not
	IF it doesnot meet the goal.
	    Push the config to the queue.
		Push the config to the Seen Configuration
		Then generate sequences from the current configuration
		and push them to a queue.
		  Run for every sequence that was generated
		     Pop the first element of the queue and check if it does meet the goal
			 If not add the list of Seen Configuration and 
			 push it back to the end of the queue
		  Repeat till all sequences where checked
	Repeat till Queue is not empty or Goal has not been reached
	
	Once reached the desired goal then traverse the map and 
	generate the sequences that lead to the result.
	
4.  The below are the virtual functions that are implemented in the class  
    that is created from the template.
	//Get the desired list of sequences from the input config
     virtual list<T> GetNextStep(T currentStep)=0;
	 //Check if the solution for the specific problem has been met or not.
     virtual bool IfSolutionMet(T currentStep)=0;
	 //Print the steps for the solution after the goal was reached
     virtual void PrintSteps(T currentStep)=0;

	
