#include<iostream>
#include<fstream>
#include<sstream>
#include<set>
using namespace std;
class stringSet {
private:
    set<string>uniqueWords;
    long long wordsNumber;
public:
    stringSet() {}
    stringSet(string content);
    stringSet(ifstream& file);
    void addString(string addition);
    void removestring(string removed);
    void clearSet();
    int numberOfStrings() { return wordsNumber; }
    void setstrings(set<string> mp) { uniqueWords = mp; }
    void setwordsNumber(int n) { wordsNumber = n; }
    void print();
    stringSet operator+(const stringSet& otherSet);//return union of them
    stringSet operator*(const stringSet& otherSet);   //it returns the intersection of two StringSet objects.
    double computesSimilarity(const stringSet& otherSet);
};
string lowerWithOutPunc(string s) {
    string lowerwithOutPunc = "";
    for (int i = 0; i < s.size(); i++) {
        if (int(s[i]) <= 122 && int(s[i]) >= 97) {
            lowerwithOutPunc += char(int(s[i]) - 32);
        }
        else if ((int(s[i]) <= 90 && int(s[i]) >= 65) || (int(s[i]) <= 57 && int(s[i]) >= 48)) {
            lowerwithOutPunc += s[i];
        }
    }
    return lowerwithOutPunc;
}
stringSet::stringSet(ifstream& file) {
    if (file.fail()) {
        cout << "No existence of such a file with this name";
        exit(1);
    }
    string  s;
    while (file >> s) {
        s = lowerWithOutPunc(s);
        uniqueWords.insert(s);
    }
    wordsNumber = uniqueWords.size();
}
stringSet::stringSet(string content) {
    stringstream cont;
    cont << content;
    content.clear();
    while (cont >> content) {
        content = lowerWithOutPunc(content);
        uniqueWords.insert(content);
    }
    wordsNumber = uniqueWords.size();
}
void stringSet::addString(string addition) {
    stringstream s;
    s << addition;
    addition.clear();
    while (s >> addition) {
        addition = lowerWithOutPunc(addition);
        uniqueWords.insert(addition);
    }
    wordsNumber = uniqueWords.size();
}
void stringSet::removestring(string removed) {
    stringstream s;
    s << removed;
    removed.clear();
    set<string>sorted;
    while (s >> removed) {
        removed = lowerWithOutPunc(removed);
        sorted.insert(removed);
    }
    auto rem = sorted.begin();
    for (auto it = uniqueWords.begin(); it != uniqueWords.end(); it++) {
        if (*it == *rem) {
            auto it2 = it;
            it2++;
            uniqueWords.erase(it, it2);
            rem++;
            if (rem == sorted.end())break;
        }
    }
    wordsNumber = uniqueWords.size();
}
void stringSet::clearSet() {
    uniqueWords.clear();
    wordsNumber = 0;
}
void stringSet::print() {
    if (uniqueWords.size() == 0)return;
    cout << "{";
    for (auto it = uniqueWords.begin(); it != --uniqueWords.end(); it++) {
        cout << *it << ", ";
    }
    if ((--uniqueWords.end()) != uniqueWords.begin() && ((uniqueWords.end()) != uniqueWords.begin()))
        cout << *(--uniqueWords.end());
    cout << "}\n";
}
stringSet  stringSet:: operator+(const stringSet& otherSet) {
    set<string> Un;
    for (auto it = uniqueWords.begin(); it != uniqueWords.end(); it++) {
        Un.insert(*it);
    }
    for (auto it = otherSet.uniqueWords.begin(); it != otherSet.uniqueWords.end(); it++) {
        Un.insert(*it);
    }
    stringSet Union;
    Union.setstrings(Un);
    Union.setwordsNumber(wordsNumber + otherSet.wordsNumber);
    return Union;
}
stringSet stringSet:: operator*(const stringSet& otherSet) {
    set<string> inter;
    for (auto it = uniqueWords.begin(); it != uniqueWords.end(); it++) {
        for (auto it1 = otherSet.uniqueWords.begin(); it1 != otherSet.uniqueWords.end(); it1++) {
            if (*it1 == *it) {
                inter.insert(*it);
            }
        }
    }
    stringSet intersection;
    intersection.setstrings(inter);
    intersection.setwordsNumber(inter.size());
    return intersection;
}
double stringSet::computesSimilarity(const stringSet& otherSet) {
    stringSet inters = ((*this) * (otherSet));
    double sim = ((double)inters.wordsNumber / (wordsNumber + otherSet.wordsNumber));
    return sim;
}
void Usingfiles();
void usingExistencestring();
int main() {
    int complete;
    int choice;
    do
    {
        cout << "If you wanna use files Enter==>1\nelse IF You wanna use existing 2 strings Enter=>2\n";
        cin >> choice;
        if (choice == 1)Usingfiles();
        else if (choice == 2)usingExistencestring();
        cout << "\nIF you wanna stop Enter ==> 0 \n";
        cin >> complete;
    } while (complete);
    return 0;
}
void usingExistencestring() {
    string contents = "programming is a wide field.";
    contents += "\nOur Faculty is very difficult.\nThe programmer's lifestyle is very difficult.";
    string contents2 = "programming is the futur.Now all countries are interested in the ";
    contents2 += "Faculty of Computer Science.\nThe programmer's lifestyle is very difficult.ICPC.";
    stringSet str(contents), str2(contents2);
    cout << "content of string1\n";
    str.print();
    cout << "\ncontent of string2\n";
    str2.print();
    cout << "\n add string (Computer Science) to string1\n";
    str.addString("Computer Science");
    str.print();
    cout << "\nEnter the word you wanna remove from string1\n";
    string removed;
    cin >> removed;
    cout << "\nstring " << removed << "has been removed from string1\n";
    str.removestring(removed);
    str.print();
    stringSet Union = str + str2;
    cout << "\nstring1 + string2\n";
    Union.print();
    stringSet intersec = str * str2;
    cout << "\nstring1 * string2\n";
    intersec.print();
    cout << "\nThe result of computing the similarity between string1 and string2\n";
    cout << str.computesSimilarity(str2);
    cout << "\nstring1 has been cleared";
    str.clearSet();
    str.print();
}
void Usingfiles() {
    ifstream file1, file2;
    string file1name, file2name;
    cout << "Enter the name of Two files: \n";
    cin >> file1name >> file2name;
    int sz1 = file1name.size(), sz2 = file2name.size();
    if (sz1 < 5)file1name += ".txt";
    else if (file1name.substr(sz1 - 4, sz1) != ".txt") {
        file1name += ".txt";
    }
    if (file2name.size() < 5)file2name += ".txt";
    else if (file2name.substr(sz2 - 4, sz2) != ".txt") {
        file2name += ".txt";
    }
    file1.open(file1name);
    file2.open(file2name);
    if (file1.fail()) { cout << "No existence of such a File with This neme"; exit(1); }
    if (file2.fail()) { cout << "No existence of such a File with This neme"; exit(1); }
    stringSet f1(file1), f2(file2);
    cout << "file1 content\n";
    f1.print();
    cout << "\nfile2 content\n";
    f2.print();
    cout << "\n add string (Computer Science) to f1\n";
    f1.addString("Computer Science");
    f1.print();
    cout << "Enter the word you wanna remove from file1\n";
    string removed;
    cin >> removed;
    cout << "\nstring " << removed << "has been removed from file1\n";
    f1.removestring(removed);
    f1.print();
    stringSet Union = f1 + f2;
    cout << "\nf1 + f2\n";
    Union.print();
    stringSet intersec = f1 * f2;
    cout << "\nf1 * f2\n";
    intersec.print();
    cout << "\nThe result of computing the similarity between f1 and f2\n";
    cout << f1.computesSimilarity(f2);
    cout << "\n clear f1";
    f1.clearSet();
    f1.print();
}
