/*巡回セールスマン問題を発見的解法を使用して解く*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define BUF_SIZE 256

/*都市の座標構造体*/
struct City {
    int x, y;
};

/*問題情報構造体*/
struct TSP {
    int N;                  /*都市数*/
    struct City *city;      /* 都市の位置 */
    int *currentOrder;      /*元の巡回順*/
    int *changedOrder;      /*変更後の巡回順*/
    int *min_order;         /*仮最小巡回順*/
    float min_cost;         /*仮最小総距離*/
    int *minimumorder;         /*仮最小巡回順*/
    float minimumcost;         /*仮最小総距離*/
};

/*都市座標データ読み込み*/
void ReadData(struct TSP *tsp,int n,char name[]){
    tsp->N=n;
    /* open file */
    FILE *fp;
    if ((fp = fopen(name,"r"))==NULL){
        printf("Can't open data file.\n");
    }
    int i;
    char buf[BUF_SIZE];
    /*データ読み込み*/
    for(i=0;i<tsp->N;i++){
        fgets(buf, BUF_SIZE, fp);
        sscanf(buf,"%4d,%4d\n",&tsp->city[i].x,&tsp->city[i].y);
    }
    fclose(fp);
}

/*初回巡回順を乱数を使用してランダムに決定*/
void FirstOrder(struct TSP *tsp){
    int k;
    for(k=0;k<tsp->N;k++){
        tsp->currentOrder[k]=k;
    }
    int i=tsp->N;
    while(i>1){
        srand((unsigned)time(NULL));
        int j=rand()%i;
        i--;
        int t=tsp->currentOrder[i];
        tsp->currentOrder[i]=tsp->currentOrder[j];
        tsp->currentOrder[j]=t;
    }
}

/*巡回順のコピー*/
void CopyOrder(struct TSP *tsp){
    int k;
    for(k=0;k<tsp->N;k++){
        tsp->changedOrder[k]=tsp->currentOrder[k];
    }
}

/*巡回順のx1番目からx2番目までを入れ替え*/
void TwoOpt(struct TSP *tsp, int x1, int x2){
    /*初期値代入*/
    CopyOrder(tsp);
    /*始点終点入れ替え*/
    do{
        int i=tsp->changedOrder[x1];
        tsp->changedOrder[x1]=tsp->changedOrder[x2];
        tsp->changedOrder[x2]=i;
        x2--;
        x1++;
    }while(x1<x2);
}

/*２都市間の距離を計算する*/
float CalcDistance(struct City a, struct City b){
    return sqrt(pow((a.x-b.x),2)+pow((a.y-b.y),2));
}

/*総移動距離の計算*/
float CalcCost(struct TSP *tsp){
    int a;
    float total_dist=0;
    /* 巡回距離計算 */
    for(a=0;a<(tsp->N);a++){
        if(a==(tsp->N)-1){
            total_dist+=CalcDistance(tsp->city[tsp->changedOrder[a]],tsp->city[tsp->changedOrder[0]]);
        }
        else
            total_dist+=CalcDistance(tsp->city[tsp->changedOrder[a+1]],tsp->city[tsp->changedOrder[a]]);
    }
    return total_dist;
}

/*総距離を最小値と比較し，仮の最小距離と最小巡回順を更新する*/
int UpdateOrder(struct TSP *tsp, int x1, int x2){
    int d;
    TwoOpt(tsp,x1, x2);
    if(CalcCost(tsp)<tsp->min_cost){
        tsp->min_cost=CalcCost(tsp);
        for(d=0;d<tsp->N;d++){
            /*最小値時の巡回順の入手*/
            tsp->currentOrder[d]=tsp->changedOrder[d];
        }
        return 1;
    }
    else
        return 0;
}

/*メイン関数*/
int main(){
    struct TSP tsp;
    int N;
    char name[100];
    printf("都市数を入力してください:");
    scanf("%d",&N);
    sprintf(name,"cities%02d.csv",N);
    
    /*動的配列の確保*/
    tsp.city=(struct City*)malloc(sizeof(struct City)*N*2);
    tsp.currentOrder=(int*)malloc(sizeof(int)*N);
    tsp.changedOrder=(int*)malloc(sizeof(int)*N);
    tsp.min_order=(int*)malloc(sizeof(int)*N);
    tsp.minimumorder=(int*)malloc(sizeof(int)*N);
    
    ReadData(&tsp,N,name);
    FirstOrder(&tsp);
    CopyOrder(&tsp);
    tsp.min_cost=CalcCost(&tsp);
    tsp.minimumcost=CalcCost(&tsp);
    
    int n;
    printf("ループ回数:");
    scanf("%d",&n);
    
    /*最急降下法の実行*/
    for(int j=0;j<n;j++){
        /*初期値の設定*/
        FirstOrder(&tsp);
        CopyOrder(&tsp);
        tsp.min_cost=CalcCost(&tsp);
        /*巡回順の入れ替えを全パターン行う*/
        int x1,x2,update=1;
        while(update!=0){
            update=0;
            for(x1=0;x1<N-1;x1++){
                for(x2=x1+1;x2<N;x2++){
                    if(UpdateOrder(&tsp,x1,x2)==1){
                        update++;                    }
                }
            }
        }
        /*総距離を最小値と比較し，最終的な最小距離と最小巡回順を更新する*/
        if(tsp.min_cost<tsp.minimumcost){
            tsp.minimumcost=tsp.min_cost;
            printf("%f\n",tsp.minimumcost);
            for(int i=0;i<tsp.N;i++){
                /*最小値時の巡回順の入手*/
                tsp.minimumorder[i]=tsp.currentOrder[i];
            }
        }
    }
    /*最小巡回順の表示*/
    printf("mincost:\n");
    for (int i=0;i<N-1;i++){
        printf("%-2d-",tsp.minimumorder[i]);
    }
    printf("%2d\n",tsp.minimumorder[N-1]);
    /*最小総距離の表示*/
    printf("mincost: %f\n",tsp.minimumcost);
    /*ending*/
    free(tsp.city);
    free(tsp.currentOrder);
    free(tsp.changedOrder);
    free(tsp.min_order);
    free(tsp.minimumorder);
    return 0;
}
