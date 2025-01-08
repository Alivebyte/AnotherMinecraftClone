file(GLOB_RECURSE MAIN_SRC
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)



add_executable(amc ${MAIN_SRC})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${MAIN_SRC})
target_include_directories(amc PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(amc PRIVATE sfml-graphics glm)
target_compile_features(amc PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET amc
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:amc>
        VERBATIM)
endif()