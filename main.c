#include "gap.h"
#include "rw/readwrite.h"

int main(){
    GapBuffer gb;
    initGb(&gb, (size_t)10);

    FILE* f = fopen("_/a.txt", "rb");
    size_t size;
    char* content;
    readFile(f, &size, &content);
    fclose(f);
    insertString(&gb, content, size);
    renderBuff(gb);


    insertChar(&gb, 'a');
    renderBuff(gb);

    char* result = getText(gb);
    f = fopen("_/a.txt", "wb");
    writeFile(f, result);
    fclose(f);

    return 0;
}