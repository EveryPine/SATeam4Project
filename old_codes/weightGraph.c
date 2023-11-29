#include<stdio.h>
#include "queue.c"

int S[5][5]={{0,1,0,0,0},
			 {0,-1,1,0,-1},
			 {0,0,0,-1,0},
			 {0,1,0,0,1},
			 {0,0,0,1,0}};
float W1[5][5];
float W2[5][5];
float W3[5][5];
float W4[5][5];
float W5[5][5];
int Red[5][2] ={{0,0},{0,0},{0,0},{0,0},{0,0}};



int dir[4][2] = {{1,0},{-1,0},{0,1}, {0,-1}};
int dirSearch[4][2] = {{0,-1},{0,1},{-1,0}, {1,0}};
float tmp[4] = {-100,-100,-100,-100};
int rDir = 1;
int g_rDir=1;
int tmp_count = 0;
char taskArr[20];
int g_x = 4, g_y = 4;
float weight = -100;
int t_x, t_y;
////
int g=1;

char g_taskW1[10];
char g_taskW2[10];
char g_taskW3[10];
char g_taskW4[10];
char g_taskW5[10];

int visited = 31;            //11111
int isVisited1 = 0;
int isVisited2 = 0;
int isVisited3 = 0;
int isVisited4 = 0;
int isVisited5 = 0;

int dirW1 = 1;
int dirW2 = 1;
int dirW3 = 1;
int dirW4 = 1;
int dirW5 = 1;

int tableXY[5][2] = {{0,0},{0,0},{0,0},{0,0},{0,0}};
////

void myStrcpy(char *dest, const char *src) {
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0'; // 문자열의 끝에 널 문자 추가
}

void myStrcat(char *dest, const char *src) {
    // dest의 끝 찾기
    while (*dest) {
        dest++;
    }

    // src의 내용을 dest의 끝에 복사
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0'; // 문자열의 끝에 널 문자 추가
}


void W1making(int s){
    
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            W1[i][j]=S[i][j];
        }
    }
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(S[i][j]==1 && (i*5+j)!=s) W1[i][j]=0.0;
        }
    }
}
void W2making(int s){
    
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            W2[i][j]=S[i][j];
        }
    }
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(S[i][j]==1 && (i*5+j)!=s) W2[i][j]=0.0;
        }
    }
}
void W3making(int s){
    
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            W3[i][j]=S[i][j];
        }
    }
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(S[i][j]==1 && (i*5+j)!=s) W3[i][j]=0.0;
        }
    }
}
void W4making(int s){
    
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            W4[i][j]=S[i][j];
        }
    }
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(S[i][j]==1 && (i*5+j)!=s) W4[i][j]=0.0;
        }
    }
}
void W5making(int s){
    
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            W5[i][j]=S[i][j];
        }
    }
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(S[i][j]==1 && (i*5+j)!=s) W5[i][j]=0.0;
        }
    }
}
void convertGraph(){
    int count=0;
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(S[i][j]==1){
                switch (count){
                case 0:
                    W1making(i*5+j);
                    Red[0][0]=i;
                    Red[0][1]=j;
                    count++;
                    break;
                case 1:
                    W2making(i*5+j);
                    Red[1][0]=i;
                    Red[1][1]=j;
                    count++;
                    break;
                case 2:
                    W3making(i*5+j);
                    Red[2][0]=i;
                    Red[2][1]=j;
                    count++;
                    break;
                case 3:
                    W4making(i*5+j);
                    Red[3][0]=i;
                    Red[3][1]=j;
                    count++;
                    break;
                case 4:
                    W5making(i*5+j);
                    Red[4][0]=i;
                    Red[4][1]=j;
                    count++;
                    break;
                
                } 
            } 
        }
    }
}

int* moveOneBlock(int x, int y, int k);
char robotDir(int beforeX, int beforeY, int afterX, int afterY, int k);
void makeWeightGraph(int a, int b, int k);

int* moveOneBlock(int x, int y, int k){
    int tmp_x = x, tmp_y = y; 
    if(k == 0){
        for(int i= 0; i<4; i++){
            if(i == 0){
                if(y+dirSearch[i][1] >= 0) {
                    tmp[i] = W1[x][y+dirSearch[i][1]];
                    if(weight < tmp[i]) {
                        printf("비교 %f %f\n", weight, tmp[i]);
                        weight = tmp[i];
                        tmp_x = x, tmp_y = y+dirSearch[i][1];
                        
                        printf("서 %d %d %f\n",tmp_x,tmp_y,weight);
                    }
                }
            }
            else if(i == 1){
                if(y+dirSearch[i][1] <= 4) {
                    tmp[i] = W1[x][y+dirSearch[i][1]];
                    if(weight < tmp[i]) {
                        weight = tmp[i];
                        tmp_x = x, tmp_y = y+dirSearch[i][1];
                        printf("동 %d %d %f\n",tmp_x,tmp_y,weight);
                    }
                }
            }
            else if(i == 2){
                if(x+dirSearch[i][0] >= 0) {
                    tmp[i] = W1[x+dirSearch[i][0]][y];
                    if(weight < tmp[i]) {
                        printf("비교 %f %f\n", weight, tmp[i]);
                        weight = tmp[i];
                        tmp_x = x+dirSearch[i][0], tmp_y = y;
                        printf("북 %d %d %f\n",tmp_x,tmp_y,weight);
                    }
                }
            }
            else if(i == 3){
                if(x+dirSearch[i][0] <= 4) {
                    tmp[i] = W1[x+dirSearch[i][0]][y];
                    if(weight < tmp[i]) {
                        weight = tmp[i];
                        tmp_x = x+dirSearch[i][0], tmp_y = y;
                        printf("남 %d %d %f\n",tmp_x,tmp_y,weight);
                    }
                }
            }
            if(i == 3) x = tmp_x, y = tmp_y;
        }
    }
    else if(k == 1){
        
        for(int i= 0; i<4; i++){
            if(i == 0){
                if(y+dirSearch[i][1] >= 0) {
                    tmp[i] = W2[x][y+dirSearch[i][1]];
                    if(weight < tmp[i]) {

                        printf("비교 %f %f\n", weight, tmp[i]);
                        weight = tmp[i];
                        tmp_x = x, tmp_y = y+dirSearch[i][1];
                        
                        printf("서 %d %d %f\n",tmp_x,tmp_y,weight);
                    }
                }
            }
            else if(i == 1){
                if(y+dirSearch[i][1] <= 4) {
                    tmp[i] = W2[x][y+dirSearch[i][1]];
                    if(weight < tmp[i]) {
                        weight = tmp[i];
                        tmp_x = x, tmp_y = y+dirSearch[i][1];
                        printf("동 %d %d %f\n",tmp_x,tmp_y,weight);
                    }
                }
            }
            else if(i == 2){
                if(x+dirSearch[i][0] >= 0) {
                    tmp[i] = W2[x+dirSearch[i][0]][y];
                    if(weight < tmp[i]) {
                        printf("비교 %f %f\n", weight, tmp[i]);
                        weight = tmp[i];
                        tmp_x = x+dirSearch[i][0], tmp_y = y;
                        printf("북 %d %d %f\n",tmp_x,tmp_y,weight);
                    }
                }
            }
            else if(i == 3){
                if(x+dirSearch[i][0] <= 4) {
                    tmp[i] = W2[x+dirSearch[i][0]][y];
                    if(weight < tmp[i]) {
                        weight = tmp[i];
                        tmp_x = x+dirSearch[i][0], tmp_y = y;
                        printf("남 %d %d %f\n",tmp_x,tmp_y,weight);
                    }
                }
            }
            if(i == 3) x = tmp_x, y = tmp_y;
        }
    }
    else if(k == 2){
        for(int i= 0; i<4; i++){
            if(i == 0){
                if(y+dirSearch[i][1] >= 0) {
                    tmp[i] = W3[x][y+dirSearch[i][1]];
                    if(weight < tmp[i]) {
                        printf("비교 %f %f\n", weight, tmp[i]);
                        weight = tmp[i];
                        tmp_x = x, tmp_y = y+dirSearch[i][1];
                        
                        printf("서 %d %d %f\n",tmp_x,tmp_y,weight);
                    }
                }
            }
            else if(i == 1){
                if(y+dirSearch[i][1] <= 4) {
                    tmp[i] = W3[x][y+dirSearch[i][1]];
                    if(weight < tmp[i]) {
                        weight = tmp[i];
                        tmp_x = x, tmp_y = y+dirSearch[i][1];
                        printf("동 %d %d %f\n",tmp_x,tmp_y,weight);
                    }
                }
            }
            else if(i == 2){
                if(x+dirSearch[i][0] >= 0) {
                    tmp[i] = W3[x+dirSearch[i][0]][y];
                    if(weight < tmp[i]) {
                        printf("비교 %f %f\n", weight, tmp[i]);
                        weight = tmp[i];
                        tmp_x = x+dirSearch[i][0], tmp_y = y;
                        printf("북 %d %d %f\n",tmp_x,tmp_y,weight);
                    }
                }
            }
            else if(i == 3){
                if(x+dirSearch[i][0] <= 4) {
                    tmp[i] = W3[x+dirSearch[i][0]][y];
                    if(weight < tmp[i]) {
                        weight = tmp[i];
                        tmp_x = x+dirSearch[i][0], tmp_y = y;
                        printf("남 %d %d %f\n",tmp_x,tmp_y,weight);
                    }
                }
            }
            if(i == 3) x = tmp_x, y = tmp_y;
        }
    }
    else if(k == 3){
        for(int i= 0; i<4; i++){
            if(i == 0){
                if(y+dirSearch[i][1] >= 0) {
                    tmp[i] = W4[x][y+dirSearch[i][1]];
                    if(weight < tmp[i]) {
                        printf("비교 %f %f\n", weight, tmp[i]);
                        weight = tmp[i];
                        tmp_x = x, tmp_y = y+dirSearch[i][1];
                        
                        printf("서 %d %d %f\n",tmp_x,tmp_y,weight);
                    }
                }
            }
            else if(i == 1){
                if(y+dirSearch[i][1] <= 4) {
                    tmp[i] = W4[x][y+dirSearch[i][1]];
                    if(weight < tmp[i]) {
                        weight = tmp[i];
                        tmp_x = x, tmp_y = y+dirSearch[i][1];
                        printf("동 %d %d %f\n",tmp_x,tmp_y,weight);
                    }
                }
            }
            else if(i == 2){
                if(x+dirSearch[i][0] >= 0) {
                    tmp[i] = W4[x+dirSearch[i][0]][y];
                    if(weight < tmp[i]) {
                        printf("비교 %f %f\n", weight, tmp[i]);
                        weight = tmp[i];
                        tmp_x = x+dirSearch[i][0], tmp_y = y;
                        printf("북 %d %d %f\n",tmp_x,tmp_y,weight);
                    }
                }
            }
            else if(i == 3){
                if(x+dirSearch[i][0] <= 4) {
                    tmp[i] = W4[x+dirSearch[i][0]][y];
                    if(weight < tmp[i]) {
                        weight = tmp[i];
                        tmp_x = x+dirSearch[i][0], tmp_y = y;
                        printf("남 %d %d %f\n",tmp_x,tmp_y,weight);
                    }
                }
            }
            if(i == 3) x = tmp_x, y = tmp_y;
        }
    }
    else if(k == 4){
        for(int i= 0; i<4; i++){
            if(i == 0){
                if(y+dirSearch[i][1] >= 0) {
                    tmp[i] = W5[x][y+dirSearch[i][1]];
                    if(weight < tmp[i]) {
                        printf("비교 %f %f\n", weight, tmp[i]);
                        weight = tmp[i];
                        tmp_x = x, tmp_y = y+dirSearch[i][1];
                        
                        printf("서 %d %d %f\n",tmp_x,tmp_y,weight);
                    }
                }
            }
            else if(i == 1){
                if(y+dirSearch[i][1] <= 4) {
                    tmp[i] = W5[x][y+dirSearch[i][1]];
                    if(weight < tmp[i]) {
                        weight = tmp[i];
                        tmp_x = x, tmp_y = y+dirSearch[i][1];
                        printf("동 %d %d %f\n",tmp_x,tmp_y,weight);
                    }
                }
            }
            else if(i == 2){
                if(x+dirSearch[i][0] >= 0) {
                    tmp[i] = W5[x+dirSearch[i][0]][y];
                    if(weight < tmp[i]) {
                        printf("비교 %f %f\n", weight, tmp[i]);
                        weight = tmp[i];
                        tmp_x = x+dirSearch[i][0], tmp_y = y;
                        printf("북 %d %d %f\n",tmp_x,tmp_y,weight);
                    }
                }
            }
            else if(i == 3){
                if(x+dirSearch[i][0] <= 4) {
                    tmp[i] = W5[x+dirSearch[i][0]][y];
                    if(weight < tmp[i]) {
                        weight = tmp[i];
                        tmp_x = x+dirSearch[i][0], tmp_y = y;
                        printf("남 %d %d %f\n",tmp_x,tmp_y,weight);
                    }
                }
            }
            if(i == 3) x = tmp_x, y = tmp_y;
        }
    }
    //printf("%d %d",x,y);
    static int result[2]; // 정적 배열 사용

    result[0] = x, result[1] = y;
    tableXY[k][0] = x;
    tableXY[k][1] = y;
    return result;
}
void makeWeightGraph(int a, int b, int k){
    addq(a,b);
    if(k == 0) {
        while(!IsEmpty()){
            struct Point removedPoint = deleteq();
            for(int i = 0; i < 4; i++) {
                if(i == 0) {
                    if(removedPoint.x + dir[i][0] <= 4 && W1[removedPoint.x + dir[i][0]][removedPoint.y] != -1) {
                        if(W1[removedPoint.x + dir[i][0]][removedPoint.y] == 0) {
                            W1[removedPoint.x + dir[i][0]][removedPoint.y] = W1[removedPoint.x][removedPoint.y] * 0.9;
                            addq(removedPoint.x + dir[i][0], removedPoint.y);
                        }
                    } 
                }
                else if(i == 1) {
                    if(removedPoint.x + dir[i][0] >= 0 && W1[removedPoint.x + dir[i][0]][removedPoint.y] != -1) {
                        if(W1[removedPoint.x + dir[i][0]][removedPoint.y] == 0) {
                            W1[removedPoint.x + dir[i][0]][removedPoint.y] = W1[removedPoint.x][removedPoint.y] * 0.9;
                            addq(removedPoint.x + dir[i][0], removedPoint.y);
                        }
                    } 
                }
                else if(i == 2) {
                    if(removedPoint.y + dir[i][1] <= 4 && W1[removedPoint.x][removedPoint.y + dir[i][1]] != -1) {
                        if(W1[removedPoint.x][removedPoint.y + dir[i][1]] == 0) {
                            W1[removedPoint.x][removedPoint.y + dir[i][1]] = W1[removedPoint.x][removedPoint.y] * 0.9;
                            addq(removedPoint.x, removedPoint.y + dir[i][1]);
                        }
                    } 
                }
                else if(i == 3) {
                    if(removedPoint.y + dir[i][1] >= 0 && W1[removedPoint.x][removedPoint.y + dir[i][1]] != -1) {
                        if(W1[removedPoint.x][removedPoint.y + dir[i][1]] == 0) {
                            W1[removedPoint.x][removedPoint.y + dir[i][1]] = W1[removedPoint.x][removedPoint.y] * 0.9;
                            addq(removedPoint.x, removedPoint.y + dir[i][1]);
                        }
                    } 
                }
            }
        }
    }
    else if(k == 1){
        while(!IsEmpty()){
            struct Point removedPoint = deleteq();
            for(int i = 0; i < 4; i++) {
                if(i == 0) {
                    if(removedPoint.x + dir[i][0] <= 4 && W2[removedPoint.x + dir[i][0]][removedPoint.y] != -1) {
                        if(W2[removedPoint.x + dir[i][0]][removedPoint.y] == 0) {
                            W2[removedPoint.x + dir[i][0]][removedPoint.y] = W2[removedPoint.x][removedPoint.y] * 0.9;
                            addq(removedPoint.x + dir[i][0], removedPoint.y);
                        }
                    } 
                }
                else if(i == 1) {
                    if(removedPoint.x + dir[i][0] >= 0 && W2[removedPoint.x + dir[i][0]][removedPoint.y] != -1) {
                        if(W2[removedPoint.x + dir[i][0]][removedPoint.y] == 0) {
                            W2[removedPoint.x + dir[i][0]][removedPoint.y] = W2[removedPoint.x][removedPoint.y] * 0.9;
                            addq(removedPoint.x + dir[i][0], removedPoint.y);
                        }
                    } 
                }
                else if(i == 2) {
                    if(removedPoint.y + dir[i][1] <= 4 && W2[removedPoint.x][removedPoint.y + dir[i][1]] != -1) {
                        if(W2[removedPoint.x][removedPoint.y + dir[i][1]] == 0) {
                            W2[removedPoint.x][removedPoint.y + dir[i][1]] = W2[removedPoint.x][removedPoint.y] * 0.9;
                            addq(removedPoint.x, removedPoint.y + dir[i][1]);
                        }
                    } 
                }
                else if(i == 3) {
                    if(removedPoint.y + dir[i][1] >= 0 && W2[removedPoint.x][removedPoint.y + dir[i][1]] != -1) {
                        if(W2[removedPoint.x][removedPoint.y + dir[i][1]] == 0) {
                            W2[removedPoint.x][removedPoint.y + dir[i][1]] = W2[removedPoint.x][removedPoint.y] * 0.9;
                            addq(removedPoint.x, removedPoint.y + dir[i][1]);
                        }
                    } 
                }
            }
        }
    }
    else if(k == 2){
        while(!IsEmpty()){
            struct Point removedPoint = deleteq();
            for(int i = 0; i < 4; i++) {
                if(i == 0) {
                    if(removedPoint.x + dir[i][0] <= 4 && W3[removedPoint.x + dir[i][0]][removedPoint.y] != -1) {
                        if(W3[removedPoint.x + dir[i][0]][removedPoint.y] == 0) {
                            W3[removedPoint.x + dir[i][0]][removedPoint.y] = W3[removedPoint.x][removedPoint.y] * 0.9;
                            addq(removedPoint.x + dir[i][0], removedPoint.y);
                        }
                    } 
                }
                else if(i == 1) {
                    if(removedPoint.x + dir[i][0] >= 0 && W3[removedPoint.x + dir[i][0]][removedPoint.y] != -1) {
                        if(W3[removedPoint.x + dir[i][0]][removedPoint.y] == 0) {
                            W3[removedPoint.x + dir[i][0]][removedPoint.y] = W3[removedPoint.x][removedPoint.y] * 0.9;
                            addq(removedPoint.x + dir[i][0], removedPoint.y);
                        }
                    } 
                }
                else if(i == 2) {
                    if(removedPoint.y + dir[i][1] <= 4 && W3[removedPoint.x][removedPoint.y + dir[i][1]] != -1) {
                        if(W3[removedPoint.x][removedPoint.y + dir[i][1]] == 0) {
                            W3[removedPoint.x][removedPoint.y + dir[i][1]] = W3[removedPoint.x][removedPoint.y] * 0.9;
                            addq(removedPoint.x, removedPoint.y + dir[i][1]);
                        }
                    } 
                }
                else if(i == 3) {
                    if(removedPoint.y + dir[i][1] >= 0 && W3[removedPoint.x][removedPoint.y + dir[i][1]] != -1) {
                        if(W3[removedPoint.x][removedPoint.y + dir[i][1]] == 0) {
                            W3[removedPoint.x][removedPoint.y + dir[i][1]] = W3[removedPoint.x][removedPoint.y] * 0.9;
                            addq(removedPoint.x, removedPoint.y + dir[i][1]);
                        }
                    } 
                }
            }
        }
    }
    else if(k == 3 && !isVisited4){
        while(!IsEmpty()){
            struct Point removedPoint = deleteq();
            for(int i = 0; i < 4; i++) {
                if(i == 0) {
                    if(removedPoint.x + dir[i][0] <= 4 && W4[removedPoint.x + dir[i][0]][removedPoint.y] != -1) {
                        if(W4[removedPoint.x + dir[i][0]][removedPoint.y] == 0) {
                            W4[removedPoint.x + dir[i][0]][removedPoint.y] = W4[removedPoint.x][removedPoint.y] * 0.9;
                            addq(removedPoint.x + dir[i][0], removedPoint.y);
                        }
                    } 
                }
                else if(i == 1) {
                    if(removedPoint.x + dir[i][0] >= 0 && W4[removedPoint.x + dir[i][0]][removedPoint.y] != -1) {
                        if(W4[removedPoint.x + dir[i][0]][removedPoint.y] == 0) {
                            W4[removedPoint.x + dir[i][0]][removedPoint.y] = W4[removedPoint.x][removedPoint.y] * 0.9;
                            addq(removedPoint.x + dir[i][0], removedPoint.y);
                        }
                    } 
                }
                else if(i == 2) {
                    if(removedPoint.y + dir[i][1] <= 4 && W4[removedPoint.x][removedPoint.y + dir[i][1]] != -1) {
                        if(W4[removedPoint.x][removedPoint.y + dir[i][1]] == 0) {
                            W4[removedPoint.x][removedPoint.y + dir[i][1]] = W4[removedPoint.x][removedPoint.y] * 0.9;
                            addq(removedPoint.x, removedPoint.y + dir[i][1]);
                        }
                    } 
                }
                else if(i == 3) {
                    if(removedPoint.y + dir[i][1] >= 0 && W4[removedPoint.x][removedPoint.y + dir[i][1]] != -1) {
                        if(W4[removedPoint.x][removedPoint.y + dir[i][1]] == 0) {
                            W4[removedPoint.x][removedPoint.y + dir[i][1]] = W4[removedPoint.x][removedPoint.y] * 0.9;
                            addq(removedPoint.x, removedPoint.y + dir[i][1]);
                        }
                    } 
                }
            }
        }
    }
    else if(k == 4){
        while(!IsEmpty()){
            struct Point removedPoint = deleteq();
            for(int i = 0; i < 4; i++) {
                if(i == 0) {
                    if(removedPoint.x + dir[i][0] <= 4 && W5[removedPoint.x + dir[i][0]][removedPoint.y] != -1) {
                        if(W5[removedPoint.x + dir[i][0]][removedPoint.y] == 0) {
                            W5[removedPoint.x + dir[i][0]][removedPoint.y] = W5[removedPoint.x][removedPoint.y] * 0.9;
                            addq(removedPoint.x + dir[i][0], removedPoint.y);
                        }
                    } 
                }
                else if(i == 1) {
                    if(removedPoint.x + dir[i][0] >= 0 && W5[removedPoint.x + dir[i][0]][removedPoint.y] != -1) {
                        if(W5[removedPoint.x + dir[i][0]][removedPoint.y] == 0) {
                            W5[removedPoint.x + dir[i][0]][removedPoint.y] = W5[removedPoint.x][removedPoint.y] * 0.9;
                            addq(removedPoint.x + dir[i][0], removedPoint.y);
                        }
                    } 
                }
                else if(i == 2) {
                    if(removedPoint.y + dir[i][1] <= 4 && W5[removedPoint.x][removedPoint.y + dir[i][1]] != -1) {
                        if(W5[removedPoint.x][removedPoint.y + dir[i][1]] == 0) {
                            W5[removedPoint.x][removedPoint.y + dir[i][1]] = W5[removedPoint.x][removedPoint.y] * 0.9;
                            addq(removedPoint.x, removedPoint.y + dir[i][1]);
                        }
                    } 
                }
                else if(i == 3) {
                    if(removedPoint.y + dir[i][1] >= 0 && W5[removedPoint.x][removedPoint.y + dir[i][1]] != -1) {
                        if(W5[removedPoint.x][removedPoint.y + dir[i][1]] == 0) {
                            W5[removedPoint.x][removedPoint.y + dir[i][1]] = W5[removedPoint.x][removedPoint.y] * 0.9;
                            addq(removedPoint.x, removedPoint.y + dir[i][1]);
                        }
                    } 
                }
            }
        }
    }
}
int minimumSearch() {
    convertGraph();
    ////
    /*
    for(int i=0;i<10;i++) taskW1[i] = 'N';
    for(int i=0;i<10;i++) taskW2[i] = 'N';
    for(int i=0;i<10;i++) taskW3[i] = 'N';
    for(int i=0;i<10;i++) taskW4[i] = 'N';
    for(int i=0;i<10;i++) taskW5[i] = 'N';
    */
    ////
    char taskW1[10]={'N','N','N','N','N','N','N','N','N','N'};
    char taskW2[10]={'N','N','N','N','N','N','N','N','N','N'};
    char taskW3[10]={'N','N','N','N','N','N','N','N','N','N'};
    char taskW4[10]={'N','N','N','N','N','N','N','N','N','N'};
    char taskW5[10]={'N','N','N','N','N','N','N','N','N','N'};

    int countW1 = 0;
    int countW2 = 0;
    int countW3 = 0;
    int countW4 = 0;
    int countW5 = 0;
    for(int i = 0; i < 5; i++){
        printf("==================\n");
        int a = Red[i][0]; int b = Red[i][1];
        printf("빨간패치의 좌표 : %d %d\n", a,b);
        makeWeightGraph(a, b, i);
        
        for(int j = 0; j<5; j++) {
            for(int k = 0; k < 5; k++){
                printf("%f ", W1[j][k]);
            }
            printf("\n");
        }
        printf("\n");
        for(int j = 0; j<5; j++) {
            for(int k = 0; k < 5; k++){
                printf("%f ", W2[j][k]);
            }
            printf("\n");
        }
        printf("\n");
        for(int j = 0; j<5; j++) {
            for(int k = 0; k < 5; k++){
                printf("%f ", W3[j][k]);
            }
            printf("\n");
        }
        printf("\n");
        for(int j = 0; j<5; j++) {
            for(int k = 0; k < 5; k++){
                printf("%f ", W4[j][k]);
            }
            printf("\n");
        }
        printf("\n");
        for(int j = 0; j<5; j++) {
            for(int k = 0; k < 5; k++){
                printf("%f ", W5[j][k]);
            }
            printf("\n");
        }
        
        
        int *result; // 포인터 변수 선언
        t_x = g_x,  t_y = g_y;
        weight = -100;
        rDir = g_rDir;
        int ii = 0;
        
        while(1){
            result = moveOneBlock(t_x, t_y, i); // 포인터에 반환값 할당
            printf(")))%d\n",i);
            //printf("%c ", robotDir(t_x, t_y, result[0], result[1]));
            if(i == 0) {
                if(!isVisited1) {
                    taskW1[ii]=robotDir(t_x, t_y, tableXY[i][0], tableXY[i][1], i);
                    countW1++;
                }
                else countW1 = 100;
            }
            else if(i == 1) {
                if(!isVisited2) {
                    taskW2[ii]=robotDir(t_x, t_y, tableXY[i][0], tableXY[i][1], i);
                    countW2++;
                }
                else countW2 = 100;
            }
            else if(i == 2) {  
                if(!isVisited3) { 
                    taskW3[ii]=robotDir(t_x, t_y, tableXY[i][0], tableXY[i][1], i);
                    countW3++;
                }
                else countW3=100;
            }
            else if(i == 3) {
                if(!isVisited4) { 
                    taskW4[ii]=robotDir(t_x, t_y, tableXY[i][0], tableXY[i][1], i);
                    countW4++;
                }
                else countW4=100;
            }
            else if(i == 4) {
                if(!isVisited5) { 
                    taskW5[ii]=robotDir(t_x, t_y, tableXY[i][0], tableXY[i][1], i);
                    countW5++;
                }
                else countW5=100;
            }
            //char dirStr[2]; // 단일 문자를 위한 문자열
            //dirStr[0] = robotDir(t_x, t_y, result[0], result[1]); // 문자를 저장
            //dirStr[1] = '\0'; // 널 문자로 문자열 끝 표시
            //myStrcat(tmp_taskArr, dirStr);

            t_x = result[0];
            t_y = result[1];
            //printf("\n");
            if(t_x == a && t_y == b) break;
            ii++;
        }
        
        /*
        for(int aa = 0; aa < 10; aa++) printf("%c ", tmp_taskArr[aa]);
        if(g_count > tmp_count) {
            g_count = tmp_count;
            tmp_count = 0;
            myStrcpy(taskArr, tmp_taskArr);
        }   
        */
        
    }
    int min = countW1;
    ////
    g=1;
    g_x = tableXY[0][0];
    g_y = tableXY[0][1];
    g_rDir = dirW1;
    ////
    printf("\nCount : %d | CountW1 : %d\n", min, countW1);
    myStrcpy(taskArr, taskW1);
    printf("\nCount : %d | CountW2 : %d\n", min, countW2);
    if(min > countW2) {
        min = countW2;
        g=2;
        g_x = tableXY[1][0];
        g_y = tableXY[1][1];
        g_rDir = dirW2;
        printf("\nIN2\n");
        for(int aa = 0; aa < 10; aa++) printf("=%c ", taskW2[aa]);
        myStrcpy(taskArr, taskW2);
    }
    printf("\nCount : %d | CountW3 : %d\n", min, countW3);
    if(min > countW3) {
        min = countW3;
        g=3;
        g_x = tableXY[2][0];
        g_y = tableXY[2][1];
        g_rDir = dirW3;
        printf("\nIN3\n");
        myStrcpy(taskArr, taskW3);
        for(int aa = 0; aa < 10; aa++) printf("=%c ", taskW3[aa]);
    }
    printf("\nCount : %d | CountW4 : %d\n", min, countW4);
    if(min > countW4) {
        min = countW4;
        g=4;
        g_x = tableXY[3][0];
        g_y = tableXY[3][1];
        g_rDir = dirW4;
        printf("\nIN4\n");
        myStrcpy(taskArr, taskW4);
        for(int aa = 0; aa < 10; aa++) printf("=%c ", taskW4[aa]);
        
    }
    printf("\nCount : %d | CountW5 : %d\n", min, countW5);
    if(min > countW5) {
        min = countW5;
        g=5;
        g_x = tableXY[4][0];
        g_y = tableXY[4][1];
        g_rDir = dirW5;
        printf("\nIN5\n");
        myStrcpy(taskArr, taskW5);
    }

    for(int aa = 0; aa < 10; aa++) printf("=%c ", taskArr[aa]);
    printf("\n");
    
    myStrcpy(g_taskW1, taskW1);
    myStrcpy(g_taskW2, taskW2);
    myStrcpy(g_taskW3, taskW3);
    myStrcpy(g_taskW4, taskW4);
    myStrcpy(g_taskW5, taskW5);
    
    return 0;
}

char robotDir(int beforeX, int beforeY, int afterX, int afterY, int k){
    tmp_count++;
    if(rDir == 0) { //동
        if(beforeX < afterX) { //아래
            rDir = 2;
            if(k ==0) dirW1 = 2;
            else if(k==1) dirW2 = 2;
            else if(k==2) dirW3 = 2;
            else if(k==3) dirW4 = 2;
            else dirW5 = 2;
            return 'R';
        }  
        else if(beforeX>afterX) { //위
            rDir=3;
            if(k ==0) dirW1 = 3;
            else if(k==1) dirW2 = 3;
            else if(k==2) dirW3 = 3;
            else if(k==3) dirW4 = 3;
            else dirW5 = 3;
            return 'L';
        }
        else if(beforeY<afterY) { //오른 
            rDir=0;
            if(k ==0) dirW1 = 0;
            else if(k==1) dirW2 = 0;
            else if(k==2) dirW3 = 0;
            else if(k==3) dirW4 = 0;
            else dirW5 = 0;
            return 'F';
        }
        else if(beforeY>afterY) { // 왼
            rDir=1;
            if(k ==0) dirW1 = 1;
            else if(k==1) dirW2 = 1;
            else if(k==2) dirW3 = 1;
            else if(k==3) dirW4 = 1;
            else dirW5 = 1;
            return 'U';
        }
    }
    else if(rDir == 1){ //서
        if(beforeX < afterX) { //아래
            rDir = 2;
            if(k ==0) dirW1 = 2;
            else if(k==1) dirW2 = 2;
            else if(k==2) dirW3 = 2;
            else if(k==3) dirW4 = 2;
            else dirW5 = 2;
            return 'L';
        }  
        else if(beforeX>afterX) { //위
            rDir=3;
            if(k ==0) dirW1 = 3;
            else if(k==1) dirW2 = 3;
            else if(k==2) dirW3 = 3;
            else if(k==3) dirW4 = 3;
            else dirW5 = 3;
            return 'R';
        }
        else if(beforeY<afterY) { //오른
            rDir=0;
            if(k ==0) dirW1 = 0;
            else if(k==1) dirW2 = 0;
            else if(k==2) dirW3 = 0;
            else if(k==3) dirW4 = 0;
            else dirW5 = 0;
            return 'U';
        }
        else if(beforeY>afterY) { //왼
            rDir=1;
            if(k ==0) dirW1 = 1;
            else if(k==1) dirW2 = 1;
            else if(k==2) dirW3 = 1;
            else if(k==3) dirW4 = 1;
            else dirW5 = 1;
            return 'F';
        }

    }
    else if(rDir == 2){ //남
        if(beforeX < afterX) { //아래
            rDir = 2;
            if(k ==0) dirW1 = 2;
            else if(k==1) dirW2 = 2;
            else if(k==2) dirW3 = 2;
            else if(k==3) dirW4 = 2;
            else dirW5 = 2;
            return 'F';
        }  
        else if(beforeX>afterX) { //위
            rDir=3;
            if(k ==0) dirW1 = 3;
            else if(k==1) dirW2 = 3;
            else if(k==2) dirW3 = 3;
            else if(k==3) dirW4 = 3;
            else dirW5 = 3;
            return 'U';
        }
        else if(beforeY<afterY) { //오른
            rDir=0;
            if(k ==0) dirW1 = 0;
            else if(k==1) dirW2 = 0;
            else if(k==2) dirW3 = 0;
            else if(k==3) dirW4 = 0;
            else dirW5 = 0;
            return 'L';
        }
        else if(beforeY>afterY) { //왼
            rDir=1;
            if(k ==0) dirW1 = 1;
            else if(k==1) dirW2 = 1;
            else if(k==2) dirW3 = 1;
            else if(k==3) dirW4 = 1;
            else dirW5 = 1;
            return 'R';
        }     
    }
    else if(rDir == 3){ //북
        if(beforeX < afterX) { //아래
            rDir = 2;
            if(k ==0) dirW1 = 2;
            else if(k==1) dirW2 = 2;
            else if(k==2) dirW3 = 2;
            else if(k==3) dirW4 = 2;
            else dirW5 = 2;
            return 'U';
        }  
        else if(beforeX>afterX) { //위
            rDir=3;
            if(k ==0) dirW1 = 3;
            else if(k==1) dirW2 = 3;
            else if(k==2) dirW3 = 3;
            else if(k==3) dirW4 = 3;
            else dirW5 = 3;
            return 'F';
        }
        else if(beforeY<afterY) { //오른
            rDir=0;
            if(k ==0) dirW1 = 0;
            else if(k==1) dirW2 = 0;
            else if(k==2) dirW3 = 0;
            else if(k==3) dirW4 = 0;
            else dirW5 = 0;
            return 'R';
        }
        else if(beforeY>afterY) { //왼
            rDir=1;
            if(k ==0) dirW1 = 1;
            else if(k==1) dirW2 = 1;
            else if(k==2) dirW3 = 1;
            else if(k==3) dirW4 = 1;
            else dirW5 = 1;
            return 'L';
        }
    }
    
}
//////////////////////////////////////////////////////////////

void realMove(char c){
    
    if(c=='R')
        printf("|R");//오른쪽
    else if(c=='L') 
        printf("|L");//왼쪽
    else if(c=='F')
        printf("|F");//전진
    else if(c=='U')
        printf("|U");//U턴
}
void main(){
    while(visited != 0){
        minimumSearch();
        switch(g){
            case 1: 
                for (int i = 0;i<10;i++){
                    if(g_taskW1[i]!='N')
                        realMove(g_taskW1[i]);
                }
                printf("\n");
                visited=visited-16;             //visited=01111
                isVisited1 = 1;
                break;
            case 2:
                for (int i = 0;i<10;i++){
                    if(g_taskW2[i]!='N')
                        realMove(g_taskW2[i]);
                }
                printf("\n");
                visited=visited-8;              //visited=10111
                isVisited2 = 1;
                break;
            case 3:
                for (int i = 0;i<10;i++){
                    if(g_taskW3[i]!='N')
                        realMove(g_taskW3[i]);
                }
                printf("\n");
                visited=visited-4;              //visited=11011
                isVisited3 = 1;
                break;
            case 4:
                for (int i = 0;i<10;i++){
                    if(g_taskW4[i]!='N')
                        realMove(g_taskW4[i]);
                }
                printf("\n");
                visited=visited-2;              //visited=11101
                isVisited4 = 1;
                break;
            case 5:
                for (int i = 0;i<10;i++){
                    if(g_taskW5[i]!='N')
                        realMove(g_taskW5[i]);
                }
                printf("\n");
                visited=visited-1;              //visited=11110
                isVisited5 = 1;
                break;
        }
        printf("\n|||%d %d %d %d|||\n", g_x, g_y, t_x, t_y);
    }   
    
    if(visited == 0){                   //도착점을 향함
        
    }

}

