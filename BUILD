cc_library(
    name = "simpleml",
    srcs = glob([
        "simpleml/operations/internal/*.cc",
    ]),
    hdrs = 
        glob(["simpleml/operations/internal/*.h"]) +
        [
            "simpleml/variable.h",
            "simpleml/math/tensor.h",
            "simpleml/operations/operations.h"
        ],
    deps = [
        "//deps/xtensor:xtensor"
    ],
    copts = [
        "-std=c++14",
        # "-Wall",
        # "-Werror",
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
