/**
 * Author: Unknown
 * Date: Unknown
 * License: Unknown
 * Source: Unknown
 * Description: 线段树节点 Info 与懒标记 Tag 的示例。
 * Time: O(1).
 * Status: 未确认
 */
#pragma once

struct Tag {
  ll mul = 1, add = 0;
  void update(const Tag &t, int l, int r) {
    mul = (mul * t.mul) % MOD;
    add = (add * t.mul) % MOD;
    add = (add + t.add) % MOD;
  }
};
struct Info {
  ll val = 0;
  void update(const Tag &t, int l, int r) {
    val = (val * t.mul + t.add * (r - l)) % MOD;
  }
  static Info merge(const Info &a, const Info &b) {
    return {(a.val + b.val) % MOD};
  }
};
