#include "LibraryManagementCore.h"

template class LinkedLibraryList<Book>; //Necessary for linking purposes
template class LinkedLibraryNode<Book>;

template<class T>
inline void LinkedLibraryList<T>::LibraryManagementInitialize(LinkedLibraryList<T>& Initiate) //Populate the list with 30 test books.
{
	Initiate.AddBook(1980,"Cosmos","Carl Sagan", Available, Science);
	Initiate.AddBook(1997,"Guns, Germs, and Steel","Jared Diamond", Available, History);
	Initiate.AddBook(1949,"1984","George Orwell", Borrowed, Fiction);
	Initiate.AddBook(2011, "Thinking, Fast and Slow", "Daniel Kahneman", Available, Psychology);
	Initiate.AddBook(1999, "Code", "Charles Petzold", Borrowed, Technology);
	Initiate.AddBook(1861, "Moby-Dick", "Herman Melville", Available, Fiction);
	Initiate.AddBook(1925, "The Great Gatsby", "F. Scott Fitzgerald", Available, Fiction);
	Initiate.AddBook(1859, "A Tale of Two Cities", "Charles Dickens", Borrowed, Fiction);
	Initiate.AddBook(2015, "The Silk Roads: A New History of the World", "Peter Frankopan", Borrowed, History);
	Initiate.AddBook(1951, "The Catcher in the Rye", "J. D. Salinger", Available, Fiction);
	Initiate.AddBook(1866, "Crime and Punishment", "Fyodor Dostoevsky", Borrowed, Fiction);
	Initiate.AddBook(1960, "To Kill a Mockingbird", "Harper Lee", Borrowed, Fiction);
	Initiate.AddBook(1884, "Adventures of Huckleberry Finn", "Mark Twian", Borrowed, Fiction);
	Initiate.AddBook(1994, "The Hot Zone: A Terrifying True Story", "Richard Preston", Available, History);
	Initiate.AddBook(1899, "Heart of Darkness", "Joseph Conrad", Available, Fiction);
	Initiate.AddBook(1961, "Catch-22", "Joseph Heller", Borrowed, Fiction);
	Initiate.AddBook(1818, "Frankenstein", "Mary Shelley", Borrowed, Fiction);
	Initiate.AddBook(1850, "David Copperfield", "Charles Dickens", Available, Fiction);
	Initiate.AddBook(1945, "Animal Farm", "George Orwell", Borrowed, Fiction);
	Initiate.AddBook(1915, "The Metamorphosis", "Franz Kafka", Borrowed, Fiction);
	Initiate.AddBook(1953, "Fahrenheit 451", "Ray Bradbury", Borrowed, Fiction);
	Initiate.AddBook(2016, "The Underground Railroad", "Colson Whitehead", Available, Fiction);
	Initiate.AddBook(2000, "The Last Samurai", "Helen DeWitt", Available, Fiction);
	Initiate.AddBook(2011, "Ready Player One", "Ernest Cline", Available, Fiction);
	Initiate.AddBook(1965, "Dune", "Frank Herbert", Borrowed, Fiction);
	Initiate.AddBook(1843, "A Christmas Carol", "Charles Dickens", Available, Fiction);
	Initiate.AddBook(2017, "Behave", "Robert Sapolsky", Borrowed, Psychology);
	Initiate.AddBook(2011, "Data Structures and Algorithms in C++", "Michael T. Goodirch, Roberto Tamassia, David M. Mount", Borrowed, Technology);
	Initiate.AddBook(2007, "A Thousand Splendid Suns", "Khaled Hosseini", Available, Fiction);
	Initiate.AddBook(2001, "Life of Pi", "Yann Martel", Borrowed, Fiction);
	Initiate.AddBook(1813, "Pride and Prejudice", "Jane Austen", Borrowed, Fiction);
}

template<class T>
inline void LinkedLibraryList<T>::AddBook(int Published, std::string Title, std::string Author, Availability Status, Category genre)
{
	
	if (head == nullptr) //If head is nullptr, then the list is empty.
	{
		head = new LinkedLibraryNode<T>();
		Book* temp = new Book(listCount, Published, Title, Author, Status, genre);
		head->element = temp;
		head->next = head;
		head->prev = head;
		current = head;
		return;
	}
	else if(head->next == head && head->prev == head) //If head next & prev are equal to itself, then it is the only member in the list
	{
		listCount++;
		LinkedLibraryNode<T>* AdditionalBook = new LinkedLibraryNode<T>();
		Book* temp = new Book(listCount, Published, Title, Author, Status, genre);

		AdditionalBook->element = temp;
		head->next = AdditionalBook;
		head->prev = AdditionalBook;
		AdditionalBook->next = head;
		AdditionalBook->prev = head;
	}
	else //Every case but the first and second added members, are the same
	{
		listCount++;
		LinkedLibraryNode<T>* AdditionalBook = new LinkedLibraryNode<T>();
		Book* temp = new Book(listCount, Published, Title, Author, Status, genre);
		AdditionalBook->element = temp;

		AdditionalBook->next = head;
		AdditionalBook->prev = head->prev;
		head->prev->next = AdditionalBook;
		head->prev = AdditionalBook;
	}
	
}

template<class T>
inline void LinkedLibraryList<T>::RemoveBook()
{

	int searchID;

	std::cout << "Enter the ID of the book" << std::endl;
	std::cin >> searchID;

	LinkedLibraryNode<T>* temp = SearchForBook(searchID); //If search can not find it with the entered ID, throw an error
	try {
		if (temp == nullptr)
		{
			throw 101;
		}
	}
	catch(int error){
		std::cout << "Invalid search parameters entered error:" << error << std::endl;
		return;
	}

	if (temp->next == temp && temp->prev == temp) //If the returned node's next and previous are itself, then it is the last element in the linked list
	{
		delete temp;
		temp = nullptr;
		head = nullptr;
		return;
	}

	if (temp == head) //If the returned node is the head, make sure there is a new head before deleting this node
	{
		head = temp->next;
	}

	if (temp == current) //If the returned node is the current, make sure there is a new current before deleting this node
	{
		current = temp->next;
	}

	temp->next->prev = temp->prev; //Make sure neighboring nodes have new prev and next
	temp->prev->next = temp->next;

	delete temp; //Deletes the node and its element, freeing the memory
}


template<class T>
inline LinkedLibraryNode<T>* LinkedLibraryList<T>::SearchForBook(int ID)
{

	if (current->element->ID < ID) //Possibly shorten iteration time, reduces the amount of cases of iterating the whole linked list
	{
		while (current->next != head) //Iterates until the last element which points to the head
		{
			if (current->element->ID == ID)
			{
				return current;
			}
			else
			{
				current = current->next;
			}
		}
	}
	else
	{
		while (current->prev != head)
		{
			if (current->element->ID == ID)
			{
				return current;
			}
			else
			{
				current = current->prev;
			}
		}
	}

	if (current->element->ID == ID) //Special case if the ID matches the last element's
	{
		return current;
	}

	return 0;
}


template<class T>
inline void LinkedLibraryList<T>::ShowInventory()
{
	//If the temp = head results in a nullptr, then the linked list must be empty, so the program throws an error and exits the function
	try {

		LinkedLibraryNode<T>* temp = head;

		if (temp == nullptr)
		{
			throw 109;
		}
	}
	catch (int error)
	{
		std::cout << "The inventory is empty error: " << error << std::endl;
		return;
	}

	LinkedLibraryNode<T>* temp = head;

	while (temp->next != head) //Print out all elements in the list but the last one
	{
		std::cout << "Entry:" << std::endl;
		std::cout << temp->element << std::endl;
		std::cout << " " << std::endl;
		temp = temp->next;
	}

	std::cout << "Entry:" << std::endl; //Prints out the last element
	std::cout << temp->element << std::endl;
	std::cout << " " << std::endl;
}

template<class T>
inline void LinkedLibraryList<T>::BorrowBook()
{
	int searchID;
	std::string searchTitle;
	std::string searchCategory;
	Category realCategory = Fiction;


	std::cout << "Enter the ID of the book" << std::endl; //User Inputs
	std::cin >> searchID;
	std::cout << "Enter the Title of the book" << std::endl;
	std::cin.ignore();
	std::getline(std::cin, searchTitle);
	std::cout << "Enter the Category of the book" << std::endl;
	std::cin >> searchCategory;
	std::cout << " " << std::endl;

	if (searchCategory.compare("Science") == 0) realCategory = Science;
	if (searchCategory.compare("History") == 0) realCategory = History;
	if (searchCategory.compare("Fiction") == 0) realCategory = Fiction;
	if (searchCategory.compare("Psychology") == 0) realCategory = Psychology;
	if (searchCategory.compare("Technology") == 0) realCategory = Technology;

	//If the search returns a nullptr, then entered information is invalid or the book does not exist
	LinkedLibraryNode<T>* temp = SearchForBook(searchID, searchTitle, realCategory);
	try {
		if (temp == nullptr)
		{
			throw 102;
		}

		if (temp->element->status == Borrowed) //Throw an error if the book is checked out already
		{
			throw 103;
		}

	}
	catch (int error) {

		if(error == 102)
			std::cout << "Invalid search parameters entered error:" << error << std::endl;

		if (error == 103)
			std::cout << "This book is already checked out, error:" << error << std::endl;

		return;
	}

	std::cout << "Your book is available and has been checked out" << std::endl;

	temp->element->status = Borrowed;
}

template<class T>
inline void LinkedLibraryList<T>::ReturnBook()
{
	int searchID;
	std::string searchTitle;
	std::string searchCategory;
	Category realCategory = Fiction;

	std::cout << "Enter the ID of the book" << std::endl; //User Inputs
	std::cin >> searchID;
	std::cout << "Enter the Title of the book" << std::endl;
	std::cin.ignore();
	std::getline(std::cin, searchTitle);
	std::cout << "Enter the Category of the book" << std::endl;
	std::cin >> searchCategory;
	std::cout << " " << std::endl;

	if (searchCategory.c_str() == "Science") realCategory = Science;
	else if (searchCategory.c_str() == "History") realCategory = History;
	else if (searchCategory.c_str() == "Fiction") realCategory = Fiction;
	else if (searchCategory.c_str() == "Psychology") realCategory = Psychology;
	else if (searchCategory.c_str() == "Technology") realCategory = Technology;

	//If the search returns nullptr, then entered information is invalid or the book does not exist
	LinkedLibraryNode<T>* temp = SearchForBook(searchID, searchTitle, realCategory);
	try {
		if (temp == nullptr)
		{
			throw 104;
		}

		if (temp->element->status == Available) //If the book is already available, throw an error and return
		{
			throw 105;
		}

	}
	catch (int error) {
		if(error == 104)
			std::cout << "Invalid search parameters entered error:" << error << std::endl;

		if (error == 105)
			std::cout << "This book is already available, error:" << error << std::endl;

		return;
	}

	std::cout << "This book has been returned" << std::endl;

	temp->element->status = Available;

}

template<class T>
inline LinkedLibraryNode<T>* LinkedLibraryList<T>::SearchForBook(int ID, std::string Title, Category Category)
{

	if (current->element->ID < ID)//Possibly shorten iteration time, reduces the amount of cases of iterating the whole linked list
	{
		while (current->next != head) //Iterates until the last element which points to the head by iterating by next
		{
			if (current->element->ID == ID && current->element->Title == Title && current->element->genre == Category)
			{
				return current;
			}
			else
			{
				current = current->next;
			}
		}
	}
	else
	{
		while (current->prev != head) //Iterates until the last element which points to the head by iterating by prev
		{
			if (current->element->ID == ID && current->element->Title == Title && current->element->genre == Category)
			{
				return current;
			}
			else
			{
				current = current->prev;
			}
		}
	}

	if (current->element->ID == ID && current->element->Title == Title && current->element->genre == Category) //Special case for the last element
	{
		return current;
	}

	return 0;
}


std::ostream& operator<<(std::ostream& os, const Book* obj) //Overload the stream operator to print out all the information for books
{
	
	std::cout << "Book ID: " << obj->ID << std::endl;
	std::cout << "Book Title: " << obj->Title << std::endl;
	std::cout << "Book Author: " << obj->Author << std::endl;
	std::cout << "Book Published: " << obj->Published << std::endl;

	if(obj->genre == 0)
	std::cout << "Book Category: Science" << std::endl;
	if (obj->genre == 1)
		std::cout << "Book Category: History" << std::endl;
	if (obj->genre == 2)
		std::cout << "Book Category: Fiction" << std::endl;
	if (obj->genre == 3)
		std::cout << "Book Category: Psychology" << std::endl;
	if (obj->genre == 4)
		std::cout << "Book Category: Technology" << std::endl;

	if (obj->status == 0)
		std::cout << "Book Status: Available" << std::endl;
	else if (obj->status == 1)
		std::cout << "Book Status: Borrowed" << std::endl;

	return os;
}
