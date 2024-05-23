#pragma once

#include <array>
#include <cassert>
#include <memory>
#include <optional>
#include <string>

struct btree_node {
  size_t size{0};
  std::array<int, 2> keys;
  std::array<std::string, 2> values;
  std::array<std::unique_ptr<btree_node>, 3> children;
};

void insert(btree_node &root, int key, std::string value);

/**
 * @brief Insert a key/value pair into a full node by splitting it
 *
 * @param node the node to insert into (and to split)
 * @param key the key to insert (must be greater than all keys of the node)
 * @param value the value associated to the key
 */
void split(btree_node &node, int key, std::string value) {
  assert(node.size >= 2);
  assert(node.keys[node.size - 1] < key);

  // create a left node and move the first key/value to it
  auto left = std::make_unique<btree_node>();
  insert(*left, node.keys[0], node.values[0]);
  node.children[0] = std::move(left);
  // remove the first key/value of the node
  node.keys[0] = node.keys[1];
  node.values[0] = node.values[1];
  node.size = 1;

  // create a right node and move the inserted key/value to it
  auto right = std::make_unique<btree_node>();
  insert(*right, key, value);
  node.children[1] = std::move(right);
}

/**
 * @brief Insert a key/value pair into a node
 *
 * @param node the node to insert into
 * @param key the key to insert
 * @param value the value associated to the key
 */
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

  if (root.size < 2) {
    // if the node is not full, put the last pair at the end
    root.keys[root.size] = key;
    root.values[root.size] = value;
    root.size++;
  } else {
    // if the node is full, split it
    split(root, key, value);
  }
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
