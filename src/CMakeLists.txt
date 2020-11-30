############ Start Version Parsing ##################

file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/version.txt" SIMPLIFYLINE_VERSION_READ)
foreach(ver ${SIMPLIFYLINE_VERSION_READ})
    if (ver MATCHES "(MAJOR|MINOR|PATCH) +([^ ]+)$")
        set(SIMPLIFYLINE_VERSION_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()
string(CONCAT SIMPLIFYLINE_VERSION
    "${SIMPLIFYLINE_VERSION_MAJOR}"
    ".${SIMPLIFYLINE_VERSION_MINOR}"
    ".${SIMPLIFYLINE_VERSION_PATCH}"
)

set(PROJECT_VERSION "${SIMPLIFYLINE_VERSION}")

message("Version is ${PROJECT_VERSION}")

############# End Version Parsing ##################


add_subdirectory(SimplifyLine)

if (SPL_BUILD_PYMODULE)
    add_subdirectory(Python)
endif ()
