/**
 * Author: Unknown
 * Date: 2026-07-26
 * License: Unknown
 * Source: Unknown
 * enDescription: Generic lazy segment tree using external Info and Tag.
 * Description: 通用懒标记线段树，使用外部定义的 Info 和 Tag。
 * Time: O(\log N).
 * Status: stress-tested
 */
#pragma once

#include "TagInfo.h"

template<typename Info, typename Tag> struct Seg {
  vector<Info> seg;vector<Tag> tag;
  Seg(const vector<Info> &val):seg(sz(val)*4), tag(sz(val)*4) {
    auto build = [&](int l, int r, int root, auto &&self) {
      if (r - l == 1) {
        seg[root] = val[l];
        return;
      }
      int mid = (l + r) >> 1;
      self(l, mid, root << 1, self);
      self(mid, r, root << 1 | 1, self);
      seg[root]=Info::merge(seg[root << 1],seg[root << 1 | 1]);
    };
    build(0, sz(val), 1, build);
  }
  void push(int l, int r, int root) {
    int m = (l + r) >> 1;
    seg[root << 1].update(tag[root], l, m);
    tag[root << 1].update(tag[root], l, m);
    seg[root << 1 | 1].update(tag[root], m, r);
    tag[root << 1 | 1].update(tag[root], m, r);
    tag[root] = Tag();
  }
  void update(int l,int r,int ql,int qr,int root,const Tag &t){
    if (r <= ql || qr <= l) return;
    if (ql <= l && r <= qr) {
      seg[root].update(t, l, r);
      tag[root].update(t, l, r);
      return;
    }
    push(l, r, root);
    int m = (l + r) >> 1;
    update(l, m, ql, qr, root << 1, t);
    update(m, r, ql, qr, root << 1 | 1, t);
    seg[root] = Info::merge(seg[root << 1],seg[root << 1 | 1]);
  }
  Info query(int l, int r, int ql, int qr, int root) {
    if (r <= ql || qr <= l) return Info();
    if (ql <= l && r <= qr) return seg[root];
    push(l, r, root);
    int m = (l + r) >> 1;
    return Info::merge(query(l, m, ql, qr, root << 1),
                       query(m, r, ql, qr, root << 1 | 1));
  }
};
