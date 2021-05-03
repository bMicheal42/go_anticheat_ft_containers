#ifndef FT_BIDIRECTIONAL_ITERATOR_HPP
# define FT_BIDIRECTIONAL_ITERATOR_HPP

// ============================ STD-LIBS =======================================

# include <cstddef>   // size_t, ptrdiff_t ...

// =============================================================================

// ============================ NAMESPACE FT ===================================

namespace ft {

// ======================== BIDIRECTIONAL ITERATOR =============================

	template <class T, class P, class R, class Node>
	class ListBidirectionalIterator {
	public:

		// Typedef -------------------------------------------------------------

		typedef ptrdiff_t                       difference_type;
		typedef T                               value_type;
		typedef P                               pointer;
		typedef R                               reference;
		typedef std::bidirectional_iterator_tag iterator_category;

		// ---------------------------------------------------------------------

		// Constructor - Destructor --------------------------------------------

		ListBidirectionalIterator(Node* node = 0) : node_(node) {};

		ListBidirectionalIterator
		(
		 const ListBidirectionalIterator<T, T*, T&, Node> & x
		)
		: node_(x.node_) {};

		virtual ~ListBidirectionalIterator(){};

		// ---------------------------------------------------------------------

		// Operators -----------------------------------------------------------

		// '='
		ListBidirectionalIterator & operator=
		(
		 const ListBidirectionalIterator & x
		)
		{
			if (this == &x)
				return *this;
			node_ = x.node_;
			return *this;
		}

		// '=='
		bool                        operator==
		(
		 const ListBidirectionalIterator & x
		)
		{
			return node_ == x.node_;
		}

		// '!='
		bool                        operator!=
		(
		 const ListBidirectionalIterator & x
		)
		{
			return node_ != x.node_;
		}

		// '*'
		reference                   operator*() {
			return node_->data;
		}

		// '->'
		pointer                     operator->() {
			return &node_->data;
		}

		// '++iter'
		ListBidirectionalIterator   operator++() {
			node_ = node_->next;
			return (*this);
		}

		// 'iter++'
		ListBidirectionalIterator   operator++(int) {
			ListBidirectionalIterator tmp(*this);

			node_ = node_->next;
			return (tmp);
		}

		// '--iter'
		ListBidirectionalIterator   operator--() {
			node_ = node_->prev;
			return (*this);
		}

		// 'iter--'
		ListBidirectionalIterator   operator--(int) {
			ListBidirectionalIterator tmp(*this);

			node_ = node_->prev;
			return (tmp);
		}

		// ---------------------------------------------------------------------

		// Getters -------------------------------------------------------------

		Node* get_node() const {
			return node_;
		}

		// ---------------------------------------------------------------------

	private:
		Node* node_;
	};

// =============================================================================

};

// =============================================================================

#endif /* FT_BIDIRECTIONAL_ITERATOR_HPP */
