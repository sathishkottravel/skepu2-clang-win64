#include <iostream>
#include <iostream>
#include <utility>
#include <cfloat>
#include <algorithm>
#include <chrono>
#include <ctime>

#define NOMINMAX

#include <skepu2.hpp>

template<typename T>
T mult(T a, T b)
{
#if SKEPU_USING_BACKEND_CPU
    std::cout << "Mult " << a << " and " << b << "\n";
#endif
    return a * b;
}

template<typename T>
T add(T a, T b)
{
    return a + b;
}

float dotproduct(skepu2::Vector<float> &a, skepu2::Matrix<float> &b)
{
    auto dotprod = skepu2::MapReduce<2>(mult<float>, add<float>);
    
    return dotprod(a, b);
}

int main(int argc, char *argv[])
{
    size_t size = 16;
    auto spec = skepu2::BackendSpec();

    if (argc < 3)
    {
        std::cout << "Usage: " << argv[0] << " size backend\n";
        //exit(1);
    }
    else {
        size = atoi(argv[1]);
        spec = skepu2::BackendSpec{ skepu2::Backend::typeFromString(argv[2]) };
    }
    
    
    skepu2::Vector<float> a(size), b(size);
    skepu2::Matrix<float> c(sqrt(size), sqrt(size));
    a.randomize(0, 3);
    b.randomize(0, 2);
    c.randomize(0, 5);
    
    std::cout << a << "\n";
    std::cout << c << "\n";
    
    float res = dotproduct(a, c);
    
    std::cout << res << "\n";
    
    
    return 0;
}

