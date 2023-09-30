#Sunset example

file(
 GLOB_RECURSE ASSIGNMENT3_INC CONFIGURE_DEPENDS
 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
 *.h *.hpp
)

file(
 GLOB_RECURSE ASSIGNMENT3_SRC CONFIGURE_DEPENDS
 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
 *.c *.cpp
)
#Copies this assignment3_textures_sunset's asset folder to bin when it is built
add_custom_target(copyAssetsA3 ALL COMMAND ${CMAKE_COMMAND} -E copy_directory
${CMAKE_CURRENT_SOURCE_DIR}/assets/
${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/)

install(FILES ${ASSIGNMENT3_INC} DESTINATION include/assignment3_textures)
add_executable(assignment3_textures ${ASSIGNMENT3_SRC} ${ASSIGNMENT3_INC} ${ASSIGNMENT3_ASSETS})
target_link_libraries(assignment3_textures PUBLIC core IMGUI)
target_include_directories(assignment3_textures PUBLIC ${CORE_INC_DIR} ${stb_INCLUDE_DIR})

#Trigger asset copy when assignment3_textures is built
add_dependencies(assignment3_textures copyAssetsA3)