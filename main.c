#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAVE_FILE "contacts.txt"

struct Contact {
    char name[50];
    long long phone;
    struct Contact *next;
};

struct Contact *head = NULL;

void addContact();
void searchContact();
void displayContacts();
void deleteContact();
void saveToFile();
void loadFromFile();

int main() {
    int choice;

    loadFromFile(); // Load saved data on start

    printf("\n=== PHONE CONTACT MANAGER (By Sai Deep) ===\n");

    while (1) {
        printf("\n1. Add Contact\n");
        printf("2. Search Contact\n");
        printf("3. Display All Contacts\n");
        printf("4. Delete Contact\n");
        printf("5. Save & Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addContact(); break;
            case 2: searchContact(); break;
            case 3: displayContacts(); break;
            case 4: deleteContact(); break;
            case 5:
                saveToFile();
                printf("\nContacts saved. Exiting...\n");
                exit(0);
            default:
                printf("Invalid Input! Try again.\n");
        }
    }
}

/* ADD CONTACT */
void addContact() {
    struct Contact *newContact, *temp;
    newContact = (struct Contact *)malloc(sizeof(struct Contact));

    printf("Enter Name: ");
    scanf("%s", newContact->name);
    printf("Enter Phone Number: ");
    scanf("%lld", &newContact->phone);

    newContact->next = NULL;

    if (head == NULL) {
        head = newContact;
    } else {
        temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newContact;
    }

    printf("Contact Added Successfully!\n");
}

/* SEARCH CONTACT */
void searchContact() {
    char searchName[50];
    struct Contact *temp = head;

    printf("Enter Name to Search: ");
    scanf("%s", searchName);

    while (temp != NULL) {
        if (strcmp(temp->name, searchName) == 0) {
            printf("\n--- Contact Found ---\n");
            printf("Name: %s | Phone: %lld\n", temp->name, temp->phone);
            return;
        }
        temp = temp->next;
    }
    printf("Contact Not Found!\n");
}

/* DISPLAY CONTACTS */
void displayContacts() {
    struct Contact *temp = head;

    if (head == NULL) {
        printf("No Contacts Saved!\n");
        return;
    }

    printf("\n----- Contact List -----\n");
    while (temp != NULL) {
        printf("Name: %s | Phone: %lld\n", temp->name, temp->phone);
        temp = temp->next;
    }
}

/* DELETE CONTACT */
void deleteContact() {
    char name[50];
    struct Contact *temp = head, *prev = NULL;

    printf("Enter Name to Delete: ");
    scanf("%s", name);

    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Contact Not Found!\n");
        return;
    }

    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    free(temp);
    printf("Contact Deleted Successfully!\n");
}

/* SAVE CONTACTS TO FILE */
void saveToFile() {
    FILE *fp = fopen(SAVE_FILE, "w");
    struct Contact *temp = head;

    if (!fp) return;

    while (temp != NULL) {
        fprintf(fp, "%s %lld\n", temp->name, temp->phone);
        temp = temp->next;
    }

    fclose(fp);
}

/* LOAD CONTACTS FROM FILE */
void loadFromFile() {
    FILE *fp = fopen(SAVE_FILE, "r");
    struct Contact *newContact;
    char name[50];
    long long phone;

    if (!fp) return;

    while (fscanf(fp, "%s %lld", name, &phone) == 2) {
        newContact = (struct Contact *)malloc(sizeof(struct Contact));
        strcpy(newContact->name, name);
        newContact->phone = phone;
        newContact->next = head;
        head = newContact;
    }

    fclose(fp);
}
