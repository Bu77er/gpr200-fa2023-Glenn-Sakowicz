#Transformations example

file(
 GLOB_RECURSE ASSIGNMENT7_INC CONFIGURE_DEPENDS
 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
 *.h *.hpp
)

file(
 GLOB_RECURSE ASSIGNMENT7_SRC CONFIGURE_DEPENDS
 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
 *.c *.cpp
)
#Copies this assignment7_lighting's asset folder to bin when it is built
add_custom_target(copyAssetsA7 ALL COMMAND ${CMAKE_COMMAND} -E copy_directory
${CMAKE_CURRENT_SOURCE_DIR}/assets/
${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/)

install(FILES ${ASSIGNMENT7_INC} DESTINATION include/assignment7_lighting)
add_executable(assignment7_lighting ${ASSIGNMENT7_SRC} ${ASSIGNMENT7_INC} ${ASSIGNMENT7_ASSETS})
target_link_libraries(assignment7_lighting PUBLIC core IMGUI)
target_include_directories(assignment7_lighting PUBLIC ${CORE_INC_DIR} ${stb_INCLUDE_DIR})

#Trigger asset copy when assignment7_lighting is built
add_dependencies(assignment7_lighting copyAssetsA7)