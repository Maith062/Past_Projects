#include <bits/stdc++.h>
#include <string>
#include "Card.h"

using namespace std;

#ifndef DECKOFCARDS_H //opening
#define DECKOFCARDS_H

/*lessons
When there are pointers int he class we use the overload operator
When we use the "new" keyword, we must use the "delete" keyword
  -->int * key = new int[5];
  --> delete [key]; 
*/

class DeckofCards{

private:

  Card *deck; // = new Card[52];// = new DeckofCards[52]; //I suppose that we have to intialize it in the constructor

  int currentCard = 0;

  int ran = 0;

  const int SIZE_OF_DECK = 52;

public:

  DeckofCards();
  ~DeckofCards(); //--> destructor to delete each object after use

  void shuffle(); //shuffles the deck

  Card dealCard(); //deals the next card in the deck

  bool moreCards(); //determines if there are any cards left in the deck


};

#endif
