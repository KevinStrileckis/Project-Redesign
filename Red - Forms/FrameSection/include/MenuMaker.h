#ifndef MENUMAKER_H
#define MENUMAKER_H

#include <windows.h>
#include "../include/RedClient.h"

class MenuMaker
{
    public:
        MenuMaker();
        HWND* makeWhiteMenu(HWND, HINSTANCE, RedClient *) const;
        HWND* makeBlackMenu(HWND, HINSTANCE) const;
        void resetWhiteListBox(HWND) const;
    protected:

    private:
};

#endif // MENUMAKER_H
