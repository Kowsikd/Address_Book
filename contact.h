/*************************************************************
 * Name: Kowsik D
 * Date: 11/11/24
 * Desc: A project to create an Address book to store contacts
 *************************************************************/

#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

#define _GNU_SOURCE     //to use strcasestr in search function
#include <stdio.h>
#include <string.h>
#include <stdio_ext.h>

typedef struct
{
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct
{
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContacts(AddressBook *addressBook);

#endif
