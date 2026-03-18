#include <vector>
#include <iostream>
#include <ostream>
#include <algorithm>

class bigint
{
private:
	std::vector<unsigned int>	v;
public:
	bigint();
	bigint(unsigned int n);
	bigint(const bigint& copy);
	~bigint();
	bigint&	operator=(const bigint& copy);
	bigint&	operator+=(const bigint& copy);
	bigint	operator+(const bigint& copy) const;
	bigint&	operator++();
	bigint	operator++(int);
	bigint&	operator<<=(const bigint& copy);
	bigint&	operator>>=(const bigint& copy);
	bigint operator<<(const bigint& copy) const;
	bigint operator>>(const bigint& copy) const;
	bool	operator<=(const bigint& copy) const;
	bool	operator>=(const bigint& copy) const;
	bool	operator!=(const bigint& copy) const;
	bool	operator==(const bigint& copy) const;
	bool	operator>(const bigint& copy) const;
	bool	operator<(const bigint& copy) const;
	friend std::ostream& operator<<(std::ostream& os, const bigint& copy);
};
