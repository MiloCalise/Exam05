#include "bigint.hpp"

bigint::bigint()
{
    v.push_back(0);
}

bigint::bigint(unsigned int n)
{
    if (!n)
        v.push_back(0);
    for (unsigned int i = n; i > 0; i/=10)
        v.push_back(i % 10);
}

bigint::bigint(const bigint& copy)
{
    *this = copy;
}

bigint::~bigint() {}

bigint& bigint::operator=(const bigint& copy)
{
    if (this != &copy)
        v = copy.v;
    return (*this);
}

bigint& bigint::operator+=(const bigint& copy)
{
    unsigned int carry = 0;
    int max = std::max(v.size(), copy.v.size());
    for (int i = 0; i < max; i++)
    {
        unsigned int n1 = i >= (int)v.size() ? 0 : v[i];
        unsigned int n2 = i >= (int)copy.v.size() ? 0 : copy.v[i];
        if (i >= (int)v.size())
            v.push_back((n1 + n2 + carry) % 10);
        else
            v[i] = (n1 + n2 + carry) % 10;
        carry = (n1 + n2 + carry) / 10;
    }
    if (carry)
        v.push_back(carry);
    for (unsigned int i = 0; i < v.size() - 1 && v.back() == 0; i++)
        v.pop_back();
    return (*this);
}

bigint  bigint::operator+(const bigint& copy) const
{
    bigint  temp(*this);
    temp += copy;
    return (temp);
}

bigint& bigint::operator++()
{
    (*this) += bigint(1);
    return (*this);
}

bigint  bigint::operator++(int)
{
    bigint temp(*this);
    (*this) += bigint(1);
    return (temp);
}

std::ostream&   operator<<(std::ostream& os, const bigint& copy)
{
    for (int i = copy.v.size() - 1; i >= 0; i--)
        os << copy.v[i];
    return (os); 
}

bigint& bigint::operator<<=(const bigint& copy)
{
    unsigned int a = 0;

    for (int i = copy.v.size() - 1; i >= 0; i--)
        a = a * 10 + copy.v[i];
    v.insert(v.begin(), a, 0);
    for (int i = 0; i < (int)v.size() - 1 && v.back() == 0; i++)
        v.pop_back();
    return (*this);
}

bigint  bigint::operator<<(const bigint& copy) const
{
    bigint  temp(*this);
    temp <<= copy;
    return (temp);
}

bigint& bigint::operator>>=(const bigint& copy)
{
    unsigned int a = 0;

    for (int i = copy.v.size() - 1; i >= 0; i--)
        a = a * 10 + copy.v[i];
    if (a >= v.size())
    {
        v.clear();
        v.push_back(0);
        return (*this);
    }
    v.erase(v.begin(), v.begin() + a);
    for (unsigned int i = 0; i < v.size() - 1 && v.back() == 0; i++)
        v.pop_back();
    return (*this);
}

bigint  bigint::operator>>(const bigint& copy) const
{
    bigint  temp(*this);
    temp >>= copy;
    return (temp);
}

bool bigint::operator<(const bigint& other) const
{
    if (v.size() < other.v.size())
        return (1);
    if (v.size() > other.v.size())
        return (0);

    for (int i = v.size() - 1; i >= 0; i--)
    {
        if (v[i] < other.v[i])
            return (1);
        if (v[i] > other.v[i])
            return (0);
    }
    return (0);
}

bool bigint::operator>(const bigint& other) const
{
    if (v.size() > other.v.size())
        return (1);
    if (v.size() < other.v.size())
        return (0);

    for (int i = v.size() - 1; i >= 0; i--)
    {
        if (v[i] > other.v[i])
            return (1);
        if (v[i] < other.v[i])
            return (0);
    }
    return (0);
}

bool bigint::operator==(const bigint& other) const
{
    if (v.size() != other.v.size())
        return (0);

    for (size_t i = 0; i < v.size(); i++)
    {
        if (v[i] != other.v[i])
            return (0);
    }
    return (1);
}

bool bigint::operator!=(const bigint& other) const
{
    return !(*this == other);
}

bool bigint::operator<=(const bigint& other) const
{
    return !(*this > other);
}

bool bigint::operator>=(const bigint& other) const
{
    return !(*this < other);
}