/**
 * Author: Lucian Bicsi, modified
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * enDescription: Zero-indexed segment tree over an Info type. Bounds are inclusive to the left and exclusive to the right.
 * Info must be default-constructible and provide static Info merge(const Info\&, const Info\&).
 * Description: 0-indexed 线段树，左闭右开区间。
 * 节点为 Info ，具有默认构造，合并函数 static Info merge(const Info\&, const Info\&)。
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once

template<typename Info>struct SegmentTree {
  int n;vector<Info> seg;
  SegmentTree(const vector<Info> &val): n(sz(val)), seg(2 * n){
    rep(i, 0, n) seg[n + i] = val[i];
    for (int i = n - 1; i > 0; --i)
      seg[i] = Info::merge(seg[i << 1], seg[i << 1 | 1]);
  }
  void update(int pos, const Info &val) {
    for (seg[pos += n] = val; pos >>= 1;)
      seg[pos] = Info::merge(seg[pos << 1], seg[pos << 1 | 1]);
  }
  Info query(int l, int r) {// query [l, r)
    Info resl{}, resr{};
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) resl = Info::merge(resl, seg[l++]);
      if (r & 1) resr = Info::merge(seg[--r], resr);
    }
    return Info::merge(resl, resr);
  }
};
