// Created by HotariTobu

#include <cassert>
#include <limits>

#include "equals.h"

using namespace std;

int main() {
    constexpr double nan = numeric_limits<double>::quiet_NaN();

    assert(Equals(nan, nan));
    assert(Equals(1.0, 1.0));
    assert(!Equals(nan, 1.0));
    assert(!Equals(1.0, 2.0));
}