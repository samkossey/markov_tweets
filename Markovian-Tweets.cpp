#include "markovian.h"
#include "Hashmap.cpp"
#include "FileHandler.cpp"
#include <time.h>

#define FILE "tweet.txt"

string generateTweet(map<string, list<Freq> > theMap){
    int length = 0;
    int modVal;
    int randVal;
    string wordSoFar = "";
    string tempWord = "";
    bool flag;
    int freqSoFar = 0;
    
    srand(time(NULL));
        modVal = theMap.at("").begin()->frequency;
        randVal = rand() % modVal + 1;
        for (list<Freq>::iterator i = theMap.at("").begin(); i != theMap.at("").end(); i++){
            freqSoFar += i->frequency;
            if (freqSoFar >= randVal){
                if ((i->word.length() + length + 1) < 145){
                    int iLength = i->word.length();
                    if (i->word.at(iLength - 1) < 65 || (i->word.at(iLength - 1) > 90 &&
                i->word.at(iLength - 1) < 97) || i->word.at(iLength - 1) > 122){
                    tempWord = "";
                }
                 else{
                     tempWord = i->word;
                 }   
                    wordSoFar += i->word;
                    length += i->word.length() + 1;
                    break;
                } 
            }
        }
        
    while (!flag){
        freqSoFar = 0;
        srand(time(NULL));
        modVal = theMap.at(tempWord).begin()->frequency;
        randVal = rand() % modVal + 1;
        for (list<Freq>::iterator i = theMap.at(tempWord).begin(); i != theMap.at(tempWord).end(); i++){
            freqSoFar += i->frequency;
            if (freqSoFar >= randVal){
                if ((i->word.length() + length + 1) < 145){
                    int iLength = i->word.length();
                    if (i->word.at(iLength - 1) < 65 || (i->word.at(iLength - 1) > 90 &&
                i->word.at(iLength - 1) < 97) || i->word.at(iLength - 1) > 122){
                    tempWord = "";
                }
                 else{
                     tempWord = i->word;
                 } 
                    wordSoFar += i->word;
                    length += i->word.length() + 1;
                    break;
                } 
                else{
                flag = true;
                break;
            }
            }
        }
    }
    return wordSoFar;
}

int main() {
    string tweets;
    File* file = new File(FILE);
    tweets = file->readfile();
    delete(file);
    list<string> tweetlist = parseText(tweets);
    map<string, list<Freq> > amap = createMap(tweetlist);
    for (map<string, list<Freq> >::iterator i = amap.begin(); i != amap.end(); ++i){
        for (list<Freq>::iterator j = i->second.begin(); j != i->second.end(); ++j){
            cout << i->first << " -> " << j->word << " " << j->frequency << endl;
        }
    }
    generateTweet(amap);

    std::cout << "Hello World!\n";
    
}