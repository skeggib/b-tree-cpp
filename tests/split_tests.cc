#include "src/btree.hh"

#include <catch2/catch_test_macros.hpp>

#include <sstream>
#include <string>

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

  if (node.children[node.size] != nullptr) {
    to_string_for_tests(*node.children[node.size], ss, indent + 1);
  }
}

std::string to_string_for_tests(const btree_node &root) {
  std::ostringstream ss;
  to_string_for_tests(root, ss, 0);
  return ss.str();
}

TEST_CASE("inserting at the beginning of a single full node") {
  btree_node root;

  insert(root, 2, "b");
  insert(root, 3, "c");
  REQUIRE(to_string_for_tests(root) == "(2,b)\n"
                                       "(3,c)\n");

  insert(root, 1, "a");
  REQUIRE(to_string_for_tests(root) == "    (1,a)\n"
                                       "(2,b)\n"
                                       "    (3,c)\n");
}

TEST_CASE("inserting in the middle of a single full node") {
  btree_node root;

  insert(root, 1, "a");
  insert(root, 3, "c");
  REQUIRE(to_string_for_tests(root) == "(1,a)\n"
                                       "(3,c)\n");

  insert(root, 2, "b");
  REQUIRE(to_string_for_tests(root) == "    (1,a)\n"
                                       "(2,b)\n"
                                       "    (3,c)\n");
}

TEST_CASE("inserting at the end of a single full node") {
  btree_node root;

  insert(root, 1, "a");
  insert(root, 2, "b");
  REQUIRE(to_string_for_tests(root) == "(1,a)\n"
                                       "(2,b)\n");

  insert(root, 3, "c");
  REQUIRE(to_string_for_tests(root) == "    (1,a)\n"
                                       "(2,b)\n"
                                       "    (3,c)\n");
}
