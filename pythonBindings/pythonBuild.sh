git clone https://github.com/pybind/pybind11
python3.9 -m venv venv
. venv/bin/activate
pip3 install -r examples/gui/requirements.txt
python3.9 setup.py install
python3.9 examples/gui/main.py
