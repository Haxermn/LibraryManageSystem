#pragma once
#include <iostream>
#include <string>

enum Availability //Status of the books when checked out or returned
{
	Available, Borrowed
};

enum Category //Genre of the books
{
	Science, History, Fiction, Psychology, Technology
};

struct Book //Book struct used for linked list
{
public:
	Book(int ID, int Published, std::string Title, std::string Author, Availability Status, Category genre) //Constructor that initializes all variables
		:ID(ID), Published(Published), Title(Title), Author(Author), genre(genre), status(Status)
	{}

	Book() //Empty constructor
	{}

	int ID; //Book ID for searches
	int Published; //Year the book was published
	std::string Title; //Title of the book
	std::string Author; //Author of the book
	
	Category genre; //Genre
	Availability status; //Status of the book, available or borrowed

	~Book() //No heap allocations, so no need to delete anything.
	{}
};

template<class T>
class LinkedLibraryNode //Node for the double linked list
{
public:
	LinkedLibraryNode() 
	{
		next = nullptr;
		prev = nullptr;
		element = nullptr;
	}

	T* element;
	LinkedLibraryNode* next;
	LinkedLibraryNode* prev;

	~LinkedLibraryNode() //Make sure to delete the heap allocated element when deleting the Linked Node.
	{
		next = nullptr;
		prev = nullptr;
		delete element;
	}

};

template<class T>
class LinkedLibraryList //Double linked list, contains that pertain to altering the list
{
public:
	LinkedLibraryNode<T>* head;
	LinkedLibraryNode<T>* current;
	int listCount;

	LinkedLibraryList() //Set list Count to start of ID numbers when constructed
	{
		head = nullptr;
		current = nullptr;
		listCount = 1001;
	}

	void AddBook(int Published, std::string Title, std::string Author, Availability Status, Category genre); //Adds a book into the linked list
	void RemoveBook(); //Removes a book from the linked list
	LinkedLibraryNode<T>* SearchForBook(int ID, std::string Title, Category Category); //Returns a linked node that matches the entered parameters
	LinkedLibraryNode<T>* SearchForBook(int ID); //Returns a linked node that matches the ID
	void ShowInventory(); //Prints out each book in the lists information
	void BorrowBook(); //Sets a book's status to borrowed if available, otherwise error and returns
	void ReturnBook(); //Sets a book's status to available if borrowed, otherwise error and returns
	void LibraryManagementInitialize(LinkedLibraryList<T>& Initiate); //Adds a predetermined amount of books
};

std::ostream& operator<<(std::ostream& os, const Book* obj); //Operator overloaded << to make printing to screen easy and repeatable.
