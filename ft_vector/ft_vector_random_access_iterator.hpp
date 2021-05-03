#ifndef FT_RANDOM_ACCESS_ITERATOR
# define FT_RANDOM_ACCESS_ITERATOR

// ============================ STD-LIBS =======================================

# include <cstddef>   // size_t, ptrdiff_t ...

// =============================================================================


namespace ft {

// ===================== VECTOR RADOM ACCESS ITERATOR ==========================

	template < class T, class P, class R >
	class VectorRandomAccessIterator {
	public:

		// Typedef -------------------------------------------------------------

		typedef ptrdiff_t                           difference_type;
		typedef T                                   value_type;
		typedef P                                   pointer;
		typedef R                                   reference;
		typedef std::random_access_iterator_tag     iterator_category;

		typedef VectorRandomAccessIterator<T, P, R> this_type;

		// ---------------------------------------------------------------------

		// Constructor - Destructor --------------------------------------------

		VectorRandomAccessIterator() : arr_(0)
		{}
		VectorRandomAccessIterator(pointer arr) : arr_(arr)
		{}
		VectorRandomAccessIterator
		(
		 VectorRandomAccessIterator<T, T*, T&> const & x
		)
		: arr_(x.get_pointer())
		{}
		virtual ~VectorRandomAccessIterator()
		{}

		// ---------------------------------------------------------------------

		// Operators -----------------------------------------------------------

		// '='
		this_type & operator=(this_type const & x) {
			if (this == &x)
				return *this;
			this->arr_ = x.arr_;
			return *this;
		}

		// '*'
		reference   operator*() {
			return *this->arr_;
		}

		// '->'
		pointer     operator->() {
			return this->arr_;
		}

		// '++iter'
		this_type   operator++() {
			++this->arr_;
			return (*this);
		}

		// 'iter++'
		this_type   operator++(int) {
			this_type tmp(*this);
			++this->arr_;
			return (tmp);
		}

		// '--iter'
		this_type   operator--() {
			--this->arr_;
			return (*this);
		}

		// 'iter--'
		this_type   operator--(int) {
			this_type tmp(*this);
			--this->arr_;
			return (tmp);
		}

		// '+'
		this_type   operator+(difference_type n) const {
			return (this_type(this->arr_ + n));
		}

		// '-'
		this_type   operator-(difference_type n) const {
			return (this_type(this->arr_ - n));
		}

		// '+='
		this_type & operator+=(difference_type n) {
			this->arr_ += n;
			return (*this);
		}

		// '-='
		this_type & operator-=(difference_type n) {
			this->arr_ -= n;
			return (*this);
		}

		reference   operator[](difference_type index) {
			return this->arr_[index];
		}

		// ---------------------------------------------------------------------

		// GETTERS -------------------------------------------------------------

		pointer get_pointer() const {
			return this->arr_;
		}

		// ---------------------------------------------------------------------

	private:
		pointer arr_;

	};

// =================== END VECTOR RADOM ACCESS ITERATOR ========================

	// Relational Operators ----------------------------------------------------

	// 'n + iter'
	template <class T, class P, class R>
	VectorRandomAccessIterator<T, P, R> operator+
	(
	 typename VectorRandomAccessIterator<T, P, R>::difference_type n,
	 VectorRandomAccessIterator<T, P, R> const & x
	)
	{
		return x + n;
	}

	 // 'iter - iter'
	template <class T, class P, class R>
	typename VectorRandomAccessIterator<T, P, R>::difference_type operator-
	(
	 VectorRandomAccessIterator<T, P, R> const & a,
	 VectorRandomAccessIterator<T, P, R> const & b
	)
	{
		return a.get_pointer() - b.get_pointer();
	}

	// 'iter > iter'
	template <class lT, class lP, class lR, class rT, class rP, class rR>
	bool operator>
	(
	 const VectorRandomAccessIterator<lT, lP, lR> & a,
	 const VectorRandomAccessIterator<rT, rP, rR> & b
	)
	{
		return a.get_pointer() > b.get_pointer();
	}

	// 'iter >= iter'
	template <class lT, class lP, class lR, class rT, class rP, class rR>
	bool operator>=
	(
	 const VectorRandomAccessIterator<lT, lP, lR> & a,
	 const VectorRandomAccessIterator<rT, rP, rR> & b
	)
	{
		return a.get_pointer() >= b.get_pointer();
	}

	// 'iter < iter'
	template <class lT, class lP, class lR, class rT, class rP, class rR>
	bool operator<
	(
	 const VectorRandomAccessIterator<lT, lP, lR> & a,
	 const VectorRandomAccessIterator<rT, rP, rR> & b
	)
	{
		return a.get_pointer() < b.get_pointer();
	}

	// 'iter <= iter'
	template <class lT, class lP, class lR, class rT, class rP, class rR>
	bool operator<=
	(
	 const VectorRandomAccessIterator<lT, lP, lR> & a,
	 const VectorRandomAccessIterator<rT, rP, rR> & b
	)
	{
		return a.get_pointer() <= b.get_pointer();
	}

	// 'iter == iter'
	template <class lT, class lP, class lR, class rT, class rP, class rR>
	bool operator==
	(
	 const VectorRandomAccessIterator<lT, lP, lR> & a,
	 const VectorRandomAccessIterator<rT, rP, rR> & b
	)
	{
		return a.get_pointer() == b.get_pointer();
	}

	// 'iter != iter'
	template <class lT, class lP, class lR, class rT, class rP, class rR>
	bool operator!=
	(
	 const VectorRandomAccessIterator<lT, lP, lR> & a,
	 const VectorRandomAccessIterator<rT, rP, rR> & b
	)
	{
		return a.get_pointer() != b.get_pointer();
	}

	// -------------------------------------------------------------------------

}

// ============================================================================

#endif /* FT_VECTOR_HPP */
