#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "wordle_lib.h"


// Most of the code that you're going to have to implement goes in here.
// Feel free to add more helper functions if necessary.

// Returns true if the guess is an exact match with the secret word, but
// more importantly, fills in the result with the following:
// - 'x' goes in a slot if the corresponding letter in the guess does not appear
//   anywhere in the secret word
// - 'y' goes in a slot if the corresponding letter in the guess appears in the
//   secret word, but not in the corresponding slot
// - 'g' goes in a slot if the corresponding letter in the guess appears in the
//   corresponding slot in the secret word.
//   You can assume that result points at enough memory for a string of length
//   5. (ie, at least 6 bytes long)
   

bool score_guess(char *secret, char *guess, char *result) {
  if (!secret || !guess || !result) {
      fprintf(stderr, "Null pointer passed to score_guess.\n");
      return false;
  }
  
  if (strlen(secret) !=5 || strlen(guess) !=5) {
      fprintf(stderr, "Inpuut strings must be exactly 5 characters long.\n");
      return false;
  } 

  bool matched_secret[5] = {false}; 
  bool matched_guess[5] = {false};

  for (int i = 0; i < 5; i++) {
    if (guess[i] == secret[i]) {
	   result[i] = 'g';
	  matched_secret[i] = true;
	  matched_guess[i] = true;
    } else {
      result[i] = 'x';
    } 
  }

  for (int i = 0; i < 5; i++) {
    if (result[i] == 'g') continue;
    for (int j = 0; j < 5; j++) {
      if (!matched_secret[j] && !matched_guess[i] && guess[i] == secret[j]) {
	 result[i] = 'y';
	matched_secret[j] = true;
        break;
      }
    } 
  }    

 result[5] = '\0';
 return strcmp(secret, guess) == 0;
} 
	
	
	
// TODO(you): finish this function 
 

// Returns true if the specified guess is one of the strings in the vocabulary,
// and false otherwise. num_words is the length of the vocabulary.
// A simple linear scan over the strings in vocabulary is fine for our purposes,
// but consider: could you do this search more quickly?
bool valid_guess(char *guess, char **vocabulary, size_t num_words) {
    if (!guess || !vocabulary) {
	fprintf(stderr, "Null pointer passed to valid_guess. \n");
	return false;
    }

    if (strlen(guess) != 5) {
      fprintf(stderr, "Invalid guess length; '%s'. Must be 5 characters.\n" , guess);
      return false;
    
    }
   for (size_t i = 0; i < num_words; i++) {
        if (vocabulary[i] && strcmp(guess, vocabulary[i]) == 0) {
	    return true;
        }
   } 

   return false;
}

// TODO(you): finish this function
 

// Returns an array of strings (so, char **), where each string contains a word
// from the specified file. The file is assumed to contain 5-letter words, one
// per line.
// Also, this function sets the value pointed at by *num_words to be the number
// of words read.
// This will need to allocate enough memory to hold all of the char* pointers --
// so you will keep track of the size of your char** array and then use realloc
// to make the array larger over time, so that you have enough space for the
// dynamically-growing array of char *.
// Use fopen to open the input file for reading,
// strdup (or strndup) to make copies of each word read from that file, and
// fclose to close the file when you are done reading from it.
// Each element of the array should be a single five-letter word,
// null-terminated.
char **load_vocabulary(char *filename, size_t *num_words) {
  if (!filename || !num_words) {
    fprintf (stderr,"Invalid input to load_vocabulary.\n");
    return NULL;
  }
  
  FILE *file = fopen(filename, "r");
  if (!file) {
      fprintf(stderr, "Failed to open file; %s/n", filename);
      return NULL;
   }
  
  char **vocabulary = NULL;
  *num_words = 0;
  size_t capacity = 0;

  char buffer[6];
  while (fscanf(file, "%5s", buffer) == 1) {
     if (strlen(buffer) !=5) continue;
     
     if (*num_words >= capacity) {
         capacity = capacity == 0 ? 10 : capacity * 2 ;
         char **temp = realloc(vocabulary, capacity * sizeof(char *));
         if (!temp) {
     		 fprintf(stderr,"Memory allocation failed.\n");
     		 fclose(file);
     		 return NULL;
	 }
   	 vocabulary = temp;
     }
  
     vocabulary[*num_words] = strdup(buffer);
     if (!vocabulary[*num_words]) {
   	 fprintf(stderr,"Memory allocation failed fpr word.\n");
   	 fclose(file);
   	 free_vocabulary(vocabulary, *num_words);
	 return NULL;
     }
     (*num_words)++;
 }

  fclose(file);
  return vocabulary;
}


// Free each of the strings in the vocabulary, as well as the pointer vocabulary
// itself (which points to an array of char *).
void free_vocabulary(char **vocabulary, size_t num_words) {
     if (!vocabulary) return;

     for (size_t i = 0; i < num_words; i++) {
         free(vocabulary[i]);
     }
     free(vocabulary);
}
