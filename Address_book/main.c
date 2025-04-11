/*
Name: Niharika
Description: Address book project
*/


#include<stdio.h>
#include<stdio_ext.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

// Color definitions for output messages
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"

// Structure to store contact details
struct data
{
	char name[20];
	char mobile[12];
	char email[30];
	char address[50];
};

// Function prototypes
void add_contacts();
void search_contacts();
void print_contacts();
void edit_contacts();
void delete_contacts();
void copy(FILE*, FILE*);

// Validation function prototypes
int name_validation(char *);
int mobile_validation(char *);
int email_validation(char *);
int count_name(char *);
int count_email(char *);

int main()
{
	char ch='y'; // Continue loop control
	int choice=0;

	// Loop until the user chooses to exit
	while(ch=='y'||ch=='Y')
	{
label1:
        // Display menu
		printf("1. Add details\n2. Search details\n3. Print details\n4. Edit details\n5. Delete details\nEnter your choice:");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				add_contacts();
				break;
			case 2:
				search_contacts();
				break;
			case 3:
				print_contacts();
				break;
			case 4:
				edit_contacts();
				break;
			case 5:
				delete_contacts();
				break;
			default:
				printf(RED "Please enter correct option" RESET);
		}
__fpurge(stdin);// Clear input buffer

		printf(YELLOW "Do you want to continue? (y/n):" RESET);
		scanf(" %c", &ch);
// Clear the console for a fresh display
system("clear");
	}
}

// Function to add a contact
void add_contacts()
{
struct data contacts;// Contact structure
int count=0;
// Open files to read current contacts and store updated list
FILE *fdata = fopen("data.csv", "r");
FILE *ftemp = fopen("temp.csv", "w");
// Check if files opened successfully
if (fdata == NULL || ftemp == NULL)
{
	printf("File not opened!");
	return;
}

fscanf(fdata, "%d\n", &count);// Read the current count of contacts
fprintf(ftemp, "%d\n", (count+1));// Increment the count and write to temp file

// Copy existing contacts from fdata to ftemp
for(int i=0; i<count; i++)
{
	fscanf(fdata, "%[^,],%[^,],%[^,],%[^\n]\n", contacts.name, contacts.mobile, contacts.email, contacts.address);
	fprintf(ftemp, "%s,%s,%s,%s\n", contacts.name, contacts.mobile, contacts.email, contacts.address);
}

// Input and validate new contact details
printf("Enter the Name:");
label1:
scanf(" %[^\n]", contacts.name);

if(name_validation(contacts.name))
	goto label1;

printf("Enter the Mobile number:");
label2:
scanf(" %[^\n]", contacts.mobile);

if(mobile_validation(contacts.mobile))
	goto label2;

printf("Enter the Email ID:");
label3:
scanf(" %[^\n]", contacts.email);
if(email_validation(contacts.email))
	goto label3;

if(count_email(contacts.email))
	goto label3;

printf("Enter the Address:");
scanf(" %[^\n]", contacts.address);
fprintf(ftemp, "%s,%s,%s,%s\n", contacts.name, contacts.mobile, contacts.email, contacts.address);// Write the new contact to the temp file

fclose(fdata);
fclose(ftemp);

// Update the main file with new contact
fdata = fopen("data.csv", "w");
ftemp = fopen("temp.csv", "r");

// Copy updated data from temp file to main file
copy(fdata, ftemp);

fclose(fdata);
fclose(ftemp);
system("clear");
printf(GREEN "Data added successfully!\n" RESET);
return;
}

// Function to copy data from one file to another
void copy(FILE *fdata, FILE *ftemp)
{
	char ch;
	// Read from temp file and write to the main file
	while((ch=fgetc(ftemp)) != EOF)
	{
		fputc(ch, fdata);
	}
}

// Function to search contacts by name
void search_contacts()
{
	char name[30];

	printf("Please enter the name for details:");
label0:
	scanf(" %[^\n]", name);

        if(name_validation(name))
	goto label0;

	int ret=count_name(name);

	if(ret==0)
	{
		printf(RED "SORRY!!! %s data not found!\n" RESET, name);
		return;
	}
	else if(ret==1)
	{
		struct data contacts;
		
		FILE *fdata = fopen("data.csv", "r");
		int count;

		fscanf(fdata, "%d\n", &count);

		for(int i=0; i<count; i++)
		{
			fscanf(fdata, "%[^,],%[^,],%[^,],%[^\n]\n", contacts.name, contacts.mobile, contacts.email, contacts.address);
			if((strcmp(contacts.name, name) == 0))
			{

system("clear");
				printf("Name: %s\nMobile number: %s\nEmail ID: %s\nAddress: %s\n", contacts.name, contacts.mobile, contacts.email, contacts.address);
			}
		}
		fclose(fdata);
		return;
	}
	else
	{
		printf(RED "There are multiple names!\n" RESET);
		char mobile[12];
		printf(RED "Please enter the mobile number for confirmation: " RESET);
label1:
	        scanf(" %[^\n]", mobile);

		if(1)
		{
			if(strlen(mobile) != 10)
			{
				printf(RED "Please enter 10 digit number!\n" RESET);
				goto label1;
			}
		
		int i=0;
		while(mobile[i])
		{

			if(isdigit(mobile[i]))
			{
				i++;
			}
			else
			{
				printf(RED "Please enter only digits!!!\n" RESET);
				goto label1;
			}
		}
	}
        
	struct data contacts;
	int count=0, flag=1;
        FILE *fdata = fopen("data.csv", "r");
	
	fscanf(fdata, "%d\n", &count);
	for(int i=0; i<count; i++)
	{
		fscanf(fdata, "%[^,],%[^,],%[^,],%[^\n]\n", contacts.name, contacts.mobile, contacts.email, contacts.address);
		if((strcmp(contacts.name, name)==0) && (strcmp(contacts.mobile, mobile)==0))
		{
			flag=0;
			printf(GREEN "Here is the details you searched for!\n" RESET "Name: %s\nMobile number: %s\nEmail ID: %s\nAddress: %s\n", contacts.name, contacts.mobile, contacts.email, contacts.address);
		  
		}
	}

	fclose(fdata);

	if(flag)
	{
		printf(RED "SORRY!!! %s with %s details not found!\n" RESET, name, mobile);
		return;
	}
}

		
}

// Function to print all contacts
void print_contacts()
{

system("clear");
	struct data contacts;
	FILE *fdata = fopen("data.csv", "r");
	if (fdata == NULL)
	{
	printf(RED "File not opened!" RESET);
	return;
	}
	int count;
	fscanf(fdata, "%d\n", &count);

	for(int i=0; i<count; i++)
	{
	fscanf(fdata, "%[^,],%[^,],%[^,],%[^\n]\n", contacts.name, contacts.mobile, contacts.email, contacts.address);
	printf("Name: %s\nMobile number: %s\nEmail ID: %s\nAddress: %s\n", contacts.name, contacts.mobile, contacts.email, contacts.address);
	}
	fclose(fdata);
}

// Function to edit contact details
void edit_contacts()
{

struct data contacts;

char name[30];
char mobile[12];
char email[30];
char address[30];

int choice;
	printf("Please enter the name that you want to edit:");
label0:
	scanf(" %[^\n]", name);

        if(name_validation(name))
	goto label0;

	int ret=count_name(name);

	if(ret==0)
	{
system("clear");
		printf(RED "SORRY!!! %s data not found!\n" RESET, name);
		return;
	}
	else if(ret==1)
	{
		FILE *fdata = fopen("data.csv", "r");
		FILE *ftemp = fopen("temp.csv", "w");
		
		if (fdata == NULL || ftemp == NULL)
		{
			printf(RED "File not opened!" RESET);
			return;
		}

int count;
fscanf(fdata, "%d\n", &count);
fprintf(ftemp, "%d\n", count);

	for(int i=0; i<count; i++)
	{
		fscanf(fdata, "%[^,],%[^,],%[^,],%[^\n]\n", contacts.name, contacts.mobile, contacts.email, contacts.address);
		
		if(strcmp(contacts.name, name)==0)
		{
system("clear");
			printf(GREEN "Here is the details you searched for!!!\n"RESET"Name: %s\nMobile number: %s\nEmail ID: %s\nAddress: %s\n", contacts.name, contacts.mobile, contacts.email, contacts.address);
label:
		printf("1. Name\n");
		printf("2. Mobile number\n");
		printf("3. Email ID\n");
		printf("4. Address\n");
		printf("Choose what you want to edit: ");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("Enter new name:");
label1:
				scanf(" %[^\n]", name);
				if(name_validation(name))
				goto label1;
			
				strcpy(contacts.name, name);
				break;

			case 2:
				printf("Enter new mobile number:");
label2:
				scanf(" %[^\n]", mobile);
				if(mobile_validation(mobile))
			        goto label2;
				
				strcpy(contacts.mobile, mobile);
				break;

			case 3:
				printf("Enter new email id:");
label3:
				scanf(" %[^\n]", email);
				if(email_validation(email))
				goto label3;
				
				strcpy(contacts.email, email);
				break;

			case 4:
				printf("Enter new Address:");
				scanf(" %[^\n]", address);
				strcpy(contacts.address, address);
				break;
			default:
				printf(RED "Please enter the correct option\n" RESET);
__fpurge(stdin);
				goto label;
		}
		}

	fprintf(ftemp, "%s,%s,%s,%s\n", contacts.name, contacts.mobile, contacts.email, contacts.address);
}

	fclose(fdata);
	fclose(ftemp);

	fdata = fopen("data.csv", "w");
	ftemp = fopen("temp.csv", "r");
	
	copy(fdata, ftemp);
	
	fclose(fdata);
	fclose(ftemp);
system("clear");
	printf(GREEN "Data edited successfully!\n" RESET);
	return;
}
else
{
	printf(RED "There are multiple names!\nPlease enter the mobile number for confirmation: " RESET);
label4:
	        scanf(" %[^\n]", mobile);

		if(1)
		{
			if(strlen(mobile) != 10)
			{
				printf(RED "Please enter 10 digit number!\n" RESET);
				goto label4;
			}
		
		
		int i=0;
		while(mobile[i])
		{

			if(isdigit(mobile[i]))
			{
				i++;
			}
			else
			{
				printf(RED "Please enter only digits!!!\n" RESET);
				goto label4;
			}
		}
		
		FILE *fdata = fopen("data.csv", "r");
		FILE *ftemp = fopen("temp.csv", "w");
		
		if (fdata == NULL || ftemp == NULL)
		{
			printf(RED "File not opened!" RESET);
			return;
		}
int count;
fscanf(fdata, "%d\n", &count);
fprintf(ftemp, "%d\n", count);

int flag=0;
	for(int i=0; i<count; i++)
	{
		fscanf(fdata, "%[^,],%[^,],%[^,],%[^\n]\n", contacts.name, contacts.mobile, contacts.email, contacts.address);
		
		if(strcmp(contacts.name, name)==0 && strcmp(contacts.mobile, mobile))
		{
system("clear");
			flag=1;
			printf(GREEN "Here is the details you searched for!\n" RESET "Name: %s\nMobile number: %s\nEmail ID: %s\nAddress: %s\n", contacts.name, contacts.mobile, contacts.email, contacts.address);
label5:
		printf("1. Name\n");
		printf("2. Mobile number\n");
		printf("3. Email ID\n");
		printf("4. Address\n");
		printf("Choose what you want to edit: ");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("Enter new name:");
label6:
				scanf(" %[^\n]", name);
				if(name_validation(name))
				goto label6;
			
				strcpy(contacts.name, name);
				break;

			case 2:
				printf("Enter new mobile number:");
label7:
				scanf(" %[^\n]", mobile);
				if(mobile_validation(mobile))
			        goto label7;
				
				strcpy(contacts.mobile, mobile);
				break;

			case 3:
				printf("Enter new email id:");
label8:
				scanf(" %[^\n]", email);
				if(email_validation(email))
				goto label8;
				
				strcpy(contacts.email, email);
				break;

			case 4:
				printf("Enter new Address:");
				scanf(" %[^\n]", address);
				strcpy(contacts.address, address);
				break;
			default:
				printf(RED "Please enter the correct option\n" RESET);
__fpurge(stdin);
				goto label5;
		}
		}

	fprintf(ftemp, "%s,%s,%s,%s\n", contacts.name, contacts.mobile, contacts.email, contacts.address);
}

	fclose(fdata);
	fclose(ftemp);

	fdata = fopen("data.csv", "w");
	ftemp = fopen("temp.csv", "r");
	
	copy(fdata, ftemp);
	
	fclose(fdata);
	fclose(ftemp);

system("clear");
	if(flag)
	printf(GREEN "Data edited successfully!\n" RESET);
	else
	printf(RED "SORRY!!! Data not found!\n" RESET);
	return;
	}
}
}

// Function to delete contact 
void delete_contacts()
{
	int count;
	char name[30];

	printf("Please enter the name that you want to delete:");
label1:
	scanf(" %[^\n]", name);

        if(name_validation(name))
	goto label1;

	int ret=count_name(name);

	if(ret==0)
	{
		printf(RED "SORRY!!! %s data not found!\n" RESET, name);
		return;
	}
	else if(ret==1)
	{
		struct data contacts;

		FILE *fdata = fopen("data.csv", "r");
		FILE *ftemp = fopen("temp.csv", "w");
		

fscanf(fdata, "%d\n", &count);
fprintf(ftemp, "%d\n", count-1);

	for(int i=0; i<count; i++)
	{
		fscanf(fdata, "%[^,],%[^,],%[^,],%[^\n]\n", contacts.name, contacts.mobile, contacts.email, contacts.address);
		
		if(strcmp(contacts.name, name)==0)
		{
			continue;
		}
		fprintf(ftemp, "%s,%s,%s,%s\n", contacts.name, contacts.mobile, contacts.email, contacts.address);
	}
	
	fclose(fdata);
	fclose(ftemp);
	
	fdata = fopen("data.csv", "w");
	ftemp = fopen("temp.csv", "r");
	
	copy(fdata, ftemp);
	
	fclose(fdata);
	fclose(ftemp);

system("clear");
	printf(GREEN "Data deleted successfully!\n" RESET);
}
else
{
	printf(RED "There are multiple names!\nPlease enter the mobile number for confirmation: " RESET);
char mobile[12];
label11:
	        scanf(" %[^\n]", mobile);

		if(1)
		{
			if(strlen(mobile) != 10)
			{
				printf(RED "Please enter 10 digit number!\n" RESET);
				goto label11;
			}
		
		
		int i=0;
		while(mobile[i])
		{

			if(isdigit(mobile[i]))
			{
				i++;
			}
			else
			{
				printf(RED "Please enter only digits!!!\n" RESET);
				goto label11;
			}
		}
		}

		struct data contacts;

		FILE *fdata = fopen("data.csv", "r");
		FILE *ftemp = fopen("temp.csv", "w");
		

fscanf(fdata, "%d\n", &count);
fprintf(ftemp, "%d\n", count-1);

int flag=0;
	for(int i=0; i<count; i++)
	{
		fscanf(fdata, "%[^,],%[^,],%[^,],%[^\n]\n", contacts.name, contacts.mobile, contacts.email, contacts.address);
		
		if((strcmp(contacts.name, name)==0) && strcmp(contacts.mobile, mobile)==0)
		{
			flag=1;
			continue;
		}
		fprintf(ftemp, "%s,%s,%s,%s\n", contacts.name, contacts.mobile, contacts.email, contacts.address);
	}
	
	fclose(fdata);
	fclose(ftemp);
	
	fdata = fopen("data.csv", "w");
	ftemp = fopen("temp.csv", "r");
	
	copy(fdata, ftemp);
	
	fclose(fdata);
	fclose(ftemp);
system("clear");
	
	if(flag)
		printf(GREEN "%s with %s data deleted successfully!\n" RESET, name, mobile);
	else
		printf(RED "SORRY!!! %s with %s data not found!\n" RESET, name, mobile);
}
}
	
// Function for name validation
int name_validation(char *name)
{
	int i=0;
	while(name[i])
	{
		if(isalpha(name[i]) || name[i] == ' ')
		{
			i++;
		}
		else
		{
			printf(RED "Please enter only alphabet characters!!!\n" RESET);
			return 1;
		}
	}
	return 0;
}

// Function for mobile number validation
int mobile_validation(char *mobile)
{
	int i=0;
        while(mobile[i])
	{
		if(isdigit(mobile[i]))
		{
			i++;
		}
		else
		{
			printf(RED "Please enter only digits!!!\n" RESET);
			return 1;
		}

	}
	if(strlen(mobile) != 10)
	{
		printf(RED "Please enter 10 digit number!\n" RESET);
		return 1;
	}

	struct data contacts;
	int count=0;
        FILE *fdata = fopen("data.csv", "r");
	
        if (fdata == NULL)
	{
	printf(RED "File not opened!" RESET);
	return 0;
	}

	fscanf(fdata, "%d\n", &count);
	for(int i=0; i<count; i++)
	{
		fscanf(fdata, "%[^,],%[^,],%[^,],%[^\n]\n", contacts.name, contacts.mobile, contacts.email, contacts.address);
		if(strcmp(contacts.mobile, mobile)==0)
		{
			printf(RED "This mobile number already exists! Please enter other mobile number\n" RESET);
		        return 1;
		}
	}

	fclose(fdata);
	return 0;
}

// Function for email validation
int email_validation(char *email)
{
int i=0, at_found=0;

	char *temp;
	if(temp=strstr(email, "@gmail.com"))
	{
		if(temp == NULL || temp[10] != '\0')
		{
			printf(RED "Please enter the email that ends with \"@gmail.com\": " RESET);
                        return 1;
                }
while(email[i] != '\0')
{
if(email[i]==' ')
        {
		printf(RED "Please enter a correct email ID without spaces.\n" RESET);
		return 1;
	}
if(email[i]=='@')
{
     if(at_found)
{
printf(RED "Invalid email! multiple '@' found.\n" RESET);
return 1;
}
at_found = 1;
}
i++;
}
}
if(!at_found)
{
printf(RED "Inavlid email! missing '@'.\n" RESET);
return 1;
}
return 0;
}

int count_name(char *name)
{
	struct data contacts;

	FILE *fdata = fopen("data.csv", "r");		
	
	int count=0;
	fscanf(fdata, "%d\n", &count);
	
	int flag=0;
	for(int i=0; i<count; i++)
	{
		fscanf(fdata, "%[^,],%[^,],%[^,],%[^\n]\n", contacts.name, contacts.mobile, contacts.email, contacts.address);
		if(strcmp(contacts.name, name)==0)
		flag++;
	}
	fclose(fdata);
	return flag;
}

int count_email(char *email)
{
	struct data contacts;

	FILE *fdata = fopen("data.csv", "r");		
	
	int count=0;
	fscanf(fdata, "%d\n", &count);
	
	for(int i=0; i<count; i++)
	{
		fscanf(fdata, "%[^,],%[^,],%[^,],%[^\n]\n", contacts.name, contacts.mobile, contacts.email, contacts.address);
		if(strcmp(contacts.email, email)==0)
		{
			printf(RED "Already email found!\nPlease enter other email id\n" RESET);
			return 1;
		}
	}
	fclose(fdata);
	return 0;
}
