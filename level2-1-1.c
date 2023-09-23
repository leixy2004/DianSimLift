#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
// #define __FCFS
#define true (1)
#define false (0)
#define MAXNUM (512)
#define INF (0x3f3f3f3f)
#define MAX(a,b) (((a)>(b)) ? (a) : (b))
#define MIN(a,b) (((a)<(b)) ? (a) : (b))

void swap(int *a,int *b) {
    int t=*a;*a=*b;*b=t;
}

const int PeoLimit = 4;

int NowLevel=0,NowPeople=0,NowTime=0,NowDirect=0;

void Move(int Direction) {
    NowTime+=1;
    NowLevel+=Direction;
}

void PrintState() {
    printf("Level:%2d  Time:%2d  People:%2d  State:%s\n",
             NowLevel,  NowTime,  NowPeople,
             (NowDirect==0 ? "Stop" : (NowDirect==1 ? "Up" : "Down")));
}
// const int MAXNUM = 64;

int RecALevel[MAXNUM],RecBLevel[MAXNUM],RecPushTime[MAXNUM];
// int Idx(int x) {
//     return x%MAXNUM;
// }
int RecCnt=0,RecNow=0;
// int WaitNum[11];
// void UpdNum() {
//     if (RecPushTime[Idx(RecNow+1)]==NowTime) {

//     }
// }

typedef struct ListNODE {
    int type,level,id;
    struct ListNODE *prev,*next;
} Node;
Node *head=NULL;

void CreateNode(int type,int level,int id) {
    Node *tmp=(Node *)malloc(sizeof (Node));
    tmp->level=level,tmp->type=type,tmp->id=id;
    tmp->prev=NULL,tmp->next=head;
    if (head) head->prev=tmp;
    head=tmp;
}

Node* RemoveNode(Node *t) {
    if (!t) return NULL;
    if (t->prev) {
        t->prev->next=t->next;
    } else {
        head=t->next;
    }
    if (t->next) {
        t->next->prev=t->prev;
    }
    Node *tmp=t->next;
    free(t);
    return tmp;
}

// int read() {
//     char c=0;
//     for (;!isdigit(c);c=getchar()) { }
//     int res=0;
//     for (;isdigit(c);c=getchar()) {
//         res=res*10+c-'0';
//     }
//     return res;
// }

int main() {
    // freopen("people.in","r",stdin);
    int InitLevel;
    // scanf("%d",&InitLevel);
    // InitLevel=read();
    printf("Please input Lift's InitLevel and Number of People FIRST.\n");
    scanf("%d%d",&InitLevel,&RecCnt);
    NowLevel=InitLevel;
    for (int i=0;i<RecCnt;i++) {
        scanf("%d%d%d",&RecALevel[i],&RecBLevel[i],&RecPushTime[i]);
    }
    // int ALevel,BLevel,PushTime;
    // while (scanf("%d%d%d",&ALevel,&BLevel,&PushTime)!=EOF) {
    //     RecALevel[RecCnt]=ALevel,RecBLevel[RecCnt]=BLevel,RecPushTime[RecCnt]=PushTime;
    //     RecCnt+=1;
    // }
    // puts("InputCompleted.");
    // printf("RecCnt:%d\n",RecCnt);
    for (int i=0;i<RecCnt;i++) { // bubble sort
        for (int j=i;j<RecCnt-1;j++) {
            if (RecPushTime[j]>RecPushTime[j+1]) {
                swap(&RecALevel[j],&RecALevel[j+1]);
                swap(&RecBLevel[j],&RecBLevel[j+1]);
                swap(&RecPushTime[j],&RecPushTime[j+1]);
            }
        }
    }
    // puts("SortCompleted.");
    // for (int i=0;i<RecCnt;i++) {
    //     printf("Rec A:%d B:%d Tim:%d\n",RecALevel[i],RecBLevel[i],RecPushTime[i]);
    // }
    // int MaxPushTime=RecPushTime[RecCnt-1]+10;
    int MaxPushTime=MAXNUM<<2;
    for (NowTime=0;NowTime<MaxPushTime;NowTime++) {
        NowLevel+=NowDirect;
        int IsChanged = false;
        while (RecNow<RecCnt && RecPushTime[RecNow]==NowTime) {
            CreateNode(+1,RecALevel[RecNow],RecNow);
            // printf("AddToOdr:%d\n",RecNow);
            RecNow++;
        }

        // for (Node *now=head;now;now=now->next) {
            
        // }

        for (Node *now=head;now;) {
            if (now->level==NowLevel) {
                // puts("Inside");
                if (now->type == +1 && NowPeople<PeoLimit) {
                    now->type=-1;
                    now->level=RecBLevel[now->id];
                    NowPeople+=1;
                    now=now->next;
                    IsChanged=true;
                } else if (now->type==-1) {
                    NowPeople-=1;
                    now=RemoveNode(now);
                    IsChanged=true;
                } else {
                    // printf("now->level:%d ->type:%d\n",now->level,now->type);
                }
            } else {
                now=now->next;
            }
        }


        int MaxLevel=0,MinLevel=INF;
        for (Node *now=head;now;now=now->next) {
            MaxLevel=MAX(MaxLevel,now->level);
            MinLevel=MIN(MaxLevel,now->level);
        }
        if (MaxLevel==0) {
            if (NowDirect!=0) IsChanged=true;
            NowDirect=0;
        } else if (NowLevel<=MinLevel) {
            if (NowDirect!=+1) IsChanged=true;
            NowDirect=+1;
        } else if (NowLevel>=MaxLevel) {
            if (NowDirect!=-1) IsChanged=true;
            NowDirect=-1;
        } else {
            puts("WRONG");
            NowDirect=0;
        }
        if (IsChanged) PrintState();
    }

    // PrintState();

    return 0;
}