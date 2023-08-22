
if(TARGET ultralight)
    return()    
endif(TARGET ultralight)

set(ULTRALIGHT_SDK_DIR ${CMAKE_CURRENT_LIST_DIR})

add_library(ultralight INTERFACE)

if(NOT DEFINED ULTRALIGHT_FIND_QUIETLY)
    message("Found ultralight at ${ULTRALIGHT_SDK_DIR}")
endif(NOT DEFINED ULTRALIGHT_FIND_QUIETLY)


if(${WIN32})
target_link_directories(ultralight INTERFACE ${ULTRALIGHT_SDK_DIR}/lib)
else()
target_link_directories(ultralight INTERFACE ${ULTRALIGHT_SDK_DIR}/bin)
endif(${WIN32})

set(ULTRALIGHT_BIN_DIR ${ULTRALIGHT_SDK_DIR}/bin)
set(ULTRALIGHT_RES_DIR ${ULTRALIGHT_SDK_DIR}/resources)

target_link_libraries(ultralight INTERFACE Ultralight UltralightCore AppCore WebCore)
target_include_directories(ultralight INTERFACE ${ULTRALIGHT_SDK_DIR}/include)