//client "gracefully" handles incorrect user input and gives usage messages
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

//prototype functions 
string checkInput();
bool checkCoord(string input, int size);
string fixFormat(string input);


/*
This program is used as follows: set a string equal to the function call "checkInput()".
This will prompt the user to enter a lat and long grids that will be places into and returned
in the same format as the GPGLL grids that the parse.py program uses. The string can be appended to the 
coordinates.txt file along with any of the other GPGLL code. 
*/
int main(){
    string output = checkInput();
    cout << output << "\n";
    return 0;
}


/*user is prompted for latitude and longitude and it is returned as a string in the format that will 
of all the other GPGLL data 
*/
string checkInput(){
    stringstream oss;
    string latitude;
    string longitude;
    //format needs to be:$GPGLL,4036.05083,N,10504.20220,W,223602.00,A,D*74
    cout << "Enter the latitude: ";
    cin >> latitude;
    cout << "\n";
    //error check the latitude
    while(checkCoord(latitude, 2) == false){
    cout << "Enter the latitude: ";
    cin >> latitude;
    }
    fixFormat(latitude);
    cout << "Enter the longitutde: ";
    cin >> longitude;
    cout << "\n";
    //error check longitude
     while(checkCoord(longitude, 3) == false){
     cout << "Enter the longitutde: ";
     cin >> longitude;
    }
    fixFormat(longitude);
    oss << "$GPGLL," << latitude << ",N," << longitude << ",W,223602.00,A,D*74";
    return oss.str();
}



//function is called by checkInput and returns true if the coordinate is correct format. False otherwise
bool checkCoord(string input, int size){

    string delimiter = ".";
    string token = input.substr(0, input.find(delimiter));

    bool isCorrectCoord = true;
    if(token.size() != size){
        cout << "Incorrect grid format. Use format "<< size << " digits, a decimal then however many digits\n";
    }
    int decimalLocation = size +1;
    //check to make sure 4 digits, one decimal and 5 digits exist
    for(size_t i = 0; i < input.size(); i ++){
        if(i == size){
            if(input[i] != '.'){
                cout << "must include a decimal in the center of coordinate at location 5.\n";
                cout << "use format xxxx.xxxxx\n";
                return false;
            }
            i++;
        }
        else{
            if(!isdigit(input[i])){
                cout << "A non digit character was detected. User format xxxx.xxxxx\n";
                return false;
            }
        }
    }
    return isCorrectCoord;
}

//this fixes the format to include the decimal in the right spot 
string fixFormat(string input){
    string delimiter = ".";
    size_t found = input.find_first_of(".");
    string firstHalf = input.substr(0, input.find(delimiter));
    string secondHalf = input.substr((int)found+1);
    string fullString = firstHalf;
    fullString += secondHalf;
    fullString.insert(4, ".");
    cout << fullString << "\n";
}



    