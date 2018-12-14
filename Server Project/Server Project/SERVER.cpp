//TCP

#include "SERVER.h"
#include <vector>
using namespace std;

int main()
{
    //Main locals
    int connectors = 0;
    long SUCCESSFUL;
    WSAData WinSockData;
    WORD DLLVERSION;

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
    vector<SOCKET> socket_COLLECTION;

    //Create at Internet domains (af_inet) using TCP (sock_stream)
    socket_BUFFER = socket(AF_INET, SOCK_STREAM, 0);
    ADDRESS.sin_addr.s_addr = inet_addr( "10.8.16.201");//"71.46.246.100"/*school*/);//("127.0.0.1");
    ADDRESS.sin_family = AF_INET;
    ADDRESS.sin_port = htons(444);
    //
    //
    sock_LISTEN = socket(AF_INET, SOCK_STREAM, 0);
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    bind(sock_LISTEN, (SOCKADDR*)&ADDRESS, sizeof(ADDRESS));//bind listen to our IP
    listen(sock_LISTEN, 128);//Listen with limits //SOMAXCONN); //listen without limits on connections
    //listen(sock_LISTEN, 4); //listen with a limit (4)

    string CONVERTER;
    char MESSAGE[200];//needs to be large enough for the largest amount of text sent at one time
    //If connection found:
    for(;;)
    {
        cout<<"\n\tSERVER: Waiting for incoming connection...";

        if(socket_BUFFER = accept(sock_LISTEN, (SOCKADDR*)&ADDRESS, &AddressSize));
        {
            connectors++;
            cout<<"\n\tA connection was found!"<<endl;
            string mess = "Welcome! You are visitor #";
            mess += to_string(connectors);
            mess += " to this server. You are added to the collection.";
            const char *cs = mess.c_str();
            SUCCESSFUL = send(socket_BUFFER, cs, 46, 0);
            socket_COLLECTION.push_back(socket_BUFFER);
        }
        if(socket_COLLECTION.size() >= 5){
            break;
        }
        /*
        connect(sock, (SOCKADDR*)&ADDRESS, sizeof(ADDRESS));
        SUCCESSFUL = recv(sock,MESSAGE, sizeof(MESSAGE), 0);
        CONVERTER = MESSAGE;
        cout<<"\n\tMessage from CLIENT:\n\n\t"<<CONVERTER<<endl;
        if(socket_COLLECTION.size() >= 5){
            shutdown(socket_BUFFER, SD_BOTH);
            closesocket(socket_BUFFER);
            for(vector<SOCKET>::iterator iter = socket_COLLECTION.begin();
                    iter < socket_COLLECTION.end(); iter++){
                shutdown(*iter, SD_BOTH);
                closesocket(*iter);
            }
            break;
        }*/
    }
    system("pause");
    return 0;
}

//Src: https://www.youtube.com/watch?v=NIqYwXcUdn0


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
