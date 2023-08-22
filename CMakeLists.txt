cmake_minimum_required(VERSION 3.0...3.5)
project(UltralightExample VERSION 0.0.1)

set(APP_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)


add_executable(${APP_NAME} WIN32 MACOSX_BUNDLE 
  src/main.cpp
  src/App.cpp
)

# Set the assets path to "/assets" or "/../Resources/assets" on macOS
if (APPLE)
set(ASSETS_PATH "$<TARGET_FILE_DIR:${APP_NAME}>/../Resources/assets") 
else ()
set(ASSETS_PATH "$<TARGET_FILE_DIR:${APP_NAME}>/assets") 
endif ()


set(Ultralight_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/ultralight_sdk)
find_package(Ultralight QUIET REQUIRED CONFIG)

target_link_libraries(${APP_NAME} PRIVATE ultralight)

file(GLOB_RECURSE AssetFiles ${CMAKE_SOURCE_DIR}/assets/*)


if (APPLE)
# Enable High-DPI on macOS through our custom Info.plist template
set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in) 
endif()

if(${WIN32})
if(${MSVC})
target_link_options(${APP_NAME} PRIVATE /SUBSYSTEM:$<$<CONFIG:Debug>:CONSOLE>$<$<NOT:$<CONFIG:Debug>>:WINDOWS>)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
target_link_options(${APP_NAME} PRIVATE -Wl,/SUBSYSTEM:$<$<CONFIG:Debug>:CONSOLE>$<$<NOT:$<CONFIG:Debug>>:WINDOWS>)
elseif(${MINGW})
target_link_options(${APP_NAME} PRIVATE -m$<$<CONFIG:Debug>:console>$<$<NOT:$<CONFIG:Debug>>:windows>)
endif(${MSVC})

target_compile_definitions(${APP_NAME} PRIVATE main=$<$<CONFIG:Debug>:main>$<$<NOT:$<CONFIG:Debug>>:WinMain>)
endif(${WIN32})

add_custom_target(Assets ALL 
  ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets/" "${ASSETS_PATH}" 
DEPENDS ${AssetFiles})

# Copy all binaries to target directory
add_custom_command(TARGET ${APP_NAME}
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${ULTRALIGHT_BIN_DIR}/ $<TARGET_FILE_DIR:${APP_NAME}>)
  
# Copy resources to assets directory
add_custom_command(TARGET ${APP_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${ULTRALIGHT_RES_DIR} "${ASSETS_PATH}/resources")
