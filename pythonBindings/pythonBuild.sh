git clone https://github.com/pybind/pybind11
python3.9 -m pip install virtualenv
python3.9 -m virtualenv venv
. venv/bin/activate
python3.9 -m pip install -r examples/gui/requirements.txt
python3.9 setup.py install
python3.9 examples/gui/main.py
