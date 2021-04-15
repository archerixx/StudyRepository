#include <windows.h>

int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nCmdShow)
{

    MessageBox(NULL, L"\tHello World!", L"My first windows app", MB_OK);
    return 0;
}