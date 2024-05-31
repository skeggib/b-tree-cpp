load('test.bzl', 'test')

cc_library(
    name = "fixture",
    srcs = [],
    hdrs = [
        "fixture.hh",
    ],
    deps = [
        "//src:btree",
        "@catch2//:catch2_main",
    ],
)

test(name = "single_node_get_tests")
test(name = "single_node_insert_tests")
test(name = "split_tests")
