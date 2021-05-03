//
// Created by Gueren Drive on 3/23/21.
//

#ifndef CONTAINERS_CPP_FT_MULTISET_HPP
#define CONTAINERS_CPP_FT_MULTISET_HPP

// ========================== OTHER INCLUDES ===================================

# include "../ft_vector/ft_vector.hpp"
# include "../utils.hpp"

# include "ft_multiset_bidir_iterator.hpp"
# include "../ft_reverse_iterator.hpp"

// =============================================================================

// ============================ NAMESPACE FT ===================================

namespace ft {

// ============================= MULTISET ======================================

	template <
	         class T,
	         class Compare = ft::Less<T>,
	         class Alloc = std::allocator<T>
	        >
	class Multiset {
	public:

		// Typedef -------------------------------------------------------------

		typedef T                                        key_type;
		typedef T                                        value_type;
		typedef Compare                                  key_compare;
		typedef Compare                                  value_compare;
		typedef Alloc                                    allocator_type;
		typedef typename allocator_type::reference       reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;

		typedef ft::MultisetBidirIterator
		        <ft::VectorRandomAccessIterator<T, T*, T&> >
		                                                 iterator;

		typedef ft::MultisetBidirIterator
		        <ft::VectorRandomAccessIterator<T, const T*, const T&> >
		                                                 const_iterator;

		typedef ft::ReverseIterator<iterator>            reverse_iterator;
		typedef ft::ReverseIterator<const_iterator>      const_reverse_iterator;

		typedef typename
		ft::MultisetBidirIterator
		        <ft::VectorRandomAccessIterator<T, T*, T&> >::difference_type
		                                                 difference_type;

		typedef size_t                                   size_type;

		// ---------------------------------------------------------------------

		// Constructor - Destructor --------------------------------------------

		explicit Multiset
		(
		 const key_compare& comp = key_compare(),
		 const allocator_type& alloc = allocator_type()
		)
		: values_(), comp_(comp), alloc_(alloc)
		{}

		template <class InputIterator>
		Multiset
		(
		 InputIterator first,
		 InputIterator last,
		 const key_compare& comp = key_compare(),
		 const allocator_type& alloc = allocator_type()
		)
		: values_(), comp_(comp), alloc_(alloc)
		{
			insert(first, last);
		}

		Multiset (const Multiset & x)
		: values_(x.values_), comp_(x.comp_), alloc_(x.alloc_)
		{}

		~Multiset() {
			this->values_.~Vector();
		}

		// ---------------------------------------------------------------------

		// Operator '=' --------------------------------------------------------

		Multiset & operator=(const Multiset & x) {
			this->values_ = x.values_;
			this->alloc_  = x.alloc_;
			this->comp_   = x.comp_;
			return (*this);
		}

		// ---------------------------------------------------------------------

		// Iterators -----------------------------------------------------------

		iterator               begin() {
			return iterator(this->values_.begin());
		}
//
		const_iterator         begin() const {
			return const_iterator(this->values_.begin());
		}

		iterator               end() {
			return iterator(this->values_.end());
		}

		const_iterator         end() const {
			return const_iterator(this->values_.end());
		}

		reverse_iterator       rbegin() {
			if (this->size() == 0) {
				return reverse_iterator(this->end());
			}
			return reverse_iterator(--(this->end()));
		}

		const_reverse_iterator rbegin() const {
			if (this->size() == 0) {
				return const_reverse_iterator(this->end());
			}
			return const_reverse_iterator(--(this->end()));
		}

		reverse_iterator       rend() {
			if (this->size() == 0) {
				return reverse_iterator(this->begin());
			}
			return reverse_iterator(--(this->begin()));
		}

		reverse_iterator       rend() const {
			if (this->size() == 0) {
				return const_reverse_iterator(this->begin());
			}
			return const_reverse_iterator(--(this->begin()));
		}

		// ---------------------------------------------------------------------

		// Capacity ------------------------------------------------------------

		bool      empty() const {
			return values_.empty();
		}

		size_type size() const {
			return values_.size();
		}

		size_type max_size() const {
			return alloc_.max_size();
		}

		// ---------------------------------------------------------------------

		// Modifiers -----------------------------------------------------------

		iterator      insert(const value_type & val) {
			if (values_.size() == 0) {
				return iterator(values_.insert(values_.begin(), val));
			}

			size_type pos_index = binary_search(val, this->values_.size());

			return
			(
			 iterator
			 (
			  values_.insert
			  (
			   values_.begin() + pos_index + (!comp_(val, values_[pos_index])),
			   val
			  )
			 )
			);
		}

		iterator      insert(iterator position, const value_type & val) {
			(void)(position);
			return insert(val);
		}

		template <class InputIterator>
		void          insert(InputIterator first, InputIterator last) {
			while (first != last) {
				insert(*first);
				++first;
			}
		}

		void          erase(iterator position) {
			values_.erase(position.base());
		}

		size_type     erase(const value_type& val) {
			if (this->size() == 0) {
				return 0;
			}

			iterator   position(find_position(val));
			value_type save_val(val);
			size_type  i = 0;

			while (!comp_(*position, save_val) && !comp_(save_val, *position)) {
				erase(position);
				position = find_position(save_val);
				++i;
			}
			return i;
		}

		void          erase(iterator first, iterator last) {
			while (first != last) {
				erase(first);
				--last;
			}
		}

		void          swap (Multiset & x) {
			ft::swap(values_, x.values_);
			ft::swap(comp_, x.comp_);
			ft::swap(alloc_, x.alloc_);
		}

		void          clear() {
			values_.clear();
		}

		// ---------------------------------------------------------------------

		// Observers -----------------------------------------------------------

		key_compare   key_comp() const {
			return comp_;
		}

		value_compare value_comp() const {
			return comp_;
		}

		// ---------------------------------------------------------------------

		// Operations ----------------------------------------------------------

		iterator  find(const value_type& val) {
			if (this->size() == 0) {
				return this->end();
			}
			iterator found(find_position(val));
			if (comp_(*found, val) || comp_(val, *found)) {
				return this->end();
			}
			return found;
		}

		size_type count(const value_type& val) {
			if (values_.size() == 0) {
				return 0;
			}

			iterator  position(find_position(val));
			size_type i = 0;

			if (position == this->end()) {
				return 0;
			}
			if (comp_(*position, val) || comp_(val, *position)) {
				return 0;
			}

			while (!comp_(*position, val) && !comp_(val, *position)) {
				if (position == begin()) {
					break ;
				}
				--position;
			}
			if (comp_(*position, val) || comp_(val, *position)) {
				++position;
			}

			while (!comp_(*position, val) && !comp_(val, *position)) {
				if (position == end()) {
					break ;
				}
				++position;
				++i;
			}
			return i;
		}

		iterator lower_bound(const value_type& val) {
			if (this->size() == 0) {
				return this->end();
			}

			iterator found(find(val));

			if (found == this->end()) {
				return found;
			}

			while (!comp_(*found, val) && !comp_(val, *found)) {
				if (found == begin()) {
					break ;
				}
				--found;
			}
			if (comp_(*found, val) || comp_(val, *found)) {
				++found;
			}
			return found;
		}

		iterator upper_bound(const value_type& val) {
			if (this->size() == 0) {
				return this->end();
			}

			iterator found(find(val));

			if(found == this->end()) {
				return found;
			}

			while (!comp_(*found, val) && !comp_(val, *found)) {
				if (found == end()) {
					break ;
				}
				++found;
			}
			return found;
		}

		std::pair<iterator,iterator> equal_range(const value_type& val) {
			iterator first(lower_bound(val));
			iterator last(upper_bound(val));

			return std::pair<iterator, iterator>(first, last);
		}

		// ---------------------------------------------------------------------

		// Allocator -----------------------------------------------------------

		allocator_type get_allocator() const {
			return alloc_;
		}

		// ---------------------------------------------------------------------

	private:

		Vector<T, Alloc> values_;
		key_compare      comp_;
		Alloc            alloc_;

	protected:
		iterator   find_position(const value_type & val) {
			return
			(
			 iterator(values_.begin() + binary_search(val, values_.size()))
			);
		}

		// Binary search -------------------------------------------------------

		size_type binary_search
		(
		 const value_type &val,
		 size_type size,
		 size_type start = 0
		) const
		{
			if (size == 1) {
				return start;
			}

			size_type half = start + size / 2 + (size % 2);

			return
			(
			 (comp_(val, values_[half])) ?
			 binary_search(val, half - start, start)
			 : binary_search(val, start + size - half, half)
			);
		}

		// ---------------------------------------------------------------------
	};


// =============================================================================

}

// ============================ END NAMESPACE FT ===============================

#endif //CONTAINERS_CPP_FT_MULTISET_HPP
