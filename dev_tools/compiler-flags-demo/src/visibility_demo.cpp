#include "visibility_demo.hpp"

namespace
{
int internal_multiply(int left, int right)
{
    return left * right;
}
}

int public_sum(int left, int right)
{
    return left + right + internal_multiply(1, 0);
}

int hidden_subtract(int left, int right)
{
    return left - right;
}