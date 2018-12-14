#include "MenuMaker.h"
#include <windef.h>
#include <iostream>
#include "../include/httprip.h"

//Variable to store all sites and their statistics
std::string g_sites = ripHTTP("http://kevinstrileckis.com/Game_DB/sites.txt");
//Client
RedClient *g_client;

MenuMaker::MenuMaker()
{
    //ctor
}

HWND* MenuMaker::makeBlackMenu(HWND h, HINSTANCE inst) const
{
    HWND elements[7];
    RECT rect;
    if(GetWindowRect(h, &rect))
    {
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;
        int y = height /3 * 2;
        //Buttons
        elements[0] = CreateWindow(TEXT("button"), TEXT("Make Redesign"),
                                             WS_VISIBLE | WS_CHILD, width-175, 15, 150, 50,
                                             h,
                                         NULL, inst,  NULL);
        elements[1] = CreateWindow(TEXT("button"), TEXT("Update Redesign List"),
                                             WS_VISIBLE | WS_CHILD, width-175, 75, 150, 50,
                                             h,
                                         NULL, inst,  NULL);
        elements[2] = CreateWindow(TEXT("button"), TEXT("Sell Data"),
                                             WS_VISIBLE | WS_CHILD, width-175, 135, 150, 50,
                                             h,
                                         NULL, inst,  NULL);
        //ListBox
        elements[3] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("listbox"), "",
                                  WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL,
                                  15, 10, width/2, height/4,
                                  h, (HMENU)105, NULL, NULL);
        elements[4] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("listbox"), "",
                                  WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL,
                                  15, height/3+25, width/2, height/4,
                                  h, (HMENU)105, NULL, NULL);
        char* name = "name1";
        for(int i=0; i<60; ++i){
            SendMessage(elements[3], LB_ADDSTRING, 0, (LPARAM)name);
            SendMessage(elements[4], LB_ADDSTRING, 0, (LPARAM)name);
        }
        //Labels
        //nedit nonedit Label label lbl text Text s box str string div spread input control NULL span
        //not for this: button edit
        elements[5] =  CreateWindow(TEXT("static"), TEXT("Vulnerabilities: "),
                               WS_VISIBLE | WS_CHILD,
                               15, 15+(height/4), 100, 25,
                               h, (HMENU)3, NULL, NULL);
        elements[6] =  CreateWindow(TEXT("STATIC"), TEXT("Locations: "),
                               WS_VISIBLE | WS_CHILD,
                               15, (height) - 120, 100, 25,
                               h, (HMENU)3, NULL, NULL);
    }
    return elements;
}

HWND g_whiteListBox = NULL;
HWND* MenuMaker::makeWhiteMenu(HWND h, HINSTANCE inst, RedClient *client) const
{
    HWND elements[3];
    RECT rect;
    g_client = client;
    if(GetWindowRect(h, &rect))
    {
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;
        int y = height /3 * 2;
        //Buttons
        elements[0] = CreateWindow(TEXT("button"), TEXT("Investigate \nSelection"),
                                             WS_VISIBLE | WS_CHILD, 10, y, 150, 70,
                                             h,
                                         (HMENU)103, inst,  NULL);
        elements[1] = CreateWindow(TEXT("button"), TEXT("Refresh \nList"),
                                             WS_VISIBLE | WS_CHILD, width-180, y, 150, 70,
                                             h,
                                         (HMENU)104, inst,  NULL);
        //ListBox
        /*
        elements[2] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("listbox"), "",
                                  WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL,
                                  10, 10, width-40, height/2,
                                  h, (HMENU)105, NULL, NULL);
        char* name = (char*)malloc(sizeof(char)*30);
        for(int i=0; i<32; ++i){
                //Get the site name
            for(int j=i*30, e=0; e<16; j++, e++){
                name[e] = g_sites[j];
            }
            name[16] = '_';
            for(int j=i*30+17, e=17; e<27; j++, e++){
                name[e] = g_sites[j];
            }
            name[27] = '\0';

            SendMessage(elements[2], LB_ADDSTRING, 0, (LPARAM)name);
        }
        free(name);
        g_whiteListBox = elements[2];*/
    }
    resetWhiteListBox(h);
    return elements;
}

bool g_currentlyResetting = false;
void MenuMaker::resetWhiteListBox(HWND h) const
{
    std::cout<<"Refreshing site list\n";
    if(g_currentlyResetting){
        return;//do not reset if reset in progress
    }
    g_currentlyResetting = true;
    RECT rect;
    if(GetWindowRect(h, &rect))
    {
        //Set up window and listbox
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;
        int y = height /3 * 2;
        g_whiteListBox = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("listbox"), "",
                                  WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL,
                                  10, 10, width-40, height/2,
                                  h, (HMENU)105, NULL, NULL);
        /*Tester: access sites list from my website*/
        //g_sites = ripHTTP("http://kevinstrileckis.com/Game_DB/sites.txt");

        //Ask server for sites list
        g_client[0].SendMessage("REQ~sites");
        //
        //Receive list of sites
        char *buffer;
        char* name = (char*)malloc(sizeof(char)*30);
        buffer = g_client[0].ListenForMessage();
        std::cout<<"Site:\t"<<buffer<<std::endl;
        while(strcmp(buffer, "INVALID") != 0){
            //Get the site name and statuses
            buffer = g_client[0].ListenForMessage();
            //Add to listbox
            SendMessage(g_whiteListBox, LB_ADDSTRING, 0, (LPARAM)buffer);
            //Free buffer (patches memory leak from ListenForMessage()
            free(buffer);
        }
    }
    else{
        std::cout<<"Rectangle invalid; I will not reset the box\n";
    }
    g_currentlyResetting = false;
}
