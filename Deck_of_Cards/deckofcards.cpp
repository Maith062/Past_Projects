#include "DeckofCards.h"
#include "Card.h"
//#include "card.cpp"

//writing the code


//default constructor intitlaizing the array


DeckofCards::DeckofCards(){

  deck = new Card[52];
  
  for (int i = 0; i < 4; i ++){ //suits
    for (int j = 0; j < 13; j++){ //faces
      deck[(j) * 4 + i]  =  Card(j,i); 
    }  
  }
  
}

void DeckofCards::shuffle(){
  for (int i = 0; i < SIZE_OF_DECK; i++){
    //int ran = (rand() % 52) + 1; //goes from 1 to 52 to producce a random variable
    int ran = (rand() % 51);//should go from 0 to 51 to produce a random variable
   // cout << "Random number: " << endl;
 
    if(ran < SIZE_OF_DECK) {
      Card temp = deck[i];
      deck[i] = deck[ran];
      deck[ran] = temp;
    }
    else {
      cout << "INDEX OUT OF RANGE << endl;" ;//
    }
   //notes: to make a copy of a card --> Card whaterver =  Card("Whatver card you want to copy")
  }//end for
}

//dealCard() function that returns the next card object
Card DeckofCards::dealCard(){ //don't have to pass in "currentCard" as its already a memeber of the class

  if (!moreCards()){ //consider making currentCard a pointer ("*") os that the value can be changed from anywhere
   // cout << "The current card is: " << currentCard << endl;
    cout << "There are no more cards to deal Resetting deck! " << endl <<endl;
    
    currentCard = 0;
    currentCard++;
    shuffle();
    //cout << "The current card is: " << (currentCard - 1) << endl;
    return deck[currentCard - 1];
    //would I have to reset the deck
    
    
  }else{
    
    currentCard++;
    return deck[currentCard - 1];
    
  }

 // currentCard++;
  //if (!moreCards())
}

//moreCards() that shows if the currentCard => 52
bool DeckofCards::moreCards(){
 // return currentCard != SIZE_OF_DECK; //if the current card being dealt is the same as the number of cards available, then return false 
  return (currentCard < 50); //when we reach 50 cards, there will be 2 remaining. Once the currentCard counter reaches 50, the two remaining cards will be put back in the pile, and shuffled again
}

//destroying the array of object "deck" when the main terminates
DeckofCards::~DeckofCards(){
  delete [] deck;
}

