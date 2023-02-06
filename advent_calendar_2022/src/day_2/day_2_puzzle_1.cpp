#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

void symbol_points(map<char, int>::iterator &key_find, int &total_score){
    switch(key_find->second){
        case 1:
            total_score +=1;
            break;
        case 2:
            total_score +=2;
            break;
        case 3:
            total_score +=3;
            break;
    }

}

int main(){
    string line;
    map <char, int> score_mapping = {{'A', 1}, {'B', 2}, {'C', 3},
                                        {'X', 1}, {'Y', 2}, {'Z', 3}};
    map<char,int>::iterator key_find;
    int total_score = 0;

    ifstream input_file ("/home/aliu/Self_Practice_Study/AdventCalendar/advent_calendar_2022/inputs/day_2.txt");
    if (input_file.is_open()){
        while(getline(input_file, line)){
            const char opponent_symbol = line[0];
            const char my_symbol = line[2];
            key_find= score_mapping.find(my_symbol);

            if ((opponent_symbol == 'A' && my_symbol == 'X') or (opponent_symbol == 'B' && my_symbol == 'Y') 
            or (opponent_symbol == 'C' && my_symbol == 'Z')){
                total_score += 3;
                symbol_points(key_find, total_score);

            }
            else if ((opponent_symbol == 'A' && my_symbol == 'Y') or (opponent_symbol == 'B' && my_symbol == 'Z') 
                    or (opponent_symbol == 'C' && my_symbol == 'X')){
                total_score += 6;
                symbol_points(key_find, total_score);
            }
            else{
                symbol_points(key_find, total_score);
            }
        }
        cout << "My score is: " << total_score;

    }
    input_file.close();
    return 0; 

}