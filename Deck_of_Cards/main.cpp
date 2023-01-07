#include <iostream>
//#include "Card.h" --> don't have to call the class, as we already do from the #include "DeckofCards.h"
#include "DeckofCards.h"

//Global variables
int ranks = 0; //essentially helps decide which poker hand is better
int grIndex = 0; //the variables determines whihc
//int hand2Rank = 0;
int counter = 0; //this is to determine if the value is a Pair or a Two Pair

//declaring the functions for comparing values
void organise (int *suit, int *face, Card *hand1);
string handLevel (Card *hand);
bool ifFound (int handRank[], int want, int index);
bool isStraight (int handFace[]);
string determineWinner(int hand1Rank, int hand2Rank, int hand1Level, int hand2Level);
int main() {

  
  //INITIAL EXPERIMENTATION -------- 

 
  //creating a deck of card
  DeckofCards deck1;

  deck1.shuffle(); //shuffling the deck of cards once
  

  //PART 1 --> CREATING A LIST OF 5 CARS AND DETERMINING WHAT "HAND" IT WILL BE
  // first creating a hand array of class DeckofCards 
  //then calls a function to compare the values and determine what hand it has (also assigns a global variable that will make it easier to compare which hand is better)

  //creating the hands of the two player
  Card *hand1 = new Card[5]; // the hand of player 1
  Card *hand2 = new Card[5]; //the hand of player 2

  char again = 'y'; //will be part of a do-while loop to see if they want to draw another hand
  
  do{ //start of the do-while loop
    
    for (int i = 0; i < 5; i++){ //my plan is essentially copy over the first 5 cards of the deck
      hand1[i] = deck1.dealCard(); // assigning a card to the hand array
      hand2[i] = deck1.dealCard();
    
    }

    cout << "Here are the cards for Player 1: " << endl << endl;
  //printing out the values in hand1
    for (int i = 0; i < 5; i++){
      
      cout << "Card " << (i + 1) << " - " << hand1[i] << endl;
    }
    cout <<"You got a: ";


    //determining waht the value of their hand is
    ranks = 0;
    grIndex = 0;
    cout << handLevel(hand1);
    int hand1Rank = ranks;
    int hand1Level = grIndex;
    
    cout << endl <<endl << "Here are the cards for Player 2: " << endl << endl;
    //printing out the values in hand2
    for (int i = 0; i < 5; i++){
      //cout << "Card " << (i + 1) << " - " << Card::faces[hand2[i].getFace()] << " OF " <<Card::suits[hand2[i].getSuit()] << endl;
      cout << "Card " << (i + 1) << " - " << hand2[i] << endl;
    }

    cout <<"You got a: ";
    
    ranks = 0;    
    grIndex = 0;
    cout << handLevel(hand2);
    int hand2Rank = ranks;
    int hand2Level = grIndex;
    
    //comparing the values of the cards and seeing what "HAND" they got
    //determines which hand is higher
    cout << endl << endl << "And... Ladies and Gentlemen..." << endl ;
    cout <<endl<< determineWinner(hand1Rank, hand2Rank, hand1Level, hand2Level) << endl;

    cout << endl << "Do you want to draw another hand? Enter 'y' to continue, and any other key to stop" << endl;
    cin >> again;

     std::cout << "\x1b[H\x1b[J" << std::flush; //to start the feel of a new game/draw, it refresehes the compiler and shows a black screen

    if (again != 'y'){

      //when they click another key, it ends the program and outputs this final mesaage
      cout << "Thank you! Bye!" << endl;
    }
  
  }while (again == 'y');

  //deleting the ymaic values
  delete [] hand1;
  delete [] hand2;

}

//the organise function, organises the hand of the player, so that in later methods where we determine what type of hand it is, it becomes easier
void organise (int *suit, int *face, Card *hand1){
 
  for (int i = 0; i < 5; i++){
    suit[i] = hand1[i].getSuit();
    face[i] = hand1[i].getFace();
  }

  //given that we will be sorting on 5 cards, we'll use the selection sort
    int pos_max, temp, temp1;

    for (int i=0; i < 5; i++) { 
  
   //i is the index of end of unsorted portion, and the value k, limits the number of sorts possible
      pos_max = 4; //assume last element is largest
    
    for (int j=3; j >= i; j--) {
      if (face[j] < face[pos_max]) //decides the order in which the sequence is arranged, depending on ">" or "<"
      pos_max= j; //if larger found, set new largest
    }

  //swap element at i with largest element found in unsorted portion

    temp = face[i];
    temp1 = suit[i];
      
    face[i] = face[pos_max]; //when I arrange the face values of the cards, I also arrange the suit values in the following line
    suit[i] = suit[pos_max];
      
    face[pos_max] = temp;
    suit[pos_max] = temp1;
  }
  
  
}

//after having the cards rearranged, this function determines the ranking of the cards
//after excepting a hand (Card * hand), it first determines if its a flush (in which case all of the suits will be the same)
//after, it determines if its a straight
//if it doesn't fall into the straight of flush categories, then it will look at how many cards of the same types there are
string handLevel (Card *hand){

  string ranking = "";
  //first organising the hand
  int *suit = new int[5];
  int *face = new int[5];
  organise(suit, face, hand); // call the organise function, to arrange the cards from least to greatest


 
  if (suit[0] == suit[1] && suit[1] == suit[2] && suit[2] == suit[3] && suit[3] == suit[4]){ // might be skuffed
    if (isStraight(face)){
      if (face[0] == 8){ // if the lowest card is a 10 and meets all of the prior conditions
        ranking = "Royal Flush!";
        ranks = 9;
        grIndex = suit[0]; //this variable is for the 2 player purpose, where it detremines who has the higher suit when they both have royal flush
        return ranking;
      } else {
        ranking = "Straight Flush!";
        ranks = 8;
        grIndex = face[4]; // returns the highest card, which we will then compare between the two hands, if both hands are straight flush
        return ranking;
      }
    } else {
      ranking = "Flush!";
      ranks = 5;
      grIndex = face[4];
      return ranking;
    }
  } else if (isStraight(face)){ // it calls the straight function, to determine if this hand is a straight
    ranking = "Straight!";
    ranks = 4;
    grIndex = face[4];
    return ranking;
  }else{
    
    //now I'll run a for-loop to see how many times a card repeats
    int handRank[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //a counter of how many times a face value such a "king" or "ace" repeats
    int index = 0;
    int max = 0; //detremines which of the counter array has the most value (to diffrentiate when both of the hands are of the same rank - ex: pair and pair). Afterwards, we assign the index of the card to 'cardhigh', and after we compare it, we can determine which player wins
    int cardhigh = 0;
    for (int i = 0; i < 5; i++){
      index = face[i]; 
      handRank[index] ++; //increases the the value of the index (the handRank[] array is a counter)
      if (max <= handRank[index]){
        max = handRank[index];
        cardhigh = index;
      }
    }
    grIndex = cardhigh;

    //deciding if its a four of a kind, full house, three of kind, etc.
    if (ifFound(handRank, 4, 0)){
      ranking = "Four of a Kind!";
      ranks = 7;
      return ranking;
    }else if (ifFound(handRank, 3, 0)){ //full house
      if (ifFound(handRank, 2, 0)){
        ranking = "Full House!";
        ranks = 6;
        return ranking;
      }else{
        ranking = "3 of a Kind!"; //a 3 of a kind
        ranks = 3;
        return ranking;
      }
    } else if (ifFound(handRank, 2, 0)){ 
      if (counter == 3){
        ranking = "Two Pair!"; // a two pair
        ranks = 2;
        return ranking;
      }else{
        ranking = "Pair!";  // pair
        ranks = 1;
        return ranking;
      }
    } else{
        ranking = "High Card!"; //a high card
        return ranking; 
    }
  
  }  

  
  
  cout << endl;
  
}

//the purpose of this function, is to determine what rank of card it is
bool ifFound (int handRank[], int want, int index){

  
  for ( ; index < 13; index++){
    
    if (handRank[index] == want && want == 2){  // if we are looking for a 2, its possible to have 2 2's (having 2 pairs)
        
        if (ifFound (handRank, want, index + 1)){ //to diffrentiate between have two pair and just a singular pair, we search the rest of the counter array, handRank, to see if there is another pair
          
          counter = 3; //if there is another pair, we set the global variable to 3
          return true;
        }else{
          counter = 2; //a random number to see if the pair is a Two pair or a Pair
        }
        
    }
    
    
    if (handRank[index] == want){ //essentially when not dealing with two pair or pair, we use thise if statemtns
      
      return true;
    }else{
      //count++;
    }
  }

    return false;
 

}

//a function that indetifies if it the hand is a straight
//the way that this method functions, is that since if already arranged in order from leaast to greatest, we just determine if the next value in the sequence is 1 higher than the previous
bool isStraight (int handFace[]){
  int count = 0;
  for (int i = 0; i < 5; i++){
   
    if (handFace[i] == (handFace[i + 1] - 1)){
      count++;
    }
  }

  if (count == 4){
    return true;
  }else{
    return false;
  }
}


//after determining the rank of each player's cards, it compares the values
string determineWinner(int hand1Rank, int hand2Rank, int hand1Level, int hand2Level){

  string result = "";

  //if one hand is greater than the other, than we return which player won
  //else, it looks at the highest ranked card. What this means, is that if both players have a pair, it looks at the value of the cards, and compares them
  if (hand1Rank > hand2Rank){
    result = "Player 1 Wins!";
    return result;
  }else if (hand1Rank < hand2Rank){
    result = "Player 2 Wins!";
    return result;
  }else{ //essentialy when they both have, for example; a pair
   
    if (hand1Level > hand2Level){
      result = "Player 1 Wins!";
      return result;
    }else if (hand1Level < hand2Level){
      result = "Player 2 Wins!";
      return result;
    }else{
      result = "It's an unexpected tie"; // if both of the ranks and levels of the cards are the same, I call it as an expected tie
      return result;
    }
    
  }
}
