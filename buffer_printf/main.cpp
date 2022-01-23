#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <chrono> 
#include <algorithm>

const unsigned int REPEATE_PRINT = 100;

using namespace std;


string read_file() {

	ifstream file("text.txt");

	if (!file) {
		cerr << "File text.txt could not be opened for reading!" << endl;
		exit(1);
	}

	string str;
	string file_contents;

	while (getline(file, str)) {
		file_contents += str;
		file_contents.push_back('\n');
	} 

	return file_contents;
}

int64_t test_printf(const char* text) {
	auto start = std::chrono::steady_clock::now();
	for (unsigned int i = 0; i < REPEATE_PRINT; i++) {
		printf("%s", text);
	}
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);  	
	return elapsed_ms.count();
}


int64_t test_cout(const char* text) {
	auto start = std::chrono::steady_clock::now();
	for (unsigned int i = 0; i < REPEATE_PRINT; i++) {
		cout << text << endl; // endl clear buff
	}
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);  	
	return elapsed_ms.count();
}


int64_t test_buffered_printf(const string text) {
	auto start = std::chrono::steady_clock::now();
	
	const size_t buffer_size = 500;
	size_t start_index = 0;

	char *buff = new(nothrow) char[buffer_size + 1];
	if (!buff) {
		cout << "Could not allocate memory";
	}

	for (unsigned int i = 0; i < REPEATE_PRINT; i++) {
		while (start_index < text.length()) {

			memcpy(buff, text.substr(start_index, start_index + buffer_size).c_str(), buffer_size);
			buff[buffer_size] = '\0'; 

			printf("%s", buff);
			memset(buff, '\0', buffer_size);

			start_index += buffer_size;
		}
		start_index = 0;
	}

	delete[] buff;
	buff = nullptr;

	auto end = chrono::steady_clock::now();
	auto elapsed_ms = chrono::duration_cast<std::chrono::milliseconds>(end - start);  	
	return elapsed_ms.count();
}

int main() {

	const string text = read_file();
	int64_t printf_time = test_printf(text.c_str());
	int64_t cout_time = test_cout(text.c_str());
	int64_t buffered_printf_time = test_buffered_printf(text);

	cout << "TEST PRITNF elapsed time: " << printf_time << " ms\n";
	cout << "TEST COUT elapsed time: " << cout_time << " ms\n";
	cout << "TEST BUFFERED PRITNF elapsed time: " << buffered_printf_time << " ms\n";

	return 0;
}