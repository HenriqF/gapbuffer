#include "gap.h"
#include "rw/readwrite.h"

int main(){
    GapBuffer gb;
    initGb(&gb, (size_t)1);

    FILE* f = fopen("_/a.txt", "rb");
    size_t size;
    char* content;
    readFile(f, &size, &content);
    fclose(f);
    insertString(&gb, content, size);
    renderBuff(gb, 1);

    
   // insertChar(&gb, 'a');
    moveLeft(&gb);
    moveLeft(&gb);
    moveLeft(&gb);
    moveLeft(&gb);
    moveLeft(&gb);
    moveLeft(&gb);
    insertChar(&gb, 'a');
    renderBuff(gb, 1);



    char* result = getText(gb);
    f = fopen("_/a.txt", "wb");
    writeFile(f, result);
    fclose(f);

    return 0;
}