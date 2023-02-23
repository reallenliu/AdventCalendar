#include <iostream>
#include <assert.h>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

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
    cout << split_strings[0] << ";" << split_strings[1] << endl;

    return split_strings;
}

// This function takes in range in string form and a vector, 
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
        cout << seq_group[0];
    }


}

// This function returns true if one of the groups is completely overlapped by the other. False otherwise
int check_for_overlap(vector<int> group_one, vector<int> group_two){
    bool contains = includes(group_one.begin(), group_one.end(), group_two.begin(), group_two.end());
    return (includes(group_one.begin(), group_one.end(), group_two.begin(), group_two.end()));
}

//Listing tests
// int test_parsed_input_single_digits(){parse_input("2-4,6-8"); return (first_half == "234");} 
// int test_parsed_input_double_digits(){parse_input("53-54,2-53"); return (first_half == "5354");}
// int test_parsed_input_triple_digits(){parse_input("100-102,3-5"); return (first_half == "100101102");}
// int test_parsed_input_single_to_double_digits(){parse_input("8-11,3-5"); return (first_half == "891011");}
// int test_parsed_input_double_to_triple_digits(){parse_input("98-102,3-5"); return (first_half == "9899100101102");}

// Contains tests
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

// String parsing tests
int test_split_string_first_half_comma(){
    vector<string> split_string = splitString("2-4,6-8", ","); 
    return (split_string[0]=="2-4");     
}
int test_split_string_sec_half_comma(){
    vector<string> split_string = splitString("2-4,6-8", ","); 
    return (split_string[1]=="6-8");   
}

//Range to sequence tests
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
    assert(test_single_group_contains());
    assert(test_overlapping_does_not_contain());
    assert(test_does_not_contain());
    assert(test_split_string_first_half_comma());
    assert(test_split_string_sec_half_comma());
    assert(test_range_to_sequence());
    assert(test_range_to_sequence_equal_ends());
    // assert(test_range_to_sequence_two_to_three());
    // test_parsed_input_single_digits();
    // assert(test_parsed_input_single_digits());
    // assert(test_parsed_input_double_digits());
    // assert(test_parsed_input_triple_digits());

    // assert(test_fully_contains());
    // assert(test_overlapping());
    // assert(test_does_not_contain());


    return 0;
}