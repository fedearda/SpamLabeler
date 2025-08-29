#include <vector>
#include <string>

#define CONTACTLIST_PATH "data/contactList.txt"
#define EMAILS_PATH "data/emails.tsv"
#define REPUTATIONLIST_PATH "data/reputationList.txt"
#define SUSPICIOUSWORDS_PATH "data/suspiciousWords.txt"

using namespace std;

extern vector<double> thresholdList;

enum FeatureIndex {
    UNTRUSTED_CONTACT = 0,
    EXCLAMATION_COUNT,
    CAPITAL_PERCENT,
    CONTAINS_FREE,
    HAS_ATTACHMENT,
    REPUTATION_SCORE
};

struct email {
    string _attachment;
    int _attachDim; // bytes
    string _body;
    string _object;
    string _sender;
    email(string obj="", string sender="", string body = "", string Attach = "none", int attDim = 0): _attachment(Attach), _attachDim(attDim),
                                                                                            _body(body), _object(obj), _sender(sender) {}                                                                                         
};


struct Node {
    bool _isLeaf;
    bool _classification; //true = spam
    Node* _leftNode;
    Node* _rightNode;
    int _featureIndex;
    double _threshold;

    //constructor for nodes
    Node(int featureIndex): _classification(false), _isLeaf(false), _leftNode(nullptr), _rightNode(nullptr), _featureIndex(featureIndex), _threshold(thresholdList[featureIndex]){}
    
    //constructor for leaves
    Node(bool classification): _classification(classification), _isLeaf(true), _leftNode(nullptr), _rightNode(nullptr), _featureIndex(-1), _threshold(0.0){}

};