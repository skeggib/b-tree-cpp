#include "fixture.hh"

TEST_CASE_METHOD(Fixture, "inserting at the beginning of a single full node") {
  insert(2, "b");
  insert(3, "c");
  REQUIRE(to_string() == "(2,b)\n"
                         "(3,c)\n");

  insert(1, "a");
  REQUIRE(to_string() == "    (1,a)\n"
                         "(2,b)\n"
                         "    (3,c)\n");
}

TEST_CASE_METHOD(Fixture, "inserting in the middle of a single full node") {
  insert(1, "a");
  insert(3, "c");
  REQUIRE(to_string() == "(1,a)\n"
                         "(3,c)\n");

  insert(2, "b");
  REQUIRE(to_string() == "    (1,a)\n"
                         "(2,b)\n"
                         "    (3,c)\n");
}

TEST_CASE_METHOD(Fixture, "inserting at the end of a single full node") {
  insert(1, "a");
  insert(2, "b");
  REQUIRE(to_string() == "(1,a)\n"
                         "(2,b)\n");

  insert(3, "c");
  REQUIRE(to_string() == "    (1,a)\n"
                         "(2,b)\n"
                         "    (3,c)\n");
}
