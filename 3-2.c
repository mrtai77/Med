/*フーリエ変換によって入力波形である心電図データの複合波を正弦波に分解し，どのような周波数の正弦波がどれくらいの大きさで含まれているかを検出する*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define pi M_PI
#define BUF_SIZE 256

int main(){
    /* open file */
    FILE *fp;
    if ((fp = fopen("ecg4000.txt","r"))==NULL){
        printf("Can't open data file.\n");
        return 1;
    }
    FILE *File;
    if ((File = fopen("File.txt","w"))==NULL){
        printf("Can't open data file.\n");
        return 1;
    }
    FILE *File2;
    if ((File2 = fopen("File2.txt","w"))==NULL){
        printf("Can't open data file.\n");
        return 1;
    }
    FILE *File3;
    if ((File3 = fopen("File3.txt","w"))==NULL){
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
    float *a1=(float*)malloc(sizeof(float)*N);
    float *b1=(float*)malloc(sizeof(float)*N);
    float *a2=(float*)malloc(sizeof(float)*N);
    float *b2=(float*)malloc(sizeof(float)*N);
    float *peri=(float*)malloc(sizeof(float)*N);
    /*データの読み込み*/
    for(i=0;i<N;i++){
        fgets(buf, BUF_SIZE, fp);
        sscanf(buf,"%f,%d\n", &etime[i], &resp[i]);
    }
    /*平均値の入手*/
    int total=0;
    for(i=0;i<=N-1;i++){
        total+=resp[i];
    }
    double Ave;
    Ave=total/N;
    /*フーリエ変換の実行*/
    for(j=0;j<N/2;j++){
        a1[j]=0;
        b1[j]=0;
        a2[j]=0;
        b2[j]=0;
        for(i=0;i<N;i++){
            /*実部の入手*/
            a1[j]+=resp[i]*cos((2*pi*i*j)/N);
            a2[j]+=(resp[i]-Ave)*cos((2*pi*i*j)/N);
            /*虚部の入手*/
            b1[j]+=resp[i]*sin((2*pi*i*j)/N);
            b2[j]+=(resp[i]-Ave)*sin((2*pi*i*j)/N);
            /*周波数成分の入手*/
            peri[j]=(1/((etime[N-1]/20)-(etime[0]/20)))*(j);
        }
        /*データをファイルに入力*/
        fprintf(File,"%f\n",(a1[j]*a1[j])+(b1[j]*b1[j]));
        fprintf(File2,"%f\n",(a2[j]*a2[j])+(b2[j]*b2[j]));
        fprintf(File3,"%f\n",peri[j]);
    }
    
    /*ending*/
    fclose(fp);
    fclose(File);
    fclose(File2);
    fclose(File3);
    free(a1);
    free(b1);
    free(a2);
    free(b2);
    free(resp);
    free(etime);
}
