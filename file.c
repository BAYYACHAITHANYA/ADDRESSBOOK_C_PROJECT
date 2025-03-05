#include <stdio.h>
#include "file.h"
#include "contact.h"

void saveContactsToFile(AddressBook *addressBook) {
	FILE * fp;
	fp = fopen("add.csv", "w");
	//Validating file
        if (fp == NULL)
	{
		perror("ERROR : ");//It will print Error with reason
		return;
	}
	fprintf(fp, "%d\n", addressBook -> contactCount);
	//Storing all contacts to add.csv file
	for (int i = 0; i < addressBook -> contactCount; i++)
	{
		fprintf(fp, "%s", addressBook -> contacts[i].name);
		fprintf(fp, ",");
		fprintf(fp, "%s", addressBook -> contacts[i].phone);
		fprintf(fp,  ",");
		fprintf(fp, "%s\n", addressBook -> contacts[i].email);

	}
	fclose(fp);
  
}

void loadContactsFromFile(AddressBook *addressBook) {

	FILE *fp;
	fp = fopen("add.csv", "r");
	//Validating file
	if (fp == NULL)
	{
		perror("ERROR : ");//It will print Error with reason
		return;
	}
	fscanf(fp, "%d\n",&(addressBook -> contactCount));
	//Feteching contacts from add.csv file
	for (int i = 0; i < addressBook -> contactCount; i++)
	{
		fscanf(fp, "%[^,],",addressBook -> contacts[i].name);
		fscanf(fp, "%[^,],",addressBook -> contacts[i].phone);
	        fscanf(fp, "%[^\n]\n",addressBook -> contacts[i].email);	
	}
	fclose(fp);
}
