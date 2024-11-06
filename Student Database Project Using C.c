#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct student
{
	int roll;
	char name[30];
	float mark;
	struct student* next;
}ST;

//int rn=1;
int add_end(ST**,int);
void delete(ST**);
void sub_delete(ST**,int);
void sub_del(ST**,char*);
void print(ST*);
void save(ST*);
void delete_all(ST**);
void reverse(ST*);
int count(ST*);
void exit_db(ST*);
void modify(ST*);
int search(ST* ,char* );
int search_mark(ST*,float);
void sort(ST*);
void sort_per(ST*);
void sort_name(ST* );

int main()
{
	char op;
	int rn=1,urn;
	ST* hptr=0;
	do
	{
		printf("---------------------------------\n");
		printf("| **** STUDENT RECORD MENU **** |\n");
		printf("---------------------------------\n");
		printf("| a/A : Add new record          |\n");
		printf("| d/D : Delete a record         |\n");
		printf("| s/S : Show the list           |\n");
		printf("| m/M : Modify a record         |\n");
		printf("| v/V : Save                    |\n");
		printf("| e/E : Exit                    |\n");
		printf("| t/T : Sort the list           |\n");
		printf("| l/L : Delete all the record   |\n");
		printf("| r/R : Reverse the list        |\n");
		printf("|                               |\n");
		printf("|Enter your choice:             |\n");
		printf("---------------------------------\n");

		scanf(" %c",&op);
		switch(op)
		{
			case 'a':
			case 'A': urn=add_end(&hptr,rn); rn=urn;break;
			case 'd':
			case 'D': delete(&hptr);break;
			case 's':
			case 'S':print(hptr);break;
			case 'm':
			case 'M':modify(hptr);break;
			case 'v':
			case 'V':save(hptr);break;
			case 'e':
			case 'E':exit_db(hptr);break;
			case 't':
			case 'T':sort(hptr);break;
			case 'l':
			case 'L':delete_all(&hptr);break;
			case 'r':
			case 'R':if(hptr!=NULL){
				 printf("----------------------------------------\n");
				 printf("|Roll no|        Name      |  Marks    |\n");
				 printf("----------------------------------------\n");
				 reverse(hptr);
				 printf("----------------------------------------\n");break;
				 }
				 else
					 printf("No data is present\n");
				 break;

		}
	}while(1);
}










int add_end(ST** ptr,int rn)
{
	char op;
	do
	{
		ST* temp= (ST*)malloc(sizeof(ST));
		printf("Enter the name and mark of the student:\n");
		scanf("%s %f",temp->name,&temp->mark);
		temp->roll=rn++;
		if (*ptr==0)
		{
			temp->next=*ptr;
			*ptr=temp;
		}
		else
		{
			ST* last=*ptr;
			while(last->next!=0)
			{
				last=last->next;
			}
			temp->next=last->next;
			last->next=temp;
		}

		printf("Do you wish to enter another student record(Y/N):\n");
		scanf(" %c",&op);
	}while((op=='Y')||(op=='y'));
	return rn;

}










int count(ST* ptr)
{
	int c=0;
	while(ptr!=0)
	{
		c++;
		ptr=ptr->next;
	}
	return c;
}










void delete(ST**ptr)
{
	int n,i;
	char op,nme[30];
	if (*ptr==0)
	{
		printf("No Data present to delete\n");
		return;
	}
	printf("---------------------------------\n");
	printf("| R/r : Enter Roll no to delete |\n");
	printf("| N/n : Enter name to delete    |\n");
	printf("---------------------------------\n");
	scanf(" %c",&op);
	if ((op=='R')||(op=='r'))
	{
		printf("Enter the roll no to delete: \n");
		scanf("%d",&n);
		sub_delete(ptr,n);
	}
	else if((op=='N')||(op=='n'))
	{
		printf("Enter the name to delete:\n");
		scanf(" %s",nme);
		i=search(*ptr,nme);
		if (i==1)
		{
			sub_del(ptr,nme);
		}
		else if(i>0)
		{

			printf("Multiple data Available...Enter the roll no to delete: \n");
			scanf("%d",&n);
			ST *prv,*temp=*ptr;
			while(temp!=0)
			{
				if (temp->roll==n)
				{
					if (strcmp(nme,temp->name)==0)
					{
					if (*ptr==temp)
					{
						*ptr=temp->next;

					}
					else
					{
						prv->next=temp->next;
					}
					free(temp);
					temp=NULL;
					return;
					}
					else
					{
						printf("Sorry the roll no doesn't belong to the provided name\n");
						return;
					}
				}
				else
				{
					prv=temp;
					temp=temp->next;
				}
			}

			printf("Data dosen't exist to delete\n");
		}
	}
	else
	{
		printf("Enter the valid option..\n");
	}

}










void sub_delete(ST** ptr,int n)
{
	ST *prv,*temp=*ptr;
	while(temp!=0)
	{
		if (temp->roll==n)
		{
			if (*ptr==temp)
			{
				*ptr=temp->next;

			}
			else
			{
				prv->next=temp->next;
			}
			free(temp);
			temp=NULL;
			printf("Data of Roll no %d Deleted Successfully\n",n);
			return;
		}
		else
		{
			prv=temp;
			temp=temp->next;
		}
	}

	printf("Data dosen't exist to delete\n");
}










void sub_del(ST** ptr,char* nm)
{
	ST *prv,*temp=*ptr;
	while(temp!=0)
	{
		if (strcmp(temp->name,nm)==0)
		{
			if (*ptr==temp)
			{
				*ptr=temp->next;

			}
			else
			{
				prv->next=temp->next;
			}
			free(temp);
			temp=NULL;
			printf("Data of name %s Deleted Successfully\n",nm);
			return;
		}
		else
		{
			prv=temp;
			temp=temp->next;
		}
	}

	printf("Data dosen't exist to delete\n");
}











void delete_all(ST** ptr)
{
	ST*temp;
	while(*ptr!=0)
	{
		temp=*ptr;
		*ptr=temp->next;
		free(temp);
	}
	printf("The Student Record Deleted Successfully\n");
}










void exit_db(ST* ptr)
{
	char op;
	printf("----------------------------------------\n");
	printf("| S/s: Save and Exit                   |\n");
	printf("| E/e: Exit without Saving             |\n");
	printf("----------------------------------------\n");
	scanf(" %c",&op);
	if ((op=='S')||(op=='s'))
	{
		save(ptr);
		exit(0);
	}
	else if((op=='E')||(op=='e'))
	{
		exit(0);
	}
	else
	{
		printf("Enter the valid option..\n");
	}
}









void modify(ST* ptr) {
    int rn, new_roll;
    char op, name[30], opt;
    float new_per;

    if (ptr == NULL) {
        printf("No data found\n");
        return;
    }
    
    printf("-----------------------------------------------\n");
    printf("| Enter which record to search for modification|\n");
    printf("| R/r: Search a Roll no                       |\n");
    printf("| N/n: Search a name                          |\n");
    printf("| P/p: Search a percentage                    |\n");
    printf("-----------------------------------------------\n");
    scanf(" %c", &op);

    if ((op == 'R') || (op == 'r')) {
        printf("Enter the Roll no to be modified:\n");
        scanf("%d", &rn);
        printf("-----------------------------------------------\n");
        printf("| n/N: Change Name                            |\n");
        printf("| p/P: Change Percentage                       |\n");
        printf("| a/A: Change Name and Percentage             |\n");
        printf("-----------------------------------------------\n");
        scanf(" %c", &opt);

        while (ptr != NULL) {
            if (ptr->roll == rn) {
                if ((opt == 'n') || (opt == 'N')) {
                    char new_name[30];
                    printf("Enter the new name:\n");
                    scanf("%29s", new_name);
                    strncpy(ptr->name, new_name, sizeof(ptr->name));
                    return;
                } else if ((opt == 'p') || (opt == 'P')) {
                    printf("Enter the new percentage:\n");
                    scanf("%f", &new_per);
                    ptr->mark = new_per; // Assuming 'mark' is the percentage
                    return;
                } else if ((opt == 'a') || (opt == 'A')) {
                    char new_name[30];
                    printf("Enter the new name and percentage:\n");
                    scanf("%29s %f", new_name, &new_per);
                    strncpy(ptr->name, new_name, sizeof(ptr->name));
                    ptr->mark = new_per;
                    return;
                } else {
                    printf("Enter a valid option\n");
                    return;
                }
            }
            ptr = ptr->next;
        }
        printf("The Roll no doesn't exist...\n");

    } else if ((op == 'N') || (op == 'n')) {
        printf("Enter the name to be modified:\n");
        scanf("%29s", name);
        int count = search(ptr, name);
        printf("count=%d\n", count);
        printf("-----------------------------------------------\n");

        if (count == 0) {
            printf("Sorry, no data for the given name exists...\n");
            return;
        } else {
            // Display records with the found name
            ST* temp = ptr;
            while (temp != NULL) {
                if (strcmp(temp->name, name) == 0) {
                    printf("Roll No: %d, Name: %s, Marks: %.2f\n", temp->roll, temp->name, temp->mark);
                }
                temp = temp->next;
            }

            printf("Please provide the Roll no to modify:\n");
            scanf("%d", &rn);
            while (ptr != NULL) {
                if (ptr->roll == rn && strcmp(ptr->name, name) == 0) {
                    printf("-----------------------------------------------\n");
                    printf("| n/N: Change Name                            |\n");
                    printf("| p/P: Change Percentage                       |\n");
                    printf("| a/A: Change Name and Percentage             |\n");
                    printf("-----------------------------------------------\n");
                    scanf(" %c", &opt);
                    if ((opt == 'n') || (opt == 'N')) {
                        char new_name[30];
                        printf("Enter the new name:\n");
                        scanf("%29s", new_name);
                        strncpy(ptr->name, new_name, sizeof(ptr->name));
                    } else if ((opt == 'p') || (opt == 'P')) {
                        printf("Enter the new percentage:\n");
                        scanf("%f", &new_per);
                        ptr->mark = new_per; // Assuming 'mark' is the percentage
                    } else if ((opt == 'a') || (opt == 'A')) {
                        char new_name[30];
                        printf("Enter the new name and percentage:\n");
                        scanf("%29s %f", new_name, &new_per);
                        strncpy(ptr->name, new_name, sizeof(ptr->name));
                        ptr->mark = new_per;
                    }
                    return;
                }
                ptr = ptr->next;
            }
            printf("Sorry, this roll no doesn't belong to the given name.\n");
            return;
        }

    } else if ((op == 'P') || (op == 'p')) {
        printf("Enter the percentage to be modified:\n");
        scanf("%f", &new_per);
        int count = search_mark(ptr, new_per);
        if (count == 0) {
            printf("Sorry, no data for the given percentage exists.\n");
            return;
        } else {
            // Handle multiple records with the same percentage
            printf("Please provide the Roll no to modify:\n");
            scanf("%d", &rn);
            while (ptr != NULL) {
                if (ptr->roll == rn && ptr->mark == new_per) {
                    char new_name[30];
                    printf("Enter the new name and percentage:\n");
                    scanf("%29s %f", new_name, &new_per);
                    strncpy(ptr->name, new_name, sizeof(ptr->name));
                    ptr->mark = new_per;
                    return;
                }
                ptr = ptr->next;
            }
            printf("Sorry, this roll no doesn't belong to the given percentage.\n");
        }
    } else {
        printf("Enter a valid option..\n");
    }
}

/*void modify(ST* ptr) {
    int rn, new_roll, val1;
    char op, name[30], opt;
    float per;

    if (ptr == NULL) {
        printf("No data found\n");
        return;
    }
    
    printf("-----------------------------------------------\n");
    printf("|Enter which record to search for modification|\n");
    printf("| R/r: Search a Roll no                       |\n");
    printf("| N/n: Search a name                          |\n");
    printf("| P/p: Percentage Based                       |\n");
    printf("-----------------------------------------------\n");
    scanf(" %c", &op);

    if ((op == 'R') || (op == 'r')) {
        printf("Enter the Roll no to be modified:\n");
        scanf("%d", &rn);
        printf("-----------------------------------------------\n");
        printf("| n/N: Change Name                            |\n");
        printf("| r/R: Change Roll No                        |\n");
        printf("| a/A: Change Name and Roll No               |\n");
        printf("-----------------------------------------------\n");
        scanf(" %c", &opt);

        while (ptr != NULL) {
            if (ptr->roll == rn) {
                if ((opt == 'n') || (opt == 'N')) {
                    printf("Enter the new name:\n");
                    scanf("%29s", ptr->name);
                    return;
                } else if ((opt == 'r') || (opt == 'R')) {
                    printf("Enter the new roll number:\n");
                    scanf("%d", &new_roll);
                    ptr->roll = new_roll;
                    return;
                } else if ((opt == 'a') || (opt == 'A')) {
                    printf("Enter the new name and roll number:\n");
                    scanf("%29s %d", ptr->name, &new_roll);
                    ptr->roll = new_roll;
                    return;
                } else {
                    printf("Enter a valid option\n");
                    return;
                }
            }
            ptr = ptr->next;
        }
        printf("The Roll no doesn't exist...\n");

    } else if ((op == 'N') || (op == 'n')) {
        printf("Enter the name to be modified:\n");
        scanf("%29s", name);
        val1 = search(ptr, name);
        printf("count=%d\n", val1);
        printf("-----------------------------------------------\n");

        if (val1 == 0) {
            printf("Sorry, no data for the given name exists...\n");
            return;
        } else {
            printf("Records found with name '%s':\n", name);
            ST* temp = ptr;
            while (temp != NULL) {
                if (strcmp(temp->name, name) == 0) {
                    printf("Roll No: %d, Name: %s, Marks: %.2f\n", temp->roll, temp->name, temp->mark);
                }
                temp = temp->next;
            }

            if (val1 > 1) {
                printf("Multiple records detected. Please provide the Roll no:\n");
                scanf("%d", &rn);
                while (ptr != NULL) {
                    if (ptr->roll == rn && strcmp(ptr->name, name) == 0) {
                        printf("-----------------------------------------------\n");
                        printf("| n/N: Change Name                            |\n");
                        printf("| r/R: Change Roll No                        |\n");
                        printf("| a/A: Change Name and Roll No               |\n");
                        printf("-----------------------------------------------\n");
                        scanf(" %c", &opt);
                        if ((opt == 'n') || (opt == 'N')) {
                            printf("Enter the new name:\n");
                            scanf("%29s", ptr->name);
                            return;
                        } else if ((opt == 'r') || (opt == 'R')) {
                            printf("Enter the new roll number:\n");
                            scanf("%d", &new_roll);
                            ptr->roll = new_roll;
                            return;
                        } else if ((opt == 'a') || (opt == 'A')) {
                            printf("Enter the new name and roll number:\n");
                            scanf("%29s %d", ptr->name, &new_roll);
                            ptr->roll = new_roll;
                            return;
                        } else {
                            printf("Enter a valid option\n");
                            return;
                        }
                    }
                    ptr = ptr->next;
                }
                printf("Sorry, this roll no doesn't belong to the given name.\n");
                return;
            }
            while (ptr != NULL) {
                if (strcmp(ptr->name, name) == 0) {
                    printf("-----------------------------------------------\n");
                    printf("| n/N: Change Name                            |\n");
                    printf("| r/R: Change Roll No                        |\n");
                    printf("| a/A: Change Name and Roll No               |\n");
                    printf("-----------------------------------------------\n");
                    scanf(" %c", &opt);
                    if ((opt == 'n') || (opt == 'N')) {
                        printf("Enter the new name:\n");
                        scanf("%29s", ptr->name);
                    } else if ((opt == 'r') || (opt == 'R')) {
                        printf("Enter the new roll number:\n");
                        scanf("%d", &new_roll);
                        ptr->roll = new_roll; 
                    } else if ((opt == 'a') || (opt == 'A')) {
                        printf("Enter the new name and roll number:\n");
                        scanf("%29s %d", ptr->name, &new_roll);
                        ptr->roll = new_roll;
                    }
                    return;
                }
                ptr = ptr->next;
            }
        }

    } else if ((op == 'P') || (op == 'p')) {
        printf("Enter the percentage to be modified:\n");
        scanf("%f", &per);
        val1 = search_mark(ptr, per);
        if (val1 == 1) {
            while (ptr != NULL) {
                if (ptr->mark == per) {
                    printf("Enter the new name and roll number:\n");
                    scanf("%29s %d", ptr->name, &new_roll);
                    ptr->roll = new_roll;
                    return;
                }
                ptr = ptr->next;
            }
        } else if (val1 > 1) {
            printf("Multiple records with the same mark exist. Please provide the Roll no:\n");
            scanf("%d", &rn);
            while (ptr != NULL) {
                if (ptr->roll == rn) {
                    if (ptr->mark == per) {
                        printf("Enter the new name and roll number:\n");
                        scanf("%29s %d", ptr->name, &new_roll);
                        ptr->roll = new_roll;
                        return;
                    } else {
                        printf("Sorry, this roll no doesn't belong to the given mark\n");
                        return;
                    }
                }
                ptr = ptr->next;
            }
        } else {
            printf("Sorry, no data for the given mark exists.\n");
        }
    } else {
        printf("Enter a valid option..\n");
    }
}
*/









int search(ST* ptr,char* name)
{
	int c=0,val;
	while(ptr!=0)
	{
		val=strcmp(name,ptr->name);
		if (val==0)
		{
			c++;
			printf("%d   %s   %f\n",ptr->roll,ptr->name,ptr->mark);
		}
		ptr=ptr->next;
	}
	return c;
}










int search_mark(ST*ptr,float mark)
{
	int c=0;
	while(ptr!=0)
	{
		if(ptr->mark==mark)
		{
			c++;
			printf("%d   %s   %f\n",ptr->roll,ptr->name,ptr->mark);
		}
		ptr=ptr->next;
	}
	return c;
}










void reverse(ST* ptr)
{
	if(ptr!=0)
	{
			reverse(ptr->next);
			printf("|  %d    |        %s      |  %.1f    |\n",ptr->roll,ptr->name,ptr->mark);
	}
}










void save(ST* ptr)
{
	FILE *fs= fopen("student.dat","w");
	while(ptr!=0)
	{
		fprintf(fs,"%d   %s   %f\n",ptr->roll,ptr->name,ptr->mark);
		ptr=ptr->next;
	}
	fclose(fs);
	printf("File saved Successfully at student.dat\n");
}










void print(ST* ptr)
{
	if (ptr==0)
	{
		printf("No data to Show\n");
		return;
	}
	printf("----------------------------------------\n");
	printf("|Roll no|        Name      |  Marks    |\n");
	printf("----------------------------------------\n");
	while(ptr!=0)
	{
		printf("|  %d    |        %s      |  %.1f    |\n",ptr->roll,ptr->name,ptr->mark);
		ptr=ptr->next;

	}

	printf("----------------------------------------\n");
}










void sort(ST* ptr)
{
	char op;
	int i=0,j=0,c=count(ptr);
	int size= sizeof(ST)-sizeof(ST*)-sizeof(int);
	ST** arr=(ST**)malloc(c*sizeof(ST*));
	ST* prr;
	ST temp;
	if (ptr==0)
	{
		printf("No Data to Sort\n");
	}
	printf("----------------------------------------\n");
	printf("| N/n: Sort with Name                  |\n");
	printf("| P/p: Sort with Percentage            |\n");
	printf("----------------------------------------\n");
	scanf(" %c",&op);
	for(i=0;i<c;i++)
	{
		arr[i]=ptr;
		ptr=ptr->next;
	}
	if ((op=='N')||(op=='n'))
	{

		for(i=0; i<(c-1); i++)
		{
			for(j=0; j<(c-1-i); j++)
			{


				if(strcmp(arr[j]->name,arr[j+1]->name)>0)
				{
					/*

					memcpy(&temp.name,&arr[j]->name,size);
					memcpy(&arr[j]->name,&arr[j+1]->name,size);
					memcpy(&arr[j+1]->name,&temp.name,size);

					//continue;
					*/
					prr=arr[j];
					arr[j]=arr[j+1];
					arr[j+1]=prr;

				}

			}
		}
		printf("----------------------------------------\n");
		printf("|Roll no|        Name      |  Marks    |\n");
		printf("----------------------------------------\n");
		for(i=0;i<c;i++)
		{
			printf("|  %d    |        %s      |  %.1f    |\n",arr[i]->roll,arr[i]->name,arr[i]->mark);
		}

		printf("----------------------------------------\n");

	}
	else if ((op=='P')||(op=='p'))
	{
		for(i=0; i<(c-1) ;i++)
		{
			for(j=0; j<(c-1-i); j++)
			{
				if(arr[j]->mark > arr[j+1]->mark)
				{
					/*
					memcpy(&temp.name,&arr[j]->name,size);
					memcpy(&arr[j]->name,&arr[j+1]->name,size);
					memcpy(&arr[j+1]->name,&temp.name,size);
					*/
					prr=arr[j];
					arr[j]=arr[j+1];
					arr[j+1]=prr;

				}

			}
		}

		printf("----------------------------------------\n");
		printf("|Roll no|        Name      |  Marks    |\n");
		printf("----------------------------------------\n");
		for(i=c-1;i>=0;i--)
		{
			printf("|  %d    |        %s      |  %.1f    |\n",arr[i]->roll,arr[i]->name,arr[i]->mark);
		}

		printf("----------------------------------------\n");

	}
	else
	{
		printf("Enter the valid option..\n");
	}
}

