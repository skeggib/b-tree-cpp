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

cc_test(
    name = "split_tests",
    srcs = ["split_tests.cc"],
    defines = ["CATCH_CONFIG_MAIN"],
    deps = [
        ":fixture",
    ],
)

cc_test(
    name = "single_node_get_tests",
    srcs = ["single_node_get_tests.cc"],
    defines = ["CATCH_CONFIG_MAIN"],
    deps = [
        ":fixture",
    ],
)

cc_test(
    name = "single_node_insert_tests",
    srcs = ["single_node_insert_tests.cc"],
    defines = ["CATCH_CONFIG_MAIN"],
    deps = [
        ":fixture",
    ],
)
