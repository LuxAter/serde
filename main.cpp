#define SERDE_IMPLEMENTATION
#include <iostream>

#include "serde.h"

int main(int argc, char* argv[]) {
  serde::node n;
  std::cout << sizeof(n) << "?\n";
  n["arden"]["dob"] = 1998;
  n["arden"]["grad"] = 2020;
  n["arden"]["majors"] = {"math", "cs", "physics"};
  n["sean"]["dob"] = 1998;
  n["sean"]["grad"] = 2020;
  n["sean"]["majors"] = {"math", "cs", "physics"};
  serde::node ra;
  ra["value"] = 3.1415;
  ra["name"] = "pi";
  n["numbers"].push_back(ra);
  ra["value"] = 2019;
  ra["name"] = "year";
  n["numbers"].push_back(ra);
  std::cout << n << '\n';
  std::cout << sizeof(n) << "?\n";
  n["numbers"][1]["value"] = 2020;
  n["arden"]["age"] = 21;
  std::cout << n << '\n';
  std::cout << sizeof(n) << "?\n";

  auto& tmp = n["sean"];
  tmp["hello"] = 3.141592;
  tmp["list"] = {"hello", "world"};
  auto& sl = tmp["object"]["sub_list"];
  sl.push_back("hello world");
  sl.push_back(2020);

  std::cout << n << '\n';
  std::cout << sizeof(n) << "?\n";
  return 0;
}
