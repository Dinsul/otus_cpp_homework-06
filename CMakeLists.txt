cmake_minimum_required(VERSION 3.2)

if ($ENV{TRAVIS_BUILD_NUMBER})
    project(bulk VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else ()
    project(bulk VERSION 0.0.0)
endif ()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_package(Doxygen)

set(DOXYGEN_HAVE_DOT YES)
set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_PROJECT_LOGO "${CMAKE_SOURCE_DIR}/logo.svg")
set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/doc")

#doxygen_add_docs(targetName
#    [filesOrDirs...]
#    [WORKING_DIRECTORY dir]
#    [COMMENT comment])

doxygen_add_docs(doc "${PROJECT_SOURCE_DIR}")

add_executable(${PROJECT_NAME} "${PROJECT_NAME}.h" "${PROJECT_NAME}.cpp" "main.cpp" ".travis.yml")

add_executable(test_${PROJECT_NAME} "test_${PROJECT_NAME}.cpp" "${PROJECT_NAME}.h")

set_target_properties(${PROJECT_NAME} test_${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )

set_target_properties(test_${PROJECT_NAME} PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    )

target_link_libraries(test_${PROJECT_NAME}
    ${Boost_LIBRARIES}
    )

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT dinsul2.0@gmail.com)

include (CPack)

enable_testing()

add_test(test_ test_${PROJECT_NAME})
