#include "markovian.h"
//#include <queue>

//prints the key value pairs of the map
void printMap(map<string, list<Freq> > &amap){
    for (map<string, list<Freq> >::iterator i = amap.begin(); i != amap.end(); ++i){
        for (list<Freq>::iterator j = i->second.begin(); j != i->second.end(); ++j){
            cout << i->first << " -> " << j->word << " " << j->frequency << endl;
        }
    }
}

void sanatize(list <string> &aList){
    for (list<string>::const_iterator i = aList.begin(); i != aList.end(); ++i){
           //todo: Finish this function
    }
}

//given a string, creates a list of the words contained in that string
list<string> parseText(string s){
    list<string> l;
    l.push_back("");
    string currString = "";
    for (int i = 0; i < s.length(); i++){
        //a space indicates the start of a new word
        if (s.at(i) == ' '){
            l.push_back(currString);
            currString = "";
        }
        else{
            //if no space, continue building a word character by character
            currString += s.at(i);
        }
    }
    if (currString != ""){
        l.push_back(currString);
    }
    sanatize(l);
    return l;
}

//given a list of words, generates a mapping of the words, with any words
//that follow them as the values and how often they appear after that key
map<string, list<Freq> > createMap2(list<string> aList){
    //queue<string> previousWords;
    map<string, list<Freq> > myMap;
    string currString = "";
    string prevString1 = "";
    string prevString2 = "";
    for (list<string>::const_iterator i = aList.begin(); i != aList.end(); ++i){
        currString = *i;
        int length = currString.length();
        //if prevString (the potential key) is not already in the map
        if (myMap.count(prevString1 + ", " + prevString2) == 0){
                list<Freq> listOfF;
                Freq f;
                f.word = currString;
                if (currString == "" && prevString1 == "" && prevString2 == ""){
                //if (currString == "" && previousWords.front() == ""){
                    f.frequency = 0;
                }
                else{
                    f.frequency++;
                }
                Freq total;
                //"." keeps track of the total frequency for that value's keys
                total.word = ".";
                total.frequency += f.frequency;
                listOfF.push_back(total);
                listOfF.push_back(f);
                //inserts the prevString as the key and a list of frequencies
                //as the value for the key
                myMap.insert(std::pair<string, list<Freq> > (prevString1 + ", " + prevString2, listOfF));
                if (length == 0 || currString.at(length - 1) < 65 || (currString.at(length - 1) > 90 &&
                currString.at(length - 1) < 97) || currString.at(length - 1) > 122){
                    //if the last character of a word is a punctuation mark, 
                    //it is counted as a "" key in the map
                    prevString1 = "";
                    prevString2 = "";
                    currString = "";
                }
                else {
                    //set the currString to prevString so it can be the new key
                    prevString2 = prevString1;
                    prevString1 = currString;
                    //set the currString to be "" which will later be populated
                    //by the next string in the input list
                    currString = "";
                }
            }
            //if a key equal to prevString is already in the map
            else if (myMap.count(prevString1 + ", " + prevString2) > 0){
                bool doesExist = false;
                //iterates through the existing key's values to see if the currString
                //is equal to any words already in the values list
                for (list<Freq>::iterator i = myMap.at(prevString1 + ", " + prevString2).begin(); i != myMap.at(prevString1 + ", " + prevString2).end(); i++){
                    if (i->word == currString && currString != ""){
                        //if currString is found, add to its frequnency
                        i->frequency = i->frequency + 1;
                        doesExist = true;
                        //add to the list of values total frequency
                        myMap.at(prevString1 + ", " + prevString2).begin()->frequency++;
                        break;
                    }
                }
                //if the currString wasn't found
                if (!doesExist){
                    //create a new Freq with currString as the word
                    Freq fr;
                    fr.word = currString;
                    fr.frequency = 1;
                    //add to the list of values total frequency
                    myMap.at(prevString1 + ", " + prevString2).begin()->frequency++;
                    //add the Freq with currString to the list of values
                    myMap.at(prevString1 + ", " + prevString2).push_back(fr);
                }
                if (length <= 0 || (currString.at(length - 1) < 65 || (currString.at(length - 1) > 90 &&  //out of range error thrown here: basic_string::at: __n (which is 18446744073709551615) >= this->size() (which is 0)
                currString.at(length - 1) < 97) || currString.at(length - 1) > 122)){
                    //if the last character of a word is a punctuation mark, 
                    //it is counted as a "" key in the map
                    prevString1 = "";
                    prevString2 = "";
                    currString = "";
                }
                else {
                    //set the currString to prevString so it can be the new key
                    prevString2 = prevString1;
                    prevString1 = currString;
                    //set the currString to be "" which will later be populated
                    //by the next string in the input list
                    currString = "";
                }
                
            }
        }
        return myMap;
}

//calls createMap2 with a lookback value of 1
map<string, list<Freq> > createMap(list<string> aList){
    //return createMapN(aList, 1);
    //queue<string> previousWords;
    map<string, list<Freq> > myMap;
    string currString = "";
    string prevString = "";
    for (list<string>::const_iterator i = aList.begin(); i != aList.end(); ++i){
        currString = *i;
        int length = currString.length();
        //if prevString (the potential key) is not already in the map
        if (myMap.count(prevString) == 0){
                list<Freq> listOfF;
                Freq f;
                f.word = currString;
                if (currString == "" && prevString == ""){
                //if (currString == "" && previousWords.front() == ""){
                    f.frequency = 0;
                }
                else{
                    f.frequency++;
                }
                Freq total;
                //"." keeps track of the total frequency for that value's keys
                total.word = ".";
                total.frequency += f.frequency;
                listOfF.push_back(total);
                listOfF.push_back(f);
                //inserts the prevString as the key and a list of frequencies
                //as the value for the key
                myMap.insert(std::pair<string, list<Freq> > (prevString, listOfF));
                if (length == 0 || currString.at(length - 1) < 65 || (currString.at(length - 1) > 90 &&
                currString.at(length - 1) < 97) || currString.at(length - 1) > 122){
                    //if the last character of a word is a punctuation mark, 
                    //it is counted as a "" key in the map
                    prevString = "";
                    currString = "";
                }
                else {
                    //set the currString to prevString so it can be the new key
                    prevString = currString;
                    //set the currString to be "" which will later be populated
                    //by the next string in the input list
                    currString = "";
                }
            }
            //if a key equal to prevString is already in the map
            else if (myMap.count(prevString) > 0){
                bool doesExist = false;
                //iterates through the existing key's values to see if the currString
                //is equal to any words already in the values list
                for (list<Freq>::iterator i = myMap.at(prevString).begin(); i != myMap.at(prevString).end(); i++){
                    if (i->word == currString && currString != ""){
                        //if currString is found, add to its frequnency
                        i->frequency = i->frequency + 1;
                        doesExist = true;
                        //add to the list of values total frequency
                        myMap.at(prevString).begin()->frequency++;
                        break;
                    }
                }
                //if the currString wasn't found
                if (!doesExist){
                    //create a new Freq with currString as the word
                    Freq fr;
                    fr.word = currString;
                    fr.frequency = 1;
                    //add to the list of values total frequency
                    myMap.at(prevString).begin()->frequency++;
                    //add the Freq with currString to the list of values
                    myMap.at(prevString).push_back(fr);
                }
                if (length <= 0 || (currString.at(length - 1) < 65 || (currString.at(length - 1) > 90 &&  //out of range error thrown here: basic_string::at: __n (which is 18446744073709551615) >= this->size() (which is 0)
                currString.at(length - 1) < 97) || currString.at(length - 1) > 122)){
                    //if the last character of a word is a punctuation mark, 
                    //it is counted as a "" key in the map
                    prevString = "";
                    currString = "";
                }
                else {
                    //set the currString to prevString so it can be the new key
                    prevString = currString;
                    //set the currString to be "" which will later be populated
                    //by the next string in the input list
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