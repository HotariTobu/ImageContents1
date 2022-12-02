// Created by HotariTobu

#include <iostream>
#include <string>

#include "../include/attribute.h"

using namespace std;

int main() {
    Color color(1, 1, 1);
    Attribute attribute(3.14, color);
    cout << ' ' << attribute << endl;

    for (int i = 0; i < 100; i++) {
        double h = i / 100.0;
        Color c(h, 1, 1);

        cout << c.r << '\t' << c.g << '\t' << c.b << endl;
    }
    
}