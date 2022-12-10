#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <list>
#include <vector>
using namespace std;

// map where vectors which were already calculated are saved
map < vector<int>, unsigned long long > savedCombinations;


int getNextSquare(vector<int> grid) {
    int line = 0;

    for(long unsigned int i = 0; i < grid.size(); i++) {
        if(grid[i] >= grid[line]) {
            line = i;
        }
    }

    return line;
}


unsigned long long calculateCombinations(vector<int> grid) {
    // checking if the map already has information about this specific grid
    if(savedCombinations.find(grid) != savedCombinations.end()) {
        return savedCombinations.at(grid);
    }
    else {

        vector<int> new_grid = grid;
        unsigned long long grid_combs = 0;
        int line = getNextSquare(new_grid);


        // checking if the grid has only one more possibility
        if(new_grid[line] <= 1) {
            savedCombinations.insert({new_grid, 1});
            return 1;
        }

        // loop for removing squares that are 2x2 or bigger
        int i = 1;
        while((grid[line] == grid[line - i]) && grid[line] > i) { 
            for(int j = 0; j <= i; j++) {
                new_grid[line-j] -= i + 1;
            }
            grid_combs += calculateCombinations(new_grid);
            new_grid = grid;
            i++;
        } 

        new_grid = grid;
        new_grid[line]--;
        grid_combs += calculateCombinations(new_grid);
        savedCombinations.insert({grid, grid_combs});


        return grid_combs;
    }
}


int main() {
    int lines;
    int columns;
    int input;
    int nonzero = 0;

    // input read
    cin >> lines;
    cin >> columns;

    vector<int> grid;

    for(int i = 0; i < lines; i++){
        cin >> input;
        grid.push_back(input);
        if (input != 0){
            nonzero = 1;            
        }
    }
    
    if(nonzero == 1)
        cout << calculateCombinations(grid) << endl;
    else
        cout << nonzero << endl;

}