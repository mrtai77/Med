#include<stdio.h>
#include<iostream>
#define N 5
#define ERROR -9999

class Stack{
    int stc[N];
    int i;
    public:
    Stack();
    ~Stack();
    int push(int num);
    int pop();
};

Stack::Stack(){
    i=0;
}

Stack::~Stack(){
    printf("スタック内に残っている数値は%d個です。\n",i);
}

int Stack::push(int num){
    if(i==N)
        return ERROR;
    else{
        stc[i]=num;
        i++;
        return stc[i-1];
    }
}

int Stack::pop(){
    if(i==0)
        return ERROR;
    else{
        i--;
        return stc[i];
    }
}

//動作検証
int main(){
    Stack s;
//スタックの基本性能確認
    printf("1st push %d\n",s.push(10));
    printf("2nd push %d\n",s.push(20));
    printf("3rd push %d\n",s.push(30));
    printf("1st pop %d\n",s.pop());
    printf("2nd pop %d\n",s.pop());
    printf("3rd pop %d\n",s.pop());
//エラーの検証 N＋1回実施
    for(int i=0;i<N+1;i++){
        printf("%d push %d\n",i+1,s.push(i));
    }
    for(int i=0;i<N+1;i++){
        printf("%d pop %d\n",i+1,s.pop());
    }
//終了時処理検証
    s.push(10);
    s.push(20);
}
