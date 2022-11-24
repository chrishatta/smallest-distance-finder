#include <iostream>
#include <iomanip>
#include <cmath>

double closestPair(std::string filename);

//basic driver to test closestPair.cpp
int main(){
  std::cout << "Name of file you want to use: ";
  std::string filename;
  std::cin >> filename;
  std::cout << "number of decimal places: ";
  int places;
  std::cin >> places;
  double dist = closestPair(filename);
  std::cout << std::setprecision(places) << "Smallest distance is: " << dist;
}