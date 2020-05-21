#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/socket.h>
#include <string.h>
#include "hangman.h"

int main(int args, char* argv[]){

	char* phrase = (char*)malloc(sizeof(char) * 1024);
	char* hint = (char*)malloc(sizeof(char) * 1024);
	char* answer = (char*)malloc(sizeof(char) * 1024);


	struct sockaddr serverName = {AF_UNIX, "RANDOM_Nc"};
	socklen_t SN_len = sizeof(struct sockaddr) + 10;

	int counter = 0;
	int play = 1;
	while(play){
		int sock = socket(AF_UNIX, SOCK_STREAM, 0);
		if(sock == -1){
			printf("Sock has failed\n");
			return -1;
		}

		if (connect(sock, &serverName, SN_len) == -1){
			printf("Connect() failed\n");
			return -1;
		}
		read(sock, phrase, sizeof(char)*1024);// sizeof(Hangman)*1024);
		read(sock, hint, sizeof(char)*1024);
		close(sock);
		sleep(1);

		//stuff happens here
		if(counter == 0){
                        printf("\nHint: ");
                        printf("%s", hint);
			printf("\n\nCommon Phrase\n");
                        printf("-------------\n");
                        init_phrase(phrase, answer);
			++counter;
                }else{


		char ch, st;
		char buffer[10];
		do {
			printf("Enter a single character guess : ");
			if (fgets(buffer, 10, stdin) == NULL) {
				printf("Error in fgets()");
            			exit(1);
        		}
    		} while ((sscanf(buffer, "%c%c", &ch, &st) != 2) || (st != '\n'));

			printf("\n\nCommon Phrase\n");
			printf("-------------\n");

			printPhrase(phrase, answer, ch);
			if(finished(answer)){
				printf("\nYou're finished, good job!\n\n");
				break;
			}
		}
	}
	free(phrase);
        free(hint);
	free(answer);

return 0;
}
