#include "MainWindow.h"
#include <iomanip>
#include <sstream>
#include "util.h"
#include "msort.h"
#include <fstream>
#include <QMessageBox>
#include <math.h>
#include <string>
#include "SkipList.h"

int hashFunction(std::string password);

MainWindow::MainWindow(MyStore* ds_) 
{
	overallLayout = new QVBoxLayout;

	ds = ds_;

	currentRow = -1;

	// Setup Login window
	LoginWindow = new QWidget;
	LoginWindow->setMinimumSize(QSize(300, 200));
	mainLoginLayout = new QVBoxLayout;
	userName = new QLineEdit;
	password = new QLineEdit;
	mainLoginLayout->addWidget(userName);
	mainLoginLayout->addWidget(password);
	loginButtonLayout = new QHBoxLayout;
	loginButton = new QPushButton("Login");
	loginQuitButton = new QPushButton("Quit");
	newUserButton = new QPushButton("New User");
	loginButtonLayout->addWidget(loginButton);
	loginButtonLayout->addWidget(loginQuitButton);
	loginButtonLayout->addWidget(newUserButton);
	mainLoginLayout->addLayout(loginButtonLayout);
	LoginWindow->setLayout(mainLoginLayout);

	LoginWindow->show();
	
	// Setup user info window
	UserInfoWindow = new QWidget;
	UserInfoWindow->setMinimumSize(QSize(300, 100));
	userInfoLayout = new QVBoxLayout;
	userNameLabel = new QLabel();	
	ageLabel = new QLabel("Age: ");
	creditLabel = new QLabel("Credit Amount: ");
	newUserAge = new QLineEdit();
	newUserCredit = new QLineEdit();
	completeNewUserButton = new QPushButton("Add User");
	userInfoLayout->addWidget(userNameLabel);
	userInfoLayout->addWidget(ageLabel);
	userInfoLayout->addWidget(newUserAge);
	userInfoLayout->addWidget(creditLabel);
	userInfoLayout->addWidget(newUserCredit);
	userInfoLayout->addWidget(completeNewUserButton);
	UserInfoWindow->setLayout(userInfoLayout);
	
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
	mainUserLabel = new QLabel(QString().fromStdString(this->mainUser));
	addCartButton = new QPushButton("Add To Cart");
	viewCartButton = new QPushButton("View Cart");
	userCartLayout->addWidget(mainUserLabel);
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

	updateUserDropdown();



	// Slots and signals
	connect(loginButton, SIGNAL(clicked()), this, SLOT(checkLogin()));
	connect(newUserButton, SIGNAL(clicked()), this, SLOT(addUser()));
	connect(completeNewUserButton, SIGNAL(clicked()), this, SLOT(completeAddUser()));
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
	connect(loginQuitButton, SIGNAL(clicked()), this, SLOT(quitApplication()));

	setLayout(overallLayout);
}

MainWindow::~MainWindow()
{
	delete searchBar;
	delete searchButton;
	delete searchLayout;
	delete orRadioButton;
	delete andRadioButton;
	delete radioLayout;
	delete ratingButton;
	delete alphabeticalButton;
	delete sortLabel;
	delete sortingLayout;
	delete viewCartButton;
	delete addCartButton;
	delete userDropdown;
	delete productList;
	delete userCartLayout;
	delete middleLayout;
	delete addReviewButton;
	delete reviewList;
	delete closeCartButton;
	delete removeProductButton;
	delete buyCartButton;
	delete buyRemoveLayout;
	delete cartList;
	delete viewCartLayout;
	delete viewCartWindow;
	delete completeAddReviewButton;
	delete reviewTextBox;
	delete reviewTextLabel;
	delete dateBox;
	delete dateLabel;
	delete ratingBox;
	delete ratingLabel;
	delete addReviewLayout;
	delete addReviewWindow;
	delete quitButton;
	delete overallLayout;
	delete ds;
}

// Slots

void MainWindow::checkLogin()
{
	// get users list
	SkipList<std::string, User*> users = ds->getUsers();
	std::string userNameText = userName->text().toStdString();
	std::string passwordText = password->text().toStdString();

	bool userFound = false;
	SkipList<std::string, User*>::iterator it;
	for(it = users.begin(); it != users.end(); ++it) {
		if(it->first == userNameText) {
			userFound = true;
		}
	}

	// Implement login authentication
	if(userFound) {
		// check if password matches
		int correctPassword = users[userNameText]->getPassword();
		int passwordHash = hashFunction(passwordText);
		if(passwordHash == correctPassword) {
			this->mainUser = userNameText;
			mainUserLabel->setText(QString().fromStdString(mainUser));
			LoginWindow->close();
			this->show();	
		}
		else {
			QMessageBox wrongPasswordMsg;
			wrongPasswordMsg.setText("Wrong username or password");
			wrongPasswordMsg.exec();
		}
	}
	else {
		QMessageBox invalidLoginMsg;
		invalidLoginMsg.setText("Wrong username or password");
		invalidLoginMsg.exec();
	}
}

void MainWindow::addUser()
{
	std::string passwordText = password->text().toStdString();
	std::string userNameText = userName->text().toStdString();
	// Get a copy of the user list
	SkipList<std::string, User*> users = ds->getUsers();
	// Check if user already exists
	if(users.find(userNameText) != users.end()) {
		QMessageBox msgBox;
		msgBox.setText("Username already exists");
		msgBox.exec();
		return;
	}
	
	// Check if password is in the right format
	for(unsigned int i=0; i < passwordText.length(); i++) {
		if(std::isspace(passwordText[i])) {
			QMessageBox msgBox;
			msgBox.setText("Passwords cannot contain space");
			msgBox.exec();
			return;
		}
	}	

	if(passwordText.length() > 8) {
		QMessageBox msgBox;
		msgBox.setText("Password cannot be longer than 8 characters");
		msgBox.exec();
		return;
	}
	
	// Open new user info window
	std::string userLabelText = "Username: " + userNameText;
	userNameLabel->setText(QString::fromStdString(userLabelText));
	UserInfoWindow->show();	
}

void MainWindow::completeAddUser()
{
	stringstream ss;

	ss << newUserAge->text().toStdString();
	int userAge;
	ss >> userAge;	

	ss.clear();
	ss.str("");

	ss << newUserCredit->text().toStdString();
	double userCredit;
   	ss >> userCredit;

	int newPassword = hashFunction(password->text().toStdString());
	std::string userNameText = userName->text().toStdString();	

	User* newUser = new User(userNameText, userAge, userCredit, 0, newPassword);
	
	ds->addUser(newUser);
	updateUserDropdown();	
	UserInfoWindow->close();
}

void MainWindow::viewCart() 
{
	std::string currentUsername = mainUser;
	std::vector<Product*> cart = ds->getCart(currentUsername);

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
		hits = ds->search(terms, 0);
	}
	else if(orRadioButton->isChecked()) {
		hits = ds->search(terms, 1);
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
		std::string currentUsername = mainUser;
		ds->addToCart(currentUsername, prod);
	}
}

void MainWindow::changeCurrentRow(int rowIndex)
{
	currentRow = rowIndex;
}

void MainWindow::buyCart()
{
	ds->buyCart(mainUser);
	viewCart();
}

void MainWindow::removeProduct()
{
	if(cartList->currentRow() != -1) {
		ds->removeFromCart(mainUser, cartList->currentRow());
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
			std::string reviewString = ratingString + " | " + hits[row]->reviews[i]->username + " | " + hits[row]->reviews[i]->date + " | " + hits[row]->reviews[i]->reviewText;
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
	std::string reviewUser = mainUser;
	newReview->rating = intRating;
	newReview->username = reviewUser;
	newReview->date = dateBox->text().toStdString();
	newReview->reviewText = reviewTextBox->text().toStdString();
	ds->addReview(newReview);

	addReviewWindow->hide();
	updateReviews(currentRow);
}

void MainWindow::quitApplication()
{
	string filename = "database.new";
	ofstream ofile(filename.c_str());
	ds->dump(ofile);
	ofile.close();
	LoginWindow->close();
	UserInfoWindow->close();
	close();
}

int hashFunction(std::string password)
{
	long long newPassword = 0;
	for(unsigned int i =0; i < password.length(); i++) {
		long long power = pow(128, i);
		newPassword += static_cast<int>(password.at(password.length()-1-i)) * power;	
	}	

	unsigned int digits[4];

	digits[3] = newPassword % 65521;
   	digits[2] = (newPassword/65521) % 65521;
	digits[1] = (newPassword/65521/65521) % 65521;
	digits[0] = (newPassword/65521/65521/65521) % 65521;
	
	return (45912*digits[0] + 35511*digits[1] + 65169*digits[2] + 4625*digits[3]) % 65521;
}

void MainWindow::updateUserDropdown() 
{
	userDropdown->clear();

	// Add usernames to User dropdown box
	SkipList<std::string, User*> userList = ds->getUsers();
	SkipList<std::string, User*>::iterator it;
	for(it = userList.begin(); it != userList.end(); ++it) {
		userDropdown->addItem(QString::fromStdString(it->first));
	}
}
