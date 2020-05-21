#ifndef HANGMAN_H
#define HANGMAN_H
typedef struct Hangman{
        char* phrase;
        char* hint;
} Hangman;
//I'm getting error from this so I won't bother using it
//const int SIZE = 1024;
//char* randomN = NULL;
void init_list(Hangman* *p);
int read_line(Hangman* *p, FILE* streamIn);
void free_list(Hangman* *p, int phraseCnt);
//char* randstring(int length, char* RANDOM_NAME);
int randomInt(int lower, int upper);
void init_phrase(char* phrase, char* answer);
void printPhrase(char* phrase, char* answer, char ch);
int finished(char* answer);
#endif
