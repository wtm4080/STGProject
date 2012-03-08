#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Defs/Mdl/STG/Bullet/Base.h"
#include "Util/STG/Locator/Linear.h"
#include <bulletmlrunner.h>
#include "CreateParam.h"
#include <list>
#include "Defs/Mdl/STG/Bullet/BulletDefs.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Mdl
{
namespace STG
{
namespace Bullet
{
namespace BulletML
{
	class MLActor
		: public Base
		, public BulletMLRunner
	{
	public:
		// コンストラクタ
		typedef Game::Util::Ptr<BulletMLParser>::Shared PBMLParser;
		typedef Game::Util::Sprite::DrawParameter DrawParameter;
		MLActor( PBMLParser bp, 
			const Game::Util::STG::Vector2DF &pos );
		MLActor( PBMLParser bp, 
			const Game::Util::STG::Locator::LinearF &locator, int hitRadius, 
			const DrawParameter &drawParam );

		// 位置の取得
		virtual Game::Util::STG::Vector2DF GetPosition() const;
		// 外力の適用
		virtual Game::Util::STG::Vector2DF ApplyExternalForce( 
			const Game::Util::STG::Vector2DF &vec );

		// ロケータの取得
		Game::Util::STG::Locator::LinearF &GetLocator();
		// 描画パラメータの取得
		const DrawParameter &GetDrawParameter() const;
		// 描画パラメータの設定
		void SetDrawParameter( const DrawParameter &drawParam );
		// ランクの取得
		double GetRank() const;
		// ランクの設定
		static const double DEFAULT_RANK;
		void SetRank( double rank );
		// 弾生成時パラメータリストの取得
		typedef std::list<CreateParam> CreateParamList;
		CreateParamList &GetCreateParamList();
		CreateParamList::iterator GetCreateParamListBegin() { return mCreateParamList.begin(); }
		CreateParamList::iterator GetCreateParamListEnd() { return mCreateParamList.end(); }
		void AddCreateParam( const CreateParam &param ) { mCreateParamList.push_back( param ); }

	private:
		Game::Util::STG::Locator::LinearF mLocator;
		DrawParameter mDrawParam;
		double mRank;
		int mFrameCount;
		CreateParamList mCreateParamList;
		float mAngle;
		PBMLParser mpBMLParser;

		MLActor( PBMLParser bp, BulletMLState *bs, 
			const Game::Util::STG::Locator::LinearF &locator, int hitRadius, 
			const DrawParameter &drawParam, 
			const CreateParamList &createParamList, 
			float angle );

		friend BulletDefs;

	protected:
		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnDestruct();
		virtual void OnDestruct( float hp );
		virtual void OnErase();

	private:
		/// この弾の角度を求める
		// 角度を度単位で、上方向 0 で時計周りで返す
		virtual double getBulletDirection();
		/// この弾から自機を狙う角度を求める
		// 角度を度単位で、上方向 0 で時計周りで返す
		virtual double getAimDirection();
		/// この弾の速度を求める
		virtual double getBulletSpeed();
		/// デフォルトの速度を求める
		virtual double getDefaultSpeed();
		/// ランクを求める
		// 0 から 1 までの実数
		virtual double getRank();
		/// action を持たない弾を作る
		virtual void createSimpleBullet( double direction, double speed );
		/// action を持つ弾を作る
		virtual void createBullet( BulletMLState *state, 
			double direction, double speed );
		/// 弾の基準となるターンの値を返す、通常はフレーム数
		virtual int getTurn();
		/// 死ぬ
		virtual void doVanish();
		/// 弾の方向を指定した方向に変更する
		virtual void doChangeDirection( double dir );
		/// 弾の速度を指定した値に変更する
		virtual void doChangeSpeed( double speed );
		/// accel に対するインターフェイス
		virtual void doAccelX( double accelX );
		virtual void doAccelY( double accelY );
		/// 弾の速さの X 方向成分を返します
		virtual double getBulletSpeedX();
		/// 弾の速さの Y 方向成分を返します
		virtual double getBulletSpeedY();
		/// 乱数を返す
		virtual double getRand();
	};
}
}
}
}
}