#include "src/btree.hh"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("inserting into an empty b-tree node") {
  btree_node root;
  int key = 1;
  std::string value = "value";
  insert(root, key, value);

  SECTION("increases its size by one") { REQUIRE(root.size == 1); }

  SECTION("fills the first key") { REQUIRE(root.keys[0] == key); }

  SECTION("fills the first value") { REQUIRE(root.values[0] == value); }

  SECTION("does not create any child") {
    for (const auto &child : root.children) {
      REQUIRE(child == nullptr);
    }
  }
}

TEST_CASE("inserting into a non-empty and non-full b-tree node") {
  btree_node root;

  { // make the node non-empty but also non-full
    int first_key = 1;
    std::string first_value = "first_value";
    insert(root, first_key, first_value);
  }

  int second_key = 2;
  std::string second_value = "second_value";
  insert(root, second_key, second_value);

  SECTION("increases its size by one") { REQUIRE(root.size == 2); }

  SECTION("fills the next key") { REQUIRE(root.keys[1] == second_key); }

  SECTION("fills the next value") { REQUIRE(root.values[1] == second_value); }

  SECTION("does not create any child") {
    for (const auto &child : root.children) {
      REQUIRE(child == nullptr);
    }
  }
}

TEST_CASE("inserting a smaller key than the one already in the b-tree node") {
  btree_node root;

  int greater_key = 2;
  std::string greater_value = "greater_value";
  insert(root, greater_key, greater_value);

  int smaller_key = 1;
  std::string smaller_value = "smaller_value";
  insert(root, smaller_key, smaller_value);

  SECTION("sorts keys in ascending order") {
    REQUIRE(root.keys[0] == smaller_key);
    REQUIRE(root.keys[1] == greater_key);
  }

  SECTION("sorts values accordingly") {
    REQUIRE(root.values[0] == smaller_value);
    REQUIRE(root.values[1] == greater_value);
  }
}

TEST_CASE("inserting an already existing key in a b-tree node") {
  btree_node root;

  int key = 2;
  std::string initial_value = "initial_value";
  insert(root, key, initial_value);

  std::string new_value = "new_value";
  insert(root, key, new_value);

  SECTION("replaces the existing value") { REQUIRE(root.values[0] == new_value); }

  SECTION("does not increase its size") { REQUIRE(root.size == 1); }
}
