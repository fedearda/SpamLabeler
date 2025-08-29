// this module is used to calculate the relevance of each feature based on information gain
// it will be useful in order to define the order of features that appear on the binary decision tree
// highest information gain -> first node
//          ...             -> i-th node
// lowest information gain  -> last node
#include "decisionTree.hpp"
#include <cmath>
#include <iostream>

extern std::vector<double> thresholdList;
extern vector<string> featureNames;

vector<vector<double>> data1 = {
                                // Trusted contacts → Mostly not spam, but some spam
                                {0, 2, 30.0, 0, 1, 7},   // Not spam
                                {0, 5, 75.0, 1, 1, 6},   // Spam
                                {0, 1, 20.0, 0, 0, 9},   // Not spam
                                {0, 4, 65.0, 1, 0, 5},   // Spam
                                {0, 0, 10.0, 0, 0, 10},  // Not spam

                                // Untrusted contacts → Mostly spam, but some not spam
                                {1, 6, 85.0, 1, 1, 2},   // Spam
                                {1, 3, 50.0, 0, 0, 6},   // Not spam
                                {1, 7, 90.0, 1, 1, 1},   // Spam
                                {1, 2, 40.0, 0, 0, 8},   // Not spam
                                {1, 5, 80.0, 1, 0, 3}    // Spam
                            };

vector<string> labels1 = {"Not spam",
                        "Spam",
                        "Not spam",
                        "Spam",
                        "Not spam",
                        "Spam",
                        "Not spam",
                        "Spam",
                        "Not spam",
                        "Spam"};

/* The entropy of a status is defined as - log2 (p) , where p is the probability that the status happens. In a binary decision tree,
 there are two status for each feature, i.e. triggered or not triggered. The entropy to be computed is the weighted average of the entropies 
 of the two states. */
double computeEntropy(vector<string>& groupLabels){
    int countSpam {0};
    for (auto label : groupLabels) if (label == "Spam") ++countSpam;
    double p_spam = double(countSpam) / double(groupLabels.size());
    double p_nspam = 1.0 - p_spam;
    double entropy = 0.0;
    if (p_spam > 0.0) entropy -= p_spam * log2(p_spam);
    if (p_nspam > 0.0) entropy -= p_nspam * log2(p_nspam);
    return entropy;
}
/* The purpose of this function is to compute the information gain for a single feature. This returns the amount of knowledge we gain
 on the output by knowing the selected feature. I.e. : difference in entropy (before knowing the feature status minus after). */
double computeInformationGain(vector<vector<double>>& data, vector<string>& labels, int featureIndex, double startEntropy){
    // infoGain = Entropy before - Entropy after

    // Split the data into two groups based on the threshold
    vector<vector<double>> leftData, rightData;
    vector<string> leftLabels, rightLabels;
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i][featureIndex] < thresholdList[featureIndex]) {
            leftData.push_back(data[i]);
            leftLabels.push_back(labels[i]);
        } else {
            rightData.push_back(data[i]);
            rightLabels.push_back(labels[i]);
        }
    }

    // Compute the entropy for each group
    double entropy_left = computeEntropy(leftLabels);
    double entropy_right = computeEntropy(rightLabels);

    // Compute the weighted average of the entropy
    double entropy_after = (double(leftLabels.size()) * entropy_left + double(rightLabels.size()) * entropy_right) / double(labels.size());

    // Compute the information gain
    double infoGain = startEntropy - entropy_after;

    return infoGain;
}

void printGainArray(unordered_map<string,double> input){
    for(auto e : input){
        cout << e.first << " -- > " << e.second << endl;
    }
}


int main (){
    // Entropy before = pspam * log2(psmap) + pnotspam * log2(pnotspam)
    double entropy_0 = computeEntropy(labels1);

    //i want to create a data structure that pairs the feature with the information gain of that feature
    unordered_map<string,double> infoGainMap;
    for (int i = 0; i < data1[0].size(); ++i) {
        infoGainMap.insert(make_pair(featureNames[i],computeInformationGain(data1, labels1, i, entropy_0)));
    }
    printGainArray(infoGainMap);
    cin.get();
}

