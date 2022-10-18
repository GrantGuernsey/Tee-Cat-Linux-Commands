#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define MSGSIZE 6

int main(int argc, char **argv)
{
  // Gets character and creates a file pointer
  char c;
  FILE *fp;

  if (argc > 1)
  {
    fp = fopen(argv[1], "r"); // Opens the file given as an argument as read and sets it to the file pointer
    if (fp == NULL)           // if the file is not found
    {
      fprintf(stderr, "ERROR - FILE %s NOT FOUND\n", argv[1]);
      exit(1);
    }
  }
  else
    fp = stdin;

  while (!feof(fp)) // while the file is not at the end
  {
    c = getc(fp); // gets char from the file
    if (!feof(fp))
      putc(c, stdout); // prints the character to stdout or the terminal
  }
}