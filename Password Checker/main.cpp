#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream> //to be able to use/handle files
using namespace std;


const string rule_msg_1 = "The selected password must be at least eight characters long.";
const string rule_msg_2 = "The selected password must have at least one uppercase letter.";
const string rule_msg_3 = "The selected password must have at least one lowercase letter.";
const string rule_msg_4 = "The selected password must have at least one digit.";
const string rule_msg_5 = "The selected password must have at least one of special characters: [@,!,#,^,&,*,$]";
const string rule_msg_6 = "The selected password has been leaked.";
const string rule_msg_7 = "The selected password cannot contain a dictionary word.";



bool eightCharacters(string password){       // function boolean checking if it passes first rule of eight char
    if (password.size() < 8){
        return false;
    }
    else{
        return true;
    }
} // Rule 1 - checking if there are at least 8 characters

bool upperCase(string password) {
    for (int i = 0; i < password.length(); ++i) {
        if(isupper(password[i])){
            return true;
            break;
        }
    }
    return false;
} // Rule 2 - checking if there are at least one upper case

bool lowerCase (string password){
    for (int i = 0; i < password.length(); ++i) {
        if(islower(password[i])){
            return true;
            break;
        }
    }
    return false;
} // Rule 3 - checking if there are at least one lower case

bool oneDigit (string password){
    for (int i = 0; i < password.length(); ++i) {
        if((password[i] >= 48) && (password[i] <= 57)){ // or I could do isdigit(password[i])....
            return true;
            break;
        }
    }
    return false;
} // Rule 4  - checking if there are at least one digit

bool specialChar(string password){
    for (int i = 0; i < password.length(); ++i) {
        if(password[i] == ('!' ) || password[i] == '@' ||password[i] == '#' ||password[i] == '$' ||password[i] =='%' ||password[i] == '^' ||password[i] =='&'
        || password[i] == '*'){
            return true;
            break;
        }
    }
    return false;
} // Rule 5 - checking if there are at least one special characters

void passwordChecker(string password){

    bool eightchar = eightCharacters(password); //Rule 1
    bool uppercase = upperCase(password);//Rule 2
    bool lowercase = lowerCase(password);//Rule 3
    bool onedigit = oneDigit(password);//Rule 4
    bool specialchar = specialChar(password);//Rule 5

    if (!eightchar){
        cout << rule_msg_1 << endl;
    }
    if (!uppercase){
        cout << rule_msg_2 << endl;
    }
    if (!lowercase){
        cout << rule_msg_3 << endl;
    }
    if (!onedigit){
        cout << rule_msg_4 << endl;
    }
    if (!specialchar){
        cout << rule_msg_5 << endl;
    }

    if ( eightchar == false || uppercase == false || lowercase == false || onedigit == false || specialchar == false ) {
        cout << "Password rejected!" << endl;
        exit(0);
    }
} // checking if Rules 1-5 are all true

bool binarySearchRule6(vector<string> leakedArray, string password) { // creating a boolean binary search for the leaked password text file

    int low = 0;
    int high = leakedArray.size() - 1;
    string validPass = "";

    for (int i = 0; i < password.size(); ++i) { // this for loop is cleaning up the passwords and
        if (isalpha(password[i]) || isdigit(password[i])) {  // transferring only letters and digits to be compared on the binary search
            validPass += (password[i]);      //clean password is saved into validPass
        }
    }

    for (int i = 0; i < validPass.size(); ++i) { //putting the validPass to lower case
        validPass[i] = tolower(validPass[i]);
    }


    while (low <= high) { //while low is less or equal to high, keep going to the if else statements
        int mid = (low + high) / 2;
        string leakedWithoutSpecialChar = "";
        for (int i = 0; i < leakedArray.at(mid).size(); ++i) {
            if (isalpha(leakedArray.at(mid)[i]) || isdigit(leakedArray.at(mid)[i])) {
                leakedWithoutSpecialChar += (leakedArray.at(mid)[i]);
            }
        }


        if (validPass == leakedWithoutSpecialChar) { //checking if the password is equal to the mid value of the array
            return false; //if so, return false
        } else if (validPass > leakedArray[mid]) { // password is on the right side
            low = mid + 1;
        } else {                  // password is on the left side
            high = mid - 1;
        }
    }
    return true;



} // Binary search for RULE 6

bool binarySearchRule7(vector<string> leakedArray, string password) { // creating a boolean binary search for the leaked password text file

    int low = 0;
    int high = leakedArray.size() - 1;
    string validPass = "";

    for (int i = 0; i < password.size(); ++i) { // this for loop is cleaning up the passwords and
        if (isalpha(password[i])) {  // transferring only letters and digits to be compared on the binary search
            validPass += (password[i]);      //clean password is saved into validPass
        }
    }

    for (int i = 0; i < validPass.size(); ++i) { //putting the validPass to lower case
        validPass[i] = tolower(validPass[i]);
    }


    while (low <= high) { //while low is less or equal to high, keep going to the if else statements
        int mid = (low + high) / 2;
        string leakedWithoutSpecialChar = "";
        for (int i = 0; i < leakedArray.at(mid).size(); ++i) {
            if (isalpha(leakedArray.at(mid)[i])) {
                leakedWithoutSpecialChar += (leakedArray.at(mid)[i]);
            }
        }


        if (validPass == leakedWithoutSpecialChar) { //checking if the password is equal to the mid value of the array
            return false; //if so, return false
        } else if (validPass > leakedArray[mid]) { // password is on the right side
            low = mid + 1;
        } else {                  // password is on the left side
            high = mid - 1;
        }

    }
    return true;
} // RULE 7

void englishWordsFunction(string password, string english_word_file,vector<string> &wordsEnglishArray){
    string wordPasswords;
    ifstream wordsFile;
    wordsFile.open(english_word_file);



    if (wordsFile.is_open()) {
        while (getline(wordsFile, wordPasswords)) {
            wordsEnglishArray.push_back(wordPasswords); // adding the passwords from file to our array
        }
        wordsFile.close();
    }
    else {
        cout << "Unable to open file";
        exit(0);
    }
}

void leakedPasswordFile(string password, string leaked_password_file, vector<string> &leakedArray){

    string leakedPasswords;
    ifstream leakedFile;
    leakedFile.open(leaked_password_file);
           //array to store all the passwords from file

    //SOMETHING WRONG WITH THIS PART ********************* if you comment it out, it exit 0 normally
    if (leakedFile.is_open()) {
        while (getline(leakedFile, leakedPasswords)) {
            leakedArray.push_back(leakedPasswords); // adding the passwords from file to our array
        }
        leakedFile.close();
    }
    else {
        cout << "Unable to open file";
        exit(0);
    }

//  checking if the file was saved into the array
//    for (int i = 0; i < leakedArray.size(); ++i) {
//        cout << leakedArray[i] << endl;
//    }
}



void run(string leaked_password_file, string english_word_file) {
    string userPassword;
    cout << "Enter password: ";
    cin >> userPassword;


    //calling the five first rules:
    eightCharacters(userPassword); //Rule 1
    upperCase(userPassword);//Rule 2
    lowerCase(userPassword);//Rule 3
    oneDigit(userPassword);//Rule 4
    specialChar(userPassword);//Rule 5


    //function to check userPassword through rules 1-5
    passwordChecker(userPassword);


    //vectors to save the words from files into a vector array.
    vector<string> leakedArray;
    vector<string> wordsEnglishArray;



    //functions to open files and pass words into the arrays created
    leakedPasswordFile(userPassword, leaked_password_file,leakedArray);
    englishWordsFunction(userPassword, english_word_file, wordsEnglishArray);



    //binary search for both rule 6 and rule 7
    binarySearchRule6(leakedArray, userPassword); // rule 6
    binarySearchRule7(wordsEnglishArray, userPassword); // rule 7



    //prints out rejection for passwords if the words from passwords are found in the files
    if (!binarySearchRule6(leakedArray, userPassword)){ //rule 6
        cout << rule_msg_6 << endl;
        cout << "Password rejected!" << endl;
        exit(0);
    }
    if (!binarySearchRule7(wordsEnglishArray, userPassword)){
        cout << rule_msg_7 << endl;
        cout << "Password rejected!" << endl;
        exit(0);
    }


    cout << "Password accepted!" << endl;

}

int main() {
    /** Change the address of the files appropriatly based on your local machine.
     * This main function will be replaced during testing. Do not add any line of code to the main function
     **/
    string leaked_password_file = "alleged-gmail-passwords.txt"; //change this based on the location of the file on your machine
    string english_word_file = "words_5.txt"; //change this based on the location of the file on your machine
    run(leaked_password_file, english_word_file);

    return 0;
}
