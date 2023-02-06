#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;



int main(){
    string line;
    map <char, int> score_mapping = {{'A', 1}, {'B', 2}, {'C', 3},
                                        {'X', 1}, {'Y', 2}, {'Z', 3}};
    map<char,int>::iterator my_symbol_iterator;
    map<char, int>::iterator op_symbol_iterator;
    int total_score = 0;

    ifstream input_file ("/home/aliu/Self_Practice_Study/AdventCalendar/advent_calendar_2022/inputs/day_2.txt");
    if (input_file.is_open()){
        while(getline(input_file, line)){
            const char opponent_symbol = line[0];
            const char my_symbol = line[2];
            my_symbol_iterator= score_mapping.find(my_symbol);
            op_symbol_iterator= score_mapping.find(opponent_symbol);

            switch (my_symbol_iterator->second){
                // Lose
                case 1:
                    switch (op_symbol_iterator->second){
                        case 1:
                            total_score+=3;
                            break;
                        case 2:
                            total_score+=1;
                            break;
                        case 3:
                            total_score+=2;
                            break;
                    }
                    break;
                //Draw
                case 2:
                    total_score+=3;
                    switch (op_symbol_iterator->second){
                        case 1:
                            total_score+=1;
                            break;
                        case 2:
                            total_score+=2;
                            break;
                        case 3:
                            total_score+=3;
                            break;
                    }
                    break;
                //Win
                case 3:
                    switch (op_symbol_iterator->second){
                        case 1:
                            total_score+=2;
                            break;
                        case 2:
                            total_score+=3;
                            break;
                        case 3:
                            total_score+=1;
                            break;
                    }
                    total_score+=6;
                    break;

            }
        }
        cout << "My score is: " << total_score;

    }
    input_file.close();
    return 0; 

}