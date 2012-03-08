#pragma once


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace View
{
namespace STG
{
	// 描画優先度
	enum DRAW_PRIORITY
	{
		// 背景
		PRI_BACKGROUND_B3, 
		PRI_BACKGROUND_B2, 
		PRI_BACKGROUND_B1, 
		PRI_BACKGROUND, 
		PRI_BACKGROUND_2, 
		PRI_BACKGROUND_3, 
		PRI_BACKGROUND_4, 

		// 敵
		PRI_ENEMY_B3, 
		PRI_ENEMY_B2, 
		PRI_ENEMY_B1, 
		PRI_ENEMY, 
		PRI_ENEMY_2, 
		PRI_ENEMY_3, 
		PRI_ENEMY_4, 

		// スコア倍率表示
		PRI_SCORE_RATE, 
		PRI_SCORE_RATE_2, 
		PRI_SCORE_RATE_3, 

		// 自機オプション
		PRI_MYSHIP_OPTION_B3, 
		PRI_MYSHIP_OPTION_B2, 
		PRI_MYSHIP_OPTION_B1, 
		PRI_MYSHIP_OPTION, 
		PRI_MYSHIP_OPTION_2, 
		PRI_MYSHIP_OPTION_3, 
		PRI_MYSHIP_OPTION_4, 

		// 自機ショット
		PRI_MYSHOT_B3, 
		PRI_MYSHOT_B2, 
		PRI_MYSHOT_B1, 
		PRI_MYSHOT, 
		PRI_MYSHOT_2, 
		PRI_MYSHOT_3, 
		PRI_MYSHOT_4, 

		// アイテム
		PRI_ITEM_B3, 
		PRI_ITEM_B2, 
		PRI_ITEM_B1, 
		PRI_ITEM, 
		PRI_ITEM_2, 
		PRI_ITEM_3, 
		PRI_ITEM_4, 

		// 敵へのロックマーカー
		PRI_LOCKMARKER_B3, 
		PRI_LOCKMARKER_B2, 
		PRI_LOCKMARKER_B1, 
		PRI_LOCKMARKER, 
		PRI_LOCKMARKER_2, 
		PRI_LOCKMARKER_3, 
		PRI_LOCKMARKER_4, 

		// 自機
		PRI_MYSHIP_B3, 
		PRI_MYSHIP_B2, 
		PRI_MYSHIP_B1, 
		PRI_MYSHIP, 
		PRI_MYSHIP_2, 
		PRI_MYSHIP_3, 
		PRI_MYSHIP_4, 
		// 自機バリア
		PRI_MYBARRIER, 

		// PrimalArmorのエフェクト
		PRI_PA_EFFECT, 
		// 爆発エフェクト
		PRI_EXPLOSION, 

		// 敵弾
		PRI_ENEMYBULLET_B3, 
		PRI_ENEMYBULLET_B2, 
		PRI_ENEMYBULLET_B1, 
		PRI_ENEMYBULLET, 
		PRI_ENEMYBULLET_2, 
		PRI_ENEMYBULLET_3, 
		PRI_ENEMYBULLET_4, 
		// 敵弾ダメージ時のエフェクト
		PRI_ENEMYBULLET_DAMAGED, 

		// 自機の当たり判定の目印
		PRI_MYSHIP_HITMARK, 

		// 敵HPゲージ
		PRI_ENEMY_HPGAUGE, 

		// Warning表示
		PRI_WARNING, 

		// Result表示
		PRI_RESULT_B3, 
		PRI_RESULT_B2, 
		PRI_RESULT_B1, 
		PRI_RESULT, 
		PRI_RESULT_2, 
		PRI_RESULT_3, 
		PRI_RESULT_4, 

		// 情報表示領域の背景
		PRI_INFAREA_BACK_B3, 
		PRI_INFAREA_BACK_B2, 
		PRI_INFAREA_BACK_B1, 
		PRI_INFAREA_BACK, 
		PRI_INFAREA_BACK_2, 
		PRI_INFAREA_BACK_3, 
		PRI_INFAREA_BACK_4, 
		// 情報表示領域の文字列
		PRI_INFAREA_STR, 

		// ポーズ画面の背景
		PRI_PAUSE_BACK_B3, 
		PRI_PAUSE_BACK_B2, 
		PRI_PAUSE_BACK_B1, 
		PRI_PAUSE_BACK, 
		PRI_PAUSE_BACK_2, 
		PRI_PAUSE_BACK_3, 
		PRI_PAUSE_BACK_4, 
		// ポーズ画面の文字列
		PRI_PAUSE_STR, 

		// フェードイン/アウト用
		PRI_FADE_EFFECT, 

		// デバッグ用文字列
		PRI_DEBUG_STR, 
	};
}
}
}