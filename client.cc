#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

#include <string>
#include <iostream>
#include <iomanip>

#define BUFFER_SIZE 256

using namespace std;

void ThrowError( string message )
{
    cerr << message << '\n';
    exit( 0 );
}

int main( int argc, char *argv[] ) {

    /*
        This is the Address of the Server that we are going to connect to.
    */
    struct sockaddr_in ServerAddress;
    /*
        This defines a host computer on the Internet. This is where we will
        put the hostname of the server we are connecting to...
    */
    struct hostent *Server;

    // This holds the messages that we are going to be sending and receiving.
    char buffer[ BUFFER_SIZE ];

    // Error Checking
    if ( argc != 3 ) {
        cerr << "Usage: " << argv[0] << " [hostname] [port]\n"; 
        exit( 0 );
    }


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
    int SocketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);

    // Error Checking
    if ( SocketFileDescriptor < 0 ) 
        ThrowError( "Error: Could Not Open Socket" );

    /* 
        This uses the Internet Hostname passed as an argument to create
        the struct hostent* which contains the information about the host AKA
        the server we are trying to connect to.
        
            If its NULL then the system could not locate a host with this name.
        
        This actually works by querying large databases all around the country
        to find the information about the hostname that we supplied to the 
        function.
    */
    Server = gethostbyname( argv[1] );

    // Error Checking
    if ( Server == NULL ) {
        cerr << "Error: No Such Host\n";
        exit( 0 );
    }

    // This zeroes out the ServerAddress struct for us.
    bzero( (char *) &ServerAddress, sizeof( ServerAddress ) );


    ServerAddress.sin_family = AF_INET;

    bcopy((char *)Server->h_addr, (char *)&ServerAddress.sin_addr.s_addr, Server->h_length);

    // This is the Port Number passed to the program
    // ***** This will change to use a rotating number of ports *****
    int PortNumber = atoi(argv[2]);

    /* 
        Here we assign the ServerAddress with the port number passed to the program
            htons() is used to change the port number from "host bye order"
            AKA normal decimal numbers. It changes it to "network byte order".
    */ 
    ServerAddress.sin_port = htons( PortNumber );

    /*
        This function is called by the client to establish a connection to the server.
        
        First Argument:
            Socket File Descriptor.
        Second Argument:
            The address of the host to which we want to connect to, including the port number.
        Third Argument:
            The size of the address.

    */
    if ( connect( SocketFileDescriptor, (struct sockaddr *) &ServerAddress, sizeof( ServerAddress ) ) < 0 ) 
        ThrowError( "ERROR connecting" );

    // Creates a Message string to be sent after prompt to User.
    string Message;
    cout << "Please enter your message: ";

    // setw here limits how many chars to take in from the User.
    cin >> setw( BUFFER_SIZE-1 ) >> Message;

    // Here we write our message to our socket.    
    int SizeOfMessage = write( SocketFileDescriptor, Message.c_str(), Message.size() );

    // Error Checking
    if ( SizeOfMessage < 0 ) 
         ThrowError( "Error: Could Not Write To Socket" );

    // This zeroes out the buffer to read a new message.
    bzero( buffer, BUFFER_SIZE );

    // This reads from the socket after the server has sent us a message.
    SizeOfMessage = read( SocketFileDescriptor, buffer, BUFFER_SIZE-1 );

    // Error Checking
    if ( SizeOfMessage < 0 ) 
         ThrowError( "ERROR reading from socket" );

    // Here we print the message from the server.
    cout << buffer << '\n';

}