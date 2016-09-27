#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

class File {
    private:
        string file;
    
    public:
    File(string filename){
        file=filename;
    }
    
    string readfile(){
        string line;
        string text;
        ifstream inFile;

        inFile.open(file);


        while (getline(inFile, line))
        {
            text+=line;
            // if (!(line.back() == '.' || line.back() == '!' || line.back() == '?' || line.back() == ';')){
            //     text+=".";
            // }
            text+=" ";
        }
        text.pop_back(); //take of the trailing space
        inFile.close();
        return text;
    }
};

int main3() {
    string tweet;
    File* file = new File("tweet.txt");
    tweet = file->readfile();
    std::cout << "\"" << tweet << "\"" << endl;
    delete(file);
}