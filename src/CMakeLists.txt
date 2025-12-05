set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

add_executable(${BINARY}_run ${SOURCES})
add_dependencies(${BINARY}_run copy-data-files)
add_library(${BINARY}_lib STATIC ${SOURCES})

install(TARGETS ${BINARY}_run)

if(APPLE)
  add_custom_command(
    TARGET ${BINARY}_run POST_BUILD
    COMMAND dsymutil $<TARGET_FILE:${BINARY}_run>
    COMMAND strip -S -x $<TARGET_FILE:${BINARY}_run>
    COMMENT "Generating dSYM and stripping ${BINARY}_run"
  )
else()
  if(CMAKE_OBJCOPY AND CMAKE_STRIP)
    add_custom_command(
      TARGET ${BINARY}_run POST_BUILD
      COMMAND ${CMAKE_OBJCOPY} --only-keep-debug $<TARGET_FILE:${BINARY}_run> $<TARGET_FILE:${BINARY}_run>.debug
      COMMAND ${CMAKE_STRIP} --strip-debug --strip-unneeded $<TARGET_FILE:${BINARY}_run>
      COMMAND ${CMAKE_OBJCOPY} --add-gnu-debuglink=$<TARGET_FILE:${BINARY}_run>.debug $<TARGET_FILE:${BINARY}_run>
      COMMENT "Splitting debug information and stripping ${BINARY}_run"
    )
  endif()
endif()
