#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <string.h>
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


// This function gets a string as an input and parses it for the moves
vector<int> ParseLineForMoves(string line){
    int first_column = 0;
    int sec_column = 0;
    int move_count = 0;


    int from_index = line.find("from");
    move_count = stoi(line.substr(5,(from_index -6)));
    first_column = stoi(line.substr(from_index+5,1));
    sec_column = stoi(line.substr(from_index+10, 1));

    cout << "move " << move_count << " from " << first_column << " to " << sec_column; 
    vector<int> results = {first_column,sec_column,move_count};
    return results;

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
int TestParseLineForMoves(){
    string test_line = "move 2 from 2 to 8";
    vector<int> expected_result = {2,8,2};
    vector<int> actual_result = ParseLineForMoves(test_line);
    return actual_result == expected_result;
        
}

int TestParseLineForMovesDoubleDigits(){
    string test_line = "move 22 from 5 to 9";
    vector<int> expected_result = {5,9,22};
    vector<int> actual_result = ParseLineForMoves(test_line);
    return actual_result == expected_result;
}


// This test passes in a move instruction and an m x n matrix and applies the move to the matrix. 
int TestApplyTransform(){
    return 1;
}



/****Main function****/
int main(){
    assert(TestParseInputCrates());
    assert(TestParseLineForMoves());
    // assert(TestParseLineForMovesDoubleDigits());
    return 0;
}