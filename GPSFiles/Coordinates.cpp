#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<string> canFileOpen(int argc, char *argv[], int optind);
vector<string> getFullFile(string fileName);

string programName;

int main(int argc, char * argv[]){
    programName = argv[0];

cout << "Using file named " << argv[1] << endl;
string fileName(argv[1]);
vector<string> fileContents = getFullFile(fileName);
cout << "Coordinates are:\n";
for(int i = 0 ; i < fileContents.size(); i++){
    cout << fileContents[i] << endl;
}

}


vector<string> getFullFile(string fileName) {
	vector < string > fileContent;
	string fileContents;

	//process each file
	//create a file object
	ifstream inFile;

	inFile.open(fileName);
	if (!inFile) {
		cerr << "Unable to open file in getFullFile " << fileName
				<< " in program " << programName << endl;
		exit(1); //
	} else {
		//use getline to get the file contents into a single string
		while (getline(inFile, fileContents)) {
			fileContent.push_back(fileContents);
		}
	}

	inFile.close();
	return fileContent;
}
