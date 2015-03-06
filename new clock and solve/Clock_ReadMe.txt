===============================================================================
File : newclock.cpp
Author's  : uw1919 (Uday Wadhone)
===============================================================================
The program provides the solution to winding a clock forward or backward when 
the current and actual time is provided. The program receives the input as
n Hours on the dial , Actual Time on the Clock and Current Time on the Clock,
and the increments that the program can use to reach the solution
 The clock puzzle implements the Puzzle class and implements that below methods
1. To initialize the Initial Configuration which intializes the 
   Dial on the clock, Actual Time, Current Time on the clock.
2. Check if the given time matches the Current Configuration.
3. GenerateNextSteps generates the next sequences for the current time.
	For example  : Consider a 12 hour clock.
	Current Time : 4 
	Actual/True Time : 7 
	Increments provided by user : 4,1,3.
	Below are the sequences been generated
		
		Current Time : 4 
		Winding Clock Forward by 4 : 8
		Winding Clock Backward by 1 : 7
	
4. The program accepts input and output in the below combinations
		./water 12 4 7 4 1 3
		where 4 is the Current Time
			  7 is the True Time
				and 4,1,3 are the increments the program can use
				to reach the solution.