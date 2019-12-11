/*
Instructions:

	To run the game:
		- Uncomment the top block of code.
		- Comment bottom block of code
		- Remove all tests from the project
		- Move all tests to test folder

	To run the tests:
		- Comment top block of code
		- Uncomment bottom block of code
		- Add all tests back into project
		- Move all tests outside of test folder

*/

//========================================================================= 

#include "ofMain.h"
#include "ofApp.h"

int main() {
	ofSetupOpenGL(1024, 768, OF_WINDOW);
	ofSetFrameRate(60);
	ofRunApp(new ofApp());
}

//========================================================================= 

/*
#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#include "C:\Users\smoor\source\repos\CS126FA19\fantastic-final\fantastic-final\catch.hpp"

#include "../ofApp.h"
#include "../ofMain.h"
*/