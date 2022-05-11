#include <bits/stdc++.h>
#define ERR 0.00001
using namespace std;
int N = 10000;
vector<array<double, 2>> upperLine;
vector<array<double, 2>> lowerLine;
double xr = INT_MAX, xl = INT_MIN, xm = 0, ans = INT_MIN;
multiset<double> x_intersect;
bool isNA = false, isINF = false, isAns = false;
double ay = INT_MIN, by = INT_MAX, smax = INT_MIN, smin=INT_MAX, tmax = INT_MIN, tmin = INT_MAX;

void intersect(array<double, 2> line1, array<double, 2> line2, array<double, 2> &point){
    if(abs(line1[0] - line2[0]) > ERR){
        double x = (double)((line2[1] - line1[1])/(line1[0]-line2[0]));
        double y = (double)(line1[0]*x + line1[1]);
        point[0] = x;
        point[1] = y;
    }
}
void PairAndPrune(){
    int lStart = lowerLine.size()-1, uStart = upperLine.size()-1;
    int lEnd = lowerLine.size()%2, uEnd = upperLine.size()%2;
    array<double, 2> point;
    //lower line
    for (int i = lStart; i > lEnd; i-=2){
        intersect(lowerLine[i], lowerLine[i-1], point);
        // printf("(%d, %d)", (*point)[0], (*point)[1]);
        if(!point.empty()){
            if(xl < point[0] && point[0] < xr) x_intersect.insert(point[0]);
            else if(point[0] >= xr){
                if(lowerLine[i][0] > lowerLine[i-1][0]) lowerLine.erase(lowerLine.begin() + i);
                else lowerLine.erase(lowerLine.begin()+i-1);
            }
            else{
                if(lowerLine[i][0] < lowerLine[i-1][0]) lowerLine.erase(lowerLine.begin() + i);
                else lowerLine.erase(lowerLine.begin()+i-1);
            }
        }
        else{
            if(lowerLine[i][0] < lowerLine[i-1][0]) lowerLine.erase(lowerLine.begin() + i);
            else lowerLine.erase(lowerLine.begin()+i-1);
        }
    }
    // upper line
    for (int i = uStart; i > uEnd; i-=2){
        intersect(upperLine[i], upperLine[i-1], point);
        if(!point.empty()){
            if(xl < point[0] && point[0] < xr) x_intersect.insert(point[0]);
            else if(point[0] >= xr){
                if(upperLine[i][0] < upperLine[i-1][0]) upperLine.erase(upperLine.begin() + i);
                else upperLine.erase(upperLine.begin()+i-1);
            }
            else{
                if(upperLine[i][0] > upperLine[i-1][0]) upperLine.erase(upperLine.begin() + i);
                else upperLine.erase(upperLine.begin()+i-1);
            }
        }
        else{
            if(upperLine[i][0] > upperLine[i-1][0]) upperLine.erase(upperLine.begin() + i);
            else upperLine.erase(upperLine.begin()+i-1);
        }
    }
}

void Bound(){
    ay = INT_MIN, by = INT_MAX, smax = INT_MIN, smin=INT_MAX, tmax = INT_MIN, tmin = INT_MAX;
    for(int i = 0; i < lowerLine.size(); i++) ay = max(ay, lowerLine[i][0]*xm + lowerLine[i][1]);
    for(int i = 0; i < upperLine.size(); i++) by = min(by, upperLine[i][0]*xm + upperLine[i][1]);
    for(int i = 0; i < lowerLine.size(); i++){
        if(abs(ay-lowerLine[i][0]*xm-lowerLine[i][1]) < ERR){
            // printf("xm = %f, slop = %f\n", xm, lowerLine[0][0]);
            smax = max(smax, lowerLine[i][0]);
            smin = min(smin, lowerLine[i][0]);
        }
    }
    for(int i = 0; i < upperLine.size(); i++){
        if(abs(by-upperLine[i][0]*xm-upperLine[i][1]) < ERR){
            tmax = max(tmax, upperLine[i][0]);
            tmin = min(tmin, upperLine[i][0]);
        }
    }
}
//==================================================
int main(){
    
    upperLine.reserve(N);
    lowerLine.reserve(N);
    int n, a, b, c;
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf("%d%d%d", &a, &b, &c);
        if(b > 0) {
            array<double, 2> line = {(double)-a/b, (double)c/b};
            upperLine.push_back(line);
        }
        else if (b < 0){
            array<double, 2> line = {(double)-a/b, (double)c/b};
            lowerLine.push_back(line);
        }
        else{
            if(0 < a && a < xr) xr = (double)c/a;
            else if (xl < a && a < 0) xl = (double)c/a;
        }
    }
    while(true){
        // printf("==============\n");
        // printf("%d\n", upperLine.size() + lowerLine.size());
        // printf("xl =%f, xr = %f\n", xl, xr);
        if(xr < xl){
            isNA = true;
            break;
        }
        if(lowerLine.empty()){
            isINF = true;
            break;
        }
        if(lowerLine.size() == 1 && upperLine.size() <= 1){
            if(upperLine.empty()){
                if ((lowerLine[0][0] > 0 && xl == INT_MIN) || (lowerLine[0][0] < 0 && xr == INT_MAX)) isINF = true;
                else{
                    ans = min(lowerLine[0][0] * xl + lowerLine[0][1], lowerLine[0][0] * xr + lowerLine[0][1]);
                    isAns = true;
                }
                break;
            }
            else{
                if(abs(lowerLine[0][1] - upperLine[0][1]) < ERR){
                    if(lowerLine[0][1] > upperLine[0][1]) isNA = true;
                    else{
                        if ((lowerLine[0][0] > 0 && xl == INT_MIN) || (lowerLine[0][0] < 0 && xr == INT_MAX)) isINF = true;
                        else{
                            ans = min(lowerLine[0][0] * xl + lowerLine[0][1], lowerLine[0][0] * xr + lowerLine[0][1]);
                            isAns = true;
                        }
                        break;
                    }
                    break;
                }
                else{
                    array<double, 2> point;
                    intersect(lowerLine[0], upperLine[0], point);
                    if(upperLine[0][0] > lowerLine[0][0] && lowerLine[0][0] >= 0){
                        if(point[0] > xr) isNA = true;
                        else if(point[0] >= xl){
                            ans = point[1];
                            isAns = true;
                        }
                        else if(xl == INT_MIN) isINF = true;
                        else{
                            ans = lowerLine[0][0]*xl + lowerLine[0][1];
                            isAns = true;
                        }
                        
                        break;
                    }
                    if(lowerLine[0][0] >= 0 && lowerLine[0][0] > upperLine[0][0]){
                        if(point[0] < xl) isNA = true;
                        else if(xl == INT_MIN) isINF = true;
                        else{
                            ans = lowerLine[0][0]*xl + lowerLine[0][1];
                            isAns = true;
                        }
                        
                        break;
                    }
                    if(0 >= lowerLine[0][0] && lowerLine[0][0] > upperLine[0][0]){
                        if(point[0] < xl) isNA = true;
                        else if(point[0] <= xr){
                            ans = point[1];
                            isAns = true;
                        }
                        else if (xr == INT_MAX) isINF = true;
                        else{
                            ans = lowerLine[0][0]*xr + lowerLine[0][1];
                            isAns = true;
                        }
                        
                        break;
                    }
                    if(0 >= lowerLine[0][0] && upperLine[0][0] > lowerLine[0][0]){
                        if(point[0] > xr) isNA = true;
                        else if(xr == INT_MAX) isINF = true;
                        else{
                            ans = lowerLine[0][0]*xr + lowerLine[0][1];
                            isAns = true;
                        }
                        break;
                    }
                }
            }
        }
        
        x_intersect.clear();
        PairAndPrune();
        if(!x_intersect.empty()) xm = *next(x_intersect.begin(), x_intersect.size() / 2);
        Bound();
        // printf("xm = %f\n", xm);
        // printf("%f, %f, %f, %f, %f, %f\n", ay, by, smax, smin, tmax, tmin);
        if(ay <= by && smin <= smax && smax < 0) xl = xm;
        if(ay <= by && smax >= smin && smin > 0) xr = xm;
        if(ay <= by && smin <= 0 && 0 <= smax) {
            ans = ay;
            isAns = true;
            break;
        }
        if(ay > by && smax < tmin) xl = xm;
        if(ay > by && smin > tmax) xr = xm;
        if(ay > by && smax >= tmin && smin <= tmax){
            isNA = true;
            break;
        }
        PairAndPrune();
    }
    // printf("intmin = %f, ans = %f\n",INT_MIN, ans);
    if(ans == INT_MIN) isINF = true;
    if(isNA) printf("NA\n");
    else if(isINF) printf("-INF\n");
    else printf("%d\n", (int)round(ans));
    return 0;
}