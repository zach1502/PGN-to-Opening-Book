#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>

#include "thc.h"
#include "thc.cpp"

bool isNumber(char ch){
    return (ch >= '0' && ch <= '9');
}

int main(int argc, char* argv[]){

    std::string filePath = "Games/lichessJan2013.pgn";
    std::ofstream ofile ("openingBook.txt");   

    // Fen : Moves
    std::map<std::string, std::vector<std::string>> openingBook;

    for(int fileNum = 1; fileNum < argc; fileNum++){
        filePath = argv[fileNum];

        // open a file
        std::string line;
        std::ifstream ifile (filePath);

        if(ifile.is_open()){
            bool isPreEval = false;
            std::vector<std::string> games;

            while(getline(ifile, line)){

                if(line[0] != '1'){
                    continue;
                }

                for(int i = 0; i < line.length(); i++){

                    if (line[i] == '1' && line[i+1] == '1'){
                        line.erase(i, line.length()-1);
                        continue;
                    }

                    // remove double digit numbers
                    if(isNumber(line[i]) && isNumber(line[i+1]) && line[i+2] == '.'){
                        line.erase(i, 4);
                        continue;
                    }

                    // erase numbers followed by a .
                    if((isNumber(line[i]) && line[i+1] == '.')){
                        line.erase(i, 3);
                        continue;
                    }

                    if (line[i] == ' ' && line[i+1] == '{'){
                        isPreEval = true;
                        break;
                    }

                    if(isNumber(line[i]) && line[i+1] == '-' && isNumber(line[i+2])){
                        line.erase(i, 3);
                        continue;
                    }
                }
                
                if(!isPreEval){
                    games.emplace_back(line);
                }
            }

            thc::ChessRules cr;
            thc::Move mv;

            for(int i = 0; i < games.size(); i++){
                // replace all spaces with commas
                games[i].pop_back();

                // wrap each word in quotes
                std::stringstream ss(games[i]);
                std::string word;
                while(std::getline(ss, word, ' ')){
                    std::string posFen = cr.ForsythPublish();
                    std::cout << posFen << std::endl;

                    if(openingBook.count(posFen)){
                        openingBook[posFen].emplace_back(word);
                    }
                    else{
                        openingBook.emplace(posFen, std::vector<std::string>{word});
                    }

                    int lengthOfWord = word.length();
                    char charArray[lengthOfWord+1];
                    strcpy(charArray, word.c_str());

                    mv.NaturalIn(&cr, charArray);
                    cr.PlayMove(mv);
                }

                cr.Forsyth("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
            }

            ifile.close();
        }
    }

    ofile << "{" << std::endl;
    auto secondLast = std::prev(openingBook.end(), 1);
    for(auto it = openingBook.begin(); it != openingBook.end(); it++){
        ofile << "    \"" << it->first << "\" : [";
        for(int i = 0; i < it->second.size()-1; i++){
            ofile << "\"" << it->second[i] << "\", ";
        }

        ofile << "\"" << it->second[it->second.size()-1] << "\"]";

        if(it != secondLast){
            ofile << ",";
        }
        ofile << std::endl;
    }
    ofile << "}";
    ofile.close();
}