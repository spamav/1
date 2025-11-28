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
}
