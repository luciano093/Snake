#ifndef AI_H
#define AI_H

#include<utility>
#include"Layers/Layer.h"

namespace Ai {
	extern double bestFitness;
	extern std::vector<std::pair<std::vector<Layer>, double>> snakes;

	extern double calcFitness(const int& steps, const int& score);
	extern void adjustLayers(Layer& layer1, Layer& layer2);
}

#endif
