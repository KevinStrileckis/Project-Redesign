#ifndef REDCLIENT_H
#define REDCLIENT_H

#pragma once

#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <string>

#define SCK_VERSION2 0x0202


class RedClient
{
    public:
        RedClient(char ipAddress[]);
        virtual ~RedClient();

        char* GetipAddress() { return m_ipAddress; }
        void SetipAddress(char* val) { m_ipAddress = val; }

        //Connecting to Server
        void Connect();
        void SendMessage(std::string);

        //Listening to Server
        char *ListenForMessage();


    protected:

    private:
        char *m_ipAddress;

        //Socket data
        WSAData WinSockData;
        WORD DLLVERSION;
        //Socket address
        SOCKADDR_IN ADDRESS;
        //Socket to connect to server
        SOCKET serverSocket;
        SOCKET listenSocket;
};

#endif // REDCLIENT_H
