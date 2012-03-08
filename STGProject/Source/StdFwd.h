#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace std
{
	// TEMPLATE CLASS basic_string
	template<class _Elem, class _Traits, class _Ax>
	class basic_string;

	// TEMPLATE STRUCT char_traits
	template<class _Elem>
	struct char_traits;

	// TEMPLATE CLASS allocator
	template<class _Ty>
	class allocator;

	typedef basic_string<char, char_traits<char>, allocator<char> > 
		string;
	typedef basic_string<wchar_t, char_traits<wchar_t>, 
		allocator<wchar_t> > wstring;

	// TEMPLATE STRUCT less
	template<class _Ty>
	struct less;

	// TEMPLATE STRUCT pair
	template<class _Ty1, class _Ty2>
	struct pair;

	// TEMPLATE CLASS map
	//template<class _Kty, class _Ty, class _Pr = less<_Kty>, 
	//class _Alloc = allocator<pair<const _Kty, _Ty> > >
	//class map;
	template<class _Kty, class _Ty, class _Pr, class _Alloc>
	class map;

	// TEMPLATE CLASS multimap
	//template<class _Kty, class _Ty, class _Pr = less<_Kty>, 
	//class _Alloc = allocator<pair<const _Kty, _Ty> > >
	//class multimap;
	template<class _Kty, class _Ty, class _Pr, class _Alloc>
	class multimap;

	// TEMPLATE CLASS set
	//template<class _Kty, class _Pr = less<_Kty>, 
	//class _Alloc = allocator<_Kty> >
	//class set;
	template<class _Kty, class _Pr, class _Alloc>
	class set;

	// TEMPLATE CLASS multiset
	//template<class _Kty, class _Pr = less<_Kty>, 
	//class _Alloc = allocator<_Kty> >
	//class multiset;
	template<class _Kty, class _Pr, class _Alloc>
	class multiset;

	// TEMPLATE CLASS list
	//template<class _Ty, class _Ax = allocator<_Ty> >
	//class list;
	template<class _Ty, class _Ax>
	class list;

	// TEMPLATE CLASS vector
	//template<class _Ty, 
	//class _Ax = allocator<_Ty> >
	//class vector;
	template<class _Ty, class _Ax>
	class vector;

	// TEMPLATE CLASS deque
	//template<class _Ty, 
	//class _Ax = allocator<_Ty> >
	//class deque;
	template<class _Ty, class _Ax>
	class deque;

	// TEMPLATE CLASS queue
	//template<class _Ty, class _Container = deque<_Ty> >
	//class queue;
	template<class _Ty, class _Container>
	class queue;

	// TEMPLATE CLASS stack
	//template<class _Ty, class _Container = deque<_Ty> >
	//class stack;
	template<class _Ty, class _Container>
	class stack;

	namespace tr1
	{
		// TEMPLATE CLASS shared_ptr
		template<class _Ty>
		class shared_ptr;

		// TEMPLATE CLASS weak_ptr
		template<class _Ty>
		class weak_ptr;

		// TEMPLATE STRUCT equal_to
		template<class _Ty>
		struct equal_to;

		// TEMPLATE CLASS unordered_set
		//template<class _Kty, 
		//class _Hasher = std::tr1::hash<_Kty>, 
		//class _Keyeq = std::equal_to<_Kty>, 
		//class _Alloc = std::allocator<_Kty> >
		//class unordered_set;
		template<class _Kty, class _Hasher, class _Keyeq, class _Alloc>
		class unordered_set;

		// TEMPLATE CLASS unordered_map
		//template<class _Kty, 
		//class _Ty, 
		//class _Hasher = std::tr1::hash<_Kty>, 
		//class _Keyeq = std::equal_to<_Kty>, 
		//class _Alloc = std::allocator<std::pair<const _Kty, _Ty> > >
		//class unordered_map;
		template<class _Kty, class _Ty, class _Hasher, class _Keyeq, class _Alloc>
		class unordered_map;
	}

	// TEMPLATE CLASS hash
	template<class _Kty>
	class hash;
}