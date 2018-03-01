cc_library(
    name = "simpleml",
    srcs = [
        "simpleml/operations/internal/add.cc",
        "simpleml/operations/internal/operation.cc",
    ],
    hdrs = [
        "simpleml/math/tensor.h",
        "simpleml/operations/internal/add.h",
        "simpleml/operations/internal/operation.h",
    ],
    deps = [
        "//deps/xtensor:xtensor"
    ],
    copts = ["-std=c++14"],
)

cc_binary(
    name = "simpleml_main",
    srcs = ["src/main.cc"],
    deps = [
        ":simpleml"
    ],
)
