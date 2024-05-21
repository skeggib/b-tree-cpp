#include "src/btree.hh"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("getting a value by key from a b-tree node") {
  btree_node root;

  int key_a = 1;
  std::string value_a = "a";
  insert(root, key_a, value_a);

  int key_b = 2;
  std::string value_b = "b";
  insert(root, key_b, value_b);

  int key_c = 3;

  SECTION("when the key exists, returns its associated value") {
    REQUIRE(**get(root, key_a) == value_a);
    REQUIRE(**get(root, key_b) == value_b);
  }

  SECTION("when the key does not exist, returns nullopt") { REQUIRE(get(root, key_c) == std::nullopt); }
}
