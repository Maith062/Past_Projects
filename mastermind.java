*********************
//Mayoor Aithal
//May 8, 2021
**********************/

//This program runs a simulation of the game, "Mastermind"
//The user must enter 4 valid characters and crack the code

import java.util.Scanner; // importing scanner object
import java.util.ArrayList;



public class Main {

  //defining colours to add to output
  public static final String ANSI_RESET = "\u001B[0m";
  public static final String ANSI_RED = "\u001B[31;1m";
  public static final String ANSI_GREEN = "\u001B[32;1m";
  public static final String ANSI_YELLOW = "\u001B[93;1m"; // changing the brightness of the yellow as it orginally looked "orange"
  public static final String ANSI_BLUE = "\u001B[34;1m";
  public static final String ANSI_PURPLE = "\u001B[35;1m";
  public static final String ANSI_CYAN = "\u001B[36;1m";
  public static final String ANSI_WHITE = "\u001B[37;1m";
  public static final String ANSI_MILK = "\033[3;37;1m";
  public static final String ANSI_ORANGE = "\033[0;33m";


//the main function in which the prgram loops
  public static void main(String[] args) {

    Scanner s = new Scanner (System.in); // creating a scanner objects that inputs the user's entries
    String repeat = ""; //this variable will deal with the play again option  

    int minRounds = 11; // this variable is for a method that finds the lowest score for a given amount of games played


  //this do-while loop will loop the primary methods responsible for the game, until the user enters "N" or "NO"

    do{

   

    //Setting up the instructions and messages that the user will see

    System.out.println("\n");
    System.out.println("WELCOME TO MASTERMIND!" + "\n");
    System.out.println("Get ready to crack the code!" + "\n");
    System.out.println("Instructions:" + "\n");
    System.out.println("1) Choose a 4-character code consisting of either " + ANSI_BLUE + "B - Blue, " + ANSI_RESET + ANSI_YELLOW + "Y - Yellow, " + ANSI_RESET + ANSI_GREEN + "G - Green, " + ANSI_RESET + ANSI_RED + "R - RED, " + ANSI_RESET + ANSI_ORANGE + "O - Orange, " + ANSI_RESET + ANSI_CYAN + "C - Cyan, " + ANSI_RESET + ANSI_PURPLE + "V - Violet, " + ANSI_RESET + ANSI_WHITE + "W - White " + ANSI_RESET + "\n");
    System.out.println("2) You have 10 rounds to try and guess the code." + "\n");
    System.out.println("3) Each " + ANSI_RED + "'x'" + ANSI_RESET + " means that one character is in the right position, while an " + "'o'" + " means the character is part of the code but not in the right position. \n");
    System.out.println("4) No characters are repeated in the code that you need to crack. Good Luck!");    
   

    //array that stores values of colours
    /*B - blue, Y - yellow, G - green, R - red, O - orange, C - Cyan, V - violet, W - white*/

    char [] colourList = {'B', 'Y', 'G', 'R', 'O', 'C', 'V', 'W'};
   

    //I think this could go in a seperate method
    ArrayList<String> entries = new ArrayList<String>(); // keeps track of entries and outputs

   
    String code = createCode(colourList); // the code that they are trying to replicate

    System.out.println(code);

   
    //looping the follwing two lines 10 times in order unless they reach a win, or number of rounds exceed 10
    boolean valid = false;
    int rounds = 1; // the number of rounds of Mastermind

 
      while (valid == false && rounds < 11 ){

        System.out.println("\n--------------------");
        System.out.println("This is round: "+ rounds);

       String temp = userInput(colourList); //stores what they entries
   
      //calling the outCome method

         
        System.out.println("Table of Results");
        String count = outCome(code, temp, entries);

        //here the if else statement determines whether or not the user wins, else the program continues
        if (count.equals("yes")){
          System.out.println("--------------------\n");
          System.out.println("YOU WIN!\n");
          valid = true;

          //once they've won, if the user would like to play again or exit the game, the option is given
          System.out.print("Would you like to play again? (Y or N) Any other answer aside from the given options will mean 'NO': ");

          repeat = s.nextLine();

          //if the user chooses to exit, the bestScore (lowest number of rounds in which the code was cracked) is printed
          bestScore(rounds, minRounds);
          System.out.println("--------------------\n");
         
         

        }else
          rounds++;
      }

      //this "if" statement is used to determine whether or not the user loses. If the code reaches more than 10 rounds, the program breaks and the user is given the option to play again
      if (rounds > 10){
        System.out.println("--------------------\n");
        System.out.println("You lose... Better luck next time!");
        System.out.println("The correct code was: " + code + "!\n");

        System.out.print("Would you like to play again? (Y or N) Any other answer aside from the given options will mean 'NO': ");
       

          repeat = s.nextLine();
      }
    } while(playAgain(repeat) == true);
       
  }

  //this method will create the code that the user tries to replicate
  public static String createCode (char [] colourList){
   
    String correct = "";

    int [] numOf = {0, 0, 0, 0, 0, 0, 0, 0}; //tracks how many of each colour there is when the code is being calculated and later entered
       
    for (int i = 0; i < 4; i++){

      //generates a random value from 0 to 7, each number corresponding to a different colour index
      int r = (int)(Math.random() * 8 + 0);

      numOf[r]++;  
      //this loop is to make sure that THERE IS ONE ONE OF EACH COLOUR
      if(numOf[r] > 1){
     
        i--;
      }else{
      correct += colourList[r];
         
      }
    }

    return correct;

  }

  //this method gets the entry from the user
  public static String userInput(char[] colourList){

    Scanner input = new Scanner (System.in);
    String stringEntry = "";

    System.out.print("Enter code: " );
    stringEntry = input.nextLine();
    stringEntry = stringEntry.toUpperCase();
    System.out.println("--------------------\n");


    // the following if statement loops until they enter a valid entry    

    if (validEntry(stringEntry, colourList) == false){
       do{

        System.out.println("Please enter a 4 letter string consisting of the options: B - Blue, Y - Yellow, G - Green, R - Red, O - Orange, C - Cyan, V - Violet, W - White");
       
       
        System.out.print("Enter code again: " );
        stringEntry = input.nextLine();
        stringEntry = stringEntry.toUpperCase(); // converting everything to upper case so the program can still run even if they enter lower case
        System.out.println("--------------------\n");

      }while (validEntry(stringEntry, colourList) == false); // passing  what the user enters and the given options (colourList) to the validEntry method to decide if the entry is valid
    }

    //if the entry is valid

    return stringEntry;


  }

  //this method will make sure that the values that the user enters are valid
  public static boolean validEntry(String stringEntry, char[] colourList){

    //creating a boolean variable that will act like a check to see if the program works or not
    boolean valid = false; // temporarily initializing it to false
    int good = 0; //sees how many of the the characters the user inputted are correct

    if (stringEntry.length() == 4){ //the 4 is for the 4 numbers of the code (checks if they entered 4 characters)
      for (int i = 0; i < 4; i++){
        for (int j = 0; j < 8; j++){ // checks if the individual characters one of the options in the colourList arrays
          if (stringEntry.charAt(i) == colourList[j]){
            good++;
          }
        }
      }
    }else
      valid = false;

    if (good == 4){
      valid = true;
    } else
      valid = false;

    return valid;  
   


  }

  //this method checks the valid code of the user, and sees how many were in the correct position and the correct colour
  public static int[] valueChecks(String code, String temp){

    //the variable that measure how many are in the correct position
    int rightPosition = 0;
    //the variable that measures how many correct colours there are
    int rightColour = 0;

    char [] col = {' ', ' ', ' ', ' '}; //in order to make sure that if though there is one place for a character, entering the specified character doesn't get you two xx's

   int wrong = 0;//sees to see if any of the characters repeat. If so, it will turn false, and won't allow the program to add an additional 'o'.

    // looping to see how many are correct
    for (int place = 0; place < 4; place++){

      char c = temp.charAt(place);

      int i = 0;
      col [place] = c;

      if (code.indexOf(c) == -1){
        //breaks??
      } else if (code.charAt(place) == c){
        rightPosition++;
      } else if (code.indexOf(c) >= 0 && code.indexOf(c) <= 3){ // because of this line we are seeing results like xxxo when there is a repeat of characters
        rightColour++;
      }

      //loops to see if there are entered values that are overlapping
      while ((place - i) != 0){
         i++;
        if(col[place]== col[place - i]){
          wrong++;
        }      
      }
     
    }

    //an array that allows the program to return the values (rightPosition and rightColour)

    int [] correct = new int [2];
    correct [0] = rightPosition;
    correct [1] = rightColour - wrong;

    return correct;

  }

  //this method outputs the score and sees how many they got correct
  public static String outCome(String code, String temp, ArrayList<String> entries){

    //calling the valueChecks method
    int [] correct = valueChecks(code, temp);
   
    String result = "";
    String output = ""; //the variable that will be entered into the array

    //looping to add the correct number of x's and o's into the result variable

    for (int rightplace = 0; rightplace < correct[0]; rightplace++){
      result += ANSI_RED + 'x' + ANSI_RESET;
    }

    for (int rightcolour = 0; rightcolour < correct[1]; rightcolour++){
      result += 'o';
    }

    //outputs the final message if they win, else continues to loop
   
    output = temp + " | " + result;
    entries.add(output);

    //showing a table of all the results
    for (int i = 0; i < entries.size(); i++){
      System.out.println(entries.get(i));
    }

    String inPosition = "";
     if (correct[0] == 4 ){
       inPosition += "yes";
     }

   
    return inPosition; // if the user gets all four characters in the code correct (position and colours) it returns yes to the main function which in turn breaks the loop (the game continuing for 10 rounds);
   
  }

  // this method deals with the user choosing to play again
  public static boolean playAgain(String repeat){

    boolean again = false;
    repeat = repeat.toUpperCase();

    //this if-else statement takes in the user's entry (if the win or if the game exceeds ten rounds and stops) and asks them to enter "y" or "n". If "no", the program will return false to the main function and the program will terminate. If they enter "yes", it will return true to the main function and the program will loop/restart
    if (repeat.equals("N") || repeat.equals("NO")){
      again = false;
      System.out.println("\nThank you for playing!");
    }else if (repeat.equals("Y") || repeat.equals("YES") || repeat.equals("YE")){
      again = true;
    }else{
      again = false;
      System.out.println("\nThank you for playing!");
    }

    return again;


  }

  // this method outputs the best score of the user if the continously enter "yes" to wanting to play again. After every round if the user beats their previous score (the number of rounds in which they crack the code), the bestScore method updates that and the game continues until the decide to leave the game
  public static void bestScore(int rounds, int minRounds){
   
      if (minRounds > rounds){
        minRounds = rounds;
      }else{
        minRounds = rounds;
      }

      //I've done 11 - rounds as if they manage to get it in 10 rounds, they're score would be 1, if they manage to get it in 1, they're score will be (11 - 1) = 0
      minRounds = 11 - minRounds;

      System.out.println("\nThe " + ANSI_YELLOW + "BEST" + ANSI_RESET  + " score is: " + minRounds + "\n");
   
  }




}
