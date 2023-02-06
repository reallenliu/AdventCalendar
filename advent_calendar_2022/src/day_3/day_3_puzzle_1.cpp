#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    string line;
    string first_comp;
    string sec_comp;

    ifstream input_file ("/home/aliu/Self_Practice_Study/AdventCalendar/advent_calendar_2022/inputs/day_3.txt");
    if(input_file.is_open()){
        while(getline(input_file, line)){
            int line_length = 0;
            line_length = line.length();
            first_comp.append(line.substr(0,line_length/2));
            sec_comp.append(line.substr(line_length/2+1, line_length/2));

            //sort both strings 
            sort(first_comp.begin(), first_comp.end());
            sort(sec_comp.begin(), sec_comp.end());

            cout << first_comp << " " << sec_comp << "\n";


            first_comp = "";
            sec_comp = "";
        }
    }
    return 0;
}