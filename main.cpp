#include <stdio.h>
#include <stdlib.h>
#define RAMSIZE 8
#define WORDSIZE 1
#define PAGESIZE 4

struct pageTableElement
{
    int adress;
    int valid;
};

int p;
struct pageTableElement *table;
FILE *fp;
char frame[PAGESIZE];
char RAM[RAMSIZE*PAGESIZE];
char buffer[PAGESIZE];
int RAMtable[PAGESIZE];
void runProgram();
char getWord(int);

int main(int argc, char *argv[])
{
    int i = 0;

    fp = fopen("program.txt", "r");
        table= (struct pageTableElement*)malloc(sizeof(struct pageTableElement)*(400/PAGESIZE));
    for(; i < 100; i++)
    {
        table[i].valid = 0;
    }

    runProgram();
    return 0;
}

void runProgram()
{
    p=0;
    int i = 0;

    for(; i < 400; i++)
    {
        //getWord(i);
        printf("%c", getWord(i));
    }
    printf("\n");
}

char getWord(int i)
{
    int page = i/PAGESIZE;
    if(table[page].valid)
    {
        return RAM[table[page].adress+(i%PAGESIZE)];
    }
    else
    {
        if(p==PAGESIZE*RAMSIZE) p=0;
        fseek(fp,i,SEEK_SET);
            fread(buffer,1,PAGESIZE,fp);

            if(RAMtable[p/PAGESIZE]!=0)
                table[RAMtable[p/PAGESIZE]].valid=0;

            RAMtable[p/PAGESIZE]=page;

            table[page].valid=1;
            table[page].adress=p;

            int j=0;
            for(;j<PAGESIZE;j++)
                RAM[p+j]=buffer[j];

            //printf("%c%c%c%c\n",RAM[p],RAM[p+1],RAM[p+2],RAM[p+3]);
            p+=PAGESIZE;
            return getWord(i);
        }
    }
