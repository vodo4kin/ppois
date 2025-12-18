#!/bin/bash
rm -rf build
conan install . --build=missing
./sc-machine/bin/sc-builder \
-i ./knowledge-base/repo.path \
-o ./kb.bin \
--clear
cmake --preset conan-release -DBUILD_TESTS=ON
cmake --build --preset conan-release
./build/Release/problem-solver/pcb-layout-module/pcb-layout-module-tests
echo "Скрипт заверишл своё выполнение..."
sleep 2
