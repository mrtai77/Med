/*呼吸波形データを読み取り，呼吸数や呼吸周期を計算する*/

#include <stdio.h>
#include <stdlib.h>
#define BUF_SIZE 256

int main(){
/* open file */
    FILE *fp;
    if ((fp = fopen("c1_data.txt","r"))==NULL){
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
    int *etime=(int*)malloc(sizeof(int)*N);
    int *resp=(int*)malloc(sizeof(int)*N);

/*先頭と末尾を三つずつ表示*/
    for (i=0;i<3;i++){
        fgets(buf, BUF_SIZE, fp);
        sscanf(buf,"%d,%d\n", &etime[i], &resp[i]);
        printf("%dms:%d\n", etime[i], resp[i]);
    }
    
    for(i=3;i<N-3;i++){
        fgets(buf, BUF_SIZE, fp);
        sscanf(buf,"%d,%d\n", &etime[i], &resp[i]);
    }
    
    for(i=N-3;i<N;i++){
        fgets(buf, BUF_SIZE, fp);
        sscanf(buf,"%d,%d\n", &etime[i], &resp[i]);
        printf("%dms:%d\n", etime[i], resp[i]);
    }
    
/*呼吸振幅の最大値，最小値，平均値の導出*/
    int Max=0,Min=1000,total=0;
    double Ave;
    /*データの最大値の入手*/
    for(i=0;i<=N-1;i++){
        if(Max<resp[i])
            Max=resp[i];
    }
    /*データの最小値を入手*/
    for(i=0;i<=N-1;i++){
        if(Min>resp[i])
            Min=resp[i];
    }
    /*データの平均を導出*/
    for(i=0;i<=N-1;i++){
        total+=resp[i];
    }
    Ave=total/N;
    /*表示*/
    printf("sampling rate:%f\n",((double)N)*1000/((double)etime[N-1]));
    printf("Max:%d  Min:%d  Ave:%f\n",Max,Min,Ave);

/*移動平均の導出*/
    /*動的配列の確保*/
    float *respma=(float*)malloc(sizeof(float)*N);
    int M=5;
    /*移動平均値の入手*/
    for(i=M-1;i<=N-1;i++){
        respma[i]=0;
        for(j=0;j<=M-1;j++){
            respma[i]+=resp[i-j];
        }
        respma[i]/=M;
    }
    /*1000~1100msの範囲の移動平均値を表示*/
     for(i=0;i<N-1;i++){
        if(etime[i]>=1000&&etime[i]<=1100)
            printf("moving average: %f\n",respma[i]);
    }
    
/*平均値との交差点を検出し，一呼吸が終了するごとに時間を記録する*/
    int *period=(int*)malloc(sizeof(int)*N);
    int time=0;
    for(i=M-1;i<=N-1;i++){
        /*iでの値がAveより大きくi+1での値が小さい場合表示と入手*/
        if(respma[i]>Ave && respma[i+1]<Ave){
            printf("%d\n",etime[i+1]);
            period[time]=etime[i+1];
            time++;
        }
    }
    
/*呼吸周期平均の導出*/
    double t_peri[8];
    /*各周期ごとに導出と表示*/
    for(time=0;time<8;time++){
        t_peri[time]=period[time+1]-period[time];
        printf("period%d: %d\n",time+1,(int)t_peri[time]);
    }
    /*平均周期の導出と表示*/
    double Ave_period=0;
    for(time=0;time<9;time++){
        Ave_period+=t_peri[time];
    }
    Ave_period/=time-1;
    printf("period_ave: %fs\nresp_rate: %ftime\n",Ave_period/1000,60000/Ave_period);
 
/* ending */
    fclose(fp);
    free(etime);
    free(resp);
    free(respma);
    free(period);
}
