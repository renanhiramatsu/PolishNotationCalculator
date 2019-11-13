
// -NAME-
// 4 May 2019
//
// This program creates a database of movies and asks users to search
// for movies. If the movie is found, it shows details and asks if the
// user wants to include it in another text file.
// displays all the favorites at the end
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>
using namespace std;

struct Movie{
    double grossTotal;
    string movieTitle,
           directorName,
           releaseDate;
    int runTime;
};

//function prototypes
Movie * createDatabase(int&);
int numberOfLines(ifstream&);
void populateMovieFromFile(ifstream&,Movie&);
void displayMovie(const Movie&);
bool caseInsensitiveCmp(string, string);
void findMovie(Movie*, int);
void saveToFile(const Movie&);
bool promptToContinue();
void displayFavorites();

//------------------------------
//             main
//receives nothing
//calls all the functions
//------------------------------
int main(){
    double grossTotal;
    string directorName, releaseDate;
    string movieTitle, inputMovie;
    int runTime, numOfMovies;
    Movie *film = createDatabase(numOfMovies);
    findMovie(film, numOfMovies);
    displayFavorites();
    delete []film;
    return 0;
}

//------------------------------
//       createDatabase
// receives the number of movies
// returns the database object
// intitializes the number of movies, creates a dynamically allocated
// array and populates each movie inside one element in the array
//------------------------------
Movie * createDatabase(int& numOfMovies)
{
    ifstream inFile;
    string name;
    bool validFile = false;
    while(validFile == false)
    {
        cout << "Enter your file name: ";
        cin >> name;
        cin.ignore();
        inFile.open(name);
        if (inFile)
            validFile = true;
        else
            cout << "Your file cannot be found! Please enter another name..."
                 << endl;
    }
    numOfMovies = numberOfLines(inFile);
    Movie *film = new Movie[numOfMovies];
    string line;
    for (int i = 0; i < numOfMovies; i++)
    {
        populateMovieFromFile(inFile,film[i]);
    }
    return film;
}

//------------------------------
//          numberOfLines
// receives the file of movies
// returns the number of lines
// this program calculates the number of lines
// that are inside the file
//------------------------------
int numberOfLines(ifstream& inFile)
{
    string line;
    int counter= 0;
    while (getline(inFile, line))
    {
        counter ++;
    }
    inFile.clear();
    inFile.seekg(0,ios::beg);
    return counter;
}

//------------------------------
//     PopulateMovieFromFile
// receives the file of movies and the empty database
// returns nothing
// this program puts all the information of one movie inside one
// element of the dynamically allocated array
//------------------------------
void populateMovieFromFile(ifstream& inFile,Movie& film)
{
    string line;
    getline(inFile, line);
    {
        unsigned long pos1, pos2, pos3, pos4; //if i use 'int' it shows warning
        int lineLength = sizeof(line);
        pos1 = line.find(',' , 0);
        film.movieTitle = line.substr(0, pos1);
        pos1 ++;
        pos2 = line.find(',', pos1);
        film.grossTotal = stod(line.substr(pos1, pos2));
        pos2 ++;
        pos3 = line.find(',', pos2);
        film.directorName = line.substr(pos2, pos3 - pos2);
        pos3++;
        pos4 = line.find(',', pos3);
        film.releaseDate = line.substr(pos3, pos4 - pos3);
        pos4++;
        film.runTime = stoi(line.substr(pos4, lineLength));
    }
}

//------------------------------
//          findMovie
// recieves the object database and the number of movies
// returns nothing
// this function compares the userInput and each line in the database.
// if there is a mtach, it outputs the movie information and asks
// the user if they want to save the movie into his/her favorites
//------------------------------
void findMovie(Movie* film, int numberOfMovies)
{
    bool exit;
    do
    {
        bool validMovie, found;
        Movie match;
        string inputMovie;
        cout << "Enter a movie title to search for: ";
        getline(cin, inputMovie);
        for (int i = 0; i < numberOfMovies; i++)
        {
            validMovie = caseInsensitiveCmp(inputMovie, film[i].movieTitle);
            if (validMovie == true)
            {
                found = true;
                match = film[i];
            }
        }
        if (found == true)
        {
            char saveOrNo;
            displayMovie(match);
            cout << endl;
            cout << "Would you like to save this movie above (Y/N)?: ";
            cin >> saveOrNo;
            if (toupper(saveOrNo) == 'Y')
            {
                saveToFile(match);
            }
        }
        else
        {
            cout << "Error!! " << inputMovie << " was not found "
                 << "in the database. " << endl;
        }
        exit = promptToContinue();
    }while(exit != false);
}

//------------------------------
//       caseInsensitiveCmp
// receives user input and one line from the database
// returns a bool if the strings match or not
// this program compares the strings to see if they match
//------------------------------
bool caseInsensitiveCmp(string inputMovie, string movieTitle)
{
    for (int i = 0; i < inputMovie.length(); i++)
    {
        inputMovie[i] = tolower(inputMovie[i]);
    }
    for (int i = 0; i < movieTitle.length(); i++)
    {
        movieTitle[i] = tolower(movieTitle[i]);
    }
    if(inputMovie == movieTitle)
    {
        return true;
    }
    else
        return false;
}


//------------------------------
//       displayMovie
// receives the database object
// returns nothing
// this program displays the information of the movie
// that the user matched with
//------------------------------
void displayMovie(const Movie & film)
{
    const int WIDTH = 15;
    cout << setw(WIDTH) << "Title: "  << film.movieTitle << endl;
    cout << setw(WIDTH) << "Gross Total: " << film.grossTotal
         << " billion dollars" << endl;
    cout << setw(WIDTH) << "Director: "  << film.directorName << endl;
    cout << setw(WIDTH) << "Release date: "
         << film.releaseDate << endl;
    cout << setw(WIDTH) << "Runtime: " << film.runTime << " minutes"
         << endl;
}

//------------------------------
//           saveToFile
// receives the database object
// returns nothing
// this program saves the movie that the user inputted into
// another file named favorites.txt if the user wishes to
//------------------------------
void saveToFile(const Movie & film)
{
    
    const int WIDTH = 15;

    ofstream outFile;
    outFile.open("favorites.txt", ios::app);
    if (outFile)
    {
        outFile << setw(WIDTH) << "Title: "  << film.movieTitle << endl;        // FILE STATUS WACK
        outFile << setw(WIDTH) << "Gross Total: " << film.grossTotal
                << " billion dollars" << endl;
        outFile << setw(WIDTH) << "Director: "
                << film.directorName << endl;
        outFile << setw(WIDTH) << "Release date: "
                << film.releaseDate << endl;
        outFile << setw(WIDTH) << "Runtime: " << film.runTime
                << " minutes" << endl;
        cout << "Successfully saved into favorites.txt!!" << endl;
        cout << endl;

    }
    else
        cout << "The file could not be opened" << endl;
    outFile.close();
    
}



//------------------------------
//       promptToContinue
// receives nothing
// returns a bool to see if the user wants to continue
// this program asks the users if they want to continue
// searching for movies.
//------------------------------
bool promptToContinue()
{
    char endOrNo;
    cout << "would you like to exit? (Y/N): ";
    cin >> endOrNo;
    cin.ignore();
    if(tolower(endOrNo) == 'y')
        return false;
    else
        return true;
}


//------------------------------
//       displayFavorites
// receives nothing
// returns nothing
// this program displays the movies that the user deemed were the favorites
// and prints them from the resultfile favorites.txt
//------------------------------
void displayFavorites()
{
    ifstream resultFile;
    string line;
    const int ELEMENTS = 5;
    int movieCount;
    int i = 0;
    resultFile.open("favorites.txt");
    movieCount = numberOfLines(resultFile);
    if (movieCount == 0)
    {
        cout << "No saved movies ";
    }
    else
    {
        cout << endl;
        cout << "Your saved movies are: " << endl;
        while(getline(resultFile, line))
        {
            cout << line << endl;
            i++;
            if (!(i % ELEMENTS))
                cout << endl;
        }
    }
}
/*
 ------- TEST RUN -------
 Enter your file name: movies.txt
 Enter a movie title to search for: frozen
 Title: Frozen
 Gross Total: 1.276 billion dollars
 Director:  Chris Buck & Jennifer Lee
 Release date:  11/27/13
 Runtime: 102 minutes
 
 Would you like to save this movie above (Y/N)?: y
 Successfully saved into favorites.txt!!
 
 would you like to exit? (Y/N): n
 Enter a movie title to search for: finding DOrY
 Title: Finding Dory
 Gross Total: 1.029 billion dollars
 Director:  Andrew Stanton
 Release date:  6/17/16
 Runtime: 97 minutes
 
 Would you like to save this movie above (Y/N)?: y
 Successfully saved into favorites.txt!!
 
 would you like to exit? (Y/N): y
 
 Your saved movies are:
 Title: Frozen
 Gross Total: 1.276 billion dollars
 Director:  Chris Buck & Jennifer Lee
 Release date:  11/27/13
 Runtime: 102 minutes
 
 Title: Finding Dory
 Gross Total: 1.029 billion dollars
 Director:  Andrew Stanton
 Release date:  6/17/16
 Runtime: 97 minutes
 
 Program ended with exit code: 0
 */

