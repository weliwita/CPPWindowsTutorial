#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>

int score_prob(int sem,int ho, int aw);

int main()
{
    int i,j,k,a,b,c,n,sc,shome=0,saway=0;
    int p[64][64],numOfTeam,numOfPlayer,z,ho,aw;
    int t[64],h,w,sem,tand;

    printf("Number Of Team  : ");scanf("%d",&numOfTeam);
    printf("Number Of Player: ");scanf("%d",&numOfPlayer);

    for(i=0;i<numOfTeam;i++)
    {
        z = 0;
        printf("\n\n");
        printf("Teamm %d \n",i+1);
        for(j=0;j<numOfPlayer;j++)
        {
            printf(". PLayer %d : " ,(j+1));scanf("%d",&p[i][j]);
            z += p[i][j];
        }
        printf("Stat of team %d = %d",i+1,z);
        t[i] = z;
    }
    srand(time(NULL));

    do
    {
        k = 0;
        printf("\n\n");
        printf("Home Team Number: ");scanf("%d",&a);a = a - 1;
        printf("Away Team Number: ");scanf("%d",&b);b = b - 1;
        for(i=0;i<90;i++)
        {
            i += 4;
            printf("\nMinute %d: ",i+1);
            {
                sem  = t[a] + t[b];
                ho=t[a];aw=t[b];

                sc = score_prob(sem,ho,aw);
                printf("\n              %d\n",score_prob(sem,t[a],t[b]));
                if(sc == 0)
                {
                    shome += 1;
                    printf("Home Score\n");printf(" %d VS %d ",shome,saway);
                }else if(sc == 2)
                {
                    printf(" %d VS %d ",shome,saway);
                }
                else{
                    saway += 1;
                    printf("Away Score\n");printf(" %d VS %d ",shome,saway);
                }
            }
        }
    }while(k == 0);
    return 0;
}

int score_prob(int sem,int ho, int aw)
{
   int st,aa,nn,sr=0,sh=0,sa=0,home,away;
   time_t t;
   sh=0;sa=0;
   aw = aw / 2; ho = ho / 2;
   srand((unsigned) time(&t));

   for(nn=0;nn<sem;nn++)
   {
        aa = rand() % sem;
        if(aa<ho)
        {
            sh += 1;
        }
        if(aa>(aa - aw))
        {
            sa += 1;
        }
        if(aa!=(aa<ho) && aa != (aa<(aa-aw)))
        {
            sr +=1;
        }
   }

   if(sr != 0)
   {
       if(sh<sa)
       {
           st = 1;
       }
       else
       {
           st = 0;
       }
   }
   else
   {
       st = 2;
   }

   return st;
}