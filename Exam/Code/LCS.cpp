#include <bits/stdc++.h>
#define MAXLEN 105
using namespace std;
struct cmp {
  bool operator()(const char* s1, const char* s2) const {
    return strcmp(s1, s2) < 0;
  }
};
multiset<const char*, cmp> ALLLCS;
int LCSLen, LCSNum, lenX, lenY;
int LCSDP[MAXLEN][MAXLEN];
char X[MAXLEN], Y[MAXLEN];
stack<int> s;
stack<char*> cS;

void LCSMatrix(){
    for (int i = 1; i <= lenX; ++i){
        for (int j = 1; j <= lenY; ++j){
            if (X[i - 1] == Y[j - 1]) {
                LCSDP[i][j] = LCSDP[i - 1][j - 1] + 1;
            } 
            else {
                LCSDP[i][j] = max(LCSDP[i - 1][j], LCSDP[i][j - 1]);
            }
        }
    }
}
void FindAllLCS(){
    char c = '\0';
    s.push(lenX-1);
    s.push(lenY-1);
    s.push(0);
    cS.push(&c);
    while(!s.empty()){
        int curLen = s.top();
        s.pop();
        int yindex = s.top();
        s.pop();
        int xindex = s.top();
        s.pop();
        char* curLCS = cS.top();
        cS.pop(); 
        if(curLen == LCSLen) {
            ALLLCS.insert(curLCS);
            continue;
        }
        if(xindex == -1 || yindex == -1) continue;
        for (int i = xindex; i > LCSLen-curLen-2; i--){
            if(LCSDP[i+1][yindex+1] + curLen < LCSLen) break;
            for (int j = yindex; j > LCSLen-curLen-2; j--){
                if(LCSDP[i+1][j+1] + curLen < LCSLen) break;
                if(X[i] == Y[j] && LCSDP[i+1][j+1] + curLen == LCSLen){
                    char* tmp = (char*)malloc(sizeof(char) * (curLen + 2));
                    tmp[0] = X[i];
                    strcpy(tmp+1, curLCS);
                    s.push(i-1);
                    s.push(j-1);
                    s.push(curLen+1);
                    cS.push(tmp);
                }
            }
        } 
    }
}

int main(){
    scanf("%s%s", X, Y);
    lenX = strlen(X);
    lenY = strlen(Y);
    memset(LCSDP, 0, sizeof(LCSDP));
    LCSMatrix();
    LCSLen = LCSDP[lenX][lenY];
    FindAllLCS();
    LCSNum = ALLLCS.size();
    printf("%d %d\n", LCSLen, LCSNum);
    for (const auto& item : ALLLCS) {
        printf("%s\n", item);
    }

    return 0;
}