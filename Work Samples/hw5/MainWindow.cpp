#include "MainWindow.h"
#include <iomanip>
#include <sstream>
#include "util.h"
#include "msort.h"
#include <fstream>

MainWindow::MainWindow(MyStore& ds_) 
{
	overallLayout = new QVBoxLayout;

	ds = ds_;

	currentRow = -1;

	//  Setup search bar
	searchLayout = new QHBoxLayout;
	searchBar = new QLineEdit;
	searchButton = new QPushButton("Search");
	searchLayout->addWidget(searchBar);
	searchLayout->addWidget(searchButton);
	overallLayout->addLayout(searchLayout);

	// Setup radio buttons
	radioLayout = new QHBoxLayout;
	andRadioButton = new QRadioButton("AND");
	orRadioButton = new QRadioButton("OR");
	radioLayout->addWidget(andRadioButton);
	radioLayout->addWidget(orRadioButton);
	radioLayout->addStretch();
	overallLayout->addLayout(radioLayout);

	// Setup sorting buttons
	sortingLayout = new QHBoxLayout;
	sortLabel = new QLabel("Sort:");
	alphabeticalButton = new QPushButton("Alphabetical");
	ratingButton = new QPushButton("Rating");
	sortingLayout->addWidget(sortLabel);
	sortingLayout->addWidget(alphabeticalButton);
	sortingLayout->addSpacing(5);
	sortingLayout->addWidget(ratingButton);
	sortingLayout->addStretch();
	overallLayout->addLayout(sortingLayout);

	// Middle of layout (product list and user/cart buttons)
	middleLayout = new QHBoxLayout;
	productList = new QListWidget;
	productList->setMinimumSize(QSize(500, 300));
	middleLayout->addWidget(productList);
	userCartLayout = new QVBoxLayout;
	userDropdown = new QComboBox;
	addCartButton = new QPushButton("Add To Cart");
	viewCartButton = new QPushButton("View Cart");
	userCartLayout->addWidget(userDropdown);
	userCartLayout->addWidget(addCartButton);
	userCartLayout->addWidget(viewCartButton);
	middleLayout->addLayout(userCartLayout);
	overallLayout->addLayout(middleLayout);

	// Review list
	reviewList = new QListWidget;
	addReviewButton = new QPushButton("Add Review");
	overallLayout->addWidget(reviewList);
	overallLayout->addWidget(addReviewButton);

	// View Cart window
	viewCartWindow = new QWidget;
	viewCartWindow->setMinimumSize(QSize(500, 300));
	viewCartLayout = new QHBoxLayout;
	cartList = new QListWidget;
	viewCartLayout->addWidget(cartList);
	buyRemoveLayout = new QVBoxLayout;
	buyCartButton = new QPushButton("Buy Cart");
	removeProductButton = new QPushButton("Remove Product");
	closeCartButton = new QPushButton("Close Cart");
	buyRemoveLayout->addWidget(buyCartButton);
	buyRemoveLayout->addWidget(removeProductButton);
	buyRemoveLayout->addWidget(closeCartButton);
	viewCartLayout->addLayout(buyRemoveLayout);
	viewCartWindow->setLayout(viewCartLayout);

	// Add review window
	addReviewWindow = new QWidget;
	addReviewWindow->setMinimumSize(QSize(400, 300));
	addReviewLayout = new QVBoxLayout;
	ratingLabel = new QLabel("Rating (1-5)");
	ratingBox = new QLineEdit;
	dateLabel = new QLabel("Date (Format: YYYY-MM-DD)");
	dateBox = new QLineEdit;
	reviewTextLabel = new QLabel("Review Text");
	reviewTextBox = new QLineEdit;
	completeAddReviewButton = new QPushButton("Add Review");
	addReviewLayout->addWidget(ratingLabel);
	addReviewLayout->addWidget(ratingBox);
	addReviewLayout->addWidget(dateLabel);
	addReviewLayout->addWidget(dateBox);
	addReviewLayout->addWidget(reviewTextLabel);
	addReviewLayout->addWidget(reviewTextBox);
	addReviewLayout->addWidget(completeAddReviewButton);
	addReviewWindow->setLayout(addReviewLayout);

	// Quit button
	quitButton = new QPushButton("Quit");
	overallLayout->addWidget(quitButton);

	// Add usernames to User dropdown box
	std::map<std::string, User*> userList = ds.getUsers();
	std::map<std::string, User*>::iterator it;
	for(it = userList.begin(); it != userList.end(); ++it) {
		userDropdown->addItem(QString::fromStdString(it->first));
	}


	// Slots and signals
	connect(viewCartButton, SIGNAL(clicked()), this, SLOT(viewCart()));
	connect(searchButton, SIGNAL(clicked()), this, SLOT(searchClicked()));
	connect(alphabeticalButton, SIGNAL(clicked()), this, SLOT(sortAlpha()));
	connect(ratingButton, SIGNAL(clicked()), this, SLOT(sortRating()));
	connect(addCartButton, SIGNAL(clicked()), this, SLOT(addToCartClicked()));
	connect(productList, SIGNAL(currentRowChanged(int)), this, SLOT(changeCurrentRow(int)));
	connect(buyCartButton, SIGNAL(clicked()), this, SLOT(buyCart()));
	connect(removeProductButton, SIGNAL(clicked()), this, SLOT(removeProduct()));
	connect(closeCartButton, SIGNAL(clicked()), this, SLOT(closeCart()));
	connect(productList, SIGNAL(currentRowChanged(int)), this, SLOT(updateReviews(int)));
	connect(addReviewButton, SIGNAL(clicked()), this, SLOT(addReviewClicked()));
	connect(completeAddReviewButton, SIGNAL(clicked()), this, SLOT(completeAddReview()));
	connect(quitButton, SIGNAL(clicked()), this, SLOT(quitApplication()));

	setLayout(overallLayout);
}

MainWindow::~MainWindow()
{
	delete overallLayout;
	/*
	delete searchButton;
	delete radioLayout;
	delete andRadioButton;
	delete orRadioButton;
	delete sortingLayout;
	delete sortLabel;subl
	delete alphabeticalButton;
	delete ratingButton;
	delete middleLayout;
	delete userCartLayout;
	delete productList;
	delete userDropdown;
	delete addCartButton;
	delete viewCartButton;
	delete reviewList;
	delete addReviewButton;
	delete viewCartWindow;
	delete viewCartLayout;
	delete cartList;
	delete buyRemoveLayout;
	delete buyCartButton;
	delete removeProductButton;
	delete closeCartButton;
	delete addReviewWindow;
	delete addReviewLayout;
	delete searchLayout;
	delete ratingLabel;
	delete ratingBox;
	delete dateLabel;
	delete dateBox;
	delete reviewTextLabel;
	delete reviewTextBox;
	delete completeAddReviewButton;
	delete quitButton;

	*/

}

// Slots

void MainWindow::viewCart() 
{
	std::string currentUsername = userDropdown->currentText().toStdString();
	std::vector<Product*> cart = ds.getCart(currentUsername);

	cartList->clear();

	for(unsigned int i=0; i < cart.size(); i++) {
		QString cartItem = QString::fromStdString(cart[i]->getName());
		cartList->addItem(cartItem);
	}

	viewCartWindow->show();
}

void MainWindow::searchClicked()
{
	std::vector<std::string> terms;
	std::string line = searchBar->text().toStdString();
	std::stringstream ss(line);

	std::string term;

	while(ss >> term) {
		term = convToLower(term);
		terms.push_back(term);
	}

	if(andRadioButton->isChecked()) {
		hits = ds.search(terms, 0);
	}
	else if(orRadioButton->isChecked()) {
		hits = ds.search(terms, 1);
	}

	fillListWidget();

}

void MainWindow::fillListWidget() {
	productList->clear();

	for(unsigned int i=0; i < hits.size(); i++) {
		// convert price double to a string
		std::stringstream doubleConverter;
		doubleConverter << hits[i]->getPrice();
		std::string priceString = doubleConverter.str();

		doubleConverter.clear();
		doubleConverter.str("");

		doubleConverter << std::setprecision(2) << hits[i]->getAvgRating();
		std::string ratingString = doubleConverter.str();

		std::string tempString = hits[i]->getName() + "\tPrice: " + priceString + "     Rating: " + ratingString;
		QString newProduct = QString::fromStdString(tempString);
		productList->addItem(newProduct);
	}
}

void MainWindow::sortAlpha() 
{
	alphaComparator comp;
	mergeSort<Product*, alphaComparator>(hits, comp);
	fillListWidget();	
}

void MainWindow::sortRating() 
{
	ratingComparator comp;
	mergeSort<Product*, ratingComparator>(hits, comp);
	fillListWidget();
}

void MainWindow::addToCartClicked()
{	

	Product* prod = NULL;
	if(currentRow != -1) {
		prod = hits[currentRow];
	}

	if(prod != NULL) {
		std::string currentUsername = userDropdown->currentText().toStdString();
		ds.addToCart(currentUsername, prod);
	}
}

void MainWindow::changeCurrentRow(int rowIndex)
{
	currentRow = rowIndex;
}

void MainWindow::buyCart()
{
	ds.buyCart(userDropdown->currentText().toStdString());
	viewCart();
}

void MainWindow::removeProduct()
{
	if(cartList->currentRow() != -1) {
		ds.removeFromCart(userDropdown->currentText().toStdString(), cartList->currentRow());
		cartList->takeItem(cartList->currentRow());
	}
}

void MainWindow::closeCart()
{
	viewCartWindow->hide();
}

void MainWindow::updateReviews(int row)
{
	if(row != -1) {
		reviewList->clear();

		dateComparator dateCompare;
		mergeSort<Review*, dateComparator>(hits[row]->reviews, dateCompare);

		for(unsigned int i=0; i < hits[row]->reviews.size(); i++) {
			std::stringstream intConverter;
			intConverter << hits[row]->reviews[i]->rating;
			std::string ratingString = intConverter.str();
			std::string reviewString = ratingString + " | " + hits[row]->reviews[i]->date + " | " + hits[row]->reviews[i]->reviewText;
			QString qReview = QString::fromStdString(reviewString);
			reviewList->addItem(qReview); 
		}
	}
}

void MainWindow::addReviewClicked() 
{
	if(currentRow != -1) {
		addReviewWindow->show();
	}
}

void MainWindow::completeAddReview()
{
	Review* newReview = new Review;
	newReview->prodName = hits[currentRow]->getName();
	std::stringstream intConverter(ratingBox->text().toStdString());
	int intRating;
	intConverter >> intRating;
	newReview->rating = intRating;
	newReview->date = dateBox->text().toStdString();
	newReview->reviewText = reviewTextBox->text().toStdString();
	ds.addReview(newReview);

	addReviewWindow->hide();
	updateReviews(currentRow);
}

void MainWindow::quitApplication()
{
	string filename = "database.new";
	ofstream ofile(filename.c_str());
	ds.dump(ofile);
	ofile.close();
	close();
}
