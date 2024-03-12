VENV_NAME = CustomTemporatyVenv
MAIN_PYTHON = main.py

CC = gcc
LIBS_CHECK = $(shell pkg-config --cflags --libs check) 
C_FILE_TESTS = TestingFiles/testing_src.c TestingFiles/testing_header.h
SHARED_LIB_NAME = calculate
PATH_BUILD = $(shell pwd)/build
CFLAGS_GCOV = -fprofile-arcs -ftest-coverage
BINNAME = CustomCalculator

all: install start_calculator

install: uninstall 
	mkdir build
	cd build; \
		sudo apt install python3.10-venv; \
		python3 -m venv $(VENV_NAME); \
		. ./$(VENV_NAME)/bin/activate; \
		pip3 install pyside6; \
		pip3 install pyqtgraph; \
		cp ../Model ../Controller ../View ../TestingFiles ../$(MAIN_PYTHON) . -r; \
		gcc -Wall -fPIC -shared ./Model/*.c ./Model/*.h -o ./Model/lib$(SHARED_LIB_NAME).so; \
		pyside6-uic ./View/ui/form.ui -o ./View/ui/form_ui.py; \
		pyside6-uic ./View/ui/form_plot.ui -o ./View/ui/form_plot_ui.py; \
		pyside6-uic ./View/ui/credit_calc.ui -o ./View/ui/credit_calc_ui.py; \
		pyside6-uic ./View/ui/deposit_calc.ui -o ./View/ui/deposit_calc_ui.py; \
		echo "$(PATH_BUILD)/$(VENV_NAME)/bin/python3 $(PATH_BUILD)/$(MAIN_PYTHON)" >> $(BINNAME); \
		chmod +x $(BINNAME); \
		deactivate; \

start_calculator:
	./build/$(BINNAME)

test: install
	cd build/TestingFiles; \
		$(CC) *.c *.h -Wl,-rpath=$(PATH_BUILD)/Model -o test $(LIBS_CHECK) -L$(PATH_BUILD)/Model -l$(SHARED_LIB_NAME); \
		./test

gcov_report: install
	cd build/TestingFiles; \
		$(CC) -c *.c *.h ../Model/*.c ../Model/*.h $(CFLAGS_GCOV); \
		$(CC) *.o -o test_gcov $(LIBS_CHECK) -lgcov; \
		./test_gcov 
	lcov --directory ./build/ --capture --output ./build/Meow.info
	genhtml ./build/Meow.info --output ./build/CatReport
	open ./build/CatReport/index.html		

dvi:
	open ../README.md

dist: uninstall
	rm -fr *.tar.gz
	tar -czf dist-customcalc.tar.gz * 

uninstall:
	rm -rf build

clean: uninstall
	rm -rf SmartCalc test __pycache__ ./View/__pycache__ Meow.info CatReport a.out 
	rm -fr *.tar.gz custom_temporaty_venv 
	rm -fr *ui.py ./View/*ui.py ./View/ui/*ui.py ./View/ui_form.h
