//
// Created by Gueren Drive on 3/30/21.
//

#ifndef CONTAINERS_CPP_FT_Stack_HPP
#define CONTAINERS_CPP_FT_Stack_HPP

// ============================ STD-LIBS =======================================

# include <cstddef> // size_t, ptrdiff_t ...

// =============================================================================

// ========================== OTHER INCLUDES ===================================

# include "../ft_list/ft_list.hpp"

// =============================================================================

namespace ft {

	template <class T, class Container = List<T> >
	class Stack {
	public:

		// Typedef -------------------------------------------------------------

		typedef T         value_type;
		typedef Container container_type;
		typedef size_t    size_type;

		// ---------------------------------------------------------------------

		// Constructor - Destructor --------------------------------------------

		explicit Stack(const container_type& ctnr = container_type())
		: ctnr_(ctnr)
		{}

		Stack(const Stack& x)
		: ctnr_(x.ctnr_)
		{}

		~Stack() {}

		Stack& operator=(const Stack& x) {
			if (this == &x) {
				return *this;
			}
			ctnr_ = x.ctnr_;
			return *this;
		}

		// ---------------------------------------------------------------------

		// Member functions ----------------------------------------------------

		bool        empty() const {
			return ctnr_.empty();
		}

		size_type   size() const {
			return ctnr_.size();
		}

		value_type& top() {
			return ctnr_.back();
		}

		value_type& top() const {
			return ctnr_.back();
		}

		void        push(const value_type& val) {
			ctnr_.push_back(val);
		}

		void        pop() {
			ctnr_.pop_back();
		}

		// ---------------------------------------------------------------------

	private:
		container_type ctnr_;
	};

	template <class T, class Container>
	bool operator==
	(
	 const Stack<T, Container>& lhs, const Stack<T, Container>& rhs
	)
	{
		return lhs._ctnr == rhs._ctnr;
	}

	template <class T, class Container>
	bool operator!=
	(
	 const Stack<T, Container>& lhs, const Stack<T, Container>& rhs
	)
	{
		return lhs._ctnr != rhs._ctnr;
	}

	template <class T, class Container>
	bool operator<
	(
	 const Stack<T, Container>& lhs, const Stack<T, Container>& rhs
	)
	{
		return lhs._ctnr < rhs._ctnr;
	}

	template <class T, class Container>
	bool operator<=
	(
	 const Stack<T, Container>& lhs, const Stack<T, Container>& rhs
	)
	{
		return lhs._ctnr <= rhs._ctnr;
	}

	template <class T, class Container>
	bool operator>
	(
	 const Stack<T, Container>& lhs, const Stack<T, Container>& rhs
	)
	{
		return lhs._ctnr > rhs._ctnr;
	}

	template <class T, class Container>
	bool operator>=
	(
	 const Stack<T, Container>& lhs, const Stack<T, Container>& rhs
	)
	{
		return lhs._ctnr >= rhs._ctnr;
	}

}

#endif //CONTAINERS_CPP_FT_Stack_HPP
