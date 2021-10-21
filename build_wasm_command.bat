emcc -I. -o dist/cave_generator.js ^
-Oz ^
-s MODULARIZE=1 ^
-s EXPORT_NAME=createModule ^
-s ALLOW_MEMORY_GROWTH=1 ^
--bind ^
cpp/cave_generator.cpp ^
cpp/flood_fill.cpp ^
cpp/grid.cpp ^
