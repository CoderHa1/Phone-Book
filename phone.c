#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 10
#define NAME_LENGTH 50
#define PHONE_LENGTH 15

// Contact struct to hold name and phone number
typedef struct {
    char name[NAME_LENGTH];
    char phone[PHONE_LENGTH];
} Contact;

void addContact(Contact contacts[], int *count);
void searchContact(Contact contacts[], int count);
void displayContacts(Contact contacts[], int count);
void deleteContact(Contact contacts[], int *count);

int main() {
    Contact contacts[MAX_CONTACTS];
    int count = 0;
    int option;

    while (1) {
        printf("\nPhone Book Menu:\n");
        printf("1. Add Contact\n");
        printf("2. Search Contact\n");
        printf("3. Display Contacts\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);
        getchar();  // to clear the newline from the buffer

        switch(option) {
            case 1:
                addContact(contacts, &count);
                break;
            case 2:
                searchContact(contacts, count);
                break;
            case 3:
                displayContacts(contacts, count);
                break;
            case 4:
                deleteContact(contacts, &count);
                break;
            case 5:
                printf("Exiting the phone book...\n");
                return 0;
            default:
                printf("Invalid option, please try again.\n");
        }
    }

    return 0;
}

void addContact(Contact contacts[], int *count) {
    if (*count < MAX_CONTACTS) {
        printf("Enter name: ");
        fgets(contacts[*count].name, NAME_LENGTH, stdin);
        contacts[*count].name[strcspn(contacts[*count].name, "\n")] = '\0'; // Remove trailing newline

        printf("Enter phone number: ");
        fgets(contacts[*count].phone, PHONE_LENGTH, stdin);
        contacts[*count].phone[strcspn(contacts[*count].phone, "\n")] = '\0'; // Remove trailing newline

        (*count)++;
        printf("Contact added successfully!\n");
    } else {
        printf("Phone book is full. Cannot add more contacts.\n");
    }
}

void searchContact(Contact contacts[], int count) {
    char searchName[NAME_LENGTH];
    printf("Enter name to search: ");
    fgets(searchName, NAME_LENGTH, stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; // Remove trailing newline

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcasecmp(contacts[i].name, searchName) == 0) {
            printf("Contact found: %s, Phone: %s\n", contacts[i].name, contacts[i].phone);
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("Contact not found.\n");
    }
}

void displayContacts(Contact contacts[], int count) {
    if (count == 0) {
        printf("No contacts in phone book.\n");
        return;
    }

    printf("\nPhone Book Contacts:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s - %s\n", i + 1, contacts[i].name, contacts[i].phone);
    }
}

void deleteContact(Contact contacts[], int *count) {
    if (*count == 0) {
        printf("No contacts to delete.\n");
        return;
    }

    // Display all contacts before deletion
    printf("Select the contact you want to delete:\n");
    displayContacts(contacts, *count);

    int index;
    printf("Enter the index of the contact to delete (1 to %d): ", *count);
    scanf("%d", &index);
    getchar();  // to clear the newline from the buffer

    if (index < 1 || index > *count) {
        printf("Invalid index. Please try again.\n");
        return;
    }

    // Shift contacts to delete the chosen one
    for (int i = index - 1; i < *count - 1; i++) {
        contacts[i] = contacts[i + 1];
    }

    (*count)--;  // Reduce the contact count
    printf("Contact deleted successfully.\n");
}
