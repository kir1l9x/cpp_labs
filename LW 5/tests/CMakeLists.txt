include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        Array_3DTests # Изменил имя на Array_3DTests
        test.cpp # Укажите здесь свой файл с тестами
)

target_link_libraries(
        Array_3DTests
        Array_3D # Зависимость от вашей библиотеки Array_3D
        GTest::gtest_main
)

target_include_directories(Array_3DTests PUBLIC ${PROJECT_SOURCE_DIR})

include(GoogleTest)

gtest_discover_tests(Array_3DTests)
