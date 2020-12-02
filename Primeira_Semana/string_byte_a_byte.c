/* oneChar.c
 * Writes a single character on the screen.
 * 2017-09-29: Bob Plantz
 */

#include <unistd.h>
#include <stdio.h>

int main(void)
{
  
  char aString[200];
  char variavel; //letra (byte)
  int i = 0;
 
  write(STDOUT_FILENO, "Digite alguma coisa: ", 22);
  //printf("\n");

  while(variavel != '\n'){
    read(STDIN_FILENO, &variavel, 1); //pegando letra por letra, lendo byte a byte
    aString[i] = variavel;
    i++;
  }


  printf("Você entrou com: %s", aString);

  
  return 0;
}
