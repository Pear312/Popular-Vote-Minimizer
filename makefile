build:
	rm -f app.exe
	gcc app.c MinPopVote.c -o app.exe

run:
	./app.exe

run_quiet:
	./app.exe -q

valgrind:
	valgrind -s --tool=memcheck --leak-check=yes --track-origins=yes ./app.exe

run_fast:
	./app.exe -f

run_quiet_fast:
	./app.exe -q -f

run_quiet_fast_1916:
	./app.exe -q -f -y 1916

built_test:
	gcc test.c MinPopVote.c -o test.exe

run_test: 
	./test.exe
