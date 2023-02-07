#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;


bool cmp(const string str_one, const string str_two){
    return str_one.size() < str_two.size();
}

char search_for_item(string first_elf, string sec_elf, string third_elf){
    string longest_elf;
    string mid_elf;
    string short_elf;
    
    vector<string> elves {first_elf, sec_elf, third_elf};
    sort(elves.begin(), elves.end(), cmp);
    longest_elf = elves[2];
    mid_elf = elves[1];
    short_elf = elves[0];

    // Look through second elf first. If a match occurs, look through third elf. If match occurs, return result
    for(int x = 0;x < longest_elf.size(); x++){                        
        int low_first = 0;
        int high_first = mid_elf.size() - 1;
        int mid_first;
        char item_to_look_for = longest_elf[x];

        while(low_first <= high_first){
            mid_first = low_first + (high_first - low_first) / 2;
            if (item_to_look_for == mid_elf[mid_first]){
                int low_sec = 0;
                int high_sec = short_elf.size() - 1;
                int mid_sec;
                //Searching through shortest elf
                while(low_sec <= high_sec){
                    mid_sec = low_sec + (high_sec - low_sec) / 2;
                    if(item_to_look_for == short_elf[mid_sec]){
                        cout << "Similar badge: " << item_to_look_for << "\n\n";
                        return item_to_look_for;
                    }
                    else if (item_to_look_for > short_elf[mid_sec]){
                        low_sec = mid_sec + 1;
                    }
                    else {
                        high_sec = mid_sec - 1;
                    }
                }
                
                if (item_to_look_for > mid_elf[mid_first]){
                    low_first = mid_first + 1;
                }
                else {
                    high_first = mid_first - 1;
                }
            }
            else if (item_to_look_for > mid_elf[mid_first]){
                low_first = mid_first + 1;
            }
            else {
                high_first = mid_first - 1;
            }
        }
    }
    return 0;
}

int main(){
    string line;
    string first_elf,sec_elf,third_elf;
    int total_sum;

    ifstream input_file ("/home/aliu/Self_Practice_Study/AdventCalendar/advent_calendar_2022/inputs/day_3.txt");
    if(input_file.is_open()){
        while(getline(input_file, first_elf) && getline(input_file, sec_elf) && getline(input_file, third_elf)){
            
            // Sort the strings
            sort(first_elf.begin(), first_elf.end());
            sort(sec_elf.begin(), sec_elf.end());
            sort(third_elf.begin(), third_elf.end());

            cout << first_elf << "\n" << sec_elf << "\n" << third_elf << "\n";
            char similar_item = search_for_item(first_elf, sec_elf, third_elf);

            if (similar_item >= 65 && similar_item <= 90){
                total_sum += similar_item-38;
            }
            else {
                total_sum+= similar_item-96;
            }

        }
        cout << "Total_priority value: " << total_sum;
    }
    return 0;
}