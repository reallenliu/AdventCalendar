#include <string.h>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <assert.h>

using namespace std;


/**FUNCTIONS**/



// Function to go through a string N times and determine if there is a substring of length 4 that contains repeating characters
// Returns the position of the character right after the end of the marker
int FindStartOfPacket(string inputString){

    return 0;
}

// Function that determines if there are repeating characters in a string. 
// Also returns the positions of the repeated characters in format:
// {true/false, first_pos, sec_pos}
vector<int> RepeatsChar(string inputString){
    int length = inputString.size();
    vector<int> result;

    for (int x = 0; x < length; x++){
        for (int i = x+1; i < length; i++)
        {
            if(inputString[x] == inputString[i]){
                result.push_back(1);
                result.push_back(x);
                result.push_back(i);
                return result;
            }
        }
    }
    result.push_back(0);
    result.push_back(0);
    result.push_back(0);
    return result;
}


// Gets a string known to have repeating elements and the results of RepeatsChar
// and returns the next element in order to skip duplicates
int SkipDuplicate(string inputString, vector<int> repeatsResult){
    int first_pos = repeatsResult[1];
    return first_pos+1;
}

/**TESTS**/


// Tests for final result
int testHasMarkerOne(){
    string test_string = "mjqjpqmgbljsphdztnvjfqwrcgsmlb";
    if(FindStartOfPacket(test_string) == 7){
        return 1;
    }
    return 0;
}
int testHasMarkerTwo(){
    string test_string = "bvwbjplbgvbhsrlpgdmjqwftvncz";
    if(FindStartOfPacket(test_string) == 5){
        return 1;
    }
    return 0;
}
int testHasMarkerThree(){
    string test_string = "nppdvjthqldpwncqszvftbrmjlhg";
    if(FindStartOfPacket(test_string) == 6){
        return 1;
    }
    return 0;
}
int testHasMarkerFour(){
    string test_string = "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg";
    if(FindStartOfPacket(test_string) == 10){
        return 1;
    }
    return 0;
}
int testHasMarkerFive(){
    string test_string = "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw";
    if(FindStartOfPacket(test_string) == 11){
        return 1;
    }
    return 0;
}
int testDoesNotHaveMarker(){
    string test_string = "mkkrmkkrmkkrmkkr";
    if(FindStartOfPacket(test_string) == 0){
        return 1;
    }
    return 0;
}


// Tests for repeating characters in a given string
int testHasRepeatingChar(){
    string input_string = "mkkr";
    vector<int> expected_result = {1,1,2};
    return (RepeatsChar(input_string) == expected_result);
}

int testDoesNotHaveRepeatingChar(){
    string input_string = "mkdr";
    vector<int> expected_result = {0,0,0};
    return (RepeatsChar(input_string) == expected_result);
}


// Tests for skipping duplicate repeating substrings
int testSkipRepeatOne(){
    string input_string = "znrn";
    vector<int> repeatsResults = RepeatsChar(input_string);
    return (SkipDuplicate(input_string, repeatsResults) == 2);
}
int testSkipRepeatTwo(){
    string input_string = "zrnn";
    vector<int> repeatsResults = RepeatsChar(input_string);
    return (SkipDuplicate(input_string,repeatsResults) == 3);
}
int testSkipRepeatAdjacent(){
    string input_string ="znnr";
    vector<int> repeatsResults = RepeatsChar(input_string);
    return (SkipDuplicate(input_string,repeatsResults) == 2);
}

/**MAIN IMPLEMENTATION**/
int main(){

    // assert(testHasMarkerOne());
    // assert(testHasMarkerTwo());
    // assert(testHasMarkerThree());
    // assert(testHasMarkerFour());
    // assert(testHasMarkerFive());
    // assert(testDoesNotHaveMarker());


    assert(testHasRepeatingChar());
    assert(testDoesNotHaveRepeatingChar());

    assert(testSkipRepeatOne());
    assert(testSkipRepeatTwo());
    assert(testSkipRepeatAdjacent());

    return 0;
}
