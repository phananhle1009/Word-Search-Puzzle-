//============================================
// Phan Anh
// October 6, 2023
// cs173_project_4.cpp
// This program will perform a word search
// puzzle. The program will read in a puzzle
// and a list of words to find, and then print
// the locations of those words.
//============================================
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
// constant for column and row size of the grid
const int grid_size = 14;
// function declaratons
bool is_within_grid(int row, int col, int rows, int cols);
void word_search(char grid[grid_size][grid_size], int rows, int cols, string word);

// main function
int main(void)
{
// initializng the word grid 2d array
    char word_grid[grid_size][grid_size];

// reading in the word grid from stdin
    for (int i = 0; i < grid_size; i++)
        for (int j = 0; j < grid_size; j++)
            cin >> word_grid[i][j];

// reading in the size of the word list
cin.ignore(10, '\n');
string temp_word_count;
cin >> temp_word_count;
int word_count = stoi(temp_word_count);

// initializing the word list array
string word_list[word_count];

 // reading in the words of the word list
for (int i = 0; i < word_count; i++)
    cin >> word_list[i];

 // printing out the word grid
for (int i = 0; i < grid_size; i++)
{
    for (int j = 0; j < grid_size; j++)
    cout << setw(2) << word_grid[i][j];
    cout << endl;
}
cout << endl;

 // initializing the word search
int rows = grid_size;
int cols = grid_size;
for (const string word : word_list)
word_search(word_grid, rows, cols, word);

return 0;
}

//============================================
// is_within_grid
// checks if the current position is still in
// the word grid or not
// PARAMETERS:
// integers of the current row, current column,
// row size, and column size of the grid
// RETURN VALUE: a boolean depending on whether
// or not the position is still in the grid
//============================================
bool is_within_grid(int row, int col, int rows, int cols)
{
    return (row >= 0 && row < rows && col >= 0 && col < cols);
}

//============================================
// word_search
// search the word in a word list, prints out
// the earliest location of the word if found
// PARAMETERS:
// a 2D array of the word grid, integers of the
// row size and column size of the grid, a
// string of the word needed to be found
// RETURN VALUE: none
//============================================
void word_search(char grid[grid_size][grid_size], int rows, int cols, string word)
{
    // creating the arrays for directions/orientations
    // array for directions to move between rows
    int dir_row[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
    // array for directions to move between columns
    int dir_col[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
    // array for the names of the directions corresponding to the previous two arrays
    string dir_name[] = { "going up", "going up right", "going right", "going down right", "going down", "going down left", "going left", "going up left" };
    // boolean to check whether the word is found or not
    bool check = false;
    // boolean to check whether the word has been found or not to avoid duplications
    bool duplicate_check = false;

    int word_length = word.length();
    // iterating through all of the rows and columns of the word grid
    for (int row = 0; row < rows; row++)
        for (int col = 0; col < cols; col++)
        // go through each direction in the direction arrays
        for (int dir = 0; dir < 8; dir++)
        {
            int r = row, c = col;
            int i;
            // in the chosen direction, checks if the word can be found or not
            for (i = 0; i < word_length; i++)
            {
                // if the position is out of the grid or
                // one character is different from the current charater of the word,
                // the search will stop immediately and moves= to a different direction
                if (!is_within_grid(r, c, rows, cols) || grid[r][c] != word[i])
                break;
                // moving the search position one step forward in the direction being chosen
                r += dir_row[dir];
                c += dir_col[dir];
            }

            // if the word has been found and this is the first time the word has been found
            if (i == word_length && !duplicate_check)
            {
            // if the word is only 1 character, it will report the direction as "up"
                if (word_length == 1)
                    cout << word << " found at " << "(" << row << "," << col << ") " << dir_name[0] << endl;
                // otherwise, it will report the starting location and the direction of the word
                else
                    cout << word << " found at " << "(" << row << "," << col << ") " << dir_name[dir] << endl;

            // marks that the word has been found
                check = true;
            // marks that the word has been found, and that there is no need to find the word again
                duplicate_check = true;
            }
        }
// if the word isn't found, report "not found" for the word
if (!check)
    cout << word << " not found" << endl;
}