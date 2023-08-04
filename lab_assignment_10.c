#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie {
  int numOccurs;
  struct Trie *children[26];
};

// Initializes a trie structure
struct Trie *createTrie() {
  struct Trie *myTrie = malloc(sizeof(struct Trie));

  myTrie->numOccurs = 0;

  for (int i = 0; i < 26; i++)
    myTrie->children[i] = NULL;

  return myTrie;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word, int iteration) {
  if (iteration == strlen(word)) {
    (pTrie->numOccurs)++;
    return ;
  }

  if (pTrie->children[word[iteration] - 'a'] == NULL)
    pTrie->children[word[iteration] - 'a'] = createTrie();

  iteration++;

  insert(pTrie->children[word[iteration-1] - 'a'], word, iteration);
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word) {
  int len = strlen(word);
  for (int i = 0; i < len; i++){
    if(pTrie->children[word[i] - 'a'] == NULL)
      return 0;
    pTrie = pTrie->children[word[i] - 'a'];
  }

  if(pTrie->numOccurs == NULL)
    return 0;

  return pTrie->numOccurs;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie) {
  if (pTrie == NULL)
    return NULL;

  for (int i = 0; i < 26; i++) {
    if (pTrie->children[i] != NULL)
      deallocateTrie(pTrie->children[i]);
  }
  
  free (pTrie);
  return NULL;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords) {
  FILE *fp = fopen(filename, "r");
  
  char w[10000];
  int num = 0;
  int i = 0;

  if (fp != NULL) {
    fscanf(fp, "%d", &num);
    while (fscanf(fp, "%s", w) != EOF) {
      pInWords[i] = malloc(sizeof(char) * (strlen(w) + 1));
      strcpy(pInWords[i], w);
      i++;
    }
  }
  
  fclose(fp);
  return num;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i < numWords; ++i) {
		printf("%s\n",inWords[i]);
  }

	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i], 0);
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
