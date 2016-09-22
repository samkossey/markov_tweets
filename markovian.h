#include <iostream>
#include <string>
#include <map>
#include <list>
using namespace std;

struct Freq{
    string word;
    int frequency;
    Freq(){
        word = "";
        frequency = 0;
    }
    ~Freq(){};
};