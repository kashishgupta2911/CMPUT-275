file_name=wordl
bash_file=test_diff
python_file=generate_random_alpha_digits

main: build run

run:
	./$(file_name) irate

build:
	gcc -Wall -Wvla -Werror $(file_name).c -o $(file_name)

test: build
	./runTests ./$(file_name) test_stem.txt

mem-check:
	gcc -g $(file_name).c -o $(file_name)
	valgrind ./$(file_name)
generate:
	python3 ./$(python_file).py

run-tests: build generate
	chmod +x ./$(bash_file)
	./$(bash_file)