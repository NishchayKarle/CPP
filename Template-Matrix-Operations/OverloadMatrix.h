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
#include <concepts>

#undef minor
using std::accumulate;
using std::array;
using std::endl;
using std::floating_point;
using std::initializer_list;
using std::max;
using std::max_element;
using std::ostream;
using std::ostringstream;
using std::setw;
using std::streamsize;
using std::unique_ptr;

namespace mpcs51044
{
	// Don't have an "arithmetic" concept yet, so demonstrating how to concept constrain with floating_point
	template <floating_point T, int rows, int cols = rows>
	class Matrix
	{
	public:
		Matrix() : data{} {}
		Matrix(initializer_list<initializer_list<T>> init)
		{
			auto dp = data.begin();
			for (auto row : init)
			{
				std::copy(row.begin(), row.end(), dp->begin());
				dp++;
			}
		}
		T &operator()(int x, int y)
		{
			return data[x][y];
		}

		T operator()(int x, int y) const
		{
			return data[x][y];
		}

		inline friend ostream &
		operator<<(ostream &os, const Matrix<T, rows, cols> &m)
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

		Matrix<T, rows - 1, cols - 1> minor(int r, int c) const
		{
			Matrix<T, rows - 1, cols - 1> result;
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

		// Defer the definition until further below to avoid
		// problems with forward references
		T determinant() const;

	private:
		static size_t accumulateMax(size_t acc, T d)
		{
			ostringstream ostr;
			ostr << d;
			return std::max(acc, ostr.str().size());
		}
		static size_t accumulateMaxRow(size_t acc, array<T, cols> row)
		{
			return std::max(acc, accumulate(row.begin(), row.end(), static_cast<size_t>(0), accumulateMax));
		}
		size_t longestElementSize() const
		{
			return accumulate(data.begin(), data.end(), 0, accumulateMaxRow);
		}
		array<array<T, cols>, rows> data;
	};

	template <floating_point T, int h, int w>
	T determinantImpl(const Matrix<T, h, w> &m)
	{
		T val = 0;
		for (int i = 0; i < h; i++)
		{
			val += (i % 2 ? -1 : 1) * m(i, 0) * m.minor(i, 0).determinant();
		}
		return val;
	}

	template <floating_point T>
	T determinantImpl(const Matrix<T, 1, 1> &m)
	{
		return m(0, 0);
	}

	template <floating_point T>
	T determinantImpl(const Matrix<T, 2, 2> &m)
	{
		return m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1);
	}

	template <floating_point T, int h, int w>
	T Matrix<T, h, w>::determinant() const
	{
		return determinantImpl(*this);
	}
	template <floating_point T, int a, int b, int c>
	inline Matrix<T, a, c>
	operator*(Matrix<T, a, b> const &l, Matrix<T, b, c> const &r)
	{
		Matrix<T, a, c> result;
		for (int i = 0; i < a; i++)
		{
			for (int j = 0; j < c; j++)
			{
				T total = 0;
				for (int k = 0; k < b; k++)
					total += l(i, k) * r(k, j);
				result(i, j) = total;
			}
		}
		return result;
	}

}
#endif