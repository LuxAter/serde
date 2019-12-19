/*
 * Copyright (c) 2019 Arden Rasmussen
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef SERDE_H
#define SERDE_H

#include <initializer_list>
#include <iostream>
#include <map>
#include <string>
#include <type_traits>
#include <vector>

namespace serde {
  enum NodeType { STRING, ARRAY, OBJECT, NUMBER, BOOLEAN, NONE };
  enum NodeNumberType { S, US, I, UI, L, UL, LL, ULL, F, D, LD, N };
  struct node {
    node();
    node(const short& v);
    node(const unsigned short& v);
    node(const int& v);
    node(const unsigned& v);
    node(const long& v);
    node(const unsigned long& v);
    node(const long long& v);
    node(const unsigned long long& v);
    node(const float& v);
    node(const double& v);
    node(const long double& v);
    node(const bool& v);
    node(const char* v);
    node(const std::string& v);
    node(const node& copy);

    node& operator=(const short& v);
    node& operator=(const unsigned short& v);
    node& operator=(const int& v);
    node& operator=(const unsigned int& v);
    node& operator=(const long& v);
    node& operator=(const unsigned long& v);
    node& operator=(const long long& v);
    node& operator=(const unsigned long long& v);
    node& operator=(const float& v);
    node& operator=(const double& v);
    node& operator=(const long double& v);
    node& operator=(const bool& v);
    template <typename T>
    node& operator=(const std::initializer_list<T>& v);
    template <typename K, typename V>
    node& operator=(const std::initializer_list<std::pair<K, V>>& v);
    template <typename T>
    node& operator=(const std::vector<T>& v);
    template <typename K, typename V>
    node& operator=(const std::map<K, V>& v);
    node& operator=(const char* v);
    node& operator=(const std::string& v);
    node& operator=(const node& copy);

    operator short() const;
    operator unsigned short() const;
    operator int() const;
    operator unsigned int() const;
    operator long() const;
    operator unsigned long() const;
    operator long long() const;
    operator unsigned long long() const;
    operator float() const;
    operator double() const;
    operator long double() const;
    operator bool() const;
    operator std::string() const;

    template <typename T, typename = typename std::enable_if<
                              std::is_arithmetic<T>::value>::type>
    T get_number() const;
    short get_short() const;
    unsigned short get_ushort() const;
    int get_int() const;
    unsigned int get_uint() const;
    long get_lint() const;
    unsigned long get_ulint() const;
    long long get_llint() const;
    unsigned long long get_ullint() const;
    float get_float() const;
    double get_double() const;
    long double get_ldouble() const;
    bool get_bool() const;
    std::string get_string() const;

    void clear();
    std::size_t size() const;
    void push_back(const node& n);
    void insert(const node& n);
    void insert(const std::size_t& pos, const node& n);
    void insert(const std::string& key, const node& n);

    node& operator[](const std::size_t& id);
    const node& operator[](const std::size_t& id) const;
    node& at(const std::size_t& id);
    const node& at(const std::size_t& id) const;
    node& operator[](const char* key);
    node& operator[](const std::string& key);
    const node& operator[](const std::string& key) const;
    node& at(const std::string& id);
    const node& at(const std::string& id) const;

    NodeType value_type = NONE;
    NodeNumberType number_type = N;
    union {
      short s;
      unsigned short us;
      int i;
      unsigned int ui;
      long l;
      unsigned long ul;
      long long ll;
      unsigned long long ull;
      float f;
      double d;
      long double ld;
      bool boolean_value;
    };
    std::string string_value;
    std::map<std::string, node> object_value;
    std::vector<node> array_value;
  };
  std::ostream& operator<<(std::ostream& out, const node& n);
}  // namespace serde

#endif  // SERDE_H

#ifdef SERDE_IMPLEMENTATION

serde::node::node() : value_type(serde::NodeType::NONE) {}
serde::node::node(const short& v)
    : value_type(serde::NodeType::NUMBER),
      number_type(serde::NodeNumberType::S),
      s(v) {}
serde::node::node(const unsigned short& v)
    : value_type(serde::NodeType::NUMBER),
      number_type(serde::NodeNumberType::US),
      us(v) {}
serde::node::node(const int& v)
    : value_type(serde::NodeType::NUMBER),
      number_type(serde::NodeNumberType::I),
      i(v) {}
serde::node::node(const unsigned int& v)
    : value_type(serde::NodeType::NUMBER),
      number_type(serde::NodeNumberType::UI),
      ui(v) {}
serde::node::node(const long& v)
    : value_type(serde::NodeType::NUMBER),
      number_type(serde::NodeNumberType::L),
      l(v) {}
serde::node::node(const unsigned long& v)
    : value_type(serde::NodeType::NUMBER),
      number_type(serde::NodeNumberType::UL),
      ul(v) {}
serde::node::node(const long long& v)
    : value_type(serde::NodeType::NUMBER),
      number_type(serde::NodeNumberType::LL),
      ll(v) {}
serde::node::node(const unsigned long long& v)
    : value_type(serde::NodeType::NUMBER),
      number_type(serde::NodeNumberType::ULL),
      ull(v) {}
serde::node::node(const float& v)
    : value_type(serde::NodeType::NUMBER),
      number_type(serde::NodeNumberType::F),
      f(v) {}
serde::node::node(const double& v)
    : value_type(serde::NodeType::NUMBER),
      number_type(serde::NodeNumberType::D),
      d(v) {}
serde::node::node(const long double& v)
    : value_type(serde::NodeType::NUMBER),
      number_type(serde::NodeNumberType::LD),
      ld(v) {}
serde::node::node(const bool& v)
    : value_type(serde::NodeType::BOOLEAN), boolean_value(v) {}
serde::node::node(const char* v)
    : value_type(serde::NodeType::STRING), string_value(v) {}
serde::node::node(const std::string& v)
    : value_type(serde::NodeType::STRING), string_value(v) {}
serde::node::node(const node& copy)
    : value_type(copy.value_type),
      number_type(copy.number_type),
      ld(copy.ld),
      string_value(copy.string_value),
      object_value(copy.object_value),
      array_value(copy.array_value) {}

serde::node& serde::node::operator=(const short& v) {
  value_type = serde::NodeType::NUMBER;
  number_type = serde::NodeNumberType::S;
  string_value.clear();
  object_value.clear();
  array_value.clear();
  s = v;
  return *this;
}
serde::node& serde::node::operator=(const unsigned short& v) {
  value_type = serde::NodeType::NUMBER;
  number_type = serde::NodeNumberType::US;
  string_value.clear();
  object_value.clear();
  array_value.clear();
  us = v;
  return *this;
}
serde::node& serde::node::operator=(const int& v) {
  value_type = serde::NodeType::NUMBER;
  number_type = serde::NodeNumberType::I;
  string_value.clear();
  object_value.clear();
  array_value.clear();
  i = v;
  return *this;
}
serde::node& serde::node::operator=(const unsigned int& v) {
  value_type = serde::NodeType::NUMBER;
  number_type = serde::NodeNumberType::UI;
  string_value.clear();
  object_value.clear();
  array_value.clear();
  ui = v;
  return *this;
}
serde::node& serde::node::operator=(const long& v) {
  value_type = serde::NodeType::NUMBER;
  number_type = serde::NodeNumberType::L;
  string_value.clear();
  object_value.clear();
  array_value.clear();
  l = v;
  return *this;
}
serde::node& serde::node::operator=(const unsigned long& v) {
  value_type = serde::NodeType::NUMBER;
  number_type = serde::NodeNumberType::UL;
  string_value.clear();
  object_value.clear();
  array_value.clear();
  ul = v;
  return *this;
}
serde::node& serde::node::operator=(const long long& v) {
  value_type = serde::NodeType::NUMBER;
  number_type = serde::NodeNumberType::LL;
  string_value.clear();
  object_value.clear();
  array_value.clear();
  ll = v;
  return *this;
}
serde::node& serde::node::operator=(const unsigned long long& v) {
  value_type = serde::NodeType::NUMBER;
  number_type = serde::NodeNumberType::ULL;
  string_value.clear();
  object_value.clear();
  array_value.clear();
  ull = v;
  return *this;
}
serde::node& serde::node::operator=(const float& v) {
  value_type = serde::NodeType::NUMBER;
  number_type = serde::NodeNumberType::F;
  string_value.clear();
  object_value.clear();
  array_value.clear();
  f = v;
  return *this;
}
serde::node& serde::node::operator=(const double& v) {
  value_type = serde::NodeType::NUMBER;
  number_type = serde::NodeNumberType::D;
  string_value.clear();
  object_value.clear();
  array_value.clear();
  d = v;
  return *this;
}
serde::node& serde::node::operator=(const long double& v) {
  value_type = serde::NodeType::NUMBER;
  number_type = serde::NodeNumberType::LD;
  string_value.clear();
  object_value.clear();
  array_value.clear();
  ld = v;
  return *this;
}
serde::node& serde::node::operator=(const bool& v) {
  value_type = serde::NodeType::BOOLEAN;
  number_type = serde::NodeNumberType::N;
  string_value.clear();
  object_value.clear();
  array_value.clear();
  boolean_value = v;
  return *this;
}
template <typename T>
serde::node& serde::node::operator=(const std::initializer_list<T>& v) {
  value_type = serde::NodeType::ARRAY;
  number_type = serde::NodeNumberType::N;
  object_value.clear();
  array_value.clear();
  string_value.clear();
  for (auto& it : v) {
    array_value.push_back(node(it));
  }
  return *this;
}
template <typename T>
serde::node& serde::node::operator=(const std::vector<T>& v) {
  value_type = serde::NodeType::ARRAY;
  number_type = serde::NodeNumberType::N;
  object_value.clear();
  array_value.clear();
  string_value.clear();
  for (auto& it : v) {
    array_value.push_back(node(it));
  }
  return *this;
}
template <typename K, typename V>
serde::node& serde::node::operator=(const std::map<K, V>& v) {
  value_type = serde::NodeType::OBJECT;
  number_type = serde::NodeNumberType::N;
  object_value.clear();
  array_value.clear();
  string_value.clear();
  for (auto& it : v) {
    object_value.insert({it.first, node(it.second)});
  }
  return *this;
}
serde::node& serde::node::operator=(const char* v) {
  value_type = serde::NodeType::STRING;
  number_type = serde::NodeNumberType::N;
  object_value.clear();
  array_value.clear();
  string_value = std::string(v);
  return *this;
}
serde::node& serde::node::operator=(const std::string& v) {
  value_type = serde::NodeType::STRING;
  number_type = serde::NodeNumberType::N;
  object_value.clear();
  array_value.clear();
  string_value = v;
  return *this;
}
serde::node& serde::node::operator=(const node& copy) {
  value_type = copy.value_type;
  number_type = copy.number_type;
  ld = copy.ld;
  string_value = copy.string_value;
  object_value = copy.object_value;
  array_value = copy.array_value;
  return *this;
}

serde::node::operator short() const { return get_number<short>(); }
serde::node::operator unsigned short() const {
  return get_number<unsigned short>();
}
serde::node::operator int() const { return get_number<int>(); }
serde::node::operator unsigned int() const {
  return get_number<unsigned int>();
}
serde::node::operator long() const { return get_number<long>(); }
serde::node::operator unsigned long() const {
  return get_number<unsigned long>();
}
serde::node::operator long long() const { return get_number<long long>(); }
serde::node::operator unsigned long long() const {
  return get_number<unsigned long long>();
}
serde::node::operator float() const { return get_number<float>(); }
serde::node::operator double() const { return get_number<double>(); }
serde::node::operator long double() const { return get_number<long double>(); }
serde::node::operator bool() const {
  if (value_type == serde::NodeType::BOOLEAN) return boolean_value;
  return bool();
}
serde::node::operator std::string() const {
  if (value_type == serde::NodeType::STRING) return string_value;
  return std::string();
}

template <typename T, typename>
T serde::node::get_number() const {
  switch (number_type) {
    case S:
      return static_cast<T>(s);
    case US:
      return static_cast<T>(us);
    case I:
      return static_cast<T>(i);
    case UI:
      return static_cast<T>(ui);
    case L:
      return static_cast<T>(l);
    case UL:
      return static_cast<T>(ul);
    case LL:
      return static_cast<T>(ll);
    case ULL:
      return static_cast<T>(ull);
    case F:
      return static_cast<T>(f);
    case D:
      return static_cast<T>(d);
    case LD:
      return static_cast<T>(ld);
    case N:
    default:
      return T();
  }
}
short serde::node::get_short() const { return get_number<short>(); }
unsigned short serde::node::get_ushort() const {
  return get_number<unsigned short>();
}
int serde::node::get_int() const { return get_number<int>(); }
unsigned int serde::node::get_uint() const {
  return get_number<unsigned int>();
}
long serde::node::get_lint() const { return get_number<long>(); }
unsigned long serde::node::get_ulint() const {
  return get_number<unsigned long>();
}
long long serde::node::get_llint() const { return get_number<long long>(); }
unsigned long long serde::node::get_ullint() const {
  return get_number<unsigned long long>();
}
float serde::node::get_float() const { return get_number<float>(); }
double serde::node::get_double() const { return get_number<double>(); }
long double serde::node::get_ldouble() const {
  return get_number<long double>();
}
bool serde::node::get_bool() const {
  if (value_type == serde::NodeType::BOOLEAN) return boolean_value;
  return bool();
}
std::string serde::node::get_string() const {
  if (value_type == serde::NodeType::STRING) return string_value;
  return std::string();
}

void serde::node::clear() {
  if (value_type == serde::NodeType::ARRAY)
    array_value.clear();
  else if (value_type == serde::NodeType::OBJECT)
    object_value.clear();
  else if (value_type == serde::NodeType::STRING)
    string_value.clear();
}
std::size_t serde::node::size() const {
  if (value_type == serde::NodeType::ARRAY)
    return array_value.size();
  else if (value_type == serde::NodeType::OBJECT)
    return object_value.size();
  else if (value_type == serde::NodeType::STRING)
    return string_value.size();
  return 0;
}

void serde::node::push_back(const node& n) {
  if (value_type == serde::NodeType::ARRAY)
    array_value.push_back(n);
  else {
    value_type = serde::NodeType::ARRAY;
    number_type = serde::NodeNumberType::N;
    string_value.clear();
    object_value.clear();
    array_value = std::vector<node>({n});
  }
}
void serde::node::insert(const node& n) {
  if (value_type == serde::NodeType::ARRAY)
    array_value.push_back(n);
  else {
    value_type = serde::NodeType::ARRAY;
    number_type = serde::NodeNumberType::N;
    string_value.clear();
    object_value.clear();
    array_value = std::vector<node>({n});
  }
}
void serde::node::insert(const std::size_t& pos, const node& n) {
  if (value_type == serde::NodeType::ARRAY)
    array_value.insert(array_value.begin() + pos, n);
  else {
    value_type = serde::NodeType::ARRAY;
    number_type = serde::NodeNumberType::N;
    string_value.clear();
    object_value.clear();
    array_value = std::vector<node>({n});
  }
}
void serde::node::insert(const std::string& key, const node& n) {
  if (value_type == serde::NodeType::OBJECT)
    object_value.insert({key, n});
  else {
    value_type = serde::NodeType::OBJECT;
    number_type = serde::NodeNumberType::N;
    string_value.clear();
    array_value.clear();
    object_value = std::map<std::string, node>({{key, n}});
  }
}

serde::node& serde::node::operator[](const std::size_t& id) {
  return array_value[id];
}
const serde::node& serde::node::operator[](const std::size_t& id) const {
  return array_value[id];
}
serde::node& serde::node::at(const std::size_t& id) {
  if (value_type == serde::NodeType::ARRAY) return array_value.at(id);
  throw std::out_of_range("node is not an array");
}
const serde::node& serde::node::at(const std::size_t& id) const {
  if (value_type == serde::NodeType::ARRAY) return array_value.at(id);
  throw std::out_of_range("node is not an array");
}
serde::node& serde::node::operator[](const char* key) {
  if (value_type != serde::NodeType::OBJECT) {
    value_type = serde::NodeType::OBJECT;
    number_type = serde::NodeNumberType::N;
    string_value.clear();
    array_value.clear();
  }
  return object_value[std::string(key)];
}
serde::node& serde::node::operator[](const std::string& key) {
  if (value_type != serde::NodeType::OBJECT) {
    value_type = serde::NodeType::OBJECT;
    number_type = serde::NodeNumberType::N;
    string_value.clear();
    array_value.clear();
  }
  return object_value[key];
}
serde::node& serde::node::at(const std::string& key) {
  if (value_type == serde::NodeType::OBJECT) return object_value.at(key);
  throw std::out_of_range("node is not an object");
}
const serde::node& serde::node::at(const std::string& key) const {
  if (value_type == serde::NodeType::OBJECT) return object_value.at(key);
  throw std::out_of_range("node is not an object");
}

std::ostream& serde::operator<<(std::ostream& out, const node& n) {
  switch (n.value_type) {
    case NONE:
      return out << "null";
    case STRING:
      return out << '"' << n.string_value << '"';
    case BOOLEAN:
      return out << n.boolean_value;
    case NUMBER:
      switch (n.number_type) {
        case S:
          return out << n.s;
        case US:
          return out << n.us;
        case I:
          return out << n.i;
        case UI:
          return out << n.ui;
        case L:
          return out << n.l;
        case UL:
          return out << n.ul;
        case LL:
          return out << n.ll;
        case ULL:
          return out << n.ull;
        case F:
          return out << n.f;
        case D:
          return out << n.d;
        case LD:
          return out << n.ld;
        default:
          return out << "NUMBER";
      }
    case ARRAY:
      out << '[';
      for (std::size_t i = 0; i < n.array_value.size() - 1; ++i) {
        out << n.array_value[i] << ',';
      }
      return out << n.array_value.back() << ']';
    case OBJECT:
      out << '{';
      for (auto it = n.object_value.begin(); it != n.object_value.end(); it++) {
        out << '"' << it->first << "\":" << it->second;
        if (it != --n.object_value.end()) out << ',';
      }
      return out << '}';
    default:
      return out << "NODE";
  }
}

#endif  // SERDE_IMPLEMENTATION
