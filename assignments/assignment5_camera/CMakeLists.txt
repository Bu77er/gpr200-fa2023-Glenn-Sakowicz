#Transformations example

file(
 GLOB_RECURSE ASSIGNMENT5_INC CONFIGURE_DEPENDS
 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
 *.h *.hpp
)

file(
 GLOB_RECURSE ASSIGNMENT5_SRC CONFIGURE_DEPENDS
 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
 *.c *.cpp
)
#Copies this assignment5_camera's asset folder to bin when it is built
add_custom_target(copyAssetsA5 ALL COMMAND ${CMAKE_COMMAND} -E copy_directory
${CMAKE_CURRENT_SOURCE_DIR}/assets/
${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/)

install(FILES ${ASSIGNMENT5_INC} DESTINATION include/assignment5_camera)
add_executable(assignment5_camera ${ASSIGNMENT5_SRC} ${ASSIGNMENT5_INC} ${ASSIGNMENT5_ASSETS})
target_link_libraries(assignment5_camera PUBLIC core IMGUI)
target_include_directories(assignment5_camera PUBLIC ${CORE_INC_DIR} ${stb_INCLUDE_DIR})

#Trigger asset copy when assignment5_camera is built
add_dependencies(assignment5_camera copyAssetsA5)