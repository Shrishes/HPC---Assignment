#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <math.h>
#include <time.h>
/***********************************************************************
*******
  Demonstrates how to crack an encrypted password using a simple
  "brute force" algorithm. Works on passwords that consist only of 2
uppercase
  letters and a 2 digit integer. Your personalised data set is included
in the
  code.

  Compile with:
    cc -o CrackAZ99-With-Data CrackAZ99-With-Data.c -lcrypt

  If you want to analyse the results then use the redirection operator
to send
  output to a file that you can view using an editor or the less
utility:

    ./CrackAZ99-With-Data > results.txt

  Dr Kevan Buckley, University of Wolverhampton, 2018
************************************************************************
******/
int n_passwords = 4;

char *encrypted_passwords[] = {

"$6$KB$5B3KGhhav2/OsufUGxdicHWDBJM7ojVt0DvSVVwcpHL2OiiiBnq.b6hHZ/uYsi9PETZ6XDOW9/xOOrcbIXcfE/",

"$6$KB$BnOJ7N1FAfJEUjwbecr9dk3lZFbrvc0XenvCyQebIefk5xcLST4qwSQw0OkkP9QzHJHtRNyLdGiXlii0Yk08N/",

"$6$KB$vGjZkftJBbu1jmhrMfA8ARGIFOn6rr/AWVlkXzUU6mKwEyCyFb748wIPEdC5Q8vKFK5Fvy6uf/ZkwMvYuBoaJ/",

"$6$KB$GV/djQ8Pe79FY.cizCUK/iUE6GX3g69PA07dwkFyHMnWclg0GoeUmwJx4rduLsbfpIAGJCj89rs0V5faHkq1g."
};

/**
 Required by lack of standard function in C.   
*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

/**
 This function can crack the kind of password explained above. All
combinations
 that are tried are displayed and when the password is found, #, is put
at the
 start of the line. Note that one of the most time consuming operations
that
 it performs is the output of intermediate results, so performance
experiments
 for this kind of program should not include this. i.e. comment out the
printfs.
*/

void crack(char *salt_and_encrypted){
  int w, x, y, z;     // Loop counters
  char salt[8];    // String used in hashing the password. Need space for \0
  char plain[8];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);
for(w='A'; w<='Z'; w++){
  for(x='A'; x<='Z'; x++){
    for(y='A'; y<='Z'; y++){
      for(z=0; z<=99; z++){
        sprintf(plain, "%c%c%c%02d", w, x, y, z);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } else {
          printf(" %-8d%s %s\n", count, plain, enc);
        }
      }
    }
  }
}
  printf("%d solutions explored\n", count);
}

int time_difference(struct timespec *start, struct timespec *finish, long long int *difference){
  long long int ds = finish->tv_sec - start->tv_sec;
  long long int dn = finish->tv_nsec - start->tv_nsec;

  if(dn < 0) {
     ds--;
     dn += 1000000000;
     }

     *difference = ds * 1000000000 + dn;
     return ! (*difference > 0); 
}

int main(int argc, char *argv[]){
  int i;

  struct timespec start, finish;
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);
 
        for(i=0;i<n_passwords;i<i++) {
        crack(encrypted_passwords[i]);
        }

clock_gettime(CLOCK_MONOTONIC, &finish);
time_difference(&start, &finish, &time_elapsed);
printf("Time elapsed was %lldns, %0.9lfs or %0.9lfmin\n", time_elapsed, (time_elapsed/1.0e9), (time_elapsed/1.0e9)/60);


  return 0;
}

