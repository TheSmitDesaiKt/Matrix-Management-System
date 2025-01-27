#include <iostream>
#include "matrix.h"
using namespace std;

// Function to display the menu
void displayMenu() {// Main Menu Prints after every opertions take place in console 
    cout << "\n================= MATRIX OPERATIONS MENU =================\n";
    cout << "Enter the corresponding number for your desired operation:\n";
    cout << "1 – Insert a new matrix\n";
    cout << "2 – Add two matrices and insert the resultant matrix\n";
    cout << "3 – Subtract a matrix from another and insert the resultant matrix\n";
    cout << "4 – Multiply two matrices and insert the resultant matrix\n";
    cout << "5 – Print all matrices\n";
    cout << "6 – End the program\n";
    cout << "==========================================================\n";
    cout << "Your choice: ";
}

int main() {
    Matrix List; // List of matrices
    int ops; // choice input

    do {// Do While Loop so Code get iterate atleast one time before chosing 6 as a ending operation
        displayMenu();
        cin >> ops;

        // Handle invalid input
        if (cin.fail()) {
            //as ops variable only take integer value if user inputs a character or a string as input this will handle that type if inputs
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input! Please enter a number.\n";
            continue;
        }

        switch (ops) {
        case 1: {
            cout << "\n--- Insert a New Matrix ---\n";
            List.Insert();
            cout << "Matrix inserted successfully!\n";
            break;
        }
        case 2: {
            cout << "\n--- Add Two Matrices ---\n";

            //Rule 1 explained in matrix.cpp line 235 ;)
            if (List.GetLength() < 2) {
                cout << "Need at least two matrices to perform this operation.\n";
            }
            else {
                int first, second;
                cout << "There are a total of " << List.GetLength() << " matrices in the list.\n";
                cout << "Enter the indices of the matrices you want to add (starting from 1): ";
                cin >> first >> second;

                try {
                    MatrixNode* result = Add(List.FindNode(first), List.FindNode(second));
                    if (result) {
                        //inserting the matrice as Insert() function does not take any parameter i have to implement a logic to add the node after the operation
                        MatrixNode* newNode = new MatrixNode{ result->matrix, nullptr };
                        newNode->next = List.matrix; // Link the new node to the current head
                        List.matrix = newNode;       // Update the head of the list
                        cout << "Matrices added successfully! Result inserted at the start.\n";
                    }
                }
                catch (const std::invalid_argument& e) {
                    cout << e.what() << endl;
                }
            }
            break;
        }
        case 3: {
            cout << "\n--- Subtract Two Matrices ---\n";
            //Rule 1 explained in matrix.cpp line 235 ;)
            if (List.GetLength() < 2) {
                cout << "Need at least two matrices to perform this operation.\n";
            }
            else {
                //inserting the matrice as Insert() function does not take any parameter i have to implement a logic to add the node after the operation
                int first, second;
                cout << "There are a total of " << List.GetLength() << " matrices in the list.\n";
                cout << "Enter the indices of the matrices you want to subtract (starting from 1): ";
                cin >> first >> second;

                try {
                    MatrixNode* result = Sub(List.FindNode(first), List.FindNode(second));
                    if (result) {
                        //inserting the matrice as Insert() function does not take any parameter i have to implement a logic to add the node after the operation
                        MatrixNode* newNode = new MatrixNode{ result->matrix, nullptr };
                        newNode->next = List.matrix; // Link the new node to the current head
                        List.matrix = newNode;       // Update the head of the list
                        cout << "Matrices subtracted successfully! Result inserted at the start.\n";
                    }
                }
                catch (const std::invalid_argument& e) {
                    cout << e.what() << endl;
                }
            }
            break;
        }
        case 4: {
            cout << "\n--- Multiply Two Matrices ---\n";
            //Rule 1 explained in matrix.cpp line 235 ;)
            if (List.GetLength() < 2) {
                cout << "Need at least two matrices to perform this operation.\n";
            }
            else {
                int first, second;
                cout << "There are a total of " << List.GetLength() << " matrices in the list.\n";
                cout << "Enter the indices of the matrices you want to multiply (starting from 1): ";
                cin >> first >> second;

                try {
                    MatrixNode* result = Mult(List.FindNode(first), List.FindNode(second));
                    if (result) {
                        MatrixNode* newNode = new MatrixNode{ result->matrix, nullptr };
                        newNode->next = List.matrix; // Link the new node to the current head
                        List.matrix = newNode;       // Update the head of the list
                        cout << "Matrices multiplied successfully! Result inserted at the start.\n";
                    }
                }
                catch (const std::invalid_argument& e) {
                    cout << e.what() << endl;
                }
            }
            break;
        }
        case 5: {
            cout << "\n--- Print All Matrices ---\n";
            List.Print();
            break;
        }
        case 6: {
            cout << "\nThank you! Bye!\n";
            break;
        }
        default: {
            cout << "\nInvalid operation! Try again.\n";
            break;
        }
        }
        cout << endl; // Add a blank line between iterations for clarity
    } while (ops != 6);

    return 0;
}
