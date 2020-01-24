#include<stdio.h>
#include<iostream>

class Matrix{
protected:
    int row,col,tb,rl,dx,dy;
    int i,j;
    double *matrix,*multi;
public:
    Matrix(int R,int C);
    Matrix(int R,int C,double *V);
    Matrix(Matrix &Mode);
    ~Matrix();
    void Set(int r,int c,double v);
    void Set(double V);
    double Get(int r,int c);
    void Add(double V);
    void Add(Matrix &Mode);
    void Show();
    int GetRow();
    int GetColumn();
    void Multiply(double v);
    double Multiply(Matrix& Mode);
    void Transpose();
    void Invert();
    int IsOK();
};

class Image:public Matrix{
public:
    Image(int R,int C):Matrix(R,C){
        if(R<1){
            fprintf(stderr,"行指定に不正有り\n");
            return;
        }
        if(C<1){
            fprintf(stderr,"列指定に不正有り\n");
            return;
        }
        row=R;
        col=C;
        matrix=new double [row*col];
        if(matrix==NULL){
            fprintf(stderr,"メモリ確保に失敗\n");
            row=0;
            col=0;
            return;
        }
        for(i=0;i<row*col;i++){
            matrix[i]=0;
        }
    }
    void DrawLine(int x1,int y1,int x2,int y2,int v);
    void Flip(int mode);
    void ShowImage();
};

//0行列
Matrix::Matrix(int R,int C){
    if(R<1){
        fprintf(stderr,"行指定に不正有り\n");
        return;
    }
    if(C<1){
        fprintf(stderr,"列指定に不正有り\n");
        return;
    }
    row=R;
    col=C;
    matrix=new double [row*col];
    if(matrix==NULL){
        fprintf(stderr,"メモリ確保に失敗\n");
        row=0;
        col=0;
        return;
    }
    for(i=0;i<row*col;i++){
        matrix[i]=0;
    }
}

//動的配列
Matrix::~Matrix(){
    delete[]matrix;
}

//確認
int Matrix::IsOK(){
    return matrix==NULL?0:1;
}

//1数値代入
void Matrix::Set(int r,int c,double v){
    matrix[r*col+c]=v;
}

//線分代入
void Image::DrawLine(int x1,int y1,int x2,int y2,int v){
    double x0=x1-(((x2-x1)*y1)/(y2-y1));
    for(i=0;i<col;i++){
        double dx=(((double)x2-(double)x1)*i/((double)y2-(double)y1))+x0+0.5;
        matrix[i*col+(int)dx]=v;
    }
}

//上下左右転換
void Image::Flip(int mode){
    if(mode==1){
        for(i=0;i<row/2;i++){
            for(j=0;j<col;j++){
                tb=matrix[i*col+j];
                matrix[i*col+j]=matrix[(row-1-i)*col+j];
                matrix[(row-1-i)*col+j]=tb;
            }
        }
    }
    else if(mode==2){
        for(i=0;i<row;i++){
            for(j=0;j<col/2;j++){
                rl=matrix[i*col+j];
                matrix[i*col+j]=matrix[i*col+(col-1-j)];
                matrix[i*col+(col-1-j)]=rl;
            }
        }
    }
    else if(mode==3){
        for(i=0;i<row/2;i++){
            for(j=0;j<col;j++){
                tb=matrix[i*col+j];
                matrix[i*col+j]=matrix[(row-1-i)*col+j];
                matrix[(row-1-i)*col+j]=tb;
            }
        }
        for(i=0;i<row;i++){
            for(j=0;j<col/2;j++){
                rl=matrix[i*col+j];
                matrix[i*col+j]=matrix[i*col+(col-1-j)];
                matrix[i*col+(col-1-j)]=rl;
            }
        }
    }
    else
        return;
}

//画像表示
void Image::ShowImage(){
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            if(j==col-1)
                printf("%d\n",(int)matrix[i*col+j]);
            else
                printf("%d",(int)matrix[i*col+j]);
        }
    }
    printf("\n\n");
}
                      
int main(){
    Image img(4,4);
    img.Set(1,2,5);
    img.ShowImage();
    img.DrawLine(0,0,1,3,2);
    img.ShowImage();
    img.Flip(1);
    img.ShowImage();
    img.Flip(2);
    img.ShowImage();
    img.Flip(3);
    img.ShowImage();
}

