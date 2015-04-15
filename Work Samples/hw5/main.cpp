#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <QApplication>
#include "product.h"
#include "datastore.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
#include "MainWindow.h"
#include "mystore.h"

int main(int argc, char* argv[])
{
	if(argc < 2) {
		std::cerr << "Please specify a database file" << std::endl;
	}

	QApplication app(argc, argv);

	MyStore ds;

	// Instantiate parser
	DBParser parser;

	// Instantiate individual product parsers
	parser.addProductParser(new ProductBookParser);
	parser.addProductParser(new ProductClothingParser);
	parser.addProductParser(new ProductMovieParser);

	// Parser the database to populate the DataStore
	if(parser.parse(argv[1], ds)) {
		std::cerr << "Error parsing!" << std::endl;
		return 1;
	}

	MainWindow mainWindow(ds);

	mainWindow.show();

	return app.exec();
}