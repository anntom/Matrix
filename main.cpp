#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "Matrix.h"

using namespace std;

bool read(MatrixType &mat, const char * path)
{
	ifstream f(path);
	if (f.is_open())
	{
		std::string buf;
		float a;
		vector<float> vec;
		int i = 0;
		while (getline(f, buf))
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
					cout << "incorrect data in file: " << path << endl;
					return false;
				}
			}
			if ( i > 0 && mat[i-1].size() != vec.size())
			{
				cout << "incorrect data in file: " << path << endl;
				return false;
			}
			i++;
			mat.push_back(vec);
		}
		return true;
	}
	else
	{
		cout << "Can't open file: " << path << endl;
		return false;
	}
}

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		cout << "Enter path to file" << endl;
		return -1;
	}
	else
	{
		string path1 = argv[1];
		string path2 = argv[2];
		MatrixType mat1, mat2;
		if (read(mat1, path1.c_str()) && read(mat2, path2.c_str()))
		{
			Matrix res = Matrix(mat1) * Matrix(mat2);
			res.print();
		} 
		else
		{
			return -1;
		}
	}
	return 0;
}