/*
This is to certify that this project is my own work, based on my personal
efforts in studying and applying the concepts learned.  We have constructed the
functions and their respective algorithms and corresponding code by ourselves.
The program was run, tested, and debugged by my own efforts.  I further certify
that I have not copied in part or whole or otherwise plagiarized the work of
other students and/or persons. <Waynes Wu>, DLSU ID# <number> <Yu Yu>, DLSU ID#
<number>
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --------------------------------------

typedef char string20[20];
typedef char string30[30];

struct Entry {
  string20 word[10];
  string20 language[10];
  int count;
};
typedef struct Entry entry;

struct Node {
  struct Node *next;
  int data;
};
typedef struct Node intNode;

// --------------------------------------

int menu();
int manageDataInput();
void addEntry(entry allEntries[], int *allEntriesCount);
void addTranslation(entry allEntries[], int *allEntriesCount);
void deleteEntry(entry allEntries[], int *allEntriesCount);
void deleteTranslation(entry allEntries[], int *allEntriesCount);
void displayAllEntries(entry allEntries[], int *allEntriesCount);
void searchWord(entry allEntries[], int *allEntriesCount);
void export(entry allEntries[], int *allEntriesCount);
void import(entry allEntries[], int *allEntriesCount);

// helper
intNode *searchAllId(intNode *head, string20 word, string30 language,
                     entry allEntries[], int *allEntriesCount);
void printAllId(intNode *head, entry allEntries[], int *allEntriesCount);
void printList(intNode *head);

// linked list stuff
intNode *addValToLinked(intNode *head, int data);
void freeList(intNode *node);

// --------------------------------------
int main() {
  int userInputMenu, userInputData;

  bool overMenu;
  bool overData;

  // ! lmfao
  entry allEntries[150];
  int allEntriesCount = 0;

  overMenu = false;

  while (!overMenu) {
    userInputMenu = menu();

    switch (userInputMenu) {
    case 1:
      // translate
      break;

    case 2:
      overData = false;
      while (!overData) {
        do {
          userInputData = manageDataInput();
        } while (userInputData > 10 && userInputData < 0);

        switch (userInputData) {
        case 1:
          // Add Entry
          addEntry(allEntries, &allEntriesCount);
          break;
        case 2:
          // Add Translations
          addTranslation(allEntries, &allEntriesCount);
          break;
        case 3:
          // Delete Entry
          deleteEntry(allEntries, &allEntriesCount);
          break;
        case 4:
          // Delete Translation
          deleteTranslation(allEntries, &allEntriesCount);
          break;
        case 5:
          // Display All Entry
          displayAllEntries(allEntries, &allEntriesCount);
          break;
        case 6:
          // Search Word
          searchWord(allEntries, &allEntriesCount);
          break;
        case 7:
          // Export
          export(allEntries, &allEntriesCount);
          break;
        case 8:
          // Import
          import(allEntries, &allEntriesCount);
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

int menu() {
  int userInput;
  string30 divider = "---------------------------";
  string20 menuOptions[3] = {"Translate", "Manage Data", "Exit"};

  printf("\tMain Menu\n%s\n", divider);
  int i;
  for (i = 0; i < 3; i++) {
    printf("[%i] %s\n", (i + 1) % 3, menuOptions[i]);
  }
  printf("Choose one of the options: ");
  scanf("%i", &userInput);
  return userInput;
}

int manageDataInput() {
  int userInput;
  string30 divider = "---------------------------";
  string20 menuOptions[10] = {"Add Entry",
                              "Add Translations",
                              "Delete Entry",
                              "Delete Translation",
                              "Display All Entry",
                              "Search Word",
                              "Search Translation",
                              "Export",
                              "Import",
                              "Exit"};

  printf("\tManage Data\n%s\n", divider);
  int i;
  for (i = 0; i < 10; i++) {
    printf("[%i] %s\n", (i + 1) % 10, menuOptions[i]);
  }
  printf("Choose one of the options: ");
  scanf("%i", &userInput);
  return userInput;
}

void addEntry(entry allEntries[], int *allEntriesCount) {
  // ask language and word
  // f(x)- search
  // f(x) - show all info
  // ask if new
  // if no return to manage data; if yes ask for new entry (do while [continue?
  // and at least 1 char]) f(x) - add translation to new id

  intNode *listOfMatched = NULL;
  int nChoice, nCurrentCount = *allEntriesCount;
  string20 word;
  string30 language;
  printf("word: ");
  scanf("%s", word);
  printf("language: ");
  scanf("%s", language);

  listOfMatched =
      searchAllId(listOfMatched, word, language, allEntries, allEntriesCount);

  if (listOfMatched == NULL) {
    printf("Creating Entry....\n\n");
    strcpy(allEntries[nCurrentCount].language[0], language);
    strcpy(allEntries[nCurrentCount].word[0], word);
    allEntries[nCurrentCount].count = 1;
    (*allEntriesCount)++;
  }

  else {
    printf("Choice:\n");

    printf("[0] New entry?\n");
    printAllId(listOfMatched, allEntries, allEntriesCount);
    scanf("%d", &nChoice);

    if (nChoice > 0) {
      printf("Returning to Manage Data\n");
    } else if (nChoice == 0) {
      // create entry
      printf("Creating Entry.\n");
      strcpy(allEntries[nCurrentCount].language[0], language);
      strcpy(allEntries[nCurrentCount].word[0], word);
      allEntries[nCurrentCount].count = 1;
      (*allEntriesCount)++;

      // Input helper function

      // while(helper_add_translation(&allEntry[nCurrentCount]))

      /* helper_add_translation(entry *a)
      if entry.count != 10
            we can put scanf here
              add pair to entry
              return true
            if sentinel value
              return false
      else
        max has reached
          return false


      // ask more entry(loop)w/ sentinel value (also need 1 char either)

      printf("press 0 to stop adding\n");
      printf("Add Language(%d):", allEntries[nCurrentCount].count+1);

      printf("Add Word(%d):", allEntries[nCurrentCount].count+1);

      */
    }
  }

  freeList(listOfMatched);
  return;
}

// dont forget to -1 on count when used in indexing
void addTranslation(entry allEntries[], int *allEntriesCount) {
  string20 word;
  string30 language;
  printf("word: ");
  scanf("%s", word);
  printf("language: ");
  scanf("%s", language);

  return;
}

void deleteEntry(entry allEntries[], int *allEntriesCount) { return; }

void deleteTranslation(entry allEntries[], int *allEntriesCount) { return; }

void displayAllEntries(entry allEntries[], int *allEntriesCount) { return; }

void searchWord(entry allEntries[], int *allEntriesCount) {
  // ask word
  // arrange by first entries
  return;
}

void export(entry allEntries[], int *allEntriesCount) { return; }

void import(entry allEntries[], int *allEntriesCount) { return; }

intNode *searchAllId(intNode *head, string20 word, string30 language,
                     entry allEntries[], int *allEntriesCount) {
  int i;
  int count = *allEntriesCount;
  for (i = 0; i < count; i++) {
    int j;
    for (j = 0; j < allEntries[i].count; j++) {
      if (strcmp(allEntries[i].word[j], word) == 0 &&
          strcmp(allEntries[i].language[j], language) == 0) {
        head = addValToLinked(head, i);
      }
    }
  }
  return head;
}

void printAllId(intNode *head, entry allEntries[], int *allEntriesCount) {
  int i = 1;
  intNode *currentNode = head;

  while (currentNode != NULL) {
    int id = currentNode->data;
    int j;
    for (j = 0; j < allEntries[id].count; j++){
      printf("[%i]-%10s|%10s\n", i, allEntries[id].language[j], allEntries[id].word[j]);
    }
    i++;
    currentNode = currentNode->next;
  }
  return;
}

intNode *addValToLinked(intNode *head, int data) {

  intNode *currentNode = head;

  intNode *newNode = (intNode *)malloc(sizeof(intNode));
  newNode->data = data;
  newNode->next = NULL;

  if (currentNode == NULL) {
    head = newNode;
    return head;
  }

  while (currentNode->next != NULL) {
    if (currentNode->data == data)
      return head;
    currentNode = currentNode->next;
  }

  currentNode->next = newNode;
  return head;
}

void freeList(intNode *node) {
  intNode *nodeTmp = NULL;
  while (node != NULL) {
    nodeTmp = node;
    node = node->next;
    free(nodeTmp);
  }
}

void printList(intNode *head) {
  intNode *tmp = head;
  while (tmp->next != NULL) {
    printf("%i\n", tmp->data);
    tmp = tmp->next;
  }

  return;
}
