#include <stdlib.h>
#include <stdio.h>

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

void renderBuff(GapBuffer gb){
    printf("[");
    for(size_t i = 0; i < gb.gapl; i++){
        printf("%c",gb.buffer[i]);
    }

    for(size_t i = gb.gapl+1; i < gb.gapr+1; i++){
        printf("_");
    }

    for(size_t i = gb.gapr+1; i < gb.buffer_size; i++){
        printf("%c",gb.buffer[i]);
    }
    printf("]\n");
}


// void grow(GapBuffer* gb){

// }

void insert(GapBuffer* gb, char c){

    if (gb->gapl > gb->gapr){
        printf("wow");
    }

    gb->buffer[gb->gapl] = c;
    gb->gapl++;



}


int main(){
    GapBuffer gb;
    initGb(&gb, (size_t)3);
    insert(&gb, 'a');
    insert(&gb, 'b');
    insert(&gb, 'b');
    insert(&gb, 'c');


    renderBuff(gb);
    return 0;
}