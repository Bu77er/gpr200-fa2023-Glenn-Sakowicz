#Transformations example

file(
 GLOB_RECURSE ASSIGNMENT6_INC CONFIGURE_DEPENDS
 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
 *.h *.hpp
)

file(
 GLOB_RECURSE ASSIGNMENT6_SRC CONFIGURE_DEPENDS
 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
 *.c *.cpp
)
#Copies this assignment6_proceduralGeometry's asset folder to bin when it is built
add_custom_target(copyAssetsA6 ALL COMMAND ${CMAKE_COMMAND} -E copy_directory
${CMAKE_CURRENT_SOURCE_DIR}/assets/
${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/)

install(FILES ${ASSIGNMENT6_INC} DESTINATION include/assignment6_proceduralGeometry)
add_executable(assignment6_proceduralGeometry ${ASSIGNMENT6_SRC} ${ASSIGNMENT6_INC} ${ASSIGNMENT6_ASSETS})
target_link_libraries(assignment6_proceduralGeometry PUBLIC core IMGUI)
target_include_directories(assignment6_proceduralGeometry PUBLIC ${CORE_INC_DIR} ${stb_INCLUDE_DIR})

#Trigger asset copy when assignment6_proceduralGeometry is built
add_dependencies(assignment6_proceduralGeometry copyAssetsA6)