#include <iostream>
#include "structures.hpp"
#include "decisionTree.hpp"
#include "toolBox.hpp"
#include "dataExtractor.hpp"

vector<string> trustedContacts = readContacts(CONTACTLIST_PATH);
vector<string> suspiciousWords = readWords(SUSPICIOUSWORDS_PATH);
unordered_map<string,double> peopleList = readPeople(REPUTATIONLIST_PATH);

vector<email> emailList = readEmail(EMAILS_PATH);

vector<vector<double>> featuresList {};

void test(Node* spamDetector);

int main(){
    
    Node* spamDetector = buildTree();

    for (auto &m: emailList) {
        auto f = featureExtract(m,trustedContacts,suspiciousWords,peopleList);
        bool isSpam = evaluate(f, spamDetector);
        cout << "Mail " << m._object << " is " << (isSpam ? "SPAM" : "NOT SPAM") << endl;
        if (isSpam){
            f[REPUTATION_SCORE] = f[REPUTATION_SCORE] - 0.7;
            if (f[REPUTATION_SCORE] < 0.0) f[REPUTATION_SCORE] = 0.0;
        }
        else {
            f[REPUTATION_SCORE] = f[REPUTATION_SCORE] + 0.1;
            if (f[REPUTATION_SCORE] > 10.0) f[REPUTATION_SCORE] = 10.0;
        }
        featuresList.push_back(f);
        peopleList[m._sender] = f[REPUTATION_SCORE];
    }

    updateRep(peopleList);

    // test(spamDetector);

    destroyTree(spamDetector);

    cin.get();

    return 0;
}

void test(Node* spamDetector){
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
        cout << "----" << endl;
    }
}
