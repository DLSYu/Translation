/*
MP WOOHOO
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// --------------------------------------

typedef char string20[20];
typedef char string30[30];

struct Entry{
    string20 word[10];
    string20 language[10];    
    int count;
};
typedef struct Entry entry;

// --------------------------------------

int menu();
int manageDataInput();
void addEntry();
void addTranslation();
void deleteEntry();
void deleteTranslation();
void displayAllEntries();
void searchWord();
void searchTranslation();
void export();
void import();

// --------------------------------------
int main()
{
    int userInputMenu, userInputData;

    bool overMenu;
    bool overData;

    overMenu = false;
    
    while (!overMenu)
    {
        userInputMenu = menu();

        switch (userInputMenu)
        {
        case 1:
            // translate
            break;

        case 2:
            overData = false;
            while (!overData)
            {
                do
                {
                    userInputData = manageDataInput();
                } while (userInputData > 10 && userInputData < 0);

                switch (userInputData)
                {
                case 1:
                    // Add Entry
                    addEntry();
                    break;
                case 2:
                    // Add Translations
                    addTranslation();
                    break;
                case 3:
                    // Delete Entry
                    deleteEntry();
                    break;
                case 4:
                    // Delete Translation
                    deleteTranslation();
                    break;
                case 5:
                    // Display All Entry
                    displayAllEntries();
                    break;
                case 6:
                    // Search Word
                    searchWord();
                    break;
                case 7:
                    // Search Translation
                    searchTranslation();
                    break;
                case 8:
                    // Export
                    export();
                    break;
                case 9:
                    // Import
                    import();
                    break;
                case 0:
                    // exit
                    overData = true;
                    break;

                default:
                break;
                }
            }
            break;

        case 0:
            // exit for input 1
            overMenu = true;
            break;

        default:
            break;
        }
    }

    return 0;
}

int menu()
{
    int userInput;
    string30 divider = "---------------------------";
    string20 menuOptions[3] = {"Translate", "Manage Data", "Exit"};

    printf("\tMain Menu\n%s\n", divider);

    for (int i = 0; i < 3; i++)
    {
        printf("[%i] %s\n", (i + 1) % 3, menuOptions[i]);
    }
    printf("Choose one of the options: ");
    scanf("%i", &userInput);
    return userInput;
}

int manageDataInput()
{
    int userInput;
    string30 divider = "---------------------------";
    string20 menuOptions[10] = {"Add Entry", "Add Translations", "Delete Entry", "Delete Translation", "Display All Entry", "Search Word", "Search Translation", "Export", "Import", "Exit"};

    printf("\tManage Data\n%s\n", divider);

    for (int i = 0; i < 10; i++)
    {
        printf("[%i] %s\n", (i + 1) % 10, menuOptions[i]);
    }
    printf("Choose one of the options: ");
    scanf("%i", &userInput);
    return userInput;
}

void addEntry()
{
    // ask language and word
    // f(x)- search
    // f(x) - show all info
    // ask if new
    // if no return to manage data; if yes ask for new entry (do while [continue? and at least 1 char])
    // f(x) - add translation to new id
    return;
}

void addTranslation()
{

    return;
}

void deleteEntry()
{
    return;
}

void deleteTranslation()
{
    return;
}

void displayAllEntries()
{
    return;
}

void searchWord()
{
    return;
}

void searchTranslation()
{
    return;
}

void export()
{
    return;
}

void import()
{
    return;
}