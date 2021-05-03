//
// Created by Gueren Drive on 3/23/21.
//

#ifndef CONTAINERS_CPP_FT_MULTISET_BIDIR_ITERATOR_HPP
#define CONTAINERS_CPP_FT_MULTISET_BIDIR_ITERATOR_HPP

// ============================ NAMESPACE FT ===================================

namespace ft {

// ======================== BIDIRECTIONAL ITERATOR =============================

	template <class Iterator>
	class MultisetBidirIterator {
	public:

		// Typedef -------------------------------------------------------------

		typedef Iterator                             iterator_type;
		typedef typename Iterator::value_type        value_type;
		typedef typename Iterator::pointer           pointer;
		typedef typename Iterator::reference         reference;
		typedef typename Iterator::difference_type   difference_type;
		typedef std::bidirectional_iterator_tag      iterator_category;

		// ---------------------------------------------------------------------

		// Constructor - Destructor --------------------------------------------

		MultisetBidirIterator()
		: it_()
		{}

		explicit MultisetBidirIterator(iterator_type it)
		: it_(it)
		{}

		template <class Iter>
		MultisetBidirIterator(const MultisetBidirIterator<Iter> & it)
		: it_(it.base())
		{}

		virtual ~MultisetBidirIterator()
		{}

		// ---------------------------------------------------------------------

		// Getters -------------------------------------------------------------

		iterator_type base() const {
			return it_;
		}

		// ---------------------------------------------------------------------

		// Operators -----------------------------------------------------------

		// '='
		MultisetBidirIterator & operator=(MultisetBidirIterator const & x) {
			if (this == &x) {
				return *this;
			}
			this->it_ = x.it_;
			return *this;
		}

		// '=='
		bool                    operator==
		(
		MultisetBidirIterator const & x
		) const
		{
			return this->it_ == x.it_;
		}

		// '!='
		bool                    operator!=
		(
		MultisetBidirIterator const & x
		) const
		{
			return this->it_ != x.it_;
		}

		// '*'
		reference               operator*() {
			return *this->it_;
		}

		// '->'
		pointer                 operator->() {
			return this->it_.get_pointer();
		}

		// '++iter'
		MultisetBidirIterator   operator++() {
			++this->it_;
			return (*this);
		}

		// 'iter++'
		MultisetBidirIterator   operator++(int) {
			MultisetBidirIterator tmp(*this);
			++this->it_;
			return (tmp);
		}

		// '--iter'
		MultisetBidirIterator   operator--() {
			--this->it_;
			return (*this);
		}

		// 'iter--'
		MultisetBidirIterator   operator--(int) {
			MultisetBidirIterator tmp(*this);
			--this->it_;
			return (tmp);
		}

		// ---------------------------------------------------------------------

	private:
		iterator_type it_;
	};
}

// ============================ END NAMESPACE FT ===============================

#endif //CONTAINERS_CPP_FT_MULTISET_BIDIR_ITERATOR_HPP
