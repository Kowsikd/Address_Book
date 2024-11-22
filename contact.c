/*************************************************************
 * Name: Kowsik D
 * Date: 11/11/24
 * Desc: A project to create an Address book to store contacts
 *************************************************************/

#include "contact.h"

//function to validate name, phone.no and email
int validate(int j, char name[], char phone[], char email[], AddressBook *addressBook)
{
    int i, flag = 0;
    //To check the given name only conntains alphabets and space character
    for(i = 0; i < strlen(name); i++)
    {
        if((name[i] >= 65 && name[i] <= 90) || (name[i] >= 97 && name[i] <= 122) || name[i] == 32)
        {
            flag = 0;
        }
        else
        {
            flag = 1;
            printf("\nGiven name is not valid.\nName should only contain Alphabets.\n\n");
            break;
        }
    }
    //To check the given name is unique in address book
    if(!flag)
    {
        int found = 0;
        for(i = 0; i < addressBook->contactCount; i++)
        {
            if(i == j)
            {
                continue;
            }
            if(!(strcmp(addressBook->contacts[i].name, name)))
            {
                found = 1;
                break;
            }
        }
        if(found)
        {
            flag = 1;
            printf("\nEntered name already exists.\nPlease try another name.\n\n");
        }
    }

    //To check the given phone no. only contains numbers and has a length of 10
    if(!flag)
    {
        if(strlen(phone) == 10)
        {
            for(i = 0; i < strlen(phone); i++)
            {
                if(phone[i] >= 48 && phone[i] <= 57)
                {
                    flag = 0;
                }
                else
                {
                    flag = 1;
                }
            }
            if(flag)
            {
                printf("\nGiven phone number is not valid!\nPhone.no should be numeric values.\n\n");
            }
        }
        else
        {
            flag = 1;
            printf("\nError! Given phone number is not valid!\nPhone.no should be numeric values and exactly 10 digits.\n\n");
        }
    }
    //To check the given phone no. is unique in address book
    if(!flag)
    {
        int found = 0;
        for(i = 0; i < addressBook->contactCount; i++)
        {
            if(i == j)
            {
                continue;
            }
            if(!(strcmp(addressBook->contacts[i].phone, phone)))
            {
                found = 1;
                break;
            }
        }
        if(found)
        {
            flag = 1;
            printf("\nEntered phone no. already exists.\nPlease try another phone no.\n\n");
        }
    }

    //To check the given email has a proper form
    if(!flag)
    {
        int at = 0;
        int com = 0;
        if((strstr(email, "@")) != NULL)
        {
            at = 1;
        }
        if((strstr(email, ".com")) != NULL)
        {
            com = 1;
        }
        if(at == 1 && com == 1)
        {
            flag = 0;
        }
        else
        {
            flag = 1;
            printf("\nGiven email is not in proper form.\nEmail should contain @ and .com!\n\n");
        }
    }
    //To check the given email is unique in address book
    if(!flag)
    {
        int found = 0;
        for(i = 0; i < addressBook->contactCount; i++)
        {
            if(i == j)
            {
                continue;
            }
            if(!(strcmp(addressBook->contacts[i].email, email)))
            {
                found = 1;
                break;
            }
        }
        if(found)
        {
            flag = 1;
                printf("\nEntered email already exists.\nPlease try another email.\n\n");
        }
    }
    
    return flag;
}

//function to initialize address book with some default values
void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    FILE *fptr = fopen("contact.txt", "r");
    if(fptr == NULL)
    {
        printf("Error opening file.\nCheck the file before proceeding further.\n\n");
    }
    else
    {
        char ch;
        char temp[50];
        char *token;
        while((ch = getc(fptr)) != EOF)
        {
            fseek(fptr, -1, SEEK_CUR);
            fscanf(fptr, "%[^\n]", temp);

            strcpy(addressBook->contacts[addressBook->contactCount].name, strtok(temp, ","));
            strcpy(addressBook->contacts[addressBook->contactCount].phone, strtok(NULL, ","));
            strcpy(addressBook->contacts[addressBook->contactCount].email, strtok(NULL, ","));

            fseek(fptr, 1, SEEK_CUR);
            (addressBook->contactCount)++;
        }
    }
    fclose(fptr);
}

//function to list the contacts in the address book
void listContacts(AddressBook *addressBook) 
{
    printf("\n------------Listing the Address book contacts------------\n\n");
    printf("S.No.\t   Name\t\t  Phone no.\t    Email\n");
    printf("-----------------------------------------------------------\n");
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%d \t %s \t %s \t %s\n", i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    printf("\n");
}

//function to create a new contact in the address book
void createContact(AddressBook *addressBook) 
{
    //prompt if the address book is full
    if(addressBook->contactCount == 100)
    {
        printf("\nAddress book is full.\nYou can't enter any more contacts.\n\n");
    }
    else
    {
        char name[50];
        char phone[20];
        char email[50];
        printf("\n------------Entering new contact information------------\n\n");
        while(1)
        {
            printf("Enter the Name : ");
            scanf(" %49[^\n]", name);

            printf("Enter the Phone : ");
            scanf(" %19[^\n]", phone);
            
            printf("Enter the Email : ");
            scanf(" %49[^\n]", email);
            
            int flag;
            flag = validate(-1, name, phone, email, addressBook);

            if(flag)
            {
                continue;
            }
            else
            {
                break;
            }
        }
        strcpy(addressBook->contacts[addressBook->contactCount].name, name);
        strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
        strcpy(addressBook->contacts[addressBook->contactCount].email, email);
        printf("\nS.No.\t   Name\t\t Phone no.\t    Email\n");
        printf("-----------------------------------------------------------\n");
        printf("%d \t %s \t %s \t %s\n", addressBook->contactCount+1, addressBook->contacts[addressBook->contactCount].name, addressBook->contacts[addressBook->contactCount].phone, addressBook->contacts[addressBook->contactCount].email);
        (addressBook->contactCount)++;
        printf("\nContact has been registered successfully.\n\n");
        //listContacts(addressBook);
    }
}

//function to search contacts in the address book
void searchContact(AddressBook *addressBook) 
{
    int option = 0;
    printf("\n------------searching the Address book for a contact------------\n");
    printf("\n1. Name\n2. Phone no.\n3. Email\n");             //giving options by which user wants to search the contact
    printf("Enter the option by which you want to search : ");

    if(scanf("%d", &option) == 0)
    {
        __fpurge(stdin);
    }

    int flag = 0, count = 0;
    switch(option)
    {
        case 1:
            char name[50];
            printf("\nEnter the name : ");
            scanf(" %49[^\n]", name);
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcasestr(addressBook->contacts[i].name, name) != NULL)    //strcasestr to search contacts case insensitive
                {
                    if(count == 0)            //to display only once before first found value
                    {
                        printf("\nS.No.\t   Name\t\t Phone no.\t    Email\n");
                        printf("-----------------------------------------------------------\n");
                    }
                    printf("%d \t %s \t %s \t %s\n", ++count, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    flag = 1;
                }
            }
            printf("\n");
            if(!flag)
            {
                printf("Entered name doesn't present in the address book\n\n");
            }
            break;
        case 2:
            char phone[20];
            printf("\nEnter the phone no. : ");
            scanf(" %19[^\n]", phone);
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strstr(addressBook->contacts[i].phone, phone) != NULL)
                {
                    if(count == 0)
                    {
                        printf("\nS.No.\t   Name\t\t Phone no.\t    Email\n");
                        printf("-----------------------------------------------------------\n");
                    }
                    printf("%d\t%s\t%s\t%s\n", ++count, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    flag = 1;
                }
            }
            printf("\n");
            if(!flag)
            {
                printf("Entered phone no. doesn't present in the address book\n\n");
            }
            break;
        case 3:
            char email[50];
            printf("\nEnter the email : ");
            scanf(" %49[^\n]", email);
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcasestr(addressBook->contacts[i].email, email) != NULL)
                {
                    if(count == 0)
                    {
                        printf("\nS.No.\t   Name\t\t Phone no.\t    Email\n");
                        printf("-----------------------------------------------------------\n");
                    }
                    printf("%d\t%s\t%s\t%s\n", ++count, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    flag = 1;
                }
            }
            printf("\n");
            if(!flag)
            {
                printf("Entered email doesn't present in the address book\n\n");
            }
            break;
        default:
            printf("\nEntered option is invalid.\n\n");
    }
}

//function to edit contact in the address book
void editContact(AddressBook *addressBook) 
{
    printf("\n------------Editing the contact in Address book------------\n");
    int option = 0;
    printf("\nsearching the Address book for a contact to edit\n\n");
    printf("1. Name\n2. Phone no.\n3. Email\n");               //options by which user want to search the contact to edit
    printf("Enter the option by which you want to search : ");

    if(scanf("%d", &option) == 0)
    {
        __fpurge(stdin);
    }

    int i, found = 0, flag;
    char name[50], phone[20], email[50];
    switch(option)
    {
        case 1:
            printf("\nEnter the Name : ");
            scanf(" %49[^\n]", name);
            for(i = 0; i < addressBook->contactCount; i++)
            {
                if(!(strcmp(addressBook->contacts[i].name, name)))
                {
                    found = 1;
                    break;
                }
            }
            if(found)
            {
                printf("\nContact found.\n");
                printf("\nS.No.\t   Name\t\t Phone no.\t    Email\n");
                printf("-----------------------------------------------------------\n");
                printf("%d \t %s \t %s \t %s\n", i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("\nEnter details to edit contact.\n");
                while(1)
                {
                    printf("Enter the Name : ");
                    scanf(" %49[^\n]", name);

                    printf("Enter the Phone : ");
                    scanf(" %19[^\n]", phone);
                    
                    printf("Enter the Email : ");
                    scanf(" %49[^\n]", email);
                    
                    flag = validate(i, name, phone, email, addressBook);

                    if(flag)
                    {
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
                strcpy(addressBook->contacts[i].name, name);
                strcpy(addressBook->contacts[i].phone, phone);
                strcpy(addressBook->contacts[i].email, email);
                printf("Here is the updated contact list.\n");
                listContacts(addressBook);                    //to display the contacts after editing
            }
            else
            {
                printf("\nEntered name not found.\n\n");
            }
            break;
        case 2:
            printf("\nEnter the phone no. : ");
            scanf(" %19[^\n]", phone);
            for(i = 0; i < addressBook->contactCount; i++)
            {
                if(!(strcmp(addressBook->contacts[i].phone, phone)))
                {
                    found = 1;
                    break;
                }
            }
            if(found)
            {
                printf("\nContact found.\n");
                printf("\nS.No.\t   Name\t\t Phone no.\t    Email\n");
                printf("-----------------------------------------------------------\n");
                printf("%d \t %s \t %s \t %s\n", i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("\nEnter details to edit contact.\n");
                while(1)
                {
                    printf("Enter the Name : ");
                    scanf(" %49[^\n]", name);

                    printf("Enter the Phone : ");
                    scanf(" %19[^\n]", phone);
                    
                    printf("Enter the Email : ");
                    scanf(" %49[^\n]", email);
                    
                    flag = validate(i, name, phone, email, addressBook);

                    if(flag)
                    {
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
                strcpy(addressBook->contacts[i].name, name);
                strcpy(addressBook->contacts[i].phone, phone);
                strcpy(addressBook->contacts[i].email, email);
                printf("Here is the updated contact list.\n");
                listContacts(addressBook);
            }
            else
            {
                printf("\nEntered phone no. not found.\n\n");
            }
            break;
        case 3:
            printf("\nEnter the email : ");
            scanf(" %49[^\n]", email);
            for(i = 0; i < addressBook->contactCount; i++)
            {
                if(!(strcmp(addressBook->contacts[i].email, email)))
                {
                    found = 1;
                    break;
                }
            }
            if(found)
            {
                printf("\nContact found.\n");
                printf("\nS.No.\t   Name\t\t Phone no.\t    Email\n");
                printf("-----------------------------------------------------------\n");
                printf("%d \t %s \t %s \t %s\n", i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("\nEnter details to edit contact.\n");
                while(1)
                {
                    printf("Enter the Name : ");
                    scanf(" %49[^\n]", name);

                    printf("Enter the Phone : ");
                    scanf(" %19[^\n]", phone);
                    
                    printf("Enter the Email : ");
                    scanf(" %49[^\n]", email);
                    
                    flag = validate(i, name, phone, email, addressBook);

                    if(flag)
                    {
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
                strcpy(addressBook->contacts[i].name, name);
                strcpy(addressBook->contacts[i].phone, phone);
                strcpy(addressBook->contacts[i].email, email);
                printf("Here is the updated contact list.\n");
                listContacts(addressBook);
            }
            else
            {
                printf("\nEntered email not found.\n\n");
            }
            break;
        default:
            printf("\nEntered option is invalid.\n\n");
    }
}

//function to delete contact in the address book
void deleteContact(AddressBook *addressBook) 
{
    printf("\n------------Deleting a contact from the Address book------------\n");
    int option = 0;
    printf("\nsearching the Address book for a contact to delete\n\n");
    printf("1. Name\n2. Phone no.\n3. Email\n");               //options by which user want to search the contact to delete
    printf("Enter the option by which you want to search : ");

    if(scanf("%d", &option) == 0)
    {
        __fpurge(stdin);
    }

    int i, j, found = 0;
    char name[50], phone[20], email[50];
    switch(option)
    {
        case 1:
            printf("\nEnter the name : ");
            scanf(" %49[^\n]", name);
            for(i = 0; i < addressBook->contactCount; i++)
            {
                if(!(strcmp(addressBook->contacts[i].name, name)))            //strcmp to compare the exact input values to delete
                {
                    found = 1;
                    break;
                }
            }
            if(found)
            {
                for(j = i; j < addressBook->contactCount-1; j++)
                {
                    addressBook->contacts[j] = addressBook->contacts[j+1];    //swaping contacts from found index to contact count
                }
                (addressBook->contactCount)--;                                //decrementing contact count after deleting
                printf("\nContact has been deleted from the address book successfully!\n");
                listContacts(addressBook);
            }
            else
            {
                printf("\nEntered name not found.\n\n");
            }
            break;
        case 2:
            printf("\nEnter the phone no. : ");
            scanf(" %19[^\n]", phone);
            for(i = 0; i < addressBook->contactCount; i++)
            {
                if(!(strcmp(addressBook->contacts[i].phone, phone)))
                {
                    found = 1;
                    break;
                }
            }
            if(found)
            {
                for(j = i; j < addressBook->contactCount-1; j++)
                {
                    addressBook->contacts[j] = addressBook->contacts[j+1];
                }
                (addressBook->contactCount)--;
                printf("\nContact has been deleted from the address book successfully!\n\n");
                listContacts(addressBook);
            }
            else
            {
                printf("\nEntered phone no. not found.\n\n");
            }
            break;
        case 3:
            printf("\nEnter the email : ");
            scanf(" %49[^\n]", email);
            for(i = 0; i < addressBook->contactCount; i++)
            {
                if(!(strcmp(addressBook->contacts[i].email, email)))
                {
                    found = 1;
                    break;
                }
            }
            if(found)
            {
                for(j = i; j < addressBook->contactCount-1; j++)
                {
                    addressBook->contacts[j] = addressBook->contacts[j+1];
                }
                (addressBook->contactCount)--;
                printf("\nContact has been deleted from the address book successfully!\n\n");
                listContacts(addressBook);
            }
            else
            {
                printf("\nEntered email not found.\n\n");
            }
            break;
        default:
            printf("\nEntered option is invalid.\n\n");
    }
}

//function to save contacts present in address book
void saveContacts(AddressBook *addressBook)
{
    FILE *fptr = fopen("contact.txt", "w");
    if(fptr == NULL)
    {
        printf("\nError in opening file.\n\n");
    }
    else
    {
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            fprintf(fptr, "%s,", addressBook->contacts[i].name);
            fprintf(fptr, "%s,", addressBook->contacts[i].phone);
            fprintf(fptr, "%s\n", addressBook->contacts[i].email);
        }
    }
    fclose(fptr);
    printf("\nAddress book contacts have been saved successfully.\n\n");
}