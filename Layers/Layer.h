#ifndef LAYER_H
#define LAYER_H

#include<random>
#include<ctime>
#include<vector>
#include"Utils.h"

class Layer {
public:
	Layer() = default;
	Layer(int inputNum, int neuronNum);

	vector2d forward(const vector2d& inputs);

	void setRandomWeights();
	void setRandomBiases();
	void adjustWeights();
	void adjustBiases();

	vector2d weights;
	std::vector<double> biases;

private:
	int inputNum, neuronNum;
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution;

	vector2d getRandomWeights(const int& rows, const int& cols);

	void populateArray(const int& rows, const int& cols);

	std::vector<double> getRandomBiases(const int& size);

	void populateBiases(const int& size);
};

#endif