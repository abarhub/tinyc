# CMakeList.txt : projet CMake pour tinyc, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

project ("tinyc")

# Ajoutez une source à l'exécutable de ce projet.
add_executable (tinyc "tinyc.cpp" "tinyc.h" "src/main.c" "src/main.h" "src/parser.c" "src/parser.h" "src/lexer.c" "src/lexer.h" "src/interpreter.c" "src/interpreter.h")

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
enable_testing()
add_executable(main_test2  "test/main_test2.c" "test/main_test.c" "src/main.c"   "src/parser.c" "src/parser.h" "src/lexer.c" "src/lexer.h" "src/interpreter.c" "test/interpreter_test.h" "test/parser_test.c" "test/parser_test.h" "test/interpreter_test.c" "test/interpreter_test.h")
#target_link_libraries(test  )
add_test(NAME  MyTest COMMAND main_test2)

