#include <iostream>
#include <ostream>

class vect2
{
private:
	int	v1;
	int	v2;
public:
	vect2();
	vect2(int a, int b);
	vect2(const vect2& copy);
	vect2&	operator=(const vect2& copy);
	const int&	operator[](int i) const;
	int&	operator[](int i);
	vect2	operator+(const vect2& other) const;
	vect2	operator-(const vect2& other) const;
	vect2	operator*(int s) const;
	vect2& operator+=(const vect2& other);
	vect2& operator-=(const vect2& other);
	vect2& operator*=(int s);
	vect2	operator-() const;
	vect2& operator++();
	vect2 operator++(int);
	vect2& operator--();
	vect2 operator--(int);
	bool	operator==(const vect2& other) const;
	bool	operator!=(const vect2& other) const;
	friend vect2 operator*(int s, const vect2& v);
	friend std::ostream&	operator<<(std::ostream& oss, const vect2& v);
	~vect2();
};


