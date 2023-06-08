#define _CRT_SECURE_NO_WARNINGS

#include "Book.h"
#include <vector>
#include <fstream>
#include <stdio.h>
#include <map>

void InitFromFile(string path, Book*& books, int& n) {
	fstream file(path);

	if (!file.is_open()) {
		cout << "file open error" << endl;
		return;
	}

	file >> n;

	books = new Book[n];

	for (int i = 0; i < n; i++) {
		string spec;

		file >> books[i].Author;
		file >> books[i].Title;
		file >> spec;
		books[i].Spec = StringToSpec(spec);
		file >> books[i].Place;
		file >> books[i].Publisher;
		file >> books[i].Year;
		file >> books[i].Pages;
	}
}

void InitFile(string path, Book* books, int& n) {
	fstream file(path);

	if (!file.is_open()) {
		cout << "file open error" << endl;
		return;
	}

	file << n << endl;
	for (int i = 0; i < n; i++) {
		file << books[i].String() << endl;
	}

	file.close();
}

void InitFromBinFile(string path, Book*& books, int& n) {
	FILE* file = fopen(path.c_str(), "rb");

	if (file == NULL) {
		cout << "file open error" << endl;
		return;
	}

	char temp[16];
	fgets(temp, 16, file);

	n = stoi(string(temp));

	books = new Book[n];

	char cbook[256];
	for (int i = 0; i < n; i++) {
		fgets(cbook, 256, file);
		books[i] = StringToBook(string(cbook));
	}

	fclose(file);
}

void InitBinFile(string path, Book* books, int& n) {
	FILE* file = fopen(path.c_str(), "a+b");

	if (file == NULL) {
		cout << "file open error" << endl;
		return;
	}

	fputs((to_string(n) + "\n").c_str(), file);

	for (int i = 0; i < n; i++) {
		fputs((books[i].String() + "\n").c_str(), file);
	}

	fclose(file);
}

void InitBooks(Book*& books, int n) {
	books = new Book[n];

	for (int i = 0; i < n; i++) {
		string spec;
		cout << "Author: "; cin >> books[i].Author;
		cout << "Title: "; cin >> books[i].Title;
		cout << "Specialization: "; cin >> spec;
		books[i].Spec = StringToSpec(spec);
		cout << "Place: "; cin >> books[i].Place;
		cout << "Publisher: "; cin >> books[i].Publisher;
		cout << "Year: "; cin >> books[i].Year;
		cout << "Pages: "; cin >> books[i].Pages;
		cout << endl;
	}
}

void Solve(Book* books, int n, int year, string path) {
	map<Specialization, vector<Book>> data;

	for (int i = 0; i < n; i++) {
		if (books[i].Year == year) {
			data[books[i].Spec].push_back(books[i]);
		}
	}

	int curr = 0;
	int max = 0;
	Specialization maxKey;
	for (auto kv : data) {
		curr = kv.second.size();
		if (curr > max) {
			maxKey = kv.first;
			max = curr;
		}
	}

	int len = data[maxKey].size();
	auto filteredBooks = new Book[len];
	for (int i = 0; i < len; i++) {
		filteredBooks[i] = data[maxKey][i];
	}

	InitFile(path, filteredBooks, len);

	delete[] filteredBooks;
}

int main() {

	int n;
	Book* books;
	string path = "data.txt";
	string bpath = "data.bin";
	string fpath = "filtered.txt";

	InitFromFile(path, books, n);

	for (int i = 0; i < n; i++) {
		cout << books[i].String() << endl;
	}

	InitBinFile(bpath, books, n);

	cout << string(64, '-') << endl;

	int k;
	Book* binBooks;
	InitFromBinFile(bpath, binBooks, k);

	for (int i = 0; i < k; i++) {
		cout << binBooks[i].String() << endl;
	}

	cout << string(64, '-') << endl;

	Solve(books, n, 2010, fpath);

	delete[] books;
	delete[] binBooks;

	return 0;
}