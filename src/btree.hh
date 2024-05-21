#pragma once

#include <array>
#include <memory>
#include <optional>
#include <string>

struct btree_node {
  int size{0};
  std::array<int, 2> keys;
  std::array<std::string, 2> values;
  std::array<std::unique_ptr<btree_node>, 3> children;
};

void insert(btree_node &root, int key, std::string value) {
  // insert the key/value pair by moving pairs with greater keys one step to the right
  for (std::size_t i = 0; i < root.size; ++i) {
    if (root.keys[i] > key) {
      // we move greater pairs by swapping them with the current one
      std::swap(root.keys[i], key);
      std::swap(root.values[i], value);
    } else if (root.keys[i] == key) {
      // if the key already exists, replace its value and leave other keys and values unchanged
      root.values[i] = value;
      return;
    }
  }
  // the last pair is put at the end
  root.keys[root.size] = key;
  root.values[root.size] = value;
  root.size++;
}

std::optional<const std::string *> get(const btree_node &root, int key) {
  for (std::size_t i = 0; i < root.size; ++i) {
    if (root.keys[i] == key) {
      return &root.values[i];
    }
  }
  return {};
}

class btree {
private:
  btree_node root;

public:
  void insert(int key, std::string value) { ::insert(root, key, value); }
  std::optional<const std::string *> get(int key) { return ::get(root, key); }
};
