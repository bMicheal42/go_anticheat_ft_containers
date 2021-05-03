#ifndef TEST_HPP
# define TEST_HPP

class Test {
public:
	Test() : some_(0) {
		// std::cout << "Test created" << std::endl;
		this->str_ = (char*)malloc(10);
	}

	Test(int s) : some_(s) {
		// std::cout << "Test " << this->some_ << " created" << std::endl;
		this->str_ = (char*)malloc(10);
	}

	Test(Test const & x) : some_(x.some_) {
		// std::cout << "Copy Test " << this->some_ << " created" << std::endl;
		this->str_ = (char*)malloc(10);
	}

	~Test() {
		if (this->str_ != 0)
			free(this->str_);
		this->some_ = 0;
		this->str_  = 0;
		// std::cout << "Test deleted" << std::endl;
	}

	Test &operator=(Test const & x) {
		// std::cout << "Test operator =" << std::endl;
		if (this == &x)
			return (*this);
		this->str_ = (char*)malloc(10);
		this->some_ = x.some_;
		return (*this);
	}

	int   some_;
	char* str_;

};

#endif
