// MatrixProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <locale>

class Matrix
{
public:
	Matrix();
	~Matrix();
	int rows;
	int cols;
	double* matrix;
	std::string fileName;
	void readFile();
	void print();
	void add(const Matrix& matrix1, const Matrix& matrix2);
	void operator = (const Matrix& matrix);
	void setSize(int row, int col);
	void transpose();
private:
	std::vector<std::string> lines;
	std::vector<double> numbers;
	void assignValues();
	bool square;
};

void Matrix::transpose()
{
	int k = 0;
	double* _new = new double[rows*cols];
	int _newCol = rows;
	int _newRow = cols;
	double* temp = matrix;
	
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			std::cout << "_new[" << k << "]: matrix[" << j*cols + i << "] = " << matrix[j*cols + i] << std::endl;
			_new[k] = matrix[j*cols + i];
			k++;
		}

	}

	matrix = _new;
	delete[] temp;
	cols = _newCol;
	rows = _newRow;
}

void Matrix::add(const Matrix& matrix1, const Matrix& matrix2)
{
	if (matrix1.rows == matrix2.rows && matrix1.cols == matrix2.cols)
	{
		//We can add the matrices because they are the same size
		this->matrix = new double[matrix1.rows*matrix1.cols];
		this->rows = matrix1.rows;
		this->cols = matrix1.cols;
		for (int i = 0; i < rows * cols; i++)
		{
			matrix[i] = matrix1.matrix[i] + matrix2.matrix[i];
		}
	}
}

void Matrix::operator=(const Matrix& copy)
{
	this->matrix = new double[copy.rows * copy.cols];
	for (int i = 0; i < copy.rows * copy.cols; i++)
	{
		std::cerr << "Copying value: " << copy.matrix[i] << std::endl;
		this->matrix[i] = copy.matrix[i];
	}
	this->rows = copy.rows;
	this->cols = copy.cols;
	this->fileName = copy.fileName;
	this->lines = copy.lines;
	this->numbers = copy.numbers;
}

Matrix::Matrix()
{
	fileName = "";
	rows = 0;
	cols = 0;
	matrix = nullptr;
	square = false;
}

Matrix::~Matrix()
{
	delete[] matrix;
}

void Matrix::readFile()
{
	std::ifstream in;
	in.open(fileName);
	if (in.fail())
	{
		std::cerr << "File does not exist." << std::endl;
		return;
	}

	/**else the file was able to be opened*/
	std::string fileLine = "";
	while (std::getline(in, fileLine))
	{
		lines.reserve(lines.size() + 1);
		lines.push_back(fileLine);
	}
	rows = lines.size();
	int colu = 0;

	std::string part = "";
	std::string line = "";

	for (int i = 0; i < lines.size(); i++)
	{
		line = lines[i];
		part = "";
		//std::cout << "LINES[" << i << "]:" << line << std::endl;

		for (int j = 0; j < line.length(); j++)
		{
			//std::cout << "LINE[" << j << "]:" << line[j] << std::endl;
			if (line[j] != ',' && line[j] != ' ' && line[j] != '\0' && line[j] != '\n')
			{
				//std::cout << "PART+=" << line[j] << std::endl;
				part += line[j];
				if (j == line.length() - 1)
				{
					//std::cout << "PART:" << part << std::endl;
					numbers.reserve(numbers.size() + 1);
					numbers.push_back(static_cast<double>(std::stoi(part)));
					part = "";
				}
			}
			else
			{
				//std::cout << "PART:" << part << std::endl;
				numbers.reserve(numbers.size() + 1);
				numbers.push_back(static_cast<double>(std::stoi(part)));
				part = "";
			}
		}
		cols = numbers.size() / rows;
	}
	square = (rows == cols);
	std::cout << "SQUARE: " << square << std::endl;
	assignValues();
}

void Matrix::assignValues()
{
	//Allocate the memory for the matrix
	matrix = new double[rows*cols];
	
	std::cerr << "Allocated memory" << std::endl;
	//Insert the values row by row
	
	int k = 0;
	for (int i = 0; i < rows*cols; i++)
	{
		matrix[i] = numbers[k++];
	}
	/**
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			std::cout << "Matrix[" << i*(cols - 1) + j << "] = " << numbers[k] << std::endl;
			matrix[(i * (cols - 1)) + j] = numbers[k];
			k++;
		}
	} */

	std::cerr << "Finished allocating memory" << std::endl;
}

void Matrix::print()
{
	/**
	std::cerr << "Printing with addressing from the dynamic array:" << std::endl;
	for (int i = 0; i < rows*cols; i++)
	{
		std::cout << matrix[i] << " ";
		if ((i+1) % (cols) == 0)
			std::cout << std::endl;
	} */

	std::cerr << "ACCESSING ELEMENTS(i,j)" << std::endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			std::cout << matrix[(i * (cols)) + j] << " ";
		}
		std::cout << std::endl;
	}  
}


int main()
{
	Matrix matrix1;
	matrix1.fileName = "matrix.csv";
	matrix1.readFile();
	matrix1.print();
	Matrix matrix2;
	matrix2.fileName = "matrix2.csv";
	matrix2.readFile();
	matrix2.print();
	Matrix matrix3;
	matrix3.add(matrix1, matrix2);
	matrix3.print();
	matrix3.transpose();
	matrix3.print();
	//std::cout << matrix1.rows << " by " << matrix1.cols << std::endl;
	return 0;
}

