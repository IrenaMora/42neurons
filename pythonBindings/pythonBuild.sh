git clone https://github.com/pybind/pybind11
pip3 install virtualenv
cd ../examples/gui/
virtualenv venv
. venv/bin/activate
pip install -r requirements.txt
python ../pythonBindings/setup.py install
python main.py
