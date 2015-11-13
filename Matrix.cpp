#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <omp.h>
#include <sstream>

Matrix Matrix::operator*(Matrix const &mat) const
{
	Matrix MatRes;
	MatRes.Mat.resize(Mat.size());
	if (Mat[0].size() != mat.Mat.size())
	{
		throw MyException("Sizes doesn't match");
	}
	int ij, i, j;
	for ( int i = 0; i < mat.Mat[0].size(); i++ )
	{
		MatRes.Mat[i].resize(mat.Mat[0].size());
	}
	#pragma omp parallel
	{
		#pragma omp for private (ij , i, j) schedule(dynamic, 1)
		for (ij = 0; ij < Mat.size() * mat.Mat[0].size(); ij++ )
		{
			i = ij / Mat.size();
			j = ij % mat.Mat[0].size();
			float sum = 0;
			for (int k = 0; k < Mat[0].size(); ++k)
			{
				sum += Mat[i][k] * mat.Mat[k][j];
			}
			MatRes.Mat[i][j] = sum;
			sum = 0;
		}	
	}
	return MatRes;
}

ifstream& operator>>(ifstream &in, Matrix & mat)
{
	std::string buf;
		float a;
		vector<float> vec;
		int i = 0;
		while (getline(in, buf))
		{
			vec.clear();
			stringstream ss(buf);
			while (ss >> a)
			{
				if (ss.good() || ss.eof())
				{
					vec.push_back(a);
				} 
				else
				{
					throw MyException("incorrect data");
				}
			}
			if ( i > 0 && mat.Mat[i-1].size() != vec.size())
			{
				throw MyException("incorrect data");
			}
			i++;
			mat.Mat.push_back(vec);
		}
		return in;
}

ofstream& operator<<(ofstream &out, Matrix & mat)
{
	for (size_t i = 0; i < mat.Mat.size(); ++i)
		{
			for (size_t j = 0; j < mat.Mat[i].size(); ++j)
			{
				out << mat.Mat[i][j] << " ";
			}
			out << endl;
		}
	return out;
}