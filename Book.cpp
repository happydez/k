#include "Book.h"

string SpecToString(Specialization spec) {
	switch (spec)
	{
		case Inform:	return "Inform";
		case Math:		return "Math";
		case Phys:		return "Physics";
		default:		return "Undefined";
	}
}

Specialization StringToSpec(string spec) {
	if (spec == "Inform") {
		return Inform;
	}
	else if (spec == "Math") {
		return Math;
	}
	else if (spec == "Physics") {
		return Phys;
	}
	else {
		return Undefined;
	}
}

void Book::Show() {
	cout << this->String() << endl;
}

void Book::SetBookSpec(Specialization spec) {
	this->Spec = spec;
}

string Book::String() {
	return this->Author + " " + this->Title + " " +
		SpecToString(this->Spec) + " " + this->Place + " " +
		this->Publisher + " " + to_string(this->Year) + " " + to_string(this->Pages);
}

Book StringToBook(string str) {
	int next = 0;

	string author = str.substr(next, str.find_first_of(' ', next));
	next = str.find_first_of(' ', next) + 1;

	string title = str.substr(next, str.find_first_of(' ', next) - next);
	next = str.find_first_of(' ', next) + 1;

	string spec = str.substr(next, str.find_first_of(' ', next) - next);
	next = str.find_first_of(' ', next) + 1;

	string place = str.substr(next, str.find_first_of(' ', next) - next);
	next = str.find_first_of(' ', next) + 1;

	string publisher = str.substr(next, str.find_first_of(' ', next) - next);
	next = str.find_first_of(' ', next) + 1;

	int year = stoi(str.substr(next, str.find_first_of(' ', next) - next));
	next = str.find_first_of(' ', next) + 1;

	int pages = stoi(str.substr(next));

	return Book(author, title, StringToSpec(spec), place, publisher, year, pages);
}