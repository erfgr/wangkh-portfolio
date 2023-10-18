#include "dsa.h"
#include <cstdio>
#include <cstdlib>

namespace lsort {
void merge(const List &la, const List &lb, List &out) {
  auto pa = la.begin(), pb = lb.begin();
  auto oa = out.before_begin();
  while (pa != la.end() && pb != lb.end()) {
    if (*pa < *pb) {
      oa = out.insert_after(oa, *pa);
      ++pa;
    } else {
      oa = out.insert_after(oa, *pb);
      ++pb;
    }
  }
  while (pa != la.end()) {
    oa = out.insert_after(oa, *pa);
    ++pa;
  }
  while (pb != lb.end()) {
    oa = out.insert_after(oa, *pb);
    ++pb;
  }
}

void partition(const List &la, List &leq, List &gt, Key pivot) {
  auto pa = la.begin();
  auto oa = leq.before_begin(), ob = gt.before_begin();
  while (pa != la.end()) {
    if (*pa <= pivot) {
      oa = leq.insert_after(oa, *pa);
    } else {
      ob = gt.insert_after(ob, *pa);
    }
    ++pa;
  }
 }
Key select_pivot(const List &la) {
  int len = 0;
  for (auto pa = la.begin(); pa != la.end(); ++pa) {
    ++len;
  }
  int index = rand() % len;
  auto pa = la.begin();
  for (int i = 0; i < index; ++i) {
    ++pa;
  }
  return *pa;
}
} // namespace lsort