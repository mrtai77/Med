/*コンピュータ同士でじゃんけんするプログラム*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define PAPER 1
#define STONE 2
#define CHOKI 3

int main(){
    int winPoint = 3;       /* 勝利に必要なポイント */
    int round  = 0;         /* 現在の対戦数 */
    int random = 0;         /* 乱数を記録 */
    int player1Hand = 0;    /* プレイヤーの手 */
    int player2Hand = 0;
    int player3Hand = 0;
    int player1Point = 0;   /* プレイヤーのポイント */
    int player2Point = 0;
    int player3Point = 0;
    /* 対戦前の初期化 */
    srand((unsigned int)time(NULL));
    printf("じゃんけんを開始します\n\n");
    
    /* 対戦のループ */
    do{
        printf("%d回戦\n", ++ round);
        /* プレイヤー１の手を決める */
        random = rand() % 300;
        if (random < 100){
            player1Hand = PAPER;
            printf("パー");
            }
        else if (random < 200){
                player1Hand = STONE;
                printf("グー");
        }
        else{
            player1Hand = CHOKI;
            printf("チョキ");
        }
        printf(" vs ");
        /* プレイヤー２の手を決める */
        random = rand() % 700; /* 0～699の乱数を発生 */
        if (random < 300){
            player2Hand = PAPER;
            printf("パー");
        }
        else if (random < 500){
            player2Hand = STONE;
            printf("グー");
        }
        else{
            player2Hand = CHOKI;
            printf("チョキ");
        }
        printf(" vs ");
        /* プレイヤー3の手を決める */
        if (round%3==1){
            player3Hand = STONE;
            printf("グー");
        }
        else if (round%3==2){
            player3Hand = CHOKI;
            printf("チョキ");
        }
        else{
            player3Hand = PAPER;
            printf("パー");
        }
        printf("\n");
        /* 勝敗判定 */
        /*勝者が二人の場合*/
        if((player1Hand + player2Hand + player3Hand)%3==1){
            if(player1Hand==player2Hand){
                printf("プレイヤー1とプレイヤー2の勝利です。\n");
                player1Point++;
                player2Point++;
            }
            if(player1Hand==player3Hand){
                printf("プレイヤー1とプレイヤー3の勝利です。\n");
                player1Point++;
                player3Point++;
            }
            if(player2Hand==player3Hand){
                printf("プレイヤー2とプレイヤー3の勝利です。\n");
                player3Point++;
                player2Point++;
            }
        }
        /*勝者が一人の場合*/
        if ((player1Hand + player2Hand + player3Hand)%3==2){
            if(player3Hand==player2Hand){
                printf("プレイヤー1の勝利です。\n");
                player1Point++;
            }
            if(player3Hand==player1Hand){
                printf("プレイヤー2の勝利です。\n");
                player2Point++;
            }
            if(player1Hand==player2Hand){
                printf("プレイヤー3の勝利です。\n");
                player3Point++;
            }
        }
        /*引き分けの場合*/
        if(player1Hand+player2Hand+player3Hand==6||(player1Hand==player2Hand&&player2Hand==player3Hand)){
            printf("引き分け\n");
        }
        printf("\n");
    }while(player1Point<winPoint&&player2Point<winPoint &&player3Point < winPoint);
    /* 終了判定 */
    /* 対戦結果の表示 */
    printf("じゃんけん終了\n");
    printf("ポイント %d 対 %d 対 %d で",player1Point,player2Point,player3Point);
    if(player1Point==winPoint){
        printf("プレイヤー１ ");
    }
    if(player2Point==winPoint){
        printf("プレイヤー2 ");
    }
    if(player3Point==winPoint){
        printf("プレイヤー３ ");
    }
    printf("の勝利です\n");
}


