#include <bits/stdc++.h>
#include <string>
#include <iostream>

using namespace std;

#ifndef CARD_H //opening
#define CARD_H

class Card{

private: //instance variables are typically always private
  int face, suit;
 
public:
  Card();
  ~Card() {}
  Card(int face, int suit);
  Card(const Card &other);
  Card& operator = (const Card &other);
  friend ostream& operator<< (ostream &output, Card const &card);
  int getFace();
  int getSuit();

  //variables
  static string faces[13]; // where 0 represents ace and 12 represents king
  static string suits[4]; // 0 = spades, 1 = clubs, 2 = hearts, 3 = diamonds

};



#endif /* FRACTION_H_*/ //closing
