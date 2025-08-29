#include <cctype>
// the purpose of this header is to contain all the functions that are used to define the indicators of spam

//toLower returns the input string with all lower cases - necessary for isWordContained
string toLower(string instr){
    string res {};
    for (auto &e : instr) {
        // uppercase letters range from 65 to 90, while the ASCII values for lowercase letters range from 97 to 122
        if ( e <= 'Z' && e >= 'A') res.push_back(e + ('a' - 'A'));
        else res.push_back(e);
    }
    return res;
}


//isWordContained returns True if the word w is contained inside of string s, otherwise returns false
bool isWordContained(string s, string w){
    string s_l = toLower(s);
    string w_l = toLower(w);
    auto pos = s_l.find(w_l);
    while (pos != string::npos) {
        bool leftOk = (pos == 0) || !isalpha(s_l[pos - 1]);
        bool rightOk = (pos + w_l.size() == s_l.size()) || !isalpha(s_l[pos + w_l.size()]);
        if (leftOk && rightOk) return true;
        pos = s_l.find(w_l, pos + 1); // look for next match
    }
    return false;
}



//counter of '!'
int counterExclamationMarks(string s){
    int n {0};
    for (auto &e: s) if (e == '!') ++n;
    return n;
}


//percentage of capital letters
double percentageCaps(string s){
    int tot = 0, capital = 0;
    for (char e : s){
        if (isalpha(e)) {
            ++tot;
            if (isupper(e)) ++capital;
        }
    }
    return (tot == 0) ? 0.0 : (double(capital) * 100.0 / double(tot));
}
