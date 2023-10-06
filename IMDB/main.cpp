/**********************************************************
Program 4: IMDB

Course: CS 141, Fall 2022, UIC

System: DevC++ on MacBook Air

Author: Ellen Kidane, starter code provided by Dr. Sara Riazi

Student: Maria Bezerra Cunha

Class: Kidane, 10am
 **********************************************************/

#include <iostream>
#include <cctype>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

// struct for TitleRecord
struct TitleRecord { //struct to store info from TitlesFile
    string titleId; //  t_const
    string primaryTitle;
    string startYear;
    string genres;
} ;

//struct for NameRecord
struct NameRecord {
    string nameId; //       n_const
    string primaryName;
    string birthYear;
    string deathYear;
    string primaryProfession;
};

//struct for PrincipalRecord
struct PrincipalRecord{
    string titleIdPrincipals; //first column(t_const)
    string nameId; // third (n_const)
    string characters;

};

/*********************************************** Helper functions ***************************************/

//The splitString function takes a line and split it on the delimiter and push the parts into items
void splitString(string line, char delimiter, vector<string>& items ) {
	stringstream s_stream(line);
	while (s_stream.good()) {
		string item;
		getline(s_stream, item, delimiter);
		items.push_back(item);
	}
}

/**********************************************************************************************************/

// A function to read all the lines of titles file into a vector of TitleRecord, names nameTitles
void movieTitleFile(string titlesFile, vector<TitleRecord>& nameTitles) {
    ifstream titleFile;
    titleFile.open(titlesFile);
    vector<string> rowTitles;
    int i = 0;


    if (titleFile.is_open()) {
        string titlesFromFile = "";
        while (getline(titleFile, titlesFromFile)) {

            splitString(titlesFromFile, '\t', rowTitles);

            nameTitles.push_back(TitleRecord());
            nameTitles[i].titleId = rowTitles[0];
            nameTitles[i].primaryTitle = rowTitles[2];
            nameTitles[i].startYear = rowTitles[5];
            nameTitles[i].genres = rowTitles[8];
            rowTitles.clear();
            i++;
        }
        titleFile.close();


//        for (int i = 0; i < nameTitles.size(); ++i) {
//            cout << nameTitles[i].titleId << endl;
//            cout << nameTitles[i].primaryTitle << endl;
//            cout << nameTitles[i].startYear << endl;
//            cout << nameTitles[i].genres << endl;
//            cout << endl << endl << endl << endl;
//        }

    }
}

// A function to read all the lines of names file into a vector of NameRecord, nameAct
void movieNamesFile(string namesFile, vector<NameRecord> & nameAct){
    ifstream fileNameStream;
    fileNameStream.open(namesFile);
    vector<string> rowNames;
    int i = 0;

    if (fileNameStream.is_open()) {
        string namesFromFile = "";
        while (getline(fileNameStream, namesFromFile)) {

            splitString(namesFromFile, '\t', rowNames);

            nameAct.push_back(NameRecord());
            nameAct[i].nameId = rowNames[0];
            nameAct[i].primaryName = rowNames[1];
            nameAct[i].birthYear = rowNames[2];
            nameAct[i].deathYear = rowNames[3];
            nameAct[i].primaryProfession = rowNames[4];
            rowNames.clear();
            i++;
        }
        fileNameStream.close();


//        for (int i = 0; i < nameAct.size(); ++i) {
//            cout << nameAct[i].nameId << endl;
//            cout << nameAct[i].primaryName << endl;
//            cout << nameAct[i].birthYear << endl;
//            cout << nameAct[i].deathYear << endl;
//            cout << nameAct[i].primaryProfession << endl;
//            cout << endl << endl << endl << endl;
//        }

    }
}

// A function to read all the lines of principal file into a vector of PrincipalRecord, namePrincipals
void moviePrincipalsFile(string principalsFile, vector <PrincipalRecord> &namePrincipals){

    ifstream filePrincipals;
    filePrincipals.open(principalsFile);
    vector<string> rowPrincipals;
    int i = 0;

    if (filePrincipals.is_open()) {
        string PrincipalsFromFile = "";
        while (getline(filePrincipals, PrincipalsFromFile)) {

            splitString(PrincipalsFromFile, '\t', rowPrincipals);

            namePrincipals.push_back(PrincipalRecord());
            namePrincipals[i].titleIdPrincipals = rowPrincipals[0];
            namePrincipals[i].nameId = rowPrincipals[2];
            namePrincipals[i].characters = rowPrincipals[5];
            rowPrincipals.clear();
            i++;
        }
        filePrincipals.close();


//        for (int i = 0; i < namePrincipals.size(); ++i) {
//            cout << namePrincipals[i].titleIdPrincipals << endl;
//            cout << namePrincipals[i].nameId << endl;
//            cout << namePrincipals[i].characters << endl;
//            cout << endl << endl << endl << endl;
//        }

    }

}

// Function to put a word to lower case
string stringToLower(string userString) {
    for (int i = 0; i < userString.length(); ++i) {
        userString.at(i) = tolower(userString[i]);
    }
    return userString;
}

// Linear Search to search for movies (first option of main manu)
int linearSearch(string userString, vector<TitleRecord>& nameTitles, vector<TitleRecord> &matchingMovies){
    vector<string> stringWithoutPlusSign;

    userString = stringToLower(userString);
    splitString(userString, '+', stringWithoutPlusSign);
    int x = 0;


    for (int i = 0; i < nameTitles.size(); i++) {
        string tempString = "";
        for (int a = 0; a < nameTitles[i].primaryTitle.length(); ++a) { // putting the entire vector in lower case
            tempString += tolower(nameTitles[i].primaryTitle.at(a));
        }

        int counter = 0;
        for (int j = 0; j < stringWithoutPlusSign.size(); j++) {
            if (tempString.find(stringWithoutPlusSign[j]) != string::npos){
                counter++;
            }
        }

        if (counter == stringWithoutPlusSign.size()){
            matchingMovies.push_back(nameTitles.at(i));
            cout << x << ":" << endl;
            cout << "Title: "<< nameTitles.at(i).primaryTitle << endl;
            cout << "Year: "<< nameTitles.at(i).startYear << endl;

            vector<string> genres;
            splitString(nameTitles.at(i).genres, ',', genres);
            cout << "Genre: " ;
            for (int j = 0; j < genres.size(); ++j) {
                 cout << genres.at(j) << " ";
            }
            cout << endl;

            cout << "---------------" << endl;
            x++;
        }

    }

    return -1;
}

//second part of MENU option 1
void secondMenu(int choiceForSecondMenu, vector<TitleRecord> &matchingMovies, vector<TitleRecord>& nameTitles, vector<NameRecord> &nameAct, vector <PrincipalRecord> &namePrincipals){
    //using this search inside Principals file and store all the n const that matches the titleID
    string title_ID_Of_Matched_Movies = matchingMovies.at(choiceForSecondMenu).titleId;


    vector <PrincipalRecord> nconst_principals; // storing the n const of tconst from Principals

    for (int i = 0; i < namePrincipals.size(); ++i) {  // looking for the titleId against the namePrincipals file
        if (title_ID_Of_Matched_Movies == namePrincipals[i].titleIdPrincipals && namePrincipals[i].characters != "\\N"){ // checking if the titleId of the matched movies is equal to the titleId of Principals
            nconst_principals.push_back(namePrincipals[i]); //pushing back the nameId(nconst) inside the vector nconst_principals
        }
    }


    for (int j = 0; j < nconst_principals.size(); ++j) {
        for (int x = 0; x < nameAct.size(); ++x) {
            if (nconst_principals[j].nameId == nameAct[x].nameId){
                cout << nameAct[x].primaryName << " " << nconst_principals.at(j).characters << endl;
                //primaryNames.push_back(nameTitles[x].primaryTitle); //storing inside of primaryNames the names that match with the Id from nconst_Principals
            }
        }
    }

}

// Linear Search to search for actors/actresses (second option of main manu)
int linearSearch2(string userString, vector<NameRecord> &matchingActors, vector<TitleRecord>& nameTitles, vector<NameRecord> &nameAct, vector <PrincipalRecord> &namePrincipals){
    vector<string> stringWithoutPlusSign;



    userString = stringToLower(userString);
    splitString(userString, '+', stringWithoutPlusSign);
    int x = 0;

    for (int i = 0; i < nameAct.size(); i++) {
        string tempString = "";
        for (int a = 0; a < nameAct[i].primaryName.length(); ++a) { //putting the entire vector in lower case
            tempString += tolower(nameAct[i].primaryName.at(a));
        }

        int counter = 0;
        for (int j = 0; j < stringWithoutPlusSign.size(); j++) {
            if (tempString.find(stringWithoutPlusSign[j]) != string::npos){
                counter++;
            }
        }
        //primaryTitle, startYear, and character
        if (counter == stringWithoutPlusSign.size()){
            matchingActors.push_back(nameAct.at(i));
            cout << x << ":" << endl;
            cout << nameAct.at(i).primaryName << endl;
            if (nameAct.at(i).primaryProfession.size() != 0) {
                cout << nameAct.at(i).primaryProfession << ", " << endl;
            }
            cout << "(" << nameAct.at(i).birthYear << "-" << nameAct.at(i).deathYear << ")" << endl;
            cout << "---------------" << endl;
            x++;
        }
    }


    return -1;
}

// Function to look up movies from the actor input (option 2 of menu)
void findMovies_fromActorChoice(int choiceTwo_SecondMenu, vector<NameRecord> matchingActors, vector<TitleRecord>& nameTitles, vector<NameRecord> &nameAct, vector <PrincipalRecord> &namePrincipals){

    //====================================================================================================================
    //using this search inside Principals file and store all the n const that matches the titleID
    vector<string> titleId_movies;
    vector<string> characters_movies;
    string temp_nconst = matchingActors[choiceTwo_SecondMenu].nameId;

    if (choiceTwo_SecondMenu >= matchingActors.size()){
        exit(1);
    }
    /*
     * 1) find name of actor
     * 2) access the nconst
     */


    for (int i = 0; i < namePrincipals.size(); ++i) {  // looking for the nameID(nconst) against the namePrincipals file
        if (temp_nconst == namePrincipals[i].nameId){ // checking if the titleId of the matched movies is equal to the titleId of Principals
            titleId_movies.push_back(namePrincipals[i].titleIdPrincipals); //pushing back the nameId(nconst) inside the vector titleId_movies
            characters_movies.push_back(namePrincipals[i].characters);
        }
    }

    vector<string> movieNames;
    vector<string> startYear;
// 4) then go to movie Title using tconst to get movie names
    for (int c = 0; c < nameTitles.size(); ++c) {
        for (int i = 0; i < titleId_movies.size(); ++i) {
            if (titleId_movies[i] == nameTitles[c].titleId) {
                movieNames.push_back(nameTitles[c].primaryTitle); //storing the movie names inside the vector movieNames
                startYear.push_back(nameTitles[c].startYear);
            }
        }
    }
//          name of the movie + start year + character

    for (int d = 0; d < titleId_movies.size(); ++d) { // printing out
        cout << movieNames[d] << " " << startYear[d] << " " << characters_movies[d] << endl;
    }

}

// Main menu for the two functionalities in searching movies or actor/actress
void userMenu(vector<TitleRecord>& nameTitles, vector<NameRecord> &nameAct, vector <PrincipalRecord> & namePrincipals){
    cout << "Select a menu option: " << endl;
    cout << "\t1. Search for movies: " << endl;
    cout << "\t2. Search for actors/actresses: " << endl;
    cout << "\t3. Exit: " << endl;

    int menuChoice;
    string userString;
    string choice_Two_ActSearch;
    int choiceForSecondMenu;
    int choiceTwo_SecondMenu;
    string userDone1;
    string userDone2;
    cout << "Your choice --> ";
    cin >> menuChoice;
    if (cin.fail()){
        exit;
    }


    vector<TitleRecord> matchingMovies;
    vector<NameRecord> matchingActors;


    switch (menuChoice) {
        case 1:             //case one will search for movies
            cout << "Enter search phrase: ";
            cin >> userString;
            if (cin.fail()){
                exit;
            }

            linearSearch(userString, nameTitles, matchingMovies);

            if (matchingMovies.size() != 0) {
                cout << "Select a movie to see its actors/actresses (-1 to go back to the previous menu): ";
                cin >> choiceForSecondMenu;
                if (cin.fail()){
                    exit;
                }

                if (choiceForSecondMenu == -1) {
                    return (userMenu(nameTitles, nameAct, namePrincipals));
                }
                secondMenu(choiceForSecondMenu, matchingMovies, nameTitles, nameAct, namePrincipals);

                cout << "Enter search phrase (type done to go back to the previous menu): ";
                cin >> userDone1;
                if (cin.fail()){
                    exit;
                }

                if (userDone1 == "done") {
                    return (userMenu(nameTitles, nameAct, namePrincipals));
                }
            }

            // if no data match the user input, output no match found and end the case
            else{
                    cout << "No match found!" << endl;
                    exit;
            }
            break;

        case 2:             //option 2 will look for actor/actress
            cout << "Enter search phrase: ";
            cin >> choice_Two_ActSearch;
            if (cin.fail()){
                exit;
            }

            //calling linear search to find the data needed
            linearSearch2(choice_Two_ActSearch, matchingActors,nameTitles, nameAct, namePrincipals );

            if (matchingActors.size() != 0){
            cout << "Select an actor/actress to see movies (-1 to go back to the previous menu): " ;
            cin >> choiceTwo_SecondMenu;
                if (cin.fail()){
                    exit;
                }

            if(choiceTwo_SecondMenu == -1){
                return(userMenu(nameTitles, nameAct, namePrincipals));
            }
            findMovies_fromActorChoice(choiceTwo_SecondMenu, matchingActors,nameTitles, nameAct, namePrincipals);
            cout << "Enter search phrase (type done to go back to the previous menu): ";


            cin >> userDone2;
                if (cin.fail()){
                    exit;
                }

            if(userDone2 == "done"){
                return(userMenu(nameTitles, nameAct, namePrincipals));
            }
            }
            else{
                //if (matchingActors.size() == 0){
                    cout << "No match found!" << endl;
                    exit;
                //}
            }
            break;


        case 3:
            break;
    }

}

//Run function that will call all the other functions of the program
int run(string titlesFile, string namesFile, string principalsFile) {


    vector <TitleRecord> nameTitles;
    movieTitleFile(titlesFile, nameTitles);

    vector <NameRecord> nameAct;
    movieNamesFile(namesFile, nameAct);

    vector <PrincipalRecord> namePrincipals;
    moviePrincipalsFile(principalsFile, namePrincipals);

    userMenu(nameTitles, nameAct, namePrincipals);

    return 0;
}

int main() {
	//Change these addresses according to your local machine
	string titlesFile =	"movie.titles.tsv";
	string namesFile = "movie.names.tsv";
	string principalsFile = "movie.principals.tsv";


	//DO NOT change the main function. The main function will be removed by the auto-grader
	run(titlesFile, namesFile, principalsFile);

	return 0;
}
