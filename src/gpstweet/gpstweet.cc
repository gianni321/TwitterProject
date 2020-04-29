#include <fstream>
#include <string>
#include <iostream>
#include <exception>
#include <sstream>

using namespace std;

int main() {

    // Variables.
    ifstream f( "/home/pi/TwitterProject/resources/Coordinates.txt" );
    string coordinates;
    
    // Check file for coordinates
    while( getline( f, coordinates ) ) {
        if( coordinates.substr(0, 6) == "$GPGLL" )
            break;
    }

    // Throw error for coordinates not found.
    if( coordinates.substr(0, 6) != "$GPGLL" )
        throw runtime_error( "No Coordinates Found.\n" );

    // More variables.
    stringstream parsed( coordinates );
    long double latitude, longtitude;
    string lat, lon;

    getline( parsed, coordinates, ',' );

    getline( parsed, coordinates, ',' );
    latitude = atof( coordinates.c_str() );

    lat = getline( parsed, coordinates, ',' );

    getline( parsed, coordinates, ',' )
    longtitude = atof( coordinates.c_str() );

    lon = getline( parsed, coordinates, ',' );

    if( lat != "N" || lat != "S" || lon != "E" || lon != "W" )
        throw runtime_error( "Invalid Direction: "s + coordinates );

    cout << parsed;

}