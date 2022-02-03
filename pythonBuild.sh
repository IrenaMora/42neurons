git clone https://github.com/pybind/pybind11
mkdir -p build &&
cd build &&
cmake .. && make && python3 ../simpleExample.py
