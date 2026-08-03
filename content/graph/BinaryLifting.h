/**
 * Author: Johan Sannemo
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * enDescription: Calculate power of two jumps in a tree,
 * to support fast upward jumps and LCAs.
 * Assumes the root node points to itself.
 * Description: 计算树上2的幂次跳跃，以支持快速向上跳跃和LCA。
 * 根节点\textbf{指向自己}。
 * Time: construction $O(N \log N)$, queries $O(\log N)$
 * Status: Tested at Petrozavodsk, also stress-tested via LCA.cpp
 */
#pragma once

vector<vi> treeJump(vi& fa){
  int pw = 1, k = 1;
  while(pw < sz(fa)) pw *= 2, k++;
  vector<vi> tbl(k, fa);
  rep(i,1,k) rep(j,0,sz(fa))
    tbl[i][j] = tbl[i-1][tbl[i-1][j]];
  return tbl;
}

int jmp(vector<vi>& tbl, int nod, int steps){
  rep(i,0,sz(tbl))
    if(steps&(1<<i)) nod = tbl[i][nod];
  return nod;
}

int lca(vector<vi>& tbl, vi& depth, int a, int b) {
  if (depth[a] < depth[b]) swap(a, b);
  a = jmp(tbl, a, depth[a] - depth[b]);
  if (a == b) return a;
  for (int i = sz(tbl); i--;) {
    int pa = tbl[i][a], pb = tbl[i][b];
    if (pa != pb) a = pa, b = pb;
  }
  return tbl[0][a];
}
