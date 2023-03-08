#include <iostream>
#include <assert.h>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <fstream>

using namespace std;

vector<int> first_range = {};
vector<int> second_range = {};

//Functions

// This function takes in a string and a delimiter returns a vector containing the 
// two strings separated by the delimiter
 vector<string> splitString(string string_to_split, const char* delim){
    vector<string> split_strings;
    string first_half;
    string sec_half;
    
    //convert string to array of char
    char str[string_to_split.length()+1];
    strncpy(str, string_to_split.c_str(), sizeof(str));
    str[sizeof(str)-1] = 0;

    //split the string by the delimiter
    char *ptr;
    ptr = strtok(str, delim);
    first_half = ptr;
    while(ptr != NULL){
        sec_half = ptr;
        ptr = strtok(NULL, delim);

    }
    split_strings.push_back(first_half);
    split_strings.push_back(sec_half);
    // cout << split_strings[0] << ";" << split_strings[1] << endl;

    return split_strings;
}

// This function takes in a range in string form and a vector, 
// then creates an inclusive sequence with the specified vector
void rangeToSequence(string range, vector<int> &seq_group){
    vector<string> split_range;
    split_range = splitString(range, "-");
    if(split_range[0] != split_range[1]){
        for (int i = stoi(split_range[0]); i < stoi(split_range[1]) + 1; i++){
        seq_group.push_back(i);
        }
    }
    else {
        seq_group.push_back(stoi(split_range[0]));
        // cout << seq_group[0];
    }


}

// This function returns true if one of the groups is completely overlapped by the other. False otherwise
int check_for_overlap(vector<int> group_one, vector<int> group_two){
    // set longer range to group_one and shorter range to group_two
    vector<int> container_one;
    vector<int> container_two;
    if (group_one.size() > group_two.size()){
        container_one = group_one;
        container_two = group_two;

    }
    else {
        container_one = group_two;
        container_two = group_one;
    }

    bool contains = includes(container_one.begin(), container_one.end(), container_two.begin(), container_two.end());
    return (includes(container_one.begin(), container_one.end(), container_two.begin(), container_two.end()));
}


// String parsing tests
int test_split_string_first_half_comma(){
    vector<string> split_string = splitString("2-4,6-8", ","); 
    return (split_string[0]=="2-4");     
}
int test_split_string_sec_half_comma(){
    vector<string> split_string = splitString("2-4,6-8", ","); 
    return (split_string[1]=="6-8");   
}

// Contains? tests
int test_fully_contains(){
    vector<int> group_one = {2,3,4,5,6,7,8};
    vector<int> group_two = {3,4,5,6,7};
    return check_for_overlap(group_one, group_two);
}
int test_overlapping_does_not_contain(){
    vector<int> group_one = {5,6,7};
    vector<int> group_two = {7,8,9};
    return !check_for_overlap(group_one, group_two);
}
int test_does_not_contain(){
    vector<int> group_one = {2,3};
    vector<int> group_two = {4,5};
    return !check_for_overlap(group_one, group_two);
}
int test_single_group_contains(){
    vector<int> group_one = {6,7,8,9};
    vector<int> group_two = {6};
    return check_for_overlap(group_one, group_two);
} 
int test_fully_contains_short_first(){
    vector<int> group_one = {3,4,5,6,7};
    vector<int> group_two = {2,3,4,5,6,7,8};
    return check_for_overlap(group_one, group_two);
}


// Range-of-numbers to sequence-of-numbers tests
int test_range_to_sequence(){
    first_range = {};
    rangeToSequence("2-4", first_range); 
    vector<int> test_range = {2,3,4};
    return (first_range == test_range); 
}
int test_range_to_sequence_equal_ends(){
    first_range = {};
    rangeToSequence("2-2", first_range); 
    vector<int> test_range = {2};
    return (first_range == test_range); 
}
int test_range_to_sequence_two_digits(){
    first_range = {};
    rangeToSequence("12-14", first_range); 
    vector<int> test_range = {12,13,14};
    return (first_range == test_range); 
}
int test_range_to_sequence_two_to_three(){
    first_range = {};
    rangeToSequence("2-10", first_range); 
    vector<int> test_range = {2,3,4,5,6,7,8,9,10};
    return (first_range == test_range); 
}


int main(){
    assert(test_fully_contains());
    assert(test_overlapping_does_not_contain());
    assert(test_does_not_contain());
    assert(test_single_group_contains());
    assert(test_fully_contains_short_first());

    assert(test_split_string_first_half_comma());
    assert(test_split_string_sec_half_comma());

    assert(test_range_to_sequence());
    assert(test_range_to_sequence_equal_ends());
    assert(test_range_to_sequence_two_digits());
    assert(test_range_to_sequence_two_to_three());

    
    int elf_counter = 0;

    string line;
    vector<int> group_one;
    vector<int> group_two;

    ifstream input_file ("/home/aliu/Self_Practice_Study/AdventCalendar/advent_calendar_2022/inputs/day_4.txt");
    if(input_file.is_open()){
        while(getline(input_file, line)){
            //split current line into the two string ranges
            vector<string> split_line = splitString(line, ",");
            
            //assign the vectors group_one and group_two to the sequence defined by the ranges in split_line
            rangeToSequence(split_line[0], group_one);
            rangeToSequence(split_line[1], group_two);

            if(check_for_overlap(group_one, group_two)){
                elf_counter++;
            }
            group_one = {};
            group_two = {};
        }
    }
    cout << "There are " << elf_counter << " groups that overlap";
    return 0;
}