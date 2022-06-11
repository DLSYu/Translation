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
void searchTranslation(entry allEntries[], int *allEntriesCount);
// helper
intNode *searchAllId(intNode *head, string20 word, string30 language,
                     entry allEntries[], int *allEntriesCount);
void printAllId(intNode *head, entry allEntries[], int *allEntriesCount);
void printList(intNode *head);
int helper_strcmp(const void *str1, const void *str2);
bool helper_add_translation(entry *a);
entry sortInsta(entry list);
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
          searchTranslation(allEntries, &allEntriesCount);
          break;
        case 8:
          // Export
          export(allEntries, &allEntriesCount);
          break;
        case 9:
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
                              "Search translation",
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
  printf("language: ");
  scanf("%s", language);
  printf("word: ");
  scanf("%s", word);

  listOfMatched =
      searchAllId(listOfMatched, word, language, allEntries, allEntriesCount);
  // no similar entries
  if (listOfMatched == NULL) {
    printf("\nCreating Entry....\n\n");
    strcpy(allEntries[nCurrentCount].language[0], language);
    strcpy(allEntries[nCurrentCount].word[0], word);
    allEntries[nCurrentCount].count = 1;
    (*allEntriesCount)++;
  }

  // found similar entries
  else {
    printf("\nIs your entry listed below?\n");

    printf("[0] New entry?\n\n");
    printAllId(listOfMatched, allEntries, allEntriesCount);
    scanf("%d", &nChoice);

    if (nChoice > 0) {
      printf("Returning to Manage Data\n");
      return;
    }

    else if (nChoice == 0) {
      // create entry
      printf("Creating Entry...\n");
      strcpy(allEntries[nCurrentCount].language[0], language);
      strcpy(allEntries[nCurrentCount].word[0], word);
      allEntries[nCurrentCount].count = 1;
      (*allEntriesCount)++;
    }
  }

  while (helper_add_translation(&allEntries[nCurrentCount]))
    ;

  freeList(listOfMatched);
  return;
}

// dont forget to -1 on count when used in indexing
void addTranslation(entry allEntries[], int *allEntriesCount) {
  intNode *listOfMatched = NULL;
  int nChoice;
  string20 word;
  string30 language;
  scanf("%s", language);
  printf("language: ");
  printf("word: ");
  scanf("%s", word);

  listOfMatched =
      searchAllId(listOfMatched, word, language, allEntries, allEntriesCount);
  // no existing entry->error message_return to manage data
  if (listOfMatched == NULL) {
    // print you should use add entry first
    printf("git fucked return to manage data\n");
    return;
  }

  // more than or equal one choose the entry
  else {
    int id;
    if (listOfMatched->next == NULL) {
      id = listOfMatched->data;
    }

    else {
      printf("\nWhich entry?\n");
      // printf("[0] Not listed here?\n\n");

      printAllId(listOfMatched, allEntries, allEntriesCount);
      scanf("%d", &nChoice);
      if (nChoice == 0) {
        printf("git fucked return to manage data\n");
        return;
      }

      intNode *tmp = listOfMatched;
      int i;

      // remember that link list requires address to address so we loop to get
      // next address
      for (i = 0; i < nChoice - 1; i++) {
        tmp = tmp->next;
      }
      id = tmp->data;
    }

    while (helper_add_translation(&allEntries[id]))
      ;
  }
  freeList(listOfMatched);
  return;
}

void deleteEntry(entry allEntries[], int *allEntriesCount) {
  // Show all entry info- done

  // ask which entry user wants to delete
  // input is number
  // deleting entry deletes language translation pairs too
  // if invalid
  // display message error + Manage data
  int i, j;
  int count = *allEntriesCount;
  int input;
  // show all
  for (i = 0; i < count; i++) {
    for (j = 0; j < allEntries[i].count; j++) {
      printf("[%i] %10s|%10s\n", i + 1, allEntries[i].language[j],
             allEntries[i].word[j]);
    }
    printf("\n");
  }
  // input id + 1
  printf("which entry would you like to delete? ");
  scanf("%i", &input);

  // input -1 == id == index
  input--;
  if (input >= 0 && input < count) // valid
  {
    for (i = input; i < count; i++) {
      if (i == count - 1) {
        entry x = {};
        allEntries[i] = x;

        printf("entry deleted \n");
        (*allEntriesCount)--;
        return;
      }
      allEntries[i] = allEntries[i + 1];
    }
  }

  else // invalid
  {
    printf("returning to manage data\n");
    return;
  }

  return;
}

void deleteTranslation(entry allEntries[], int *allEntriesCount) {
  // Display all entry

  // ask which entry user wants to delete from

  // input is number

  // if valid
  // only initialized can be chosen
  // delete lang-trans pair
  // keep asking for more deletion from same entry as long as user wants to
  //* if last lang-trans get deleted, delete entry too
  // if invalid get fucked
  // notify wrong
  // ask if continue(pick what to delete) or not(go manage data)

  // if invalid
  // display message error + Manage data
  char cChoice = 'Y';
  int i, j;
  int count = *allEntriesCount;
  int input;
  // show all
  for (i = 0; i < count; i++) {
    for (j = 0; j < allEntries[i].count; j++) {
      printf("[%i] %10s|%10s\n", i + 1, allEntries[i].language[j],
             allEntries[i].word[j]);
    }
    printf("\n");
  }

  printf("which entry would you like to delete? ");
  scanf("%i", &input);
  input--;
  if (input >= 0 && input < count) // valid ENTRY
  {
    while ((cChoice == 'Y' || cChoice == 'y') &&
           allEntries[input].count != 0) // to loop lang-trans deletion process
    {
      // printing all language pair
      for (i = 0; i < allEntries[input].count; i++) {

        printf("[%i] %10s|%10s\n", i + 1, allEntries[input].language[i],
               allEntries[input].word[i]);
      }

      int inputToBeGone;
      printf("which pair would you like to delete? ");
      scanf("%i", &inputToBeGone);
      inputToBeGone--;

      // if valid
      if (inputToBeGone < allEntries[input].count) {

        // loop delete lang-trans pair
        for (i = inputToBeGone; i < allEntries[input].count; i++) {
          if (i == allEntries[input].count - 1) { // last shifting or deletion
            strcpy(allEntries[input].language[inputToBeGone], "");
            strcpy(allEntries[input].word[inputToBeGone], "");
            allEntries[input].count--;
          }
          // delete or shift to right
          strcpy(allEntries[input].language[inputToBeGone],
                 allEntries[input].language[inputToBeGone + 1]);
          strcpy(allEntries[input].word[inputToBeGone],
                 allEntries[input].word[inputToBeGone + 1]);
        }

        if (allEntries[input].count == 0) {
          for (i = input; i < count; i++) {
            if (i == count - 1) {
              entry x = {};
              allEntries[i] = x;
              printf("Entry deleted \n");
              (*allEntriesCount)--;
              return;
            }
            allEntries[i] = allEntries[i + 1];
          }
        }

      }

      else // if invalid get fucked
        printf("\nInvalid Input, ");
      // ask if continue(pick what to delete) or not(go manage data)
      // ask if continue(pick what to delete) or not(go manage data)
      if (allEntries[input].count != 0) {

        do {
          printf("Would you like to continue deleting?\n"); // notify wrong
          scanf(" %c", &cChoice);
        } while (cChoice != 'N' && cChoice != 'Y' && cChoice != 'n' &&
                 cChoice != 'y');

        if (cChoice == 'n' || cChoice == 'N') {
          printf("\nReturning to Manage Data\n\n");
          return;
        }

        else if (cChoice == 'y' || cChoice == 'Y')
          printf("\nContinuing deletion\n");
      }
    }
  }

  else // invalid ENTRY
  {
    printf("returning to manage data\n");
    return;
  }

  return;
}

void displayAllEntries(entry allEntries[], int *allEntriesCount) {

  // new entry element to save current entry
  int i, nCount = *allEntriesCount;
  int nPage = 0;
  char nAct = ' ';
  // nested for loop for all entries
  while (true) {
    entry tmpEntry = allEntries[nPage];

    if (nCount == 0) {
      printf("Add new entries first\nyou will now be redirected to manage "
             "data...\n");
      return;
    }

    // display first entry(on access, otherwise display nPage)
    int currEntryCount = tmpEntry.count;
    printf("Entry has %i count\n\n", currEntryCount);
    tmpEntry = sortInsta(tmpEntry);
    // sort here
    // linear sort cuz im monkey

    for (i = 0; i < currEntryCount; i++) {
      printf("[%i] %10s|%10s\n", i + 1, tmpEntry.language[i], tmpEntry.word[i]);
    }

    if (nPage != nCount-1)
      printf("[N]ext, ");
    if (nPage != 0)
      printf("[P]revious, ");
    printf("or E[X]it\n\n");
    printf("Action: ");
    scanf(" %c", &nAct);

    // ask for action('N'ext, 'P'revious, 'X'-it)
    switch (nAct) {
    case 'N':
      if (nPage != nCount-1)
        nPage++;
      break;
    case 'P':
      if (nPage != 0)
        nPage--;
      break;
    case 'X':
      printf("\nReturning to Manage Data...\n\n");
      return;
    default:
      printf("try again lemao\n");
      break;
    }
  }

  // for all pair in entry
  // after this we sort all
  // print

  return;
}

void searchWord(entry allEntries[], int *allEntriesCount) {
  // ask word
  // arrange by first entries
  return;
}

void searchTranslation(entry allEntries[], int *allEntriesCount) { return; }

void export(entry allEntries[], int *allEntriesCount) { return; }

void import(entry allEntries[], int *allEntriesCount) {

  string30 filename;
  scanf("%s", filename);
  FILE *ptr;
  fopen(filename, "r");
  // while(fscanf(ptr, "", &) == 1);

  return;
}

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
    for (j = 0; j < allEntries[id].count; j++) {
      printf("[%i] %10s|%10s\n", i, allEntries[id].language[j],
             allEntries[id].word[j]);
    }
    printf("\n");
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

bool helper_add_translation(entry *a) {
  int count = (*a).count;
  string20 word;
  string30 language;

  if (count == 10) {
    printf("Language-Tanslation slot is full\n");
    return false;
  }

  printf("Add translation #%i\n", count + 1);
  printf("(Put 'X' on both word and language to stop)\n");
  printf("language: ");
  scanf("%s", language);
  printf("word: ");
  scanf("%s", word);

  if (strcmp(word, "X") == 0 && strcmp(language, "X") == 0)
    return false;

  // assigning values
  strcpy(a->word[count], word);
  strcpy(a->language[count], language);
  a->count++;
  return true;
}
int sortstring(const void *str1, const void *str2) {
  char *const *pp1 = str1;
  char *const *pp2 = str2;
  return strcmp(*pp1, *pp2);
}
entry sortInsta(entry list) {
  int i, j;
  string20 sTemp;

  //

  for (i = 0; i < list.count; i++) // checks first index
  {
    int min = i;
    for (j = i + 1; j < list.count; j++) // looking at the rest of the array
    {
      if (strcmp(list.language[min], list.language[j]) > 0)
        min = j;
    }
    //swap langauge
    strcpy(sTemp, list.language[i]);//original put to temp
    strcpy(list.language[i], list.language[min]);//put wanted val on i
    strcpy(list.language[min], sTemp);//put i orig val to swapped

    //swap word
    strcpy(sTemp, list.word[i]);//original put to temp
    strcpy(list.word[i], list.word[min]);//put wanted val on i
    strcpy(list.word[min], sTemp);//put i orig val to swapped
  }

  return list;
}
