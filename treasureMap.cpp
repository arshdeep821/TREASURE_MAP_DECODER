#include "treasureMap.h"
#include "queue.h"
using namespace std;

treasureMap::treasureMap(const PNG & baseim, const PNG & mazeim, pair<int,int> s)
{

/* YOUR CODE HERE */
    start = s;
    base = baseim;
    maze = mazeim;
}

void treasureMap::setGrey(PNG & im, pair<int,int> loc){

/* YOUR CODE HERE */
    int column = loc.first;
    int row = loc.second;
    RGBAPixel * currPixel = im.getPixel(column, row);

    currPixel->r = 2*(currPixel->r/4);
    currPixel->g = 2*(currPixel->g/4);
    currPixel->b = 2*(currPixel->b/4);
}

void treasureMap::setLOB(PNG & im, pair<int,int> loc, int d){

/* YOUR CODE HERE */
    RGBAPixel * currPixel = im.getPixel(loc.first, loc.second);
    currPixel->r = (currPixel->r & 0b11111100) + ((d % 64) /16);
    currPixel->g = (currPixel->g & 0b11111100) + ((d % 16) / 4);
    currPixel->b = (currPixel->b & 0b11111100) + ((d% 4) / 1);
}

PNG treasureMap::renderMap(){

/* YOUR CODE HERE */
    //0
    PNG copyBase = base;
    //1a
    vector<vector<bool>> visited(base.width(), vector<bool>(base.height(), false));
    //1b
    vector<vector<int>> paths(base.width(), vector<int>(base.height(), 0));
    //2 
    Queue<pair<int, int>> locations;
    //3

    //3a
    int x = start.first;
    int y = start.second;

    visited[x][y] = true;

    //3b
    paths[x][y] = 0;

    //3c
    setLOB(copyBase, start, 0);
    //3d
    locations.enqueue(start);
    //4
    while (!locations.isEmpty()) {
        //4a
        pair<int, int> currLocation = locations.peek();
        locations.dequeue();

        int currX = currLocation.first;
        int currY = currLocation.second;
        int currDistance = paths[currX][currY];

        vector<pair<int, int>> allNeighbours = neighbors(currLocation);

        for (int i = 0; i<4; i++) {
            if (good(visited, currLocation, allNeighbours[i])) {
                pair<int, int> validNeighbor = allNeighbours[i];
                visited[validNeighbor.first][validNeighbor.second] = true;
                paths[validNeighbor.first][validNeighbor.second] = currDistance + 1;
                setLOB(copyBase, validNeighbor, currDistance + 1);
                locations.enqueue(validNeighbor);
            }
        }
    }
    return copyBase;
}


PNG treasureMap::renderMaze(){

/* YOUR CODE HERE */
    PNG copyBase = base;
    int startX = start.first;
    int startY = start.second;
    int width = base.width();
    int height = base.height();

    vector<vector<bool>> visited(base.width(), vector<bool>(base.height(), false));

    Queue<pair<int, int>> locations; 
    
    visited[startX][startY] = true;
    setGrey(copyBase, start);

    locations.enqueue(start);

    while (!locations.isEmpty()) {

        pair<int, int> currLocation = locations.peek();
        locations.dequeue();

        vector<pair<int, int>> allNeighbours = neighbors(currLocation);

        for (int i = 0; i<4; i++) {
            if (good(visited, currLocation, allNeighbours[i])) {
                pair<int, int> validNeighbor = allNeighbours[i];
                visited[validNeighbor.first][validNeighbor.second] = true;
                setGrey(copyBase, validNeighbor);
                locations.enqueue(validNeighbor);
            }
        }
    }

    // bottom right corner
    for (int x = startX; x<startX + 4; x++) {
        for (int y = startY; y< startY + 4; y++) {
            if ((x<width && y<height) && (x>=0 && y>=0)) {
                RGBAPixel * currPixel = copyBase.getPixel(x, y);
                currPixel->r = 255;
                currPixel->g = 0;
                currPixel->b = 0;
            } else {
                break;
            }
        }
    }

    //bottom left corner
    for (int x = startX; x>startX - 4; x--) {
        for (int y = startY; y< startY + 4; y++) {
            if ((x<width && y<height) && (x>=0 && y>=0)) {
                RGBAPixel * currPixel = copyBase.getPixel(x, y);
                currPixel->r = 255;
                currPixel->g = 0;
                currPixel->b = 0;
            } else {
                break;
            }
        }
    }

    //top right corner
    for (int x = startX; x<startX+4; x++) {
        for (int y = startY; y>startY-4; y--) {
            if ((x<width && y<height) && (x>=0 && y>=0)) {
                RGBAPixel * currPixel = copyBase.getPixel(x, y);
                currPixel->r = 255;
                currPixel->g = 0;
                currPixel->b = 0;
            } else {
                break;
            }
        }
    }

    //top left corner
    for (int x = startX; x>startX-4; x--) {
        for (int y = startY; y> startY - 4; y--) {
            if ((x<width && y<height) && (x>=0 && y>=0)) {
                RGBAPixel * currPixel = copyBase.getPixel(x, y);
                currPixel->r = 255;
                currPixel->g = 0;
                currPixel->b = 0;
            } else {
                break;
            }
        }
    }
    return copyBase;
}

bool treasureMap::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){

/* YOUR CODE HERE */
    int nextX = next.first;
    int nextY = next.second;

    int width = base.width();
    int height = base.height();

    if ((nextX < width && nextY < height) && (nextX >= 0 && nextY >= 0)) {
        if (!v[nextX][nextY]) {
            RGBAPixel * next = maze.getPixel(nextX, nextY);
            RGBAPixel * current = maze.getPixel(curr.first, curr.second);
            if (*next == *current) {
                return true;
            }
        }
    }
    return false;
}

vector<pair<int,int>> treasureMap::neighbors(pair<int,int> curr) {

/* YOUR CODE HERE */
    vector<pair<int, int>> neighbors;

    int currX = curr.first;
    int currY = curr.second;

    pair<int, int> currNeighbor;

    //left
    currNeighbor.first = currX - 1;
    currNeighbor.second = currY;
    neighbors.push_back(currNeighbor);
    //below
    currNeighbor.first = currX;
    currNeighbor.second = currY + 1;
    neighbors.push_back(currNeighbor);
    //right
    currNeighbor.first = currX + 1;
    currNeighbor.second = currY;
    neighbors.push_back(currNeighbor);
    //above
    currNeighbor.first = currX;
    currNeighbor.second = currY - 1;
    neighbors.push_back(currNeighbor);

    return neighbors;
}