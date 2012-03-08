#include "PCH.h"
#include "Pause.h"

#include "View/STG/Pause/IPause.h"

using namespace Game;
using namespace Ctrl::STG;


// コンストラクタ
Pause::Pause( const UpdateFunc &func, PView pView )
: mpView( pView )
, mUpdateFunc( func )
{
}


// 更新関数
bool Pause::Update()
{
	mUpdateFunc();

	if( !mpView->Update() )
	{
		mpView->Draw();

		Util::Sprite::Manager::StartShake();
		return false;
	}
	else
	{
		mpView->Draw();
	}

	return true;
}

bool Pause::Update_Continue()
{
	mUpdateFunc();

	if( !mpView->Update_Continue() )
	{
		mpView->Draw_Continue();

		Util::Sprite::Manager::StartShake();
		return false;
	}
	else
	{
		mpView->Draw_Continue();
	}

	return true;
}