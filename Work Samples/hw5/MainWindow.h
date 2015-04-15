#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QListWidget>
#include <QComboBox>
#include <QLabel>
#include "mystore.h"
#include <vector>
#include <sstream>
#include <algorithm>

struct alphaComparator {
	bool operator()(Product* lhs, Product* rhs) {
		return lhs->getName() < rhs->getName();
	}
};

struct ratingComparator {
	bool operator()(Product* lhs, Product* rhs) {
		return lhs->getAvgRating() > rhs->getAvgRating();
	}
};

struct dateComparator {
	bool operator()(Review* lhsR, Review* rhsR) {
		std::string lhs = lhsR->date;
		std::string rhs = rhsR->date;


		return lhs > rhs;
	}
};

class MainWindow : public QWidget
{
	Q_OBJECT

	public:
		MainWindow(MyStore& ds_);
		~MainWindow();

	private slots:
	// add slots later
	void viewCart();
	void searchClicked();
	void sortAlpha();
	void sortRating();
	void addToCartClicked();
	void changeCurrentRow(int);
	void buyCart();
	void removeProduct();
	void closeCart();
	void updateReviews(int);
	void addReviewClicked();
	void completeAddReview();
	void quitApplication();

	private:

	MyStore ds;

	QVBoxLayout* overallLayout;

	// Search bar
	QHBoxLayout* searchLayout;
	QLineEdit* searchBar;
	QPushButton* searchButton;

	// Radio buttons for AND and OR
	QHBoxLayout* radioLayout;
	QRadioButton* andRadioButton;
	QRadioButton* orRadioButton;

	// Sorting buttons
	QHBoxLayout* sortingLayout;
	QLabel* sortLabel;
	QPushButton* alphabeticalButton;
	QPushButton* ratingButton;

	// Product list and user/cart related components (middle of layout)
	QHBoxLayout* middleLayout;
	QVBoxLayout* userCartLayout; // use for dropdown and cart buttons
	QListWidget* productList;
	QComboBox* userDropdown;
	QPushButton* addCartButton;
	QPushButton* viewCartButton;

	// Reviews list
	QListWidget* reviewList;
	QPushButton* addReviewButton;

	// View cart window
	QWidget* viewCartWindow;
	QHBoxLayout* viewCartLayout;
	QListWidget* cartList;
	QVBoxLayout* buyRemoveLayout;
	QPushButton* buyCartButton;
	QPushButton* removeProductButton;
	QPushButton* closeCartButton;

	// Add review window
	QWidget* addReviewWindow;
	QVBoxLayout* addReviewLayout;
	QLabel* ratingLabel;
	QLineEdit* ratingBox;
	QLabel* dateLabel;
	QLineEdit* dateBox;
	QLabel* reviewTextLabel;
	QLineEdit* reviewTextBox;
	QPushButton* completeAddReviewButton;

	// Quit button
	QPushButton* quitButton;

	// hits
	std::vector<Product*> hits;

	// variable to hold selected row
	int currentRow;

	void fillListWidget();

	// sorting function
};	

#endif