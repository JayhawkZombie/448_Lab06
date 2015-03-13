// MatrixCPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

class Matrix
{
public:
	Matrix();
	std::ifstream input;
	std::string fileName;
	void readFile();
	void print();
private:
	std::vector<std::string> lines;
	std::vector<std::string> numbers;
	int cols;
	int rows;
	double** matrix;
	void assignValuesToMatrix();
};

void Matrix::assignValuesToMatrix()
{
	//loops to allocate the memory for the matrix
//	matrix = new double*[rows];
	//	for (int j = 0; j < cols; j++)
		//{
			//matrix[j] = new double[cols];
		//}
}

void Matrix::print()
{
	std::cout << "Rows: " << rows << std::endl;
	std::cout << "Cols: " << cols << std::endl;
	for (int i = 0; i < rows; i++)
	{
		std::cout << lines[i] << std::endl;
	}
}

void Matrix::readFile()
{
	input.open(fileName);
	if (input.fail())
	{
		std::cout << "File " << fileName << " doesn't exist, stupid" << std::endl;
		return;
	}
	std::string fileString = "";

	input.close();
	input.open(fileName);

	while (std::getline(input, fileString))
	{
		lines.reserve(lines.size() + 1);
		lines.push_back(fileString);
	}
	rows = lines.size();
	int cols1 = 0, col2 = 0;

	//This code will remove the commas from the string
	for (int i = 0; i < rows; i++)
	{
		std::replace(lines[i].begin(), lines[i].end(), ',', ' ');
	}
	cols = (lines[0].length() + 1) / 2;
	print();

	/* At this point, the CSV file contains a valid matrix */
	std::string part = "";
	std::string line = "";
	for (int i = 0; i < lines.size(); i++)
	{
		line = lines[i];
		std::cout << "Lines[" << i << "]: " << line << std::endl;
		for (int j = 0; j < lines[i].length(); j++)
		{
			if (line[j] != ' ')
			{
				part += line[j]; //appending the 'number' to the string to be converted later
				std::cout << "PART[" << j << "]: " << part;
			}
			else
			{
				numbers.reserve(numbers.size() + 1);
				numbers.push_back(part);
				part = "";
			}
		}
		std::cout << "Numbers" << i << ": " << numbers[i] << std::endl;
	}
	
}

Matrix::Matrix()
{
	cols = 0;
	rows = 0;
	matrix = nullptr;
}

int main()
{

	Matrix matrix1;
	matrix1.fileName = "matrix1.csv";
	matrix1.readFile();
//	std::cout << "LINES: " << matrix1.lines.size() << std::endl;
	matrix1.print();


	return 0;
}

