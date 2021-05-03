#ifndef FT_QUEUE_HPP
# define FT_QUEUE_HPP

// ============================ STD-LIBS =======================================

# include <cstddef> // size_t, ptrdiff_t ...

// =============================================================================

// ========================== OTHER INCLUDES ===================================

# include "../ft_list/ft_list.hpp"

// =============================================================================


// ============================ NAMESPACE FT ===================================

namespace ft {

// =============================== QUEUE =======================================

	// template <class T, class Container = Vector<T> >
	template <class T, class Container = List<T> >
	class Queue {
	public:

		// Typedef -------------------------------------------------------------

		typedef T         value_type;
		typedef Container container_type;
		typedef size_t    size_type;

		// ---------------------------------------------------------------------

		// Constructor - Destructor --------------------------------------------

		explicit Queue(const container_type & ctnr = container_type())
		: c_(ctnr)
		{}

		Queue(const Queue& x)
		: c_(x.c_)
		{}

		~Queue() {}

		Queue& operator=(const Queue& x) {
			if (this == &x) {
				return *this;
			}
			c_ = x.c_;
			return *this;
		}

		// ---------------------------------------------------------------------

		// Member functions ----------------------------------------------------

		bool               empty() const {

			return this->c_.empty();
		}

		size_type          size() const {

			return this->c_.size();
		}

		value_type &       front() {

			return this->c_.front();
		}

		const value_type & front() const {

			return this->c_.front();
		}

		value_type &       back() {

			return this->c_.back();
		}

		const value_type & back() const {

			return this->c_.back();
		}

		void               push (const value_type & val) {

			return this->c_.push_back(val);
		}

		void               pop() {

			return this->c_.pop_front();
		}

		// ---------------------------------------------------------------------

		// Getters -------------------------------------------------------------

		container_type get_container() const {

			return this->c_;
		}

		// ---------------------------------------------------------------------

	private:

		container_type c_;
	};

// =============================================================================

// Relational operators ========================================================

template <class T, class Container>
bool operator==(const Queue<T,Container>& lhs, const Queue<T,Container>& rhs) {

	return lhs.get_container() == rhs.get_container();
}

template <class T, class Container>
bool operator!=(const Queue<T,Container>& lhs, const Queue<T,Container>& rhs) {

	return lhs.get_container() != rhs.get_container();
}

template <class T, class Container>
bool operator<(const Queue<T,Container>& lhs, const Queue<T,Container>& rhs) {

	return lhs.get_container() < rhs.get_container();
}

template <class T, class Container>
bool operator<=(const Queue<T,Container>& lhs, const Queue<T,Container>& rhs) {

	return lhs.get_container() <= rhs.get_container();
}

template <class T, class Container>
bool operator>(const Queue<T,Container>& lhs, const Queue<T,Container>& rhs) {

	return lhs.get_container() > rhs.get_container();
}

template <class T, class Container>
bool operator>=(const Queue<T,Container>& lhs, const Queue<T,Container>& rhs) {

	return lhs.get_container() >= rhs.get_container();
}

// =============================================================================

}

// ============================ END NAMESPACE FT ===============================

#endif /* FT_VECTOR_HPP */
