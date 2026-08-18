#pragma once
#include "LibraryManagementCore.h"

class LibraryUser //A class to store functions and exit program bool
{
public:
	bool endProgram;

	LibraryUser()
	{
		endProgram = true;
	}
	void CommandInformation(); //Prints out all the commands available

	void ErrorInformation(); //Prints out all the possible errors

	void ShowGenres(); //Prints out all the possible genres

	void InputCommand(LinkedLibraryList<Book>& mainList); //The main loop function to enter commands

	void ClearScreen(); //Clears the console

	bool ExitProgram(); //Ends the program

};