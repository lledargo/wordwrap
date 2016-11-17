/*****************************************************************************
 * K&R 1.22
 * Write a program to "fold" long lines into two or more shorter lines after 
 * the last non-blank character that occurs before the n'th column of input.
 *
 * K&R 2.2
 * see line 53 
 *****************************************************************************/

#include <stdio.h>

#define WIDTH 80
#define LINEMAX 1000

int lineget(char[], int);
int wordwrap(int, int, char[], char[]);
void copystr(int, int, char[], char[]);

/* break long lines at 80 columns */
int main()
{
  char fullline[LINEMAX];
  char line[WIDTH + 2];
  int position, br;

  position = 0;
  br = -1;

  while( (lineget(fullline, LINEMAX)) != 0 )
  {
    while( br != 0 )
    {
      br = wordwrap(position, WIDTH, fullline, line);
      fputs(line, stdout);
      position = position + br + 1;

    }
    br = -1;
    position = 0;
  }
  return 0;
}



// Should produce the same result at stdio getline(). I implemented my own for 
// educational purposes.

int lineget(char s[], int linemax)
{
  int c, i, n;
  
//K&R 2.2 asks for a a version of the below for loop without any logical operators
//  for( i = 0; (i < linemax - 1) * (((c = getchar()) != EOF ) * ( c != '\n' )); ++i)

  for(i=0; i < linemax - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;
  if (c == '\n')
  {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  for( n = i; n < linemax -1; ++n)
    s[n] = '\0';
  return i;
}

int wordwrap(int start, int width, char line[], char selection[])
{
  int i, br;
  i = start + width - 1;
  br = 0;
  
  while(i >= start)
  {
    if( line[i] == ' ' || line[i] == '\t' )
    {
      br = i - start;
      copystr(start, br, line, selection);
      selection[br + 1] = '\n';
      selection[br + 2] = '\0';
      return br;
    }
    else if( line[i] == '\n' )
    {
      br = i - start;
      copystr(start, br, line, selection);
      selection[br + 1] = '\0';
      return 0;
    }
    else
      --i;
  }
  if( i < start )
  {
      br = width - 1;
      copystr(start, br, line, selection);
      selection[br + 1] = '\n';
      selection[br + 2] = '\0';
      return br;
  }
 }

void copystr( int start, int length, char from[], char to[])
{
  int i;
  for( i = 0; i <= length; ++i)
    to[i] = from[i + start];
}
