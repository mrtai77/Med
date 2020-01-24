/*乱数で数列を入手し，それを大きさ順に並び替え，平均値を求める*/

#include <stdio.h>
#include <stdlib.h>

/*渡された，乱数により並べられた配列を，大きさを降順に並び替える*/
void sort(int values[],int count){
    int i=0,j;
    while(i<count){
        for(j=0;j<count;j++){
            if (values[i]<values[j]){
                    int temp=values[j];
                    values[j]=values[i];
                    values[i]=temp;
                }
        }
        i++;
    }
    printf("sort:");
    for(j=0;j<count;j++){
        printf("%d ",values[j]);
    }
    printf("\n");
}

/*渡された配列ないの数値の平均値を求める*/
void average(int a[],int n){
    int b,c=0;
    for(b=0;b<n;b++){
            c=c+a[b];
        }
    printf("average=%4.1f\n",c/20.0);
}

int main(){
    const int N=20;
    const int VALUE_MAX=100;
    int values[N];
    int i;
    printf("values:");
    for (i=0;i<N;i++){
        values[i]=rand()%VALUE_MAX;
        printf("%d ",values[i]);
    }
    printf("\n");
    sort(values,N);
    average(values,N);
}


