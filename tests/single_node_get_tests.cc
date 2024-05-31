#include "fixture.hh"

TEST_CASE_METHOD(Fixture, "getting a value by key from a b-tree node") {
  insert(1, "a");
  insert(2, "b");

  SECTION("when the key exists, returns its associated value") {
    REQUIRE(**get(1) == "a");
    REQUIRE(**get(2) == "b");
  }

  SECTION("when the key does not exist, returns nullopt") { REQUIRE(get(3) == std::nullopt); }
}
