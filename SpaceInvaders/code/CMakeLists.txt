include(utils)

get_folder_name(FOLDER_NAME)

collect_files(HEADER_FILES SOURCE_FILES)
group_files("${HEADER_FILES}" "${SOURCE_FILES}")


add_executable(${PROJECT_NAME} WIN32
    ${HEADER_FILES}
	${SOURCE_FILES}
)

if( ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
set(CMAKE_EXECUTABLE_SUFFIX .html)
endif()

add_subdirectory(sdl-engine-libs/src)

include_directories(
	${PROJECT_SOURCE_DIR}/code/
)

target_link_libraries(${PROJECT_NAME}
	${SO_LIBRARIES}
	SpaceInvadersEngine
)
