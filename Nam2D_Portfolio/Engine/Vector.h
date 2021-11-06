#pragma once

#include <cmath>

#include "Matrix.h"

template<size_t n>
using Vector = Matrix<1, n>;

template<size_t n>
inline float Dot(Vector<n> const & one, Vector<n> const & other)
{
    return one * reinterpret_cast<Matrix<n, 1> const &>(other);
}

template<size_t n>
inline float Length(Vector<n> const & one)
{
    return sqrtf(Dot(one, one));
}

template<size_t n>
inline Vector<n> Normalize(Vector<n> const & one)
{
    return one / Length(one);
}

inline Vector<3> Cross(Vector<3> const & one, Vector<3> const & other)
{
    Vector<3> product = Vector<3>();

    for(size_t u = 0; u < 3; ++u)
    {
        size_t v = (u + 1) % 3;
        size_t w = (v + 1) % 3;

        product[u] = one[v] * other[w] - one[w] * other[v];
    }

    return product;
}