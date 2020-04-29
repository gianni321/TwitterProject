#include <fstream>
#include <string>
#include <iostream>
#include <exception>
#include <sstream>

using namespace std;

int main() {

    // Variables.
    ifstream f( "/home/pi/TwitterProject/resources/Coordinates.txt" );

    if( !f )
        throw " file not open ";
    string coordinates;
    
    // Check file for coordinates
    getline( f, coordinates );

    // More variables.
    stringstream parsed( coordinates );
    long double latitude, longtitude;
    string lat, lon;

    getline( parsed, coordinates, ',' );
    cout << coordinates << '\n';

    getline( parsed, coordinates, ',' );
    latitude = atof( coordinates.c_str() ) / 100;
    cout << "latitude: " << latitude << '\n';

    getline( parsed, lat, ',' );
    cout << "lat: " << lat << '\n';

    getline( parsed, coordinates, ',' );
    longtitude = atof( coordinates.c_str() ) / 100;
    cout << "longtitude: " << longtitude << '\n';

    getline( parsed, lon, ',' );
    cout << "lon: " << lon << '\n';

    if( lat != "N" && lat != "S" || lon != "E" && lon != "W" )
        throw runtime_error( "Invalid Direction: "s + coordinates );

    stringstream coords;
    coords << "python3 ~/TwitterProject/src/tweeting/post_tweet.py "
                << "\"" << latitude << " " << lat << " " << longtitude << " " << lon << "\"";

    // coordinates.close();
    cout << coords.str() << '\n';
    system( coords.str().c_str() );

}