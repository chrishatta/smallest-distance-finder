/*
 * Name: Chris Hattan  
 *
 * Purpose of Program: find the two closest points in a unit square (1x1) and the distance between them.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct point
{
    double x;
    double y;
};


double compare(point p1, point p2){//helper function that compares 2 points useing the formula
  return (sqrt(pow(p1.x-p2.x,2) + pow(p1.y-p2.y,2)));
}

double closestPair(string filename){
  ifstream myFile (filename);
  int numPoint;
  myFile >> numPoint;
  double x, y, min = 10; // min intialized to ensure it changes
  int b = sqrt(numPoint) + 1;//uses sqrt becasue it scales reasonably well. if the number is to small too many points will be checked for distance if too big there may not be any points that are in adjacent squares
  double interval = sqrt(numPoint);
  point pos, final1, final2;

  vector<vector<vector<point>>> myArray;
  //resizes vectors
  myArray.resize(b);
  for (int i = 0; i < myArray.size(); ++i){
    myArray[i].resize(b);
  }
  //reads in vectors
  for (int i = 0; i < numPoint; ++i){
    myFile >> x >> y;
    point pos;
    pos.x = x;
    pos.y = y;
    //uses the interval value to assign the points to the correct place in the 3D vector
    myArray[trunc(pos.x * interval)][trunc(pos.y * interval)].push_back(pos);
    
  }

  for (int i = 0; i < b; ++i){
    for (int j = 0; j < b; ++j){
      for (int k = 0; k < myArray[i][j].size();++k){
        point pos1 = myArray[i][j][k];

        for(int l = 1; l + k < myArray[i][j].size(); ++l){//checks points in same vector
          if (compare(pos1, myArray[i][j][l+k]) < min){
            min = compare(pos1, myArray[i][j][k+l]);
            final1 = pos1;
            final2 = myArray[i][j][k+l];
          }
        }
          
        if (j + 1 < b && i + 1 < b){ //checks up right
          for (int l = 0; l < myArray[i+1][j+1].size();++l){
            if (compare(pos1,myArray[i+1][j+1][l]) < min){
              min = compare(pos1,myArray[i+1][j+1][l]);
              final1 = pos1;
              final2 = myArray[i+1][j+1][l];
            }
          }
        }
        
        if (i + 1 < b){ //checks right
          for (int l = 0; l < myArray[i+1][j].size();++l){
            if (compare(pos1,myArray[i+1][j][l]) < min){
              min = compare(pos1,myArray[i+1][j][l]);
              final1 = pos1;
              final2 = myArray[i+1][j][l];
            }
          }
        }

        if (j - 1 >= 0 && i + 1 < b){ //checks down right
          for (int l = 0; l < myArray[i+1][j-1].size();++l){
            if (compare(pos1,myArray[i+1][j-1][l]) < min){
              min = compare(pos1,myArray[i+1][j-1][l]);
              final1 = pos1;
              final2 = myArray[i+1][j-1][l];
            }
          }
        }

        if (j - 1 >= 0){ //checks down
          for (int l = 0; l < myArray[i][j-1].size();++l){
            if (compare(pos1,myArray[i][j-1][l]) < min){
              min = compare(pos1,myArray[i][j-1][l]);
              final1 = pos1;
              final2 = myArray[i][j-1][l];
            }
          }
        }
      }
    }
  }
  cout << setprecision(20) << "Point one: " << final1.x <<  "," << final1.y << endl;
  cout << "Point two: " << final2.x << "," << final2.y << endl;
  return min;
}