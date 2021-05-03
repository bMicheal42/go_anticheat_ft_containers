#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

// ============================ STD-LIBS =======================================

# include <iostream>
# include <cstddef>   // size_t, ptrdiff_t ...
# include <cstring>   // memcpy();
# include <memory>    // allocator
# include <cstddef>   // ptrdiff_t
# include <limits>    // std::numeric_limits
# include <exception> // std::exception

// =============================================================================

// ========================== OTHER INCLUDES ===================================

# include "ft_vector_random_access_iterator.hpp"
# include "../ft_reverse_iterator.hpp"
# include "../utils.hpp"

// =============================================================================

// ============================ NAMESPACE FT ===================================

namespace ft {

// ============================= VECTOR ========================================

	template < class T, class Alloc = std::allocator<T> >
	class Vector {

	public:

		// Typedef -------------------------------------------------------------

		typedef T                                               value_type;
		typedef Alloc                                           allocator_type;
		typedef typename allocator_type::reference              reference;
		typedef typename allocator_type::const_reference        const_reference;
		typedef typename allocator_type::pointer                pointer;
		typedef typename allocator_type::const_pointer          const_pointer;

		typedef ft::VectorRandomAccessIterator<T, T*, T& >      iterator;
		typedef ft::VectorRandomAccessIterator<T, const T*, const T&>
		                                                        const_iterator;

		typedef ft::ReverseIterator<iterator>                  reverse_iterator;
		typedef ft::ReverseIterator<const_iterator>      const_reverse_iterator;

		typedef typename VectorRandomAccessIterator<T, T*, T&>::difference_type
                                                                difference_type;

		typedef size_t                                          size_type;

		// ---------------------------------------------------------------------

		// Constructor - Destructor --------------------------------------------

		explicit Vector(const allocator_type & alloc = allocator_type())
		: arr_(0), begin_(0), size_(0), capacity_(0), alloc_(alloc) {}

		explicit Vector
		(
		 size_type n,
		 const value_type & val = value_type(),
		 const allocator_type & alloc = allocator_type()
		)
		: arr_(0), begin_(0), size_(n), capacity_(n), alloc_(alloc)
		{
			try {
				 arr_  = alloc_.allocate(n);
			} catch (std::exception & e) {
			this->~Vector();
			throw Vector::LengthError();
		}
			begin_ = arr_;
			for (size_type i = 0; i < n; ++i) {
				alloc_.construct(arr_ + i, val);
			}
		}

		template <class InputIterator>
		Vector
		(
		 InputIterator first,
		 InputIterator last,
		 const allocator_type& alloc = allocator_type(),
		 typename enable_if
		 < !std::numeric_limits<InputIterator>::is_specialized >::type* = 0
		)
		: arr_(0), begin_(0), size_(0), capacity_(0), alloc_(alloc)
		{
			size_     = std::distance(first, last);
			capacity_ = size_;
			try {
				arr_ = alloc_.allocate(size_);
			} catch (std::exception & e) {
				this->~Vector();
				Vector::LengthError();
			}
			begin_ = arr_;
			for (size_type i = 0; i < size_; ++i) {
				alloc_.construct(arr_ + i, *first);
				++first;
			}
		}

		Vector(const Vector & x)
		: arr_(0), begin_(0),
		size_(x.size_), capacity_(x.capacity_), alloc_(x.alloc_)
		{
			try {
				arr_ = alloc_.allocate(x.capacity_);
			} catch (std::exception & e) {
				this->~Vector();
				throw Vector::LengthError();
			}
			begin_    = arr_;
			size_     = x.size_;
			capacity_ = x.capacity_;
			alloc_    = x.alloc_;
			for (size_type i = 0; i < x.size_; ++i) {
				alloc_.construct(arr_ + i, x[i]);
			}
		}

		virtual ~Vector() {
			if (begin_ == 0) {
				return ;
			}
			for (size_type i = 0; i < size_; ++i) {
				alloc_.destroy(arr_ + i);
			}
			alloc_.deallocate(begin_, capacity_);
			arr_      = 0;
			begin_    = 0;
			size_     = 0;
			capacity_ = 0;
		}

		// ---------------------------------------------------------------------

		// Operator '=' --------------------------------------------------------

		Vector & operator=(const Vector & x) {
			if (this == &x) {
				return (*this);
			}
			this->~Vector();
			alloc_ = x.alloc_;
			arr_   = alloc_.allocate(x.capacity_);
			for (size_type i = 0; i < x.size_; ++i) {
				alloc_.construct(arr_ + i, x[i]);
			}
			begin_    = arr_;
			size_     = x.size_;
			capacity_ = x.capacity_;
			return *this;
		}

		// ---------------------------------------------------------------------

		// Iterators -----------------------------------------------------------

		iterator               begin() {
			return iterator(arr_);
		}

		const_iterator         begin() const {
			return const_iterator(arr_);
		}

		iterator               end() {
			return iterator(arr_ + size_);
		}

		const_iterator         end() const {
			return const_iterator(arr_ + size_);
		}

		reverse_iterator       rbegin() {
			if (size_ == 0) {
				return reverse_iterator(iterator(arr_));
			}
			return reverse_iterator(iterator(arr_ + size_ - 1));
		}

		const_reverse_iterator rbegin() const {
			if (size_ == 0) {
				return iterator(arr_);
			}
			return iterator(arr_ + size_ - 1);
		}

		reverse_iterator       rend() {
			if (size_ == 0) {
				return reverse_iterator(iterator(arr_));
			}
			return reverse_iterator(iterator(arr_ - 1));
		}

		reverse_iterator       rend() const {
			if (size_ == 0) {
				return reverse_iterator(iterator(arr_));
			}
			return reverse_iterator(iterator(arr_ - 1));
		}

		// ---------------------------------------------------------------------

		// Capacity ------------------------------------------------------------

		size_type size() const {
			return size_;
		}

		size_type max_size() const {
			return alloc_.max_size();
		}

		void      resize(size_type n, value_type val = value_type()) {
			size_type i = 0;

			// size_ > n ----> just delete elements.
			if (size_ >= n) {
				for (i = n; i < size_; ++i) {
					alloc_.destroy(arr_ + i);
				}
				size_ = n;
				return ;
			}
			// capacity_ >= n ----> just adding elements.
			if (capacity_ >= n) {
				for (i = size_; i < n; ++i) {
					alloc_.construct(arr_ + i, val);
				}
				size_ = n;
				return ;
			}

			// n > capacity_ ----> allocate new memory.
			pointer new_arr;

			try {
				new_arr = alloc_.allocate(n);
			} catch (std::exception & e) {
				throw Vector::LengthError();
			}
			memmove(new_arr, arr_, sizeof(value_type) * size_);
			for (i = size_; i < n; ++i) {
				alloc_.construct(new_arr + i, val);
			}
			if (begin_ != 0) {
				alloc_.deallocate(begin_, capacity_);
			}
			arr_      = new_arr;
			begin_    = new_arr;
			size_     = n;
			capacity_ = n;
		}

		size_type capacity() const {
			return capacity_;
		}

		bool      empty() const {
			return size_ == 0;
		}

		void      reserve(size_type n) {
			if (capacity_ >= n) {
				return ;
			}

			pointer new_arr = alloc_.allocate(n);

			memmove(new_arr, arr_, sizeof(value_type) * size_);
			if (begin_ != 0) {
				alloc_.deallocate(begin_, capacity_);
			}
			arr_      = new_arr;
			begin_    = new_arr;
			capacity_ = n;
		}

		// ---------------------------------------------------------------------

		// Element access ------------------------------------------------------

		reference       operator[] (size_type n) {
			return arr_[n];
		}

		const_reference operator[] (size_type n) const {
			return arr_[n];
		}

		reference       at(size_type n) {
			if (n >= size_) {
				throw Vector::OutOfRange();
			}
			return arr_[n];
		}

		const_reference at(size_type n) const {
			if (n >= size_) {
				throw Vector::OutOfRange();
			}
			return arr_[n];
		}

		reference       front() {
			return *arr_;
		}

		const_reference front() const {
			return *arr_;
		}

		reference       back() {
			return arr_[size_ - 1];
		}

		const_reference back() const {
			return arr_[size_ - 1];
		}

		// ---------------------------------------------------------------------

		// Modifiers -----------------------------------------------------------

		template <class InputIterator>
		void     assign
		(
		 InputIterator first,
		 InputIterator last,
		 typename enable_if
		 < !std::numeric_limits<InputIterator>::is_specialized >::type* = 0
		)
		{
			difference_type new_size = std::distance(first, last);

			if (new_size < 0 ) {
				this->~Vector();
				throw Vector::LengthError();
			}

			Vector    save(first, last);

			this->clear();
			this->reserve(new_size);
			this->insert(this->begin(), save.begin(), save.end());
		}

		void     assign(size_type n, const value_type& val) {
			value_type save(val);

			this->clear();
			this->reserve(n);
			this->insert(this->begin(), n, save);
		}

		void     push_back(const value_type & val) {
			this->insert(this->end(), val);
		}

		void     pop_back() {
			alloc_.destroy(arr_ + size_ - 1);
			--size_;
		}

		iterator insert(iterator position, const value_type& val) {
			size_type before = position - this->begin();

			this->insert(position, 1, val);
			return iterator(arr_ + before);
		}

		iterator insert(iterator position, size_type n, const value_type& val) {
			size_type before = position - this->begin();

			// capacity_ >= size_ + n example: [1,2,3,.,.,.] <-- 5 between 1, 2
			if (capacity_ >= size_ + n) {
				size_type last = (size_ == 0) ? 0 : size_ - 1;

				// moving [1,2,3,.,.,.] ----> [1,.,2,3,.,.]
				for (size_type i = before; i < size_; ++i, --last) {
					memmove
					(
					 arr_ + last + n,
					 arr_ + last,
					 sizeof(value_type)
					);
				}
				// adding 5: [1,.,2,3,.,.] ----> [1,5,2,3,.,.];
				for (size_type i = 0; i < n; ++i) {
					alloc_.construct(arr_ + before + i, val);
				}
				size_ += n;
				return iterator(arr_ + before);
			}
			// capacity_ < size_ + n: allocate new memory
			size_type new_capacity = capacity_ * 2;

			if (new_capacity < size_ + n) {
				new_capacity = size_ + n;
			}

			value_type      save_val(val);
			difference_type save_pos(position - this->begin());

			this->reserve(new_capacity);
			this->insert(iterator(arr_ + save_pos), n, save_val);
			return iterator(arr_ + before);
		}

		template <class InputIterator>
		void     insert
		(
		 iterator position,
		 InputIterator first,
		 InputIterator last,
		 typename enable_if
		 < !std::numeric_limits<InputIterator>::is_specialized >::type* = 0
		 )
		 {
			difference_type n      = std::distance(first, last);
			difference_type before = position - this->begin();

			if (n <= 0) {
				return ;
			}
			// capacity_ >= size_ + n: just adding elements.
			if (capacity_ >= size_ + n) {
				while (first != last) {
					insert(position, *first);
					++first;
					++position;
				}
				return ;
			}

			// capacity_ < size_ + n: allocate new memory
			pointer new_arr;
			size_t  new_capacity = capacity_ * 2;

			if (size_ + n > new_capacity) {
				new_capacity = size_ + n;
			}

			new_arr = alloc_.allocate(new_capacity);

			memmove(new_arr, arr_, sizeof(value_type) * before);
			std::copy(first, last, new_arr + before);
			memmove(
			 new_arr + before + n,
			 arr_ + before,
			 sizeof(value_type) * (size_ - before)
			);
			if (begin_ != 0) {
				alloc_.deallocate(begin_, capacity_);
			}
			size_     += n;
			arr_      = new_arr;
			begin_    = new_arr;
			capacity_ = new_capacity;

		}

		iterator erase(iterator position) {
			difference_type index = position - this->begin();

			if (size_ == 0) {
				return iterator(arr_ + index);
			}

			alloc_.destroy(arr_ + index);
			--size_;
			memmove
			(
			 arr_ + index,
			 arr_ + index + 1,
			 sizeof(value_type) * (size_ - index)
			);
			return iterator(arr_ + index);
		}

		iterator erase(iterator first, iterator last) {
			size_type start = first - this->begin();

			while (first != last) {
				this->erase(first);
				--last;
			}
			return iterator(arr_ + start);
		}

		void     swap (Vector & x) {
			ft::swap(arr_, x.arr_);
			ft::swap(begin_, x.begin_);
			ft::swap(size_, x.size_);
			ft::swap(capacity_, x.capacity_);
			ft::swap(alloc_, x.alloc_);
		}

		void     clear() {
			if (begin_ != 0) {
				for (size_type i = 0; i < size_; ++i) {
					alloc_.destroy(arr_ + i);
				}
			}
			size_ = 0;
		}

		// ---------------------------------------------------------------------

		// Allocator -----------------------------------------------------------

		allocator_type get_allocator() const {
			return alloc_;
		}

		// ---------------------------------------------------------------------

		// Exceptions ----------------------------------------------------------

		class OutOfRange : public std::exception {
		public:
			const char*  what() const throw() {
				return "vector";
			}
		};

		class LengthError : public std::exception {
			const char* what() const throw() {
				return "vector";
			}
		};

		// ---------------------------------------------------------------------

	private:
		pointer          arr_;
		pointer          begin_;
		size_type        size_;
		size_type        capacity_;
		allocator_type   alloc_;
  };

// ========================= END VECTOR CLASS ==================================

// Relational operators ========================================================

template <class T, class Alloc>
bool operator==(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
	return
	(
	 lhs.size() == rhs.size() &&
	 std::equal(lhs.begin(), lhs.end(), rhs.begin())
	);
}

template <class T, class Alloc>
bool operator!=(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
	return
	!(
	 lhs.size() == rhs.size() &&
	 std::equal(lhs.begin(), lhs.end(), rhs.begin())
	);
}

template <class T, class Alloc>
bool operator<(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
	return std::lexicographical_compare
	(
	 lhs.begin(),
	 lhs.end(),
	 rhs.begin(),
	 rhs.end()
	);
}

template <class T, class Alloc>
bool operator<=(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
	return !std::lexicographical_compare
	(
	 rhs.begin(),
	 rhs.end(),
	 lhs.begin(),
	 lhs.end()
	);
}

template <class T, class Alloc>
bool operator>(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
	return std::lexicographical_compare
	(
	 rhs.begin(),
	 rhs.end(),
	 lhs.begin(),
	 lhs.end()
	);
}

template <class T, class Alloc>
bool operator>=(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
	return !std::lexicographical_compare
	(
	 lhs.begin(),
	 lhs.end(),
	 rhs.begin(),
	 rhs.end()
	);
}

// =============================================================================

}

// ============================ END NAMESPACE FT ===============================

#endif /* FT_VECTOR_HPP */
