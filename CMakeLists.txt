cmake_minimum_required(VERSION 3.18)

project("Void Trader" C)

add_executable(void-trader main.c)
set_target_properties(void-trader PROPERTIES SUFFIX ".elf")

gba_add_library_subdirectory(rom tonc)

target_link_libraries(void-trader PRIVATE rom tonc)

gba_target_objcopy(void-trader
 FIX_HEADER
 TITLE "Void Trader"
 MAKE_CODE VT
 VERSION 0
)
