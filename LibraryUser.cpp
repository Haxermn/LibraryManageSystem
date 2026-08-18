#include <Windows.h> //Added soley for clearing console window for testing
#include "LibraryUser.h"

void LibraryUser::CommandInformation() //Provides information for all possible commands
{
	std::cout << "Available commands are as follow:" << std::endl;
	std::cout << "Type 'AddBook' - Add a book to the library list" << std::endl;
	std::cout << "Type 'RemoveBook' - Remove a book from the library list" << std::endl;
	std::cout << "Type 'ShowInventory' - Lists all books in the library list" << std::endl;
	std::cout << "Type 'CheckBook' - Check out a book from library list if available" << std::endl;
	std::cout << "Type 'ReturnBook' - Return a book to the library list if checked out" << std::endl;
	std::cout << "Type 'SearchBook' - Search the library list for a book by its ID" << std::endl;
	std::cout << "Type 'CommandInformation' - Lists available commands" << std::endl;
	std::cout << "Type 'ErrorInformation' - Lists error codes" << std::endl;
	std::cout << "Type 'ShowGenres' - Lists possible genres" << std::endl;
	std::cout << "Type 'ClearScreen' - Clear the console screen" << std::endl;
	std::cout << "Type 'ExitProgram' - Exits the program" << std::endl;
}

void LibraryUser::ErrorInformation() //Provides information on errors that could appear
{
	std::cout << "Following possible error codes:" << std::endl;
	std::cout << "Error code 101: 'RemoveBook' command failed, invalid ID was entered or library list empty" << std::endl;
	std::cout << "Error code 102: 'CheckBook' command failed, invalid ID, Title, or Category was entered or library list empty" << std::endl;
	std::cout << "Error code 103: 'CheckBook' command failed, the entered book is already borrowed" << std::endl;
	std::cout << "Error code 104: 'ReturnBook' command failed, invalid ID, Title, or Category was entered or library list empty" << std::endl;
	std::cout << "Error code 105: 'ReturnBook' command failed, the entered book is already available" << std::endl;
	std::cout << "Error code 106: entered command failed, the command does not exist" << std::endl;
}

void LibraryUser::ShowGenres()
{
	std::cout << "The following are possibles genres:" << std::endl;
	std::cout << "Science" << std::endl;
	std::cout << "History" << std::endl;
	std::cout << "Fiction" << std::endl;
	std::cout << "Psychology" << std::endl;
	std::cout << "Technology" << std::endl;
}

void LibraryUser::InputCommand(LinkedLibraryList<Book>& mainList) //Takes a linked library of books then reads input string to determine commands
{
	
	std::string commandInput;
	std::string commandLower;
	//std::cin.ignore();
	//std::cin.get();
	std::cin.clear();
	std::getline(std::cin, commandLower);
	std::cout << " " << std::endl;


	for (char c : commandLower)
	{
		commandInput += tolower(static_cast<int>(c));
	}

	if (commandInput.compare("addbook") == 0 || commandInput.compare("add book") == 0) //User input to add books based on their characteristics
	{
		int enterPublished;
		std::string enterTitle;
		std::string enterAuthor;
		std::string enterCategory;
		std::string enterAvailability;
		Availability enterAvailable;
		Category enterGenre;

		//Following is User Input
		std::cout << "Enter the year published" << std::endl;
		std::cin >> enterPublished;

		if (enterPublished == 0)
		{
			std::cout << "Invalid year entered, exiting command" << std::endl;
			std::cin.clear();
			return;
		}
		std::cout << "Enter the book's title" << std::endl;
		std::cin.ignore();
		std::getline(std::cin,enterTitle);
		std::cout << "Enter the book's author" << std::endl;
		std::getline(std::cin, enterAuthor);
		std::cout << "Enter the book's genre" << std::endl;
		std::cin >> enterCategory;
		//std::cout << "Enter the book's status" << std::endl;
		//std::cin >> enterAvailability;
		std::cout << " " << std::endl;

		//Determines if a correct status and genre was entered to avoid incompatible entries
		if (enterCategory.compare("Science") == 0) enterGenre = Science;
		else if (enterCategory.compare("History") == 0) enterGenre = History;
		else if (enterCategory.compare("Fiction") == 0) enterGenre = Fiction;
		else if (enterCategory.compare("Psychology") == 0) enterGenre = Psychology;
		else if (enterCategory.compare("Technology") == 0) enterGenre = Technology;
		else {
			std::cout << "Invalid genre entered, exiting command" << std::endl;
			return;
		}


		mainList.AddBook(enterPublished,enterTitle,enterAuthor,Available,enterGenre);
		
		std::cout << "The book has been successfully added to the library list" << std::endl;
	}
	else if (commandInput.compare("showgenres") == 0 || commandInput.compare("show genres") == 0)
	{
		ShowGenres();
	}
	else if (commandInput.compare("removebook") == 0 || commandInput.compare("remove book") == 0) //Removes a book from the list
	{
		mainList.RemoveBook();
		std::cout << "The book has been removed" << std::endl;
	}
	else if (commandInput.compare("showinventory") == 0 || commandInput.compare("show inventory") == 0) //Prints all the information for each book in the linked list
	{
		mainList.ShowInventory();
	}
	else if (commandInput.compare("checkbook") == 0 || commandInput.compare("check book") == 0) //Checks out a book if available, setting its status to borrowed
	{
		mainList.BorrowBook();
	}
	else if (commandInput.compare("returnbook") == 0 || commandInput.compare("return book") == 0) //Returns a book if borrowed, setting its status to available
	{
		mainList.ReturnBook();
	}
	else if (commandInput.compare("searchbook") == 0 || commandInput.compare("search book") == 0) //Searches for a book based on user entered ID
	{
		int ID;

		std::cout << "Enter the book's ID" << std::endl;
		std::cin >> ID;
		std::cout << " " << std::endl;

		//Error handling, if the book ID
		try {
			mainList.current = mainList.SearchForBook(ID);
			if (mainList.current == nullptr)
			{
				throw 107;
			}
		}
		catch (int error)
		{
			std::cout << "Invalid ID entered error: " << error << std::endl;
			return;
		}

		mainList.current = mainList.SearchForBook(ID);
		std::cout << "Book found:" << std::endl;
		std::cout << mainList.current->element << std::endl;

	}
	else if (commandInput.compare("commandinformation") == 0 || commandInput.compare("command information") == 0) //Command to print out information about the commands
	{
		CommandInformation();
	}
	else if (commandInput.compare("errorinformation") == 0 || commandInput.compare("error information") == 0) //Command to print out information about the errors
	{
		ErrorInformation();
	}
	else if (commandInput.compare("clearscreen") == 0 || commandInput.compare("clear screen") == 0) //Clears the console of text
	{
		ClearScreen();
	}
	else if (commandInput.compare("exitprogram") == 0 || commandInput.compare("exit program") == 0) //Ends the main loop to exit program
	{
		endProgram = ExitProgram();
	}
	else if (commandInput.compare("") == 0)
	{
		return;
	}
	else
	{
		std::cout << "The command entered is not a command error: 106" << std::endl; //Informs of a wrong command
		std::cout << "Type 'CommandInformation' to see command options" << std::endl;
	}

}

void LibraryUser::ClearScreen()
{
	system("cls"); //The only use of the windows header
}

bool LibraryUser::ExitProgram()
{
	return false;
}
