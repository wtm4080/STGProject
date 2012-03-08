#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#pragma warning(disable:4819)

#include <boost/function/function_fwd.hpp>
#include <boost/functional/hash_fwd.hpp>
#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/pool/poolfwd.hpp>
#include <boost/variant/variant_fwd.hpp>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace boost
{
	class bad_any_cast;
	class any;

	class exception;

	template<class T> 
	class scoped_ptr;
	template<class T> 
	class scoped_array;

	template<class T> 
	class shared_ptr;
	template<class T> 
	class shared_array;

	template<class T> 
	class weak_ptr;

	template<class T> 
	class intrusive_ptr;
}


//----------------------------------------------------------------------------------
//	Function
//----------------------------------------------------------------------------------

// intrusive_ptrの参照カウンタ操作用関数
void intrusive_ptr_add_ref( Selene::Interface *p );
void intrusive_ptr_release( Selene::Interface *p );