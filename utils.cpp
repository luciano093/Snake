#include"Layers/Utils.h"

template<typename T, typename T2>
T add(const T& array1, const T2& array2) {
	std::vector<double> sum;
	int size = 0;

	for (auto i : array1) {
		++size;
	}

	for (int i = 0; i < size; ++i) {
		sum.push_back(array1[i] + array2[i]);
	}

	return sum;
}

vector2d add(const vector2d& array1, const std::vector<double>& array2) {
	vector2d result;

	for (int i = 0; i < array1.size(); ++i) {
		std::vector<double> sum = add(array1[i], array2);
		result.push_back(sum);
	}

	return result;
}

double dot(const std::vector<double>& vec1, const std::vector<double>& vec2) {
	double sum = 0;

	for (int i = 0; i < vec1.size(); ++i) {
		sum += vec1[i] * vec2[i];
	}

	return sum;
}

vector2d dot(const vector2d& array1, const vector2d& array2) {
	vector2d result;

	for (int i = 0; i < array1.size(); ++i) {
		std::vector<double> vec;

		for (int j = 0; j < array2.size(); ++j) {
			vec.push_back(dot(array1[i], array2[j]));
		}
		result.push_back(vec);
	}

	return result;
}

void print1d(const std::vector<double>& vec) {
	for (auto i : vec) {
		std::cout << i << " ";
	}
	std::cout << "\n";
}

void print2d(const vector2d& vec2d) {
	for (auto vec : vec2d) {
		print1d(vec);
	}
}

std::vector<double> sum(const std::vector<double>& vec1, const std::vector<double>& vec2) {
	std::vector<double> result;

	for (int i = 0; i < vec1.size(); ++i) {
		result.push_back(vec1[i] + vec2[i]);
	}

	return result;
}

vector2d sum(const vector2d& vec1, const vector2d& vec2) {
	vector2d result;

	for (int i = 0; i < vec1.size(); ++i) {
		std::vector<double> tempVec;

		for (int j = 0; j < vec1[0].size(); ++j) {
			tempVec.push_back(vec1[i][j] + vec2[i][j]);
		}
		result.push_back(tempVec);
	}

	return result;
}

std::vector<double> activationReLu(const std::vector<double>& inputs) {
	std::vector<double> result;

	for (const double& i : inputs) {
		result.push_back((i > 0) ? i : 0);
	}

	return result;
}

vector2d activationReLu(const vector2d& inputs) {
	vector2d result;

	for (int i = 0; i < inputs.size(); ++i) {
		result.push_back(activationReLu(inputs[i]));
	}

	return result;
}

double max(const std::vector<double>& arr) {
	double maxNum = arr[0];

	for (const double& d : arr) {
		if (maxNum < d) maxNum = d;
	}

	return maxNum;
}

std::vector<double> exp(const std::vector<double>& outputs) {
	std::vector<double> result;

	for (int i = 0; i < outputs.size(); ++i) {
		result.push_back(std::exp(outputs[i] - max(outputs)));
	}

	return result;
}

vector2d exp(const vector2d& outputs) {
	vector2d result;

	for (int i = 0; i < outputs.size(); ++i) {
		result.push_back(exp(outputs[i]));
	}

	return result;
}

double sum(const std::vector<double>& vec) {
	double sum = 0;

	for (int i = 0; i < vec.size(); ++i) {
		sum += vec[i];
	}

	return sum;
}

std::vector<double> sum(const vector2d& vec) {
	std::vector<double> vecSum;

	for (int i = 0; i < vec.size(); ++i) {
		vecSum.push_back(sum(vec[i]));
	}

	return vecSum;
}

vector2d divideVec(const vector2d& arr2d, const std::vector<double>& arr1d) {
	vector2d result;

	for (int i = 0; i < arr2d.size(); ++i) {
		std::vector<double> vec;

		for (int j = 0; j < arr2d[0].size(); ++j) {
			vec.push_back(arr2d[i][j] / arr1d[i]);
		}

		result.push_back(vec);
	}

	return result;
}

vector2d activationSoftmax(const vector2d& inputs) {
	vector2d expValues = exp(inputs);
	vector2d probabilities = divideVec(expValues, sum(expValues));

	return probabilities;
}

std::vector<double> getTarget(const vector2d& output, const std::vector<double>& targetOutput) {
	std::vector<double> result;

	for (int i = 0; i < targetOutput.size(); ++i) {
		result.push_back(output[i][targetOutput[i]]);
	}

	return result;
}

std::vector<double> negLog(const std::vector<double>& vec) {
	std::vector<double> result;

	for (const double& d : vec) {
		result.push_back(-std::log(d));
	}

	return result;
}

vector2d multi(const vector2d& vec1, const vector2d& vec2) {
	vector2d result;

	for (int i = 0; i < vec1.size(); ++i) {
		std::vector<double> vec;

		for (int j = 0; j < vec1[0].size(); ++j) {
			vec.push_back(vec1[i][j] * vec2[i][j]);
		}
		result.push_back(vec);
	}

	return result;
}

std::vector<double> sumAndMultiply(const vector2d& vec1, const vector2d& vec2) {
	vector2d multiVec = multi(vec1, vec2);

	std::vector<double> result = sum(multiVec);

	return result;
}

double mean(std::vector<double> vec) {
	double vecSum = sum(vec);

	return vecSum / vec.size();
}

double calcLossCCE(const vector2d& output, const std::vector<double>& expected) {
	std::vector<double> correctConfidence = getTarget(output, expected);
	std::vector<double> negLogLikelyhood = negLog(correctConfidence);

	double result = mean(negLogLikelyhood);

	return result;
}

double calcLossCCE(const vector2d& output, const vector2d& expected) {
	std::vector<double> correctConfidence = sumAndMultiply(output, expected);
	std::vector<double> negLogLikelyhood = negLog(correctConfidence);

	double result = mean(negLogLikelyhood);

	return result;
}