# загружаем информацию о sc-machine::sc-memory
find_package(sc-machine REQUIRED)

# собираем исходные файлы
file(GLOB SOURCES CONFIGURE_DEPENDS
    "*.cpp" "*.hpp"
    "agent/*.cpp" "agent/*.hpp"
    "keynodes/*.cpp" "keynodes/*.hpp"
)

# создаём библиотеку
add_library(pcb-layout-module SHARED ${SOURCES})

# линкуем с sc-machine
target_link_libraries(pcb-layout-module
    PUBLIC sc-machine::sc-memory
)

# указываем, где искать заголовочные файлы текущего модуля
target_include_directories(pcb-layout-module
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

# устанавливаем директорию для вывода
if(NOT DEFINED SC_EXTENSIONS_DIRECTORY)
    set(SC_EXTENSIONS_DIRECTORY "${CMAKE_BINARY_DIR}/lib/extensions")
endif()

set_target_properties(pcb-layout-module
    PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${SC_EXTENSIONS_DIRECTORY}
)

# =========== ТЕСТЫ ===========
if(BUILD_TESTS)
    find_package(GTest REQUIRED)
    include(GoogleTest)
    
    file(GLOB TEST_SOURCES CONFIGURE_DEPENDS "test/*.cpp")
    
    if(TEST_SOURCES)
        add_executable(pcb-layout-module-tests ${TEST_SOURCES})
        
        target_link_libraries(pcb-layout-module-tests
            PRIVATE pcb-layout-module
            PRIVATE GTest::gtest_main
        )
        
        target_include_directories(pcb-layout-module-tests 
            PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
        )
        
        gtest_discover_tests(pcb-layout-module-tests
            TEST_LIST TEST_SOURCES
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test
        )
    endif()
endif()

