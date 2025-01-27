#include "matrix.h"
#include <iostream>
#include <iomanip>
using namespace std;

MatrixType::MatrixType() {
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

void MatrixType::SetSize() {
	cout << "Enter the number of Rows and Columns: ";
	cin >> values.numRows >> values.numCols;
}

void MatrixType::SetValues() {
	for (int i = 0; i < values.numRows; i++) {
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

unsigned int MatrixType::GetRows() {
	return values.numRows;
}
unsigned int MatrixType::GetColumns() {
	return values.numCols;
}

int MatrixType::GetValue(unsigned int row, unsigned int col) {
	return values.matrixValues[row][col];
}

MatrixType Add(MatrixType matrix1, MatrixType matrix2) {
	unsigned int rows = matrix1.GetRows();
	unsigned int cols = matrix1.GetColumns();
	int resultValues[MAX_ROWS][MAX_COLS] = { 0 };

	// Check compatibility for addition
	if (rows != matrix2.GetRows() || cols != matrix2.GetColumns()) {
		throw std::invalid_argument("Matrix addition failed: Dimensions are not compatible.");
	}

	// Perform addition
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			resultValues[i][j] = matrix1.GetValue(i, j) + matrix2.GetValue(i, j);
		}
	}
	return MatrixType(rows, cols, resultValues);
}

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
	return MatrixType(rows, cols, resultValues);
}

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
	return MatrixType(rows1, cols2, resultValues);
}


bool AddSubCompatible(MatrixType matrix1, MatrixType matrix2) {

	unsigned int rows1 = matrix1.GetRows();
	unsigned int cols1 = matrix1.GetColumns();
	unsigned int rows2 = matrix2.GetRows();
	unsigned int cols2 = matrix2.GetColumns();

	return (rows1 == rows2) && (cols1 == cols2);
}

bool MultCompatible(MatrixType matrix1, MatrixType matrix2) {

	unsigned int cols1 = matrix1.GetColumns();
	unsigned int rows2 = matrix2.GetRows();

	return (cols1 == rows2);
}

Matrix::Matrix() {
	matrix = {};
}

unsigned int Matrix::GetLength() {
	unsigned int l = 0;
	MatrixNode* current = matrix;
	while (current) {
		l++;
		current = current->next;
	}
	return l;
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

void Matrix::Print() {
	MatrixNode* current = matrix;
	int index = 1; // To display matrix indices
	while (current) {
		cout << "\nMatrix " << index++ << ":\n";

		// Print each value with proper spacing
		for (unsigned int i = 0; i < current->matrix.GetRows(); ++i) {
			for (unsigned int j = 0; j < current->matrix.GetColumns(); ++j) {
				cout << setw(5) << current->matrix.GetValue(i, j); // Adjust column width
			}
			cout << endl; // Move to the next row
		}
		current = current->next;
		cout << endl; // Add extra space between matrices
	}
}

void Matrix::Insert() {
	unsigned int numRows, numCols;
	cout << "A matrix has been created. Enter the number of rows and columns for the new matrix: ";
	cin >> numRows >> numCols;

	int newValues[MAX_ROWS][MAX_COLS];
	cout << "Enter Values: \n";
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			cin >> newValues[i][j];
		}
	}
	MatrixType newMatrix(numRows, numCols, newValues);
	MatrixNode* newNode = new MatrixNode{ newMatrix, nullptr };

	// Add the new node at the start
	newNode->next = matrix; // Link the new node to the current head
	matrix = newNode;       // Update head to point to the new node
}


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

MatrixNode* Mult(MatrixNode* matrix1, MatrixNode* matrix2) {
	if (!matrix1 || !matrix2) {
		cout << "One of the matrices does not exist.\n";
		return nullptr;
	}
	MatrixType resultMatrix = Mult(matrix1->matrix, matrix2->matrix);
	return new MatrixNode{ resultMatrix, nullptr };
}