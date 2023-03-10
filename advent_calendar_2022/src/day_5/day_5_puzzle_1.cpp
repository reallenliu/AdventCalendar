#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

/****Functions****/

// Each line length is 34
// This function gets an input file and returns a matrix representing the arrangement of crates
void ParseInputCrates(){
    string line;
    vector<string> rows = {};
    ifstream input_file ("/home/aliu/Self_Practice_Study/AdventCalendar/advent_calendar_2022/inputs/day_5.txt");
    if(input_file.is_open()){
        while(getline(input_file, line)){
            if (line == "\n"){
                break;
            }
            cout << line << endl;
            rows.push_back(line);
        }
    }
    cout << "done!";

}



/****Tests****/

//This test passes an input of arranged crates and returns an m x n matrix representing the input. 
int TestParseInputCrates(){
    return 1;
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
    ParseInputCrates();
    return 0;
}