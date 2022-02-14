git clone https://github.com/pybind/pybind11
pip3 install virtualenv
virtualenv venv
. venv/bin/activate
pip install -r examples/gui/requirements.txt
python setup.py install
python examples/gui/main.py
