//
// Created by Gueren Drive on 3/25/21.
//

#ifndef CONTAINERS_CPP_FT_MAP_HPP
#define CONTAINERS_CPP_FT_MAP_HPP

// ========================== OTHER INCLUDES ===================================

# include "../ft_multiset/ft_multiset.hpp"
# include "ft_map_bidir_iterator.hpp"
# include "../ft_reverse_iterator.hpp"

// =============================================================================

namespace ft {

// ================================ MAP ========================================

	template
	< class Key,                                       // map::key_type
	  class T,                                         // map::mapped_type
	  class Compare = ft::KeyComp<Key, T>,             // map::key_compare
	  class Alloc = std::allocator<std::pair<Key,T> > // map::allocator_type
	>
	class Map {
	public:

		// Typedef -------------------------------------------------------------

		typedef Key                                      key_type;
		typedef T                                        mapped_type;
		typedef std::pair<key_type, mapped_type>         value_type;
		typedef Compare                                  key_compare;
		typedef Compare                                  value_compare;
		typedef Alloc                                    allocator_type;

		typedef typename allocator_type::reference       reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;

		typedef ft::MapBidirIterator
		        <
		         ft::MultisetBidirIterator
		                <
		                 ft::VectorRandomAccessIterator
		                        <
		                         value_type, value_type*, value_type&
		                        >
		                >
		        >                                        iterator;

		typedef ft::MapBidirIterator
		        <
		         ft::MultisetBidirIterator
		                 <
		                  ft::VectorRandomAccessIterator
		                          <
		                           value_type,
		                           const value_type*,
		                           const value_type&
		                          >
		                 >
		         >                                       const_iterator;

		typedef ft::ReverseIterator<iterator>            reverse_iterator;
		typedef ft::ReverseIterator<const_iterator>      const_reverse_iterator;

		typedef typename ft::MapBidirIterator
		<
		 ft::MultisetBidirIterator
		         <
		          ft::VectorRandomAccessIterator
		                  <
		                   value_type, value_type*, value_type&
		                  >
		         >
		 >::difference_type                              difference_type;

		typedef size_t                                   size_type;

		// ---------------------------------------------------------------------

		// Constructor - Destructor --------------------------------------------

		explicit Map
		(
		 const key_compare& comp = key_compare(),
		 const allocator_type& alloc = allocator_type()
		)
		: values_(), comp_(comp), alloc_(alloc)
		{}

		template <class InputIterator>
		Map
		(
		 InputIterator first,
		 InputIterator last,
		 const key_compare& comp = key_compare(),
		 const allocator_type& alloc = allocator_type()
		)
		: values_(), comp_(comp), alloc_(alloc)
		{
			this->insert(first, last);
		}

		Map
		(
		 const Map & x
		)
		: values_(x.values_), comp_(x.comp_), alloc_(x.alloc_)
		{}

		// ---------------------------------------------------------------------

		// Operators -----------------------------------------------------------

		// '='
		Map &         operator=(const Map & x) {
			if (this == &x) {
				return *this;
			}
			values_ = x.values_;
			alloc_  = x.alloc_;
			comp_   = x.comp_;
			return *this;
		}

		mapped_type & operator[] (const key_type & k) {
			return
			(
			 (*((this->insert(std::pair<Key, T>(k, T()))).first)).second
			);
		}

		// ---------------------------------------------------------------------

		// Iterators -----------------------------------------------------------

		iterator               begin() {
			return iterator(values_.begin());
		}

		const_iterator         begin() const {
			return const_iterator(values_.begin());
		}

		iterator               end() {
			return iterator(values_.end());
		}

		const_iterator         end() const {
			return const_iterator(values_.end());
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

		const_reverse_iterator rend() const {
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

		std::pair<iterator, bool> insert (const value_type & val) {
			if (values_.size() == 0) {
				return
				(
				 std::pair<iterator, bool>(iterator(values_.insert(val)), true)
				);
			}

			iterator position(values_.find(val));

			if (position == end()) {
				return
				(
				 std::pair<iterator, bool>(iterator(values_.insert(val)), true)
				);
			}
			return std::pair<iterator, bool>(position, false);
		}

		iterator                  insert
		(
		 iterator position, const value_type& val
		)
		{
			(void)(position);
			std::pair<iterator, bool> pos(this->insert(val));

			return pos.first;
		}

		template <class InputIterator>
		void                      insert
		(
		 InputIterator first, InputIterator last
		)
		{
			while (first != last) {
				this->insert(*first);
				++first;
			}
		}

		void                      erase(iterator position) {
			values_.erase(position.base());
		}

		size_type                 erase(const key_type & k) {
			if (this->size() == 0) {
				return 0;
			}

			iterator  found(values_.find(value_type(k, T())));
			size_type i = 0;

			while (found != this->end()) {
				erase(found);
				found = iterator(values_.find(value_type(k, T())));
				++i;
			}
			return i;
		}

		void                      erase(iterator first, iterator last) {
			while (first != last) {
				erase(first);
				--last;
			}
		}

		void                      swap(Map & x) {
			values_.swap(x.values_);
			ft::swap(comp_, x.comp_);
			ft::swap(alloc_, x.alloc_);
		}

		void                      clear() {
			values_.clear();
		}

		// ---------------------------------------------------------------------

		// Observers -----------------------------------------------------------

		key_compare               key_comp() const {
			return comp_;
		}

		value_compare             value_comp() const {
			return comp_;
		}

		// ---------------------------------------------------------------------

		// Operations ----------------------------------------------------------

		iterator                                 find(const key_type& k) {
			return iterator(values_.find(value_type(k, mapped_type ())));
		}

		size_type                                count(const key_type& k) {
			iterator found
			(
			 values_.find(std::pair<key_type, mapped_type>(k, mapped_type()))
			);

			return found != this->end();
		}

		iterator                                 lower_bound
		(
		 const key_type & k
		)
		 {
			return iterator
			(
			 values_.find(std::pair<key_type, mapped_type>(k, mapped_type()))
			);
		}

		const_iterator                           lower_bound
		(
		 const key_type & k
		) const
		{
			return const_iterator
			(
			 values_.find(std::pair<key_type, mapped_type>(k, mapped_type()))
			);
		}

		iterator                                 upper_bound
		(
		 const key_type & k
		)
		{
			iterator pos(this->lower_bound(k));

			return (pos != this->end()) ? ++pos : pos;
		}

		const_iterator                           upper_bound
		(
		 const key_type& k
		) const
		{
			const_iterator pos(this->lower_bound(k));

			return (pos != this->end()) ? ++pos : pos;
		}

		std::pair<iterator, iterator>            equal_range
		(
		 const key_type & k
		)
		{
			iterator first(this->lower_bound(k));
			iterator last(this->upper_bound(k));

			return std::pair<iterator, iterator >(first, last);
		}

		std::pair<const_iterator,const_iterator> equal_range
		(
		 const key_type & k
		) const
		{
			const_iterator first(this->lower_bound(k));
			const_iterator last(this->upper_bound(k));

			return std::pair<const_iterator, const_iterator >(first, last);
		}

		// ---------------------------------------------------------------------

	private:
		Multiset<value_type, Compare, Alloc> values_;
		key_compare                          comp_;
		Alloc                                alloc_;
	};

// =============================================================================

}

// ============================ END NAMESPACE FT ===============================

#endif //CONTAINERS_CPP_FT_MAP_HPP
