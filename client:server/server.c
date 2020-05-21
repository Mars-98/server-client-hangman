#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/socket.h>
#include <string.h>
#include "hangman.h"
#include <stdbool.h>

int main(int args, char* argv[]){
	int sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sock == -1){
		printf("The socket failed");
		return -1;
	}

	struct sockaddr serverName = {AF_UNIX, "RANDOM_Nc"};
	socklen_t SN_len = sizeof(struct sockaddr) + 10;

	int sockBind = bind(sock, &serverName, SN_len);
	if(sockBind == -1){
		printf("Binding was unsuccessful\n");
		return -1;
	}

	Hangman* list[1024];
	init_list(list);
	int phraseCnt = 0;
	FILE* file = fopen("phrases.txt", "r");
        if ( file == NULL ) {
		printf("phrases.txt could not be opened!");
		exit(1);
	}else{
		phraseCnt = read_line(list, file);
		fclose(file);
	}

	int chosenP = randomInt(0, 14);

	struct sigaction news;
	struct sigaction olds;

	void ctrlc(){
		sigaction( SIGINT, &olds, NULL);
		close(sock);
		unlink("RANDOM_Nx");

		// 2)free whatever you allocated up there in step 1
		for(int i = 0; i < 1024; i++){
			free(list[i]->phrase);
			free(list[i]->hint);
			free(list[i]);
		}
		exit(0);
	}

	news.sa_handler = ctrlc;
	news.sa_flags = 0;

	sigaction( SIGINT, &news, &olds);

	int keepPlay = 1;
	int sock2;

	while(keepPlay){
		if(listen(sock, 1) == -1){
			printf("Listen() failed");
			return -1;
		}

		if((sock2 = accept(sock, NULL, NULL)) == -1  )  {
			printf("Accept() failed");
                        return -1;
		}

		//put game back to default stage

		write(sock2, list[chosenP]->phrase ,sizeof(char)*1024);
		write(sock2, list[chosenP]->hint ,sizeof(char)*1024);
		close(sock2);
	}

	for(int i = 0; i < 1024; i++){
		free(list[i]->phrase);
                free(list[i]->hint);
                free(list[i]);
        }


return 0;
}


