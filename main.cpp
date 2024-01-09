#include<iostream>
#include<vector>
#include<cmath>
#include<cstdlib>
#include<ctime>

class NeuralNetwork {
private:
  std::vector<std::vector<double>> inputHiddenWeights;
  std::vector<std::vector<double>> hiddenOutputWeights;
  std::vector<double> hiddenBiases;
  std::vector<double> outputBiases;

public:
  NeuralNetwork(int inputSize, int hiddenSize, int outputSize)
	  : inputHiddenWeights(inputSize, std::vector<double>(hiddenSize)),
	    hiddenOutputWeights(hiddenSize, std::vector<double>(outputSize)),
	    hiddenBiases(hiddenSize),
	    outputBiases(outputSize) {
	
	initializeRandomWeights();

  }
   
  void initializeRandomWeights() {
	srand(static_cast<unsigned>(time(nullptr)));
        for (auto& row : inputHiddenWeights) {
	  for (double& weight : row) {
	    weight = (2.0 * rand() / RAND_MAX) - 1.0;
	  }
	}

	for (auto& row : hiddenOutputWeights) {
	  for (double& weight : row) {
	    weight = (2.0 * rand() / RAND_MAX) - 1.0;
	  }
	}

	for (double& bias : hiddenBiases) {
	  bias = (2.0 * rand() / RAND_MAX) - 1.0;
	}

        for (double& bias : outputBiases) {
          bias = (2.0 * rand() / RAND_MAX) - 1.0;
        }
  }

  double sigmoid(double x) {
	  return 1.0 / (1.0 + std::exp(-x));
  }

  double sigmoid_deriv(double x) {
    double sig = sigmoid(x);
    return sig * (1.0 - sig);
  }

  std::vector<double> forwardPass(const std::vector<double>& input) {
    std::vector<double> hiddenValues(inputHiddenWeights[0].size());
    std::vector<double> outputValues(hiddenOutputWeights[0].size());

    for (size_t i = 0; i < hiddenValues.size(); ++i) {
      hiddenValues[i] = 0;
      for (size_t j = 0; j < input.size(); ++j) {
        hiddenValues[i] += input[j] * inputHiddenWeights[j][i];
      }

      hiddenValues[i] = sigmoid(hiddenValues[i] + hiddenBiases[i]);

    }

    for (size_t i = 0; i < outputValues.size(); ++i) {
      outputValues[i] = 0;
      for (size_t j = 0; j < hiddenValues.size(); ++j) {
        outputValues[i] += hiddenValues[j] * hiddenOutputWeights[j][i];
      }

      outputValues[i] = sigmoid(outputValues[i] + outputBiases[i]);

    }

    return outputValues;

  }

};

int main() {
  NeuralNetwork neuralNetwork(4, 3, 2);

  std::vector<double> input = {0, 1, 0, 1};

  std::vector<double> output = neuralNetwork.forwardPass(input);

  std::cout << "Output:";
  for (const double& val : output) {
    std::cout << val << " ";
  }

  std::cout<<std::endl;

  return 0;
};  
