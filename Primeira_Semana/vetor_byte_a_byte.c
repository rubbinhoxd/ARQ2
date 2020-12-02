#include <unistd.h>
#include <stdio.h>

int main(){
    char vetor1[5000], variavel; //byte a byte
    int vetor2[5000], variavel2;  //byte a byte
    int aux = 0, aux2 = 0;
    
    int buff = 0; //variavel inteira que irá armazenar variaveis do tipo char

    while (1) {
        read(STDIN_FILENO, &variavel, 1);
        if (variavel == ' ') {
            vetor2[variavel2++] = buff;
            buff = 0;
            continue;
        } else if (variavel == '\n') {
            vetor2[variavel2++] = buff;
            break;
        }
        buff = buff * 10 + (int)(variavel-'0');
    }

    for (int i = 0; i < variavel2; ++i) {
        aux += vetor2[i];
        aux2 += vetor2[i];
    }

    variavel2 = 0;
    while (aux2 > 0) {
        ++variavel2;
        aux2/=10;
    }

    if (variavel2 == 0) variavel2 = 1;
    for (int i = variavel2-1; i >= 0; --i) {
        vetor1[i] = (char)(aux % 10 + '0');
        aux /= 10;
    }
    vetor1[variavel2++] = '\n';

    write(STDOUT_FILENO, &vetor1, variavel2);

    return 0;
}
