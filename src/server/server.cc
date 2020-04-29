/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#define BUFFER_SIZE 256
#define PORTNUMBER "34546"

using namespace std;

void ThrowError( string Message ) {
    cerr << Message << '\n';
    exit( 1 );
}

int main( int argc, char *argv[] ) {

    // This buffer is used to hold the message.
    char buffer[ BUFFER_SIZE ];
    // This contains the internet address of the client.
    struct sockaddr_in ServerAddress, ClientAddress;
    // Number of characters read from buffer.
    int SizeOfMessage;

    /*
        Creates a socket on this computer. We save the File Descriptor
        to reference this later.
        The First Argument: 
            The address domain of the socket. Recall that 
            there are two possible address domains, the unix domain for two 
            processes which share a common file system, and the Internet domain 
            for any two hosts on the Internet.
            AF_UNIX for the Unix Domain.
            AF_INET for the Internet.
        We are using the internet here, obviously, so we use AF_INET.
        The Second Argument:
            The type of socket. There are two choices here. Using SOCK_STREAM
            which will read in a continuous stream as if from a file or pipe.
            Then there is a datagram socket SOCK_DGRAM in which messages are read
            in chunks.
        We are using SOCK_STREAM here to read in a continuous stream.
        The Third Argument:
            The protocol. If this protocol is 0 then the operating system will
            choose the most appropriate protocol. It will choose TCP for stream
            sockets and UDP for datagram sockets.
        We are using 0 here to get TCP, however, if we switch to datagram.
        We can keep this as is and trust the OS. 
    */
    int SocketFileDescriptor = socket( AF_INET, SOCK_STREAM, 0 );
    
    // Checks if the file descriptor is 0. Indicating an ThrowError.
    if ( SocketFileDescriptor < 0 )  
        ThrowError( "ThrowError opening socket" );
    
    /*
        This function zeroes all values in the ServerAddress.
            The first argument is a pointer to the buffer.
            The second argument is the size fo the buffer.
        The buffer being our Server Address Struct [ClientAddress].
    */
    bzero( (char *) &ServerAddress, sizeof( ServerAddress ) );
     
    // This identifies our Server Address to be an Internet Address.
    ServerAddress.sin_family = AF_INET;
    // This sets the address to be the IP Address of the host. (The Pi).
    ServerAddress.sin_addr.s_addr = INADDR_ANY;

    // This is the Port Number passed to the program
    // ***** This will change to use a rotating number of ports *****
    int PortNumber = atoi( PORTNUMBER );
    /* 
        Here we assign the serv_addr with the port number passed to the program
            htons() is used to change the port number from "host bye order"
            AKA normal decimal numbers. It changes it to "network byte order".
    */ 
    /*
        This will bind the current host and port number to the socket we
        created earlier.
        First Argument:
            The SocketFileDescriptor that we created earlier.
        Second Argument:
            The pointer to the ServerAddress struct. This can fail if the
            current socket (port) is already in use.
        Third Argument:
            The size of the Server Address.  
    */
        // Check the Next Port...
    do { 
        ServerAddress.sin_port = htons( PortNumber );

        ++PortNumber;
    } while ( (PortNumber < atoi(PORTNUMBER) + 10) && bind( SocketFileDescriptor, ( struct sockaddr * ) &ServerAddress, sizeof( ServerAddress )) < 0 );
              
    
    /*
        This allows the process to listen on the current socket for connections.
        The first argument is the file descriptor, the second is the size of the 
        backlog queue.
            ( i.e. the number of connections that can be waiting while the process is handling 
            the particular connection. This should be set to 5, the maximum size permitted by most systems.)
    */
    listen( SocketFileDescriptor, 5 );

    // Saves the size of the Client Address.
    socklen_t ClientAddressLength = sizeof( ClientAddress );
     
    /*
        This is the new file descriptor for the connection between the two
        computers. This will be used for all communication from this point on.
        First Argument:
            Our Socket File Descriptor.
        Second Argument:
            Client Address
        Third Argument:
            Lenght of the Client Address
    */
    // this loop ensures that we will listen for more connections following the end of a client message
    while( true ) {
	    int ConnectionFileDescriptor = accept( SocketFileDescriptor, (struct sockaddr *) &ClientAddress , &ClientAddressLength );
	    
	    // Checks if the new file descriptor 
	    if ( ConnectionFileDescriptor < 0 ) 
	        ThrowError( "ThrowError on accept" );
	    
	    // Zeroes the buffer to hold the messages.
	    bzero( buffer, BUFFER_SIZE );
	    
	    /*
	        This reads from the socket, if there is nothing there, it will
	        block until there is data to be read. It returns the length of 
	        the message read from the socket file.
	    */
	    while( true ) {
		    SizeOfMessage = read( ConnectionFileDescriptor , buffer, BUFFER_SIZE-1 );

		    while( SizeOfMessage < 2 ) {
		    	read( ConnectionFileDescriptor, buffer, BUFFER_SIZE-1 );
		    }
		     
		    stringstream info(buffer);
		    if( info.str() == "exit" ) {
		    	break;
		    }
		    // Obviously something went wrong if this happens.
		    if ( SizeOfMessage < 0 ) 
		        ThrowError( "ThrowError reading from socket" );

		    // Here we are printing the message.
		    cout << "Here are the coordinates: " << info.str() << '\n';
		    
            double latitude, longtitude;
            char lat, lon;

            info >> latitude;
            info >> lat;
            info >> longtitude;
            info >> lon;

            fstream coordinates( "/home/pi/TwitterProject/resources/Coordinates.txt" );

            if( !coordinates )
                cout << "Failed\n";

            coordinates << "$GPGLL," << latitude << "," << lat << "," << longtitude << ","
                        << lon << "," << "221325.00,A,A*72\n";

            coordinates.close();
            system( "python3 ~/TwitterProject/src/tweeting/post_tweet.py " );

		    /*
		        This returns a message to the socket file to be picked up by the client
		        confirming the message was read.
		    */
		    string message = "Proper coordinates received.";
		    SizeOfMessage = write( ConnectionFileDescriptor, message.c_str(), message.size() );
		     
		    // Obviously something went wrong here.
		    if ( SizeOfMessage < 0 ) 
		        ThrowError( "ThrowError writing to socket" );

		    bzero( buffer, BUFFER_SIZE );
	    }
    }
}
