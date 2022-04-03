cmake_minimum_required(VERSION 3.0)
project(c_web_app)

set(CMAKE_EXPORT_COMPILE_COMMANDS)
add_compile_options(-fsanitize=address -O1 -fno-omit-frame-pointer -g)

add_library(utility SHARED
  utility/str_lib.c
)

add_library(weather_lib SHARED
 weather_lib.c
)
target_link_libraries(weather_lib utility)

add_executable(main main.c)
target_link_libraries(main weather_lib curl)

# enable_testing()

# add_executable(test_str_lib test/test_str_lib.c)
# target_include_directories(test_str_lib PUBLIC utility)
# target_link_libraries(test_str_lib asan utility)
# add_test(
#   NAME test_str_lib
#   COMMAND $<TARGET_FILE:test_str_lib>
#   )

# add_executable(test_weather_lib test/test_weather_lib.c)
# target_include_directories(test_weather_lib PUBLIC .)
# target_link_libraries(test_weather_lib asan weather_lib)
# add_test(
#   NAME test_weather_lib
#   COMMAND $<TARGET_FILE:test_weather_lib>
#   )
