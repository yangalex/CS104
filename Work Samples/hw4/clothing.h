#include "product.h"
#include "util.h"

class Clothing : public Product {
	public:
		Clothing(const std::string name, double price, int qty, const std::string size, const std::string brand);
		~Clothing();
		std::set<std::string> keywords() const;

		std::string displayString() const;

		void dump(std::ostream& os) const;

		// Accessors
		std::string getSize() const;
		std::string getBrand() const;

	private:
		std::string size_;
		std::string brand_;	
};