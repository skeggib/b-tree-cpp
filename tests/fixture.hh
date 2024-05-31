#include "src/btree.hh"

#include <catch2/catch_test_macros.hpp>

// TODO: move definitions to .cc file
class Fixture {
private:
  btree b;

public:
  /**
   * @brief Wraps btree::insert to add additional coherence checks (checks that B-tree constrains are respected)
   */
  void insert(int key, std::string value) {
    b.insert(key, value);
    check_b_tree_properties();
  }

  std::optional<const std::string *> get(int key) { return b.get(key); }

  std::string to_string() const { return b.to_string(); }

private:
  void check_b_tree_properties() {
    check_all_non_root_nodes_have_at_least_n_keys();
    check_all_non_root_nodes_have_at_most_2n_keys();
    check_root_node_has_the_correct_number_of_keys();
    check_tree_is_balanced();
  }

  void check_all_non_root_nodes_have_at_least_n_keys() {
    // TODO
  }

  void check_all_non_root_nodes_have_at_most_2n_keys() {
    // TODO
  }

  void check_root_node_has_the_correct_number_of_keys() {
    // TODO
  }

  void check_tree_is_balanced() {
    // TODO
  }
};
