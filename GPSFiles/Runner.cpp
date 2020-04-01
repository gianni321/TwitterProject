#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
/*
Jordan Bayless
program will run the GPS module, extract the N and W coordinates and send it to a file called myCoordinates.txt
Errors could include not being able to open a file.
*/

int main(int argc, char * argv[]){

//run the gps code and put raw coordinates data into a file called myFile
cout << "Getting GPS coordinates\n";
system("sudo gpspipe -rn 50 | grep GPGLL > myFile");
system("sleep 8");
cout << "Coordinates now in text file\n";
    string fileName = "myFile";
    ifstream inFile;
	inFile.open(fileName);
    if(!inFile){
        cerr << "Could not open file\n" << endl;
    }

    //extract doubles from file into vector
    vector<double> theCoordinates;
    //full file contents
    string fileContents;
    stringstream input;
    //current line
    string currentString;
    for(int i = 0; i < 5; i++){
    getline(inFile, currentString);
			fileContents += "\n";
            fileContents += currentString;
    }

    //get the numbers only
    while(1){
        double number;
        input >> number;
        theCoordinates.push_back(number);
        if(!input){
            break;
        }
    }

    ofstream outdata; // outdata is like cin
    outdata.open("myCoordinates.txt"); // opens the file
    double coordinatesN = theCoordinates[0];
    double coordinatesW = theCoordinates[1];
    outdata << coordinatesN << "  " << coordinatesW << endl;
      outdata.close();

system("cat myCoordinates.txt");
return 0;

}

