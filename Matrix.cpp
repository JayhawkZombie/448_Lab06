// MatrixProject.cpp : Defines the entry point for the console application.
//HAHA
//MADE A CHANGE

/** I am using std::cerr for debugging code because it skips the standout output buffer and prints
    the string directly to the screen
    The parser isn't going to catch all error, but it should catch some of them - I'll make a more robust validator later
    The Matrix class has a dynamically allocated one-dimensional array to store the elements
    They are stored like this:
    [X X X X
     Y Y Y Y 
     Z Z Z Z]
    becomes
    [X X X X Y Y Y Y Z Z Z Z]
    To access a certain element, we go to the element (i * rows + j) where (i,j) is the MATRIX coordinate
    that we want to access
*/

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
private:
	std::vector<std::string> lines;
	std::vector<double> numbers;
	void assignValues();
	bool square;
};

void Matrix::add(const Matrix& matrix1, const Matrix& matrix2)
{
	if (matrix1.rows == matrix2.rows && matrix1.cols == matrix2.cols)
	{
		//We can add the matrices because they are the same size
	}
	this->matrix = new double[matrix1.rows*matrix1.cols];
	this->rows = matrix1.rows;
	this->cols = matrix1.cols;
	for (int i = 0; i < rows * cols; i++)
	{
		matrix[i] = matrix1.matrix[i] + matrix2.matrix[i];
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
	/** This reads the file one line at a time */
	/** fileLine is one line from the file - it should look something like this "1,3,5,7,9" without the quotes */
	std::string fileLine = "";
	while (std::getline(in, fileLine))
	{
		/** Pushing the lines into a vector so that I can parse them later */
		lines.reserve(lines.size() + 1);
		lines.push_back(fileLine);
	}
	//calculate the number of rows in the file
	rows = lines.size();
	//oops, unused variable
//	int colu = 0;

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
				//if it passes that test, then the character must be a number
				//so we'll put that into a string and convert that string to a double
				//std::cout << "PART+=" << line[j] << std::endl;
				part += line[j];
				if (j == line.length() - 1)
				{
					//this is a bug fix - the last value in the rows was not getting assigned
					//to the matrix, so this is a workaround
					//std::cout << "PART:" << part << std::endl;
					numbers.reserve(numbers.size() + 1);
					//oops, need to change std::stoi to std::stod
					//will change later and test functionality
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
	char c;
	std::cin >> c;
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
	//std::cout << matrix1.rows << " by " << matrix1.cols << std::endl;
	return 0;
}

