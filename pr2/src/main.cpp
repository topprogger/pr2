#include <iostream>
#include <iomanip>
#include <string>

#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#include "db.cpp"
using namespace std;

enum INPUTS {
	ADD = 1,
	VIEW_DATA,
	EDIT_DATA,
	REMOVE,
	EXIT
};

enum EDIT_MENU_COMMANDS {
	EDIT_CAPTION = 1,
	EDIT_PRICE,
	EDIT_COUNT,
	EDIT_DATE,
	EDIT_BACK
};

void __pause()
{
	cout << "Press any key...";
	cin.get();
	cin.ignore();
}

int main(int argc, char* argv[])
{
	DataBase data_base;
	unsigned int input = 0;

	string caption = "", date = "";
	int price = 0, count = 0;

	system("clear");
	cout << "Welcome to DataBae" << '\n';
	cout << setfill('-') << setw(50) << '\n';

	bool is_input = true;
	while (is_input) {

		cout << "[" << ADD << "] -> Add" << '\n';
		cout << "[" << VIEW_DATA << "] -> View" << '\n';
		cout << "[" << EDIT_DATA << "] -> Edit" << '\n';
		cout << "[" << REMOVE << "] -> Remove" << '\n';
		cout << "[" << EXIT << "] -> Exit" << '\n';

		cout << ">: ";
		cin >> input;

		if (cin.good()) {
			system("clear");
			switch (input) {
				case ADD: {
					caption = "", date = "";
					price = 0, count = 0;

					bool not_add = true;
					while (not_add) {

						if (caption.empty()) {
							cout << "Enter cost caption: ";
							cin >> caption;
						}

						while (price <= 0 or cin.fail()) {
							cout << "Enter cost price: ";
							cin >> price;

							if (cin.good()) {

								if (price < 0) {
									cerr << "Price wasn't <= 0" << '\n';
								}

							} else if (cin.fail()) {
								cin.clear();
								cin.sync();
								cin.ignore(INT_MAX, '\n');
							}
						}

						while (count <= 0 or cin.fail()) {
							cout << "Enter cost count: ";
							cin >> count;

							if (cin.good()) {
								if (count < 0) {
									cerr << "Count wasn't <= 0" << '\n';
								}
							} else if (cin.fail()) {
								cin.clear();
								cin.sync();
								cin.ignore(INT_MAX, '\n');
							}
						}

						if (date.empty()) {
							cout << "Enter cost date (dd.mm.yyy): ";
							cin >> date;
						}

						if (!caption.empty() && (price > 0) && (count > 0) && !date.empty()) {
							data_base.add(
								new Cost(caption, price, count, date)
							);
							not_add = false;
						} else {
							cerr << "Someone data is empty";
						}
					}
				} break;
				case VIEW_DATA: {

					if (data_base.count() > 0) {
						data_base.view();
					} else {
						cerr << "Databae is empty" << '\n';
					}

					__pause();
				} break;
				case EDIT_DATA: {

					if (data_base.count() > 0) {
						int id = 0;
						data_base.view();

						cout << "Enter entry ID: ";
						cin >> id;

						system("clear");
						if (cin.good()) {
							if (id > 0) {
								Cost *edit_cost_entry = data_base.edit(id);

								bool is_edit = true;
								while (is_edit) {
									caption = "", date = "";
									price = 0, count = 0;
									int edit_input = 0;

									data_base.view(id);
									cout << setfill('-') << setw(80) << '\n';
									cout << EDIT_CAPTION << ". Change cost caption" << '\n';
									cout << EDIT_PRICE <<   ". Change cost price" << '\n';
									cout << EDIT_COUNT <<   ". Change cost count" << '\n';
									cout << EDIT_DATE <<    ". Change cost date" << '\n';
									cout << EDIT_BACK <<    ". Back" << '\n';

									cout << ">: ";
									cin >> edit_input;

									system("clear");
									if (cin.good()) {

										switch (edit_input) {
											case EDIT_CAPTION: {

												do {

													cout << "Enter new cost caption: ";
													cin >> caption;

												} while (caption.empty());

												edit_cost_entry->setCaption(caption);

											} break;
											case EDIT_PRICE: {

												do {

													cout << "Enter new cost price: ";
													cin >> price;

													if (cin.good()) {
														if (price < 0) {
															cout << "Price wasn't <= 0" << '\n';
														}
													} else if (cin.fail()) {
														cin.clear();
														cin.sync();
														cin.ignore(INT_MAX, '\n');
													}

												} while (price == 0 or cin.fail());

												edit_cost_entry->setPrice(price);
											} break;
											case EDIT_COUNT: {

												do {

													cout << "Enter new cost count: ";
													cin >> count;

													if (cin.good()) {

														if (count < 0) {
															cout << "Count wasn't <= 0" << '\n';
														}

													} else if (cin.fail()) {
														cin.clear();
														cin.sync();
														cin.ignore(INT_MAX, '\n');
													}

												} while (count == 0 or cin.fail());

												edit_cost_entry->setCount(count);

											} break;
											case EDIT_DATE: {

												do {

													cout << "Enter new date (dd.mm.yyyy): ";
													cin >> date;

												} while (date.empty());

												edit_cost_entry->setDate(date);

											} break;
											case EDIT_BACK: {
												is_edit = false;
											} break;
										}

									} else if (cin.fail()) {
										cin.clear();
										cin.sync();
										cin.ignore(INT_MAX, '\n');
									}

									system("clear");
								}

							} else {
								cerr << "ID wasn't be <= 0" << '\n';
								__pause();
							}
						} else {
							cerr << "Incorrect input" << '\n';
							cin.clear();
							cin.sync();
							__pause();
						}
					} else {
						cerr << "Database is empty" << '\n';
						__pause();
					}

				} break;
				case REMOVE: {
					if (data_base.count() > 0) {
						int id = 0;

						data_base.view();
						cout << "Enter entry ID: ";
						cin >> id;

						if (cin.good()) {
							if (id > 0) {
								data_base.remove(id);
							} else {
								cerr << "ID wasn't be <= 0" << '\n';
								__pause();
							}
						} else {
							cerr << "Incorrect input" << '\n';
							cin.clear();
							cin.sync();
							__pause();
						}

					} else {
						cerr << "Database is empty" << '\n';
					}

					__pause();
				} break;
				case EXIT: {
					is_input = false;
				} break;
			}
		} else {
			cerr << "Incorrect input" << '\n';
			cin.clear();
			cin.sync();
			__pause();
		}
		system("clear");
	}

}

