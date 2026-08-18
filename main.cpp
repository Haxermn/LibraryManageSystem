#include "LibraryUser.h"

int main()
{
	LibraryUser User;
	LinkedLibraryList<Book> LibraryList = LinkedLibraryList<Book>();
	std::cout << "Initializing Books" << std::endl;
	LibraryList.LibraryManagementInitialize(LibraryList);
	User.ClearScreen();
	User.CommandInformation();

	while (User.endProgram)
	{
		User.InputCommand(LibraryList);
	}

	return 0;
}