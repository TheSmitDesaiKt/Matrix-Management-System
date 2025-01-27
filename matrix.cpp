#include "matrix.h" // connecting the header file I created 
#include <iostream>
#include <iomanip>
using namespace std;

MatrixType::MatrixType() { //Defining Constructor 
	values.numRows = 0;
	values.numCols = 0;
}

MatrixType::MatrixType(unsigned int numRows, unsigned int numCols, int matrixValues[MAX_ROWS][MAX_COLS]) {
	values.numRows = numRows;
	values.numCols = numCols;
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			values.matrixValues[i][j] = matrixValues[i][j];
		}
	}
}

//Defining Destructor
MatrixType::~MatrixType() {
	// there is no dynamic allocation usage
	//this implematation is done due to just good gooding habit 
}


//setter functions
void MatrixType::SetSize() {
	cout << "Enter the number of Rows and Columns: ";
	cin >> values.numRows >> values.numCols; //Inputs the values for a particular instance of Matrix type
}

void MatrixType::SetValues() {
	for (int i = 0; i < values.numRows; i++) {  // Do same thing as in line 30 but this sets the indices of the matrix created
		for (int j = 0; j < values.numCols; j++) {
			cin >> values.matrixValues[i][j]; 
		}
	}
}

void MatrixType::PrintValues() { 
	for (int i = 0; i < values.numRows; i++) {
		for (int j = 0; j < values.numCols; j++) {
			cout << values.matrixValues[i][j];
		}
		cout << endl;
	}
}

// Above function only prints the indices of a particular Matrix
// Eg: if a function is called for a particular matrix in a list lets say number 2 matrix 
// it will print only matrix which is on number 2 in list of matrices


//getter functions
unsigned int MatrixType::GetRows() {
	return values.numRows;
}
unsigned int MatrixType::GetColumns() {
	return values.numCols;
}

int MatrixType::GetValue(unsigned int row, unsigned int col) {
	return values.matrixValues[row][col];
}


// Addition Operation for MatrixType instances
MatrixType Add(MatrixType matrix1, MatrixType matrix2) {
	unsigned int rows = matrix1.GetRows();
	unsigned int cols = matrix1.GetColumns();
	int resultValues[MAX_ROWS][MAX_COLS] = { 0 };

	// Check compatibility for addition
	if (!AddSubCompatible(matrix1, matrix2)) {
		throw std::invalid_argument("Matrix addition failed: Dimensions are not compatible.");
	}

	// Perform addition
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			resultValues[i][j] = matrix1.GetValue(i, j) + matrix2.GetValue(i, j);
		}
	}
	return MatrixType(rows, cols, resultValues); // creates the new result matrix 
}

// Subtraction operation for MatrixType instances
MatrixType Sub(MatrixType matrix1, MatrixType matrix2) {
	unsigned int rows = matrix1.GetRows();
	unsigned int cols = matrix1.GetColumns();
	int resultValues[MAX_ROWS][MAX_COLS] = { 0 };

	// Check compatibility for subtraction
	if (!AddSubCompatible(matrix1, matrix2)) {
		throw std::invalid_argument("Matrix subtraction failed: Dimensions are not compatible.");
	}

	// Perform subtraction
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			resultValues[i][j] = matrix1.GetValue(i, j) - matrix2.GetValue(i, j);
		}
	}
	return MatrixType(rows, cols, resultValues); // creates an new matrix from the operation of two others
}


//Multiplication Operation of MatrixType instances
MatrixType Mult(MatrixType matrix1, MatrixType matrix2) {
	unsigned int rows1 = matrix1.GetRows();
	unsigned int rows2 = matrix2.GetRows();
	unsigned int cols1 = matrix1.GetColumns();
	unsigned int cols2 = matrix2.GetColumns();
	int resultValues[MAX_ROWS][MAX_COLS] = { 0 };

	// Check compatibility for multiplication
	if (!MultCompatible(matrix1, matrix2)) {
		throw std::invalid_argument("Matrix multiplication failed: Dimensions are not compatible.");
	}

	// Perform multiplication
	for (unsigned int i = 0; i < rows1; i++) {
		for (unsigned int j = 0; j < cols2; j++) {
			for (unsigned int k = 0; k < cols1; k++) {
				resultValues[i][j] += matrix1.GetValue(i, k) * matrix2.GetValue(k, j);
			}
		}
	}
	return MatrixType(rows1, cols2, resultValues); // creates a new matrix as in above functions 
}



// Boolean Function {Condition Functions}
bool AddSubCompatible(MatrixType matrix1, MatrixType matrix2) {

	unsigned int rows1 = matrix1.GetRows();
	unsigned int cols1 = matrix1.GetColumns();
	unsigned int rows2 = matrix2.GetRows();
	unsigned int cols2 = matrix2.GetColumns();

	return (rows1 == rows2) && (cols1 == cols2); // operations happend only when the this returns true
}

bool MultCompatible(MatrixType matrix1, MatrixType matrix2) {

	unsigned int cols1 = matrix1.GetColumns();
	unsigned int rows2 = matrix2.GetRows();

	return (cols1 == rows2); // operations happend only when the this returns true
}

Matrix::Matrix() { // new class Matrix constructor
	matrix = {};
}

Matrix::~Matrix() { // Matrix Class Destructor
	MatrixNode* current = matrix;
	while (current) {
		MatrixNode* temp = current;
		current = current->next;
		delete temp; // Free the memory of each node
	}
	matrix = nullptr; // Set the pointer to null for safety
}

//getter function
unsigned int Matrix::GetLength() { // run a loop in list and l varialble increment by 1 everytime a node detected until a nullptr is detected
	unsigned int l = 0;
	MatrixNode* current = matrix;
	while (current) {
		l++;
		current = current->next;
	}
	return l; // returns number of nodes in a list 
}

MatrixNode* Matrix::FindNode(int n) {
	MatrixNode* current = matrix;
	int i = 1;
	while (current && i < n) {
		current = current->next;
		i++;
	}
	return current;
}

void Matrix::Print() { // Unlike PrintValue() Function this Function Prints all the matrices Node happends to be in List 
	MatrixNode* current = matrix;
	int index = 1; // To display matrix indices
	while (current) {
		cout << "\nMatrix " << index++ << ":\n";

		// Print each value with proper spacing
		for (unsigned int i = 0; i < current->matrix.GetRows(); ++i) {
			for (unsigned int j = 0; j < current->matrix.GetColumns(); ++j) {
				cout << setw(5) << current->matrix.GetValue(i, j); // Adjust column width
				//using the library <iomanip> the space is created betwwen the indices of matrices so we can identify which indices is located where in the matrix
			}
			cout << endl; // Move to the next row
		}
		current = current->next;
		//for betterment of code add a liltle space so output terminal look good
		cout << endl; // Add extra space between matrices
	}
}


//this is the main funtion which create and add the new Matrix Nodes in to the List 
void Matrix::Insert() {
	unsigned int numRows, numCols;
	cout << "A matrix has been created. Enter the number of rows and columns for the new matrix(Exception : Rows and columns should be smaller than 10):  ";
	cin >> numRows >> numCols;// take inputs of number of rows and columns

	int newValues[MAX_ROWS][MAX_COLS]; 
	cout << "Enter Values: \n";
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			cin >> newValues[i][j];
		}
	}

	//Creation of New Matrix Type 
	MatrixType newMatrix(numRows, numCols, newValues);
	MatrixNode* newNode = new MatrixNode{ newMatrix, nullptr };

	// Add the new node at the start
	newNode->next = matrix; // Link the new node to the current head
	matrix = newNode;       // Update head to point to the new node
}


// Rule:1 Always Check the conditions of the presence of parameters and if a list is empty or not before 
// defining the function functionality - Catherine Song ;)

// Addition Operation for Matrix Nodes
MatrixNode* Add(MatrixNode* matrix1, MatrixNode* matrix2) {
	if (!matrix1 || !matrix2) {
		cout << "One of the matrices does not exist.\n";
		return nullptr;

	}
	else {
		MatrixType resultMatrix = Add(matrix1->matrix, matrix2->matrix);
		return new MatrixNode{ resultMatrix, nullptr };
	}
}

//Subtraction Operation for Matrix Nodes
MatrixNode* Sub(MatrixNode* matrix1, MatrixNode* matrix2 ){
	if (!matrix1 || !matrix2) {
		cout << "One of matrices does not exist.\n";
		return nullptr;
	}
	else {
		MatrixType resultMatrix = Sub(matrix1->matrix, matrix2->matrix);
		return new MatrixNode{ resultMatrix, nullptr };
	}
}

//Multiplacation Operation for Matrix Nodes
MatrixNode* Mult(MatrixNode* matrix1, MatrixNode* matrix2) {
	if (!matrix1 || !matrix2) {
		cout << "One of the matrices does not exist.\n";
		return nullptr;
	}
	MatrixType resultMatrix = Mult(matrix1->matrix, matrix2->matrix);
	return new MatrixNode{ resultMatrix, nullptr };
}