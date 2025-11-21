cmake_minimum_required(VERSION 3.14)
project(TravelBooking)
set(CMAKE_CXX_STANDARD 17)
find_package(GTest REQUIRED)
file(GLOB_RECURSE SOURCES 
    "modules/*/cpp/*.cpp"
    "app/*.cpp"
)
file(GLOB_RECURSE HEADERS 
    "modules/*/hpp/*.hpp"
    "app/*.hpp"
    "modules/*/*.hpp"
)
set(MAIN_SOURCES ${SOURCES})
list(FILTER MAIN_SOURCES EXCLUDE REGEX ".*tests?.*")
add_executable(travel_booking ${MAIN_SOURCES} ${HEADERS})
target_include_directories(travel_booking PRIVATE 
    modules/persons/hpp
    modules/booking/hpp
    modules/tours/hpp
    modules/transportation/hpp
    modules/accommodation/hpp
    modules/meal/hpp
    app/
    modules
)
set(TEST_SOURCES ${SOURCES})
list(FILTER TEST_SOURCES EXCLUDE REGEX ".*main\.cpp$")
add_executable(test_runner 
    tests/AccommodationTest.cpp
    tests/MealTest.cpp
    tests/BookingTest.cpp
    tests/TransportationTest.cpp
    tests/PersonsTest.cpp
    tests/TourTest.cpp
    ${TEST_SOURCES} ${HEADERS}
)
target_include_directories(test_runner PRIVATE 
    modules/persons/hpp
    modules/booking/hpp
    modules/tours/hpp
    modules/transportation/hpp
    modules/accommodation/hpp
    modules/meal/hpp
    app/
    modules
)
target_link_libraries(test_runner GTest::gtest GTest::gtest_main pthread)
# ПОКРЫТИЕ КОДАА
option(ENABLE_COVERAGE "Enable code coverage" OFF)
if(ENABLE_COVERAGE)
    message(STATUS "Building with coverage instrumentation")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage -lgcov")
    find_program(GCOVR_PATH gcovr)
    if(GCOVR_PATH)
        file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/coverage)
        add_custom_target(coverage-html
            COMMAND ${GCOVR_PATH}
                --root ${CMAKE_SOURCE_DIR}
                --exclude ".*tests?.*"
                --exclude ".*main\.cpp"
                --html-nested ${CMAKE_BINARY_DIR}/coverage/index.html
                --html-title "TravelBooking Test Coverage"
                --print-summary
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Generating HTML coverage report"
        )
        add_custom_target(coverage
            COMMAND ${GCOVR_PATH}
                --root ${CMAKE_SOURCE_DIR}
                --exclude ".*tests?.*"
                --exclude ".*main\.cpp"
                --print-summary
                --sort-percentage
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Running gcovr to generate coverage report"
        )
    else()
        message(WARNING "gcovr not found! Coverage targets will not be available.")
    endif()
endif()