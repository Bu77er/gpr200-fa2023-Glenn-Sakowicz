#Transformations example

file(
 GLOB_RECURSE ASSIGNMENT4_INC CONFIGURE_DEPENDS
 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
 *.h *.hpp
)

file(
 GLOB_RECURSE ASSIGNMENT4_SRC CONFIGURE_DEPENDS
 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
 *.c *.cpp
)
#Copies this assignment4_transformations's asset folder to bin when it is built
add_custom_target(copyAssetsA4 ALL COMMAND ${CMAKE_COMMAND} -E copy_directory
${CMAKE_CURRENT_SOURCE_DIR}/assets/
${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/)

install(FILES ${ASSIGNMENT4_INC} DESTINATION include/assignment4_transformations)
add_executable(assignment4_transformations ${ASSIGNMENT4_SRC} ${ASSIGNMENT4_INC} ${ASSIGNMENT4_ASSETS})
target_link_libraries(assignment4_transformations PUBLIC core IMGUI)
target_include_directories(assignment4_transformations PUBLIC ${CORE_INC_DIR} ${stb_INCLUDE_DIR})

#Trigger asset copy when assignment4_transformations is built
add_dependencies(assignment4_transformations copyAssetsA4)