# CMakeList.txt : projet CMake pour tinyc, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

project ("tinyc")

# Ajoutez une source à l'exécutable de ce projet.
add_executable (tinyc "tinyc.cpp" "tinyc.h" "src/main.c" "src/main.h")

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
