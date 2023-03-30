#ifndef MATRIX_H
#define MATRIX_H
#include <initializer_list>
#include <algorithm>
#include <array>
#include <memory>
#include <numeric>
#include <iostream>
#include <sstream>
#include <iomanip>

#undef minor // Some compilers have a macro named minor

using std::accumulate;
using std::array;
using std::endl;
using std::initializer_list;
using std::inner_product;
using std::max;
using std::max_element;
using std::ostream;
using std::ostringstream;
using std::setw;
using std::streamsize;
using std::unique_ptr;

namespace mpcs51044
{

	template <int rows, int cols = rows>
	class Matrix
	{
	public:
		Matrix() : data{} {}
		Matrix(initializer_list<initializer_list<double>> init)
		{
			auto dp = data.begin();
			for (auto row : init)
			{
				std::copy(row.begin(), row.end(), dp->begin());
				dp++;
			}
		}
		double &operator()(int x, int y)
		{
			return data[x][y];
		}

		double operator()(int x, int y) const
		{
			return data[x][y];
		}

		inline friend ostream &
		operator<<(ostream &os, const Matrix<rows, cols> &m)
		{
			size_t width = m.longestElementSize() + 2;
			os << "[ " << endl;
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					os << setw(static_cast<streamsize>(width)) << m(i, j);
				}
				os << endl;
			}
			os << "]" << endl;
			return os;
		}

		Matrix<rows - 1, cols - 1> minor(int r, int c) const
		{
			Matrix<rows - 1, cols - 1> result;
			for (int i = 0; i < rows; i++)
			{
				if (i == r)
				{
					continue;
				}
				for (int j = 0; j < cols; j++)
				{
					if (j == c)
					{
						continue;
					}
					result(i < r ? i : i - 1, j < c ? j : j - 1) = data[i][j];
				}
			}
			return result;
		}

		double determinant() const
		{
			double val = 0;
			for (int i = 0; i < rows; i++)
			{
				val += (i % 2 ? -1 : 1) * data[i][0] * minor(i, 0).determinant();
			}
			return val;
		}

		inline void
		operator+=(Matrix<rows, cols> const &r)
		{
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++)
					data[i][j] += r(i, j);
		}

	private:
		static size_t accumulateMax(size_t acc, double d)
		{
			ostringstream ostr;
			ostr << d;
			return std::max(acc, ostr.str().size());
		}
		static size_t accumulateMaxRow(size_t acc, array<double, cols> row)
		{
			return std::max(acc, accumulate(row.begin(), row.end(), static_cast<size_t>(0), accumulateMax));
		}
		size_t longestElementSize() const
		{
			return accumulate(data.begin(), data.end(), 0, accumulateMaxRow);
		}
		array<array<double, cols>, rows> data;
	};

	template <>
	double
	Matrix<1, 1>::determinant() const
	{
		return data[0][0];
	}

	template <>
	double
	Matrix<2, 2>::determinant() const
	{
		return data[0][0] * data[1][1] - data[1][0] * data[0][1];
	}

	template <int a, int b, int c>
	inline Matrix<a, c>
	operator*(Matrix<a, b> const &l, Matrix<b, c> const &r)
	{
		Matrix<a, c> result;
		for (int i = 0; i < a; i++)
		{
			for (int j = 0; j < c; j++)
			{
				double total = 0;
				for (int k = 0; k < b; k++)
					total += l(i, k) * r(k, j);
				result(i, j) = total;
			}
		}
		return result;
	}

	template <int a, int b>
	inline Matrix<a, b>
	operator+(Matrix<a, b> const &l, Matrix<a, b> const &r)
	{
		Matrix<a, b> result;
		for (int i = 0; i < a; i++)
			for (int j = 0; j < b; j++)
				result(i, j) = l(i, j) + r(i, j);

		return result;
	}

}
#endif