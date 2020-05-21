#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hangman.h"
#include <time.h>
#include <ctype.h>
void init_list(Hangman* *p){
        int i;
        for(i = 0; i < 1024; i++){
                p = NULL;
        }
}

int read_line(Hangman* *p, FILE* streamIn){
        char array[1024];
        int i = 0;

        while(fgets(array, sizeof(array), streamIn) != NULL){
                p[i] = (Hangman*)malloc(sizeof(Hangman) * 1024);

                char* string = strtok(array, "~");
                p[i]->phrase = strdup(string);
//printf("phrase: %s ->", p[i]->phrase); fflush(stdout);
                string = strtok(NULL, "~");
                p[i]->hint = strdup(string);
//printf("hint : %s", p[i]->hint);fflush(stdout);
                i++;
        }
        return i;
}

void free_list(Hangman* *p, int phraseCnt){
        int i;
        for(i = 0; i< phraseCnt; i++){
                free(p[i]->phrase);
		free(p[i]->hint);
                free(p[i]);
        }
}

int randomInt(int lower, int upper){
	srand(time(0));
	int num = (rand() % (upper - lower + 1)) + lower;
	return num;
}

/*char* randstring(int length) {

    char set[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char* randN = NULL;

    if (length != 0) {
        randN = malloc(sizeof(char) * (length + 1));

	srand(time(0));

    	if(randN) {
            for (int i = 0;i < length;i++) {
                int chara = rand() % (int)(sizeof(set) - 1);
                randN[i] = set[chara];
            }

            randN[length] = '\0';
        }
    }
return randN;
//	*randomN = *randN;
//printf("%s\n", ranStr);
}*/

void init_phrase(char* phrase, char* answer){
	int size = strlen(phrase);
	int i = 0;
	for(i = 0; i < size; i++){
		if(phrase[i] != ' '){
			answer[i] = '?';
          	}else{
			answer[i] = ' ';
          	}
	}
	printf("%s\n\n", answer);
}

void printPhrase(char* phrase, char* answer, char ch){
	int size = strlen(phrase);
	int i = 0;
        for(i = 0; i < size; i++){
		if(tolower(phrase[i]) == tolower(ch)){
                        answer[i] = tolower(ch);
                }else if(phrase[i] == ' '){
                  answer[i] = ' ';
                }
        }
        printf("%s\n\n", answer);
}

int finished(char* answer){
	int size = strlen(answer);
	int counter =0;
	int i;
	for(i = 0; i<size; i++){
		if(answer[i] != '?'){
			++counter;
		}
	}
	if(counter == size){
		return 1;
	}
return 0;
}
