#include <stdio.h>

#include "ui.h"

/*
 * Single-key input without echo.
 *  - Windows : uses _getch() from <conio.h> (original behaviour).
 *  - Others  : termios fallback so the project also builds on Linux/macOS.
 *              Keys are normalised to the Windows codes used by
 *              getPassword() below (Enter = 13, Backspace = 8).
 */
#ifdef _WIN32
#include <conio.h>

static int readKey(void)
{
    return _getch();
}
#else
#include <termios.h>
#include <unistd.h>

static int readKey(void)
{
    struct termios oldSettings, newSettings;
    int haveTerminal;
    unsigned char c = 0;
    ssize_t n;

    fflush(stdout);

    haveTerminal = (tcgetattr(STDIN_FILENO, &oldSettings) == 0);

    if(haveTerminal)
    {
        newSettings = oldSettings;
        newSettings.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
    }

    n = read(STDIN_FILENO, &c, 1);

    if(haveTerminal)
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
    }

    if(n <= 0 || c == '\n')
    {
        return 13;
    }

    if(c == 127)
    {
        return 8;
    }

    return c;
}
#endif

void header(const char title[])
{
    printf("\n\n==================================================");
    printf("\n              CITY CARE HOSPITAL");
    printf("\n              %s", title);
    printf("\n==================================================\n");
}

void successMessage(const char message[])
{
    printf("\n\n+--------------------------------------+");
    printf("\n SUCCESS: %s", message);
    printf("\n+--------------------------------------+\n");
}

void errorMessage(const char message[])
{
    printf("\n\n+--------------------------------------+");
    printf("\n ERROR: %s", message);
    printf("\n+--------------------------------------+\n");
}

void getPassword(char password[])
{
    int i = 0;
    char ch;

    while(1)
    {
        ch = readKey();

        if(ch == 13)   // Enter key
        {
            password[i] = '\0';
            break;
        }

        else if(ch == 8)   // Backspace
        {
            if(i > 0)
            {
                i--;
                printf("\b \b");
            }
        }

        else
        {
            password[i] = ch;
            i++;
            printf("*");
        }
    }
}
