#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int main(){
    string line;
    int first_elf = 0;
    int second_elf = 0;
    int third_elf = 0;
    int current_calories = 0;
    int total_calories = 0;
    
    cout << "Reading input file...";
    ifstream input_file ("/home/aliu/Self_Practice_Study/AdventCalendar/advent_calendar_2022/inputs/day_1.txt");
    if (input_file.is_open()){
        while(getline(input_file, line)){
            if (line != ""){
                current_calories += stoi(line);
            }
            else{
                if (current_calories > first_elf){
                    third_elf = second_elf;
                    second_elf = first_elf;
                    first_elf = current_calories;
                    
                }
                else if(current_calories > second_elf && current_calories != first_elf){
                    third_elf = second_elf;
                    second_elf = current_calories;
                }
                else if(current_calories > third_elf && current_calories != second_elf){
                    third_elf = current_calories;
                }
                
                current_calories = 0;
            }
        }
        total_calories = first_elf+second_elf+third_elf;
        cout << "Top 3 total calories: " << total_calories;
        input_file.close();
    }
    else cout << "couldn't open file";
    
    return 0;
}