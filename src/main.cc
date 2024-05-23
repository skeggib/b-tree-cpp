#include "btree.hh"

#include <iostream>
#include <sstream>

void to_string_for_tests(const btree_node &node, std::ostringstream &ss, size_t indent) {
  constexpr size_t indent_size = 4;
  const std::string indent_str(indent * indent_size, ' ');

  if (node.size <= 0) {
    ss << indent_str << "[empty]\n";
    return;
  }

  for (size_t i = 0; i < node.size; ++i) {
    if (node.children[i] != nullptr) {
      to_string_for_tests(*node.children[i], ss, indent + 1);
    }
    ss << indent_str << "(" + std::to_string(node.keys[i]) + "," + node.values[i] + ")\n";
  }

  if (node.children[node.children.size() - 1] != nullptr) {
    to_string_for_tests(*node.children[node.children.size() - 1], ss, indent + 1);
  }
}

std::string to_string_for_tests(const btree_node &root) {
  std::ostringstream ss;
  to_string_for_tests(root, ss, 0);
  return ss.str();
}

std::unique_ptr<btree_node> node(size_t size, std::array<int, 2> keys, std::array<std::string, 2> values) {
  return std::unique_ptr<btree_node>(new btree_node{size, keys, values, {}});
}

int main(int argc, char **argv) {
  // clang-format off
  btree_node root{
    2,
    {4, 6},
    {"4", "6"},
    {
      node(1, {1}, {"1"}),
      node(1, {5}, {"5"}),
      node(2, {7, 8}, {"7", "8"})
    }
  };
  // clang-format on
  std::cout << to_string_for_tests(root) << std::endl;
  return 0;
}
