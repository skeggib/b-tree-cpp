#include "src/btree.hh"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("inserting into a b-tree", "[example]") {
  btree b;
  b.insert(1, "value");
  REQUIRE(**b.get(1) == "value");
}

TEST_CASE("getting a non-existing value returns nullopt", "[example]") {
  btree b;
  b.insert(2, "value");
  REQUIRE(b.get(1) == std::nullopt);
}
