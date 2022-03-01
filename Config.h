#ifndef CONFIG_H
#define CONFIG_H

#include<array>
#include"EntityType.h"

constexpr int GRID_SIZE = 5;

typedef std::array<std::array<EntityType, GRID_SIZE>, GRID_SIZE> array2d;

#endif