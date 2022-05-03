#pragma once
#include <GL/gl.h>
#include <stddef.h>

template<typename T, size_t N>
struct Vector
{
	T v[N];

	operator T const*() const
	{
		return v;
	}

	Vector & operator *=(T factor)
	{
		for (size_t i = 0; i < N; ++i)
		{
			v[i] *= factor;
		}
		return *this;
	}
	Vector & operator +=(Vector const& other)
	{
		for (size_t i = 0; i < N; ++i)
		{
			v[i] += other.v[i];
		}
		return *this;
	}

	T & operator [](size_t index)
	{
		return v[index];
	}
	T const& operator [](size_t index) const
	{
		return v[index];
	}
};
typedef Vector<GLfloat, 2> Vector2f;
typedef Vector<GLint, 2> Vector2i;

template<typename T, size_t N>
Vector<T, N> operator *(T lhs, Vector<T, N> const& rhs)
{
	return Vector<T, N>(rhs) *= lhs;
}

template<typename T, size_t N>
Vector<T, N> operator +(Vector<T, N> const& lhs, Vector<T, N> const& rhs)
{
	return Vector<T, N>(lhs) += rhs;
}
