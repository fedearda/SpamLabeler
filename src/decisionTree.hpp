#include <unordered_map>

using namespace std;

vector<string> featureNames {"Is from an untrusted contact","Number of exclamative points", "Percentage of capital letters", 
    "Cointains suspicious words", "Has attachment", "Reputation score of sender"};
vector<double> thresholdList {0.5,3.5,15.0,0.5,0.5,8.0};


//function to manually build a tree and return the root of the tree
Node* buildTree() {

    //root
    Node* root = new Node(EXCLAMATION_COUNT);


    //first level
    Node* leftNode = new Node(REPUTATION_SCORE); //be careful! this node is inverted -> low reputation, under threshold means more likely to be spam. left child node is closer to spam than right child node
    root->_leftNode = leftNode;

    Node* rightNode = new Node(CAPITAL_PERCENT);
    root->_rightNode = rightNode;


    //second level
    Node* leftleftNode = new Node(CONTAINS_FREE);
    leftNode->_leftNode = leftleftNode;

    Node* leftrightNode = new Node(false); //leaf
    leftNode->_rightNode = leftrightNode;

    Node* rightleftNode = new Node(HAS_ATTACHMENT);
    rightNode->_leftNode = rightleftNode;

    Node* rightrightNode = new Node(true); //leaf
    rightNode->_rightNode = rightrightNode;


    //third level
    Node* leftleftleftNode = new Node(UNTRUSTED_CONTACT);
    leftleftNode->_leftNode = leftleftleftNode;

    Node* leftleftrightNode = new Node(true); //leaf
    leftleftNode->_rightNode = leftleftrightNode;

    Node* rightleftleftNode = new Node(false); //leaf
    rightleftNode->_leftNode = rightleftleftNode;

    Node* rightleftrightNode = new Node(false); //leaf
    rightleftNode->_rightNode = rightleftrightNode;


    //fourth level
    Node* leftleftleftleftNode = new Node(false); //leaf
    leftleftleftNode->_leftNode = leftleftleftleftNode;

    Node* leftleftleftrightNode = new Node(true); //leaf
    leftleftleftNode->_rightNode = leftleftleftrightNode;


    return root;
}


//recursive function to clear heap
void destroyTree(Node* root){
    if (!root) return;
    if (! root->_isLeaf){
        destroyTree(root->_leftNode);
        destroyTree(root->_rightNode);
    }
    delete root;
}


bool evaluate(vector<double> features, Node* currentNode){
    if (currentNode->_isLeaf) return currentNode->_classification;
    else {
        if (features[currentNode->_featureIndex] <= thresholdList[currentNode->_featureIndex]) //if the node feature is lower than the threshold for that feature, evaluate the _leftNode, otherwise the _rightNode
        {
            return evaluate(features, currentNode->_leftNode);
        }
        else return evaluate(features, currentNode->_rightNode);
    }
}

