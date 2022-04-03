C_FLAGS = [
    "-w",
    "-std=c11",
    "-pedantic",
]

cc_library(
    name = "graph",
    srcs = [
        "graph.h",
        "graph.c",
        "term_drawing.h"
        ],
    hdrs = ["graph.h"],
    deps = ["//utility:utility"],
    copts = C_FLAGS,
    visibility = ["//:__pkg__"],
    include_prefix = "main",
)

cc_binary(
    name = "gui",
    srcs = ["gui.c"],
    deps = ["graph", "@X11//:lib"],
    copts = C_FLAGS,
)

cc_test(
    name = "test_graph",
    srcs = [
        "term_drawing.h",
        "test_graph.c",
    ],
    deps = ["graph"],
    copts = C_FLAGS,
)