#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    int i ;
    printf(" Name                Contact             Eamil\n");
   for (i = 0; i < addressBook -> contactCount; i++)
   {   
    printf(" %-20s%-20s%-20s", addressBook -> contacts[i].name, addressBook ->contacts[i].phone, addressBook -> contacts[i].email);
    printf("\n");
   }
}
//Name validation function definition
void name_validation(char name[], int *n)
{
	int i ;
	for (i = 0; i < strlen(name); i++)
	{
		//Checking wheather name has only characters
		if (name[i] >= 'A' && name[i] <= 'Z' || name[i] >= 'a' && name[i] <= 'z' || name[i] == ' ' )
		{
			return;
		}
		else
		{
			*n = 1;
			printf("Enterd name is not a character please try again");
			return;
		}
	}	
	
}
//Number validation function definition
void number_validation(char * ptr1, AddressBook *addressBook, int * res)
{
    
    int  num_exist = 0;
    int mobile_len = strlen(ptr1);
    //Checking enterd mobile number has equals to 10 digits or not
    if(mobile_len == 10)
    {
        int mobile_flag = 0;
        for(int i = 0; i < mobile_len; i++)
        {
	//Checking the number contains only digits or not
            if(ptr1[i] >= '0' && ptr1[i] <= '9')
            continue;
            else
            {
               mobile_flag = 1;
               *res = 1;
               printf("You entered invalid mobile numer");
               return;
            }
        }
        if(mobile_flag == 0)
        {
            //Comparing enterd number is alerady exist in contacts list 
            for(int j = 0; j<addressBook -> contactCount; j++)
            {
                if(strcmp(addressBook->contacts[j].phone,ptr1) == 0)
                {
                    num_exist = 1;
                    *res = 1;
                    printf("Entered number is already existed");
                    return;
                }
                 else
                 continue;
            }
        }

    }
    else
    {
        *res = 1;
        printf("You entered is  insufficient mobile number ");
        return;
    } 
}
//Mail validation function definition
void mail_validation(char*ptr2, AddressBook *addressBook, int * res)
{
    char ch = '@';
    int mail_exist, ch_count = 0;
    int mail_len = strlen(ptr2);
    //Checking Enterd mail id has @ or not
    for(int i = 1; i < mail_len; i++)
    {
        if(ptr2[i] == ch)
        {
            ch_count++;
            break;
        }
    }
    char sub_mail[10] = ".com";
    if( ch_count == 1)
    {
        int m = 0;
        int mail_flag = 0;
        for(int j = (mail_len - 4);j < mail_len; j++)
        {
		//Checking last 4 characters of entered mail id has .com or not
            if(sub_mail[m] == ptr2[j])
            {
                mail_flag++;
                m++;
            }
        }
        if(mail_flag == 4)
        {
            for(int k = 0; k < addressBook -> contactCount; k++)
            {
		    //Comparing if the enterd mail id is already exist in  contacts list 
                if(strcmp(addressBook->contacts[k].email,ptr2) == 0)
                {
                    mail_exist = 1;
                    *res = 1;
                    printf("Entered mail is already existed");
                    return;
                }
                 else
                 continue;
            }
            *res = 0;
        }
        else
        {
            *res = 1;
            printf("You entered insufficient email\n");
            return;
        }
    }
    else
    {
        *res = 1;
        printf("You entered invalid mail ID");
    }
}
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
  //  populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char Name[20];
    char mobile_num[20];
    char mail[30];
    printf("Enter the contact name : ");
    scanf(" %[^\n]", Name);
    getchar();
    int name_exist = 0;
    //Calling Function
    name_validation(Name, &name_exist);
    //if any conidtion is false in name validation excute if or go to else
    if (name_exist == 1)
    return;
    else
    {

	//Copying enterd name to contact list
	 strcpy(addressBook -> contacts[addressBook -> contactCount].name, Name);
         printf("Name added successfully\n");	 
    }
    printf("Enter the mobile number : ");
    scanf("%s", mobile_num);
    getchar();
    int num_exist = 0;
    //Calling function
    number_validation(mobile_num, addressBook, &num_exist);
    //if any conidtion is false in  number validation, excute if or go to else
    if(num_exist == 1)
    return;
    else
    {
	 //Copying enterd mobile number to contact list   
         strcpy(addressBook -> contacts[addressBook -> contactCount].phone, mobile_num);
         printf("Mobile number is added successfully\n");
    }
    printf("Enter the Email ID : ");
    scanf("%s", mail);
    getchar();
    int mail_exists = 0;
    //Calling function
    mail_validation(mail, addressBook, &mail_exists);
    //if any conidtion is false in mail validation excute if or go to else
    if(mail_exists == 1)
    return;
    else
    {
	//Copying enterd Mail ID to contacts    
        strcpy(addressBook -> contacts[addressBook -> contactCount].email, mail);
        addressBook->contactCount++;
        printf("Email updated successfully");
    }
    
}
void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
	int option;
	char search[20];
	printf("Select your choice : 1.name \n 2.phone\n 3.Email ID\n");
	printf("Enter your choice: ");
	scanf("%d", &option);
	getchar();
	switch(option)
	{ 
		case 1:
		printf("Enter the name :");
		scanf(" %[^\n]", search);
		getchar();
	        int search_count = 0;
	        int search_arr[200];
	        int n = 0;
	        for (int i = 0; i < addressBook -> contactCount; i++)
          	{
			//Comparing entered name with contacts names
			//if found print the founded contacts
		       if (strcmp(addressBook -> contacts[i].name, search) ==0)
		       { 
			       search_count++;
			       //Storing index postions of contacts
			       search_arr[n++] = i;
			       printf("%d. name : %s\n",i, addressBook -> contacts[i].name);
			       printf("    mobile number :%s\n",addressBook -> contacts[i].phone);
			       printf("    Email ID : %s\n",addressBook -> contacts[i].email);
			       printf("\n");
		       }
		       else
			continue;       
		}
		//if conatcts found more than 1 it will enter into this block
		if (search_count > 1)
		{
			int name_search1;
			int flag = 0;
			printf("Enter the index number which  contact you want to search : ");
		       scanf("%d", &name_search1);
		       getchar();
		       for (int h = 0; h < addressBook -> contactCount; h++)
		       {
			       //Comparing entered index position with stored index position
			       if (name_search1 == search_arr[h])
			       {
				       flag = 1;
				       break;
			       }
		       }
		
		if (flag == 0)
		{
			//printing contacts if you entered invalid index
			printf("you entered invalid index number\n");
			printf("%d .name : %s\n",name_search1, addressBook -> contacts[name_search1].name);
			printf("   Mobile number :%s\n",addressBook -> contacts[name_search1].phone);
			printf("   Email ID : %s\n",addressBook -> contacts[name_search1].email);
		}
		if (flag)
		{
			//printing entered index position contact
			 printf("%d .name : %s\n",name_search1, addressBook -> contacts[name_search1].name);
			 printf("   Mobile number :%s\n",addressBook -> contacts[name_search1].phone);
			 printf("   Email ID : %s\n",addressBook -> contacts[name_search1].email);
		}
		}
		break;
	       	       
		case 2:
		printf("Enter the Mobile Number: ");
		scanf("%s", search);
		getchar();
		int j, search_count2 = 0;
		for (j = 0; j < addressBook -> contactCount; j++)
		{
			//Comparing entered mobile number with contacts list 
			if(strcmp(addressBook -> contacts[j].phone, search) == 0)
			{
				search_count2++;
				break;
			}
		}
		if (search_count2 == 1)
		{
			//printing name,phone number and email id if found
			 printf("%d. name : %s\n",j, addressBook -> contacts[j].name);
			 printf("    mobile number :%s\n",addressBook -> contacts[j].phone);
			 printf("    Email ID : %s\n",addressBook -> contacts[j].email);
		}
		else
		{
			printf("Your entered number is not in the contact list please try with another number");
			return;
		}
		break;

		case 3:
		printf("Enter the Email Id : ");
		scanf("%s", search);
		getchar();
		int i, search_count1 = 0;
		for ( i = 0; i < addressBook -> contactCount; i++)
		{
			//Comparing entered mail id with contacts list
			if (strcmp(addressBook -> contacts[i].email,search) ==0)
			{
				search_count1++;
				break;
			}
		}
		if (search_count1 == 1)
		{
			//printing name,phone number and mail id if found
			 printf("%d. name : %s\n",i, addressBook -> contacts[i].name);
			 printf("    mobile number :%s\n",addressBook -> contacts[i].phone);
			 printf("    Email ID : %s\n",addressBook -> contacts[i].email);
		}
		else
		{
			printf("Your entered Email Id is not in the contact list please try with another Email ID");
			return;
		}
		break;

		default:
		printf("You entered invalid option please try again");
	}

}
void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    char edit[30];
    char new_name[30];
    char new_num[30];
    char new_mail[30];
    printf("Select Your choice : 1. name\n 2. phone\n 3. Email ID\n ");
    int option;
    scanf("%d", &option);
    getchar();
    int i, index = -1, found_count = 0;
    switch (option) 
    {
        case 1:
            printf("Enter the name: ");
            scanf(" %[^\n]", edit);
            getchar();
            int edit_arr[200];
            int n = 0;
            for (i = 0; i < addressBook->contactCount; i++) 
            {
		//Comparing Entered name with contacts list
		//if found print name,phone number and mail id    
                if (strcmp(addressBook->contacts[i].name, edit) == 0) 
                {
			//Storing index postions
                    edit_arr[n++] = i;
                    printf("%d. Name: %s\n", i, addressBook->contacts[i].name);
                    printf("    Mobile Number: %s\n", addressBook->contacts[i].phone);
                    printf("    Email ID: %s\n", addressBook->contacts[i].email);
                    found_count++;
                    index = i;
                }
            }
             int flag1 = 0;
            if (found_count == 0) 
            {
                printf("Name not found! Please try again.\n");
                return;
            } 
	    //If contacts are more than 1  it will enter into this block
            else if (found_count > 1) 
            {
                printf("Enter the index of the contact you want to edit: ");
                scanf("%d", &index);
                getchar();
                if(index >= 0 && index < addressBook->contactCount)
                {
                    for(int h = 0; h < addressBook -> contactCount; h++)
                    {
			//Comparing entered index with stored index     
                        if(index == edit_arr[h])
                        {
                            flag1 = 1;
                            break;
                        }
                    }
                    if(flag1 == 0)
                    {
                        printf("You entered invalid choice! please try again");
                        return;
                    }
                }
            }
	    //if entered index is found or only found 1 contact it will enter into this block
            if(flag1 == 1 || found_count == 1)
            {
                        printf("Enter your choice for which detail you want to edit:\n 1. name\n 2. number\n 3. email\n 4. all\n");
                        int edit_opt;
                        scanf("%d", &edit_opt);
                        getchar();
                        switch (edit_opt) 
                        {
                            case 1:
                                printf("Enter the new name: ");
                                scanf(" %[^\n]", new_name);
                                getchar();
				//Copying Newly enterd name to old name
                                strcpy(addressBook->contacts[index].name, new_name);
                                printf("New name updated successfully.\n");
                            break;
                            case 2:
                                printf("Enter the new number: ");
                                scanf("%s", new_num);
                                getchar();
				//validating number with function
                                number_validation(new_num, addressBook, &edit_opt);
                                if (edit_opt == 1) 
                                return;
				//Copying newly entered phone number to old phone number
                                strcpy(addressBook->contacts[index].phone, new_num);
                                printf("New number updated successfully.\n");
                            break;
                            case 3:
                                printf("Enter the new email: ");
                                scanf("%s", new_mail);
                                getchar();
				//Validating mail id with function
                                mail_validation(new_mail, addressBook, &edit_opt);
                                if (edit_opt == 1)
                                return;
				//Copying newly entred number to old mail id
                                strcpy(addressBook->contacts[index].email, new_mail);
                                printf("New email updated successfully.\n");
                            break;
                            case 4:
                                printf("Enter the new name: ");
                                scanf(" %[^\n]", new_name);
                                getchar();
                                printf("Enter the new number: ");
                                scanf("%s", new_num);
                                getchar();
				//calling number validation function
                                number_validation(new_num, addressBook, &edit_opt);
                                if (edit_opt == 1)
                                return;
                                else
                                {
                                printf("Enter the new email: ");
                                scanf("%s", new_mail);
                                getchar();
				//calling mail validation function
                                mail_validation(new_mail, addressBook, &edit_opt);
                                if (edit_opt == 1)
                                return;
				//copying name , mobile number and mail id to contact list
                                strcpy(addressBook->contacts[index].name, new_name);
                                strcpy(addressBook->contacts[index].phone, new_num);
                                strcpy(addressBook->contacts[index].email, new_mail);
                                printf("Contact edited successfully.\n");
                                }
                        break;
                        default:
                            printf("Invalid choice! Please try again.\n");
                            return;
                        }
                    //}
            }
            //}
        break;

        case 2:
            printf("Enter the number: ");
            scanf("%s", edit);
            getchar();

            for (i = 0; i < addressBook->contactCount; i++) 
            {
		//comparing entred phone number with contacts    
                if (strcmp(addressBook->contacts[i].phone, edit) == 0) 
                {
                    found_count++;
                    index = i;
                }
            }

            if (found_count == 0) 
            {
                printf("Number not found! Please try again.\n");
                return;

            }
            else if (found_count > 1) 
            {
                printf("Enter the index of the contact you want to edit: ");
                scanf("%d", &index);
                getchar();
            }
            //Checking entered index value is greatherthan 0 and lessthan conatactcount
            if (index >= 0 && index < addressBook->contactCount) 
            {
                printf("Enter your choice for which detail you want to edit:\n 1. name\n 2. number\n 3. email\n 4. all\n");
                int edit_opt;
                scanf("%d", &edit_opt);
                getchar();
                switch (edit_opt) 
                {
                    case 1:
                        printf("Enter the new name: ");
                        scanf(" %[^\n]", new_name);
                        getchar();
			//Copying newly entered name to old name
                        strcpy(addressBook->contacts[index].name, new_name);
                        printf("New name updated successfully.\n");
                        break;
                    case 2:
                        printf("Enter the new number: ");
                        scanf("%s", new_num);
                        getchar();
			//Calling number validation function
                        number_validation(new_num, addressBook, &edit_opt);
                        if (edit_opt == 1) return;
			//Copying newly entered phone number to old number
                        strcpy(addressBook->contacts[index].phone, new_num);
                        printf("New number updated successfully.\n");
                        break;
                    case 3:
                        printf("Enter the new email: ");
                        scanf("%s", new_mail);
                        getchar();
			//Calling mail validation function
                        mail_validation(new_mail, addressBook, &edit_opt);
                        if (edit_opt == 1) return;
			//Copying newly entered mailid to old mail id
                        strcpy(addressBook->contacts[index].email, new_mail);
                        printf("New email updated successfully.\n");
                        break;
                    case 4:
                        printf("Enter the new name: ");
                        scanf(" %[^\n]", new_name);
                        getchar();
                        printf("Enter the new number: ");
                        scanf("%s", new_num);
                        getchar();
			//Calling number validation function 
                        number_validation(new_num, addressBook, &edit_opt);
                        if (edit_opt == 1) return;
                        printf("Enter the new email: ");
                        scanf("%s", new_mail);
                        getchar();
			//Calling mail validation function
                        mail_validation(new_mail, addressBook, &edit_opt);
                        if (edit_opt == 1) return;
			//Copying newly entred name, mobile number and mail id to contact list
                        strcpy(addressBook->contacts[index].name, new_name);
                        strcpy(addressBook->contacts[index].phone, new_num);
                        strcpy(addressBook->contacts[index].email, new_mail);
                        printf("Contact edited successfully.\n");
                        break;
                    default:
                        printf("Invalid choice! Please try again.\n");
                        return;
                }
            }
        break;

        case 3:
            printf("Enter the email: ");
            scanf("%s", edit);
            getchar();
            printf("Enter your choice for which detail you want to edit:\n 1. name\n 2. number\n 3. email\n 4. all\n");
            int edit_opt;
            scanf("%d", &edit_opt);
            getchar();
            switch (edit_opt) 
            {
                case 1:
                    printf("Enter the new mail: ");
                    scanf(" %[^\n]", new_name);
                    getchar();
		    //Copying newly entered name to old name
                    strcpy(addressBook->contacts[index].name, new_name);
                    printf("New name updated successfully.\n");
                break;
                case 2:
                    printf("Enter the new number: ");
                    scanf("%s", new_num);
                    getchar();
		    //Calling number validation function
                    number_validation(new_num, addressBook, &edit_opt);
                    if (edit_opt == 1) return;
		    //Copying newly entered mobile number to old mobile number
                    strcpy(addressBook->contacts[index].phone, new_num);
                    printf("New number updated successfully.\n");
                break;
                case 3:
                    printf("Enter the new email: ");
                    scanf("%s", new_mail);
                    getchar();
		    //Calling mail validation function
                    mail_validation(new_mail, addressBook, &edit_opt);
                    if (edit_opt == 1) return;
		    //Copying new mail id to old mail id
                    strcpy(addressBook->contacts[index].email, new_mail);
                    printf("New email updated successfully.\n");
                break;
                case 4:
                    printf("Enter the new name: ");
                    scanf(" %[^\n]", new_name);
                    getchar();
                    printf("Enter the new number: ");
                    scanf("%s", new_num);
                    getchar();
		    //Calling number validation function for validation
                    number_validation(new_num, addressBook, &edit_opt);
                    if (edit_opt == 1) return;
                    printf("Enter the new email: ");
                    scanf("%s", new_mail);
                    getchar();
		    //Calling mail validation function
                    mail_validation(new_mail, addressBook, &edit_opt);
                    if (edit_opt == 1) return;
		    //Copying newly entered name, phone number and mail id to contact list
                    strcpy(addressBook->contacts[index].name, new_name);
                    strcpy(addressBook->contacts[index].phone, new_num);
                    strcpy(addressBook->contacts[index].email, new_mail);
                    printf("Contact edited successfully.\n");
                break;
                default:
                    printf("Invalid choice! Please try again.\n");
                    return;
            }
        break;
        default:
            printf("You enter invalid choice! please try again");
    
    }
}
void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
         int option;
	 char delete[30];
	 printf("Options are 1.name 2.Mobile Number 3.Emaid Id\n");
	 printf("Enter your choice : ");
	 scanf("%d", &option);
	 switch (option)
	 {
		 case 1:
			 printf("Enter the name :");
			 scanf(" %[^\n]",delete);
			 int delete_count1 = 0;
			 int delete_str[200];
			 int s, n = 0;
			 for (int i = 0; i < addressBook -> contactCount; i++)
			 {
				 //Comparing Entered name with contact list
				 //if found print the contacts
				 if (strcmp(addressBook ->contacts[i].name, delete) == 0)
				 {
					 delete_count1++;
					 //Storing index positions 
					 delete_str[n++] = i;
					 printf("%d . Name :%s\n",i,addressBook -> contacts[i].name);
					 printf("     Mobile Number:%s\n",addressBook -> contacts[i].phone);
					 printf("     Emaid ID :%s\n",addressBook -> contacts[i].email);
					 printf("\n");
					 if (delete_count1 == 1)
                                        //Storing i value
					 s = i;
				 }
				 
				
			 }
			 int flag = 0;
			 if (delete_count1 > 1)
			 {
				 int index;
				 printf("Enter the index of contact you want to delete: ");
				 scanf("%d", &index);
				 for (int j = 0; j < addressBook -> contactCount; j++)
				 {
					 //Checking entered index  with stored index 
					 if (index == delete_str[j])
					 {
						 flag = 1;
						 s = index;
						 break ;
					 }
				 }
				 if (flag == 0)
				 {
					 printf("You Entered invalid index try again\n");
				 }
				 if (flag == 1 || delete_count1 == 1)
				 {

			            for (int k = s; k < addressBook -> contactCount; k++)
			            {
					//Deleting the conatct by shifiting characters to left side    
				       addressBook -> contacts[k] = addressBook -> contacts[k + 1];
			            } 
			            printf(" Contact deleted succesfully\n ");
			            break;
				 }
			 }
			 if (delete_count1 == 0)
			 {
				 printf("Contact name is not found try again\n");
			 }
			 break;
		 case 2:
			 printf("Enter the Mobile Number :");
			 scanf("%s", delete);
			 int delete_count2 = 0;
			 int m = 0;
			 for (int i = 0; i < addressBook -> contactCount; i++)
			 {
				 //Comparing entered mobile number with conatct list
				 if (strcmp(addressBook -> contacts[i].phone,delete) == 0)
				 {
					 delete_count2 = 1;
					 m = i;
					 break;
				 }
			 }
			 if (delete_count2 == 1)
			 {
				 for (int k = m; k < addressBook -> contactCount; k++)
				 {
					 //Deleting the conatct by shifiting characters to left side
					 addressBook -> contacts[k] = addressBook -> contacts[k + 1];
				 }
				 printf("Contact deleted Succesfully\n");
				 break;
			 }
			 if (delete_count2 == 0)
			 {
				 printf("You entered number is not in the contacts please try again\n");
			 }
			 break;
		 case 3:
			 printf("Enter the Email ID : ");
			 scanf("%s", delete);
			 int j = 0;
			 int delete_count3 = 0;
			 for (int i = 0; i < addressBook -> contactCount; i++)
			 {
				 //Comparing Entered mail id with contact list
				 if (strcmp(addressBook -> contacts[i].email,delete) == 0)
				 {
					 delete_count3 = 1;
					 j = i;
				 }
			 }
			 if (delete_count3 == 1)
			 {
				 for (int k = j; k < addressBook -> contactCount; k++)
				 {
					 //Deleting the conatct by shifiting characters to left side
					 addressBook -> contacts[k] = addressBook -> contacts[k + 1];
				 }
				 printf("Contact deleted successfully\n");
				 break;
			 }
			 if(delete_count3 == 0)
			 {
				 printf("You entered Email ID is not in the list please try again\n");
			 }
			 break;
		       default :
			 printf("you Entered invalid option please try again\n");
					 
	 }
   
}

