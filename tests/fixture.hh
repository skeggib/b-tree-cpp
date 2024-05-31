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
  /**
   * @brief B-Tree representation used by the fixture to check its properties
   */
  struct node {
    size_t size{0};
    std::array<int, 2> keys;
    std::array<std::string, 2> values;
    std::array<std::unique_ptr<node>, 3> children;
  };

  static void insert_to_fixture_representation(node &node, size_t depth, int key, std::string value) {
    if (depth == 0) {
      node.keys[node.size] = key;
      node.values[node.size] = value;
      node.size++;
    } else {
      if (node.children[node.size] == nullptr) {
        node.children[node.size] = std::make_unique<Fixture::node>();
      }
      insert_to_fixture_representation(*node.children[node.size], depth - 1, key, value);
    }
  };

  node convert_to_fixture_representation() {
    node root;
    b.traverse([&root](size_t depth, int key, std::string value) {
      insert_to_fixture_representation(root, depth, key, value);
    });
    return root;
  }

  /**
   * @brief Produces the same output than b_tree::to_string
   *
   * Used to check that the fixture representation is equivalent to the B-Tree it originates from.
   */
  static std::string to_string_fixture_representation(const node &root) {
    std::ostringstream ss;
    to_string_fixture_representation(root, ss, 0);
    return ss.str();
  }

  static void to_string_fixture_representation(const node &node, std::ostringstream &ss, size_t indent) {
    constexpr size_t indent_size = 4;
    const std::string indent_str(indent * indent_size, ' ');

    if (node.size <= 0) {
      ss << indent_str << "[empty]\n";
      return;
    }

    for (size_t i = 0; i < node.size; ++i) {
      if (node.children[i] != nullptr) {
        to_string_fixture_representation(*node.children[i], ss, indent + 1);
      }
      ss << indent_str << "(" + std::to_string(node.keys[i]) + "," + node.values[i] + ")\n";
    }

    if (node.children[node.size] != nullptr) {
      to_string_fixture_representation(*node.children[node.size], ss, indent + 1);
    }
  }

  void check_b_tree_properties() {
    // convert the b-tree to our own representation and check that it is equivalent to the b-tree
    auto fixture_representation = convert_to_fixture_representation();
    REQUIRE(to_string_fixture_representation(fixture_representation) == to_string());

    check_all_non_root_nodes_have_at_least_n_keys(fixture_representation);
    check_all_non_root_nodes_have_at_most_2n_keys(fixture_representation);
    check_root_node_has_the_correct_number_of_keys(fixture_representation);
    check_tree_is_balanced(fixture_representation);
  }

  static void traverse_all_nodes(const node &node, std::function<void(const Fixture::node &, size_t)> callback,
                                 size_t depth = 0) {
    callback(node, depth);
    for (size_t i = 0; i < node.size; ++i) {
      if (node.children[i] != nullptr) {
        traverse_all_nodes(*node.children[i], callback, depth + 1);
      }
    }
    if (node.children[node.size] != nullptr) {
      traverse_all_nodes(*node.children[node.size], callback, depth + 1);
    }
  }

  static void traverse_all_non_root_nodes(const node &root, std::function<void(const Fixture::node &, size_t)> callback,
                                          size_t depth = 0) {
    for (size_t i = 0; i < root.size; ++i) {
      if (root.children[i] != nullptr) {
        traverse_all_nodes(*root.children[i], callback, depth + 1);
      }
    }
    if (root.children[root.size] != nullptr) {
      traverse_all_nodes(*root.children[root.size], callback, depth + 1);
    }
  }

  void check_all_non_root_nodes_have_at_least_n_keys(const node &root) {
    traverse_all_non_root_nodes(root, [](const node &node, size_t depth) { REQUIRE(node.size >= 1); });
  }

  void check_all_non_root_nodes_have_at_most_2n_keys(const node &root) {
    traverse_all_non_root_nodes(root, [](const node &node, size_t depth) { REQUIRE(node.size <= 2); });
  }

  void check_root_node_has_the_correct_number_of_keys(const node &root) {
    bool has_children = std::any_of(root.children.begin(), root.children.begin() + root.size,
                                    [](const std::unique_ptr<node> &child) { return child != nullptr; });
    if (!has_children) {
      REQUIRE(root.size >= 0);
      REQUIRE(root.size <= 2);
    } else {
      REQUIRE(root.size >= 1);
      REQUIRE(root.size <= 2);
    }
  }

  void check_tree_is_balanced(const node &root) {
    std::optional<size_t> first_leaf_depth;
    traverse_all_nodes(root, [&first_leaf_depth](const node &node, size_t depth) {
      auto is_leaf = node.children[0] == nullptr;
      if (is_leaf) {
        if (!first_leaf_depth.has_value()) {
          first_leaf_depth = depth;
        } else {
          REQUIRE(first_leaf_depth == depth);
        }
      }
    });
  }
};
