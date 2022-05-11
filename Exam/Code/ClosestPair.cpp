#include <bits/stdc++.h>
using namespace std;
struct Point{
    int id;
    long long x, y;
};
struct Pair{
    int id1, id2;
    Pair();
    Pair(int a, int b){
        if(a < b) {
            id1 = a;
            id2 = b;
        }
        else{
            id1 = b;
            id2 = a;
        }
    }
};
vector<Pair> result;
long long cloesestDistance = LLONG_MAX;

bool CompX(Point p1, Point p2){
    if(p1.x == p2.x) return p1.y < p2.y;
    return p1.x < p2.x;
}
bool CompY(Point p1, Point p2){
    if(p1.y == p2.y) return p1.x < p2.x;
    return p1.y < p2.y;
}
bool PairComp(Pair p1, Pair p2){
    if(p1.id1 == p2.id1) return p1.id2 < p2.id2;
    return p1.id1 < p2.id1;
}
bool PairEqual(Pair p1, Pair p2){
    return p1.id1 == p2.id1 && p1.id2 == p2.id2;
}
long long Distance(Point p1, Point p2){
    return (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y);
}

void ClosestPair(Point px[], Point py[], int left, int right){
    if(right - left < 2) return;
    if(right - left == 2){
        if(cloesestDistance == Distance(px[left], px[right-1])){
            Pair pair(px[left].id, px[right-1].id);
            result.push_back(pair);
        }
        else if(cloesestDistance > Distance(px[left], px[right-1])){ 
            cloesestDistance = Distance(px[left], px[right-1]);
            Pair pair(px[left].id, px[right-1].id);
            result.clear();
            result.push_back(pair);
        }
        return;
    }
    int mid = (left+right)/2;
    Point pyl[mid-left], pyr[right-mid];
    int li=0, ri=0;
    for(int i=0; i < right-left; i++){
        if((py[i].x < px[mid].x || (py[i].x == px[mid].x && py[i].y < px[mid].y)) && li < mid-left){
            pyl[li++] = py[i];
        }
        else{
            pyr[ri++] = py[i];
        }
    }
    ClosestPair(px, pyl, left, mid);
    ClosestPair(px, pyr, mid, right);
    // merge
    vector<Point> midPoints;
    for(int i=0; i < right-left; i++){
        if(abs(py[i].x-px[mid].x) <= sqrt(cloesestDistance)) midPoints.push_back(py[i]);
    }
    for(int i = 0; i < midPoints.size(); i++){
        for(int j = i+1; j < midPoints.size() && abs(midPoints[j].y-midPoints[i].y) <= sqrt(cloesestDistance); j++){
            if(Distance(midPoints[i], midPoints[j]) < cloesestDistance){
                cloesestDistance = Distance(midPoints[i], midPoints[j]);
                Pair p(midPoints[i].id, midPoints[j].id);
                result.clear();
                result.push_back(p);
            }
            else if(Distance(midPoints[i], midPoints[j]) == cloesestDistance){
                Pair p(midPoints[i].id, midPoints[j].id);
                result.push_back(p);
            }
        }
    }
}

int main(int argc, char **argv){
    int N;
    scanf("%d", &N);
    //=============
    // FILE *file;
    // file = fopen(argv[1], "r");
    // fscanf(file, "%d", &N);
    //============== 
    Point px[N], py[N];
    for (int i=0; i<N; i++) {
        px[i].id = i+1;
        scanf("%lld %lld",&px[i].x, &px[i].y);
        // fscanf(file, "%lld%lld", &px[i].x, &px[i].y);
        py[i].id = px[i].id;
        py[i].x = px[i].x;
        py[i].y = px[i].y;
    }
    fclose(file);
    // printf("Her");
    sort(px, px+N, CompX); 
    sort(py, py+N, CompY);
    ClosestPair(px, py, 0, N);
    // printf("THERE\n");
    
    sort(result.begin(), result.end(), PairComp);
    result.erase(unique(result.begin(), result.end(), PairEqual), result.end());
    printf("%lld %d\n", cloesestDistance, result.size());
    for (int i = 0; i < result.size(); i++) printf("%d %d\n", result[i].id1, result[i].id2);
}