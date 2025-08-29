#include <iostream>
#include "structures.hpp"
#include "decisionTree.hpp"
#include "toolBox.hpp"
#include "dataExtractor.hpp"

vector<string> trustedContacts = readContacts(CONTACTLIST_PATH);
vector<string> suspiciousWords = readWords(SUSPICIOUSWORDS_PATH);
unordered_map<string,double> peopleList = readPeople(REPUTATIONLIST_PATH);

vector<email> emailList = readEmail(EMAILS_PATH);

int main(){
    Node* spamDetector = buildTree();

    vector<vector<double>> featuresList {};

    for (auto &m: emailList) featuresList.push_back(featureExtract(m,trustedContacts,suspiciousWords,peopleList));

    for (int i = 0; i < emailList.size(); ++i) {
    auto &m = emailList[i];
    cout << "Email " << i+1 << " sender: " << m._sender << endl;
    cout << "Email " << i+1 << " subject: " << m._object << endl;
    cout << "Email " << i+1 << " attachment: " << m._attachment << endl;
    cout << "Email " << i+1 << " body: " << m._body << endl;
    cout << "----" << endl;
}


    for (int i{0}; i<featuresList.size(); ++i) {
    cout << "Email " << i+1 << " features: ";
    for (double f : featuresList[i]) cout << f << " ";
    cout << endl;
    cout << "Label: " << ( evaluate(featuresList[i], spamDetector) ? "SPAM" : "NOT SPAM" ) << endl;
}


    for (int i{0}; i<featuresList.size();++i) cout << "Mail " << i+1 << " is " << ( evaluate(featuresList[i], spamDetector) ? "SPAM" : "NOT SPAM" ) << endl;

    destroyTree(spamDetector);

    cin.get();

    return 0;
}
