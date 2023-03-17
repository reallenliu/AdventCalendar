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

    // cout << "move " << move_count << " from " << first_column << " to " << sec_column; 
    vector<int> results = {first_column,sec_column,move_count};
    return results;

}

// This function takes in a column number and a matrix and returns the next non-zero character on the column. Also includes the position of the element
vector<char> findNextColumnElement(int column_of_interest, vector<vector<char>> cargo_ship){
    vector<char> full_column = {};
    vector<char> result = {' ',' '};
    int height = cargo_ship.size();
    for(int x = 0; x < height; x++){
        char current_element = cargo_ship[x][column_of_interest-1];
        if(current_element != '0'){
            // If the column is not empty, return the element along with the index of it
            result[0]= current_element;
            char pos = x + 1 + '0';
            result[1] = pos;
            return result;
        }
    }
    // If the column is empty, return '0' and the height of the matrix
    char c = height + '0';
    result = {'0', c};
    return result;
}


// This function gets a move_instructions vector and a matrix (passed by reference). It then applies the moves to the matrix
void ApplyTransformToCrates(vector<int> instructions, vector<vector<char>> &cargo_ship){
    int first_column = instructions[0];
    int sec_column = instructions[1];
    int moves = instructions[2];

    int current_matrix_height = cargo_ship.size();
    int current_matrix_width = cargo_ship[0].size();
    // move `moves` amount of elements from first_column to sec_column
    // - if the column in sec_column is full, add another row above it and insert the element into the correct position
    for(int i = 0; i < moves; i++){
        // Get the top element position in the first column
        vector<char> top_element = findNextColumnElement(first_column, cargo_ship);
        //check state of column to move_to
        vector<char> destination_element = findNextColumnElement(sec_column, cargo_ship);
        
        //Gets the next element row index from the bottom of the first column
        int bottom_element_row = (top_element[1]-'0')+ moves - 1 - i;
        //Gets the next element to move
        char next_el = cargo_ship[bottom_element_row-1][first_column-1];

        // If there is space above the destination column, move the top_element to it
        if (destination_element[1] != '1'){
            int destination_row = destination_element[1]-'0'-2;
            cargo_ship[destination_row][sec_column-1] = next_el;
            cargo_ship[bottom_element_row-1][first_column-1] = '0';
        } 
        else{
            //Construct vector to insert
            vector<char> new_row = {};
            for(int x = 0; x < current_matrix_width; x ++){
                new_row.push_back('0');
            }
            new_row[sec_column-1] = next_el;
            //insert new row with element
            cargo_ship.insert(cargo_ship.begin(), new_row);
            cargo_ship[bottom_element_row][first_column-1] = '0';
        }
    }
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
    // Move 1 from 2 to 1
    vector<int> move_instructions = {2,1,1};
    vector<vector<char>> input_matrix = {   {'0', 'D', '0'},
                                            {'N', 'C', '0'},
                                            {'Z', 'M', 'P'} };
    vector<vector<char>> expected_matrix = {{'D', '0', '0'},
                                            {'N', 'C', '0'},
                                            {'Z', 'M', 'P'} };
    ApplyTransformToCrates(move_instructions, input_matrix);
    for(int x = 0; x < expected_matrix.size(); x++){
        if (expected_matrix[x] != input_matrix[x]){
            return false;
        }
    }
    return true;
}

int TestApplyTransformMultiple(){
    // Move 2 from 1 to 3
    vector<int> move_instructions = {1,3,2};
    vector<vector<char>> input_matrix = {{'D', '0', '0'},
                                         {'N', 'C', '0'},
                                         {'Z', 'M', 'P'}};
    vector<vector<char>> expected_matrix = {{'0', '0', 'D'},
                                            {'0', 'C', 'N'},
                                            {'Z', 'M', 'P'} };
    ApplyTransformToCrates(move_instructions, input_matrix);
    for(int x = 0; x < expected_matrix.size(); x++){
        if (expected_matrix[x] != input_matrix[x]){
            return false;
        }
    }
    return true; 
}

int TestApplyTransformAddRow(){
    // Move 1 from 2 to 1
    vector<int> move_instructions = {1,3,3};
    vector<vector<char>> input_matrix = {{'D', '0', '0'},
                                         {'N', 'C', '0'},
                                         {'Z', 'M', 'P'}};
    vector<vector<char>> expected_matrix = {{'0', '0', 'D'},
                                            {'0', '0', 'N'},
                                            {'0', 'C', 'Z'},
                                            {'0', 'M', 'P'} };
    ApplyTransformToCrates(move_instructions, input_matrix);
    for(int x = 0; x < expected_matrix.size(); x++){
        if (expected_matrix[x] != input_matrix[x]){
            return false;
        }
    }
    return true;
}


// Tests for finding next element in specified column
int testFindNextColumnOneElement(){
    vector<vector<char>> expected_matrix = {{'0', 'D', '0'},
                                            {'N', 'C', '0'},
                                            {'Z', 'M', 'P'} };
    int column = 1;
    vector<char> expected_result = {'N', '2'};

    return (findNextColumnElement(column, expected_matrix) == expected_result);

}

int testFindNextColumnTwoElement(){
    vector<vector<char>> expected_matrix = {{'0', 'D', '0'},
                                            {'N', 'C', '0'},
                                            {'Z', 'M', 'P'} };
    int column = 2;
    vector<char> expected_result = {'D', '1'};

    return (findNextColumnElement(column, expected_matrix) == expected_result);
}

int testFindNextColumnThreeElement(){
    vector<vector<char>> expected_matrix = {{'0', 'D', '0'},
                                            {'N', 'C', '0'},
                                            {'Z', 'M', 'P'} };
    int column = 3;
    vector<char> expected_result = {'P', '3'};

    return (findNextColumnElement(column, expected_matrix) == expected_result);
}

int testFindNextColumnEmptyElement(){
    vector<vector<char>> expected_matrix = {{'0', 'D', '0'},
                                            {'N', 'C', '0'},
                                            {'Z', 'M', '0'} };
    int column = 3;
   vector<char> expected_result = {'0', '3'};

    return (findNextColumnElement(column, expected_matrix) == expected_result);
}


/****Main function****/
int main(){
    // Parsing tests
    assert(TestParseInputCrates());
    assert(TestParseLineForMoves());
    assert(TestParseLineForMovesDoubleDigits());


    // get next element in column tests
    assert(testFindNextColumnOneElement());
    assert(testFindNextColumnTwoElement());
    assert(testFindNextColumnThreeElement());
    assert(testFindNextColumnEmptyElement());

    // Apply Transform tests
    assert(TestApplyTransform());
    assert(TestApplyTransformMultiple());
    assert(TestApplyTransformAddRow());

    // string line;
    // string file_path = "/home/aliu/Self_Practice_Study/AdventCalendar/advent_calendar_2022/inputs/day_5.txt";
    // vector<vector<char>> cargo_ship = ParseInputCrates(file_path);
    
    // ifstream input_file (file_path);
    // //Need a function to get each line of instructions after the cargo ship
    // if(input_file.is_open()){
    //     while(getline(input_file, line)){
    //         if(line[0] == 'm'){
    //             vector<int> parsed_instr = ParseLineForMoves(line);
    //             ApplyTransformToCrates(parsed_instr, cargo_ship);
    //         }
    //     }
    // }

    // for(int x = 0; x < cargo_ship[0].size(); x++){
    //     vector<char> next_char = findNextColumnElement(x+1, cargo_ship);
    //     cout << next_char[0];
    // }

    return 0;
}