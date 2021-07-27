#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

// Map class
class Map {
public:
    const static int mapWidth = 6;
    const static int mapHeight = 5;
    vector<vector<int> > grid = {
        { 0, 1, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0 }
    };

    vector<vector<int>> manhattan = {
        { 9, 8, 7, 6, 5, 4 },
        { 8, 7, 6, 5, 4, 3 },
        { 7, 6, 5, 4, 3, 2 },
        { 6, 5, 4, 3, 2, 1 },
        { 5, 5, 3, 2, 1, 0 }
    };

};

// Planner class
class Planner : Map {
public:
    int start[2] = { 0, 0 };
    int goal[2] = { mapHeight - 1, mapWidth - 1 };
    int cost = 1;

    string movements_arrows[4] = { "^", "<", "v", ">" };

    vector<vector<int> > movements{
        { -1, 0 },
        { 0, -1 },
        { 1, 0 },
        { 0, 1 }
    };
};

// Template function to print 2D vectors of any type
template <typename T>
void print2DVector(T Vec)
{
    for (int i = 0; i < Vec.size(); ++i) {
        for (int j = 0; j < Vec[0].size(); ++j) {
            cout << Vec[i][j] << ' ';
        }
        cout << endl;
    }
}

void search(Map map, Planner planner)
{
    vector<vector<int>> box = { {0,0,0,0} }; // [f,g,x,y]
    vector<vector<int>> temp = {  };
    while (1) {
        box[0][1] += 1;

        int temp1;
        int temp2;

        for (int i = 0; i < 4; i++) {
            cout << box[0][0] << " " << box[0][1] << " " << box[0][2] << " " << box[0][3] << "\n";

            int manhattanVal;
            if (box[0][2] + planner.movements[i][0] < 0 || box[0][3] + planner.movements[i][1] < 0 ||
                box[0][2] + planner.movements[i][0] >= map.mapHeight || box[0][3] + planner.movements[i][1] >= map.mapWidth) {
                manhattanVal = 100;
            }
            else {
                manhattanVal = map.manhattan[box[0][2] + planner.movements[i][0]][box[0][3] + planner.movements[i][1]];
            }

            temp.insert(temp.begin(), {box[0][0] + manhattanVal,
                box[0][1], box[0][2] + planner.movements[i][0], box[0][3] + planner.movements[i][1] });
            
            //Out of scope
            if (temp[0][2] < 0 || temp[0][3] < 0 || temp[0][2] >= map.mapHeight || temp[0][3] >= map.mapWidth) {
                cout << temp[0][0] << " " << temp[0][1] << " " << temp[0][2] << " " << temp[0][3] << "\n";
                temp.erase(temp.begin());
                cout << "Robot detected out of scope. Vector was removed." << "\n";
                continue;
            }

            //Obstacle Check
            if (map.grid[temp[0][2]][temp[0][3]] == 1) {
                cout << temp[0][0] << " " << temp[0][1] << " " << temp[0][2] << " " << temp[0][3] << "\n";
                temp.erase(temp.begin());
                cout << "Robot detected obatacle. Vector was removed." << "\n";
                continue;
            }

            cout << temp[0][0] << " " << temp[0][1] << " " << temp[0][2] << " " << temp[0][3] << "\n";
            box.push_back(temp.front());
            cout << "Vector push backed.\n";
            temp.erase(temp.begin());
            
        }
        cout << "\n";
        box.erase(box.begin());
        
        for (int i = 0; i < box.size() - 1; ++i) {
            cout << box.size() << "\n";
            
            if (box[0][0] >= box[1][0]) {
                box.erase(box.begin());
            }else {
                box.push_back(box.front());
                box.erase(box.begin());
            }
        }
        cout << box.size() << "\n";

        //box.erase(box.begin());
        
        if (box[0][2] == planner.goal[0] && box[0][3] == planner.goal[1]) {
            break;
        }
    }


    cout << box[0][0] << " " << box[0][1] << " " << box[0][2] << " " << box[0][3];
}

int main()
{
    // Instantiate map and planner objects
    Map map;
    Planner planner;

    // Search for the expansions
    search(map, planner);

    return 0;
}
