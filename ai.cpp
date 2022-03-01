#include"Ai.h"

#include<random>
#include<ctime>

std::default_random_engine generator;
std::uniform_real_distribution<double> distribution;

Layer getOffspring(const Layer& layer1, const Layer& layer2) {
	Layer result = layer1;
	generator.seed(std::time(nullptr));
	distribution = std::uniform_real_distribution<double>(-1, 1);

	for (int i = 0; i < layer1.weights.size(); i++) {
		int choice = distribution(generator);
		result.weights[i] = ((choice >= 0) ? layer1.weights[i] : layer2.weights[i]);
	}

	for (int i = 0; i < layer1.biases.size(); ++i) {
		int choice = distribution(generator);
		result.biases[i] = ((choice >= 0) ? layer1.biases[i] : layer2.biases[i]);
	}

	return result;
}

namespace Ai {
	double bestFitness = 0;

	std::vector<std::pair<std::vector<Layer>, double>> snakes;

	double calcFitness(const int& steps, const int& score) {
		double result = steps + (std::pow(2, score) + (std::pow(score, 2.1) * 500));
		result -= (std::pow(score, 1.2) * std::pow((0.25 * steps), 1.3));
		return result;
	}

	void adjustLayers(Layer& layer1, Layer& layer2) {
		int bestIndex = 0;
		int secondBestIndex = 0;

		for (int i = 0; i < snakes.size(); ++i) {
			if (snakes[i].second > bestFitness) {
				bestFitness = snakes[i].second;
				bestIndex = i;
			}
		}

		for (int i = 0; i < snakes.size(); ++i) {
			if (snakes[i].second > bestFitness && i != bestIndex) {
				secondBestIndex = i;
			}
		}

		layer1 = getOffspring(snakes[bestIndex].first[0], snakes[secondBestIndex].first[0]);
		layer2 = getOffspring(snakes[bestIndex].first[1], snakes[secondBestIndex].first[1]);

		snakes.clear();
	}
}