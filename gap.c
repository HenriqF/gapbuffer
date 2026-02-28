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
    //printf("(%lld, %lld)", gb.gapl, gb.gapr);
    printf("[");
    for(size_t i = 0; i < gb.gapl; i++){
        printf("%c",gb.buffer[i]);
    }

    for(size_t i = gb.gapl; i < gb.gapr+1; i++){
        if (gb.buffer[i]) printf("%c",gb.buffer[i]);
        else printf("_");
        
    }

    for(size_t i = gb.gapr+1; i < gb.buffer_size; i++){
        printf("%c",gb.buffer[i]);
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

    if (gb->gapr == gb->buffer_size-1){
        gb->buffer[gb->gapr] = 0;
    }
}

void insert(GapBuffer* gb, char c){
    if (gb->gapl > gb->gapr){
        grow(gb);
    }

    gb->buffer[gb->gapl] = c;
    gb->gapl++;
    renderBuff(*gb);
}


int main(){
    GapBuffer gb;
    initGb(&gb, (size_t)3);


    for (int i = 0; i < 26; i++){
        insert(&gb, (char)i+97);

        if (i % 7 == 0 && i != 0 ){
            //printf("volta");
            gb.gapl = i/7;
        }
    }
    
    return 0;
}