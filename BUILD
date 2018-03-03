cc_library(
    name = "simpleml",
    srcs = [
        "simpleml/operations/internal/add.cc",
        "simpleml/operations/internal/mul.cc",
        "simpleml/operations/internal/operation.cc",
    ],
    hdrs = [
        "simpleml/math/tensor.h",
        "simpleml/operations/internal/add.h",
        "simpleml/operations/internal/mul.h",
        "simpleml/operations/internal/transpose.h",
        "simpleml/operations/internal/operation.h",
        "simpleml/operations/operations.h"
    ],
    deps = [
        "//deps/xtensor:xtensor"
    ],
    copts = [
        "-std=c++14",
        "-Wall",
        "-Werror",
    ],
)

cc_binary(
    name = "simpleml_main",
    srcs = ["src/main.cc"],
    deps = [
        ":simpleml"
    ],
    copts = ["-std=c++14"],
)
