#include <iostream>
#include <assert.h>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

string group_one;
string group_two;

//Functions

// This function will take a line from the input file and assign the two vectors for each elf group
int parse_input(string line){
    char str[line.length()+1];
    strncpy(str, line.c_str(), sizeof(str));
    str[sizeof(str)-1] = 0;
    
    //Split line by ","
    char *ptr;
    ptr = strtok(str, ",");
    group_one = ptr;
    while(ptr != NULL){
        group_two = ptr;
        ptr = strtok(NULL, ",");

    }

    std::vector<string> groups = {group_one, group_two};
    string low_range;
    string high_range;

    // Split group by "-"
    for(int i = 0; i < 2; i++){
        char group[groups[i].length()+1];
        strcpy(group, groups[i].c_str());

        ptr = strtok(group, "-");
        low_range = ptr;
        while(ptr != NULL){
            high_range = ptr;
            ptr = strtok(NULL, ",");

        }
        groups[i] = "";
        for(int x = stoi(low_range); x < stoi(high_range)+1; x++){
            groups[i]+=to_string(x);
        }

    }
    group_one = groups[0];
    group_two = groups[1];

    return 0;
}

// This function returns true if one of the groups is completely overlapped by the other. False otherwise
int check_for_overlap(string first_group, string sec_group){

    return 0;
}






//Listing tests
int test_parsed_input_single_digits(){parse_input("2-4,6-8"); return (group_one == "234");} 
int test_parsed_input_double_digits(){parse_input("53-54,2-53"); return (group_one == "5354");}
int test_parsed_input_triple_digits(){parse_input("100-102,3-5"); return (group_one == "100101102");}
int test_parsed_input_single_to_double_digits(){parse_input("8-11,3-5"); return (group_one == "891011");}
int test_parsed_input_double_to_triple_digits(){parse_input("98-102,3-5"); return (group_one == "9899100101102");}

int test_fully_contains(){return check_for_overlap("2345678", "34567");}
int test_overlapping_does_not_contain(){return check_for_overlap("567", "789");}
int test_does_not_contain(){return check_for_overlap("23", "45");}
int test_single_group(){return check_for_overlap("6", "6789");}


int main(){
    // test_parsed_input_single_digits();
    assert(test_parsed_input_single_digits());
    assert(test_parsed_input_double_digits());
    assert(test_parsed_input_triple_digits());

    // assert(test_fully_contains());
    // assert(test_overlapping());
    // assert(test_does_not_contain());


    return 0;
}