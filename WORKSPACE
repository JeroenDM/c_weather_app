# load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# http_archive(
#   name = "curl",
#   urls = ["https://github.com/curl/curl/releases/download/curl-7_82_0/curl-7.82.0.zip"],
#   strip_prefix = "curl-7.82.0",
#   build_file = "//third-party:curl.BUILD.bazel",
# )


new_local_repository(
    name = "curl",
    path = "/usr/lib/x86_64-linux-gnu",
    build_file = "curl.BUILD"
)

new_local_repository(
    name = "X11",
    path = "/usr/lib/x86_64-linux-gnu",
    build_file = "X11.BUILD"
)
