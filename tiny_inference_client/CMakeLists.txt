add_subdirectory(tie_client)

if(TIE_CLIENT_BUILD_UNIT_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(TIE_CLIENT_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()