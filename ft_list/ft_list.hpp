#ifndef FT_LIST_HPP
# define FT_LIST_HPP

// ============================ STD-LIBS =======================================

# include <cstddef>   // size_t, ptrdiff_t ...
# include <memory>    // allocator

// =============================================================================

// ========================== OTHER INCLUDES ===================================

# include "ft_list_bidirectional_iterator.hpp"
# include "../ft_reverse_iterator.hpp"
# include "../utils.hpp"

// =============================================================================

// ============================ NAMESPACE FT ===================================

namespace ft {

// =============================== LIST ========================================

	template < class T, class Alloc = std::allocator<T> >
	class List {

	private:

		// ======================= Node ========================================

		struct Node {
			T     data;
			Node* next;
			Node* prev;
			};

			// -----------------------------------------------------------------

		// =====================================================================

	public:

		// Typedef -------------------------------------------------------------

		typedef T                                               value_type;
		typedef Alloc                                           allocator_type;
		typedef typename allocator_type::reference              reference;
		typedef typename allocator_type::const_reference        const_reference;
		typedef typename allocator_type::pointer                pointer;
		typedef typename allocator_type::const_pointer          const_pointer;

		typedef ft::ListBidirectionalIterator<T, T*, T&, Node>  iterator;

		typedef ft::ListBidirectionalIterator<T, const T*, const T&, Node>
		                                                       const_iterator;

		 typedef ft::ReverseIterator<iterator>                 reverse_iterator;
		 typedef ft::ReverseIterator<const_iterator>     const_reverse_iterator;

		 typedef typename
		 ft::ListBidirectionalIterator<T, T*, T&, Node>::difference_type
		                                                        difference_type;

		typedef size_t                                          size_type;


		// ---------------------------------------------------------------------

		// Constructor - Destructor --------------------------------------------

		explicit List(const allocator_type& alloc = allocator_type())
		: size_(0), alloc_(alloc)
		{
			end_node_ = allocate_node();
		}

		explicit List
		(
		 size_type n,
		 const value_type& val = value_type(),
		 const allocator_type& alloc = allocator_type()
		)
		: size_(0), alloc_(alloc)
		{
			end_node_ = allocate_node();
			for (size_type i = 0; i < n; ++i) {
				this->push_back(val);
			}
		}

		template <class InputIterator>
		List
		(
		 InputIterator first,
		 InputIterator last,
		 const allocator_type& alloc = allocator_type(),
		 typename enable_if
		 < !std::numeric_limits<InputIterator>::is_specialized >::type* = 0
		) : size_(0), alloc_(alloc)
		{
			end_node_ = allocate_node();
			while (first != last) {
				this->push_back(*first);
				++first;
			}
		}

		List (const List & x)
		: size_(0), alloc_(x.alloc_)
		{
			end_node_ = allocate_node();
			for (const_iterator it(x.begin()); it != x.end(); ++it) {
				this->push_back(*it);
			}
		}

		virtual ~List() {
			while (this->size_ > 0) {
				this->pop_back();
			}
			deallocate_node(end_node_);
		}

		// ---------------------------------------------------------------------

		// Iterators -----------------------------------------------------------

		iterator               begin() {
			return iterator(end_node_->next);
		}

		const_iterator         begin() const {
			return const_iterator(end_node_->next);
		}

		iterator               end() {
			return iterator(end_node_);
		}

		const_iterator         end() const {
			return const_iterator(end_node_);
		}

		reverse_iterator       rbegin() {
			if (this->size() == 0) {
				return reverse_iterator(this->end());
			}
			return reverse_iterator(--(this->end()));
		}

		const_reverse_iterator rbegin() const {
			if (this->size() == 0) {
				return reverse_iterator(this->end());
			}
			return reverse_iterator(--(this->end()));
		}

		reverse_iterator       rend() {
			if (this->size() == 0) {
				return reverse_iterator(this->begin());
			}
			return reverse_iterator(--(this->begin()));
		}

		const_reverse_iterator rend() const {
			if (this->size() == 0) {
				return reverse_iterator(this->begin());
			}
			return reverse_iterator(--(this->begin()));
		}

		// ---------------------------------------------------------------------

		// Capacity ------------------------------------------------------------

		bool      empty() const {
			return size_ == 0;
		}

		size_type size() const {
			return size_;
		}

		size_type max_size() const {
			return alloc_.max_size();
		}

		// ---------------------------------------------------------------------

		// Element access ------------------------------------------------------

		reference       front() {
			return end_node_->next->data;
		}

		const_reference front() const {
			return end_node_->next->data;
		}

		reference       back() {
			return end_node_->prev->data;
		}

		const_reference back() const {
			return end_node_->prev->data;
		}

		// ---------------------------------------------------------------------

		// Modifiers -----------------------------------------------------------

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last) {
			List new_list(first, last, allocator_type());
			this->swap(new_list);
		}

		void assign(size_type n, const value_type & val) {
			List new_list(n, val, allocator_type());
			this->swap(new_list);
		}

		void push_front(const value_type & val) {
			this->insert(this->begin(), val);
		}

		void pop_front() {
			erase(this->begin());
		}

		void push_back(value_type const & val) {
			this->insert(this->end(), val);
		}

		void pop_back() {
			this->erase(--this->end());
		}

		iterator insert(iterator position, const value_type & val) {
			Node* new_node = construct_node(val);

			new_node->next                  = position.get_node();
			new_node->prev                  = position.get_node()->prev;
			position.get_node()->prev->next = new_node;
			position.get_node()->prev       = new_node;
			++this->size_;
			return iterator(new_node);
		}

		void insert(iterator position, size_type n, const value_type & val) {
			for (size_type i = 0; i < n; ++i) {
				position = insert(position, val);
			}
		}

		template <class InputIterator>
		void insert
		(
		 iterator position,
		 InputIterator first,
		 InputIterator last,
		 typename enable_if
		 < !std::numeric_limits<InputIterator>::is_specialized >::type* = 0
		)
		{
			while (first != last) {
				position = insert(position, *first);
				++position;
				++first;
			}
		}

		iterator erase(iterator position) {
			Node* next;

			next = position.get_node()->next;
			destroy_node(position.get_node());
			--this->size_;
			return iterator(next);
		}

		iterator erase (iterator first, iterator last) {
			Node* current;
			while (first != last) {
				current = first.get_node();
				++first;
				destroy_node(current);
				--this->size_;
			}
			return last;
		}

		void     swap(List & x) {
			ft::swap(end_node_, x.end_node_);
			ft::swap(size_, x.size_);
			ft::swap(alloc_, x.alloc_);
			ft::swap(node_alloc_, x.node_alloc_);
		}

		void resize(size_type n, value_type val = value_type()) {
			for (size_type i = n; i < size_; ++i) {
				this->push_back(val);
			}
			for (size_type i = n; i > size_; --i) {
				this->pop_back();
			}
		}

		void clear() {
			this->erase(this->begin(), this->end());
		}

		// ---------------------------------------------------------------------

		// Operations ----------------------------------------------------------

		void splice(iterator position, List & x) {
			if (x.size_ == 0) {
				return ;
			}

			Node* pos  = position.get_node();
			Node* prev = pos->prev;

			pos->prev         = x.end_node_->prev;
			pos->prev->next   = pos;
			prev->next        = x.end_node_->next;
			prev->next->prev  = prev;
			size_            += x.size_;
			x.size_           = 0;
			x.end_node_->next = x.end_node_;
			x.end_node_->prev = x.end_node_;
		}

		void splice(iterator position, List & x, iterator i) {
			Node* pos    = position.get_node();
			Node* prev   = pos->prev;
			Node* from_x = i.get_node();

			from_x->prev->next = from_x->next;
			from_x->next->prev = from_x->prev;
			from_x->prev       = prev;
			from_x->next       = pos;
			pos->prev          = from_x;
			prev->next         = from_x;
			++size_;
			--x.size_;
		}

		void splice
		(
		 iterator position,
		 List & x,
		 iterator first,
		 iterator last
		)
		{
			List from_x(first, last);
			Node* f = first.get_node();
			Node* l = last.get_node();

			this->splice(position, from_x);
			f->prev->next = l;
			l->prev       = f->prev;
			while(first != last) {
				f = first.get_node();
				++first;
				destroy_node(f);
				--x.size_;
			}
		}

		void remove(const value_type& val) {
			if (this->size_ == 0) {
				return ;
			}

			Node* current       = end_node_->next;
			size_type save_size = size_;

			for (size_type i = 0; i < save_size + 1; ++i) {
				current = current->next;
				if (current->prev->data == val) {
					destroy_node(current->prev);
					--size_;
				}
			}
		}

		template <class Predicate>
		void remove_if (Predicate pred) {
			if (this->size_ == 0) {
				return ;
			}

			Node* current       = this->end_node_->next;
			size_type save_size = this->size_;

			for (size_type i = 0; i < save_size + 1; ++i) {
				current = current->next;
				if (pred(current->prev->data)) {
					destroy_node(current->prev);
					--this->size_;
				}
			}
		}

		void unique() {
			if (size_ <= 1) {
				return ;
			}

			Node* current = end_node_->next->next;

			while (current != end_node_) {
				if (current->data == current->prev->data) {
					current = current->next;
					destroy_node(current->prev);
					--size_;
				} else {
					current = current->next;
				}
			}
		}

		template <class BinaryPredicate>
		void unique (BinaryPredicate binary_pred) {
			if (size_ <= 1) {
				return ;
			}

			Node* current = end_node_->next->next;

			while (current != end_node_){
				if (binary_pred(current->data, current->prev->data)) {
					current = current->next;
					destroy_node(current->prev);
					--size_;
				} else {
					current = current->next;
				}
			}
		}

		void merge(List & x) {
			if (this == &x) {
				return ;
			}

			Node* this_current = this->begin().get_node();
			Node* x_current    = x.begin().get_node();

			while (this_current != this->end_node_ && x_current != x.end_node_)
			{
				if (x_current->data < this_current->data) {
					x_current = x_current->next;
					put_node(this_current, x_current->prev);
				} else {
					this_current = this_current->next;
				}
			}
			if (x_current != x.end_node_) {
				x_current->prev          = this_current->prev;
				this_current->prev->next = x_current;
				x.end_node_->prev->next  = this->end_node_;
				this->end_node_->prev    = x.end_node_->prev;
			}
			this->size_      += x.size_;
			x.size_           = 0;
			x.end_node_->next = x.end_node_;
			x.end_node_->prev = x.end_node_;
		}

		template <class Compare>
		void merge (List & x, Compare comp) {
			if (this == &x) {
				return ;
			}

			Node* this_current = this->begin().get_node();
			Node* x_current    = x.begin().get_node();

			while (this_current != end_node_ && x_current != x.end_node_) {
				if (comp(x_current->data, this_current->data)) {
					x_current = x_current->next;
					put_node(this_current, x_current->prev);
				} else {
					this_current = this_current->next;
				}
			}
			if (x_current != x.end_node_) {
				x_current->prev          = this_current->prev;
				this_current->prev->next = x_current;
				x.end_node_->prev->next  = end_node_;
				end_node_->prev          = x.end_node_->prev;
			}
			x.end_node_->next = x.end_node_;
			x.end_node_->prev = x.end_node_;
			size_            += x.size_;
			x.size_           = 0;
		}

		void sort() {
			if (this->size_ <= 1) {
				return ;
			}
			merge_sort(*this, ft::Less<value_type>());
		}

		template <class Compare>
		void sort(Compare comp) {
			if (this->size_ <= 1) {
				return ;
			}
			merge_sort(*this, comp);

		}

		void reverse() {
			if (this->size_ <= 1) {
				return ;
			}

			Node* begin = end_node_->next;
			Node* end   = end_node_->prev;

			for (size_type i = 0; i < size_ + 1; ++i) {
				begin = begin->next;
				end   = end->prev;
				swap_node(begin->prev, end->next);
			}
		}

		// ---------------------------------------------------------------------

	private:
		Node*                end_node_;
		size_type            size_;
		allocator_type       alloc_;
		std::allocator<Node> node_alloc_;

	protected:

		// Merge-sort ----------------------------------------------------------

		iterator split_list(List & current)
		{
			if (current.size_ == 1) {
				return (current.end());
			}

			Node* fast = current.begin().get_node();
			Node* slow = fast;

			while
			(
			 fast != current.end_node_ &&
			 fast->next != current.end_node_
			)
			{
				fast = fast->next->next;
				slow = slow->next;
			}
			if (current.size_ % 2 != 0) {
				slow = slow->next;
			}
			return (iterator(slow));
		}

		template<class Compare>
		void     merge_sort(List & current, Compare comp)
		{
			iterator half(split_list(current));
			iterator end(current.end());
			List     new_list(half, end);
			Node*    node;

			while (half != end) {
				node = half.get_node();
				++half;
				destroy_node(node);
				--this->size_;
			}
			if (current.size_ == 1) {
				return ;
			} else if (current.size_ == 2) {
				node        = current.begin().get_node();
				Node *node2 = node->next;

				if (comp(node2->data, node->data)) {
					swap_node(node, node2);
				}
				if (new_list.size_ > 1) {
					new_list.sort(comp);
				}
				if (new_list.size_ > 0) {
					current.merge<Compare>(new_list, comp);
				}
				return ;
			}
			current.sort<Compare>(comp);
			new_list.sort<Compare>(comp);
			current.merge<Compare>(new_list, comp);
		}

		// ---------------------------------------------------------------------

		Node* allocate_node() {
			Node* node;

			node       = node_alloc_.allocate(1);
			node->next = node;
			node->prev = node;
			return node;
		}

		Node* construct_node(value_type val) {
			Node* node;

			node = allocate_node();
			alloc_.construct(&node->data, val);
			return node;
		}

		void  deallocate_node(Node* node) {
			node->prev->next = node->next;
			node->next->prev = node->prev;
			node_alloc_.deallocate(node, 1);
		}

		void  destroy_node(Node* node) {
			alloc_.destroy(&node->data);
			deallocate_node(node);
		}

		void  put_node(iterator position, Node* node) {
			node->prev                      = position.get_node()->prev;
			node->next                      = position.get_node();
			position.get_node()->prev->next = node;
			position.get_node()->prev       = node;
		}

		bool are_they_neighbours(Node* A,Node* B) {
			return
			(
			 (A->next == B && B->prev == A) || (A->prev == B && B->next == A)
			);
		}

		void refresh_outer_pointers(Node* A) {
				A->prev->next = A;
				A->next->prev = A;
		}

		void swap_node(Node* A,Node* B) {
			Node* swapper[4];
			Node* tmp;

			if (A == B) {
				return ;
			}
			if (B->next == A) {
				tmp = A;
				A = B;
				B = tmp;
			}
			swapper[0] = A->prev;
			swapper[1] = B->prev;
			swapper[2] = A->next;
			swapper[3] = B->next;
			if (are_they_neighbours(A,B)) {
				A->prev = swapper[2];
				B->prev = swapper[0];
				A->next = swapper[3];
				B->next = swapper[1];
			} else {
				A->prev = swapper[1];
				B->prev = swapper[0];
				A->next = swapper[3];
				B->next = swapper[2];
			}
			refresh_outer_pointers(A);
			refresh_outer_pointers(B);
		}
	};

// ========================== END LIST CLASS ===================================

// Relational operators ========================================================

	template <class T, class Alloc>
	bool operator==(const List<T,Alloc> & lhs, const List<T,Alloc> & rhs) {
		if (lhs.size() != rhs.size()) {
			return false;
		}

		typename ft::List<T, Alloc>::const_iterator lit(lhs.begin());
		typename ft::List<T, Alloc>::const_iterator rit(rhs.begin());

		while (lit != lhs.end()) {
			if (*lit != *rit) {
				return false;
			}
			++lit;
			++rit;
		}
		return true;
	}

	template <class T, class Alloc>
	bool operator!=(const List<T,Alloc> & lhs, const List<T,Alloc> & rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<(const List<T,Alloc> & lhs, const List<T,Alloc> & rhs) {
		typename List<T, Alloc>::const_iterator lit(lhs.begin());
		typename List<T, Alloc>::const_iterator rit(rhs.begin());

		while (lit != lhs.end() && rit != rhs.end()) {
			if (*lit < *rit) {
				return true;
			}
			++lit;
			++rit;
		}
		return lhs.size() < rhs.size();
	}

	template <class T, class Alloc>
	bool operator>(const List<T,Alloc> & lhs, const List<T,Alloc> & rhs) {
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator<=(const List<T,Alloc> & lhs, const List<T,Alloc> & rhs) {
		return !(lhs > rhs);
	}

	template <class T, class Alloc>
	bool operator>=(const List<T,Alloc> & lhs, const List<T,Alloc> & rhs) {
		return !(lhs < rhs);
	}

// =============================================================================

}

// ========================= END NAMESPACE FT ==================================

#endif /* FT_LIST_HPP */
