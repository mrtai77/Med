/*Nクイーン問題*/

#include <stdio.h>
#include <stdlib.h>

#define MINIMUM_QUEENS 4
#define SET 1
#define NONE 0

typedef unsigned char BYTE;

/* Show queens board on display */
void showBoard(BYTE* board,int n){
    static int count=0;
    int col,row;
    printf("Soluton%dof%d-Queens problem\n",++count,n);
    for(row=0;row<n;row++){
        for(col=0;col<n;col++){
            int idx=row*n+col;
            printf("%s",board[idx]==SET?"QQ":"  ");
            if (col<n-1)
                printf("|");
        }
        printf("\n");
        if (row<n-1){
            for (col=0;col<n;col++){
                printf("%s",col<n-1?"--+":"--");
            }
            printf("\n");
        }
    }
    printf("\n");
}

/* Judge the board return 1:OK 0:NG */
int CheckBoard(BYTE* board,int n){
    int row,col,count;
    /* check horizontal lines */
    for(row=0;row<n;row++){
        count=0;
        for(col=0;col<n;col++){
            count+=board[row*n+col];
        }
        if(count!=1)
            return 0;
    }

    /* check vertical lines */
    for (col = 0; col < n; col ++){
        count = 0;
        for (row = 0; row < n; row ++){
            count += board[row * n + col];
        }
        if (count != 1) return 0;
    }

    /* check cross lines */
    int ver,m;
    for(ver=0;ver<n-1;ver++){
        int rightup=0,rightdown=0,leftup=0,leftdown=0;
        for(m=0;m+1<n;m++){
            rightup+=board[m*n+(n-1-(m+ver))+1];
            rightdown+=board[(m+ver)*n+(n-1-m)];
            leftup+=board[m*n+(m+ver)+1];
            leftdown+=board[(m+ver)*n+m];
        }
        if(rightup>1)
            return 0;
        if(rightdown>1)
            return 0;
        if(leftup>1)
            return 0;
        if(leftdown>1)
            return 0;
    }
    return 1;
}

/* N-Queens solver */
void serch(BYTE* board ,int a,int n){
    int *row,*col;
    row=(int*)malloc(sizeof(int)*n);
    col=(int*)malloc(sizeof(int)*n);
    int idx;
    if(a==n){
        if(CheckBoard(board,n)==1)
            showBoard(board,n);
        return ;
    }
    else{
        for(row[a]=0;row[a]<n;row[a]++){
            col[a]=a;
            idx=row[a]*n+col[a];
            board[idx]=SET;
            serch(board,a+1,n);
            board[idx]=NONE;
        }
    }
}

/* N-Queens solver */
void nqueens(int n){
    /* initialize board */
    BYTE* board=(BYTE*)malloc(sizeof(BYTE)*n*n);
    int i;
    for (i=0;i<n*n;i++){
        board[i] = NONE;
    }
    int a=0;
    serch(board,a,n);
    free(board);
}

/* Start point */
int main(int argc, char* argv[]){
    /* set number of queens from command line */
    if (argc!=2){
        printf("usage:%sN(N is number of queens)\n",argv[0]);
        return 1;
    }
    int n=atoi(argv[1]);
    if(n<MINIMUM_QUEENS){
        printf("number of queens must be 4 or more.\n");
        return 1;
    }
    nqueens(n);
    return 0;
}
