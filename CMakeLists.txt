cmake_minimum_required(VERSION 3.14)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp Fighter.h Typedefs.h Fighter.cpp Move.h Move.cpp Mario.h Mario.cpp Jump.h Jump.cpp "Ground Pound.h" "Ground Pound.cpp" Grab.h Grab.cpp Kick.h Kick.cpp Helpers.h PlayerMoveSelector.cpp PlayerMoveSelector.h CPUMoveSelector.cpp CPUMoveSelector.h Charge.h Charge.cpp Bite.cpp Bite.h BattleEngine.cpp BattleEngine.h)