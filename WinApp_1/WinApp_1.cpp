#include <windows.h>
#include "pch.h"

int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nCmdShow)
{

    MessageBox(NULL, L"\tHello World!", L"My first windows app", NULL);
    return 0;
}