workspace "SimpleMLWorkspace"
    configurations {"Debug", "Release"}
    basedir "builddir"
    targetdir "builddir/bin/${cfg.buildcfg}"

    objdir "builddir/obj/${cfg.buildcfg}"
    

    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"
    filter "system:macosx"
        buildoptions "-std=c++14"
    filter ""

project "gtest"
    kind "StaticLib"
    language "C++"
    
    defines {
        "GTEST_HAS_PTHREAD=0"
    }

    files {
        "deps/googletest/googletest/src/**.cc",
        "deps/googletest/googletest/src/**.h",
        "deps/googletest/googletest/include/**.h",
        "deps/googletest/googlemock/src/*.cc",
        "deps/googletest/googlemoc/include/**.h"
    }
    removefiles {
        "deps/googletest/googletest/src/gtest-all.cc",
        "deps/googletest/googletest/src/gtest_main.cc",
        "deps/googlemock/googletest/src/gmock-all.cc",
        "deps/googlemock/googletest/src/gmock_main.cc"
    }
    includedirs {
        "deps/googletest/googletest/",
        "deps/googletest/googletest/include",
        "deps/googletest/googlemock",
        "deps/googletest/googlemock/include"
    }

project "SimpleML"
    kind "StaticLib"
    language "C++"
    warnings "Extra"

    files {
        "simpleml/**.h",
        "simpleml/**.cc"
    }

    removefiles {
        "simpleml/test/**"
    }

    includedirs {
        "deps",
        "./"
    }

project "SimpleMLTest"
    kind "ConsoleApp"
    language "C++"
    links {
        "gtest",
        "SimpleML"
    }

    files {
        "simpleml/test/**.cc"
    }

    includedirs {
        "deps/googletest/googletest/include",
        "deps",
        "./"
    }