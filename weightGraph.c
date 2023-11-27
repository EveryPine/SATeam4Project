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
int tmp_count = 0;
char taskArr[20], tmp_taskArr[20];
int g_x = 4, g_y = 4;
float weight = -100;
int t_x, t_y;

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
char robotDir(int beforeX, int beforeY, int afterX, int afterY);
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
                        printf("111111\n");
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
    else if(k == 3){
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
    char taskW1[10] = {'N','N','N','N','N','N','N','N','N','N'};
    char taskW2[10] = {'N','N','N','N','N','N','N','N','N','N'};
    char taskW3[10] = {'N','N','N','N','N','N','N','N','N','N'};
    char taskW4[10] = {'N','N','N','N','N','N','N','N','N','N'};
    char taskW5[10] = {'N','N','N','N','N','N','N','N','N','N'};

    int countW1 = 0;
    int countW2 = 0;
    int countW3 = 0;
    int countW4 = 0;
    int countW5 = 0;
    for(int i = 0; i < 5; i++){
        printf("==================\n");
        int a = Red[i][0]; int b = Red[i][1];
        makeWeightGraph(a, b, i);
        /*
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
        */
        
        int *result; // 포인터 변수 선언
        t_x = g_x,  t_y = g_y;
        weight = -100;
        rDir = 1;
        int ii = 0;
        
        while(1){
            result = moveOneBlock(t_x, t_y, i); // 포인터에 반환값 할당
            //printf("%c ", robotDir(t_x, t_y, result[0], result[1]));
            if(i == 0) {
                taskW1[ii]=robotDir(t_x, t_y, result[0], result[1]);
                countW1++;
            }
            else if(i == 1) {
                taskW2[ii]=robotDir(t_x, t_y, result[0], result[1]);
                countW2++;
            }
            else if(i == 2) {   
                taskW3[ii]=robotDir(t_x, t_y, result[0], result[1]);
                countW3++;
            }
            else if(i == 3) {
                taskW4[ii]=robotDir(t_x, t_y, result[0], result[1]);
                countW4++;
            }
            else if(i == 4) {
                taskW5[ii]=robotDir(t_x, t_y, result[0], result[1]);
                countW5++;
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
    int g=1;
    myStrcpy(taskArr, taskW1);
    
    if(min > countW2) {
        min = countW2;
        g=2;
        myStrcpy(taskArr, taskW2);
    }
    if(min > countW3) {
        min = countW3;
        g=3;
        myStrcpy(taskArr, taskW3);
    }
    if(min > countW4) {
        min = countW4;
        g=4;
        myStrcpy(taskArr, taskW4);
    }
    if(min > countW5) {
        min = countW5;
        g=5;
        myStrcpy(taskArr, taskW5);
    }

    for(int aa = 0; aa < 10; aa++) printf("=%c ", taskArr[aa]);
    printf("\n");
    
    
    return 0;
}

char robotDir(int beforeX, int beforeY, int afterX, int afterY){
    tmp_count++;
    if(rDir == 0) { //동
        if(beforeX < afterX) { //아래
            rDir = 2;
            return 'R';
        }  
        else if(beforeX>afterX) { //위
            rDir=3;
            return 'L';
        }
        else if(beforeY<afterY) { //오른 
            rDir=0;
            return 'F';
        }
        else if(beforeY>afterY) { // 왼
            rDir=1;
            return 'U';
        }
    }
    else if(rDir == 1){ //서
        if(beforeX < afterX) { //아래
            rDir = 2;
            return 'L';
        }  
        else if(beforeX>afterX) { //위
            rDir=3;
            return 'R';
        }
        else if(beforeY<afterY) { //오른
            rDir=0;
            return 'U';
        }
        else if(beforeY>afterY) { //왼
            rDir=1;
            return 'F';
        }

    }
    else if(rDir == 2){ //남
        if(beforeX < afterX) { //아래
            rDir = 2;
            return 'F';
        }  
        else if(beforeX>afterX) { //위
            rDir=3;
            return 'U';
        }
        else if(beforeY<afterY) { //오른
            rDir=0;
            return 'L';
        }
        else if(beforeY>afterY) { //왼
            rDir=1;
            return 'R';
        }     
    }
    else if(rDir == 3){ //북
        if(beforeX < afterX) { //아래
            rDir = 2;
            return 'U';
        }  
        else if(beforeX>afterX) { //위
            rDir=3;
            return 'F';
        }
        else if(beforeY<afterY) { //오른
            rDir=0;
            return 'R';
        }
        else if(beforeY>afterY) { //왼
            rDir=1;
            return 'L';
        }
    }
    
}
//////////////////////////////////////////////////////////////


