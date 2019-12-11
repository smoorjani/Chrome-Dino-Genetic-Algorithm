 - **11/16/19** Cloned repo and set up project with openFrameworks

 - **11/17/19** Created basic objects like dino and obstacle
	- Started basic physics engine and collision detection
	- Created hitboxes for the characters along with getters/setters for characteristics

 - **11/18/19** Finished basic game functionality like jumping and moving obstacles
	- Need to make obstacle generation random and such that the game is winnable 

 - **11/20/19** Included genetic algorithms library after downloading
	- Made a basic GA model (not working just yet) as a proof of concept

 - **11/21/19** Refactored the project to work with images instead of basic rectangles

 - **11/22/19** Fine-tuned game mechanics
	- Restructured hitboxes to make the game easier to play
	- Changed a few constants to make gameplay identical to the actual game

 - **11/24/19** Fixed GA model
	- Went through algorithm and found few coding errors

 - **11/25/19** Created basic foundation for GA in final project
	- Created individual and population classes
	- Basic constructors and functionality (getters/setters)
	- Made design choice to not use the GA library due to optimization functions overcomplicating the problem
		- Should replace with data visualization library (track score over time)?
		- Also include sound library for gameplay

 - **11/26/19** Finished implementing helper functions and adjusting constants
	- Changed proof-of-concept model's binary approach to genes to a float between -5 and 5
	- Adjusted gene length and came up with input values
	- Considering adding a random bias to the equation
	- Note that the optimization function could be used to determine a time to jump
		- i.e. 10 pixels before the cactus, jump
		- find a way to optimize the linear equation (6 variables)
		- problem is that this may only provide one acceptable solution (one absolute maximum)

 - **11/30/19** Implemented crossover, mutation, and selection functions
	- Crossover for reproducing desireable children with traits from both parents
	- Mutation for random genetic changes
	- Selection to find best individual

 - **12/1/19** Unit tested dinosaur/obstacle classes
	- Assumed getters and setters work as intended
	- Ensure all other functionality works
	- Have to find an acceptable way to test the update() function for both
	- Catch2 having problems being integrated?

 - **12/2/19** Integrated genetic algorithm into the program
	- Had dino run through multiple generations
	- Reset dinos when all are dead and replay game with new generation
	- Will try to output data to a csv file (generation, individual genes)
	- Possible problem with selection and crossover?

 - **12/5/19** Worked on implementing matplotlib for C++ data visualization / Created Menu
	- Having problems with Python.h files
	- Made a menu to choose between playing against the AI and training the AI
	- Have yet to isolate fittest for the playing against AI option

 - **12/6/19** Implemented a menu for the game that allows for the player to choose between training or playing against AI
	- Have yet to make the Player vs. AI option work against a trained AI
	- Changed visualization to include all dino's in the population rather than just the fittest

 - **12/7/19** Added sound as an external library
	- Cleaned code in ofApp by breaking up the draw function into little pieces
	- Added a threshold for the dino's decisin to jump in order to limit the problem of unnecessary jumping

 - **12/8/19** Tweaked fitness formula to use successful jumps instead of the score
	- The fitness formula penalizes unnecessary jumps and also still incorporates the score as a factor
	- Included a write to CSV method to save data from previous training sessions
	- Created a way to recover the best model from before
	- Added display functionality for the genetic algorithm info (generation, genes)

 - **12/9/19** Implemented data visualization library (ofxGraph) to show fitness score
	- Started testing the genetics and output methods

 - **12/10/19** Cleaned and refactored code to make it more efficient and readable
	- Commented through all code explaining confusing areas
	- Continued unit testing functionality

 - **12/11/19** Finished testing all functionality in the program
	- Fixed problem with save prompt for graph always popping up




