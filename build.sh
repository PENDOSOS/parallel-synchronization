if [ -d "build" ]; then
    cd build
else
    mkdir "build"
    cd build
fi

cmake ..
cmake --build .