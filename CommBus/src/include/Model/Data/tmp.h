#include <vector>
#include <stdio.h>

struct non_trivial {
  ~non_trivial() { printf("this just isn't trivial\n"); }
};

struct constructible {
  constructible(std::vector<int>&&) {}
};

struct some_union {
  union {
    non_trivial nt;
    constructible c;
  };

  enum {
    type_nt,
    type_c,
  } type;

  some_union(const non_trivial& nt) : nt(nt), type(type_nt) {}
  some_union(std::vector<int>&& v) : c(std::move(v)), type(type_c) {}

  ~some_union() {
    switch (type) {
      case type_nt: nt.~non_trivial();  return;
      case type_c:  c.~constructible(); return;
    }
  }
};