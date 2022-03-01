#ifndef UTILS_H
#define UTILS_H

#include<vector>
#include<cmath>
#include<iostream>

using vector2d = std::vector<std::vector<double>>;

template<typename T, typename T2>
extern T add(const T& array1, const T2& array2);

extern vector2d add(const vector2d& array1, const std::vector<double>& array2);

extern double dot(const std::vector<double>& vec1, const std::vector<double>& vec2);

extern vector2d dot(const vector2d& array1, const vector2d& array2);

extern void print1d(const std::vector<double>& vec);

extern void print2d(const vector2d& vec2d);

extern std::vector<double> sum(const std::vector<double>& vec1, const std::vector<double>& vec2);

extern vector2d sum(const vector2d& vec1, const vector2d& vec2);

extern std::vector<double> activationReLu(const std::vector<double>& inputs);

extern vector2d activationReLu(const vector2d& inputs);
extern double max(const std::vector<double>& arr);

extern std::vector<double> exp(const std::vector<double>& outputs);

extern vector2d exp(const vector2d& outputs);
extern double sum(const std::vector<double>& vec);
extern std::vector<double> sum(const vector2d& vec);

extern vector2d divideVec(const vector2d& arr2d, const std::vector<double>& arr1d);

extern std::vector<double> getTarget(const vector2d& output, const std::vector<double>& targetOutput);

extern std::vector<double> negLog(const std::vector<double>& vec);

extern vector2d multi(const vector2d& vec1, const vector2d& vec2);

extern std::vector<double> sumAndMultiply(const vector2d& vec1, const vector2d& vec2);

extern double mean(std::vector<double> vec);

extern double calcLossCCE(const vector2d& output, const std::vector<double>& expected);

extern double calcLossCCE(const vector2d& output, const vector2d& expected);

extern vector2d activationSoftmax(const vector2d& inputs);

#endif