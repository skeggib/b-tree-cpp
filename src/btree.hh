#pragma once

#include <array>
#include <cassert>
#include <functional>
#include <memory>
#include <optional>
#include <sstream>
#include <string>

class btree {
private:
  struct node {
    size_t size{0};
    std::array<int, 2> keys;
    std::array<std::string, 2> values;
    std::array<std::unique_ptr<node>, 3> children;
  };

  node root;

public:
  void insert(int key, std::string value) { insert(root, key, value); }

  std::optional<const std::string *> get(int key) {
    // TODO: search child nodes
    for (std::size_t i = 0; i < root.size; ++i) {
      if (root.keys[i] == key) {
        return &root.values[i];
      }
    }
    return {};
  }

  std::string to_string() const {
    std::ostringstream ss;
    to_string(root, ss, 0);
    return ss.str();
  }

  /**
   * @brief Traverse the B-Tree in ascending order
   */
  void traverse(std::function<void(size_t depth, int key, std::string value)> callback) { traverse(root, 0, callback); }

private:
  /**
   * @brief Insert a key/value pair into a full node by splitting it
   *
   * @param node the node to insert into (and to split)
   * @param key the key to insert (must be greater than all keys of the node)
   * @param value the value associated to the key
   */
  static void split(node &node, int key, std::string value) {
    assert(node.size >= 2);
    assert(node.keys[node.size - 1] < key);

    // create a left node and move the first key/value to it
    auto left = std::make_unique<btree::node>();
    insert(*left, node.keys[0], node.values[0]);
    node.children[0] = std::move(left);
    // remove the first key/value of the node
    node.keys[0] = node.keys[1];
    node.values[0] = node.values[1];
    node.size = 1;

    // create a right node and move the inserted key/value to it
    auto right = std::make_unique<btree::node>();
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
  static void insert(node &node, int key, std::string value) {
    // insert the key/value pair by moving pairs with greater keys one step to the right
    for (std::size_t i = 0; i < node.size; ++i) {
      if (node.keys[i] > key) {
        // we move greater pairs by swapping them with the current one
        std::swap(node.keys[i], key);
        std::swap(node.values[i], value);
      } else if (node.keys[i] == key) {
        // if the key already exists, replace its value and leave other keys and values unchanged
        node.values[i] = value;
        return;
      }
    }

    if (node.size < 2) {
      // if the node is not full, put the last pair at the end
      node.keys[node.size] = key;
      node.values[node.size] = value;
      node.size++;
    } else {
      // if the node is full, split it
      split(node, key, value);
    }
  }

  static void to_string(const node &node, std::ostringstream &ss, size_t indent) {
    constexpr size_t indent_size = 4;
    const std::string indent_str(indent * indent_size, ' ');

    if (node.size <= 0) {
      ss << indent_str << "[empty]\n";
      return;
    }

    for (size_t i = 0; i < node.size; ++i) {
      if (node.children[i] != nullptr) {
        to_string(*node.children[i], ss, indent + 1);
      }
      ss << indent_str << "(" + std::to_string(node.keys[i]) + "," + node.values[i] + ")\n";
    }

    if (node.children[node.size] != nullptr) {
      to_string(*node.children[node.size], ss, indent + 1);
    }
  }

  static void traverse(const node &node, size_t depth,
                       std::function<void(size_t depth, int key, std::string value)> callback) {
    for (size_t i = 0; i < node.size; ++i) {
      if (node.children[i] != nullptr) {
        traverse(*node.children[i], depth + 1, callback);
      }
      callback(depth, node.keys[i], node.values[i]);
    }
    if (node.children[node.size] != nullptr) {
      traverse(*node.children[node.size], depth + 1, callback);
    }
  }
};
