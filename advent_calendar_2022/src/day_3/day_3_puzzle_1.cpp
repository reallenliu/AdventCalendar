#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;


char search_for_item(string first_comp, string second_comp, int length){
    string identical_item = "";
    for (int x = 0; x < length; x++){
        int lower = 0;
        int upper = length-1;
        int mid = length / 2;
        while (lower <= upper ){
            mid = lower + (upper-lower)/2;
            if (first_comp[x] == second_comp[mid]){
                cout << second_comp[mid] << "\n";
                char sames = second_comp[mid];
                return sames;
            }
            else if (first_comp[x] > second_comp[mid]){
                lower = mid +1;
            }
            else {
                upper = mid - 1;
            }
        }
    }
    return 0;
}

int main(){
    string line;
    string first_comp;
    string sec_comp;
    int total_sum;

    ifstream input_file ("/home/aliu/Self_Practice_Study/AdventCalendar/advent_calendar_2022/inputs/day_3.txt");
    if(input_file.is_open()){
        while(getline(input_file, line)){
            int line_length = 0;
            line_length = line.length();
            first_comp.append(line.substr(0,line_length/2));
            sec_comp.append(line.substr(line_length/2, line_length/2));

            //sort both strings 
            sort(first_comp.begin(), first_comp.end());
            sort(sec_comp.begin(), sec_comp.end());
            cout << first_comp << " " << sec_comp << "\n";

            char similar_item = search_for_item(first_comp, sec_comp, line_length/2);
            
            if (similar_item >= 65 && similar_item <= 90){
                total_sum += similar_item-38;
            }
            else {
                total_sum+= similar_item-96;
            }
            // cout << total_sum << "\n";
            first_comp = "";
            sec_comp = "";
        }
        cout << "Total_priority value: " << total_sum;
    }
    return 0;
}