cmake_minimum_required(VERSION 3.5)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION "0.0.${PATCH_VERSION}")

project(main VERSION ${PROJECT_VERSION})


configure_file(version.h.in version.h)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tests main.cpp)

enable_testing()
find_package(GTest REQUIRED)
target_include_directories(tests PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(tests PRIVATE GTest::gtest_main)

install(TARGETS runTests
    RUNTIME DESTINATION bin
)

add_test(NAME runTests COMMAND runTests)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "tests")
set(CPACK_PACKAGE_FILE_NAME "tests-0.0.${PATCH_VERSION}-Linux")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_CONTACT "example@example.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "example@example.com")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.7), libmysqlcppconn8v5, libsqlite3-0")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "tests shared library and tools")

include(CPack)
