#include <fstream>
#include <sstream>


//function to extract trusted contacts from the file
vector<string> readContacts(const string& filename){
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return {}; // or throw
    }

    vector<string> res;
    string line;
    while(getline(file,line)){
        res.push_back(line);
    }
    file.close();
    return res;
}


//function to extract the list of people in the organization
unordered_map<string,double> readPeople(const string& filename){
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return {}; // or throw
    }

    unordered_map<string,double> res;
    string line;
    
    while(getline(file,line)){
        stringstream ss(line);
        double rep {0.0};
        string contact, temp;

        getline(ss,contact,',');
        getline(ss,temp,',');

        rep = stod(temp);

        res[contact] = rep;
    }

    file.close();

    return res;
}


//function returns a list of suspicious words read from file
vector<string> readWords(const string& filename){
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return {}; // or throw
    }

    vector<string> res;
    string line;

    while(getline(file,line)){
        res.push_back(line);
    }

    file.close();
    return res;
}


//the function must return a feature list from an input of object email
vector<double> featureExtract(email in, vector<string> trustedContacts, vector<string> suspiciousWords, unordered_map<string,double> peopleList){
    bool isUntrusted {true}, hasSuspiciousWords {false};
    double exclMarks {0.0};

    for (auto &e: trustedContacts) if (e == in._sender) isUntrusted = false;

    exclMarks = double(counterExclamationMarks(in._body)) + double(counterExclamationMarks(in._object));

    for (auto &word: suspiciousWords){
        hasSuspiciousWords |= isWordContained(in._body,word) || isWordContained(in._object,word);
    }

    double reputation = 0.0;
    if (peopleList.find(in._sender) != peopleList.end()) reputation = peopleList.at(in._sender);

    return {double(isUntrusted), exclMarks, percentageCaps(in._body), double(hasSuspiciousWords), double(!(in._attachment=="none")), reputation};
}

//the function must create a set of email objects starting from a .csv file 
vector<email> readEmail(const string& filename){
    ifstream file(filename);
    vector<email> emails;
    string line;

    while (getline(file,line)){
        email m;
        stringstream ss(line);

        getline(ss,m._sender,'\t');
        getline(ss,m._object,'\t');
        getline(ss,m._attachment,'\t');
        getline(ss,m._body,'\t');

        emails.push_back(m);
    }

    file.close();
    
    return emails;
}