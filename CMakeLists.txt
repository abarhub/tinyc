# CMakeList.txt : projet CMake pour tinyc, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

project ("tinyc")

if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

# Ajoutez une source à l'exécutable de ce projet.
add_executable (tinyc "tinyc.cpp" "tinyc.h" "src/main.c" "src/main.h" "src/parser.c" "src/parser.h" "src/lexer.c" "src/lexer.h" "src/interpreter.c" "src/interpreter.h")

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
enable_testing()
add_executable(main_test2  "test/main_test2.c" "test/main_test.c" "src/main.c"   "src/parser.c" "src/parser.h" "src/lexer.c" "src/lexer.h" "src/interpreter.c" "test/interpreter_test.h" "test/parser_test.c" "test/parser_test.h" "test/interpreter_test.c" "test/interpreter_test.h")
#target_link_libraries(test  )
add_test(NAME  MyTest COMMAND main_test2)

