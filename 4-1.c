#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define BUF_SIZE 256

/* 都市の座標構造体 */
struct City {
    int x, y;
};

/* 問題情報構造体 */
struct TSP {
    int N;
    struct City *city;       /* 都市の位置 */
    int *order;             /* 巡回順 */
    float cost;                /* 総移動距離 */
    int *c;                 /*仮巡回順*/
    int *min_order;         /*最小巡回順*/
    float min_cost;         /*最小総距離*/
};

/* 関数の宣言 */
void ReadData(struct TSP *tsp,int n,char name[]);
void ShowData(struct TSP *tsp);
float CalcDistance(struct City a, struct City b);
void FirstOrder(struct TSP *tsp);
void SimpleOrder(struct TSP *tsp,int n);
void CalcCost(struct TSP *tsp);
void ShowCost(struct TSP *tsp);
void CompiarMin(struct TSP *tsp);
void MinOrder(struct TSP *tsp);
void Change(struct TSP *tsp,int i,int j);


/*メイン関数*/
int main(){
    struct TSP tsp;
    int N;
    char name[100];
    printf("都市数を入力してください:");
    scanf("%d",&N);
    sprintf(name,"cities%02d.csv",N);
    ReadData(&tsp,N,name);
    ShowData(&tsp);
    FirstOrder(&tsp);
    SimpleOrder(&tsp,tsp.N);
    MinOrder(&tsp);
    free(tsp.city);
    free(tsp.order);
    free(tsp.min_order);
    return 0;
}

/*都市座標データ読み込み 引数：struct TSP *tsp : TSPデータ*/
void ReadData(struct TSP *tsp,int n,char name[]){
    tsp->N=n;
    /* open file */
    FILE *fp;
    if ((fp = fopen(name,"r"))==NULL){
        printf("Can't open data file.\n");
    }
    int i;
    char buf[BUF_SIZE];
    tsp->min_cost=10000000;
    tsp->city=(struct City*)malloc(sizeof(struct City)*tsp->N*2);
    tsp->order=(int*)malloc(sizeof(int)*tsp->N);
    tsp->min_order=(int*)malloc(sizeof(int)*tsp->N);
    /*データ読み込み*/
    for(i=0;i<tsp->N;i++){
        fgets(buf, BUF_SIZE, fp);
        sscanf(buf,"%4d,%4d\n",&tsp->city[i].x,&tsp->city[i].y);
    }
    fclose(fp);
}

/* 都市座標データ表示 引数：struct TSP *tsp : TSPデータ*/
void ShowData(struct TSP *tsp){
    int j;
    /* データ表示 */
    printf("Cities location:\n");
    for (j = 0; j<tsp->N; j ++) {
        printf("C%-2d : %4d,%4d\n",j + 1, tsp->city[j].x, tsp->city[j].y);
    }
}

void FirstOrder(struct TSP *tsp){
    int k;
    for(k=0;k<tsp->N;k++){
        tsp->order[k]=k;
    }
}

/*巡回順の決定 引数：struct TSP *tsp : TSPデータ*/
void SimpleOrder(struct TSP *tsp,int n){
    int l;
    if(n<=1){
        /*総距離算出*/
        CalcCost(tsp);
        /*巡回順表示*/
        ShowCost(tsp);
        /*最小距離の比較*/
        CompiarMin(tsp);
    }
    else{
        for(l=1;l<n;l++){
            /*順序入れ替え*/
            Change(tsp,l,n-1);
            /*回帰*/
            SimpleOrder(tsp,n-1);
            /*順序復元*/
            Change(tsp,n-1,l);
        }
    }
}
        
    /*巡回順入れ替え*/
void Change(struct TSP *tsp,int x,int y){
    char c;
    c=tsp->order[x];
    tsp->order[x]=tsp->order[y];
    tsp->order[y]=c;
}
    
void MinOrder(struct TSP *tsp){
    int z;
    /*最小距離の表示*/
    printf("min-distance : %f\n",tsp->min_cost);
    /*最小巡回順の表示*/
    printf("min-coast :\n");
    for (z=0;z<tsp->N;z++){
        printf("C%2d> ",tsp->min_order[z]+1);
    }
    printf("C%2d\n",tsp->min_order[0]+1);
    /*逆順の表示*/
    printf("C%2d> ",tsp->min_order[0]+1);
    for (z=(tsp->N)-1;z>0;z--){
        printf("C%2d> ",tsp->min_order[z]+1);
    }
    printf("C%2d\n",tsp->min_order[0]+1);
}

/*総移動距離を計算する 引数：struct TSP *tsp : TSPデータ*/
void CalcCost(struct TSP *tsp){
    int a;
    float total_dist=0;
    /* 巡回距離計算 */
    for(a=0;a<(tsp->N);a++){
        if(a==(tsp->N)-1){
            total_dist+=sqrt(((tsp->city[tsp->order[a]].x-tsp->city[0].x)*(tsp->city[tsp->order[a]].x-tsp->city[0].x))+((tsp->city[tsp->order[a]].y-tsp->city[0].y)*(tsp->city[tsp->order[a]].y-tsp->city[0].y)));
        }
        else
            total_dist+=sqrt(((tsp->city[tsp->order[a+1]].x-tsp->city[tsp->order[a]].x)*(tsp->city[tsp->order[a+1]].x-tsp->city[tsp->order[a]].x))+((tsp->city[tsp->order[a+1]].y-tsp->city[tsp->order[a]].y)*(tsp->city[tsp->order[a+1]].y-tsp->city[tsp->order[a]].y)));
    }
    tsp->cost=total_dist;
}

/*２都市間の距離を計算 引数：struct City a : 都市1   引数：struct City b : 都市2  戻り値：距離*/
float CalcDistance(struct City a, struct City b){
    return sqrt(((b.x)*(a.x))+((b.y)*(a.y)));
}

/*巡回順と総移動距離を表示  引数：struct TSP *tsp : TSPデータ */
void ShowCost(struct TSP *tsp){
    int b;
    for (b=0;b<tsp->N;b++){
        printf("C%-2d> ",tsp->order[b]+1);
    }
    printf("C%2d  cost=%7.1f\n", tsp->order[0] + 1, tsp->cost);
}

void CompiarMin(struct TSP *tsp){
    int d;
    if(tsp->cost<tsp->min_cost){
        tsp->min_cost=tsp->cost;
        for(d=0;d<tsp->N;d++){
            /*最小値時の巡回順の入手*/
            tsp->min_order[d]=tsp->order[d];
        }
    }
}
