#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 10
#define pi M_PI

int main(){
    /* open file */
    FILE *File;
    if ((File = fopen("File.txt","w"))==NULL){
        printf("Can't open data file.\n");
        return 1;
    }
    /*動的配列の確保*/
    float *g=(float*)malloc(sizeof(float)*N);
    float *a=(float*)malloc(sizeof(float)*N);
    float *b=(float*)malloc(sizeof(float)*N);
    int i,k;
    /*振幅の設定*/
    float amp=1;
    /*周波数の設定*/
    float fre=3;
    /*信号の離散化*/
    for(k=0;k<N;k++){
        g[k]=amp*sin((2*pi*k*fre)/(N));
    }
    /*フーリエ変換の実行*/
    for(k=0;k<=N/2;k++){
        a[k]=0;
        b[k]=0;
        for(i=0;i<N;i++){
            /*実部の入手*/
            a[k]+=g[i]*cos((2*pi*i*k)/N);
            /*虚部の入手*/
            b[k]+=g[i]*sin((2*pi*i*k)/N);
        }
        /*データをファイルに入力*/
        fprintf(File,"%f\n",(a[k]*a[k])+(b[k]*b[k]));
    }
    /*ending*/
    fclose(File);
    free(a);
    free(b);
    free(g);
}

