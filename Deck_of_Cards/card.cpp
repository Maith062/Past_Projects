#include "DeckofCards.h"
#include "Card.h"
#include <bits/stdc++.h>
using namespace std;

//string array for faces
 string Card::faces[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};

//string array for the suits
 string Card::suits[4] = {"Clubs", "Spades", "Hearts", "Diamond"};

//default constructor
Card::Card(){
  this->suit = 0;
  this->face = 0;
}

//overloading constructor
Card::Card(int face, int suit){
  this->suit = suit;
  this->face = face;
}

//copy constructor
Card::Card(const Card &other){ 
  this->suit = other.suit;
  this->face = other.face;
}

//assignment overloader
Card& Card::operator = (const Card &other){ //HAVEN'T DECLARED IT IN THE CLASS
  if (this != &other){ //if they don't share the same address, the function will proceed
    suit = other.suit;
    face = other.face;
  }
  return *this;
}

//output
ostream &operator<<(ostream &output, Card const &card){ //could make the array of cards a const
    output << Card::faces[card.face] + " of " + Card::suits[card.suit];
    return output;
}

//returns the "face" attribute of an object
int Card::getFace(){
  return face;
}

//returns the "suit" of an object
int Card::getSuit(){
  return suit;
}
