config_setting(
    name = "windows",
    values = { "cpu": "x64_windows" },
)

config_setting(
    name = "macos",
    values = {"cpu": "x64_macos" },
)

cc_library(
    name = "simpleml",
    srcs = glob([
        "simpleml/operations/internal/*.cc",
        "simpleml/operations/*.cc",
        "simpleml/*.cc",
        ]),
    hdrs = 
        glob([
            "simpleml/operations/internal/*.h",
            "simpleml/*.h"]) +
        [
            "simpleml/math/tensor.h",
            "simpleml/operations/operations.h"
        ],
    deps = [
        "//deps/xtensor:xtensor"
    ],
    copts = select(
        {
            ":windows": [
                "/std:c++17",
            ],
            "//conditions:default": 
            [
                "-std=c++14",
                # "-Wall",
                # "-Werror",
            ]
        }),
)

cc_binary(
    name = "simpleml_main",
    srcs = ["src/main.cc"],
    deps = [
        ":simpleml"
    ],
    copts = select(
        {
            ":windows": [
                "/std:c++17",
            ],
            "//conditions:default": 
            [
                "-std=c++14",
                # "-Wall",
                # "-Werror",
            ]
        }),
)

cc_test (
    name = "test",
    srcs = [
        "simpleml/test/operations_test.cc",
        "simpleml/test/test_main.cc",
    ],
    deps = [
        ":simpleml",
        "@googletest//:gtest",
    ],
    copts = select(
    {
        ":windows": [
            "/std:c++17",
        ],
        "//conditions:default": 
        [
            "-std=c++14",
            # "-Wall",
            # "-Werror",
        ]
    }),
)