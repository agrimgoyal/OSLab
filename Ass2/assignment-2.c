// Agrim Goyal 102215080
#include <stdio.h>

int main() {
    FILE *fin = fopen("example.txt", "r"), *fout = fopen("encrypted.txt", "w");
    char ch;
    char key = 'K'; // Simple XOR key
    while ((ch = fgetc(fin)) != EOF) {
        fputc(ch ^ key, fout); // Write encrypted char
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
