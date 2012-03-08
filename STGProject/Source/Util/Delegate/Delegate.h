#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Forward.h"
#include "Detail/StaticHolder.h"
#include "Detail/SharedPtrHolder.h"
#include "Detail/WeakPtrHolder.h"
#include "Detail/RawPtrHolder.h"
#include <memory>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Delegate
{
	template <class RetType>
	class Delegate0
	{
	public:
		Delegate0()
			: mpHolder()
		{}
		Delegate0( typename Detail::StaticHolder0<RetType>::StaticFunction f )
			: mpHolder( new Detail::StaticHolder0<RetType>( f ) )
		{}
		template <class ClassType>
		Delegate0( boost::shared_ptr<ClassType> p, 
			typename Detail::SharedPtrHolder0<ClassType, RetType>::ClassFunction f )
			: mpHolder( new Detail::SharedPtrHolder0<ClassType, RetType>( p, f ) )
		{}
		template <class ClassType>
		Delegate0( boost::weak_ptr<ClassType> p, 
			typename Detail::WeakPtrHolder0<ClassType, RetType>::ClassFunction f )
			: mpHolder( new Detail::WeakPtrHolder0<ClassType, RetType>( p, f ) )
		{}
		template <class ClassType>
		Delegate0( ClassType *p, 
			typename Detail::RawPtrHolder0<ClassType, RetType>::ClassFunction f )
			: mpHolder( new Detail::RawPtrHolder0<ClassType, RetType>( p, f ) )
		{}
		Delegate0( const Delegate0 &value )
			: mpHolder()
		{
			*this = value;
		}
		Delegate0 &operator = ( const Delegate0 &value )
		{
			mpHolder = value.mpHolder;

			return *this;
		}

		RetType Call() const
		{
			if( mpHolder )
			{
				return mpHolder->Call();
			}

			return RetType();
		}
		RetType operator () () const
		{
			return Call();
		}

		bool IsEmpty() const
		{
			return !mpHolder;
		}

		void Reset()
		{
			mpHolder.reset();
		}
		void Reset( typename Detail::StaticHolder0<RetType>::StaticFunction f )
		{
			mpHolder.reset( new Detail::StaticHolder0<RetType>( f ) );
		}
		template <class ClassType>
		void Reset( boost::shared_ptr<ClassType> p, 
			typename Detail::SharedPtrHolder0<ClassType, RetType>::ClassFunction f )
		{
			mpHolder.reset( new Detail::SharedPtrHolder0<ClassType, RetType>( p, f ) );
		}
		template <class ClassType>
		void Reset( boost::weak_ptr<ClassType> p, 
			typename Detail::WeakPtrHolder0<ClassType, RetType>::ClassFunction f )
		{
			mpHolder.reset( new Detail::WeakPtrHolder0<ClassType, RetType>( p, f ) );
		}
		template <class ClassType>
		void Reset( ClassType *p, 
			typename Detail::RawPtrHolder0<ClassType, RetType>::ClassFunction f )
		{
			mpHolder.reset( new Detail::RawPtrHolder0<ClassType, RetType>( p, f ) );
		}

	private:
		typename Ptr<Detail::IHolder0<RetType>>::Shared mpHolder;
	};

	template <class Arg1, class RetType>
	class Delegate1
	{
	public:
		Delegate1()
			: mpHolder()
		{}
		Delegate1( typename Detail::StaticHolder1<Arg1, RetType>::StaticFunction f )
			: mpHolder( new Detail::StaticHolder1<Arg1, RetType>( f ) )
		{}
		template <class ClassType>
		Delegate1( boost::shared_ptr<ClassType> p, 
			typename Detail::SharedPtrHolder1<ClassType, Arg1, RetType>::ClassFunction f )
			: mpHolder( new Detail::SharedPtrHolder1<ClassType, Arg1, RetType>( p, f ) )
		{}
		template <class ClassType>
		Delegate1( boost::weak_ptr<ClassType> p, 
			typename Detail::WeakPtrHolder1<ClassType, Arg1, RetType>::ClassFunction f )
			: mpHolder( new Detail::WeakPtrHolder1<ClassType, Arg1, RetType>( p, f ) )
		{}
		template <class ClassType>
		Delegate1( ClassType *p, 
			typename Detail::RawPtrHolder1<ClassType, Arg1, RetType>::ClassFunction f )
			: mpHolder( new Detail::RawPtrHolder1<ClassType, Arg1, RetType>( p, f ) )
		{}
		Delegate1( const Delegate1 &value )
			: mpHolder()
		{
			*this = value;
		}
		Delegate1 &operator = ( const Delegate1 &value )
		{
			mpHolder = value.mpHolder;

			return *this;
		}

		RetType Call( Arg1 arg1 ) const
		{
			if( mpHolder )
			{
				return mpHolder->Call( arg1 );
			}

			return RetType();
		}
		RetType operator () ( Arg1 arg1 ) const
		{
			return Call( arg1 );
		}

		bool IsEmpty() const
		{
			return !mpHolder;
		}

		void Reset()
		{
			mpHolder.reset();
		}
		void Reset( typename Detail::StaticHolder1<Arg1, RetType>::StaticFunction f )
		{
			mpHolder.reset( new Detail::StaticHolder1<Arg1, RetType>( f ) );
		}
		template <class ClassType>
		void Reset( boost::shared_ptr<ClassType> p, 
			typename Detail::SharedPtrHolder1<ClassType, Arg1, RetType>::ClassFunction f )
		{
			mpHolder.reset( new Detail::SharedPtrHolder1<ClassType, Arg1, RetType>( p, f ) );
		}
		template <class ClassType>
		void Reset( boost::weak_ptr<ClassType> p, 
			typename Detail::WeakPtrHolder1<ClassType, Arg1, RetType>::ClassFunction f )
		{
			mpHolder.reset( new Detail::WeakPtrHolder1<ClassType, Arg1, RetType>( p, f ) );
		}
		template <class ClassType>
		void Reset( ClassType *p, 
			typename Detail::RawPtrHolder1<ClassType, Arg1, RetType>::ClassFunction f )
		{
			mpHolder.reset( new Detail::RawPtrHolder1<ClassType, Arg1, RetType>( p, f ) );
		}

	private:
		typename Ptr<Detail::IHolder1<Arg1, RetType>>::Shared mpHolder;
	};

	template <class Arg1, class Arg2, class RetType>
	class Delegate2
	{
	public:
		Delegate2()
			: mpHolder()
		{}
		Delegate2( typename Detail::StaticHolder2<Arg1, Arg2, RetType>::StaticFunction f )
			: mpHolder( new Detail::StaticHolder2<Arg1, Arg2, RetType>( f ) )
		{}
		template <class ClassType>
		Delegate2( boost::shared_ptr<ClassType> p, 
			typename Detail::SharedPtrHolder2<ClassType, Arg1, Arg2, RetType>::ClassFunction f )
			: mpHolder( new Detail::SharedPtrHolder2<ClassType, Arg1, Arg2, RetType>( p, f ) )
		{}
		template <class ClassType>
		Delegate2( boost::weak_ptr<ClassType> p, 
			typename Detail::WeakPtrHolder2<ClassType, Arg1, Arg2, RetType>::ClassFunction f )
			: mpHolder( new Detail::WeakPtrHolder2<ClassType, Arg1, Arg2, RetType>( p, f ) )
		{}
		template <class ClassType>
		Delegate2( ClassType *p, 
			typename Detail::RawPtrHolder2<ClassType, Arg1, Arg2, RetType>::ClassFunction f )
			: mpHolder( new Detail::RawPtrHolder2<ClassType, Arg1, Arg2, RetType>( p, f ) )
		{}
		Delegate2( const Delegate2 &value )
			: mpHolder()
		{
			*this = value;
		}
		Delegate2 &operator = ( const Delegate2 &value )
		{
			mpHolder = value.mpHolder;

			return *this;
		}

		RetType Call( Arg1 arg1, Arg2 arg2 ) const
		{
			if( mpHolder )
			{
				return mpHolder->Call( arg1, arg2 );
			}

			return RetType();
		}
		RetType operator () ( Arg1 arg1, Arg2 arg2 ) const
		{
			return Call( arg1, arg2 );
		}

		bool IsEmpty() const
		{
			return !mpHolder;
		}

		void Reset()
		{
			mpHolder.reset();
		}
		void Reset( typename Detail::StaticHolder2<Arg1, Arg2, RetType>::StaticFunction f )
		{
			mpHolder.reset( new Detail::StaticHolder2<Arg1, Arg2, RetType>( f ) );
		}
		template <class ClassType>
		void Reset( boost::shared_ptr<ClassType> p, 
			typename Detail::SharedPtrHolder2<ClassType, Arg1, Arg2, RetType>::ClassFunction f )
		{
			mpHolder.reset( new Detail::SharedPtrHolder2<ClassType, Arg1, Arg2, RetType>( p, f ) );
		}
		template <class ClassType>
		void Reset( boost::weak_ptr<ClassType> p, 
			typename Detail::WeakPtrHolder2<ClassType, Arg1, Arg2, RetType>::ClassFunction f )
		{
			mpHolder.reset( new Detail::WeakPtrHolder2<ClassType, Arg1, Arg2, RetType>( p, f ) );
		}
		template <class ClassType>
		void Reset( ClassType *p, 
			typename Detail::RawPtrHolder2<ClassType, Arg1, Arg2, RetType>::ClassFunction f )
		{
			mpHolder.reset( new Detail::RawPtrHolder2<ClassType, Arg1, Arg2, RetType>( p, f ) );
		}

	private:
		typename Ptr<Detail::IHolder2<Arg1, Arg2, RetType>>::Shared mpHolder;
	};

	template <class Arg1, class Arg2, class Arg3, class RetType>
	class Delegate3
	{
	public:
		Delegate3()
			: mpHolder()
		{}
		Delegate3( typename Detail::StaticHolder3<Arg1, Arg2, Arg3, RetType>::StaticFunction f )
			: mpHolder( new Detail::StaticHolder3<Arg1, Arg2, Arg3, RetType>( f ) )
		{}
		template <class ClassType>
		Delegate3( boost::shared_ptr<ClassType> p, 
			typename Detail::SharedPtrHolder3<ClassType, Arg1, Arg2, Arg3, RetType>::ClassFunction f )
			: mpHolder( new Detail::SharedPtrHolder3<ClassType, Arg1, Arg2, Arg3, RetType>( p, f ) )
		{}
		template <class ClassType>
		Delegate3( boost::weak_ptr<ClassType> p, 
			typename Detail::WeakPtrHolder3<ClassType, Arg1, Arg2, Arg3, RetType>::ClassFunction f )
			: mpHolder( new Detail::WeakPtrHolder3<ClassType, Arg1, Arg2, Arg3, RetType>( p, f ) )
		{}
		template <class ClassType>
		Delegate3( ClassType *p, 
			typename Detail::RawPtrHolder3<ClassType, Arg1, Arg2, Arg3, RetType>::ClassFunction f )
			: mpHolder( new Detail::RawPtrHolder3<ClassType, Arg1, Arg2, Arg3, RetType>( p, f ) )
		{}
		Delegate3( const Delegate3 &value )
			: mpHolder()
		{
			*this = value;
		}
		Delegate3 &operator = ( const Delegate3 &value )
		{
			mpHolder = value.mpHolder;

			return *this;
		}

		RetType Call( Arg1 arg1, Arg2 arg2, Arg3 arg3 ) const
		{
			if( mpHolder )
			{
				return mpHolder->Call( arg1, arg2, arg3 );
			}

			return RetType();
		}
		RetType operator () ( Arg1 arg1, Arg2 arg2, Arg3 arg3 ) const
		{
			return Call( arg1, arg2, arg3 );
		}

		bool IsEmpty() const
		{
			return !mpHolder;
		}

		void Reset()
		{
			mpHolder.reset();
		}
		void Reset( typename Detail::StaticHolder3<Arg1, Arg2, Arg3, RetType>::StaticFunction f )
		{
			mpHolder.reset( new Detail::StaticHolder3<Arg1, Arg2, Arg3, RetType>( f ) );
		}
		template <class ClassType>
		void Reset( boost::shared_ptr<ClassType> p, 
			typename Detail::SharedPtrHolder3<ClassType, Arg1, Arg2, Arg3, RetType>::ClassFunction f )
		{
			mpHolder.reset( new Detail::SharedPtrHolder3<ClassType, Arg1, Arg2, Arg3, RetType>( p, f ) );
		}
		template <class ClassType>
		void Reset( boost::weak_ptr<ClassType> p, 
			typename Detail::WeakPtrHolder3<ClassType, Arg1, Arg2, Arg3, RetType>::ClassFunction f )
		{
			mpHolder.reset( new Detail::WeakPtrHolder3<ClassType, Arg1, Arg2, Arg3, RetType>( p, f ) );
		}
		template <class ClassType>
		void Reset( ClassType *p, 
			typename Detail::RawPtrHolder3<ClassType, Arg1, Arg2, Arg3, RetType>::ClassFunction f )
		{
			mpHolder.reset( new Detail::RawPtrHolder3<ClassType, Arg1, Arg2, Arg3, RetType>( p, f ) );
		}

	private:
		typename Ptr<Detail::IHolder3<Arg1, Arg2, Arg3, RetType>>::Shared mpHolder;
	};
}
}
}