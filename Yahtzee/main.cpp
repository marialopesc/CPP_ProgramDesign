/****************************
 * HEADER
 *
 * Starter code provided by: Dr. Sara Riazi
 * ***************************/


#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
using namespace std;
const int HAND_SIZE = 5;



class Dice{
private:
    int value;
    bool selection;

public:

    //Randomly assigns a value between from 1 to 6 to the dice.
    void roll(){
        int ranZeroToSix = rand() % 6 + 1;
        this->value = ranZeroToSix;
    }

    int reveal() {return value;}
    //assigns a bool to keep true
    void set_Wanted_Dice(bool selection) {this->selection = selection;}
    //gets the wanted dice and return the selection (the wanted dice)
    bool get_Wanted_Dice() {return selection;}

    //The autograder will set the values directly instead of calling roll() to avoid randomness!
    void setValue(int value) {this->value = value;}

};


class Hand {
public:

    //Display the value of the five dice
    void show(){
        for (int i = 0; i < HAND_SIZE; i++) {
            cout << random_array[i].reveal() << " ";

        }
        cout << endl;
    }

    void play(){
        for (int i = 0; i < HAND_SIZE; ++i) {
            if (random_array[i].get_Wanted_Dice() != true){
                random_array[i].roll();
            }
        }
    }
    void setSelection(string selection);

    Dice* getDice(int diceNum);

    //selection is the string of dice numbers that the player wants to keep.
    //For example, "125" means that player wants to keep the first, second, and fifth dice, and roll the rest.


    void random_Num(){
        for (int i = 0; i < HAND_SIZE; i++) {
            random_array[i].roll();
        }
    }

    Hand(){
        for (int i = 0; i < HAND_SIZE; i++) {
            random_array[i].set_Wanted_Dice(false);
        }
    }


private:
    //array to type the dice and the size of HAND_SIZE, which is equal to 5
    Dice random_array[HAND_SIZE];
};


Dice* Hand::getDice(int diceNum){
    return &random_array[diceNum];
}

void Hand::setSelection(string selection){ //selection is the user input
    for (int i = 0; i < selection.length(); i++) {
        int temporary = selection.at(i) - '0'-1;
        random_array[temporary].set_Wanted_Dice(true);
    }
}

//List of rows in the board
const int ONES = 0;
const int TWOS = 1;
const int THREES = 2;
const int FOURS = 3;
const int FIVES = 4;
const int SIXES = 5;
const int THREE_OF_KIND = 6;
const int FOUR_OF_KIND = 7;
const int FULL_HOUSE = 8;
const int SMALL_STRAIGHT = 9;
const int LARGE_STRAIGHT = 10;
const int CHANCE = 11;
const int YAHTZEE = 12;
const int BOARD_SIZE=13;

class Game {

public:
    //calcScore returns a score of a hand (5 dice) for given row in the board.
    //Note the rows are indexed from zero.
    //For example if the hand is 2 1 1 5 1 then calcScore(hand, ONES) returns 3 and  calcScore(hand, TWOS) returns 2.

    //Default constructor:

    int getUpperScore();

    int getLowerScore();

    int getBonusScore();

    int getTotalScore();

    bool isPlayed(int row);

    bool isFinished();

    void play(Hand* hand, int row);

    Game();

    string dash_default(int row);

    int onesToFives(Hand* hand, int var);

    bool three_of_aKind(Hand* hand);

    bool four_of_aKind(Hand* hand);

    bool smallStraight(Hand* hand);

    bool largeStraight(Hand* hand);

    int calcScore(Hand* hand, int row);

    void show();

    bool yahtzee(Hand* hand);

    bool full_House(Hand* hand);

private:
    int array_display[BOARD_SIZE];
};

//initialize the board game to -1
Game::Game() {
    for (int i = 0; i < BOARD_SIZE; i++){
        array_display[i] = -1;
    }
}

//default dashboard to initialize row equals to 0, to replace with a '-'
string Game::dash_default(int row){
    if (array_display[row] == 0){
        return "-";
    }
    else{
        return to_string(array_display[row]);
    }
}

//Display the board
void Game::show(){
    cout << "1. Ones: "<< setw(18)<< dash_default(ONES)<< endl;
    cout << "2. Twos: "<< setw(18)<< dash_default(TWOS)<< endl;
    cout << "3. Threes: "<< setw(16)<< dash_default(THREES)<< endl;
    cout << "4. Fours: "<< setw(17) << dash_default(FOURS)<< endl;
    cout << "5. Fives: "<< setw(17) << dash_default(FIVES)<< endl;
    cout << "6. Sixes: "<< setw(17) << dash_default(SIXES)<< endl;
    cout << "   Sum: " << setw(19) << getUpperScore() << endl;
    cout << "   Bonus: " << setw(17) << getBonusScore() << endl;
    cout << "7. Three of a kind: " << setw(7) << dash_default(THREE_OF_KIND)<< endl;
    cout << "8. Four of a kind: " << setw(8) << dash_default(FOUR_OF_KIND)<< endl;
    cout << "9. Full house: " << setw(12) << dash_default(FULL_HOUSE)<< endl;
    cout << "10.Small straight: "<< setw(8) << dash_default(SMALL_STRAIGHT)<< endl;
    cout << "11.Large straight: "<< setw(8) << dash_default(LARGE_STRAIGHT)<< endl;
    cout << "12.Chance: "<< setw(16) << dash_default(CHANCE)<< endl;
    cout << "13.Yahtzee: "<< setw(15)<< dash_default(YAHTZEE)<< endl;
    cout << "Total: " << setw(22) << getTotalScore() << endl;


}

//function to calculate the score from ONES to SIXES
int Game::onesToFives(Hand* hand, int var) {
    int counter = 0;
    for (int i = 0; i < 5; ++i) {
        if(hand->getDice(i)->reveal() == var){
            counter += var;
        }
    }
    return counter;
}

bool Game::three_of_aKind(Hand* hand) {
    int counter_ones = 0;
    int counter_twos = 0;
    int counter_threes = 0;
    int counter_fours = 0;
    int counter_fives = 0;
    int counter_sixes = 0;
    for (int i = 0; i < HAND_SIZE; ++i) {
        if (hand->getDice(i)->reveal() == 1) {
            counter_ones += 1;
        }

        if (hand->getDice(i)->reveal() == 2) {
            counter_twos += 1;
        }

        if (hand->getDice(i)->reveal() == 3) {
            counter_threes += 1;
        }

        if (hand->getDice(i)->reveal() == 4) {
            counter_fours += 1;
        }

        if (hand->getDice(i)->reveal() == 5) {
            counter_fives += 1;
        }

        if (hand->getDice(i)->reveal() == 6) {
            counter_sixes += 1;
        }
    }

    if (counter_ones >= 3 || counter_twos >= 3 || counter_threes >= 3 || counter_fours >= 3 || counter_fives >= 3 ||
        counter_sixes >= 3) {
        return true;
    }

        return false;

}

bool Game::four_of_aKind(Hand* hand) {
    int counter_ones_4 = 0;
    int counter_twos_4 = 0;
    int counter_threes_4 = 0;
    int counter_fours_4 = 0;
    int counter_fives_4 = 0;
    int counter_sixes_4 = 0;
    for (int i = 0; i < HAND_SIZE; ++i) {
        if (hand->getDice(i)->reveal() == 1){
            counter_ones_4 += 1;
        }

        if (hand->getDice(i)->reveal() == 2){
            counter_twos_4 += 1;
        }

        if (hand->getDice(i)->reveal() == 3){
            counter_threes_4 += 1;
        }

        if (hand->getDice(i)->reveal() == 4){
            counter_fours_4 += 1;
        }

        if (hand->getDice(i)->reveal() == 5){
            counter_fives_4 += 1;
        }

        if (hand->getDice(i)->reveal() == 6){
            counter_sixes_4 += 1;
        }
    }

    if (counter_ones_4 >= 4 || counter_twos_4 >= 4 || counter_threes_4 >= 4 || counter_fours_4 >= 4 || counter_fives_4 >= 4 ||
        counter_sixes_4 >= 4) {
        return true;
    } else {
        return false;
    }

}

bool Game::smallStraight(Hand* hand){
    int array[6]{};
    for (int i = 0; i < HAND_SIZE; ++i) {
        if(hand->getDice(i)->reveal() == 1){
            array[0] += 1;
        }
        if(hand->getDice(i)->reveal() == 2){
            array[1] += 1;
        }
        if(hand->getDice(i)->reveal() == 3){
            array[2] += 1;
        }
        if(hand->getDice(i)->reveal() == 4){
            array[3] += 1;
        }
        if(hand->getDice(i)->reveal() == 5){
            array[4] += 1;
        }
        if(hand->getDice(i)->reveal() == 6){
            array[5] += 1;
        }
    }
    if(array[0] >= 1){
        if (array[1] >= 1 && array[2] >= 1 && array[3] >= 1){
            return true;
        }
    }
    if(array[1] >= 1){
        if (array[2] >= 1 && array[3] >= 1 && array[4] >= 1){
            return true;
        }
    }
    if(array[2] >= 1){
        if (array[3] >= 1 && array[4] >= 1 && array[5] >= 1){
            return true;
        }
    }
    return false;
}

bool Game::largeStraight(Hand* hand){
    int array[6]{};
    for (int i = 0; i < HAND_SIZE; ++i) {
        if(hand->getDice(i)->reveal() == 1){
            array[0] += 1;
        }
        if(hand->getDice(i)->reveal() == 2){
            array[1] += 1;
        }
        if(hand->getDice(i)->reveal() == 3){
            array[2] += 1;
        }
        if(hand->getDice(i)->reveal() == 4){
            array[3] += 1;
        }
        if(hand->getDice(i)->reveal() == 5){
            array[4] += 1;
        }
        if(hand->getDice(i)->reveal() == 6){
            array[5] += 1;
        }
    }
    if(array[0] == 1){
        if (array[1] == 1 && array[2] == 1 && array[3] == 1 && array[4] == 1){
            return true;
        }
    }
    if(array[1] == 1){
        if (array[2] == 1 && array[3] == 1 && array[4] == 1 && array[5] == 1){
            return true;
        }
    }
    return false;
}

bool Game::full_House(Hand* hand){
    int count = 0;
    int count2 = 0;

    int one = hand->getDice(0)->reveal();
    int two ;

    for (int i = 1 ; i < HAND_SIZE ; ++i){
        if(one != hand->getDice(i)->reveal()){
            two = hand->getDice(i)->reveal();
        }
    }
    for (int i = 0 ; i < HAND_SIZE ; ++i) {
        if(one == hand->getDice(i)->reveal()){
            count++;
        }
        else if(two == hand->getDice(i)->reveal()){
            count2++;
        }
    }
    if (count + count2 == 5){
        return true;
    }
    return false;
}

void Game::play(Hand* hand, int row){
    array_display[row] = calcScore(hand, row);
}

//Returns the score of the upper part of the board
int Game::getUpperScore(){
    int upperSum = 0;
    for (int i = 0; i < 6; ++i) {
        upperSum += array_display[i];
    }
    return upperSum;
}

//Returns the score of the lower part of the board
int Game::getLowerScore(){
    int lowerSum = 0;
    for (int i = 0; i < 6; ++i) {
        lowerSum += array_display[i];
    }
    return lowerSum;
}

//Returns the bonus points
int Game::getBonusScore(){
    int sumOfUpper = getUpperScore();
    int bonus;

    if (sumOfUpper >= 63){
        bonus = 35;
    }

    else{
        bonus = 0;
    }

    return bonus;
}

//Returns the total score
int Game::getTotalScore(){
    int upper = getUpperScore();
    int lower = getLowerScore();
    int bonus = getBonusScore();
    int total = 0;
    total = upper + lower + bonus;

    return total;
}

bool Game::yahtzee(Hand* hand){
    int count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0, count6 = 0;

    for (int i = 0; i < HAND_SIZE; ++i) {
        if (hand->getDice(i)->reveal() == 1){
            count1 += 1;
        }
        if (hand->getDice(i)->reveal() == 2){
            count2 += 1;
        }
        if (hand->getDice(i)->reveal() == 3){
            count3 += 1;
        }
        if (hand->getDice(i)->reveal() == 4){
            count4 += 1;
        }
        if (hand->getDice(i)->reveal() == 5){
            count5 += 1;
        }
        if (hand->getDice(i)->reveal() == 6){
            count6 += 1;
        }

    }

    if (count1 == 5 || count2 == 5 || count3 == 5 || count4 == 5 || count5 == 5 || count6 == 5) {
        return true;
    } else {
        return false;
    }

}

//function to calculate the score of the game
int Game::calcScore(Hand* hand, int row){
    if (row == ONES){
        //send 1 to the function
        return onesToFives(hand, 1);
    }
    if (row == TWOS){
        //send 2 to the function
        onesToFives(hand, 2);
    }
    if (row == THREES){
        //send 3 to the function
        onesToFives(hand, 3);
    }
    if (row == FOURS){
        //send 4 to the function
        onesToFives(hand, 4);
    }
    if (row == FIVES){
        //send 5 to the function
        onesToFives(hand, 5);
    }
    if (row == SIXES){
        //send 6 to the function
        onesToFives(hand, 6);
    }

    int sum = 0;
    if (row == THREE_OF_KIND) {
        if(three_of_aKind(hand)){
            for (int i = 0; i < HAND_SIZE; ++i) {
                sum += hand->getDice(i)->reveal();
            }
            return sum;
        }
    }

    int sum_4 = 0;
    if (row == FOUR_OF_KIND) {
        if(four_of_aKind(hand)){
            for (int i = 0; i < HAND_SIZE; ++i) {
                sum_4 += hand->getDice(i)->reveal();
            }
            return sum_4;
        }
    }

    if(row == FULL_HOUSE){
        if (full_House(hand)){
            return 25;
        }
    }

    int chance = 0;
    if (row == CHANCE){
        for (int i = 0; i < HAND_SIZE; ++i) {
            chance += hand->getDice(i)->reveal();
        }
        return chance;
    }

    if (row == SMALL_STRAIGHT) {
        if (smallStraight(hand)) {
            return 30;
        }
    }

    if (row == LARGE_STRAIGHT) {
        if (largeStraight(hand)) {
            return 40;
        }
    }

    if (row == YAHTZEE) {
        if (yahtzee(hand)) {
            return 50;
        }
    }


};

//Check to see if a row has been played or not (returns true if a row has been played)
bool Game::isPlayed(int row){
    if(array_display[row] != -1) {
        return true;
    }
        return false;
}

//Check to see if all rows haven been played or not (returns true if all rows have been played)
bool Game::isFinished(){
    for (int row = 0; row < BOARD_SIZE; ++row) {
        if (!isPlayed(row)){
            return false;
        }
    }
    return true;
}

//The run function is the main loop of your program
void run() {
    Game game;
    game.show();
    string choose;
    int row;
    Hand *hand = new Hand();
    while (!game.isFinished()) {
        hand->play();
        for (int i = 0; i < 2; ++i) {
            hand->show();
            cout << "Keep Dice ('s' to stop the roll): ";
            cin >> choose;
            if (choose == "s") {
                break;
            }
            hand->setSelection(choose);
            hand->play();
        }
        game.show();
        hand->show();
        cout << "Select a combination to play: ";
        cin >> row;
        while (game.isPlayed(row - 1) || row > BOARD_SIZE) {
            if (row > BOARD_SIZE) {
                cout << "Choose a number from 1-13: ";
            } else {
                cout << "Choose a different combination to play: ";
            }
            cin >> row;
        }
        game.play(hand, row - 1);
        game.show();

    }
}


//For these types of programs there exists many combinations that you might have missed. 
//The best way to check them all is to write test cases for your program. 
//Here I give you an example of checking large straight. You can design your own test cases for different parts.


void test_case() {
    Game game;
    Hand* hand = new Hand();
    hand->getDice(0)->setValue(1);
    hand->getDice(1)->setValue(1);
    hand->getDice(2)->setValue(1);
    hand->getDice(3)->setValue(1);
    hand->getDice(4)->setValue(5);
    hand->setSelection("1");
    hand->play();

    cout << hand->getDice(0)->reveal();

    bool check1 = true;
    if (game.calcScore(hand, FOUR_OF_KIND) != 9) {
        check1 = false;
    }
    if (check1) {
        cout << "check 1 passed\n";
    }
    delete hand;
    hand = new Hand();
    hand->getDice(0)->setValue(2);
    hand->getDice(1)->setValue(6);
    hand->getDice(2)->setValue(4);
    hand->getDice(3)->setValue(3);
    hand->getDice(4)->setValue(5);

    bool check2 = true;
    if (game.calcScore(hand, LARGE_STRAIGHT) != 40) {
        check2 = false;
    }

    if (check2) {
        cout << "check 2 passed\n";
    }

    hand->getDice(0)->setValue(3);
    hand->getDice(1)->setValue(2);
    hand->getDice(2)->setValue(5);
    hand->getDice(3)->setValue(6);
    hand->getDice(4)->setValue(3);

    bool check3 = true;
    if (game.calcScore(hand, LARGE_STRAIGHT) != 0) {
        check3 = false;
    }

    if (check3) {
        cout << "check 3 passed\n";
    }

    hand->getDice(0)->setValue(1);
    hand->getDice(1)->setValue(2);
    hand->getDice(2)->setValue(3);
    hand->getDice(3)->setValue(4);
    hand->getDice(4)->setValue(6);

    bool check4 = true;
    if (game.calcScore(hand, LARGE_STRAIGHT) != 0) {
        check4 = false;
    }

    if (check4) {
        cout << "check 4 passed\n";
    }


}

// THE AUTOGRADER WILL REPLACE THE MAIN FUNCTION. 
// DO NOT ADD ANY LOGIC OF YOUR PROGRAM HERE.
int main() {

    srand(time(0));
    run();
    //test_case();
    return 0;
}