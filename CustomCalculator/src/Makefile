VENV_NAME = custom_temporaty_venv
MAIN_PYTHON_FILE = mainwindow.py

CC = gcc
LIBS_CHECK = $(shell pkg-config --cflags --libs check) 
C_FILE_TESTS = testing_files/testing_src.c testing_files/testing_header.h
LIBRARY_FILE_A = s21_calculate.a
SHARED_LIB_NAME = calculate
PATH_BUILD = $(shell pwd)/build
CFLAGS_GCOV = -fprofile-arcs -ftest-coverage
BINNAME = SmartCalc

all: install

install: uninstall 
	mkdir build
	cd build; \
		sudo apt install python3.10-venv; \
		python3 -m venv $(VENV_NAME); \
		. ./$(VENV_NAME)/bin/activate; \
		pip3 install pyside6; \
		pip3 install pyqtgraph; \
		cp ../Model/* ../Controller/* ../View/* ../testing_files . -r; \
		gcc -Wall -fPIC -shared -o lib$(SHARED_LIB_NAME).so calculate.h *.c; \
		echo "$(PATH_BUILD)/custom_temporaty_venv/bin/python3 $(PATH_BUILD)/mainwindow.py" >> $(BINNAME); \
		chmod +x $(BINNAME); \
		deactivate; \

start_calculator:
	./build/$(BINNAME)

test: install
	cd build; \
		$(CC) $(C_FILE_TESTS) -Wl,-rpath=$(PATH_BUILD) -o test $(LIBS_CHECK) -L$(PATH_BUILD) -l$(SHARED_LIB_NAME); 
	./build/test

gcov_report: install
	cd build; \
		$(CC) -c *.c  $(CFLAGS_GCOV); \
		$(CC) *.o $(C_FILE_TESTS) -o test_gcov $(LIBS_CHECK) -lgcov; 
	./build/test_gcov 
	lcov --directory ./build/ --capture --output ./build/Meow.info
	genhtml ./build/Meow.info --output ./build/CatReport
	open ./build/CatReport/index.html		

dvi:
	echo If make fails to open the file, it means, Make cannot open PDF files on your system. You can open ../docs/index.pdf manually in your favourite PDF viewer instead. Also, there is a markdown index.md analogue.
	open index.pdf

dist: uninstall
	rm -fr dist-idaliaka-smartcalc.tar.gz
	tar -czf dist-idaliaka-smartcalc.tar.gz * 

uninstall:
	rm -rf build

clean: uninstall
	rm -rf $(LIBRARY_FILE_A) SmartCalc test __pycache__ Meow.info CatReport a.out 
	rm -fr dist-idaliaka-smartcalc.tar.gz custom_temporaty_venv 
	rm -fr *ui.py ./View/*ui.py