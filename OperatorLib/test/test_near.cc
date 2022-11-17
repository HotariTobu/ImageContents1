// Created by HotariTobu

#include <cassert>
#include <limits>

#include "near.h"

using namespace std;

int main() {
    constexpr double nan = numeric_limits<double>::quiet_NaN();

    assert(!Near(nan, nan));
    assert(Near(1.0, 1.00000000000001));
    assert(!Near(nan, 1.0));
    assert(!Near(1.0, 2.0));
}