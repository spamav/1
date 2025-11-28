#include<stdio.h>
#include<conio.h>
void main()
{
int np,ps,ms,nop,pa,i,j,x,y,rempage,offset;
int s[10],fno[10][20];
clrscr();
printf("enter memory size");
scanf("%d",&ms);
printf("enter page size");
scanf("%d",&ps);
printf("enter number of processor");
scanf("%d",&np);
nop=ms/ps;
printf("enter number of used process:%d",nop);
rempage=nop;
for(i=1;i<=np;i++)
{
printf("enter number of pages availablep[%d]",i);
scanf("%d",&s[i]);
if(s[i]>rempage)
{
printf("Memory is full");
break;
}
rempage=rempage-s[i];
printf("enter page table for p[%d]:",i);
for(j=0;j<s[i];j++)
scanf("%d",&fno[i][j]);
}
printf("enter logical and physical address");
printf("\nenter the process number and page number and offset");
scanf("%d%d%d",&x,&y,&offset);
if(x>np || y>=s[i] || offset>=ps)
printf("invalid process or page number");
else
{
pa=fno[x][y]*ps+offset;
printf("physical address is%d",pa);
}
getch();



d). Priority Scheduling Algorithm.

Source Code :

#include<stdio.h>

void main()
{
    int i, j, np, temp, P[10], bt[10], wt[10], PP[10], tat[10];
    int total_wt = 0, total_tat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &np);

    printf("Enter the burst time and priority number of each process\n");

    for(i = 0; i < np; i++)
    {
        P[i] = i+1;
        printf("Burst time of Process[%d]: ", P[i]);
        scanf("%d", &bt[i]);
        printf("Priority number of Process[%d]: ", P[i]);
        scanf("%d", &PP[i]);
    }

    for(i = 0; i < np; i++)
    {
        for(j = i+1; j < np; j++)
        {
            if(PP[j] < PP[i])
            {
                temp = PP[j];
                PP[j] = PP[i];
                PP[i] = temp;

                temp = bt[j];
                bt[j] = bt[i];
                bt[i] = temp;

                temp = P[j];
                P[j] = P[i];
                P[i] = temp;
            }
        }
    }

    wt[0] = 0;

    for(i = 0; i < np; i++)
    {
        tat[i] = wt[i] + bt[i];
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        wt[i+1] = tat[i];
    }

    printf("Process\tBT\tPriority\tWT\tTAT\n");

    for(i = 0; i < np; i++)
    {
        printf("Process[%d]\t%d\t%d\t%d\t%d\n",
               P[i], bt[i], PP[i], wt[i], tat[i]);
    }

    printf("Average wait time is : %.2f\n",
           (float) total_wt / (float) np);

    printf("Average turn around time is : %.2f\n",
           (float) total_tat / (float) np);
}
