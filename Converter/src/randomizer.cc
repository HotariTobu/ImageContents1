// Created by guinpen98

#include "../include//randomizer.h"

#include <algorithm>
#include <random>

template<typename T>
void Randomize(T& container) {
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  std::shuffle(std.begin(container), std.end(container), engine);
}