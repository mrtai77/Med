#include<stdio.h>
#include<iostream>

class Matrix{
    int row,col;
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
};

//0行列
Matrix::Matrix(int R,int C){
    row=R;
    col=C;
    matrix=new double [row*col];
    for(i=0;i<row*col;i++){
        matrix[i]=0;
    }
}

//行列生成
Matrix::Matrix(int R,int C,double *V){
    row=R;
    col=C;
    matrix=new double [row*col];
    for(i=0;i<row*col;i++){
        matrix[i]=V[i];
    }
}

//他行列
Matrix::Matrix(Matrix &Mode){
    row=Mode.row;
    col=Mode.col;
    matrix=new double [row*col];
    for(i=0;i<row*col;i++){
        matrix[i]=Mode.matrix[i];
    }
}

//動的配列
Matrix::~Matrix(){
    delete[]matrix;
}

//1数値代入
void Matrix::Set(int r,int c,double v){
    matrix[r*col+c]=v;
}

//全数値代入
void Matrix::Set(double V){
    for(i=0;i<row*col;i++){
        matrix[i]=0;
    }
}

//1数取得
double Matrix::Get(int r,int c){
    return matrix[r*col+c];
}

//全加算
void Matrix::Add(double V){
    for(i=0;i<row*col;i++){
        matrix[i]+=V;
    }
}

//行加算
void Matrix::Add(Matrix& Mode){
    for(i=0;i<row*col;i++){
        matrix[i]+=Mode.matrix[i];
    }
}

//行列表示
void Matrix::Show(){
    for(i=0;i<row;i++){
        printf("|");
        for(j=0;j<col;j++){
            if(j==col-1)
                printf("%6.2f|\n",matrix[i*col+j]);
            else
                printf("%6.2f ",matrix[i*col+j]);
        }
    }
}

//行数取得
int Matrix::GetRow(){
    return row;
}

//列数取得
int Matrix::GetColumn(){
    return col;
}

//乗算
void Matrix::Multiply(double v){
    for(i=0;i<row*col;i++){
        matrix[i]*=v;
    }
}

//内積
double Matrix::Multiply(Matrix&Mode){
    multi=new double[row*col];
    for(int r=0;r<row;r++){
        for(int c=0;c<col;c++){
            for(i=0;i<row;i++){
                multi[col*r+c]+=matrix[row*r+i]*Mode.matrix[col*i+c];
            }
        }
    }
    for(i=0;i<row*col;i++){
        matrix[i]=multi[i];
    }
    return *matrix;
}

//転置
void Matrix::Transpose(){
    for(int r=0;r<row;r++){
        for(int c=0;c<col;c++){
            if((row*r+c)<(col*c+r)){
                i=matrix[row*r+c];
                matrix[row*r+c]=matrix[col*c+r];
                matrix[col*c+r]=i;
            }
        }
    }
}

int main(){
    Matrix mat1(2,2);   //2*2の行列作成
    printf("mat1=\n");
    mat1.Show();

    mat1.Set(0,0,1.0);  //各要素に数値の代入
    mat1.Set(0,1,2.0);
    mat1.Set(1,0,3.0);
    mat1.Set(1,1,4.0);
    printf("mat1=\n");
    mat1.Show();

    printf("mat1(0,1)=%f\n",mat1.Get(0,1)); //指定した要素の数値を入手

    double vals[4] = {5.1, 6.2, 7.3, 8.4};  //配列を行列に代入
    Matrix mat2(2,2,vals);
    printf("mat2=\n");
    mat2.Show();

    Matrix mat3(mat1);  //行列のコピー
    printf("mat3=\n");
    mat3.Show();
    
    mat3.Add(0.5);      //全要素に指定した数値の代入
    printf("mat3=\n");
    mat3.Show();
    
    mat3.Add(mat2);     //行列同士の加算
    printf("mat3=\n");
    mat3.Show();
    
    printf("mat1の行数は%dです\n",mat1.GetRow());
    printf("mat1の列数は%dです\n",mat1.GetColumn());
//乗算
    Matrix mat4(mat1);
    mat4.Multiply(5.0);
    printf("mat4=\n");
    mat4.Show();
//内積
    Matrix mat5(mat1);
    mat5.Multiply(mat1);
    printf("mat5=\n");
    mat5.Show();
//転置
    Matrix mat6(mat1);
    mat6.Transpose();
    printf("mat6=\n");
    mat6.Show();
}

