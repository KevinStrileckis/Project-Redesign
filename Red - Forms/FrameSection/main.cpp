#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include "MenuMaker.h"
#include "RedClient.h"
#include <iostream>
#include <stdlib.h>
#include "include/httprip.h"
#include <map>
#include "../../Red/include/LocationList.h"
#include <vector>
using namespace std;


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

//Menu maker tool
MenuMaker g_menuMaker;

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    //Create the client
    RedClient *g_client;
    //
    //Ask the user for the IP address to connect to.
    // I will let students know what IP address on which the server is hosted
    char ipString[15];
    cin>>ipString;
    g_client = (RedClient *)malloc(sizeof(RedClient));
    g_client[0] = RedClient(ipString);
    //Connect to the server
    g_client[0].Connect();
    //
    //

    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) (COLOR_WINDOW-2);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("White Menu"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );
    //HWND *elementsWhite, *elementsBlack;
    g_menuMaker.makeWhiteMenu(hwnd, hThisInstance, g_client);//THE elements DOES NOT WORK
    //elementsBlack = m.makeBlackMenu(hwnd, hThisInstance);


    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

void displayListItemSelection(HWND hwnd){
    HWND hwndList1 = GetDlgItem(hwnd, 105 );
    int itemIndex = (int) SendMessage(hwndList1, LB_GETCURSEL, (WPARAM)0, (LPARAM) 0);
    std::cout<<itemIndex<<endl;
    //Reset the box
    // Has been tested with //for(int i=0; i<1000; ++i)
    g_menuMaker.resetWhiteListBox(hwnd);

}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_COMMAND:
            switch(wParam)
            {
                case 103:
                    //Investigate selection
                    //CreateProcessA( NULL, "cardgame/Red.exe", NULL,NULL, NULL,NULL, NULL, NULL,NULL ,NULL);
                    ShellExecute(hwnd, NULL, "cardgame\\Red.exe", "-l", NULL, SW_NORMAL);
                    return DefWindowProc (hwnd, message, wParam, lParam);
                case 104:
                    //Refresh list
                    displayListItemSelection(hwnd);
                    return DefWindowProc (hwnd, message, wParam, lParam);
                default:
                    return DefWindowProc (hwnd, message, wParam, lParam);
            }
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}


//Developer's Diary:
//11-20-2018:
/*HTTP Reading
    I just tested the update listbox function for White Hat. Looking into how to
    send data from C++ to HTTP using POST I'm tempted to make it a stretch goal.
    In that case, I would have students read as often as they liked, but would
    change the sites.txt myself. Alternatively, I could have several files on my
    website, splitting sites into their levels and names.
    This project really shows how little I understand about transmitting data
    over HTTP.
    Src: https://stackoverflow.com/questions/26070899/use-c-to-send-a-file-using-http-post
    */
