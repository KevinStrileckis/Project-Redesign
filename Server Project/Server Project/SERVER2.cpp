//TCP

#include "SERVER.h"
#include <vector>
#include "include/Location.h"
using namespace std;

vector<Location> InitSites(vector<Location>);
string ConvertToProp(string, int);

int main()
{
    //Main locals
    int connectors = 0;
    long SUCCESSFUL;
    WSAData WinSockData;
    WORD DLLVERSION;

    //Establish initial sites database
    vector<Location> sites;
    sites = InitSites(sites);
    cout<<sites.at(1)<<endl;

    //Start Winsock DLL
    DLLVERSION = MAKEWORD(2,1);//Concats 2 and 1 together
    SUCCESSFUL = WSAStartup(DLLVERSION, &WinSockData);

    //Create Socket Struct
    SOCKADDR_IN ADDRESS;
    int AddressSize = sizeof(ADDRESS);

    //Create sockets
    SOCKET sock_LISTEN;     //
    SOCKET socket_BUFFER; //activate if connection found
    //Collection of sockets for our clients

    //Create at Internet domains (af_inet) using TCP (sock_stream)
    socket_BUFFER = socket(AF_INET, SOCK_STREAM, 0);

    char ipAd[60];
    cin>>ipAd;

    ADDRESS.sin_addr.s_addr = inet_addr( ipAd);//"71.46.246.100"/*school*/);//("127.0.0.1");
    ADDRESS.sin_family = AF_INET;
    ADDRESS.sin_port = htons(444);
    //
    //
    sock_LISTEN = socket(AF_INET, SOCK_STREAM, 0);
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    bind(sock_LISTEN, (SOCKADDR*)&ADDRESS, sizeof(ADDRESS));//bind listen to our IP
    listen(sock_LISTEN, 128);//Listen with limits
    //SOMAXCONN); //listen without limits on connections

    fd_set master;
    //Start by clearing it out ("Zero" the set)
    FD_ZERO(&master);

    //Set the first listen socket
    FD_SET(sock_LISTEN, &master);

    //TODO: manage a database of "website" informations.

    //Welcome Server User
    cout<<"Server established. Welcome to Strileckis Server Manager 2018.\n\n";

    //Run the server
    while(true){
        //SELECT will destroy the FD set, so make a duplicate
        fd_set copySet = master;

        int socketCount = select(0, &copySet/*in/out allowable*/, nullptr, nullptr, nullptr);

        for(int i=0; i<socketCount; ++i){
            SOCKET inBound = copySet.fd_array[i];
            if(inBound == sock_LISTEN){
                //Accept new connection
                //Send a message

                //Add the new connection to list of connected clients (master file set)
                SOCKET client = accept(sock_LISTEN, nullptr, nullptr);
                FD_SET(client, &master);

                //Send welcome message and increment number of connectors
                string welcome = "Welcome to the server";
                send(client, welcome.c_str(), welcome.size() + 1, 0);
                cout<<"\tAccepted new connection.\n";
                connectors++;
            }
            else{
                //Accept new message
                cout<<"\t\tAccepting new message:\t";
                char buffer[60];
                ZeroMemory(buffer, 60);
                int bytesIn = recv(inBound, buffer, 60, 0);

                //Client in not sending
                if(bytesIn <= 0){
                    cout<<"Client has dropped\n";
                    //Drop client (close the socket, remove from master)
                    closesocket(inBound);
                    FD_CLR(inBound, &master);
                }
                else{
                    if(strstr(buffer, "REQ") != nullptr){
                        cout<<"\t\tRequirement!: ";
                        if(strstr(buffer, "~sites")){
                            cout<<"Send list of sites to a client";
                            for( Location loc : sites){
                                cout<<loc.getFullSite()<<endl;
                                send(inBound, loc.getFullSite().c_str(), bytesIn, 0);
                            }
                        }
                    }
                    /*
                    //Send message to all OTHER clients
                    for(int i=0; i<master.fd_count; ++i){
                        cout<<"\t\tMessaging other clients\n";
                        SOCKET outSock = master.fd_array[i];
                        if(outSock != sock_LISTEN && outSock != inBound){
                            send(outSock, buffer, bytesIn, 0);
                        }
                    }
                    //Send message to this client
                    for(int i=0; i<master.fd_count; ++i){
                        cout<<"\t\tMessaging client\n";
                        SOCKET outSock = master.fd_array[i];
                        if(outSock != sock_LISTEN && outSock == inBound){
                            send(outSock, buffer, bytesIn, 0);
                        }
                    }
                    */
                    //Output message here
                    cout<<buffer<<endl;
                }

                //TODO: check that message is properly started
                //TODO: update database with user's message
            }
        }
    }


    WSACleanup();

    system("pause");
    return 0;
}

/**
    Generates the initial list of websites for the server to hold.

    @param a vector<Location *> to add the sites to
    @return a vector<Location *> of the list of sites
*/
vector<Location> InitSites(vector<Location> sites){
    string siteArray[] = {"kevinStrileckis.", "scps.instructure.", "skyward.scps.k12.fl.us", "https://www.monapp./", "http://gmail.",
    "https://quizlet.", "https://code.", "https://albert.io", "https://www.microsoft./en-us/", "https://gmetrix.net", "https://repl.it/",
    "https://overview.mail.yahoo./", "https://www.linkedin./feed/", "https://www.bing./", "https://www.wikipedia./",
    "https://creativecommons./", "https://www.wikimedia./", "geocities."
    } ;

    //Loop through the siteArray and:
    // 1. transform each string into a location
    // 2. add the string to the vector

    for( string s : siteArray ){
        Location buffer(ConvertToProp(s,18) + ConvertToProp("Personal.", 11) + " " + " " + " ");
        cout<<s<<endl;
        sites.push_back(buffer);
        cout<<s<<endl;
    }

    return sites;
}

//Src: https://www.youtube./watch?v=NIqYwXcUdn0


//Socket Functions
/*
    htons()
    Inet_addr()
    WSAStartup()        long successful = WSAStartup(WORD, WSADATA)
    bind()              binds socket to SOCKADDR_IN
    listen()            tells socket to listen for incoming connection. Specifies max connections
    accept()
    connect()
    WSACleanup()        terminates use of WS2_32.dll file. Pass it void, returns int
    closesocket()
 */
//TCP Use
/*
    initiating: SOCKET sock_X = socket(AF_INET, SOCK_STREAM, NULL)
    sending:    answer = send(sock_X, "You have connected to CG server!", 46, NULL)
    receiving:  answer = recv(sock_X, MESSAGE, sizeof(MESSAGE), NULL)
 */


//Code Clean up
/*
struct SOCKADDR_IN{
    short sin_family; //address fam. Usu AF_INET
    u_short sin_port; //htons() will handle reversal since byte order is different
        //host byte and network byte order conversions
    struct in_addr sin_addr; //IP for socket connection
    char sin_zero[8]; //buffer. Usu 0
};
typedef struct WSAData
{
    WORD wVersion;
    WORD wHighVersion;
    char szDescription[WSADESCRIPTION_LEN+1];
    char szSystemStatus[WSASYS_STATUS_LEN+1];
    unsigned short iMaxSockets;
    unsigned short iMaxUdpDg;
    char *IpVendorInfo;
}
*/


/**
    Pads a string so that it is the proper length

    @param s the string to pad
    @param l the length allowed
    @return a copy of s with spaces at the beginning
        so that it meets the length requirement given
        in l,      OR
        the string "invalid" if s is too long
*/
string ConvertToProp(string s, int l){
    int x = s.find("www.");
    if(x != string::npos){
        s.erase(0, x+3);
        if(s[0] == '.'){
            s.erase(0,1);
        }
    }
    x = s.find("https://");
    if(x != string::npos){
        s.erase(0, x+8);
        if(s[0] == '.'){
            s.erase(0,1);
        }
    }
    x = s.find("http://");
    if(x != string::npos){
        s.erase(0, x+7);
        if(s[0] == '.'){
            s.erase(0,1);
        }
    }
    x = s.find("http");
    if(x != string::npos){
        s.erase(0, x+4);
        if(s[0] == '.'){
            s.erase(0,1);
        }
    }
    if(s[s.length()-1] == '/'){
        s.erase(s.length()-1, s.length());
    }
    x = s.find("/");
    if(x != string::npos){
        s.erase(x);
        if(s[0] == '.'){
            s.erase(0,1);
        }
    }

    l-=1;
    if(s.length() > l){
        return "invalid";
    }
    while(s.length() < l){
        s = " "+s;
    }
    cout<<"____"<<s<<endl;
    return s;
}


/*
    cout<<"Sites[0]: "<<sites[0]<<endl;
    cout<<"Sites[17]: "<<sites[17]<<endl;
    cout<<"Sites[18]: "<<sites[18]<<endl;
    cout<<"Sites[19]: "<<sites[19]<<endl;
    cout<<"Sites[20]: "<<sites[20]<<endl;
    cout<<"Sites[25]: "<<sites[25]<<endl;
    cout<<"Sites[30]: "<<sites[30]<<endl;
    cout<<"Sites[31]: "<<sites[31]<<endl;
    cout<<"Sites[64]: "<<sites[64]<<endl;
    */
