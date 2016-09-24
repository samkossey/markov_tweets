#include "markovian.h"



list<string> parseText(string s){
    list<string> l;
    l.push_back("");
    string currString = "";
    for (int i = 0; i < s.length(); i++){
        if (s.at(i) == ' '){
            l.push_back(currString);
            currString = "";
        }
        else{
            currString += s.at(i);
        }
    }
    if (currString != ""){
        l.push_back(currString);
    }
    return l;
}

map<string, list<Freq> > createMap(list<string> aList){
    map<string, list<Freq> > myMap;
    string currString = "";
    string prevString = "";
    for (list<string>::const_iterator i = aList.begin(); i != aList.end(); ++i){
        currString = *i;
        int length = currString.length();
        if (myMap.count(prevString) == 0){
                list<Freq> listOfF;
                Freq f;
                f.word = currString;
                if (currString == "" && prevString == ""){
                    f.frequency = 0;
                }
                else{
                    f.frequency++;
                }
                Freq total;
                total.word = ".";
                total.frequency += f.frequency;
                listOfF.push_back(total);
                listOfF.push_back(f);
                myMap.insert(std::pair<string, list<Freq> > (prevString, listOfF));
                if (length == 0 || currString.at(length - 1) < 65 || (currString.at(length - 1) > 90 &&
                currString.at(length - 1) < 97) || currString.at(length - 1) > 122){
                    prevString = "";
                    currString = "";
                }
                else {
                    prevString = currString;
                    currString = "";
                }
            }
            else if (myMap.count(prevString) > 0){
                bool doesExist = false;
                for (list<Freq>::iterator i = myMap.at(prevString).begin(); i != myMap.at(prevString).end(); i++){
                    if (i->word == currString && currString != ""){
                        i->frequency = i->frequency + 1;
                        doesExist = true;
                        myMap.at(prevString).begin()->frequency++;
                        break;
                    }
                }
                if (!doesExist){
                    Freq fr;
                    fr.word = currString;
                    fr.frequency = 1;
                    myMap.at(prevString).begin()->frequency++;
                    myMap.at(prevString).push_back(fr);
                }
                if (length > 0 && (currString.at(length - 1) < 65 || (currString.at(length - 1) > 90 &&  //out of range error thrown here: basic_string::at: __n (which is 18446744073709551615) >= this->size() (which is 0)
                currString.at(length - 1) < 97) || currString.at(length - 1) > 122)){
                    prevString = "";
                    currString = "";
                }
                else {
                    prevString = currString;
                    currString = "";
                }
                
            }
        }
        return myMap;
}

int main2() {
    string teststring = "I am alive to go to the store.  I am me. I wish I could go to the store.";
    list<string> testlist = parseText(teststring);
    for (list<string>::iterator i = testlist.begin(); i != testlist.end(); i++){
        cout << *i << endl;
    }
    map<string, list<Freq> > amap = createMap(testlist);
    for (map<string, list<Freq> >::iterator i = amap.begin(); i != amap.end(); ++i){
        for (list<Freq>::iterator j = i->second.begin(); j != i->second.end(); ++j){
            cout << i->first << " -> " << j->word << " " << j->frequency << endl;
        }
    }
    //.cout << testlist.popback() << endl;
}


/*
        if (s.at(i) == "." || s.at(i) == "!" || s.at(i) == "?"){
            
        }
        else 
    */