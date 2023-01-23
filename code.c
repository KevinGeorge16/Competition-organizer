#include<stdio.h>
#include<string.h>
#include<math.h>
struct ptpnt
{
    char name[50];
    int points;
    int pos;
}participant[100];
char stack[100][50];

struct ranker
{
    int ids;
    int point;
}ranks[100];

int top=-1,max=100;
void insert()
{
    if(top>=max-1)
    {
        printf("\nNumber of participants exceeded");
    }
    else
    {
        top++;
        printf("\nEnter participant %d's name: ",top+1);
        scanf("%s",&participant[top].name);
        strcpy(stack+top,participant[top].name);
        printf("Registered %s \n",stack+top);
        participant[top].pos = top;
        participant[top].points = 0;
        ranks[top].ids= top;
        ranks[top].point = participant[top].points;
    }
}
void check(char x[50])
{
    char temp[50];
    int ck = 0;
    while(ck==0)
    {
        for(int a=0;a<=top;a++)
                {
                    if(strcmpi(x,participant[a].name)==0)
                    {
                        participant[a].points++;
                        ranks[participant[a].pos].point=participant[a].points;
                        ck =1;
                    }
                }
        if(ck==0)
        {
            printf("\n Invalid name ;type again: ");
            scanf("%s",&temp);
            strcpy(x,temp);
        }
    }
}
void swap(int a,int b)
 {
 int temp = ranks[a].point;
 ranks[a].point = ranks[b].point;
 ranks[b].point = temp;
 int temp2 = ranks[a].ids;
 ranks[a].ids = ranks[b].ids;
 ranks[b].ids = temp2;
 int temp3 = participant[ranks[a].ids].pos;
 participant[ranks[a].ids].pos = participant[ranks[b].ids].pos;
 participant[ranks[b].ids].pos = temp3;
 }
void heapify(int n, int i)
{
 int largest = i;
 int left = 2 * i + 1;
 int right = 2 * i + 2;
 if (left < n && ranks[left].point > ranks[largest].point)
    largest = left;
 if (right < n && ranks[right].point > ranks[largest].point)
    largest = right;
 if (largest != i)
    {
    swap(i, largest);
    heapify(n, largest);
    }
 }
void heapSort()
 {
     int m = top+1;
 for (int i = m / 2 - 1; i >= 0; i--)
 {
 heapify(m, i);
 }
 for (int i = m - 1; i >= 0; i--)
 {
 swap(0,i);
 heapify(i, 0);
 }
 }

 void displayranks()
 {
 for (int i = top; i >= 0; i=i-1)
 {
 printf("\n Rank %d ---> Participant %s points - %d ",top+1-i,participant[ranks[i].ids].name,participant[ranks[i].ids].points);
 }
 }

void knockout()
{
    char twinner[50];
    int temp,game=1,ko =1,o=0,jk;
    int rounds=ceil(log(top+1)/log(2));
    jk = top+1;
    printf("\n Number of rounds = %d",rounds);
    for(int h = 1; h<=rounds;h++)
    {
        if((jk%2) == 0)
        {
        printf("\nxx Fixtures for round %d xx\n",h);
        for(int u =o;u<=top-1;u+=2)
        {
         printf("\nGame %d : %s VS %s",game,participant[ranks[u].ids].name,participant[ranks[u+1].ids].name);
         game++;
        }
        printf("\nPlease enter results of round %d",h);
        for(int y=ko;y<game;y++)
        {
            printf("\nGame %d: ",y);
            scanf("%s",twinner);
            check(twinner);
            heapSort();
        }
        printf("\n Ranks at the end of the round : ");
        displayranks();
        ko = game;
        jk = (jk+1)/2;
        o = top+1 -jk;
        }
        else if((jk%2)!=0)
        {
             printf("\nxx Fixtures for round %d xx\n",h);
            for(int u =o;u<=top-1;u+=2)
            {
                printf("\nGame %d : %s VS %s",game,participant[ranks[u].ids].name,participant[ranks[u+1].ids].name);
                game++;
            }
            printf("\n%s Gets a by to the next round.",participant[ranks[top].ids].name);
            check(participant[ranks[top].ids].name);
            heapSort();
            printf("\nPlease enter results of round %d",h);
            for(int y=ko;y<game;y++)
            {
                printf("\nGame %d: ",y);
                scanf("%s",twinner);
                check(twinner);
                heapSort();
                displayranks();
            }
        ko = game;
        jk = (jk+1)/2;
        o = top+1-jk;
        }
    }
    printf("\n \n WINNER OF THE TOURNAMENT IS %s\n",participant[ranks[top].ids].name);
}
void print()
{
    for(int f = 0; f <= top ; f++)
        printf("%s -> ",stack + f);
}

void cycle(int arr[])
{
    int n;
    n=top;
    int temp;
    for(int g=n-1;g>=1;g--)
    {
        temp = arr[g];
        arr[g]=arr[n];
        arr[n]=temp;
    }
}
void league()
{
    int number = top+1,game=1;
    int rounds,ko=1;
    char twinner[50];
    int legray[number];
        for (int h=0;h<number;h++)
        {
            legray[h]=h;
        }
    if (number%2 == 0)
    {
        rounds = number-1;
        for(int k =1;k<= rounds;k++)
        {
            printf("\nxx FIXTURES FOR ROUND - %d xx\n",k);
            for(int y=0;y<(number/2);y++)
            {
              printf("GAME %d: %s VS %s \n",game,participant[legray[y]].name,participant[legray[top-y]].name);
              game++;
            }
            printf("\nPlease enter results of round %d",k);
            for(int y=ko;y<game;y++)
            {
                printf("\nGame %d: ",y);
                scanf("%s",twinner);
                check(twinner);
                heapSort();
            }
            printf("\n Ranks at the end of the round : ");
            displayranks();
            ko = game;
            cycle(legray);
        }
    }
    else
    {
        rounds = number;
        for(int k =1;k<= rounds;k++)
        {
            printf("\nxx FIXTURES FO ROUND - %d xx\n",k);
            for(int y=0;y<(number/2);y++)
            {
              printf("GAME %d: %s VS %s \n",game,participant[legray[y]].name,participant[legray[top-y]].name);
              game++;
            }
            printf("--> %s GETS A BY THIS ROUND -->\n",participant[legray[number/2]].name);
            printf("\nPlease enter results of round %d",k);
            for(int y=ko;y<game;y++)
            {
                printf("\nGame %d: ",y);
                scanf("%s",twinner);
                check(twinner);
                heapSort();
            }
            printf("\n Ranks at the end of the round : ");
            displayranks();
            ko = game;
            cycle(legray);
        }
    }
}
int main()
{
    int type,type1,choice;
    printf("\nPlease enter the type of tournament: \n1)League \n2)Knockout\n");
    do{
    scanf("%d",&type1);
    switch(type1)
    {
    case 1:
        printf("\n#You have chosen League tournament#\n");
        break;
    case 2:
        printf("\n#You have chosen Knockout tournament#\n");
        break;
    default:
        printf("X INVALID INPUT , Type again :");
        break;
    }
    }while((type1 != 1) & (type1 != 2));
    printf("\n xx REGISTRATION xx \n");
    printf("1)Add participant\n2)Complete Registration \n");
    do
    {
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            insert();
            break;
        case 2:
            printf("\nxx Completed registration xx\n");
            break;
        default:
            printf("\n Invalid input, Type again: \n");
            break;
        }
    }while(choice != 2);
    print();
    if(type1==1)
        league();
    else
        knockout();
}

