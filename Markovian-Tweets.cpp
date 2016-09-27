//#include "markovian.h"
#include "Hashmap.cpp"
#include "FileHandler.cpp"
#include <ctime>
#include <cstdlib>

#define FILE "Const.txt"
#define DEBUG false

//given a map of words and the frequencies of their successors, generates
//a string that is a tweet (< 145 characters) based on the likelihood of 
//words appearing from the map
string generateTweet(map<string, list<Freq> > theMap){
    //length of the tweet
    int length = 0;
    //the total frequency of a list of values
    int modVal;
    int modVal2;
    //the raw random value mod the modVal
    int randVal;
    int random;
    //the string that will eventually be returned (the tweet)
    string wordSoFar = "";
    //a potential new word to add to wordSoFar as you iterate
    string tempWord = "";
    string prevWord = "";
    //if true, the tweet has hit its length limit
    bool flag;
    //once this value reaches the randVal or greater, the word associated with
    //that frequency becomes tempWord
    int freqSoFar = 0;
    srand(time(NULL));
    //"" holds words that can start a sentence
    modVal = theMap.at(", ").begin()->frequency;
    //randVal can be [1,modVal]
    randVal = rand() % modVal + 1;
    list<Freq>::iterator i = theMap.at(", ").begin();
    i++;
    for (i; i != theMap.at(", ").end(); i++){
        freqSoFar += i->frequency;
        if (freqSoFar >= randVal){
            if ((i->word.length() + length + 1) < 145){
                //saves the length that word added to the tweet's total length
                int iLength = i->word.length();
                
                if (iLength == 0 || i->word.at(iLength - 1) < 65 || (i->word.at(iLength - 1) > 90 &&
            i->word.at(iLength - 1) < 97) || i->word.at(iLength - 1) > 122){
                //if the word ends in a punctuation mark, the key associated is
                //""
                tempWord = "";
                prevWord = "";
            }
             else{
                 //sets the new key to find to the current word
                 prevWord = tempWord;
                 tempWord = i->word;
             }   
                //adds the new word to the tweet so far
                wordSoFar += i->word;
                //adds the length of the new word to the total length
                //of the tweet so far
                length += iLength;
                break;
            } 
        }
    }
    //while the tweet is under 145 characters
    while (!flag){
        #if DEBUG 
            cout << "Previous word: \"" << tempWord << "\" Previous word2: \"" << prevWord << "\"" << endl;
        #endif
        freqSoFar = 0;
        modVal = 1;
        //modVal2 = 1;
        //modVal is the total frequency of the list of values
        // if (theMap.count(tempWord)==1) {
        //     modVal2 = theMap.at(tempWord).begin()->frequency;
        //     int random = 1;
        // }
        if (theMap.count(tempWord + ", " + prevWord)==1) {
            modVal = theMap.at(tempWord + ", " + prevWord).begin()->frequency;
            //random = rand() % (modVal*10 + modVal2) + 1;
        }
        //random= rand() % ( modVal + modVal2 ) + 1;
        //randVal can be [1,modVal]
        string wordOrWords = "";
        // if ( random <= modVal ) {
        //     randVal = rand() % modVal2 + 1;
        //     list<Freq>::iterator i = theMap.at(tempWord).begin();
        //     #if DEBUG 
        //     cout << "for word: \"" << tempWord << "\" rand val: " << randVal << " of " << modVal << endl;
        //     #endif
        //     wordOrWords = tempWord;
        // } else {
            randVal = rand() % modVal + 1;
            list<Freq>::iterator i = theMap.at(tempWord + ", " + prevWord).begin();
            #if DEBUG 
                cout << "for words: \"" << tempWord + ", " + prevWord << "\" rand val: " << randVal << " of " << modVal << endl;
            #endif
            wordOrWords = tempWord + ", " + prevWord;
        // }
        i++;
        //iterates through the list of values looking for one whose frequency
        //added to the previous frequecies hits the threshold of randVal
        for (i; i != theMap.at(tempWord + ", " + prevWord).end(); i++){
            freqSoFar += i->frequency;
            if (freqSoFar >= randVal){
                //check if the length of the word and a space after it 
                //makes the tweet too long
                if ((i->word.length() + length + 1) < 145){
                    int iLength = i->word.length();
                    #if DEBUG
                        cout << "word: " << i->word << endl;
                        for (map<string, list<Freq> >::iterator j = theMap.begin(); j != theMap.end(); ++j){
                            int counter=1;
                            for (list<Freq>::iterator k = j->second.begin(); k != j->second.end(); ++k){
                                if (j->first == tempWord + ", " + prevWord && k->word != "." && k->word != "") {
                                    cout << j->first << " -> " << k->word << " " << counter << endl;
                                    counter+=k->frequency;
                                }
                            }
                        }
                    #endif
                    if (iLength <= 0 || i->word.at(iLength - 1) < 65 || (i->word.at(iLength - 1) > 90 &&
                i->word.at(iLength - 1) < 97) || i->word.at(iLength - 1) > 122){
                    //if a word ends in punctuation, it's key is ""
                    tempWord = "";
                    prevWord = "";
                }
                 else{
                     //otherwise the key is the word itself
                     prevWord = tempWord;
                     tempWord = i->word;
                 } 
                    //add a space to the final tweet
                    wordSoFar += " ";
                    //increase the length of the tweet because of the space
                    length++;
                    //add the current word to the tweet
                    wordSoFar += i->word;
                    //add the length of the new word to the total length
                    length += i->word.length();
                    #if DEBUG
                        cout << "New Word: \"" << i->word << "\"" << endl;
                        cout << "length: " << length << endl;
                    #endif
                    break;
                } 
                else{
                    #if DEBUG
                        cout << "cut off word " << i->word << endl;
                    #endif
                    flag = true;
                    break;
            }
            }
        }
    }
    return wordSoFar;
}

//if the last word of the tweet does not finish a sentence, that sentence fragment
//is removed
void trimToLastSentence(string &text){
    #if DEBUG
    cout << "Original Sentence: " << text << endl;
    #endif
    while(text.back() != '.' && text.back() != '!' && text.back() != '?' && !text.empty()){
        #if DEBUG
            cout << text.back() << " is not a sentence terminator." << endl;
        #endif
        text.pop_back();
    }
    #if DEBUG
    cout << "New Sentence: " << text << endl;
    #endif
}

int main() {
    string tweets;
    File* file;
    
    // file = new File("story6.txt");
    // tweets += " " + file->readfile();
    // delete(file);

    // file = new File("Const.txt");
    // tweets = file->readfile();
    // delete(file);
    
    file = new File(FILE);
    tweets = file->readfile();
    delete(file);
    
    // file = new File("story2.txt");
    // tweets += " " + file->readfile();
    // delete(file);
    
    // file = new File("story3.txt");
    // tweets += " " + file->readfile();
    // delete(file);
    
    // file = new File("story4.txt");
    // tweets += " " + file->readfile();
    // delete(file);
    
    // file = new File("story.txt");
    // tweets += " " + file->readfile();
    // delete(file);
    
    
    list<string> tweetlist = parseText(tweets);
    
    map<string, list<Freq> > amap = createMap2(tweetlist);
    //map<string, list<Freq> > amap2 = createMap(tweetlist);
    //amap.insert(amap2.begin(), amap2.end());
    
    #if DEBUG 
    printMap(amap); 
    #endif
    
    string newTweet = generateTweet(amap);
    trimToLastSentence(newTweet);
    cout << "Generated Tweet: \"" << newTweet << "\"" << endl;
}