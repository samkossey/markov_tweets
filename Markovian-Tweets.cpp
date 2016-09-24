//#include "markovian.h"
#include "Hashmap.cpp"
#include "FileHandler.cpp"
#include <ctime>
#include <cstdlib>

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
        list<Freq>::iterator i = theMap.at("").begin();
        i++;
        for (i; i != theMap.at("").end(); i++){
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
                    length += iLength;
                    break;
                } 
            }
        }
        
    while (!flag){
        freqSoFar = 0;
        modVal = theMap.at(tempWord).begin()->frequency;
        randVal = rand() % modVal + 1;
        list<Freq>::iterator i = theMap.at(tempWord).begin();
        i++;

        for (i; i != theMap.at(tempWord).end(); i++){
            freqSoFar += i->frequency;
            cout << "rand val " << randVal << endl;
            if (freqSoFar >= randVal){
                if ((i->word.length() + length + 1) < 145){
                    int iLength = i->word.length();
                    cout << "i->word at second " << i->word << endl;
                    if (i->word.at(iLength - 1) < 65 || (i->word.at(iLength - 1) > 90 &&
                i->word.at(iLength - 1) < 97) || i->word.at(iLength - 1) > 122){
                    tempWord = "";
                }
                 else{
                     
                     tempWord = i->word;
                 } 
                    wordSoFar += " ";
                    length++;
                    wordSoFar += i->word;
                    length += i->word.length();
                    cout << "length " << length << endl;
                    break;
                } 
                else{
                cout << "cut off word " << i->word << endl; 
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
    string newTweet = generateTweet(amap);
    cout << "Generated Tweet: \"" << newTweet << "\"" << endl;

    std::cout << "Hello World!\n";
    
}