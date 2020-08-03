// Eric Tran 
// 18089350
// github: @wangermote https://github.com/wangermote/CP386_A4

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>
// RQ request RL release * print values Run find safe sequence and run each ad every trheads

int available[4] = {}; // these here a re the availble
int maximum[4] = {}; // this here is the maximum 
int allocation[4] = {}; // here this is the allocation 
int need[4] = {}; // here will be the array for need
typedef struct cust // a structure for customer, will be called cust
{

    int id; // the id for the cust
    int item[4]; // can have up to 5 items for the customer, and we'l start from 0.

}Cust;

int readFile(char* name,Cust** cust ){ // this shall be our read file function here

    FILE* fp = fopen(name,"r"); // r is for read mode, read a file in withy name file 
	
    if(!fp)
	{
		printf("Looks like there was an error with opening a file. Now "); // here there is an error with opening the file, and so we shall return negative one.
		return -1;
	}
	struct stat stats; // make a stat called stats
	fstat(fileno(fp), &stats);
	char* contentsFile = (char*)malloc(((int)stats.st_size+1)* sizeof(char));  // allocating the correect size to contents file, which shall contain the contents.
	contentsFile[0]='\0'; //append null to the beginning!

    while(!feof(fp)) 
	{
		char buffer[100]; // createing a buffer of 100 size
		if(fgets(buffer,100,fp)!=NULL)
		{
			strncat(contentsFile,buffer,strlen(buffer)); // concatenate !
		}
	}
    fclose(fp); // close that file!

	char* commands = NULL;
	int custCount = 0;
	char* copiefile = (char*)malloc( (strlen(contentsFile)+1)*sizeof(char) ); // also still allocating the correct size to copiefile
	strcpy(copiefile,contentsFile);
	commands = strtok(copiefile,"\r\n");

	while(commands!=NULL){
		custCount++; // counting of cusmters, increment by 1 
		commands = strtok(NULL,"\r\n");
	}
	*cust = (Cust*)malloc(sizeof(cust) * custCount); // now that we have trhe custcount we can allocate the correct amount of space for our cust

	strcpy(copiefile,contentsFile); // copy contents file into copiefile once again
	commands = strtok(copiefile,"\r\n");
	char* thelist[custCount];
	int i =0 ;

	while (commands!=NULL){
		thelist[i] = malloc(sizeof(commands) * sizeof(char));
		thelist[i] = strcpy(thelist[i],commands);
		i++;
		commands = strtok(NULL, "\r\n");
	}

	for (int i =0; i < custCount; i++){
		int j = 0;
		char* tokeytoke = NULL;
		tokeytoke =  strtok(thelist[i],",");
		while(tokeytoke!=NULL) // while it is not null 
		{
			
			if(j==0){
				(*cust)[i].item[0] = atoi(tokeytoke); // do this, setting up all the items resources numbers 
				//do the resource setting number for item 1 in index 0 
			}

			else if(j==1){
				(*cust)[i].item[1] = atoi(tokeytoke); // do the resource setting number for item 2 in index 1 
			}
			else if(j==2){
				(*cust)[i].item[2] = atoi(tokeytoke); // do the resource setting number for item 3 in index 2 
			}

			else if(j==3){
				(*cust)[i].item[3] = atoi(tokeytoke); // do the resource setting number for item 4 in index 3
			}

			else if(j==4){
				(*cust)[i].item[4] = atoi(tokeytoke); // do the resource setting number for item 5 in index 4 
			}
			tokeytoke = strtok(NULL,",");
			j++;
			
		}
	}
    

	return custCount; // here is the returning of the customer count . 
}

int determineRQ(int i[4]){ // take in 4 integers
	
	for (int j =0; j <5; j++){
		if (i[j]==0){
			return -1;
		}
	}
	

	return 1;
}

int determineRL(int i[4]){


	return !determineRQ(&i[4]);
}


int main(int argc, char *argv[])
{
	Cust* cust= NULL;
    int numcust = readFile("sample4_in.txt",&cust);
	
	printf("Number of Customers: %d\n", numcust);
  	printf("Currently Available resources:\n");
	for (int i=0; i <4; i++){
		available[i]  = atoi(argv[i + 1]);
  		printf("%d ",available[i]);
	}
	printf("\n");
  	printf("Maximum resources from file:\n");
	for (int i=0; i <5; i++){
		
  		printf("%d,",cust[i].item[0]);
		printf("%d,",cust[i].item[1]);
		printf("%d,",cust[i].item[2]);
		printf("%d",cust[i].item[3]);

		printf("\n");
		
		
	}
	char* input = (char*)malloc(sizeof(char) * 50);
	while(1){
		printf("Enter Command:");
		fgets(input,50,stdin);
		char* RQ = strstr(input,"RQ");
		char* RL = strstr(input,"RL");
		char* Run = strstr(input,"Run");
		char* PrintResource = strstr(input,"*");
		char* Exit = strstr(input,"Exit");


		if (RQ != NULL){
			if (determineRQ(cust[0].item) != -1){
				printf("Request is satisfied\n");
			}
			else{ // this case it is -1
				printf("Request is not satisfied\n");
			}
			
		}
		else if (RL != NULL){

			if(determineRL(cust[0].item) != -1){
				printf("Request is satisfied\n");
			}
			else{
				printf("Request is not satisfied\n");
			}
		}

		else if (Exit != NULL){
			printf("Exiting");
			break;
		}

		else if (PrintResource != NULL){
			printf("Printing\n");
		}

		else if (Run != NULL){
			printf("Running\n");
		}

		

	}


}