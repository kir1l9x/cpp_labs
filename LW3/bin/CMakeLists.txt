add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE SandPileLib WorkWithInputLib BMPOutputLib ArgParsingLib)
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/sand_pile_sim
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/work_with_input_resources
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/work_with_output_bmp
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/work_with_comm_args
        )
