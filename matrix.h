#pragma once
#ifndef MATRIX_H //  header file
#define MATRIX_H
//global value for max number of rows and columns in a matrix
const unsigned int MAX_ROWS = 10;
const unsigned int MAX_COLS = 10;

// There is a limitation to code that Matrices cant be bigger than 10X10
// But we can use vectors using vector STL in code to dynamically define the matrices
// As the code was pre defined in assignment i didnt use vectors
// structure instance of a matrix 
struct MatrixValues {
	unsigned int numRows;
	unsigned int numCols;
	int matrixValues[MAX_ROWS][MAX_COLS];
};

// operation of matrix values 
class MatrixType {
	MatrixValues values;
public:
	MatrixType(); // default constructor
	MatrixType(unsigned int numRows, unsigned int numCols,
		int matrixValues[MAX_ROWS][MAX_COLS]);  
	~MatrixType(); // destructor

	//Set Operation
	void SetSize();
	void SetValues();
	void PrintValues();

	//Get Operation
	unsigned int GetRows();
	unsigned int GetColumns();
	int GetValue(unsigned int row, unsigned int col);

};

//Other Operations 
MatrixType Add(MatrixType matrix1, MatrixType matrix2);
MatrixType Sub(MatrixType matrix1, MatrixType matrix2);
MatrixType Mult(MatrixType matrix1, MatrixType matrix2);


//link list implematation of matrix list 
struct MatrixNode {
	MatrixType matrix;
	MatrixNode* next;
};

//Conditions for compatibiltiy
bool AddSubCompatible(MatrixType matrix1, MatrixType matrix2);
bool MultCompatible(MatrixType matrix1, MatrixType matrix2);


//Operational class for Node Operations
class Matrix {
public:
	MatrixNode* matrix;
	Matrix(); // defualt constructor
	~Matrix(); // destructor
	unsigned int GetLength(); // gives length of link list
	MatrixNode* FindNode(int n); // 
	void Print();
	void Insert();
};
MatrixNode* Add(MatrixNode* matrix1, MatrixNode* matrix2);
MatrixNode* Sub(MatrixNode* matrix1, MatrixNode* matrix2);
MatrixNode* Mult(MatrixNode* matrix1, MatrixNode* matrix2);

#endif //MATRIX_H