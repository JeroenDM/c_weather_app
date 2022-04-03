
C_FLAGS = [
    "-w",
    "-std=c11",
    "-pedantic",
]

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
    name = "maybe",
    srcs = ["maybe.c"],
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
