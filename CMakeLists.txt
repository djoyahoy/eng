cmake_minimum_required(VERSION 3.0)

project(eng)

set(
	SRCS
	${CMAKE_CURRENT_SOURCE_DIR}/gen/src/enemy_maker.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gen/src/prop_maker.cpp
	libs/src/jsoncpp.cpp
	src/actor/spirit.cpp
	src/actor/state_flag.cpp
	src/actor/health.cpp
	src/common/counter.cpp
	src/enemy/enemy.cpp
	src/enemy/enemy_spirit.cpp
	src/game/game_sdl2.cpp
	src/gfx/camera.cpp
	src/gfx/painter_gl21.cpp
	src/gfx/sprite.cpp
	src/hero/hero.cpp
	src/hero/spirit.cpp
	src/hero/states/common.cpp
	src/hero/states/idle.cpp
	src/hero/states/fall.cpp
	src/hero/states/walk.cpp
	src/hero/states/jump.cpp
	src/hero/states/roll.cpp
	src/hero/states/docile.cpp
	src/hero/states/attack.cpp
	src/hero/states/healthy.cpp
	src/hero/states/damaged.cpp
	src/hero/states/cling.cpp
	src/hero/states/jump_away.cpp
	src/hero/states/climb.cpp
	src/hero/states/explore.cpp
	src/input/controller.cpp
	src/main.cpp
	src/physics/bound.cpp
	src/physics/force.cpp
	src/physics/mass.cpp
	src/physics/point.cpp
	src/prop/prop.cpp
	src/stage/dungeon.cpp
	src/stage/room.cpp
	src/stage/tile.cpp
	src/stage/zone.cpp
)
add_executable(eng ${SRCS})

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/gen/include/enemy_maker.h ${CMAKE_CURRENT_SOURCE_DIR}/gen/src/enemy_maker.cpp
	COMMAND ./generate.py enemy ${CMAKE_CURRENT_SOURCE_DIR}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/scripts
	COMMENT "Generating code"
)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/gen/include/prop_maker.h ${CMAKE_CURRENT_SOURCE_DIR}/gen/src/prop_maker.cpp
	COMMAND ./generate.py prop ${CMAKE_CURRENT_SOURCE_DIR}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/scripts
	COMMENT "Generating code"
)

add_custom_target(
	builder ALL
	COMMAND ./builder.py
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/scripts
	DEPENDS eng
	COMMENT "Building resources"
)

include_directories(./include ./gen/include ./libs/include /usr/local/include/SDL2 /System/Library/Frameworks/OpenGL.framework/Headers)
set_target_properties(eng PROPERTIES COMPILE_FLAGS "-c -Wall -std=c++1y -D_THREAD_SAFE -O0 -g -DDEBUG")

link_directories(/usr/local/lib)
set_target_properties(eng PROPERTIES LINK_FLAGS "-lSDL2 -framework OpenGL")
