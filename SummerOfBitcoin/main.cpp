#include <iostream>

#include <string>

#include <vector>

#include <algorithm>

#include <queue>

#include <deque>

#include <iterator>

#include <list>

#include <stack>

#include <map>

#include <set>

#include <functional>

#include <numeric>

#include <utility>

#include <time.h>

#include <math.h>

#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <assert.h>
 //#pragma once
using namespace std;

class mempool {
  public:
    string txid;
  int fee;
  int w;
  vector < string > parent;
  mempool(string id, int f, int we, vector < string > pa) {
    txid = id;
    fee = f;
    w = we;
    parent = pa;
  }
};

void bringAll(vector < mempool > & arr, vector < vector < int > > & graph, int curr, vector < string > & ans, int & wi, int & temp) {
  wi += arr[curr].w;
  temp += arr[curr].fee;
  for (int i = 0; i < graph[curr].size(); i++) {
    bringAll(arr, graph, graph[curr][i], ans, wi, temp);
  }
  ans.push_back(arr[curr].txid);
  return;
}

int main() {

  freopen("input.txt", "r", stdin);
  freopen("block_output.txt", "w", stdout);
  map < string, int > m;
  int counter = 0;
  int n;
  n = 5214;
  vector < mempool > arr;
  int max_weight = 4000000;
  int ww = n;
  while (n--) {
    string s, pa;
    int f, we;
    cin >> s >> f >> we >> pa;
    m[s] = counter;
    counter++;
    vector < string > p;
    if (pa[0] != 'N') {
      for (int i = 0; i < pa.length();) {
        string help = "";
        int j;
        for (j = i; j < pa.length(); j++) {
          if (pa[j] == ';') break;
          help += pa[j];
        }
        p.push_back(help);
        i = j + 1;
      }
    }
    mempool newdata(s, f, we, p);
    arr.push_back(newdata);
  }
  vector < vector < int > > graph(ww, vector < int > ());
  for (int i = 0; i < ww; i++) {
    for (int j = 0; j < arr[i].parent.size(); j++) graph[i].push_back(m[arr[i].parent[j]]);
  }
  vector < int > fe, weight;
  vector < vector < string > > pare;
  for (int i = 0; i < ww; i++) {
    int fee_a = 0, we_a = 0;
    vector < string > help;
    bringAll(arr, graph, i, help, we_a, fee_a);
    fe.push_back(fee_a);
    weight.push_back(we_a);
    pare.push_back(help);
  }
  vector < pair < int, pair < int, vector < string > > > > ans;
  for (int i = 0; i < ww; i++) {

    pair < int, pair < int, vector < string > > > xx;
    xx.first = fe[i], xx.second.first = weight[i], xx.second.second = pare[i];
    ans.push_back(xx);
  }
  sort(ans.begin(), ans.end());
  reverse(ans.begin(), ans.end());
  int curr = 0;
  vector < vector < string > > x;
  int i = 0;
  long long sato = 0;
  while (i < ans.size() && (curr + ans[i].second.first) < max_weight) {
    curr += ans[i].second.first;
    sato += ans[i].first;
    x.push_back(ans[i].second.second);
    i++;
  }
  for (i = 0; i < x.size(); i++) {
    for (int j = 0; j < x[i].size(); j++) cout << x[i][j] << endl;
  }
}
