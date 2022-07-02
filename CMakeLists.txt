cmake_minimum_required(VERSION 3.18)

project("Void Trader" C)

add_executable(
# target
void-trader

    #main    
        source/main.c
    #game
        source/game.c include/game.h
    #scene
        source/scene.c include/scene.h
    #station
        source/station.c include/station.h
    #commodity
        source/commodity.c include/commodity.h
    #util
        source/util.c include/util.h
    
    #img
        #splash
        source/splash.c include/splash.h
)


target_include_directories(void-trader PRIVATE include)

set_target_properties(void-trader PROPERTIES SUFFIX ".elf")

gba_add_library_subdirectory(rom tonc seven)

target_link_libraries(void-trader PRIVATE rom tonc seven)

gba_target_objcopy(void-trader
 FIX_HEADER
 TITLE "Void Trader"
 MAKE_CODE VT
 VERSION 1
)
