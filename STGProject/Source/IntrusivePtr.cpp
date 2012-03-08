#include "PCH.h"


// intrusive_ptrの参照カウンタ操作用関数
void intrusive_ptr_add_ref( Selene::Interface *p )
{
	SAFE_ADDREF( p );
}
void intrusive_ptr_release( Selene::Interface *p )
{
	SAFE_RELEASE( p );
}