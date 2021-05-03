#ifndef FT_REVERSE_ITERATOR_HPP
# define FT_REVERSE_ITERATOR_HPP

namespace ft {

	template < class Iterator >
	class ReverseIterator {
	public:

		// Typedef -------------------------------------------------------------

		typedef Iterator                             iterator_type;
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type        value_type;
		typedef typename Iterator::difference_type   difference_type;
		typedef typename Iterator::pointer           pointer;
		typedef typename Iterator::reference         reference;

		// ---------------------------------------------------------------------

		// Constructor - Destructor --------------------------------------------

		ReverseIterator() : it_()
		{}
		explicit ReverseIterator(iterator_type it) : it_(it)
		{}
		template <class Iter>
		ReverseIterator(const ReverseIterator<Iter> & rev_it)
		: it_(rev_it.base())
		{}
		virtual ~ReverseIterator()
		{}

		// ---------------------------------------------------------------------

		// Member-funcs --------------------------------------------------------

		iterator_type base() const {
			return this->it_;
		}

		// ---------------------------------------------------------------------

		// Operators -----------------------------------------------------------

		// '='
		ReverseIterator & operator=(ReverseIterator const & x) {
			if (this == &x) {
				return *this;
			}
			this->it_ = x.base();
			return *this;
		}

		// '*'
		reference       operator*() {
			return *this->it_;
		}

		// '->'
		pointer         operator->() {
			return this->it_.get_pointer();
		}

		// '++iter'
		ReverseIterator operator++() {
			--this->it_;
			return (*this);
		}

		// 'iter++'
		ReverseIterator operator++(int) {
			ReverseIterator tmp(*this);
			--this->it_;
			return (tmp);
		}

		// '--iter'
		ReverseIterator operator--() {
			++this->it_;
			return (*this);
		}

		// 'iter--'
		ReverseIterator operator--(int) {
			ReverseIterator tmp(*this);
			++this->it_;
			return (tmp);
		}

		// '+'
		ReverseIterator operator+(difference_type n) const {
			return ReverseIterator(this->it_ - n);
		}

		// '-'
		ReverseIterator operator-(difference_type n) const {
			return (ReverseIterator(this->it_ + n));
		}

		// '+='
		ReverseIterator &operator+=(difference_type n) {
			this->it_ -= n;
			return (*this);
		}

		// '-='
		ReverseIterator &operator-=(difference_type n) {
			this->it_ += n;
			return (*this);
		}

		// '<'
		bool            operator<(ReverseIterator const & x) const {
			return this->it_ > x.base();
		}

		// '>'
		bool            operator>(ReverseIterator const & x) const {
			return this->it_ < x.base();
		}

		// '>='
		bool            operator<=(ReverseIterator const & x) const {
			return this->it_ >= x.base();
		}

		// '>='
		bool            operator>=(ReverseIterator const & x) const {
			return this->it_ <= x.base();
		}

		reference       operator[](difference_type index) {
			return this->it_[-index];
		}

		// ---------------------------------------------------------------------

	private:
		iterator_type it_;
	};

	// Relational Operators ----------------------------------------------------

	// 'n + iter'
	template < class Iterator >
	ReverseIterator<Iterator> operator+
	(
	 typename ReverseIterator<Iterator>::difference_type n,
	 ReverseIterator<Iterator> const & x
	)
	{
		return x + n;
	}

	// // 'iter - iter'
	template < class Iterator >
	typename ReverseIterator<Iterator>::difference_type operator-
	(
	 ReverseIterator<Iterator> const & a,
	 ReverseIterator<Iterator> const & b
	)
	{
		return b.base() - a.base();
	}

	template<class lIterator, class rIterator>
	bool operator>
	(
	 const ReverseIterator<lIterator> & a,
	 const ReverseIterator<rIterator> & b
	)
	{
		return a.base() > b.base();
	}

	template<class lIterator, class rIterator>
	bool operator>=
	(
	 const ReverseIterator<lIterator> & a,
	 const ReverseIterator<rIterator> & b
	)
	{
		return a.base() >= b.base();
	}

	template<class lIterator, class rIterator>
	bool operator<
	(
	 const ReverseIterator<lIterator> & a,
	 const ReverseIterator<rIterator> & b
	)
	{
		return a.base() < b.base();
	}

	template<class lIterator, class rIterator>
	bool operator<=
	(
	 const ReverseIterator<lIterator> & a,
	 const ReverseIterator<rIterator> & b
	)
	{
		return a.base() <= b.base();
	}

	template<class lIterator, class rIterator>
	bool operator==
	(
	 const ReverseIterator<lIterator> & a,
	 const ReverseIterator<rIterator> & b
	)
	{
		return a.base() == b.base();
	}

	template<class lIterator, class rIterator>
	bool operator!=
	(
	 const ReverseIterator<lIterator> & a,
	 const ReverseIterator<rIterator> & b
	)
	{
		return a.base() != b.base();
	}

	// -------------------------------------------------------------------------
}

#endif /* FT_REVERSE_ITERATOR_HPP */
