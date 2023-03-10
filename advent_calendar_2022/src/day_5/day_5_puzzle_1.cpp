#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <assert.h>

using namespace std;

/****Functions****/

// Each line length is 34
// This function gets an input file and returns a matrix representing the arrangement of crates
vector<vector<char>> ParseInputCrates(string file_path){
    string line;
    vector<string> rows = {};
    vector<vector<char>> cargo_ship; 
    ifstream input_file (file_path);
    
    if(input_file.is_open()){
        while(getline(input_file, line)){
            if (line == ""){
                break;
            }
            // cout << line << endl;
            rows.push_back(line);
        }
    }

    int line_length = rows[rows.size()-1].size();
    int num_of_cols = rows[rows.size()-1][line_length-2] - 48;
    // cout << line_length;
    // cout << num_of_cols;

    vector<char> temp_vector;

    for(int i = 0; i < rows.size()-1; i++){
        string current_line = rows[i];
        temp_vector = {};
        for(int x = 1; x < line_length; x+=4){
            char current_elem = current_line[x];
            if (current_line[x] == ' '){
                temp_vector.push_back('0');
            }
            else{
                temp_vector.push_back(current_line[x]);
            }
        }
        cargo_ship.push_back(temp_vector);
    }
    return cargo_ship;
}



/****Tests****/

//This test passes an input of arranged crates and returns an m x n matrix representing the input. 
int TestParseInputCrates(){
    string test_file = "/home/aliu/Self_Practice_Study/AdventCalendar/advent_calendar_2022/inputs/day_5_tests/cargo_order_test.txt";
    vector<vector<char>> expected_matrix = {{'0', 'D', '0'},
                                            {'N', 'C', '0'},
                                            {'Z', 'M', 'P'} };
    vector<vector<char>> actual_matrix = ParseInputCrates(test_file);
    for(int x = 0; x < expected_matrix.size(); x++){
        if (expected_matrix[x] != actual_matrix[x]){
            return false;
        }
    }
    return true;
    
}

// This test passes a transform instruction into the parsing function 
int TestParseTransformLine(){
    return 1;
}


// This test passes in a move instruction and an m x n matrix and applies the move to the matrix. 
int TestApplyTransform(){
    return 1;
}


int main(){
    assert(TestParseInputCrates());
    return 0;
}