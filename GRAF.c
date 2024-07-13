#include <stdio.h>
#include <stdlib.h>
/*   DFS GRAPH VERÝ YAPISI                */
int source,V,E,time,visited[20],G[20][20];
void DFS(int i)
{
    int j;
    visited[i]=1;
    printf(" %d->",i+1);
    for(j=0;j<V;j++)
    {
        if(G[i][j]==1&&visited[j]==0)
            DFS(j);
    }
}
int main()
{
	
    int i,j,v1,v2;
    printf("\t\t\t**** GRAF VERI YAPISI ****\n");
    printf("DUGUM SAYISINI GIRINIZ:");
    scanf("%d",&E);
    printf("KENAR SAYISINI GIRINIZ:");
    scanf("%d",&V);
    for(i=0;i<V;i++)
    {
        for(j=0;j<V;j++)
            G[i][j]=0;
    }
    /*    KENARLARI OLUÞTURUYORUZ :P    */
    for(i=0;i<E;i++)
    { 
    /*HOCAM KENARLARI (7,3),(3,6),(6,9),(9,8),(8,2),(2,0),(2,1),(9,1) OLACAK ÞEKÝLDE GÝRÝNÝZ*/
        printf("KENARLARI GIRINIZ (format: V1 V2) : ");
        scanf("%d%d",&v1,&v2);
        G[v1-1][v2-1]=1;

    }

    for(i=0;i<V;i++)
    {
        for(j=0;j<V;j++)
            printf(" %d ",G[i][j]);
        printf("\n");
    }
    //BAÞLANGIÇ DÜÐÜMÜNÜ 7 OLARAK BELÝRLEDÝM 
    printf("BASLANGIC DUGUMUNU GIRINIZ: ");
    scanf("%d",&source);
        DFS(source-1);
    return 0;
}
