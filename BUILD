
C_FLAGS = [
    "-w",
    "-std=c11",
    "-pedantic",
]

cc_library(
    name = "utility",
    srcs = ["utility/str_lib.c"],
    hdrs = ["utility/str_lib.h", "utility/magic.h"],
    linkstatic = False,
    copts = C_FLAGS,
)


cc_library(
    name = "weather_lib",
    srcs = ["weather_lib.c"],
    hdrs = ["weather_lib.h"],
    linkstatic = False,
    deps = ["utility"],
    copts = C_FLAGS,
)

cc_binary(
    name = "app",
    deps = ["weather_lib", "@curl//:lib"],
    srcs = ["main.c"],
    copts = C_FLAGS,
)

cc_binary(
    name = "gui",
    srcs = ["gui.c"],
    deps = ["@X11//:lib"],
    copts = C_FLAGS,
)

cc_binary(
    name = "maybe",
    srcs = ["maybe.c"],
    copts = C_FLAGS,
)

cc_binary(
    name = "graph",
    srcs = ["graph.c", "term_drawing.h"],
    copts = C_FLAGS,
)

cc_library(
    name = "layout",
    srcs = ["layout.c"],
    hdrs = ["layout.h"],
    data = ["layout.txt"],
    copts = C_FLAGS,
)

cc_test(
    name = "test_layout",
    deps = ["layout"],
    srcs = ["test_layout.c"],
    data = ["layout.txt"],
)
