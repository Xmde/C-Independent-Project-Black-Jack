#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <cstdlib>

using namespace std;

//Function to convert a String into all Uppercase
string toUpperCase(string str){
    string output;
    for(int i = 0; i < str.length(); i++){
        output += toupper(str.at(i));
    }
    return output;
}

//Function to Convert the card number into the cards face
string toCards(int card){
    switch(card) {
        case 1:
            return "A";
        case 2:
            return "2";
        case 3:
            return "3";
        case 4:
            return "4";
        case 5:
            return "5";
        case 6:
            return "6";
        case 7:
            return "7";
        case 8:
            return "8";
        case 9:
            return "9";
        case 10:
            return "10";
        case 11:
            return "J";
        case 12:
            return "Q";
        case 13:
            return "K";
    }
}

//funtion to see if a player has busted.
bool checkBust(vector<int> hand){
    int total = 0;
    for(int i = 0; i < hand.size(); i++){
        total += hand[i];
    }
    if(total > 21){
        return true;
    }
    return false;
}

//function that returns the total value of the players hand.
int totalCards(vector<int> hand){
    int total = 0;
    for(int i = 0; i < hand.size(); i++){
        total += hand[i];
    }
    return total;
}

//Function to see if the dealer wins. It takes in two players hands. A Player and a dealer.
bool dealerWins(vector<int> playerHand, vector<int> dealerHand){
    int playerTotal = 0;
    int dealerTotal = 0;
    for(int i = 0; i < playerHand.size(); i++){
        playerTotal += playerHand[i];
    }
    for(int i = 0; i < dealerHand.size(); i++){
        dealerTotal += dealerHand[i];
    }
    return dealerTotal >= playerTotal;
}

//Function to see if the dealer should hit to stay.
bool dealerHits(vector<int> dealerHand){
    int total = 0;
    for(int i = 0; i < dealerHand.size(); i++){
        total += dealerHand[i];
    }
    if(total < 17){
        return true;
    }
    return false;
}

int main() {
    string usr;
    int numOfPlayers;
    //All the players including the dealer are stored in a 2d vector.
    vector<vector<int>> playersHands;

    //Starting script asking If you  want to play a game and exiting if you say No and continuing if you say Yes.
    start:
    cout << "Do you want to play a Game(Y/N)? ";
    cin >> usr;
    if(toUpperCase(usr) == "N"){
        exit(0);
    } else if (toUpperCase(usr) == "Y"){
        goto game;
    } else {
        cout << "Please enter either Y for Yes or N for No.";
        goto start;
    }

    //The main area of the game logic.

    game:

    cout << "Welcome, today we will be playing Black Jack. How many people want to go against the dealer? ";
    cin >> usr;

    //Converting the Users String into an Int and making sure that it is a valid number and not a char.
    try{
        numOfPlayers = abs(stoi(usr));
    }
    catch(exception e){
        cout << "Please enter a valid number";
        goto game;
    }

    //Gives Each player and the Dealer a set of Cards.
    for(int i = 0; i <= numOfPlayers; i++){
        playersHands.push_back({rand() % 13 + 1, rand() % 13 + 1});
        //playersHands[i][0] = rand() % 13 + 1;
        //playersHands[i][1] = rand() % 13 + 1;
    }

    int newCard;
    //Prints one of the dealers cards.
    cout << "\nThe dealers First Card is " + toCards(playersHands[0][0]);

    //This is the main loop for the players to see if they want to hit or skip.
    for(int i = 1; i <= numOfPlayers; i++){
        cout << "\n\nPlayer " + to_string(i) + ":Your cards are " + toCards(playersHands[i][0]) + " and " + toCards(playersHands[i][1]) + ". TOTAL: " + to_string(totalCards(playersHands[i]));
        hitskip:
        cout << "\nDo you want to Hit or Skip (H/S)";
        cin >> usr;
        if(toUpperCase(usr) == "H"){
            //Generates a New card if the player decides to hit
            newCard = rand()%13+1;
            //Adds that card to that players hand inside of the 2d vector.
            playersHands[i].push_back(newCard);
            //Displays info to the player about the card recived and their new total.
            cout << "You got a " + toCards(newCard) + ". TOTAL: " + to_string(totalCards(playersHands[i]));
            //checks to see if the player has busted and if they havn't goes back to up see if the player wants to hit or skip.
            if(!checkBust(playersHands[i])){
                goto hitskip;
            }
            //If the player busts it sets their first card to -500 making further comparisions show the dealer as a winner.
            playersHands[i][0] = -500;
            cout << "\nYou BUST. Better luck next time.";
        }else if (toUpperCase(usr) == "S"){
        }else{
            //Fail safe to make sure that player either hits or skips.
            cout << "\nPlease enter either a H or S";
            goto hitskip;
        }
    }

   //Dealers Turn and all the main Logic for him.
    cout << "\n\nDealers Turn";
    cout << "\nDealers Cards: " + toCards(playersHands[0][0]) + " and " + toCards(playersHands[0][1]) + ". TOTAL: " + to_string(totalCards(playersHands[0]));
    //Loop itterating as long as the dealer doesn't bust.
    while (!checkBust(playersHands[0])){
        //If the dealer should hit it gives him a new card.
        if(dealerHits(playersHands[0])){
            newCard = rand()%13+1;
            playersHands[0].push_back(newCard);
            cout << "\nDealer Hits and Recives a " + toCards(newCard) + ". TOTAL: " + to_string(totalCards(playersHands[0]));
        }else{
            //If the dealer shouldn't hit it breaks out of the loop.
            goto dealerNoBust;
        }
    }
    //Print statement for when the dealer busts. Also sets the dealers first card to -100 to show that the dealer has lost. This value is larger than the -500 for the player so if both parties bust the dealer still wins.
    cout << "\nDealer Busts!";
    playersHands[0][0] = -100;

    dealerNoBust:

    cout << "\n";

    //Prints out all the final standings on who has won and who has lost.
    for(int i = 1; i <= numOfPlayers; i++){
        if(dealerWins(playersHands[i], playersHands[0])){
            cout << "\nPlayer " + to_string(i) + ": Better luck Next time Looks like the dealer wins.";
        }else{
            cout << "\nPlayer " + to_string(i) + ": GOOD JOB YOU WIN!!!";
        }
    }

    cout << "\nEnter anything to Exit";
    cin >> usr;
    exit(0);

}
