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

  void backwardPass(const std::vector<double>& input,
		    const std::vector<double>& target,
		    const std::vector<double>& outputValues,
		    double learningRate) {

    std::vector<double> outputErrors(outputValues.size());
    for (size_t i = 0; i < outputValues.size(); ++i) {
      outputErrors[i] = target[i] - outputValues[i];
    }

    std::vector<double> outputGradients(outputValues.size());
    for (size_t i = 0; i < outputValues.size(); ++i) {
      outputGradients[i] = outputErrors[i] * sigmoid_deriv(outputValues[i]);
    }

    for (size_t i = 0; i < hiddenBiases.size(); ++i) {
      outputBiases[i] += learningRate * outputGradients[i];
      for (size_t j = 0; j < hiddenOutputWeights.size(); ++j) {
        hiddenOutputWeights[j][i] += learningRate * outputGradients[i] * hiddenValues[j];
      }
    }

    std::vector<double> hiddenErrors(hiddenValues.size());
    for (size_t i = 0; i < hiddenValues.size(); ++i) {
      double sum = 0.0;
      for (size_t j = 0; j < outputValues.size(); ++j) {
        sum += outputGradients[j] * hiddenOutputWeights[i][j];
      }
      hiddenErrors[i] = sum;
    }

    std::vector<double> hiddenGradients(hiddenValues.size());
    for (size_t i = 0; i < hiddenValues.size(); ++i) {
      hiddenGradients[i] = hiddenErrors[i] * sigmoid_deriv(hiddenValues[i]);
    }

    for (size_t i = 0; i < input.size(); ++i) {
      for (size_t j = 0; j < outputValues.size(); ++j) {
        inputHiddenWeights[i][j] += learningRate * hiddenGradients[j] * input[i];
      }    
    }

    for (size_t i = 0; i < input.size(); ++i) {
      hiddenBiases[i] += learningRate * hiddenGradients[i];                     
    }

  }

};

int main() {
  NeuralNetwork neuralNetwork(4, 3, 2);

  std::vector<double> input = {0, 1, 0, 1};

  std::vector<double> target = {1, 0};

  std::vector<double> output = neuralNetwork.forwardPass(input);

  std::cout << "Output:";
  for (const double& val : output) {
    std::cout << val << " ";
  }

  std::cout<<std::endl;

  return 0;
};  
