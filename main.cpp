#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <cstdlib>

using namespace std;

string toUpperCase(string str){
    string output;
    for(int i = 0; i < str.length(); i++){
        output += toupper(str.at(i));
    }
    return output;
}

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

int totalCards(vector<int> hand){
    int total = 0;
    for(int i = 0; i < hand.size(); i++){
        total += hand[i];
    }
    return total;
}

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

    cout << "\nThe dealers First Card is " + toCards(playersHands[0][0]);

    for(int i = 1; i <= numOfPlayers; i++){
        cout << "\n\nPlayer " + to_string(i) + ":Your cards are " + toCards(playersHands[i][0]) + " and " + toCards(playersHands[i][1]) + ". TOTAL: " + to_string(totalCards(playersHands[i]));
        hitskip:
        cout << "\nDo you want to Hit or Skip (H/S)";
        cin >> usr;
        if(toUpperCase(usr) == "H"){
            newCard = rand()%13+1;
            playersHands[i].push_back(newCard);
            cout << "You got a " + toCards(newCard) + ". TOTAL: " + to_string(totalCards(playersHands[i]));
            if(!checkBust(playersHands[i])){
                goto hitskip;
            }
            playersHands[i][0] = -100;
            cout << "\nYou BUST. Better luck next time.";
        }else if (toUpperCase(usr) == "S"){
        }else{
            cout << "\nPlease enter either a H or S";
            goto hitskip;
        }
    }

    cout << "\n\nDealers Turn";
    cout << "\nDealers Cards: " + toCards(playersHands[0][0]) + " and " + toCards(playersHands[0][1]) + ". TOTAL: " + to_string(totalCards(playersHands[0]));
    while (!checkBust(playersHands[0])){
        if(dealerHits(playersHands[0])){
            newCard = rand()%13+1;
            playersHands[0].push_back(newCard);
            cout << "\nDealer Hits and Recives a " + toCards(newCard) + ". TOTAL: " + to_string(totalCards(playersHands[0]));
        }else{
            goto dealerNoBust;
        }
    }
    cout << "\nDealer Busts!";
    playersHands[0][0] = -50;

    dealerNoBust:

    cout << "\n";

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