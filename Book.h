#pragma once

#include <iostream>
#include <string>

using namespace std;

enum Specialization { Undefined, Inform, Math, Phys };

string SpecToString(Specialization spec);
Specialization StringToSpec(string spec);

struct Book {
	string Author;
	string Title;
	Specialization Spec;
	string Place;
	string Publisher;
	int Year;
	int Pages;

	Book() {
		this->Author = "";
		this->Title = "";
		this->Spec = Undefined;
		this->Place = "";
		this->Publisher = "";
		this->Year = this->Pages = 0;
	}

	Book(string author, string title, Specialization spec, string place, string publisher, int year, int pages) {
		this->Author = author;
		this->Title = title;
		this->Spec = spec;
		this->Place = place;
		this->Publisher = publisher;
		this->Year = year;
		this->Pages = pages;
	}

	void Show();
	void SetBookSpec(Specialization spec);

	string String();
};

Book StringToBook(string str);