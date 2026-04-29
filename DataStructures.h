//#pragma once
//
//#include <iostream>
//
//template <typename T>
//class Node
//{
//public:
//	Node* prev = nullptr;
//	Node* next = nullptr;
//	T data = 0;
//
//	Node(T _data)
//	{
//		data = _data;
//	}
//};
//
//template <typename T>
//class LinkedList
//{
//	
//
//	Node* head = nullptr;
//	int len = 0; // Tracks The Total No Of Elements In List
//
//public:
//
//	// Insert The Element At The Beginning Of The LinkedList
//	void InsertAtBegin(T val)
//	{
//		Node* insNode = new Node(val); // Node To Insert
//
//		// Check For Overflow
//		if (!insNode)
//		{
//			std::cerr << "Error! Overflow Occured In LinkedList...\n";
//			return;
//		}
//
//		// If LinkedList Is Empty
//		if (head == nullptr)
//		{
//			head = insNode;
//			len++;
//			return;
//		}
//
//		// Insert The Node At Start
//		Node* temp = head;
//		head = insNode;
//		insNode->next = temp;
//		len++; // Increase The Length
//
//	}
//
//	Node* GetFirstNode() const
//	{
//		return head;
//	}
//
//	// Insert The Element Before The pos Node 
//	void InsertBefore(T pos, T val)
//	{
//		Node* insNode = new Node(val); // Node To Insert
//		Node* temp = head;
//
//		// Check For Overflow
//		if (!insNode)
//		{
//			std::cerr << "Error! Overflow Occured In LinkedList...\n";
//			return;
//		}
//
//		// If LinkedList Is Empty
//		if (head == nullptr)
//		{
//			head = insNode;
//			len++;
//			return;
//		}
//
//		// If LinkedList Has One Element
//		if (temp->prev == nullptr)
//		{
//			insNode->next = temp;
//			temp->prev = insNode;
//			head = insNode;
//			return;
//		}
//
//
//
//		// Find The Position Node For Insertion
//		while (temp != nullptr and temp->data != pos)
//		{
//			temp = temp->next;
//		}
//
//		// If The Position Doesn't Exist
//		if (temp == nullptr)
//		{
//			std::cerr << "Error! The Specified Position (" << pos << ") Doesn't Exist In The LinkedList...\n";
//			delete insNode;
//			return;
//		}
//
//
//
//		insNode->next = temp;
//		insNode->prev = temp->prev;
//		(temp->prev)->next = insNode;
//		temp->prev = insNode;
//
//		len++; // Increase The Length
//
//
//	}
//
//	// Insert The Element After The pos Node
//	void InsertAfter(T pos, T val)
//	{
//		Node* insNode = new Node(val); // Node To Insert
//
//		// Check For Overflow
//		if (!insNode)
//		{
//			std::cerr << "Error! Overflow Occured In LinkedList...\n";
//			return;
//		}
//
//		// If LinkedList Is Empty
//		if (head == nullptr)
//		{
//			head = insNode;
//			len++;
//			return;
//		}
//
//		Node* temp = head;
//
//		// Find The Position Node For Insertion
//		while (temp != nullptr and temp->data != pos)
//		{
//			temp = temp->next;
//		}
//
//		// If The Position Doesn't Exist
//		if (temp == nullptr)
//		{
//			std::cerr << "Error! The Specified Position (" << pos << ") Doesn't Exist In The LinkedList...\n";
//			delete insNode;
//			return;
//		}
//
//		// Insert The Node After <temp>
//		insNode->next = temp->next;
//		insNode->prev = temp;
//		temp->next = insNode;
//
//		len++; // Increase The Length
//	}
//
//	// Insert The Element At The Last Of The LinkedList
//	void InsertAtEnd(T val)
//	{
//		Node* insNode = new Node(val); // Node To Insert
//		Node* temp = head; // Stores The Last Node
//
//		// Check For Overflow
//		if (!insNode)
//		{
//			std::cerr << "Error! Overflow Occured In LinkedList...\n";
//			return;
//		}
//
//		// If LinkedList Is Empty
//		if (head == nullptr)
//		{
//			head = insNode;
//			len++;
//			return;
//		}
//
//		// Find The Last Node
//		while (temp->next != nullptr)
//		{
//			temp = temp->next;
//		}
//
//		// Insert The Node After Last Node
//		temp->next = insNode;
//		insNode->prev = temp;
//		len++;
//
//	}
//
//	// Delete The First Element
//	void DeleteAtStart()
//	{
//
//		// Check For Underflow
//		if (head == nullptr)
//		{
//			std::cerr << "Error! Underflow Occurred In LinkedList...\n";
//			return;
//		}
//
//		// Delete The First Node
//		Node* temp = head;
//		head = head->next;
//		delete temp;
//		len--;
//
//	}
//
//	// Delete The Specified Element
//	void Delete(T val)
//	{
//		Node* temp = head;
//
//		// Check For Underflow
//		if (head == nullptr)
//		{
//			std::cerr << "Error! Underflow Occurred In LinkedList...\n";
//			return;
//
//		}
//
//		// If The Node To Delete Is The First Node
//		if (head->data == val)
//		{
//			head = head->next;
//			delete temp;
//			len--;
//			return;
//		}
//
//		// Find The Node To Delete
//		while (temp != nullptr and temp->data != val)
//		{
//			temp = temp->next;
//		}
//
//		// If The Node To Delete Doesn't Exist
//		if (temp == nullptr)
//		{
//			std::cerr << "Error! Cannot Find The Node To Delete With Value (" << val << ")...\n";
//			return;
//		}
//
//
//		// Delete The Node
//		(temp->prev)->next = temp->next;
//		delete temp;
//		len--;
//	}
//
//	// Delete The Last Element
//	void DeleteAtEnd()
//	{
//		Node* temp = head;
//
//		// Check For Underflow
//		if (head == nullptr)
//		{
//			std::cerr << "Error! Underflow Occurred In LinkedList...\n";
//			return;
//		}
//
//		// If LinkedList Has Only One Node
//		if (head->prev == nullptr and head->next == nullptr)
//		{
//			delete head;
//			head = nullptr;
//			len--;
//			return;
//		}
//
//
//		// Find The Last Node
//		while (temp->next != nullptr)
//		{
//			temp = temp->next;
//		}
//
//		// Delete The Last Node
//		(temp->prev)->next = nullptr;
//		delete temp;
//		len--;
//
//
//	}
//
//	// Print The Linked List
//	void Print()
//	{
//		Node* temp = head;
//
//		std::cout << "{ ";
//
//		while (temp != nullptr)
//		{
//			std::cout << temp->data << " ";
//			temp = temp->next;
//		}
//
//		std::cout << "}\n";
//	}
//
//	// Print The Linked List In Reverse Order
//	void PrintReverse()
//	{
//		Node* temp = head;
//
//		std::cout << "{ ";
//
//		// Go To The Last Node
//		while (temp->next != nullptr)
//			temp = temp->next;
//
//		// Print From Last To First
//		while (temp != nullptr)
//		{
//			std::cout << temp->data << " ";
//			temp = temp->prev;
//		}
//
//		std::cout << "}\n";
//	}
//
//	// Returns The Total Number Of Elements Present In The List
//	int Length()
//	{
//		return len;
//	}
//
//	// Forcefully Check The Length Of LinkedList
//	int Size()
//	{
//		Node* temp = head;
//		int count = 0;
//
//		while (temp != nullptr)
//		{
//			count++;
//			temp = temp->next;
//		}
//
//		return count;
//	}
//
//	// Returns The Value Of The Previous Element Within Linked List
//	T Before(T val)
//	{
//		Node* temp = head;
//
//		// Find The val Node
//		while (temp != nullptr and temp->data != val)
//		{
//			temp = temp->next;
//		}
//
//		// If The Node With Specified Value Doesn't Exist
//		if (temp == nullptr)
//		{
//			std::cerr << "Error! Cannot Find The Node With Value (" << val << ") Within LinkedList...\n";
//			return NULL;
//		}
//
//		// No Previous Node Exists
//		if (temp->prev == nullptr)
//		{
//			return NULL;
//		}
//
//		// Return The Previous Node's Value
//		return (temp->prev)->data;
//	}
//
//	// Returns The Value Of The Next Element Within Linked List
//	T After(T val)
//	{
//		Node* temp = head;
//
//		// Find The val Node
//		while (temp != nullptr and temp->data != val)
//		{
//			temp = temp->next;
//		}
//
//		// If The Node With Specified Value Doesn't Exist
//		if (temp == nullptr)
//		{
//			std::cerr << "Error! Cannot Find The Node With Value (" << val << ") Within LinkedList...\n";
//			return NULL;
//		}
//
//		// No Previous Node Exists
//		if (temp->next == nullptr)
//		{
//			return NULL;
//		}
//
//		// Return The Previous Node's Value
//		return (temp->next)->data;
//	}
//
//	// Checks Whether A Given Value Is Present In The List Or Not
//	bool Find(T val)
//	{
//		Node* temp = head;
//
//		// Traverse The List
//		while (temp->next != nullptr)
//		{
//			// Element Found
//			if (temp->data == val)
//			{
//				return true;
//			}
//
//			temp = temp->next;
//		}
//
//		// If No Element Found
//		return false;
//
//	}
//
//	// Destructor
//	~LinkedList()
//	{
//		// Deallocate The Memory
//		while (head)
//		{
//			DeleteAtStart();
//		}
//	}
//};
//
//
//class Vector2
//{
//public:
//	int x, y;
//
//	Vector2(int _x, int _y)
//	{
//		x = _x;
//		y = _y;
//	}
//
//	// Empty Constructor
//	Vector2() : x(0), y(0) {}
//
//	static Vector2 Zero()
//	{
//		return { 0,0 };
//	}
//
//	static Vector2 One()
//	{
//		return { 1,0 };
//	}
//};
//
//









#pragma once

#include <iostream>

template <typename T>
class Node
{
public:
	Node* prev = nullptr;
	Node* next = nullptr;
	T data;

	Node(T _data)
	{
		data = _data;
	}


};

template <typename T>
class LinkedList
{


	
	int len = 0; // Tracks The Total No Of Elements In List

public:
	Node<T>* head = nullptr;

	// Insert The Element At The Beginning Of The LinkedList
	void InsertAtBegin(T val)
	{
		Node<T>* insNode = new Node<T>(val); // Node To Insert

		// Check For Overflow
		if (!insNode)
		{
			std::cerr << "Error! Overflow Occured In LinkedList...\n";
			return;
		}

		// If LinkedList Is Empty
		if (head == nullptr)
		{
			head = insNode;
			len++;
			return;
		}

		// Insert The Node At Start
		Node<T>* temp = head;
		head = insNode;
		insNode->next = temp;
		len++; // Increase The Length

	}

	Node<T>*&  GetHead() 
	{
		return head;
	}

	// Insert The Element Before The pos Node 
	void InsertBefore(T pos, T val)
	{
		Node<T>* insNode = new Node(val); // Node To Insert
		Node<T>* temp = head;

		// Check For Overflow
		if (!insNode)
		{
			std::cerr << "Error! Overflow Occured In LinkedList...\n";
			return;
		}

		// If LinkedList Is Empty
		if (head == nullptr)
		{
			head = insNode;
			len++;
			return;
		}

		// If LinkedList Has One Element
		if (temp->prev == nullptr)
		{
			insNode->next = temp;
			temp->prev = insNode;
			head = insNode;
			return;
		}



		// Find The Position Node For Insertion
		while (temp != nullptr and temp->data != pos)
		{
			temp = temp->next;
		}

		// If The Position Doesn't Exist
		if (temp == nullptr)
		{
			std::cerr << "Error! The Specified Position (" << pos << ") Doesn't Exist In The LinkedList...\n";
			delete insNode;
			return;
		}



		insNode->next = temp;
		insNode->prev = temp->prev;
		(temp->prev)->next = insNode;
		temp->prev = insNode;

		len++; // Increase The Length


	}

	// Insert The Element After The pos Node
	void InsertAfter(T pos, T val)
	{
		Node<T>* insNode = new Node(val); // Node To Insert

		// Check For Overflow
		if (!insNode)
		{
			std::cerr << "Error! Overflow Occured In LinkedList...\n";
			return;
		}

		// If LinkedList Is Empty
		if (head == nullptr)
		{
			head = insNode;
			len++;
			return;
		}

		Node<T>* temp = head;

		// Find The Position Node For Insertion
		while (temp != nullptr and temp->data != pos)
		{
			temp = temp->next;
		}

		// If The Position Doesn't Exist
		if (temp == nullptr)
		{
			std::cerr << "Error! The Specified Position (" << pos << ") Doesn't Exist In The LinkedList...\n";
			delete insNode;
			return;
		}

		// Insert The Node After <temp>
		insNode->next = temp->next;
		insNode->prev = temp;
		temp->next = insNode;

		len++; // Increase The Length
	}

	// Insert The Element At The Last Of The LinkedList
	void InsertAtEnd(T val)
	{
		Node<T>* insNode = new Node<T>(val); // Node To Insert
		Node<T>* temp = head; // Stores The Last Node

		// Check For Overflow
		if (!insNode)
		{
			std::cerr << "Error! Overflow Occured In LinkedList...\n";
			return;
		}

		// If LinkedList Is Empty
		if (head == nullptr)
		{
			head = insNode;
			len++;
			return;
		}

		// Find The Last Node
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}

		// Insert The Node After Last Node
		temp->next = insNode;
		insNode->prev = temp;
		len++;

	}

	// Delete The First Element
	void DeleteAtStart()
	{

		// Check For Underflow
		if (head == nullptr)
		{
			std::cerr << "Error! Underflow Occurred In LinkedList...\n";
			return;
		}

		// Delete The First Node
		Node<T>* temp = head;
		head = head->next;
		delete temp;
		len--;

	}

	// Delete The Specified Element
	void Delete(T val)
	{
		Node<T>* temp = head;

		// Check For Underflow
		if (head == nullptr)
		{
			std::cerr << "Error! Underflow Occurred In LinkedList...\n";
			return;

		}

		// If The Node To Delete Is The First Node
		if (head->data == val)
		{
			head = head->next;
			delete temp;
			len--;
			return;
		}

		// Find The Node To Delete
		while (temp != nullptr and temp->data != val)
		{
			temp = temp->next;
		}

		// If The Node To Delete Doesn't Exist
		if (temp == nullptr)
		{
			std::cerr << "Error! Cannot Find The Node To Delete With Value (" << val << ")...\n";
			return;
		}


		// Delete The Node
		(temp->prev)->next = temp->next;
		delete temp;
		len--;
	}

	// Delete The Last Element
	void DeleteAtEnd()
	{
		Node<T>* temp = head;

		// Check For Underflow
		if (head == nullptr)
		{
			std::cerr << "Error! Underflow Occurred In LinkedList...\n";
			return;
		}

		// If LinkedList Has Only One Node
		if (head->prev == nullptr and head->next == nullptr)
		{
			delete head;
			head = nullptr;
			len--;
			return;
		}


		// Find The Last Node
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}

		// Delete The Last Node
		(temp->prev)->next = nullptr;
		delete temp;
		len--;


	}

	// Print The Linked List
	void Print()
	{
		Node<T>* temp = head;

		std::cout << "{ ";

		while (temp != nullptr)
		{
			std::cout << temp->data << " ";
			temp = temp->next;
		}

		std::cout << "}\n";
	}

	// Print The Linked List In Reverse Order
	void PrintReverse()
	{
		Node<T>* temp = head;

		std::cout << "{ ";

		// Go To The Last Node
		while (temp->next != nullptr)
			temp = temp->next;

		// Print From Last To First
		while (temp != nullptr)
		{
			std::cout << temp->data << " ";
			temp = temp->prev;
		}

		std::cout << "}\n";
	}

	// Returns The Total Number Of Elements Present In The List
	int Length()
	{
		return len;
	}

	// Forcefully Check The Length Of LinkedList
	int Size()
	{
		Node<T>* temp = head;
		int count = 0;

		while (temp != nullptr)
		{
			count++;
			temp = temp->next;
		}

		return count;
	}

	// Returns The Value Of The Previous Element Within Linked List
	T Before(T val)
	{
		Node<T>* temp = head;

		// Find The val Node
		while (temp != nullptr and temp->data != val)
		{
			temp = temp->next;
		}

		// If The Node With Specified Value Doesn't Exist
		if (temp == nullptr)
		{
			std::cerr << "Error! Cannot Find The Node With Value (" << val << ") Within LinkedList...\n";
			return NULL;
		}

		// No Previous Node Exists
		if (temp->prev == nullptr)
		{
			return NULL;
		}

		// Return The Previous Node's Value
		return (temp->prev)->data;
	}

	// Returns The Value Of The Next Element Within Linked List
	T After(T val)
	{
		Node<T>* temp = head;

		// Find The val Node
		while (temp != nullptr and temp->data != val)
		{
			temp = temp->next;
		}

		// If The Node With Specified Value Doesn't Exist
		if (temp == nullptr)
		{
			std::cerr << "Error! Cannot Find The Node With Value (" << val << ") Within LinkedList...\n";
			return NULL;
		}

		// No Previous Node Exists
		if (temp->next == nullptr)
		{
			return NULL;
		}

		// Return The Previous Node's Value
		return (temp->next)->data;
	}

	// Checks Whether A Given Value Is Present In The List Or Not
	bool Find(T val)
	{
		Node<T>* temp = head;

		// Traverse The List
		while (temp->next != nullptr)
		{
			// Element Found
			if (temp->data == val)
			{
				return true;
			}

			temp = temp->next;
		}

		// If No Element Found
		return false;

	}

	// Destructor
	~LinkedList()
	{
		// Deallocate The Memory
		while (head)
		{
			DeleteAtStart();
		}
	}
};


class Vector2
{
public:
	int x, y;

	Vector2(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	// Empty Constructor
	Vector2() : x(0), y(0) {}

	static Vector2 Zero()
	{
		return { 0,0 };
	}

	static Vector2 One()
	{
		return { 1,0 };
	}
};




