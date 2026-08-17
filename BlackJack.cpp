#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <iterator> 
#include <ctime>

using namespace std;

string suit[] = {
    "Hearts", "Spades", "Diamods", "Clubs"
};
//string names[] = { "Ace", "2", "3", "4" ,"5" ,"6" ,"7","8","9","10","Jack","Queen","King" };


class Card {
private:
    int cardNumber;
    string cardShape;
public:
    Card(int num, string shape) {//constructor
        cardNumber = num;
        cardShape = shape;

    }    
    void print() {
        //לא יעיל בכלל מה שהולך פה
        if (cardNumber == 1)
        {cout << "Ace of " << cardShape << endl;}
        else if (cardNumber == 11)
        {cout << "Jack of " << cardShape << endl;}
        else if (cardNumber == 12){cout << "Queen of " << cardShape << endl;}
        else if (cardNumber == 13){cout << "King of " << cardShape << endl;}
        else {cout << cardNumber << " of " << cardShape << endl;}
    }
    int getValue() {
        if (cardNumber > 10) {
            return 10;
        }
        else if (cardNumber == 1) {
            return 11;
        }
        return cardNumber;       
    }
};

class Deck {
private:
    vector<Card> gameDeck;
public:
    void createDeck() {
        gameDeck.clear();
        for (int i = 0; i < 13; ++i) {
            for (int j = 0; j < 4; ++j) {
                int temp = i + 1;
                Card newCard(temp, suit[j]);
                gameDeck.push_back(newCard);
            }
        }
    }
    void shuffle() {
        unsigned seed = time(0);
        mt19937 g(seed);
        std::shuffle(gameDeck.begin(), gameDeck.end(), g);
    }

    void displaycard(int index) {
        if (index >= 0 && index < gameDeck.size())
        {
            gameDeck[index].print();
            cout << endl;
        }
    }

    Card dealCards() {
        // safteycheck
        if (gameDeck.empty()) {
            //צריך למצוא מה לעשות אם החבילה ריקה
            createDeck();
            shuffle();
        }        
        Card pulledCard = gameDeck.back(); //pulling a card and saving it
        gameDeck.pop_back(); // deleting the card from the deck
        return pulledCard;        
    }
};

class Hand {
public:    
    vector<Card> playerHand;
    string text;

    void addCard(Card card) {
        playerHand.push_back(card); //add card to the vector
    }

    int getScore() {
        int countHand = 0;
        int aceCount = 0;

        for (Card card : playerHand) {
            countHand += card.getValue();
            //cout << card.getValue() << endl;
            if (card.getValue() == 11) {
                aceCount++;
            }
        }
        while (countHand > 21 && aceCount > 0)
        {
            countHand -= 10;
            aceCount--;
        }
        return countHand;
    }

    void showHand(bool isPlayer) {
        if (isPlayer) {
            text = "Your";
        }
        else { text = "The Dealer"; }
            cout << text <<" hand: " << endl;
            for (Card card : playerHand) {
                card.print();
            }        
    }
};

class Wallet {
    private:
        double balance;

    public:
        Wallet(double startingBalance) { //constractur
            balance = startingBalance;
        }        
        double getBalance() {
            return balance;
        }
        bool roundBet(double bet) {
            if (bet <= 0) {
                cout << "You cant bet that... " << endl;
            }
            else if (balance < bet) {
                cout << "you cant over bet your balance" << endl;
                return false;
            }
            else {
                balance -= bet;
                return true;
            }
        }
        void addWinnings(double amount) {
            balance += amount;
        }
};

int main()
{
    //creatin a wallet
    Wallet playerWallet(2000);   
    bool play = true;
    while (play) {
        cout << "your current balance is: " << playerWallet.getBalance() << endl;
        cout << endl;
        char anotherRound;
        int playerScore = 0;
        int dealerScore = 0;
        double roundBet;
        bool doubleDown = true;
        //creating a deck
        Deck myDeck;
        myDeck.createDeck();   //creat a deck    
        myDeck.shuffle(); //shuffle it        
        cout << "please place your bet for this round" << endl;
        cin >> roundBet;
        while (!playerWallet.roundBet(roundBet)) {
            cout << "please place your bet for this round" << endl;
            cin >> roundBet;
        }
        //creating hand for the player and for the dealler
        Hand playerHand;
        Hand dealerHand;
        //for the player
        playerHand.addCard(myDeck.dealCards());
        playerHand.addCard(myDeck.dealCards());
        playerScore = playerHand.getScore();
        playerHand.showHand(true);
        cout << "your score: " << playerScore << endl;
        cout << endl;
        //for the dealler
        dealerHand.addCard(myDeck.dealCards());
        dealerScore = dealerHand.getScore();
        dealerHand.showHand(false);
        cout << "the dealer score is: " << dealerHand.getScore() << endl;
        cout << endl;
        //starting the game
        char playerChoice;
        bool gameOver = false;
        if (playerScore == 21) {
            cout << "You got a Black Jack! you WIN!!";
            roundBet = 2.5 * roundBet;
            playerWallet.addWinnings(roundBet);
            gameOver = true;
        }
        while (!gameOver) {
            cout << "Please choose: 'h' for hit, 's' for stand or 'd' for double down (only on first move) " << endl;
            cin >> playerChoice;
            if (playerChoice == 'h') { //player choose to HIT
                doubleDown = false;
                playerHand.addCard(myDeck.dealCards());
                playerScore = playerHand.getScore();
                playerHand.showHand(true);
                cout << "your score: " << playerScore << endl;
                cout << endl;
                if (playerScore > 21) {
                    cout << endl;
                    cout << "BUST! YOU LOSE!" << endl;
                    break;
                }
            }
            else if (playerChoice == 's') { //player choose to STAND
                doubleDown = false;
                while (dealerHand.getScore() < 17) {
                    cout << "DEALER'S GETTING A CARD" << endl;
                    dealerHand.addCard(myDeck.dealCards());
                    dealerScore = dealerHand.getScore();
                    dealerHand.showHand(false);

                }
                cout << "the dealer score is: " << dealerHand.getScore() << endl;
                cout << endl;
                if (dealerHand.getScore() > 21) {
                    cout << "DEALER BUST! YOU WIN!" << endl;
                    roundBet += roundBet;
                    playerWallet.addWinnings(roundBet);
                    break;
                }
                else if (dealerHand.getScore() == playerScore) {
                    cout << "IT'S A TIE!" << endl;
                    playerWallet.addWinnings(roundBet);
                    break;
                }
                else if (dealerHand.getScore() > playerScore) {
                    cout << "DEALER WIN!" << endl;
                    break;
                }
                else {
                    cout << "YOU WIN!" << endl;
                    roundBet += roundBet;
                    playerWallet.addWinnings(roundBet);
                    break;
                }

            }
            else if (playerChoice == 'd' && doubleDown) {
                if (playerWallet.roundBet(roundBet)) {
                    roundBet = roundBet * 2;
                    playerHand.addCard(myDeck.dealCards());
                    playerScore = playerHand.getScore();
                    playerHand.showHand(true);
                    cout << "your score: " << playerScore << endl;
                    cout << endl;
                    if (playerScore > 21) {
                        cout << endl;
                        cout << "BUST! YOU LOSE!" << endl;
                        break;
                    }
                    while (dealerHand.getScore() < 17) {
                        cout << "DEALER'S GETTING A CARD" << endl;
                        dealerHand.addCard(myDeck.dealCards());
                        dealerScore = dealerHand.getScore();
                        dealerHand.showHand(false);

                    }
                    cout << "the dealer score is: " << dealerHand.getScore() << endl;
                    cout << endl;
                    if (dealerHand.getScore() > 21) {
                        cout << "DEALER BUST! YOU WIN!" << endl;
                        roundBet += roundBet;
                        playerWallet.addWinnings(roundBet);
                        break;
                    }
                    else if (dealerHand.getScore() == playerScore) {
                        cout << "IT'S A TIE!" << endl;
                        playerWallet.addWinnings(roundBet);
                        break;
                    }
                    else if (dealerHand.getScore() > playerScore) {
                        cout << "DEALER WIN!" << endl;
                        break;
                    }
                    else {
                        cout << "YOU WIN!" << endl;
                        roundBet += roundBet;
                        playerWallet.addWinnings(roundBet);
                        break;
                    }

                }
                
            }
            else {
                cout << "Invalid input' please type only 'h' or 's' " << endl;
            }

        }
        cout << "do you want to play again? " << endl;
        cout << "enter 'y' for yes or 'n' for no " << endl;
        cin >> anotherRound;
        if (anotherRound == 'n')
        {
            play = false;
        }
    }
    cout << "Thank you for playing!" << endl;
        return 0;
}


