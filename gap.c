#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "rw/readwrite.h"

#define RED "\x1b[31m"
#define RESET "\x1b[0m"

typedef struct{
    char* buffer;
    size_t buffer_size;

    size_t gap_size;
    size_t gapl;
    size_t gapr;

} GapBuffer;

void initGb(GapBuffer* gb, size_t gap_size){
    gb->buffer = calloc(gap_size, gap_size*sizeof(char));
    gb->buffer_size = gap_size;
    gb->gap_size = gap_size;
    gb->gapl = 0;
    gb->gapr = gap_size-1;
}

void printValid(char c){
    if (isprint(c)) printf("%c",c);
    else printf("_");
}

void renderBuff(GapBuffer gb){
    printf("[");
    for(size_t i = 0; i < gb.gapl; i++){
        printValid(gb.buffer[i]);
    }

    for(size_t i = gb.gapl; i < gb.gapr+1; i++){
        printf(RED);
        printValid(gb.buffer[i]);
        printf(RESET);
    }

    for(size_t i = gb.gapr+1; i < gb.buffer_size; i++){
        printValid(gb.buffer[i]);
    }
    printf("]\n");
}

void grow(GapBuffer* gb){
    
    gb->buffer = realloc(gb->buffer, gb->buffer_size+gb->gap_size);
    gb->buffer_size += gb->gap_size;

    for (size_t i = gb->gapr; i < gb->buffer_size; i++){
        gb->buffer[i+gb->gap_size] = gb->buffer[i];
    }
    gb->gapr += gb->gap_size;
    gb->buffer[gb->gapr] = 0;

    // if (gb->gapr == gb->buffer_size-1){
    //     gb->buffer[gb->gapr] = 0;
    // }
}

void insert(GapBuffer* gb, char c){
    if (gb->gapl > gb->gapr){
        grow(gb);
    }

    gb->buffer[gb->gapl] = c;
    gb->gapl++;

}

void insertText(GapBuffer* gb, char* text, size_t size){
    for (size_t i = 0; i < size; i++){
        insert(gb, text[i]);
    }
}

void moveLeft(GapBuffer* gb){
    if (gb->gapl == 0){
        return;
    }

    gb->gapl--;
    char temp = gb->buffer[gb->gapl];
    gb->buffer[gb->gapl] = gb->buffer[gb->gapr];
    gb->buffer[gb->gapr] = temp;
    gb->gapr--;
}

void moveRight(GapBuffer* gb){
    if (gb->gapr == gb->buffer_size-1){
        return;
    }

    gb->gapr++;
    char temp = gb->buffer[gb->gapr];
    gb->buffer[gb->gapr] = gb->buffer[gb->gapl];
    gb->buffer[gb->gapl] = temp;
    gb->gapl++;
}



int main(){
    GapBuffer gb;
    initGb(&gb, (size_t)20);

    FILE* f = fopen("_/a.txt", "rb");
    size_t size;
    char* content;
    readFile(f, &size, &content);
    fclose(f);

    insertText(&gb, content, size);
    renderBuff(gb);

    return 0;
}