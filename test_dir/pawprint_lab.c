#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct player {
	char Fname[25];
	char Lname[25];
	int Singles;
	int Doubles;
	int Triples;
	int Homeruns;
	int At_Bats;
	float Slugging_Percentage;
} Player;

// This function will read in size  struct players from filename and add these // the players array. The function will use index  to know where to start       // writing  the players to in the array.
// Parameters
//
// filename – The name of the input file
// players – a pointer to the array of player structures
// index – The index of the array to start placing players into
// size – The number of players in the input file
// Return - Nothing
void read_from_file(char* filename, Player* players, int index, int size);


// This function will take in a structure of players and print them into the      // given 
// output file, filename
// Parameters
//
// filename – the name of the output file
// players – a pointer to the array of struct players to write to the file
// size – the size of the players  array
// Return - Nothing
void write_to_file(char* filename, Player* players, int size);

// This function will take in an array of players and calculate their slugging      // percentage using the other variables in the structure(Singles, Doubles,           // Triples, Homeruns).
// Parameters
//
// players – a pointer to the array of Players structures
// size – the size of the array of structures
void calculate_slugging(Player* players, int size);

//This function takes in an array of players and will sort this array based on Slugging      // Percentage. The formula for calculating slugging percentage can be found toward the       // bottom of the document. 
// Parameters
//
// players – a pointer to the array of Player structures
// size – the size of the array
// Return - Nothing
void sort_array(Player* players, int size);


void close_FD();

int main(int argc, char* argv[]){

	//Error check the command line
	if(argc != 6){
		printf("-----------------------------------------------------------------\n");
		printf("\nINCORRECT USE OF PROGRAM\n");
		printf("Correct usage: ./a.out <Total_Number_Of_Players> <input1> <input2> <input3> <output>");
		printf("\n....exiting.....\n");
                printf("-----------------------------------------------------------------\n");
		close_FD();
	}

	//Gather command line arguments:
	int num_players = atoi(argv[1]);
	char* input_1 = argv[2];
	char* input_2 = argv[3];
	char* input_3 = argv[4];
	char* output = argv[5];
	
	//Test command line args
	printf("\n\n-----------------------Command Line Argument Check------------------------\n\n");
        printf("argv[1]: %d\n",num_players);
	printf("argv[2]: %s\n",input_1);
	printf("argv[3]: %s\n",input_2);
	printf("argv[4]: %s\n",input_3);
	printf("argv[5]: %s\n",output);	
	printf("\n\n-----------------------------------------------------\n\n");

	//Allocate memory for 30 players
	Player* players = malloc(sizeof(Player)*num_players);
	if(players == NULL){
		printf("Error when attempting to allocate memory for players\nexiting.....\n");
		close_FD();
		return 0;
	}

	//Create variable to represent size of each input file
	int file_size = num_players/3;
        int index = 0;

	//Read from our first file
	printf("\n\n------------------------------ Player scan test ---------------------\n\n");
	read_from_file(input_1,players,index,file_size); 
	index+=10;
	
	//Read from second file
	read_from_file(input_2,players,index,file_size);
	index+=10;

	//Read from third file
	read_from_file(input_3,players,index,file_size);
        printf("\n\n---------------------------------------------------------------------\n");
	
	//Calcualte the slugging percentage
	calculate_slugging(players,num_players);
	
	//Sort By Slugging
	sort_array(players,num_players);

	//Print to output file
	write_to_file(output,players,num_players);

	//Free pointer
	free(players);	

	close_FD();
	return 0;
}

void write_to_file(char* filename, Player* players, int size){
	
	FILE* fp = fopen(filename,"w");
	if(fp == NULL){
		printf("FAILED TO OPEN: %s\n",filename);
	}

	int i = 0;

	for(i = 0; i < size; i++){
                fprintf(fp,"%s %s %d %d %d %d %d\n",(players+i)->Fname,(players+i)->Lname,(players+i)->Singles, (players+i)->Doubles, (players+i)->Triples, (players+i)->Homeruns, (players+i)->At_Bats);
        }
	
	fclose(fp);

	return;

}

void sort_array(Player* players, int size){
	int i = 0;
	int j = 0;
	Player temp;

	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			if( (players+i)->Slugging_Percentage > (players+j)->Slugging_Percentage){
				memcpy(&temp,(players+i),sizeof(Player));
				memcpy((players+i),(players+j),sizeof(Player)); 
				memcpy((players+j),&temp,sizeof(Player)); 		
			}
		}
	}

	printf("\n\n------------------------------- TESTING SORT ------------------------------\n\n");
	for(i = 0; i < size; i++){
		printf("Player: %s has slugging: %.4lf\n",(players+i)->Fname,(players+i)->Slugging_Percentage);
	}
	printf("\n\n---------------------------------------------------------------------------\n\n");
}

void calculate_slugging(Player* players, int size){

	int i = 0;
	int singles = 0;
	int doubles = 0;
	int triples = 0;
	int homeruns = 0;	
	int at_bats = 0;

	printf("\n\n----------------------------------------- TESTING SLUGGING ------------------------------------\n\n");
	for(i = 0; i < size; i++){
		singles = (players+i)->Singles;
		doubles = (players+i)->Doubles;
		triples = (players+i)->Triples;
		doubles = (players+i)->Homeruns;
		at_bats = (players+i)->At_Bats;
 
		(players+i)->Slugging_Percentage = (float) (singles+(doubles*2)+(triples*3)+(homeruns*4)) / (float) at_bats;
		
		printf("Player: %s has slugging: %.4lf\n",(players+i)->Fname,(players+i)->Slugging_Percentage);
	}
	printf("\n\n------------------------------------------------------------------------------------------------\n\n");

	return;
}

void read_from_file(char* filename, Player* players, int index, int size){

	if(filename == NULL || players == NULL || index < 0 || index > 30 || size < 0){
		printf("Invalid values passed to read_from_file, go double check\n");
		return;
	}

	//Open our given file
	FILE* fp = fopen(filename,"r");
	if(fp == NULL){
		printf("ERROR OPENING FILE: %s\n",filename);
		return;
	}

	//Scan players from file
	//NOTE: START FROM SPECIFIED INDEX!!! 0-9, 10-19, 20-29
	int i = index;
	
	while(i < (index+10)){
		fscanf(fp,"%s %s %d %d %d %d %d",(players+i)->Fname,(players+i)->Lname,&(players+i)->Singles, &(players+i)->Doubles, &(players+i)->Triples, &(players+i)->Homeruns, &(players+i)->At_Bats);
		printf("%s %s %d %d %d %d %d\n",(players+i)->Fname,(players+i)->Lname,(players+i)->Singles, (players+i)->Doubles, (players+i)->Triples, (players+i)->Homeruns, (players+i)->At_Bats);
		i++;
	}

	fclose(fp);
	return;
}

void close_FD(){
	close(0);
	close(1);
	close(2);
}
