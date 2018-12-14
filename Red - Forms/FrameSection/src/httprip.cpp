#include "../include/httprip.h"
#ifndef HTTPRIPPER
#define HTTPRIPPER


#include <windows.h>
#include <wininet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>

#include <winsock.h>
#include <shellapi.h>
#include <mmsystem.h>

#define HTTP_USER_AGENT "httprip"
#define BUFFER_SIZE 4200

void usage(void);
void die(const char *message);

const char http[] = "HTTP";


std::string ripHTTP(char* requesturl)
{
    int argc = 3;
    HANDLE file;
    //SECURITY_ATTRIBUTES sa;
    HINTERNET handle_Internet;
    HINTERNET url;
    char *buf = NULL;
    DWORD bytesread;
    DWORD byteswritten;
    int k;

    // validate protocol -- first 4 alphas should be http, case insensitive
    for (k = 0; k < 4; k++)
        if (requesturl[k] != http[k] &&	requesturl[k] != (char)(http[k] + 32))
            die("Invalid url");


    printf("Opening connection...\n");
    //InternetOpen is the first WinInet function called by an application.
    handle_Internet = InternetOpen(
                            HTTP_USER_AGENT,  //this file (which rips http)
                            INTERNET_OPEN_TYPE_PRECONFIG, //checks registry for configuration (proxy/direct)
                            NULL, //proxy servers allowed
                            NULL, //host names to rout through
                            0); //kind of Internet flag
    if (handle_Internet == NULL)
        die("InternetOpen()");

    printf("Requesting url...\n");
    url = InternetOpenUrl(handle_Internet, //handler
                          requesturl, //url
                          NULL, //Headers to be sent
                          0, //length of additional headers
                          INTERNET_FLAG_RAW_DATA, //find as raw HTML
                          //INTERNET_FLAG_PRAGMA_NOCACHE, //old flag--I don't know what this does
                          0);//value returned to any callback functions
    if (url == NULL)
        die("InternetOpenUrl()");

    buf = (char*)malloc(BUFFER_SIZE + 1);
    if (buf == NULL)
        die("Unable to allocate memory for receive buffer");

    printf("Saving file");
    while (InternetReadFile(url, buf, BUFFER_SIZE, &bytesread))
    {
        if (bytesread == 0)
            break;
    }
    return buf;

    free(buf);
    InternetCloseHandle(url);
    InternetCloseHandle(handle_Internet);
    CloseHandle(file);

    printf("Done.\n");

    return 0;
}



void usage(void)
{
    fprintf(stderr, "http rip - Chad Osgood\n\nusage: httprip url filename\n");
    exit(EXIT_FAILURE);
}

void die(const char *message)
{
    fprintf(stderr, "%s", message);
    exit(EXIT_FAILURE);
}


#endif // HTTPRIPPER

