//
// Created by Gueren Drive on 3/24/21.
//

#include <iostream>
#include <utility>
#include <vector>
#include <set>
#include "../utils.hpp"

#define lib std
#define con multiset

template<class T>
class More {

public:
	More() {};
	More(const More & x) {(void)(x);}
	~More() {};

	More & operator=(const More & x) {(void)(x); return *this;}

	bool   operator()(const T & a, const T & b) const {
		return a > b;
	}
};

template <class T, class Compare = ft::Less<T> >
void print_multiset(lib::con<T, Compare> & multiset) {
	typename lib::con<T>::iterator it(multiset.begin());

	std::cout
	<<  "empty: " << multiset.empty()
	<< " size: "  << multiset.size()
	<< " multiset:\n";
	size_t i = 0;
	while (it != multiset.end()) {
		if (i != 0 && i % 32 == 0) {
			std::cout << "\n";
		}
		std::cout << *it << " ";
		++it;
		++i;
	}
	std::cout << std::endl;
}

namespace same_with_reverse_comp {


// Constructors ----------------------------------------------------------------

	void default_constructor_test() {
		std::cout << "default_constructor_test" << std::endl;
		More<int> more_;
		lib::con<int, More<int> > def(more_);
		print_multiset<int>(def);

	}

	void constructor_first_last_test() {
		std::cout << "constructor_first_last_test" << std::endl;
		std::vector<int> src;
		for (int i = 1000; i > 0; --i) {
			src.push_back(i);
		}
		More<int> more_;
		lib::con<int, More<int> > def(src.begin(), src.end(), more_);
		print_multiset(def);
	}

	void copy_constructor() {
		std::cout << "copy_constructor" << std::endl;
		std::vector<int> src;
		for (int i = 1000; i > 0; --i) {
			src.push_back(i);
		}
		More<int> more_;
		lib::con<int, More<int> > def(src.begin(), src.end(), more_);
		lib::con<int, More<int> > copy_def(def);
		print_multiset(copy_def);
	}

// -----------------------------------------------------------------------------

// Modifiers -------------------------------------------------------------------

	void insert_val_test() {
		std::cout << "insert_val_test" << std::endl;
		More<int> more_;
		lib::con<int, More<int> > def(more_);

		size_t j = 0;
		std::cout << "Inserting: \n";
		for (int i = 999; i >= 0; --i) {
			if (j != 0 && j % 32 == 0) {
				std::cout << "\n";
			}
			std::cout << *(def.insert(i)) << " " ;
			++j;
		}
		std::cout << std::endl;
		print_multiset<int>(def);
	}

	void insert_position_val_test() {
		std::cout << "insert_position_val_test" << std::endl;
		More<int> more_;
		lib::con<int, More<int> > def(more_);

		size_t j = 0;
		std::cout << "Inserting: \n";
		for (int i = 999; i >= 0; --i) {
			if (j != 0 && j % 32 == 0) {
				std::cout << "\n";
			}
			std::cout << *(def.insert(def.begin(), i)) << " ";
			++j;
		}
		print_multiset<int>(def);
	}

	void insert_first_last_test() {
		std::cout << "insert_first_last_test" << std::endl;
		std::vector<int> src;
		More<int> more_;
		lib::con<int, More<int> >    def(more_);
		for (int i = 1000; i > 0; --i) {
			src.push_back(i);
		}
		def.insert(src.begin(), src.end());
		def.insert(src.begin(), src.end());
		print_multiset(def);
	}

	void erase_position_test() {
		std::cout << "erase_position_test" << std::endl;
		std::vector<int> src;
		for (int i = 1000; i > 0; --i) {
			src.push_back(i);
		}
		More<int> more_;
		lib::con<int, More<int> >           def(src.begin(), src.end(), more_);
		lib::con<int, More<int> >::iterator it;

		def.erase(def.begin());

		it = def.begin();
		for (int i = 0; i < 10; ++i) {
			++it;
		}
		def.erase(it);

		it = def.end();
		for (int i = 0; i < 10; ++i) {
			--it;
		}
		def.erase(it);

		print_multiset(def);
	}

	void erase_val() {
		std::cout << "erase_val" << std::endl;
		More<int> more_;
		lib::con<int, More<int> >           def(more_);
		lib::con<int, More<int> >::iterator it;
		for (int i = 0; i < 10 ; ++i) {
			def.insert(def.end(), i);
			def.insert(def.end(), i);
		}

		def.erase(5);
		print_multiset(def);

		it = def.begin();
		for (int i = 0; i < 10; ++i) {
			def.insert(it, 6);
			it = def.begin();
		}
		def.erase(6);
		print_multiset(def);

		for (int i = 0; i < 10; ++i) {
			def.insert(99);
		}
		def.erase(99);
		print_multiset(def);
	}

	void erase_first_last() {
		std::cout << "erase_val" << std::endl;
		More<int> more_;
		lib::con<int, More<int> >           def(more_);
		lib::con<int, More<int> >::iterator it;
		lib::con<int, More<int> >::iterator it2;
		for (int i = 0; i < 10 ; ++i) {
			def.insert(def.end(), i);
			def.insert(def.end(), i);
		}

		def.erase(def.begin(), def.end());
		print_multiset(def);

		for (int i = 0; i < 30; ++i) {
			def.insert(i);
		}
		it = def.begin();
		for (int i = 0; i < 5; ++i) {
			++it;
		}
		it2 = def.end();
		for (int i = 0; i < 5; ++i) {
			--it2;
		}
		def.erase(it, it2);
		print_multiset(def);
	}

	void swap_test() {
		std::cout << "swap_test" << std::endl;
		More<int> more_;
		lib::con<int, More<int> >           def(more_);
		for (int i = 0; i < 10 ; ++i) {
			def.insert(def.end(), i);
			def.insert(def.end(), i);
		}
		lib::con<int, More<int> >           def2(more_);
		for (int i = 0; i < 10 ; ++i) {
			def2.insert(def2.end(), i + 100);
			def2.insert(def2.end(), i + 100);
		}

		def.swap(def2);
		print_multiset(def);
		print_multiset(def2);
	}

	void clear_test() {
		std::cout << "clear" << std::endl;
		More<int> more_;
		lib::con<int, More<int> >           def(more_);
		for (int i = 0; i < 10 ; ++i) {
			def.insert(def.end(), i);
			def.insert(def.end(), i);
		}

		def.clear();
		print_multiset(def);
	}

// -----------------------------------------------------------------------------

// Operations ------------------------------------------------------------------

	void find_test() {
		More<int> more_;
		lib::con<int, More<int> > def(more_);
		for (int i = 0; i < 10000 ; ++i) {
			def.insert(def.end(), i);
		}

		std::cout << *(def.find(400)) << std::endl;
		std::cout << *(def.find(6789)) << std::endl;
		std::cout << *(def.find(2399)) << std::endl;
		std::cout << *(def.find(9999)) << std::endl;
		std::cout << *(def.find(12)) << std::endl;
		std::cout << *(def.find(0)) << std::endl;
	}

	void count_test() {
		std::cout << "count_test" << std::endl;
		More<int> more_;
		lib::con<int, More<int> >           def(more_);
		for (int i = 0; i < 30 ; ++i) {
			if (i == 5) {
				for (int j = 0; j < i; ++j) {
					def.insert(def.end(), i);
				}
			} else if (i == 10) {
				for (int j = 0; j < i; ++j) {
					def.insert(def.end(), i);
				}
			} else if (i == 29){
				for (int j = 0; j < i; ++j) {
					def.insert(def.end(), i);
				}
			} else {
				def.insert(def.end(), i);
			}
		}

		std::cout << def.count(99) << std::endl;
		std::cout << def.count(5)  << std::endl;
		std::cout << def.count(10) << std::endl;
		std::cout << def.count(29) << std::endl;
	}

	void lower_bound_test() {
		std::cout << "lower_bound_test" << std::endl;
		More<int> more_;
		lib::con<int, More<int> >           def(more_);
		lib::con<int, More<int> >::iterator it;
		for (int i = 0; i < 30 ; ++i) {
			if (i == 5) {
				for (int j = 0; j < i; ++j) {
					def.insert(def.end(), i);
				}
			} else if (i == 10) {
				for (int j = 0; j < i; ++j) {
					def.insert(def.end(), i);
				}
			} else if (i == 29){
				for (int j = 0; j < i; ++j) {
					def.insert(def.end(), i);
				}
			} else {
				def.insert(def.end(), i);
			}
		}

		it = def.lower_bound(5);
		for (size_t i = 0; i < 5 ; ++i) {
			std::cout << *it << " ";
			++it;
		}
		std::cout << std::endl;

		it = def.lower_bound(29);
		for (size_t i = 0; i < 29; ++i) {
			std::cout << *it << " ";
			++it;
		}
		std::cout << std::endl;

	}

	void upper_bound_test() {
		std::cout << "upper_bound_test" << std::endl;
		More<int> more_;
		lib::con<int, More<int> >           def(more_);
		lib::con<int, More<int> >::iterator it;
		for (int i = 0; i < 30 ; ++i) {
			if (i == 5) {
				for (int j = 0; j < i; ++j) {
					def.insert(def.end(), i);
				}
			} else if (i == 10) {
				for (int j = 0; j < i; ++j) {
					def.insert(def.end(), i);
				}
			} else if (i == 29){
				for (int j = 0; j < i; ++j) {
					def.insert(def.end(), i);
				}
			} else {
				def.insert(def.end(), i);
			}
		}

		it = def.upper_bound(5);
		--it;
		for (size_t i = 0; i < 5; ++i) {
			std::cout << *it << " ";
			--it;
		}
		std::cout << std::endl;

		it = def.upper_bound(29);
		for (size_t i = 0; i < 29; ++i) {
			std::cout << *it << " ";
			--it;
		}
		std::cout << std::endl;
	}

	void equal_range_test() {
		std::cout << "equal_range_test" << std::endl;

		More<int> more_;
		lib::con<int, More<int> >           def(more_);
		lib::con<int, More<int> >::iterator it;
		lib::con<int, More<int> >::iterator it2;
		for (int i = 0; i < 30 ; ++i) {
			if (i == 5) {
				for (int j = 0; j < i; ++j) {
					def.insert(def.end(), i);
				}
			} else if (i == 10) {
				for (int j = 0; j < i; ++j) {
					def.insert(def.end(), i);
				}
			} else if (i == 29){
				for (int j = 0; j < i; ++j) {
					def.insert(def.end(), i);
				}
			} else {
				def.insert(def.end(), i);
			}
		}

		std::pair<
				lib::con<int, More<int> >::iterator,
				lib::con<int, More<int> >::iterator>        range(def.equal_range(5));

		it  = std::get<0>(range);
		it2 = std::get<1>(range);
		while (it != it2) {
			std::cout << *it << " ";
			++it;
		}
		std::cout << std::endl;

		range = def.equal_range(29);
		it  = std::get<0>(range);
		it2 = std::get<1>(range);
		while (it != it2) {
			std::cout << *it << " ";
			++it;
		}
		std::cout << std::endl;
	}

// -----------------------------------------------------------------------------
}

// Constructors ----------------------------------------------------------------

void default_constructor_test() {
	std::cout << "default_constructor_test" << std::endl;
	lib::con<int> def;
	print_multiset<int>(def);

}

void constructor_first_last_test() {
	std::cout << "constructor_first_last_test" << std::endl;
	std::vector<int> src;
	for (int i = 1000; i > 0; --i) {
		src.push_back(i);
	}
	lib::con<int> def(src.begin(), src.end());
	print_multiset(def);
}

void copy_constructor() {
	std::cout << "copy_constructor" << std::endl;
	std::vector<int> src;
	for (int i = 1000; i > 0; --i) {
		src.push_back(i);
	}
	lib::con<int> def(src.begin(), src.end());
	lib::con<int> copy_def(def);
	print_multiset(copy_def);
}

// -----------------------------------------------------------------------------

// Modifiers -------------------------------------------------------------------

void insert_val_test() {
	std::cout << "insert_val_test" << std::endl;
	lib::con<int> def;

	size_t j = 0;
	std::cout << "Inserting: \n";
	for (int i = 999; i >= 0; --i) {
		if (j != 0 && j % 32 == 0) {
			std::cout << "\n";
		}
		std::cout << *(def.insert(i)) << " " ;
		++j;
	}
	std::cout << std::endl;
	print_multiset<int>(def);
}

void insert_position_val_test() {
	std::cout << "insert_position_val_test" << std::endl;
	lib::con<int> def;

	size_t j = 0;
	std::cout << "Inserting: \n";
	for (int i = 999; i >= 0; --i) {
		if (j != 0 && j % 32 == 0) {
			std::cout << "\n";
		}
		std::cout << *(def.insert(def.begin(), i)) << " ";
		++j;
	}
	print_multiset<int>(def);
}

void insert_first_last_test() {
	std::cout << "insert_first_last_test" << std::endl;
	std::vector<int> src;
	lib::con<int>    def;
	for (int i = 1000; i > 0; --i) {
		src.push_back(i);
	}
	def.insert(src.begin(), src.end());
	def.insert(src.begin(), src.end());
	print_multiset(def);
}

void erase_position_test() {
	std::cout << "erase_position_test" << std::endl;
	std::vector<int> src;
	for (int i = 1000; i > 0; --i) {
		src.push_back(i);
	}
	lib::con<int>           def(src.begin(), src.end());
	lib::con<int>::iterator it;

	def.erase(def.begin());

	it = def.begin();
	for (int i = 0; i < 10; ++i) {
		++it;
	}
	def.erase(it);

	it = def.end();
	for (int i = 0; i < 10; ++i) {
		--it;
	}
	def.erase(it);

	print_multiset(def);
}

void erase_val() {
	std::cout << "erase_val" << std::endl;
	lib::con<int>           def;
	lib::con<int>::iterator it;
	for (int i = 0; i < 10 ; ++i) {
		def.insert(def.end(), i);
		def.insert(def.end(), i);
	}

	def.erase(5);
	print_multiset(def);

	it = def.begin();
	for (int i = 0; i < 10; ++i) {
		def.insert(it, 6);
		it = def.begin();
	}
	def.erase(6);
	print_multiset(def);

	for (int i = 0; i < 10; ++i) {
		def.insert(99);
	}
	def.erase(99);
	print_multiset(def);
}

void erase_first_last() {
	std::cout << "erase_val" << std::endl;
	lib::con<int>           def;
	lib::con<int>::iterator it;
	lib::con<int>::iterator it2;
	for (int i = 0; i < 10 ; ++i) {
		def.insert(def.end(), i);
		def.insert(def.end(), i);
	}

	def.erase(def.begin(), def.end());
	print_multiset(def);

	for (int i = 0; i < 30; ++i) {
		def.insert(i);
	}
	it = def.begin();
	for (int i = 0; i < 5; ++i) {
		++it;
	}
	it2 = def.end();
	for (int i = 0; i < 5; ++i) {
		--it2;
	}
	def.erase(it, it2);
	print_multiset(def);
}

void swap_test() {
	std::cout << "swap_test" << std::endl;
	lib::con<int>           def;
	for (int i = 0; i < 10 ; ++i) {
		def.insert(def.end(), i);
		def.insert(def.end(), i);
	}
	lib::con<int>           def2;
	for (int i = 0; i < 10 ; ++i) {
		def2.insert(def2.end(), i + 100);
		def2.insert(def2.end(), i + 100);
	}

	def.swap(def2);
	print_multiset(def);
	print_multiset(def2);
}

void clear_test() {
	std::cout << "clear" << std::endl;
	lib::con<int>           def;
	for (int i = 0; i < 10 ; ++i) {
		def.insert(def.end(), i);
		def.insert(def.end(), i);
	}

	def.clear();
	print_multiset(def);
}

// -----------------------------------------------------------------------------

// Operations ------------------------------------------------------------------

void find_test() {
	lib::con<int> empty;
	lib::con<int> def;
	for (int i = 0; i < 10000 ; ++i) {
		def.insert(def.end(), i);
	}

	std::cout << *(def.find(400)) << std::endl;
	std::cout << *(def.find(6789)) << std::endl;
	std::cout << *(def.find(2399)) << std::endl;
	std::cout << *(def.find(9999)) << std::endl;
	std::cout << *(def.find(12)) << std::endl;
	std::cout << *(def.find(0)) << std::endl;
	std::cout << (empty.find(9) == empty.end()) << std::endl;
}

void count_test() {
	std::cout << "count_test" << std::endl;
	lib::con<int>           empty;
	lib::con<int>           def;
	for (int i = 0; i < 30 ; ++i) {
		if (i == 5) {
			for (int j = 0; j < i; ++j) {
				def.insert(def.end(), i);
			}
		} else if (i == 10) {
			for (int j = 0; j < i; ++j) {
				def.insert(def.end(), i);
			}
		} else if (i == 29){
			for (int j = 0; j < i; ++j) {
				def.insert(def.end(), i);
			}
		} else {
			def.insert(def.end(), i);
		}
	}

	std::cout << def.count(99) << std::endl;
	std::cout << def.count(5)  << std::endl;
	std::cout << def.count(10) << std::endl;
	std::cout << def.count(29) << std::endl;
	std::cout << def.count(1000) << std::endl;
	std::cout << empty.count(1000) << std::endl;
}

void lower_bound_test() {
	std::cout << "lower_bound_test" << std::endl;
	lib::con<int>           empty;
	lib::con<int>           def;
	lib::con<int>::iterator it;
	for (int i = 0; i < 30 ; ++i) {
		if (i == 5) {
			for (int j = 0; j < i; ++j) {
				def.insert(def.end(), i);
			}
		} else if (i == 10) {
			for (int j = 0; j < i; ++j) {
				def.insert(def.end(), i);
			}
		} else if (i == 29){
			for (int j = 0; j < i; ++j) {
				def.insert(def.end(), i);
			}
		} else {
			def.insert(def.end(), i);
		}
	}

	it = def.lower_bound(5);
	for (size_t i = 0; i < 5 ; ++i) {
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;

	it = def.lower_bound(29);
	for (size_t i = 0; i < 29; ++i) {
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;
	it = def.lower_bound(12234);
	std::cout << (it == def.end()) << std::endl;
	it = empty.lower_bound(12234);
	std::cout << (it == def.end()) << std::endl;
}

void upper_bound_test() {
	std::cout << "upper_bound_test" << std::endl;
	lib::con<int>           empty;
	lib::con<int>           def;
	lib::con<int>::iterator it;
	for (int i = 0; i < 30 ; ++i) {
		if (i == 5) {
			for (int j = 0; j < i; ++j) {
				def.insert(def.end(), i);
			}
		} else if (i == 10) {
			for (int j = 0; j < i; ++j) {
				def.insert(def.end(), i);
			}
		} else if (i == 29){
			for (int j = 0; j < i; ++j) {
				def.insert(def.end(), i);
			}
		} else {
			def.insert(def.end(), i);
		}
	}

	it = def.upper_bound(5);
	--it;
	for (size_t i = 0; i < 5; ++i) {
		std::cout << *it << " ";
		--it;
	}
	std::cout << std::endl;

	it = def.upper_bound(29);
	--it;
	for (size_t i = 0; i < 29; ++i) {
		std::cout << *it << " ";
		--it;
	}
	std::cout << std::endl;
	it = def.lower_bound(12234);
	std::cout << (it == def.end()) << std::endl;
	it = empty.lower_bound(12234);
	std::cout << (it == def.end()) << std::endl;
}

void equal_range_test() {
	std::cout << "equal_range_test" << std::endl;

	lib::con<int>           def;
	lib::con<int>::iterator it;
	lib::con<int>::iterator it2;
	for (int i = 0; i < 30 ; ++i) {
		if (i == 5) {
			for (int j = 0; j < i; ++j) {
				def.insert(def.end(), i);
			}
		} else if (i == 10) {
			for (int j = 0; j < i; ++j) {
				def.insert(def.end(), i);
			}
		} else if (i == 29){
			for (int j = 0; j < i; ++j) {
				def.insert(def.end(), i);
			}
		} else {
			def.insert(def.end(), i);
		}
	}

	std::pair<
	        lib::con<int>::iterator,
	        lib::con<int>::iterator>        range(def.equal_range(5));

	it  = std::get<0>(range);
	it2 = std::get<1>(range);
	while (it != it2) {
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;

	range = def.equal_range(29);
	it  = std::get<0>(range);
	it2 = std::get<1>(range);
	while (it != it2) {
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;
}

// -----------------------------------------------------------------------------

void reverse_iterator_test() {
	std::cout << "reverse_iterator_test" << std::endl;
	lib::con<int>           def;
	lib::con<int>::reverse_iterator rit;
	for (int i = 0; i < 30 ; ++i) {
		if (i == 5) {
			for (int j = 0; j < i; ++j) {
				def.insert(def.end(), i);
			}
		} else if (i == 10) {
			for (int j = 0; j < i; ++j) {
				def.insert(def.end(), i);
			}
		} else if (i == 29){
			for (int j = 0; j < i; ++j) {
				def.insert(def.end(), i);
			}
		} else {
			def.insert(def.end(), i);
		}
	}

	rit = def.rbegin();
	while (rit != def.rend()) {
		std::cout << *rit << " ";
		++rit;
	}
	std::cout << std::endl;

}

int main() {
	// Constructors
	default_constructor_test();
	constructor_first_last_test();
	copy_constructor();
	// ------------

	// Modifiers
	insert_val_test();
	insert_position_val_test();
	insert_first_last_test();
	erase_position_test();
	erase_val();
	erase_first_last();
	swap_test();
	clear_test();
	// ------------

	// Operations
	find_test();
	count_test();
	lower_bound_test();
	upper_bound_test();
	equal_range_test();
	// ------------


	// Constructors
	same_with_reverse_comp::default_constructor_test();
	same_with_reverse_comp::constructor_first_last_test();
	same_with_reverse_comp::copy_constructor();
	// ------------

	// Modifiers
	same_with_reverse_comp::insert_val_test();
	same_with_reverse_comp::insert_position_val_test();
	same_with_reverse_comp::insert_first_last_test();
	same_with_reverse_comp::erase_position_test();
	same_with_reverse_comp::erase_val();
	same_with_reverse_comp::erase_first_last();
	same_with_reverse_comp::swap_test();
	same_with_reverse_comp::clear_test();
	// ------------

	// Operations
	same_with_reverse_comp::find_test();
	same_with_reverse_comp::count_test();
	same_with_reverse_comp::lower_bound_test();
	same_with_reverse_comp::upper_bound_test();
	same_with_reverse_comp::equal_range_test();
	// ------------
	reverse_iterator_test();
	return 0;
}
