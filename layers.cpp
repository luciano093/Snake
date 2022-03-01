#include"Layers/Layer.h"

Layer::Layer(int inputNum, int neuronNum) : inputNum(inputNum), neuronNum(neuronNum), distribution(-0.1, 0.1) {
	populateArray(neuronNum, inputNum);
	populateBiases(neuronNum);
}

vector2d Layer::forward(const vector2d& inputs) {
	return add(dot(inputs, weights), biases);
}

void Layer::setRandomWeights() {
	populateArray(neuronNum, inputNum);
}

void Layer::setRandomBiases() {
	populateBiases(neuronNum);
}

void Layer::adjustWeights() {
	weights = sum(weights, getRandomWeights(neuronNum, inputNum));
}

void Layer::adjustBiases() {
	biases = sum(biases, getRandomBiases(neuronNum));
}

vector2d Layer::getRandomWeights(const int& rows, const int& cols) {
	generator.seed(std::time(nullptr));
	vector2d result;

	for (int i = 0; i < rows; ++i) {
		std::vector<double> vec;

		for (int j = 0; j < cols; ++j) {
			vec.push_back(distribution(generator));
		}
		result.push_back(vec);
	}

	return result;
}

void Layer::populateArray(const int& rows, const int& cols) {
	weights = getRandomWeights(rows, cols);
}

std::vector<double> Layer::getRandomBiases(const int& size) {
	generator.seed(std::time(nullptr));
	std::vector<double> result;

	for (int i = 0; i < size; ++i) {
		result.push_back(distribution(generator));
	}

	return result;
}

void Layer::populateBiases(const int& size) {
	biases = getRandomBiases(size);
}