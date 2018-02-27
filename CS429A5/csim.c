//Kevin Nguyen
//kdn433

//Defines and Includes for program
#define NULL 0
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include "cachelab.h"

//The structs of the cache, set, and lines; these will be used as our data structure of a cache
//Caches have sets in them, sets have lines in them, and lines a valid bit and tag bits
typedef struct Cache {
	int SBits;
	struct Set *head_S;
} cacheData;

typedef struct Set {
	int EBits;
	struct Line *head_L;
	struct Set *next;
} setData;

typedef struct Line {
	int validBit, tagBits;
	struct Line *next;
} lineData;

//Function Definitions are declared here for future use
void initialSet(int E, setData *set);
void initialCache(int E, int s, cacheData *cache);
void addToHead(setData *set, lineData *line);
void lineIntoSet(setData *set, lineData *line, lineData *previous);
void deleteLast(setData *set);
void getAddress(cacheData *cache, unsigned address);
void freeCache(cacheData *cache);
void validateArgs(int opt, int argc, char **argv);
void analyzeCurrentFile(cacheData *cache, char op, int size, int address, int oddCheck);
int getSetSize(setData *set);

//Declaration of variables, each variables is related to the cache
int s, b, t, E;
int verboseFlag = 0;
int hits = 0, misses = 0, evictions = 0;
int m = sizeof(long) * 8;
char *traces;

//initialize the set, should have empty lines (empty cache)
void initialSet(int E, setData *set) {
	set->EBits = E;
	set->head_L = NULL, set->next = NULL;
}

//Initialize the cache with empty initialized sets (empty cache idea)
void initialCache(int E, int s, cacheData *cache) {
	//Local variable and declare the set to be used for now
	int iterations = 1;
	cache->SBits = (1 << s);
	setData  *currentSet = (setData*)malloc(sizeof(setData));
	initialSet(E, currentSet);
	cache->head_S = currentSet;

	//Iterate through sets (create more if needed) in the cache and initialize them
	while (iterations < cache->SBits) {
		setData *nextSets = (setData*)malloc(sizeof(setData));
		initialSet(E, nextSets);
		currentSet->next = nextSets;
		currentSet = nextSets;
		iterations++;
	}
}

//Add a valid line to head of set and evict if needed
void addToHead(setData *set, lineData *line) {
	if (set->EBits == getSetSize(set)) {
		deleteLast(set);
		if (verboseFlag) {
			printf("Eviction ");
		}
		evictions++;
	}
	line->next = set->head_L;
	set->head_L = line;
}

//Match in set? then move line into set
void lineIntoSet(setData *set, lineData *line, lineData *previous) {
	if (previous != NULL) {
		previous->next = line->next;
		line->next = set->head_L;
		set->head_L = line;
	}
}

//Remove a line from the set (last one)
void deleteLast(setData *set) {
	//Local variables for use
	lineData *current = set->head_L, *tmp = NULL, *previous = NULL;

	//Find last line in Set, then proceed to check
	while (current != NULL) {
		tmp = previous;
		previous = current;
		current = current->next;
	}

	//Clear the tmp that has the last line of information, free leftover info on previous
	if (tmp != NULL) {
		tmp->next = NULL;
	}
	else if (tmp == NULL) {
		set->head_L = NULL;
	} 
	free(previous);
}

//Get address in the cache, search through the sets and lines to find the correct match
void getAddress(cacheData *cache, unsigned address) {
	//Local Variables to use (Note: addressing has format Tagbits | SetBits | Offset Bits )
	int iterations = 0, done = 0, tagBits = (address >> (s + b)), setBits = ((address << t) >> (t + b));
	
	//Find needed set in the cache
	setData *setTarget = cache->head_S;
	while (iterations < setBits) {
		setTarget = setTarget->next;
		iterations++;
	}
	
	//Get the lines from the set and match up the tagBits and validBit
	//If hit then add to it and skip the miss, otherwise skip hit and go through miss logic
	//Also if verbose mode is active, logic can print out hit, miss, eviction as needed
	lineData *thisLine = setTarget->head_L, *previous = NULL;
	while (thisLine != NULL) {
		if (thisLine->validBit && (thisLine->tagBits == tagBits)) {
			if (verboseFlag) {
				printf("Hit ");
			}
			hits++;
			lineIntoSet(setTarget, thisLine, previous);
			done = 1;
			break;
		}
		previous = thisLine;
		thisLine = thisLine->next;
	}
	if (done == 0) {
		if(verboseFlag) {
			printf("Miss ");
		}
		misses++;
		lineData *newLine = (lineData*)malloc(sizeof(lineData));
		newLine->validBit = 1;
		newLine->tagBits = tagBits;
		addToHead(setTarget, newLine);
		done = 0;
	}
} 

//Free the caches, sets, and lines
void freeCache(cacheData *cache) {
	//Go through each set and within each set each line, then clear them all. Clear cache afterwards
	setData *setFree = cache->head_S;
	while (setFree != NULL) {
		lineData *lineFree = setFree->head_L;
		while (lineFree != NULL) {
			lineData *tmpLine = lineFree->next;
			free(lineFree);
			lineFree = tmpLine;
		}
		setData *tmpSet = setFree->next;
		free(setFree);
		setFree = tmpSet;
	}
	free(cache);
}

//Validate the arguments from the terminal
void validateArgs(int opt, int argc, char **argv) {
	//Go through each argument and most of them should enter the if-else if case below
	//v = verbose mode, s = set index bits, E = number of lines per set, b = block Bits, and t = name of valgrind trace to replay
	while ((opt = getopt(argc, argv, "vhs:E:b:t:")) != -1) {
		if (opt == 'v') {
			verboseFlag = 1;
		}
		else if (opt == 's') {
			s = atoi(optarg);
			if ((s < 0) && (s > m)) {
				printf("Error: s value incorrect\n");
				exit(1);
			}
		}
		else if (opt == 'E') {
			E = atoi(optarg);
			if (E <= 0) {
				printf("Error: E value incorrect\n");
				exit(1);
			}
		}
		else if (opt == 'b') {
			b = atoi(optarg);
			if ((b < 0) || (b > m)) {
				printf("Error: b value incorrect\n");
				exit(1);
			}
		}
		else if (opt == 't') {
			traces = optarg;
		}
	}
}

//Analyze into file and drive the cache simulator with verbose mode
void analyzeCurrentFile(cacheData *cache, char op, int size, int address, int oddCheck) {
	FILE *traceFile = fopen(traces, "r");
	if (!traceFile) {
		fprintf(stderr, "Error: The file can’t be analyzed!\n");
		exit(1);
	}
	else {
		//Scan into the file and output as needed with verbose format, oddCheck to ensure format is printed correctly
		while (fscanf(traceFile, "%c %x, %d", &op, &address, &size) > 0) {
			if (verboseFlag && ((oddCheck % 2) == 1)) {
				printf("%c %x, %d ", op, address, size);
			}
			oddCheck++;
			if (op == 'S') {
				getAddress(cache, address);
			}
			else if (op == 'L') {
				getAddress(cache, address);	
			}
			else if (op == 'M') {
				getAddress(cache, address);
				getAddress(cache, address);
			}
			else {
				if (verboseFlag == 1) {
					printf ("\n");
				}
			}
		}
		fclose(traceFile);
		freeCache(cache);
	}
}

//Return number of valid lines inside the set itself; the size of the set
int getSetSize(setData *set) {
	//Local variable
	int setSize = 0;

	//Iterate through each line in set and add them up
	lineData *current = set->head_L;	
	while (current != NULL) {
		setSize++;
		current = current->next;
	}
	return setSize;
}

//Main function to be called
int main (int argc, char **argv) {
	//Local variable
	char op = NULL;
	int opt = 0, size = 0, address = 0, oddCheck = 0;

	//validate the arguments as needed
	validateArgs(opt, argc, argv);
	
	//After validate is finished and args are valid then create the initial cache and perform simulator
	t = m - (s + b);
	cacheData *cache = (cacheData*)malloc(sizeof(cacheData));
	initialCache(E, s, cache);
	analyzeCurrentFile(cache, op, size, address, oddCheck);

	//Print the results of our simulator and end program
	printSummary(hits, misses, evictions);
	return 0;
}