#include "fixture.hh"

TEST_CASE_METHOD(Fixture, "inserting into an empty b-tree node") {
  insert(1, "a");
  REQUIRE(to_string() == "(1,a)\n");
}

TEST_CASE_METHOD(Fixture, "inserting into a non-empty and non-full b-tree node") {
  // make the node non-empty but also non-full
  insert(1, "a");
  REQUIRE(to_string() == "(1,a)\n");

  insert(2, "b");
  REQUIRE(to_string() == "(1,a)\n"
                             "(2,b)\n");
}

TEST_CASE_METHOD(Fixture, "inserting a smaller key than the one already in the b-tree node") {
  insert(2, "b");
  REQUIRE(to_string() == "(2,b)\n");

  insert(1, "a");
  REQUIRE(to_string() == "(1,a)\n"
                             "(2,b)\n");
}

TEST_CASE_METHOD(Fixture, "inserting an already existing key into an non-full b-tree node") {
  insert(1, "a");
  REQUIRE(to_string() == "(1,a)\n");

  insert(1, "b");
  REQUIRE(to_string() == "(1,b)\n");
}

TEST_CASE_METHOD(Fixture, "inserting an already existing key into a full b-tree node") {
  insert(1, "a");
  insert(2, "b");
  REQUIRE(to_string() == "(1,a)\n"
                             "(2,b)\n");

  insert(2, "c");
  REQUIRE(to_string() == "(1,a)\n"
                             "(2,c)\n");
}
