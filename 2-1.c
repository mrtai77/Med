/*呼吸波形データを読み込み微分の要素を用いてR波周期や，それに基づき呼吸周期を検出する*/
#include <stdio.h>
#include <stdlib.h>
#define BUF_SIZE 256

int main(){
/* open file */
    FILE *fp;
    if ((fp = fopen("ecg4000.txt","r"))==NULL){
        printf("Can't open data file.\n");
        return 1;
    }

/* read data */
    int N,i,j;
    char buf[BUF_SIZE];
    /*ファイルの一行目を入手*/
    fgets(buf, BUF_SIZE, fp);
    sscanf(buf,"%d\n", &N);
    /*動的配列の確保*/
    float *etime=(float*)malloc(sizeof(float)*N);
    int *resp=(int*)malloc(sizeof(int)*N);
    /*データのコピー*/
    for(i=0;i<N;i++){
        fgets(buf, BUF_SIZE, fp);
        sscanf(buf,"%f,%d\n", &etime[i], &resp[i]);
    }
    /*動的配列の確保*/
    float *respma=(float*)malloc(sizeof(float)*N);
    float *diff=(float*)malloc(sizeof(float)*N);
    float *period=(float*)malloc(sizeof(float)*N);
    int M=5;
    /*移動平均値の入手*/
    for(i=M-1;i<=N-1;i++){
        respma[i]=0;
        for(j=0;j<=M-1;j++){
            respma[i]+=resp[i-j];
        }
        respma[i]/=M;
    }
    /*隣り合う2データ間の差分を入手*/
    for(i=M-1;i<=N-1;i++){
        diff[i]=respma[i+1]-respma[i];
    }
    /*極大点の時間入手*/
    j=0;/*呼吸数を記録*/
    for(i=M-1;i<=N-1;i++){
        /*変化率が正から負に変わり，かつ，閾値よりも高い時刻を検出し心電図中のR波を検出する*/
        if(diff[i-1]>=0 && diff[i]<=0 && respma[i]>1200){
            printf("ピーク時刻:%f\n",etime[(i-(M/2))]);
            period[j]=etime[i-(M/2)];
            j++;
        }
    }
    /*R波間隔の平均値の導出*/
    float total=0;
    for(i=0;i<j-1;i++){
        printf("%fs\n",(period[i+1]-period[i])/20);
        total+=(period[i+1]-period[i]);
    }
    total/=(j-1);
    printf("R波間隔の平均値:%fs\n心拍数:%f回\n",total/20,(float)60/(total/20));
    /*ending*/
    fclose(fp);
    free(etime);
    free(resp);
    free(respma);
    free(diff);
    free(period);
}
