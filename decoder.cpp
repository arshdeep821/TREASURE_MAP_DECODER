#include "decoder.h"
#include "queue.h"
#include "stack.h"
using namespace std;

decoder::decoder(const PNG & tm, pair<int,int> s)
   :start(s),mapImg(tm) {

/* YOUR CODE HERE */
   pair<int, int> zeroPair;
   zeroPair.first = 0;
   zeroPair.second = 0;
   Queue<pair<int, int>> q;
   vector<vector<bool>> visited(mapImg.height(), vector<bool>(mapImg.width(), false));
   vector<vector<int>> distances(mapImg.height(), vector<int>(mapImg.width(), 0));
   vector<vector<pair<int, int>>> hintVector(mapImg.height(), vector<pair<int, int>>(mapImg.width(), zeroPair));
   
   
   visited[start.second][start.first] = true;
   hintVector[start.second][start.first] = start;
   distances[start.second][start.first] = 0;
   q.enqueue(start);

   pair<int, int> currLast = start;

   while(!q.isEmpty()) {
      pair<int, int> currLocation = q.peek();
      q.dequeue();

      int currX = currLocation.first;
      int currY = currLocation.second;
      int currDistance = distances[currY][currX];


      vector<pair<int, int>> allNeighbours = neighbors(currLocation);
      for (int i = 0; i<4; i++) {
         if(good(visited, distances, currLocation, allNeighbours[i])) {
            pair<int, int> validNeighbor = allNeighbours[i];
            visited[validNeighbor.second][validNeighbor.first] = true;
            distances[validNeighbor.second][validNeighbor.first] = currDistance + 1;
            hintVector[validNeighbor.second][validNeighbor.first] = currLocation;

            int currEndDistance = distances[currLast.second][currLast.first];
            int validNeighborDistance = distances[validNeighbor.second][validNeighbor.first];
            if (validNeighborDistance >= currEndDistance) {
               currLast = validNeighbor;
            }
            q.enqueue(validNeighbor);   
         }
      }
   }

   pair<int, int> p = currLast;
   Stack<pair<int, int>> S;
   while (p != start) {
      S.push(p);
      pair<int, int> parent = hintVector[p.second][p.first];
      p = parent;
   } 

   S.push(start);

   while (!S.isEmpty()) {
      pathPts.push_back(S.pop());
   }
   
}

PNG decoder::renderSolution(){
/* YOUR CODE HERE */
   PNG copyMaze = mapImg;

   for (int i = 0; i< pathPts.size(); i++) {
      RGBAPixel * currPixel = copyMaze.getPixel(pathPts[i].first, pathPts[i].second);
      currPixel->r = 255;
      currPixel->g = 0;
      currPixel->b = 0;
   }
   return copyMaze;
}

PNG decoder::renderMaze(){

/* YOUR CODE HERE */
   PNG copyMap = mapImg;
   int startX = start.first;
   int startY = start.second;
   int width = mapImg.width();
   int height = mapImg.height();

   vector<vector<bool>> visited(mapImg.height(), vector<bool>(mapImg.width(), false));
   vector<vector<int>> distances(mapImg.height(), vector<int>(mapImg.width(), 0));

   Queue<pair<int, int>> locations;

   visited[startY][startX] = true;
   distances[startY][startX] = 0;
   setGrey(copyMap, start);

   locations.enqueue(start);

   while (!locations.isEmpty()) {

      pair<int, int> currLocation = locations.peek();
      int curdist = distances[currLocation.second][currLocation.first];
      locations.dequeue();

      vector<pair<int, int>> allNeighbours = neighbors(currLocation);

      for (int i = 0; i<4; i++) {
         if (good(visited, distances, currLocation, allNeighbours[i])) {
            pair<int, int> validNeighbor = allNeighbours[i];
            visited[validNeighbor.second][validNeighbor.first] = true;
            distances[validNeighbor.second][validNeighbor.first] = curdist + 1;
            setGrey(copyMap, validNeighbor);
            locations.enqueue(validNeighbor);
         }
      }
   }

       // bottom right corner
   for (int x = startX; x<startX + 4; x++) {
      for (int y = startY; y< startY + 4; y++) {
         if ((x<width && y<height) && (x>=0 && y>=0)) {
               RGBAPixel * currPixel = copyMap.getPixel(x, y);
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
                RGBAPixel * currPixel = copyMap.getPixel(x, y);
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
                RGBAPixel * currPixel = copyMap.getPixel(x, y);
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
                RGBAPixel * currPixel = copyMap.getPixel(x, y);
                currPixel->r = 255;
                currPixel->g = 0;
                currPixel->b = 0;
            } else {
                break;
            }
        }
    }
   return copyMap;
}

void decoder::setGrey(PNG & im, pair<int,int> loc){

/* YOUR CODE HERE */
   int column = loc.first;
   int row = loc.second;
   RGBAPixel * currPixel = im.getPixel(column, row);

   currPixel->r = 2*(currPixel->r/4);
   currPixel->g = 2*(currPixel->g/4);
   currPixel->b = 2*(currPixel->b/4);
}

pair<int,int> decoder::findSpot(){

/* YOUR CODE HERE */
   return pathPts[pathPts.size() - 1];
}

int decoder::pathLength(){

/* YOUR CODE HERE */
   return pathPts.size();
}

bool decoder::good(vector<vector<bool>> & v, vector<vector<int>> & d, pair<int,int> curr, pair<int,int> next){

/* YOUR CODE HERE */
   int nextX = next.first;
   int nextY = next.second;
   int width = mapImg.width();
   int height = mapImg.height();

   if ((nextX < width && nextY < height) && (nextX >=0 && nextY >= 0)) {
      if (!v[nextY][nextX]) {
         int val = d[curr.second][curr.first];
         RGBAPixel * nextPixel = mapImg.getPixel(nextX, nextY);
         if (compare(*nextPixel, val)) {
            return true;
         }
      }
   }
   return false;
}

vector<pair<int,int>> decoder::neighbors(pair<int,int> curr) {

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

bool decoder::compare(RGBAPixel p, int d){

/* YOUR CODE HERE */
   int mazeVal = (p.r%4)*16 + (p.g%4)*4 + (p.b%4);

   return mazeVal == ((d+1)%64);
}
