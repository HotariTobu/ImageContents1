// Created by guinpen98

#include "../include//randomizer.h"

#include <algorithm>
#include <random>

void Randomize(std::vector<Point2d>& points) {
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  std::shuffle(points.begin(), points.end(), engine);
}