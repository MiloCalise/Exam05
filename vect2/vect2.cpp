#include "vect2.hpp"

vect2::vect2() : v1(0), v2(0) {}

vect2::vect2(int a, int b) : v1(a), v2(b) {}

vect2::vect2(const vect2& copy)
{
	*this = copy;
}

vect2::~vect2() {}

vect2&	vect2::operator=(const vect2& copy)
{
	if (this != &copy)
	{
		v1 = copy.v1;
		v2 = copy.v2;
	}
	return (*this);
}

int&	vect2::operator[](int i)
{
	if (!i)
		return (v1);
	else
		return (v2);
}

const int& vect2::operator[](int i) const
{
	if (!i)
		return (v1);
	else
		return (v2);
}

std::ostream&	operator<<(std::ostream& os, const vect2& v)
{
	os << "{" << v.v1 << ", " << v.v2 << "}";
	return (os);
}

vect2	vect2::operator+(const vect2& other) const
{
	vect2	v(*this);
	v += other;
	return (v);
}

vect2	vect2::operator-(const vect2& other) const
{
	vect2	v(*this);
	v -= other;
	return (v);
}

vect2	vect2::operator*(int s) const
{
	vect2	v(*this);
	v *= s;
	return (v);
}

vect2& vect2::operator+=(const vect2& other)
{
	v1 = v1 + other.v1;
	v2 = v2 + other.v2;
	return (*this);
}

vect2&	vect2::operator-=(const vect2& other)
{
	v1 = v1 - other.v1;
	v2 = v2 - other.v2;
	return (*this);
}

vect2& vect2::operator*=(int s)
{
	v1 = v1 * s;
	v2 = v2 * s;
	return (*this);
}

vect2	vect2::operator-() const
{
	vect2	v(*this);
	v.v1 = v.v1 * -1;
	v.v2 = v.v2 * -1;
	return (v);
}

vect2&	vect2::operator++()
{
	++v1;
	++v2;
	return (*this);
}

vect2	vect2::operator++(int)
{
	vect2 temp = *this;
	++v1;
	++v2;
	return (temp);
}

vect2&	vect2::operator--()
{
	--v1;
	--v2;
	return (*this);
}

vect2	vect2::operator--(int)
{
	vect2 temp = *this;
	--v1;
	--v2;
	return (temp);
}

bool	vect2::operator!=(const vect2& other) const
{
	return (v1 != other.v1 || v2 != other.v2);
}

bool	vect2::operator==(const vect2& other) const
{
	return (v1 == other.v1 && v2 == other.v2);
}

vect2	operator*(int s, const vect2& other)
{
	vect2	v;
	v.v1 = s * other.v1;
	v.v2 = s * other.v2;
	return (v);
}
