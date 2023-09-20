#include <stdio.h>
#include <math.h>
#define true 1
#define false 0

int NowLevel=0,NowPeople=0,NowTime=0;

void MoveTo(int Level) {
    NowTime+=abs(Level-NowLevel);
    NowLevel=Level;
}

void PrintState() {
    printf("Level:%2d  Time:%2d  People:%2d\n",
            NowLevel, NowTime, NowPeople);
}

int main() {
    int LevelIn,LevelOut,LevelNow;
    scanf("%d%d%d",&LevelIn,&LevelOut,&LevelNow);

    NowLevel=LevelNow;
    PrintState();
    MoveTo(LevelIn);
    PrintState();
    NowPeople+=1;
    MoveTo(LevelOut);
    PrintState();

    return 0;
}