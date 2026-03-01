#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
    // printf("[%s]  ", gb.buffer);


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
    char* temp = realloc(gb->buffer, gb->buffer_size+gb->gap_size);
    gb->buffer = temp;
    gb->buffer_size += gb->gap_size;

    for (size_t i = gb->buffer_size-1; i > gb->buffer_size-gb->gap_size; i--){
        gb->buffer[i] = 0;
    }

    if (gb->gapr < gb->buffer_size-gb->gap_size-1){
        size_t afteri = gb->gapl+1;
        size_t aftere = gb->buffer_size-gb->gap_size-1;
        size_t l = aftere-afteri+1;

        memmove(gb->buffer+(gb->buffer_size-l), gb->buffer+afteri, l);
        memset(gb->buffer+afteri, '\0', l);
    }

    gb->gapr += gb->gap_size;
}

void insert(GapBuffer* gb, char c){
    if (gb->gapl == gb->gapr){
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
    insertText(&gb, content, size);
    renderBuff(gb);
    insertText(&gb, content, size);
    renderBuff(gb);

    // insert(&gb, 'a');
    // renderBuff(gb);

    // insert(&gb, 'b');
    // renderBuff(gb);

    // insert(&gb, 'c');
    // renderBuff(gb);

    // moveLeft(&gb);
    // renderBuff(gb);

    // moveLeft(&gb);
    // renderBuff(gb);
    
    // insert(&gb, 'd');
    // renderBuff(gb);

    // insert(&gb, 'e');
    // renderBuff(gb);

    // insert(&gb, 'f');
    // renderBuff(gb);
    return 0;
}