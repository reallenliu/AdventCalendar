// Library include statements
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int main(){
    string line;
    int most_calories = 0;
    int current_calories = 0;
    
    cout << "Reading input file...";
    ifstream input_file ("/home/aliu/Self_Practice_Study/AdventCalendar/advent_calendar_2022/inputs/day_1.txt");
    if (input_file.is_open()){
        // this while loop gets the next line in the text file.
        while(getline(input_file, line)){
            // If still on the current elf
            if (line != ""){
                current_calories += stoi(line);
            }
            else{
                most_calories = (current_calories > most_calories) ? current_calories : most_calories;
                current_calories = 0;
            }
        }
        cout << "Most Calories: " << most_calories;
        input_file.close();
    }
    else cout << "couldn't open file";
    
    return 0;
}