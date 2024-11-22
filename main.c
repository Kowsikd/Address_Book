/*************************************************************
 * Name: Kowsik D
 * Date: 11/11/24
 * Desc: A project to create an Address book to store contacts
 *************************************************************/

#include "contact.h"

int main()
{
    AddressBook addressBook;

    //loading addressbook with some default values
    initialize(&addressBook);
    
    //all function calls should be inside the main
    printf("-----------This is an address book-----------\n\n");
    while(1)
    {
        int option = 0;
        //menu to give options for user to choose
        printf("--------Address Book Menu--------\n");
        printf("\n\t1. Create Contact\n\t2. Search Contact\n\t3. Edit Contact\n\t4. Delete Contact\n\t5. List Contacts\n\t6. Save Contacts\n\t7. Exit\n");
        printf("\n---------------------------------");
        printf("\n\nPlease enter an option to be done in the address book : ");
        
        if(scanf("%d", &option) == 0)
        {
            __fpurge(stdin);
        }
        
        //calling the function based on the user's choice
        switch (option)
        {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                listContacts(&addressBook);
                break;
            case 6:
                saveContacts(&addressBook);
                break;
            case 7:
                return 0;
            default:
                printf("\nEntered option is invalid.\nPlease choose from the given list.\n\n");
        }
    }
    return 0;
}
