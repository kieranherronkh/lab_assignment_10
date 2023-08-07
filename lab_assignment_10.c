// Kieran Herron
// COP 3502C
// Lab Assignment 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Trie structure
struct Trie
{	

	char data;
	int leaf;
	struct Trie * children[26];
	int isEnd;
	int count;
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
	int i;
	int j;
	// temp trie pointer
	struct Trie *spTrie = pTrie;
	for(i = 0; word[i] != '\0'; i++) {
		int ind = (word[i] - 'a');
		if(spTrie->children[ind] == NULL) {
			spTrie->children[ind] = (struct Trie *) malloc(1 * sizeof(struct Trie));

			for(j=0; j < 26; j++) {
				((spTrie->children[ind]->children[j]) = NULL);

			}

			spTrie->children[ind]->isEnd = 0;
			spTrie->children[ind]->count = 0;

		}
		// iterate through word into trie
		spTrie = spTrie->children[ind];
	}
	// word end flag
	spTrie->isEnd = 1;
	// increment word count
	spTrie->count+1;

}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
	int i;
	int j;
	int k;

	for(i=0; i<strlen(word); i++) {
		int ind = word[i] - 'a';
		if(pTrie->children[ind] == NULL) {
			return(0);
		}
		pTrie = pTrie->children[ind];
	}
	if(pTrie->isEnd = 1) {
		return(pTrie->count);
	}
	else {
		return(0);
	}


}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
	int i;
	int j;
	if(pTrie == NULL) {
		return(NULL);
	}
	for(i=0; i<26; i++) {
		if(pTrie->children[i] != NULL) {
			deallocateTrie(pTrie->children[i]);
		}
	}
	free(pTrie);
	pTrie = NULL;


	return(0);
}

// Initializes a trie structure
struct Trie *createTrie()
{
	struct Trie * root = (struct Trie *)malloc(1 * sizeof(struct Trie));
	int i;

	for(i = 0; i< 26; i++) {
		root->children[i] = NULL;
		return(root);
	}
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
	// helper variables and return var
	char character;
	FILE * dictionaryFile;
	int wordCount = 0;
    int i = 0;
    int j = 0;
    char buffer[50];
    dictionaryFile = fopen("dictionary.txt", "r");

    // memory allocation for array of pointers
    // and array of characters
    pInWords = malloc(256 * sizeof(*pInWords));
    // arrays of size 50
    *pInWords = malloc(50 * sizeof(char));


	//reads dictionary.txt and puts into pInWords
	while((character = fgetc(dictionaryFile)) != EOF) {
        *pInWords[i] = character;
		if((character == ' ') || (character == '\n')) {
        pInWords[j] = *pInWords;
		wordCount++;
        j++;
        }
        i++;
	}

	fclose(dictionaryFile);
	//returns num of words
	return(wordCount);
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}