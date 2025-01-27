#pragma once
#ifndef MATRIX_H // 
#define MATRIX_H
const unsigned int MAX_ROWS = 10;
const unsigned int MAX_COLS = 10;

struct MatrixValues {
	unsigned int numRows;
	unsigned int numCols;
	int matrixValues[MAX_ROWS][MAX_COLS];
};

class MatrixType {
	MatrixValues values;
public:
	MatrixType();
	MatrixType(unsigned int numRows, unsigned int numCols,
		int matrixValues[MAX_ROWS][MAX_COLS]);
	void SetSize();
	void SetValues();
	void PrintValues();
	unsigned int GetRows();
	unsigned int GetColumns();
	int GetValue(unsigned int row, unsigned int col);
};
MatrixType Add(MatrixType matrix1, MatrixType matrix2);
MatrixType Sub(MatrixType matrix1, MatrixType matrix2);
MatrixType Mult(MatrixType matrix1, MatrixType matrix2);

struct MatrixNode {
	MatrixType matrix;
	MatrixNode* next;
};
bool AddSubCompatible(MatrixType matrix1, MatrixType matrix2);
bool MultCompatible(MatrixType matrix1, MatrixType matrix2);

class Matrix {
public:
	MatrixNode* matrix;
	Matrix();
	unsigned int GetLength();
	MatrixNode* FindNode(int n);
	void Print();
	void Insert();
};
MatrixNode* Add(MatrixNode* matrix1, MatrixNode* matrix2);
MatrixNode* Sub(MatrixNode* matrix1, MatrixNode* matrix2);
MatrixNode* Mult(MatrixNode* matrix1, MatrixNode* matrix2);

#endif