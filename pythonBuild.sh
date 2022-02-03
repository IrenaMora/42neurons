#pip3 install -r requirements.txt
mkdir -p build
cd build
cmake .. && make && python ../simpleExample.py
