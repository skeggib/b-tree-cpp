def test(name):
    native.cc_test(
        name = name,
        srcs = [name+ ".cc"],
        defines = ["CATCH_CONFIG_MAIN"],
        deps = [
            ":fixture",
        ],
    )
