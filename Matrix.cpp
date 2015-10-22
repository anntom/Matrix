#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <omp.h>
#include "time.h"

Matrix::Matrix(MatrixType & mat)
	:Mat(mat)
{
}
Matrix Matrix::operator*(Matrix const &mat) const
{
	time_t start;
	time_t end;
	MatrixType MatRes(Mat.size());
	if (Mat[0].size() != mat.Mat.size())
	{
		cout << "Sizes doesn't match" << endl;
		return MatRes;
	}
	int ij, i, j;
	for ( int i = 0; i < mat.Mat[0].size(); i++ )
	{
		MatRes[i].resize(mat.Mat[0].size());
	}
	time(&start);
	#pragma omp parallel
	{
		#pragma omp for private (ij , i, j)
		for (ij = 0; ij < Mat.size() * mat.Mat[0].size(); ij++ )
		{
			i = ij / Mat.size();
			j = ij % mat.Mat[0].size();
			float sum = 0;
			for (int k = 0; k < Mat[0].size(); ++k)
			{
				sum += Mat[i][k] * mat.Mat[k][j];
			}
			MatRes[i][j] = sum;
			sum = 0;
		}	
	}
	time(&end);
	cout << difftime(end, start) << endl;
	return MatRes;
}
void Matrix::print() const
{
	ofstream f("res.txt");
	if (f.is_open())
	{
		for (size_t i = 0; i < Mat.size(); ++i)
		{
			for (size_t j = 0; j < Mat[i].size(); ++j)
			{
				f << Mat[i][j] << " ";
			}
			f << endl;
		}
	}
}