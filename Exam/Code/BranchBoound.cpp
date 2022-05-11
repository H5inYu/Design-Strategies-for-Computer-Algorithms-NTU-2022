#include <bits/stdc++.h>
using namespace std;
struct Item {
    int weight, value;
};
struct Node{
    int level;
    int curW;
    int curV;
    int ub;
};
bool ItemComp(Item a, Item b){
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}
struct NodeComp{
    bool operator()(Node& n1, Node& n2){
        if(n1.ub == n2.ub) return n1.level < n2.level;
        return n1.ub < n2.ub;
    }
};

int W, itemNumber, weight, value;
vector<Item> itemList;

int Bound(float curValue, int curWeight, int level){
    if(curWeight >= W) return 0;
    for (int i=level; i<itemNumber; i++){
        if(curWeight + itemList[i].weight <= W) {
            curWeight += itemList[i].weight;
            curValue += itemList[i].value;
        }
        else {
            curValue += (W-curWeight) * itemList[i].value/itemList[i].weight;
            break;
        }
    }
    return curValue;    
}
int Knapsack(){
    priority_queue<Node, vector<Node>, NodeComp> pq;
    int l = -1, curW = 0, curV = 0, maxProfit = 0;
    int ub = Bound(curV, curW, 0);
    Node u = {l, curW, curV, ub};
    Node v;
    pq.push(u);
    while(!pq.empty()){
        u = pq.top();
        pq.pop();
        if(u.level == itemNumber-1) continue;
        u.level += 1;
        
        v.level = u.level;
        v.curW = u.curW;
        v.curV = u.curV;

        //u take the item
        u.curW += itemList[u.level].weight;
        u.curV += itemList[u.level].value;
        if(u.curW <= W) {
            maxProfit = max(u.curV, maxProfit);
        }
        u.ub = Bound(u.curV, u.curW, u.level+1);
        if(u.ub > maxProfit) pq.push(u);
        // v not take the item
        v.ub = Bound(v.curV, v.curW, v.level+1);
        if(v.ub > maxProfit) pq.push(v);
    }
    return maxProfit;
}

int main(){
    scanf("%d %d", &W, &itemNumber);
    itemList.resize(itemNumber);
    for(int i=0; i<itemNumber; i++){
        scanf("%d %d", &itemList[i].value, &itemList[i].weight);
    }
    sort(itemList.begin(), itemList.end(), ItemComp);
    printf("%d\n", Knapsack());
}