
C_FLAGS = [
    "-w",
    "-std=c11",
    "-pedantic",
]

cc_library(
    name = "utility",
    # Also include header files here so we can do
    #   #include "vec.h" in vec.c, instead of
    #   #include "utility/vec.h"
    # because I added an include prefix below.
    srcs = [
        "magic.h",
        "assert_macros.h",
        "str.h",
        "str.c",
        "vec.h",
        "vec.c",
        ],
    hdrs = [
        "magic.h",
        "assert_macros.h",
        "str.h",
        "vec.h",
        ],
    linkstatic = False,
    copts = C_FLAGS,
    visibility = ["//main:__pkg__"],
    include_prefix = "utility",
)

cc_test(
    name="test_str_lib",
    srcs=["test_str_lib.c"],
    deps=[":utility"],
)
