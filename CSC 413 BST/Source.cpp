/*************************************************************************************************************************
*   Source.cpp
*   BinarySearchTree
*
*   Created by Zachary Torricelli on 3/18/19.
*   Copyright © 2019 Zachary Torricelli. All rights reserved.
*
*   Implement your binary search tree.
*   You must implement all the following functions/ algorithms (in-order tree traversal, search for a particular key in a
*   binary search tree, find the minimum and maximum, find the successor of a given node x [must test both the
*   situations], insert a new key, delete a key [must test all the situations]) for binary search trees
*
*************************************************************************************************************************/


// Header file and using directive
#include <iostream>

using namespace std;

#define SIZE 11


// Struct used to create a node
struct node
{

	int data;
	node *leftChild;
	node *rightChild;
	node *parent;

};


// Global variable
node *root = NULL;


// Function prototypes
void menu();
node *newNode(int);
node* insert(node*, int);
node *minimumValue(node*);
node *maximumValue(node*);
node *search(node*, int);
node *successor(node*);
void transplant(node*, node*);
void remove(node*);
void printTreeInOrder(node*);



// Main driver function
int main()
{

	menu();


	system("pause");
	return 0;

}



// Menu function that displays to the console
void menu()
{

	// Variable declaration in this function function
	int myArray[SIZE] = { 15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9 };
	int choice = 8;
	int insertValue = 0;
	int searchValue = 0;
	node *goal;
	node *success;


	// Displays a welcome message to the console
	cout << "Welcome to Zac's Binary Search Tree!" << endl;
	cout << "Please enter a number (1-8)." << endl << endl;


	// Hard codes the binary tree
	root = insert(root, 15);
	insert(root, 6);
	insert(root, 18);
	insert(root, 3);
	insert(root, 7);
	insert(root, 17);
	insert(root, 20);
	insert(root, 2);
	insert(root, 4);
	insert(root, 13);
	insert(root, 9);


	// Do-while loop for the menu 
	do
	{

		// Displays a menu to the console
		cout << "1. View Binary Tree " << endl;
		cout << "2. Insert New Key" << endl;
		cout << "3. Find Minimum and Maximum Value" << endl;
		cout << "4. Search Tree" << endl;
		cout << "5. View Successor" << endl;
		cout << "6. Print Tree In Order" << endl;
		cout << "7. Delete Key" << endl;
		cout << "8. Exit" << endl << endl;

		cin >> choice;


		// While loop to make sure the user inputs a valid option
		while (cin.fail())
		{

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Please enter a number (1-8)." << endl << endl;
			cin >> choice;

		}


		// Switch statement to switch between menu options
		switch (choice)
		{

			// Case 1 will print the current BST
		case 1:

			system("CLS");

			cout << "Current Binary Search Tree: " << endl;


			// For loop to display the BST from an array
			for (int i = 0; i < SIZE; i++)
			{

				cout << myArray[i] << "\t";

			}

			cout << endl << endl;

			break;


			// Case 2 will allow the user to insert a new key
		case 2:

			system("CLS");

			cout << "What value would you like to insert? " << endl;
			cin >> insertValue;
			cout << endl << endl;

			insert(root, insertValue);
			cout << "Updated Binary Tree: " << endl;
			printTreeInOrder(root);

			cout << endl << endl;

			break;


			// Case 3 will find the minimum and maximum value in the BST1
		case 3:

			system("CLS");

			// Calls the minimumValue and maximumValue functions and displays their values
			cout << "The Minimum Value is: " << minimumValue(root)->data << endl << endl;
			cout << "The Maximum Value is: " << maximumValue(root)->data << endl << endl;

			break;


			// Case 4 will perform a search of the BST
		case 4:

			system("CLS");

			cout << "What value would you like to search for? " << endl;
			cin >> searchValue;
			cout << endl << endl;

			goal = search(root, searchValue);


			if (goal)
			{

				cout << "Search Key Found: " << goal->data << endl;

			}

			else
			{

				cout << "Search Key Not Found" << endl;

			}

			cout << endl << endl;

			break;


			// Case 5 will print the successors in the BST
		case 5:

			system("CLS");

			cout << "Successor of the root is: ";
			cout << successor(root)->data << endl << endl;

			cout << "Successor of the Minimum Value is: ";
			cout << (successor(minimumValue(root)))->data << endl << endl;

			success = successor(maximumValue(root));

			if (success != NULL)
			{

				cout << "Successor is: " << success->data << endl << endl;

			}

			else
			{

				cout << "No Successor of the Maximum Value" << endl << endl;

			}

			cout << endl << endl;

			break;


			// Case 6 will print the BST in order
		case 6:

			system("CLS");

			cout << "Binary Tree In Order: " << endl;
			printTreeInOrder(root);

			cout << endl << endl;

			break;


			// Case 7 will delete a key from the BST
		case 7:

			system("CLS");

			cout << "Removed Root: " << endl;
			remove(root);
			printTreeInOrder(root);

			cout << endl << endl;

			cout << "Removed Minimum Value: " << endl;
			remove(minimumValue(root));
			printTreeInOrder(root);

			cout << endl << endl;

			cout << "Removed Maximum Value: " << endl;
			remove(maximumValue(root));
			printTreeInOrder(root);

			cout << endl << endl;

			break;


			// Case 8 will exit the program
		case 8:

			exit(0);


			// Default case will collect the invalid options input and let the user try again
		default:

			system("CLS");

			cout << "Invalid selection. Try again" << endl;

		}


	} while (choice != 8);


}



// Function used to create a new node
node *newNode(int data)
{

	// Creates a new node
	struct node *temp = (struct node *)malloc(sizeof(struct node));

	temp->data = data;

	temp->leftChild = temp->rightChild = temp->parent = NULL;

	// Returns the new node
	return temp;

}



// Function to insert a new node in the binary search tree
node *insert(node* node, int data)
{


	if (node == NULL)
	{

		return newNode(data);

	}


	if (data < node->data)
	{

		struct node *tempL = insert(node->leftChild, data);
		node->leftChild = tempL;

		tempL->parent = node;

	}

	else if (data > node->data)
	{

		struct node *tempR = insert(node->rightChild, data);
		node->rightChild = tempR;

		tempR->parent = node;

	}

	// Returns the node
	return node;

}



// Function used to find the minimum node value in the binary tree
node *minimumValue(node *node)
{


	// Node declaraton
	struct node *current = node;


	// While loop to search down to find the leftmost leaf
	while (current->leftChild != NULL)
	{

		current = current->leftChild;

	}

	// Returns the minimum value
	return current;

}



// Function used to find the maximum value in the binary tree
node *maximumValue(node *node)
{

	// Node declaraton
	struct node *current = node;


	// While loop to search down to find the leftmost leaf
	while (current->rightChild != NULL)
	{

		current = current->rightChild;

	}

	// Returns the minimum value
	return current;

}



// Function used to search for a particular value in the binary search tree
node *search(node* node, int data)
{

	if (node == NULL || node->data == data)
	{

		return node;

	}


	if (node->data < data)
	{

		return search(node->rightChild, data);

	}

	return search(node->leftChild, data);

}



// Function used to returnn the successor of a node in a BST
node *successor(node* node)
{

	if (node->rightChild != NULL)
	{

		return minimumValue(node->rightChild);

	}


	struct node *temp;
	temp = node->parent;


	while (temp != NULL && node == temp->rightChild)
	{

		node = temp;
		temp = temp->parent;

	}

	// Returns the successor
	return temp;

}



// Transplant function that replaces one subtree as a child of its parent with another subtree
void transplant(node *node, struct node *otherNode)
{

	if (node->parent == NULL)
	{

		root = otherNode;

	}

	else if (node == node->parent->leftChild)
	{

		node->parent->leftChild = otherNode;

	}

	else
	{

		node->parent->rightChild = otherNode;

	}

	if (otherNode != NULL)
	{

		otherNode->parent = node->parent;

	}

}



// Remove function to delete a node from the BST
void remove(node *node)
{


	if (node->leftChild == NULL)
	{

		transplant(node, node->rightChild);

	}

	else if (node->rightChild == NULL)
	{

		transplant(node, node->leftChild);

	}

	else
	{

		struct node *temp = minimumValue(node->rightChild);

		if (temp->parent != node)
		{

			transplant(temp, temp->rightChild);
			temp->rightChild = node->rightChild;
			temp->rightChild->parent = temp;

		}


		transplant(node, temp);
		temp->leftChild = node->leftChild;
		temp->leftChild->parent = temp;

	}

}



// Recursive function used to print the BST in order
void printTreeInOrder(node *node)
{

	if (node != NULL)
	{

		printTreeInOrder(node->leftChild);

		cout << node->data << "\t";

		printTreeInOrder(node->rightChild);

	}

}
