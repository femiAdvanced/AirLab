//  main.cpp
//  LLTemplate
//
//  Created by James Shockey on 12/6/16.
//  Copyright © 2016 James Shockey. All rights reserved.
//

/*

        Linked List lab.
        - Build a library for singly linked list.
        - Replace the airport array in main with a Linked List.
  - sort the array.

 */

#include "slist.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

using namespace std;

class Airport {
public:
  char code[5];
  double longi;
  double lati;
  Airport *nextNode;
};

void simpleSortTotal(Airport *a);
void swapPorts(Airport *a, Airport *b);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

int main() {
  ifstream infile;
  int c = 0;
  char cNum[10];
  Airport *head = new Airport();
  Airport *prev = head;
  int airportCount;

  infile.open("USAirportCodes.csv", ifstream::in);
  if (infile.is_open()) {
    while (infile.good()) {
      Airport *version = new Airport();
      infile.getline(version->code, 256, ',');
      infile.getline(cNum, 256, ',');
      version->lati = atof(cNum);
      infile.getline(cNum, 256, '\n');
      version->longi = atof(cNum);
      c++;
      prev->nextNode = version;
      prev = version;
    }
    airportCount = c - 1;
    infile.close();

  } else {
    cout << "Error opening file";
  }
  Airport *current = head->nextNode;
  double largest = 0;
  Airport *far;
  while (current->nextNode != NULL) {
    double d = distanceEarth(30.1944, 97.6700, current->nextNode->lati,
                             current->nextNode->longi);
    if (d > largest) {
      largest = d;
      far = current->nextNode;
    }
    current = current->nextNode;
  }
<<<<<<< HEAD
  cout << "Farthest: " << far->code << endl;
=======
  cout << "Farthest: " << far->code  << " " <<far->lati << " " << far->longi << " dist: " << largest << endl;
>>>>>>> fc3eab2 (Changed so Replit Can Run)
  simpleSortTotal(head);
  cout << "Within 100 miles." << endl;

  Airport *output = head;
  double dista;
  int Amount = 0;

  while (output->nextNode != NULL) {
    dista = distanceEarth(30.1944, 97.6700, output->nextNode->lati,
                          output->nextNode->longi);
    if (dista < 161) {
      cout << output->nextNode->code << " " << dista << endl;
      Amount++;
    }
    output = output->nextNode;
  }
  cout << "total amount: " << Amount << endl;
}

// This function converts decimal degrees to radians
double deg2rad(double deg) { return (deg * pi / 180); }

//  This function converts radians to decimal degrees
double rad2deg(double rad) { return (rad * 180 / pi); }

/*
  Returns the distance between two points on the Earth.
  Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
  @param lat1d Latitude of the first point in degrees
  @param lon1d Longitude of the first point in degrees
  @param lat2d Latitude of the second point in degrees
  @param lon2d Longitude of the second point in degrees
  @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r) / 2);
  v = sin((lon2r - lon1r) / 2);
  return 2.0 * earthRadiusKm *
         asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

void swapPorts(Airport *a, Airport *b) {
  swap(a->code, b->code);
  swap(a->lati, b->lati);
  swap(a->longi, b->longi);
}

/*
        Provide sort routine on the linked list
*/
void simpleSortTotal(Airport *Airs) {
  Airport *c = Airs;
  while (c->nextNode != NULL) {
    Airport *X = c;
    Airport *after = c->nextNode;
    while (after->nextNode != NULL) {
      double distNext = distanceEarth(30.1944, 97.6700, after->nextNode->lati,
                                      after->nextNode->longi);
      double distX = distanceEarth(30.1944, 97.6700, X->lati, X->longi);
      if (distNext > distX) {
        // swap them
        swapPorts(X, after);
      }
      after = after->nextNode;
    }
    c = c->nextNode;
  }
}
