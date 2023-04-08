#include <vector>
#include <algorithm>

/**
 * Computes the weights for each value in the vector using a linear scaling
 * Time Complexity: O(n) being n the number of values
 * @param values Vector of values
 * @param weights Vector of weights
 * @return The sum of the weights to be used to compute the average
 */
float computeWeights(const std::vector<int>& values, std::vector<float> &weights) {
    int maxVal = *std::max_element(values.begin(), values.end());
    int minVal = *std::min_element(values.begin(), values.end());

    float weightSum = 0;

    for (int i = 0; i < values.size(); i++) {
        if (maxVal == minVal) {
            weights[i] = 1.0 / values.size();
        } else {
            weights[i] = (values[i] - minVal) / static_cast<float>(maxVal - minVal);
        }
        weightSum += weights[i];
    }

    return weightSum;
}