'''
Created on 2011/03/04

@author: t

このモジュールでは、ゲームを実現するうえで基本となる機能を提供します。
'''

import Game


ColorF = Game.ColorF
ColorF.__doc__ = """
色を表現するクラス

色をRGBAで表現します。
各要素の範囲は、[0, 1]です。
演算子は、+, -, *, /, +=, -=, *=, /=, ==, != が定義されています。

@ivar r: R要素
@ivar g: G要素
@ivar b: B要素
@ivar a: A要素
"""

ColorF.__init__.__doc__ = """
コンストラクタ

__init__( (object)self) -> None :
	'''
	各要素を1で初期化します
	
	  C++ signature :
		  void __init__(struct _object * __ptr64)
	'''

__init__( (object)self, (float)r[, (float)g[, (float)b[, (float)a]]]) -> None :
	'''
	各要素を指定した値で初期化します
	
	@param r: 赤
	@param g: 緑
	@param b: 青
	@param a: アルファ値
	
	  C++ signature :
		  void __init__(
		  struct _object * __ptr64,
		  float,float,float,float)
	'''

__init__( (object)self, (ColorF)color) -> None :
	'''
	色を表現する他のオブジェクトで初期化します
	
	@param color: 他のオブジェクト
	
	  C++ signature :
		  void __init__(
		  struct _object * __ptr64,
		  struct Selene::ColorF)
	'''
"""


Point2DF = Game.Point2DF
Point2DF.__doc__ = """
２次元の座標を示すクラス

各種演算子を備えた、2次元の座標を示すクラスです。
各座標は浮動小数点数で表現されます。
演算子は、+, -, *, /, +=, -=, *=, /= が定義されています。

@ivar x: X座標
@ivar y: Y座標
"""

Point2DF.__init__.__doc__ = """
コンストラクタ

__init__( (object)self) -> None :
	'''
	座標を0で初期化します
	
	  C++ signature :
		  void __init__(struct _object * __ptr64)
	'''

__init__( (object)self, (float)x, (float)y) -> None :
	'''
	座標を引数のX座標とY座標で初期化します
	
	@param x: X座標
	@param y: Y座標
	
	  C++ signature :
		  void __init__(struct _object * __ptr64,float,float)
	'''

__init__( (object)self, (Point2DF | Point2DI)point) -> None :
	'''
	座標を他の2次元座標オブジェクトで初期化します
	
	@param point: 他の2次元座標オブジェクト
	
	  C++ signature :
		  void __init__(
		  struct _object * __ptr64,
		  (class Selene::Point2D<float> | class Selene::Point2D<long>))
	'''
"""

Point2DF.limitLength.__doc__ = """
原点からの長さをある範囲内に収まるようにした座標を取得します

limitLength( (Point2DF)self, (float)limit) -> Point2DF :

@param limit: 制限値
@return: 制限された座標

  C++ signature :
	  class Selene::Point2D<float> limitLength(
	  class Selene::Point2D<float> {lvalue},
	  float)
"""

Point2DF.normalize.__doc__ = """
長さを1になるように正規化した座標を取得します

normalize( (Point2DF)self) -> Point2DF :

@return: 正規化された座標

  C++ signature :
	  class Selene::Point2D<float> normalize(class Selene::Point2D<float> {lvalue})
"""


Point2DI = Game.Point2DI
Point2DI.__doc__ = """
２次元の座標を示すクラス

各種演算子を備えた、2次元の座標を示すクラスです。
各座標は整数で表現されます。
演算子は、+, -, *, /, +=, -=, *=, /= が定義されています。

@ivar x: X座標
@ivar y: Y座標
"""

Point2DI.__init__.__doc__ = """
コンストラクタ

__init__( (object)self) -> None :
	'''
	座標を0で初期化します
	
	  C++ signature :
		  void __init__(struct _object * __ptr64)
	'''

__init__( (object)self, (int)x, (int)y) -> None :
	'''
	座標を引数のX座標とY座標で初期化します
	
	@param x: X座標
	@param y: Y座標
	
	  C++ signature :
		  void __init__(
		  struct _object * __ptr64,
		  long,
		  long)
	'''

__init__( (object)self, (Point2DI | Point2DF)point) -> None :
	'''
	座標を他の2次元座標オブジェクトで初期化します
	
	@param point: 他の2次元座標オブジェクト
	
	  C++ signature :
		  void __init__(
		  struct _object * __ptr64,
		  (class Selene::Point2D<long> | class Selene::Point2D<float>))
	'''
"""

Point2DI.limitLength.__doc__ = """
原点からの長さをある範囲内に収まるようにした座標を取得します

limitLength( (Point2DI)self, (float)limit) -> Point2DI :

@param limit: 制限値
@return: 制限された座標

  C++ signature :
	  class Selene::Point2D<long> limitLength(
	  class Selene::Point2D<long> {lvalue},
	  float)
"""

Point2DI.normalize.__doc__ = """
長さを1になるように正規化した座標を取得します

normalize( (Point2DI)self) -> Point2DI :

@return: 正規化された座標

  C++ signature :
	  class Selene::Point2D<long> normalize(class Selene::Point2D<long> {lvalue})
"""


RectF = Game.RectF
RectF.__doc__ = """
矩形を表現するクラス

左上のXY座標と、幅と高さで矩形を表現します。
XY座標と幅と高さは浮動小数点数で表現されます。

@ivar x: 左上のX座標
@ivar y: 左上のY座標
@ivar w: 幅
@ivar h: 高さ
"""

RectF.__init__.__doc__ = """
コンストラクタ

__init__( (object)self) -> None :
	'''
	  C++ signature :
		  void __init__(struct _object * __ptr64)
	'''

__init__( (object)self, (float)x, (float)y, (float)w, (float)h) -> None :
	'''
	XY座標と幅と高さを指定して初期化します
	
	@param x: X座標
	@param y: Y座標
	@param w: 幅
	@param h: 高さ
	
	  C++ signature :
		  void __init__(struct _object * __ptr64,float,float,float,float)
	'''

__init__( (object)self, (RectF | RectI)rect) -> None :
	'''
	他の矩形オブジェクトで初期化します
	
	@param rect: 他の矩形オブジェクト
	
	  C++ signature :
		  void __init__(
		  struct _object * __ptr64,
		  (class Selene::Rect<float> | class Selene::Rect<long>))
	'''
"""

RectF.getPosition.__doc__ = """
左上の座標を取得します

getPosition( (RectF)self) -> Point2DF :

@return: 座標オブジェクト

  C++ signature :
	  class Selene::Point2D<float> getPosition(class Selene::Rect<float> {lvalue})
"""

RectF.getLocalPosition.__doc__ = """
左上のローカル座標を取得します

getLocalPosition( (RectF)self, (Point2DF)position) -> Point2DF :

@param position: ローカル座標
@return: 座標オブジェクト

  C++ signature :
	  class Selene::Point2D<float> getLocalPosition(
	  class Selene::Rect<float> {lvalue},
	  class Selene::Point2D<float>)
"""

RectF.getSize.__doc__ = """
幅と高さを取得します

getSize( (RectF)self) -> Point2DF :

@return: 幅と高さ

  C++ signature :
	  class Selene::Point2D<float> getSize(class Selene::Rect<float> {lvalue})
"""

RectF.clip.__doc__ = """
指定した矩形で切り抜いた矩形を取得します

clip( (RectF)self, (RectF)rect) -> RectF :

@param rect: 切り抜く矩形領域
@return: 切り抜かれた矩形領域

  C++ signature :
	  class Selene::Rect<float> clip(
	  class Selene::Rect<float> {lvalue},
	  class Selene::Rect<float>)
"""

RectF.checkHit.__doc__ = """
指定した座標が矩形内にあるか判定します

checkHit( (RectF)self, (Point2DF)position) -> bool :

@param position: 判定する座標
@return: TrueまたはFalse

  C++ signature :
	  bool checkHit(
	  class Selene::Rect<float> {lvalue},
	  class Selene::Point2D<float>)
"""

RectF.scaleByCenter.__doc__ = """
矩形の中心を基準として、指定した値でスケーリングした矩形を取得します

scaleByCenter( (RectF)self, (float)scaling) -> RectF :

@param scaling: スケーリング量
@return: スケーリングされた矩形領域

  C++ signature :
	  class Selene::Rect<float> scaleByCenter(
	  class Selene::Rect<float> {lvalue},
	  float)
"""


RectI = Game.RectI
RectI.__doc__ = """
矩形を表現するクラス

左上のXY座標と、幅と高さで矩形を表現します。
XY座標と幅と高さは整数で表現されます。

@ivar x: 左上のX座標
@ivar y: 左上のY座標
@ivar w: 幅
@ivar h: 高さ
"""

RectI.__init__.__doc__ = """
コンストラクタ

__init__( (object)self) -> None :
	'''
	各要素を0で初期化します
	
	  C++ signature :
		  void __init__(struct _object * __ptr64)
	'''

__init__( (object)self, (int)x, (int)y, (int)w, (int)h) -> None :
	'''
	XY座標と幅と高さを指定して初期化します
	
	@param x: X座標
	@param y: Y座標
	@param w: 幅
	@param h: 高さ
	
	  C++ signature :
		  void __init__(struct _object * __ptr64,long,long,long,long)
	'''

__init__( (object)self, (RectI | RectF)rect) -> None :
	'''
	他の矩形オブジェクトで初期化します
	
	@param rect: 他の矩形オブジェクト
	
	  C++ signature :
		  void __init__(
		  struct _object * __ptr64,
		  (class Selene::Rect<long> | class Selene::Rect<float>))
	'''
"""

RectI.getPosition.__doc__ = """
左上の座標を取得します

getPosition( (RectI)self) -> Point2DI :

@return: 座標オブジェクト

  C++ signature :
	  class Selene::Point2D<long> getPosition(class Selene::Rect<long> {lvalue})
"""

RectI.getLocalPosition.__doc__ = """
左上のローカル座標を取得します

getLocalPosition( (RectI)self, (Point2DI)position) -> Point2DI :

@param position: ローカル座標
@return: 座標オブジェクト

  C++ signature :
	  class Selene::Point2D<long> getLocalPosition(
	  class Selene::Rect<long> {lvalue},
	  class Selene::Point2D<long>)
"""

RectI.getSize.__doc__ = """
幅と高さを取得します

getSize( (RectI)self) -> Point2DI :

@return: 幅と高さ

  C++ signature :
	  class Selene::Point2D<long> getSize(class Selene::Rect<long> {lvalue})
"""

RectI.clip.__doc__ = """
指定した矩形で切り抜いた矩形を取得します

clip( (RectI)self, (RectI)rect) -> RectI :

@param rect: 切り抜く矩形領域
@return: 切り抜かれた矩形領域

  C++ signature :
	  class Selene::Rect<long> clip(
	  class Selene::Rect<long> {lvalue},
	  class Selene::Rect<long>)
"""

RectI.checkHit.__doc__ = """
指定した座標が矩形内にあるか判定します

checkHit( (RectI)self, (Point2DI)position) -> bool :

@param position: 判定する座標
@return: TrueまたはFalse

  C++ signature :
	  bool checkHit(
	  class Selene::Rect<long> {lvalue},
	  class Selene::Point2D<long>)
"""

RectI.scaleByCenter.__doc__ = """
矩形の中心を基準として、指定した値でスケーリングした矩形を取得します

scaleByCenter( (RectI)self, (int)scaling) -> RectI :

@param scaling: スケーリング量
@return: スケーリングされた矩形領域

  C++ signature :
	  class Selene::Rect<long> scaleByCenter(
	  class Selene::Rect<long> {lvalue},
	  long)
"""


ArrowLocator = Game.ArrowLocator
ArrowLocator.__doc__ = """
項目を選択する矢印を管理するクラス

何らかの選択項目を指し示す矢印またはそれに準ずるものを管理するクラスです。

@ivar position: 矢印の位置
@ivar top: 最上項目の位置
@ivar bottom: 最下項目の位置
@ivar horizontal: 水平モード
@ivar repeatWait: 入力リピートの待ち間隔
@ivar repeatInterval: 入力リピートの間隔
@ivar controller: 入力コントローラー
"""

ArrowLocator.__init__.__doc__ = """
コンストラクタ

__init__( (object)self, (int)initialArrowPos, (int)top, (int)bottom[, (bool)loop[, (bool)horizontal]]) -> None :
	'''
	初期位置と、最上項目と最下項目と、最上と最下のループと、水平モードにするかを指定して初期化します
	
	@param initialArrowPos: 初期位置
	@param top: 最上位置
	@param bottom: 最下位置
	@param loop: ループ可否
	@param horizontal: 水平モードかどうか
	
	  C++ signature :
		  void __init__(
		  struct _object * __ptr64,
		  int,
		  int,
		  int,
		  [bool, [bool]])
	'''
"""

ArrowLocator.update.__doc__ = """
状態を更新します

update( (ArrowLocator)self) -> None :

  C++ signature :
	  void update(class Defs::Util::ArrowLocator {lvalue})
"""

ArrowLocator.setMoveCallback.__doc__ = """
矢印の移動時に呼ばれるコールバック関数を設定します

setMoveCallback( (ArrowLocator)self, (object)callback) -> None :

@param callback: 引数が0個の関数

  C++ signature :
	  void setMoveCallback(
	  class Defs::Util::ArrowLocator {lvalue},
	  class boost::python::api::object)
"""


CirclingF = Game.CirclingF
CirclingF.__doc__ = """
旋回角度を管理するクラス

@ivar circling: 旋回の可否(デフォルトでFalse)
@ivar angle: 現在の角度
@ivar circlingAngle: 旋回角度
@ivar targetAngle: 旋回目標角度 この角度へ向けて旋回していきます
"""

CirclingF.__init__.__doc__ = """
コンストラクタ

__init__( (object)self) -> None :
	'''
	デフォルト状態で初期化します
	
	後で個別にプロパティを設定する必要があります。
	
	  C++ signature :
		  void __init__(struct _object * __ptr64)
	'''

__init__( (object)self, (float)circlingAngle) -> None :
	'''
	旋回角度を指定して初期化します
	
	@param circlingAngle: 旋回角度
	
	  C++ signature :
		  void __init__(
		  struct _object * __ptr64,
		  float)
	'''
"""

CirclingF.update.__doc__ = """
状態を更新します

update( (CirclingF)self) -> None :

  C++ signature :
	  void update(class Game::Util::STG::Circling<float> {lvalue})
"""


Consts = Game.Consts
Consts.__doc__ = """
定数クラス

__init__ = <built-in function __init__>
  Raises an exception
  This class cannot be instantiated from Python

@cvar ScreenSize: スクリーンのサイズ
@cvar StgInfAreaSize: STG画面の情報表示領域のサイズ
"""


class Hit:
	"""当たり判定クラス"""
	
	CircleF = Game.HitCircleF
	CircleF.__doc__ = """
	円形の当たり判定を行うクラス
	
	内部の値は浮動小数点数で保持されます。
	
	@ivar center: 中心座標
	@ivar radius: 半径
	"""
	
	CircleF.__init__.__doc__ = """
	コンストラクタ
	
	__init__( (object)self) -> None :
		'''
		デフォルト状態で初期化します
		
		  C++ signature :
			  void __init__(struct _object * __ptr64)
		'''
	
	__init__( (object)self, (HitCircleF | HitCircleI)circle) -> None :
		'''
		他のオブジェクトをコピーして初期化します
		
		@param circle: 他のHitCircleオブジェクト
		
		  C++ signature :
			  void __init__(
			  struct _object * __ptr64,
			  (class Game::Util::STG::Hit::Circle<float> | class Game::Util::STG::Hit::Circle<long>))
		'''
	
	__init__( (object)self, (float | int)x, (float | int)y, (float | int)radius) -> None :
		'''
		XY座標と半径を指定して初期化します
		
		@param x: X座標
		@param y: Y座標
		@param radius: 半径
		
		  C++ signature :
			  void __init__(
			  struct _object * __ptr64,
			  (float | long),
			  (float | long),
			  (float | long))
		'''
	
	__init__( (object)self, (Vector2DF | Vector2DI)center, (float | int)radius) -> None :
		'''
		XY座標ベクトルと半径を指定して初期化します
		
		@param center: 中心座標ベクトル
		@param radius: 半径
		
		  C++ signature :
			  void __init__(
			  struct _object * __ptr64,
			  (class Game::Util::STG::Vector2D<float> | class Game::Util::STG::Vector2D<long>),
			  (float | long))
		'''
	"""
	
	CircleF.isHit.__doc__ = """
	他のオブジェクトと当たっているか判定します
	
	isHit( (HitCircleF)self, (HitCircleF | HitCircleI)circle) -> bool :
	
	@param circle: 他のHitCircleオブジェクト
	@return: TrueまたはFalse
	
	  C++ signature :
		  bool isHit(
		  class Game::Util::STG::Hit::Circle<float> {lvalue},
		  (class Game::Util::STG::Hit::Circle<float> | class Game::Util::STG::Hit::Circle<long>))
	"""
	
	
	CircleI = Game.HitCircleI
	CircleI.__doc__ = """
	円形の当たり判定を行うクラス
	
	内部の値は整数で保持されます。
	
	@ivar center: 中心座標
	@ivar radius: 半径
	"""
	
	CircleI.__init__.__doc__ = """
	コンストラクタ
	
	__init__( (object)self) -> None :
		'''
		デフォルト状態で初期化します
		
		  C++ signature :
			  void __init__(struct _object * __ptr64)
		'''
	
	__init__( (object)self, (HitCircleI | HitCircleF)circle) -> None :
		'''
		他のオブジェクトをコピーして初期化します
		
		@param circle: 他のHitCircleオブジェクト
		
		  C++ signature :
			  void __init__(
			  struct _object * __ptr64,
			  (class Game::Util::STG::Hit::Circle<long> | class Game::Util::STG::Hit::Circle<float>))
		'''
	
	__init__( (object)self, (int | float)x, (int | float)y, (int | float)radius) -> None :
		'''
		中心のXY座標と半径を指定して初期化します
		
		@param x: 中心のX座標
		@param y: 中心のY座標
		@param radius: 半径
		
		  C++ signature :
			  void __init__(
			  struct _object * __ptr64,
			  (long | float),
			  (long | float),
			  (long | float))
		'''
	
	__init__( (object)self, (Vector2DI | Vector2DF)center, (int | float)radius) -> None :
		'''
		XY座標ベクトルと半径を指定して初期化します
		
		@param center: 中心座標ベクトル
		@param radius: 半径
		
		  C++ signature :
			  void __init__(
			  struct _object * __ptr64,
			  (class Game::Util::STG::Vector2D<long> | class Game::Util::STG::Vector2D<float>),
			  (long | float))
		'''
	"""
	
	CircleI.isHit.__doc__ = """
	他のオブジェクトと当たっているか判定します
	
	isHit( (HitCircleI)self, (HitCircleI | HitCircleF)circle) -> bool :

	@param circle: 他のHitCircleオブジェクト
	@return: TrueまたはFalse
	
	  C++ signature :
		  bool isHit(
		  class Game::Util::STG::Hit::Circle<long> {lvalue},
		  (class Game::Util::STG::Hit::Circle<long> | class Game::Util::STG::Hit::Circle<float>))
	"""
	
	
	RectF = Game.HitRectF
	RectF.__doc__ = """
	矩形の当たり判定を行うクラス
	
	内部の値は浮動小数点数で保持されます。
	
	@ivar center: 中心座標
	@ivar size: 幅と高さを表すベクトル
	"""
	
	RectF.__init__.__doc__ = """
	コンストラクタ
	
	__init__( (object)self) -> None :
		'''
		デフォルト状態で初期化します
		
		  C++ signature :
			  void __init__(struct _object * __ptr64)
		'''
	
	__init__( (object)self, (HitRectF | HitRectI)rect) -> None :
		'''
		他のオブジェクトをコピーして初期化します
		
		@param rect: 他のオブジェクト
		
		  C++ signature :
			  void __init__(
			  struct _object * __ptr64,
			  (class Game::Util::STG::Hit::Rect<float> | class Game::Util::STG::Hit::Rect<long>))
		'''
	
	__init__( (object)self, (float | int)x, (float | int)y, (float | int)width, (float | int)height, (bool)centerPos) -> None :
		'''
		XY座標と、幅と高さを指定して初期化します
		
		@param x: X座標
		@param y: Y座標
		@param width: 幅
		@param height: 高さ
		@param centerPos: 座標が矩形の中心ならTrue、矩形の左上ならFalse
		
		  C++ signature :
			  void __init__(
			  struct _object * __ptr64,
			  (float | long),
			  (float | long),
			  (float | long),
			  (float | long),
			  bool)
		'''
	
	__init__( (object)self, (Vector2DF | Vector2DI)position, (float | int)width, (float | int)height, (bool)centerPos) -> None :
		'''
		XY座標ベクトルと、幅と高さを指定して初期化します
		
		@param position: XY座標ベクトル
		@param width: 幅
		@param height: 高さ
		@param centerPos: 座標が矩形の中心ならTrue、矩形の左上ならFalse
		
		  C++ signature :
			  void __init__(
			  struct _object * __ptr64,
			  (class Game::Util::STG::Vector2D<float> | class Game::Util::STG::Vector2D<long>),
			  (float | long),
			  (float | long),
			  bool)
		'''
	
	__init__( (object)self, (Vector2DF | Vector2DI)position, (Vector2DF | Vector2DI)widthHeight, (bool)centerPos) -> None :
		'''
		XY座標ベクトルと、幅と高さを表すベクトルを指定して初期化します
		
		@param position: XY座標ベクトル
		@param widthHeight: 幅と高さのベクトル
		@param centerPos: 座標が矩形の中心ならTrue、矩形の左上ならFalse
		
		  C++ signature :
			  void __init__(
			  struct _object * __ptr64,
			  (class Game::Util::STG::Vector2D<float> | class Game::Util::STG::Vector2D<long>),
			  (class Game::Util::STG::Vector2D<float> | class Game::Util::STG::Vector2D<long>),
			  bool)
		'''
	
	__init__( (object)self, (RectF | RectI)rect) -> None :
		'''
		(RectF | RectI)オブジェクトをもとに初期化します
		
		@param rect: (RectF | RectI)オブジェクト
		
		  C++ signature :
			  void __init__(
			  struct _object * __ptr64,
			  (class Selene::Rect<float> | class Selene::Rect<long>))
		'''
	"""
	
	RectF.isHit.__doc__ = """
	他のオブジェクトと当たっているか判定します
	
	isHit( (HitRectF)self, (HitRectF | HitRectI)rect) -> bool :
	
	@param rect: 他の矩形オブジェクト
	@return: TrueまたはFalse
	
	  C++ signature :
		  bool isHit(
		  class Game::Util::STG::Hit::Rect<float> {lvalue},
		  (class Game::Util::STG::Hit::Rect<float> | class Game::Util::STG::Hit::Rect<long>))
	"""
	
	RectF.getPosition.__doc__ = """
	位置座標ベクトルを取得します
	
	getPosition( (HitRectF)self, (bool)centerPos) -> Vector2DF :
	
	@param centerPos: 中心座標ならTrue、左上座標ならFalse
	@return: 中心座標ベクトルまたは左上座標ベクトル
	
	  C++ signature :
		  class Game::Util::STG::Vector2D<float> getPosition(
		  class Game::Util::STG::Hit::Rect<float> {lvalue},
		  bool)
	"""
	
	RectF.setPosition.__doc__ = """
	位置座標ベクトルを設定します
	
	setPosition( (HitRectF)self, (Vector2DF | Vector2DI)pos, (bool)centerPos) -> None :
	
	@param pos: 位置座標ベクトル
	@param centerPos: 中心座標ならTrue、左上座標ならFalse
	
	  C++ signature :
		  void setPosition(
		  class Game::Util::STG::Hit::Rect<float> {lvalue},
		  (class Game::Util::STG::Vector2D<float> | class Game::Util::STG::Vector2D<long>),
		  bool)
	"""
	
	
	RectI = Game.HitRectI
	RectI.__doc__ = """
	矩形の当たり判定を行うクラス
	
	内部の値は整数で保持されます。
	
	@ivar center: 中心座標
	@ivar size: 幅と高さを表すベクトル
	"""
	
	RectI.__init__.__doc__ = """
	コンストラクタ
	
	__init__( (object)self) -> None :
		'''
		デフォルト状態で初期化します
		
		  C++ signature :
			  void __init__(struct _object * __ptr64)
		'''
	
	__init__( (object)self, (HitRectI | HitRectF)rect) -> None :
		'''
		他のオブジェクトをコピーして初期化します
		
		@param rect: 他のオブジェクト
		
		  C++ signature :
			  void __init__(
			  struct _object * __ptr64,
			  (class Game::Util::STG::Hit::Rect<long> | class Game::Util::STG::Hit::Rect<float>))
		'''
	
	__init__( (object)self, (int | float)x, (int | float)y, (int | float)width, (int | float)height, (bool)centerPos) -> None :
		'''
		XY座標と、幅と高さを指定して初期化します
		
		@param x: X座標
		@param y: Y座標
		@param width: 幅
		@param height: 高さ
		@param centerPos: 座標が矩形の中心ならTrue、矩形の左上ならFalse
		
		  C++ signature :
			  void __init__(
			  struct _object * __ptr64,
			  (long | float),
			  (long | float),
			  (long | float),
			  (long | float),
			  bool)
		'''
	
	__init__( (object)self, (Vector2DI | Vector2DF)position, (int | float)width, (int | float)height, (bool)centerPos) -> None :
		'''
		XY座標ベクトルと、幅と高さを指定して初期化します
		
		@param position: XY座標ベクトル
		@param width: 幅
		@param height: 高さ
		@param centerPos: 座標が矩形の中心ならTrue、矩形の左上ならFalse
		
		  C++ signature :
			  void __init__(
			  struct _object * __ptr64,
			  (class Game::Util::STG::Vector2D<long> | class Game::Util::STG::Vector2D<float>),
			  (long | float),
			  (long | float),
			  bool)
		'''
	
	__init__( (object)self, (Vector2DI | Vector2DF)position, (Vector2DI | Vector2DF)widthHeight, (bool)centerPos) -> None :
		'''
		XY座標ベクトルと、幅と高さを表すベクトルを指定して初期化します
		
		@param position: XY座標ベクトル
		@param widthHeight: 幅と高さのベクトル
		@param centerPos: 座標が矩形の中心ならTrue、矩形の左上ならFalse
		
		  C++ signature :
			  void __init__(
			  struct _object * __ptr64,
			  (class Game::Util::STG::Vector2D<long> | class Game::Util::STG::Vector2D<float>),
			  (class Game::Util::STG::Vector2D<long> | class Game::Util::STG::Vector2D<float>),
			  bool)
		'''
	
	__init__( (object)self, (RectI | RectF)rect) -> None :
		'''
		Rectオブジェクトをもとに初期化します
		
		@param rect: Rectオブジェクト
		
		  C++ signature :
			  void __init__(
			  struct _object * __ptr64,
			  (class Selene::Rect<long> | class Selene::Rect<float>))
		'''
	"""
	
	RectI.isHit.__doc__ = """
	他のオブジェクトと当たっているか判定します
	
	isHit( (HitRectI)self, (HitRectI | HitRectF)rect) -> bool :
	
	@param rect: 他の矩形オブジェクト
	@return: TrueまたはFalse
	
	  C++ signature :
		  bool isHit(
		  class Game::Util::STG::Hit::Rect<long> {lvalue},
		  (class Game::Util::STG::Hit::Rect<long> | class Game::Util::STG::Hit::Rect<float>))
	"""
	
	RectI.getPosition.__doc__ = """
	位置座標ベクトルを取得します
	
	getPosition( (HitRectI)self, (bool)centerPos) -> Vector2DI :
	
	@param centerPos: 中心座標ならTrue、左上座標ならFalse
	@return: 中心座標ベクトルまたは左上座標ベクトル
	
	  C++ signature :
		  class Game::Util::STG::Vector2D<long> getPosition(
		  class Game::Util::STG::Hit::Rect<long> {lvalue},
		  bool)
	"""
	
	RectF.setPosition.__doc__ = """
	位置座標ベクトルを設定します
	
	setPosition( (HitRectI)self, (Vector2DI | Vector2DF)pos, (bool)centerPos) -> None :
	
	@param pos: 位置座標ベクトル
	@param centerPos: 中心座標ならTrue、左上座標ならFalse
	
	  C++ signature :
		  void setPosition(
		  class Game::Util::STG::Hit::Rect<long> {lvalue},
		  (class Game::Util::STG::Vector2D<long> | class Game::Util::STG::Vector2D<float>),
		  bool)
	"""

class Locator:
	"""座標とその移動を管理するクラス"""
	
	LinearF = Game.LocatorLinearF
	LinearF.__doc__ = """
	直線移動する座標を管理するクラス
	
	@ivar position: 位置ベクトル
	@ivar speed: 速度ベクトル
	@ivar accel: 加速度ベクトル
	"""
	
	LinearF.__init__.__doc__ = """
	コンストラクタ
	
	__init__( (object)self) -> None :
		'''
		デフォルト状態で初期化します
		
		  C++ signature :
			  void __init__(struct _object * __ptr64)
		'''
	
	__init__( (object)self, (LocatorLinearF)locator) -> None :
		'''
		他のオブジェクトの状態をコピーして初期化します
		
		@param locator: 他のオブジェクト
		
		  C++ signature :
			  void __init__(
			  struct _object * __ptr64,
			  class Game::Util::STG::Locator::Linear<float>)
		'''
	
	__init__( (object)self, (Vector2DF)position[, (Vector2DF)speed, (Vector2DF)accel]) -> None :
		'''
		位置と速度と加速度を初期化します
		
		@param position: 位置ベクトル
		@param speed: 速度ベクトル
		@param accel: 加速度ベクトル
		
		  C++ signature :
			  void __init__(
			  struct _object * __ptr64,
			  class Game::Util::STG::Vector2D<float>,
			  [class Game::Util::STG::Vector2D<float>,
			  class Game::Util::STG::Vector2D<float>])
		'''
	"""
	
	LinearF.update.__doc__ = """
	状態を更新します
	
	update( (LocatorLinearF)self) -> None :
	
	  C++ signature :
		  void update(class Game::Util::STG::Locator::Linear<float> {lvalue})
	"""
	
	LinearF.applyExternalForce.__doc__ = """
	外力を適用します
	
	applyExternalForce( (LocatorLinearF)self, (Vector2DF)force) -> Vector2DF :
	
	@param force: 外力ベクトル
	@return: 反発ベクトル
	
	  C++ signature :
		  class Game::Util::STG::Vector2D<float> applyExternalForce(
		  class Game::Util::STG::Locator::Linear<float> {lvalue},
		  class Game::Util::STG::Vector2D<float>)
	"""
	
	
	RotateF = Game.LocatorRotateF
	RotateF.__doc__ = """
	円移動する座標を管理するクラス
	
	@ivar position: 位置ベクトル
	@ivar center: 中心位置ベクトル
	@ivar centerSpeed: 中心位置移動速度ベクトル
	@ivar centerAccel: 中心位置移動加速度ベクトル
	@ivar radius: 半径
	@ivar radiusSpeed: 半径伸縮速度
	@ivar radiusAccel: 半径伸縮加速度
	@ivar angle: 角度
	@ivar angleSpeed: 角速度
	@ivar angleAccel: 角加速度
	"""
	
	RotateF.__init__.__doc__ = """
	コンストラクタ
	
	__init__( (object)self) -> None :
		'''
		デフォルト状態で初期化します
		
		  C++ signature :
			  void __init__(struct _object * __ptr64)
		'''
	
	__init__( (object)self, (LocatorRotateF)locator) -> None :
		'''
		他のオブジェクトの状態をコピーして初期化します
		
		@param locator: 他のオブジェクト
		
		  C++ signature :
			  void __init__(
			  struct _object * __ptr64,
			  class Game::Util::STG::Locator::Rotate<float>)
		'''
	"""
	
	RotateF.update.__doc__ = """
	状態を更新します
	
	update( (LocatorRotateF)self) -> None :
	
	  C++ signature :
		  void update(class Game::Util::STG::Locator::Rotate<float> {lvalue})
	"""
	
	RotateF.applyExternalForce.__doc__ = """
	外力を適用します
	
	applyExternalForce( (LocatorRotateF)self, (Vector2DF)force) -> Vector2DF :
	
	@param force: 外力ベクトル
	@return: 反発ベクトル
	
	  C++ signature :
		  class Game::Util::STG::Vector2D<float> applyExternalForce(
		  class Game::Util::STG::Locator::Rotate<float> {lvalue},
		  class Game::Util::STG::Vector2D<float>)
	"""
	
	
	TraceF = Game.LocatorTraceF
	TraceF.__doc__ = """
	目標を追尾移動する座標を管理するクラス
	
	@ivar tracing: 追尾の可否
	@ivar position: 位置ベクトル
	@ivar targetPosition: 目標位置ベクトル
	@ivar speed: 速度ベクトル
	@ivar accel: 加速度ベクトル
	@ivar maxCirclingAngle: 最大旋回角度
	"""
	
	TraceF.__init__.__doc__ = """
	コンストラクタ
	
	__init__( (object)self) -> None :
		'''
		デフォルト状態で初期化します
		
		  C++ signature :
			  void __init__(struct _object * __ptr64)
		'''
	
	__init__( (object)self, (LocatorTraceF)locator) -> None :
		'''
		他のオブジェクトの状態をコピーして初期化します
		
		@param locator: 他のオブジェクト
		
		  C++ signature :
			  void __init__(
			  struct _object * __ptr64,
			  class Game::Util::STG::Locator::Trace<float>)
		'''
	
	__init__( (object)self, (float)maxCirclingAngle) -> None :
		'''
		最大旋回角度を指定して初期化します
		
		@param maxCirclingAngle: 最大旋回角度
		
		  C++ signature :
			  void __init__(
			  struct _object * __ptr64,
			  float)
		'''
	"""
	
	TraceF.update.__doc__ = """
	状態を更新します
	
	update( (LocatorTraceF)self) -> None :
	
	  C++ signature :
		  void update(class Game::Util::STG::Locator::Trace<float> {lvalue})
	"""
	
	TraceF.applyExternalForce.__doc__ = """
	外力を適用します
	
	applyExternalForce( (LocatorTraceF)self, (Vector2DF)force) -> Vector2DF :
	
	@param force: 外力ベクトル
	@return: 反発ベクトル
	
	  C++ signature :
		  class Game::Util::STG::Vector2D<float> applyExternalForce(
		  class Game::Util::STG::Locator::Trace<float> {lvalue},
		  class Game::Util::STG::Vector2D<float>)
	"""

RepeatCounter = Game.RepeatCounter
RepeatCounter.__doc__ = """
繰り返しを管理するクラス

@ivar repeatCount: 現在の繰り返し回数
@ivar interval: 繰り返し間隔
"""

RepeatCounter.__init__.__doc__ = """
コンストラクタ

__init__( (object)self) -> None :
	'''
	繰り返し間隔を1.0で初期化します
	
	  C++ signature :
		  void __init__(struct _object * __ptr64)
	'''

__init__( (object)self, (RepeatCounter)repeatCounter) -> None :
	'''
	他のオブジェクトで初期化します
	
	@param repeatCounter: 他のオブジェクト
	
	  C++ signature :
		  void __init__(
		  struct _object * __ptr64,
		  class Game::Util::RepeatCounter)
	'''

__init__( (object)self, (float)interval) -> None :
	'''
	繰り返し間隔を指定して初期化します
	
	@param interval: 繰り返し間隔
	
	  C++ signature :
		  void __init__(
		  struct _object * __ptr64,
		  float)
	'''
"""

RepeatCounter.update.__doc__ = """
状態を更新します

update( (RepeatCounter)self) -> None :

  C++ signature :
	  void update(class Game::Util::RepeatCounter {lvalue})
"""

RepeatCounter.reset.__doc__ = """
状態を初期化します

reset( (RepeatCounter)self) -> None :

  C++ signature :
	  void reset(class Game::Util::RepeatCounter {lvalue})
"""


Vector2DF = Game.Vector2DF
Vector2DF.__doc__ = """
２次元ベクトルクラス

座標は浮動小数点数で保持されます。
演算子は、+, -, *, /, +=, -=, *=, /=, -(単項) が定義されています。

@ivar x: X座標
@ivar y: Y座標
"""

Vector2DF.__init__.__doc__ = """
コンストラクタ

__init__( (object)self) -> None :
	'''
	(0, 0)で初期化します
	
	  C++ signature :
		  void __init__(struct _object * __ptr64)
	'''

__init__( (object)self, (float | int)x, (float | int)y) -> None :
	'''
	XY座標で初期化します
	
	@param x: X座標
	@param y: Y座標
	
	  C++ signature :
		  void __init__(
		  struct _object * __ptr64,
		  (float | long),
		  (float | long))
	'''

__init__( (object)self, (Vector2DF | Vector2DI)vector) -> None :
	'''
	他のオブジェクトで初期化します
	
	@param vector: 他のオブジェクト
	
	  C++ signature :
		  void __init__(
		  struct _object * __ptr64,
		  (class Game::Util::STG::Vector2D<float> | class Game::Util::STG::Vector2D<long>))
	'''
"""

Vector2DF.getXY.__doc__ = """
XY座標を取得します

getXY( (Vector2DF)self) -> object :

@return: XY座標

  C++ signature :
	  struct std::pair<float,float> getXY(
	  class Game::Util::STG::Vector2D<float> {lvalue})
"""

Vector2DF.setXY.__doc__ = """
XY座標を設定します

setXY( (Vector2DF)self, (float)x, (float)y) -> Vector2DF :

@param x: X座標
@param y: Y座標
@return: このオブジェクトへの参照

  C++ signature :
	  class Game::Util::STG::Vector2D<float> {lvalue} setXY(
	  class Game::Util::STG::Vector2D<float> {lvalue},
	  float,
	  float)
"""

Vector2DF.getAbs.__doc__ = """
絶対値を取得します

getAbs( (Vector2DF)self) -> float :

@return: 絶対値

  C++ signature :
	  float getAbs(class Game::Util::STG::Vector2D<float> {lvalue})
"""

Vector2DF.normalize.__doc__ = """
正規化します

normalize( (Vector2DF)self) -> Vector2DF :

@return: このオブジェクトへの参照

  C++ signature :
	  class Game::Util::STG::Vector2D<float> {lvalue} normalize(
	  class Game::Util::STG::Vector2D<float> {lvalue})
"""

Vector2DF.setUnitVector.__doc__ = """
角度から単位ベクトルを設定します

setUnitVector( (Vector2DF)self, (float)degree) -> Vector2DF :

@param degree: 角度
@result: このオブジェクトへの参照

  C++ signature :
	  class Game::Util::STG::Vector2D<float> {lvalue} setUnitVector(
	  class Game::Util::STG::Vector2D<float> {lvalue},
	  float)
"""

Vector2DF.getAngle.__doc__ = """
角度を求めます

getAngle( (Vector2DF)self) -> float :
	'''
	原点からの角度を求めます
	
	@return: 角度
	
	  C++ signature :
		  float getAngle(class Game::Util::STG::Vector2D<float> {lvalue})
	'''

getAngle( (Vector2DF)self, (float)x, (float)y) -> float :
	'''
	他の座標への角度を求めます
	
	@param x: 他のX座標
	@param y: 他のY座標
	@return: 角度
	
	  C++ signature :
		  float getAngle(
		  class Game::Util::STG::Vector2D<float> {lvalue},
		  float,
		  float)
	'''

getAngle( (Vector2DF)self, (Vector2DF)pos) -> float :
	'''
	他の座標への角度を求めます
	
	@param pos: 他の座標の位置ベクトル
	@return: 角度
	
	  C++ signature :
		  float getAngle(
		  class Game::Util::STG::Vector2D<float> {lvalue},
		  class Game::Util::STG::Vector2D<float>)
	'''
"""

Vector2DF.getDistance.__doc__ = """
他の座標への距離を求めます

getDistance( (Vector2DF)self, (Vector2DF)pos) -> float :

@param pos: 他の座標の位置ベクトル
@return: 距離

  C++ signature :
	  float getDistance(
	  class Game::Util::STG::Vector2D<float> {lvalue},
	  class Game::Util::STG::Vector2D<float>)
"""

Vector2DF.rotate.__doc__ = """
回転します

rotate( (Vector2DF)self, (float)degree) -> None :
	'''
	原点を中心に回転します
	
	@param degree: 回転角度
	
	  C++ signature :
		  void rotate(
		  class Game::Util::STG::Vector2D<float> {lvalue},
		  float)
	'''

rotate( (Vector2DF)self, (float)degree, (Vector2DF)center) -> None :
	'''
	任意の位置を中心に回転します
	
	@param degree: 回転角度
	@param center: 中心の位置ベクトル
	
	  C++ signature :
		  void rotate(
		  class Game::Util::STG::Vector2D<float> {lvalue},
		  float,
		  class Game::Util::STG::Vector2D<float>)
	'''
"""

Vector2DF.makeRect.__doc__ = """
矩形領域を生成します

makeRect( (Vector2DF)self, (float)w, (float)h, (bool)center) -> RectF :
	'''
	@param w: 幅
	@param h: 高さ
	@param center: 中心座標ならTrue、左上の座標ならFalse
	@return: 矩形領域
	
	  C++ signature :
		  class Selene::Rect<float> makeRect(
		  class Game::Util::STG::Vector2D<float> {lvalue},
		  float,
		  float,
		  bool)
	'''

makeRect( (Vector2DF)self, (Vector2DF)widthHeight, (bool)center) -> RectF :
	'''
	@param widthHeight: 幅と高さのベクトル
	@param center: 中心座標ならTrue、左上の座標ならFalse
	@return: 矩形領域
	
	  C++ signature :
		  class Selene::Rect<float> makeRect(
		  class Game::Util::STG::Vector2D<float> {lvalue},
		  class Game::Util::STG::Vector2D<float>,
		  bool)
	'''
"""


Vector2DI = Game.Vector2DI
Vector2DI.__doc__ = """
２次元ベクトルクラス

座標は整数で保持されます。
演算子は、+, -, *, /, +=, -=, *=, /=, -(単項) が定義されています。

@ivar x: X座標
@ivar y: Y座標
"""

Vector2DI.__init__.__doc__ = """
コンストラクタ

__init__( (object)self) -> None :
	'''
	(0, 0)で初期化します
	
	  C++ signature :
		  void __init__(struct _object * __ptr64)
	'''

__init__( (object)self, (int | float)x, (int | float)y) -> None :
	'''
	XY座標で初期化します
	
	@param x: X座標
	@param y: Y座標
	
	  C++ signature :
		  void __init__(
		  struct _object * __ptr64,
		  (long | float),
		  (long | float))
	'''

__init__( (object)self, (Vector2DI | Vector2DF)vector) -> None :
	'''
	他のオブジェクトで初期化します
	
	@param vector: 他のオブジェクト
	
	  C++ signature :
		  void __init__(
		  struct _object * __ptr64,
		  (class Game::Util::STG::Vector2D<long> | class Game::Util::STG::Vector2D<float>))
	'''
"""

Vector2DI.getXY.__doc__ = """
XY座標を取得します

getXY( (Vector2DI)self) -> object :

@return: XY座標

  C++ signature :
	  struct std::pair<long,long> getXY(
	  class Game::Util::STG::Vector2D<long> {lvalue})
"""

Vector2DI.setXY.__doc__ = """
XY座標を設定します

setXY( (Vector2DI)self, (int)x, (int)y) -> Vector2DI :

@param x: X座標
@param y: Y座標
@return: このオブジェクトへの参照

  C++ signature :
	  class Game::Util::STG::Vector2D<long> {lvalue} setXY(
	  class Game::Util::STG::Vector2D<long> {lvalue},
	  long,
	  long)
"""

Vector2DI.getAbs.__doc__ = """
絶対値を取得します

getAbs( (Vector2DI)self) -> int :

@return: 絶対値

  C++ signature :
	  long getAbs(class Game::Util::STG::Vector2D<long> {lvalue})
"""

Vector2DI.normalize.__doc__ = """
正規化します

normalize( (Vector2DI)self) -> Vector2DI :

@return: このオブジェクトへの参照

  C++ signature :
	  class Game::Util::STG::Vector2D<long> {lvalue} normalize(
	  class Game::Util::STG::Vector2D<long> {lvalue})
"""

Vector2DI.setUnitVector.__doc__ = """
角度から単位ベクトルを設定します

setUnitVector( (Vector2DI)self, (int)degree) -> Vector2DI :

@param degree: 角度
@result: このオブジェクトへの参照

  C++ signature :
	  class Game::Util::STG::Vector2D<long> {lvalue} setUnitVector(
	  class Game::Util::STG::Vector2D<long> {lvalue},
	  long)
"""

Vector2DI.getAngle.__doc__ = """
角度を求めます

getAngle( (Vector2DI)self) -> int :
	'''
	原点からの角度を求めます
	
	@return: 角度
	
	  C++ signature :
		  long getAngle(class Game::Util::STG::Vector2D<long> {lvalue})
	'''

getAngle( (Vector2DI)self, (int)x, (int)y) -> int :
	'''
	他の座標への角度を求めます
	
	@param x: 他のX座標
	@param y: 他のY座標
	@return: 角度
	
	  C++ signature :
		  long getAngle(
		  class Game::Util::STG::Vector2D<long> {lvalue},
		  long,
		  long)
	'''

getAngle( (Vector2DI)self, (Vector2DI)pos) -> int :
	'''
	他の座標への角度を求めます
	
	@param pos: 他の座標の位置ベクトル
	@return: 角度
	
	  C++ signature :
		  long getAngle(
		  class Game::Util::STG::Vector2D<long> {lvalue},
		  class Game::Util::STG::Vector2D<long>)
	'''
"""

Vector2DF.getDistance.__doc__ = """
他の座標への距離を求めます

getDistance( (Vector2DI)self, (Vector2DI)pos) -> int :

@param pos: 他の座標の位置ベクトル
@return: 距離

  C++ signature :
	  float getDistance(
	  class Game::Util::STG::Vector2D<long> {lvalue},
	  class Game::Util::STG::Vector2D<long>)
"""

Vector2DF.rotate.__doc__ = """
回転します

rotate( (Vector2DI)self, (int)degree) -> None :
	'''
	原点を中心に回転します
	
	@param degree: 回転角度
	
	  C++ signature :
		  void rotate(
		  class Game::Util::STG::Vector2D<long> {lvalue},
		  long)
	'''

rotate( (Vector2DI)self, (int)degree, (Vector2DI)center) -> None :
	'''
	任意の位置を中心に回転します
	
	@param degree: 回転角度
	@param center: 中心の位置ベクトル
	
	  C++ signature :
		  void rotate(
		  class Game::Util::STG::Vector2D<long> {lvalue},
		  long,
		  class Game::Util::STG::Vector2D<long>)
	'''
"""

Vector2DF.makeRect.__doc__ = """
矩形領域を生成します

makeRect( (Vector2DI)self, (int)w, (int)h, (bool)center) -> RectI :
	'''
	@param w: 幅
	@param h: 高さ
	@param center: 中心座標ならTrue、左上の座標ならFalse
	@return: 矩形領域
	
	  C++ signature :
		  class Selene::Rect<long> makeRect(
		  class Game::Util::STG::Vector2D<long> {lvalue},
		  long,
		  long,
		  bool)
	'''

makeRect( (Vector2DI)self, (Vector2DI)widthHeight, (bool)center) -> RectI :
	'''
	@param widthHeight: 幅と高さのベクトル
	@param center: 中心座標ならTrue、左上の座標ならFalse
	@return: 矩形領域
	
	  C++ signature :
		  class Selene::Rect<long> makeRect(
		  class Game::Util::STG::Vector2D<long> {lvalue},
		  class Game::Util::STG::Vector2D<long>,
		  bool)
	'''
"""


class Console:
	"""コンソールに関する機能を提供するクラス"""
	
	@staticmethod
	def create():
		"""
		コンソールウィンドウを作成します
		
		@return: 成功すればTrue、失敗すればFalse
		
		  C++ signature :
			  bool create()
		"""
		
		return Game.Console.create()
	
	@staticmethod
	def write(string):
		"""
		コンソールへ文字列を書き込みます
		
		@param string: コンソールへ書き込む文字列
		@return: 成功すればTrue、失敗すればFalse
		
		  C++ signature :
			  bool write(
			  class std::basic_string<wchar_t,struct std::char_traits<wchar_t>,class std::allocator<wchar_t> >)
		"""
		
		return Game.Console.write(string)
	
	@staticmethod
	def writeLine(string):
		"""
		コンソールへ文字列を書き込み、改行します
		
		@param string: コンソールへ書き込む文字列
		@return: 成功すればTrue、失敗すればFalse
		
		  C++ signature :
			  bool writeLine(
			  class std::basic_string<wchar_t,struct std::char_traits<wchar_t>,class std::allocator<wchar_t> >)
		"""
		
		return Game.Console.writeLine(string)
	
	@staticmethod
	def delete():
		"""
		コンソールウィンドウを閉じます
		
		@return: 成功すればTrue、失敗すればFalse
		
		  C++ signature :
			  bool delete()
		"""
		
		return Game.Console.delete()


class _File:
	"""ファイルに関する機能を提供するクラス"""
	
	def openSync(self, path, cache = True, throwException = True):
		"""
		パスを指定してファイルを開きます
		
		@param path: ファイルパス文字列
		@param cache: キャッシュ可否
		@param throwException: 例外可否
		@return: FileObject
		
		cacheをFalseにすることで、システム側でキャッシュされなくなり、
		FileObjectがスコープを外れた時点で解放されることが保障されます。
		
		throwExceptionをFalseにすることで、
		読み込み失敗時に例外を投げずに無効な値を返します。
		
		  C++ signature :
			  class Defs::Util::File::FileObject open(
			  class std::basic_string<wchar_t,struct std::char_traits<wchar_t>,class std::allocator<wchar_t> >,
			  bool,
			  bool)
		"""
		
		return Game.File.open(path, cache, throwException)
	
	def openASync(self, path, cache = True, throwException = True):
		"""
		パスを指定して非同期でファイルを開きます
		
		@param path: ファイルパス文字列
		@param cache: キャッシュ可否
		@param throwException: 例外可否
		@return: FileObject
		
		cacheをFalseにすることで、システム側でキャッシュされなくなり、
		FileObjectがスコープを外れた時点で解放されることが保障されます。
		
		throwExceptionをFalseにすることで、
		読み込み失敗時に例外を投げずに無効な値を返します。
		
		  C++ signature :
			  class Defs::Util::File::FileObject openASync(
			  class std::basic_string<wchar_t,struct std::char_traits<wchar_t>,class std::allocator<wchar_t> >,
			  bool,
			  bool)
		"""
		
		return Game.File.openASync(path, cache, throwException)
	
	@property
	def cacheSize(self):
		"""現在キャッシュされているFileObjectの総サイズを取得します"""
		
		return Game.File.cacheSize
	
	@property
	def maxCacheSize(self):
		"""
		総キャッシュサイズの最大値を取得します
		
		総キャッシュサイズがこの値を超えると、
		この値を下回るまで最も大きなFileObjectから削除されていきます。
		"""
		
		return Game.File.maxCacheSize
	
	@maxCacheSize.setter
	def maxCacheSize(self, value):
		"""総キャッシュサイズの最大値を設定します"""
		
		Game.File.maxCacheSize = value
	
	def eraseCache(self, path):
		"""
		指定したパスで開いたFileObjectをキャッシュから削除します
		
		@param path: 削除するFileObjectのパス文字列
		
		  C++ signature :
			  void eraseCache(
			  class std::basic_string<wchar_t,struct std::char_traits<wchar_t>,class std::allocator<wchar_t> >)
		"""
		
		Game.File.eraseCache(path)
	
	def clearCache(self):
		"""
		キャッシュをすべて削除します
		
		  C++ signature :
			  void clearCache()
		"""
		
		Game.File.clearCache()
File = _File()

_FileObject = Game.FileObject
_FileObject.__doc__ = """
ファイルを表すクラス

__init__ = <built-in function __init__>
  Raises an exception
  This class cannot be instantiated from Python

@ivar loaded: 読み込みが完了しているかどうか
このプロパティは非同期で開いた場合に意味を持ちます。
同期読み込み時は常にTrueとなります。

@ivar fileName: ファイル名
@ivar size: ファイルサイズ
"""


class Font:
	"""フォントに関する機能を提供するクラス"""
	
	@staticmethod
	def load(path):
		"""
		SFFファイルのパスを指定してフォントを読み込みます
		
		@param path: SFFファイルのパス文字列
		@return: FontObject
		
		  C++ signature :
			  class Defs::Util::Font::Wrapper load(
			  class std::basic_string<wchar_t,struct std::char_traits<wchar_t>,class std::allocator<wchar_t> >)
		"""
		
		return Game.Font.load(path)

_FontObject = Game.FontObject
_FontObject.__doc__ = """
フォントを表すクラス

__init__ = <built-in function __init__>
  Raises an exception
  This class cannot be instantiated from Python

@ivar size: 文字サイズ
@ivar originalSize: オリジナルの文字サイズ
@ivar shakable: 振動エフェクトの影響を受けるかどうか
"""

_FontObject.setPriority.__doc__ = """
描画優先度を設定します

setPriority( (FontObject)self, (int)priority) -> None :

@param priority: 描画優先度を表す整数

  C++ signature :
	  void setPriority(
	  class Defs::Util::Font::Wrapper {lvalue},
	  long)
"""

_FontObject.draw.__doc__ = """
文字列を描画します

draw( (FontObject)self, (Point2DF)position, (ColorF)color, (str)string[, (int)length]) -> Point2DF :

@param position: 描画を開始する左上の座標
@param color: 乗算する色
@param string: 描画する文字列
@param length: 描画する最大文字数
@return: 文字描画終端位置

文字数がlengthを超えた場合、それ以上は描画されません。

  C++ signature :
	  class Selene::Point2D<float> draw(
	  class Defs::Util::Font::Wrapper {lvalue},
	  class Selene::Point2D<float>,
	  struct Selene::ColorF,class std::basic_string<wchar_t,struct std::char_traits<wchar_t>,class std::allocator<wchar_t> >,
	  long)
"""

_FontObject.drawLeft.__doc__ = """
左揃えで文字列を描画します

drawLeft( (FontObject)self, (RectF)rect, (Point2DF)offset, (ColorF)color, (str)string[, (int)length]) -> Point2DF :

@param rect: 描画する矩形領域
@param offset: 描画位置のオフセット
@param color: 乗算する色
@param string: 描画する文字列
@param length: 描画する最大文字数
@return: 文字描画終端位置

文字数がlengthを超えた場合、それ以上は描画されません。

  C++ signature :
	  class Selene::Point2D<float> drawLeft(
	  class Defs::Util::Font::Wrapper {lvalue},
	  class Selene::Rect<float>,
	  class Selene::Point2D<float>,
	  struct Selene::ColorF,
	  class std::basic_string<wchar_t,struct std::char_traits<wchar_t>,class std::allocator<wchar_t> >,
	  long)
"""

_FontObject.drawCenter.__doc__ = """
中央揃えで文字列を描画します

drawCenter( (FontObject)self, (RectF)rect, (Point2DF)offset, (ColorF)color, (str)string[, (int)length]) -> Point2DF :

@param rect: 描画する矩形領域
@param offset: 描画位置のオフセット
@param color: 乗算する色
@param string: 描画する文字列
@param length: 描画する最大文字数
@return: 文字描画終端位置

文字数がlengthを超えた場合、それ以上は描画されません。

  C++ signature :
	  class Selene::Point2D<float> drawCenter(
	  class Defs::Util::Font::Wrapper {lvalue},
	  class Selene::Rect<float>,
	  class Selene::Point2D<float>,
	  struct Selene::ColorF,
	  class std::basic_string<wchar_t,struct std::char_traits<wchar_t>,class std::allocator<wchar_t> >,
	  long)
"""

_FontObject.drawRight.__doc__ = """
右揃えで文字列を描画します

drawRight( (FontObject)self, (RectF)rect, (Point2DF)offset, (ColorF)color, (str)string[, (int)length]) -> Point2DF :

@param rect: 描画する矩形領域
@param offset: 描画位置のオフセット
@param color: 乗算する色
@param string: 描画する文字列
@param length: 描画する最大文字数
@return: 文字描画終端位置

文字数がlengthを超えた場合、それ以上は描画されません。

  C++ signature :
	  class Selene::Point2D<float> drawRight(
	  class Defs::Util::Font::Wrapper {lvalue},
	  class Selene::Rect<float>,
	  class Selene::Point2D<float>,
	  struct Selene::ColorF,
	  class std::basic_string<wchar_t,struct std::char_traits<wchar_t>,class std::allocator<wchar_t> >,
	  long)
"""


class _Input:
	"""入力に関する機能を提供するクラス"""
	
	# 方向入力に用いる軸のID
	AxisId = Game.AxisId
	# 入力に用いるキーのID
	KeyId = Game.KeyId
	
	def getController(self):
		"""
		入力コントローラーを取得します
		
		@return: InputController
		
		C++ signature :
		  class Defs::Util::Input::Controller getController()
		"""
		
		return Game.Input.getController()
	
	@property
	def joystickExistence(self):
		"""ジョイスティックが存在するかをチェックします"""
		
		if Game.Input.getJoystickCount() > 0:
			return True
		else:
			return False
	
	@property
	def joystickCount(self):
		"""利用可能なジョイスティックの数を取得します"""
		
		return Game.Input.getJoystickCount()
	
	def setAxis(self, *args):
		"""
		コントローラーの軸の設定をします
		
		setAxis( (AxisId)axis) -> int :
			'''
			ゲームパッドのアナログスティックをコントローラーに割り当てます
			
			@param axis: 割り当てる軸のID
			@return: 現在入力されているゲームパッドの仮想キー
			-1でどれも入力されていない状態
			
			  C++ signature :
				  long setAxis(enum Game::Util::Input::STG::Detail::AXIS_ID)
			'''
		
		setAxis( (AxisId)axis, (int)virtualKey) -> None :
			'''
			コントローラーにゲームパッドの仮想キーを割り当てます
			
			@param axis: 割り当てる軸のID
			@param virtualKey: ゲームパッドの仮想キー
			
			割り当てる仮想キーが分かっている場合はこちらを使います
			
			  C++ signature :
				  void setAxis(
				  enum Game::Util::Input::STG::Detail::AXIS_ID,
				  unsigned long)
			'''
		"""
		
		return Game.Input.setAxis(*args)
	
	def setButton(self, *args):
		"""
		コントローラーのボタンの設定をします
		
		setButton( (KeyId)key) -> int :
			'''
			ゲームパッドのボタンをコントローラーに割り当てます
			
			@param key: 割り当てるキーのID
			@return: 現在入力されているゲームパッドの仮想キー
			-1でどれも入力されていない状態
			
			Axisに割り当てられている仮想キーは無視されます
			
			  C++ signature :
				  long setButton(enum Game::Util::Input::STG::KEY_ID)
			'''
		
		setButton( (KeyId)key, (int)virtualKey) -> None :
			'''
			コントローラーにゲームパッドの仮想キーを割り当てます
			
			@param key: 割り当てるキーのID
			@param virtualKey: ゲームパッドの仮想キー
			
			割り当てる仮想キーが分かっている場合はこちらを使います
			
			  C++ signature :
				  void setButton(
				  enum Game::Util::Input::STG::KEY_ID,
				  unsigned long)
			'''
		"""
		
		return Game.Input.setButton(*args)
	
	def getAxisVirtualKey(self, axisId):
		"""
		軸に割り当てられている仮想キーを取得します
		
		@param axis: 軸のID
		@return: 仮想キー
		割り当てられていない場合、-1が返されます
		
		  C++ signature :
			  long getAxisVirtualKey(enum Game::Util::Input::STG::Detail::AXIS_ID)
		"""
		
		return Game.Input.getAxisVirtualKey(axisId)
	
	def getButtonVirtualKey(self, keyId):
		"""
		ボタンに割り当てられている仮想キーを取得します
		
		@param key: キーのID
		@return: 仮想キー
		割り当てられていない場合、-1が返されます
		
		  C++ signature :
			  long getButtonVirtualKey(enum Game::Util::Input::STG::KEY_ID)
		"""
		
		return Game.Input.getButtonVirtualKey(keyId)
Input = _Input()

_InputController = Game.InputController
_InputController.__doc__ = """
入力コントローラークラス

__init__ = <built-in function __init__>
  Raises an exception
  This class cannot be instantiated from Python

@ivar direction: 入力されている方向のベクトル
ベクトルの絶対値の範囲は、[0, 1]です。
"""

_InputController.isFree.__doc__ = """
押されていない状態かを取得します

isFree( (InputController)self, (KeyId)key) -> bool :

@param key: キーのID
@return: TrueまたはFalse

  C++ signature :
	  bool isFree(
	  class Defs::Util::Input::Controller {lvalue},
	  enum Game::Util::Input::STG::KEY_ID)
"""

_InputController.isPull.__doc__ = """
離した瞬間かを取得します

isPull( (InputController)self, (KeyId)key) -> bool :

@param key: キーのID
@return: TrueまたはFalse

  C++ signature :
	  bool isPull(
	  class Defs::Util::Input::Controller {lvalue},
	  enum Game::Util::Input::STG::KEY_ID)
"""

_InputController.isPush.__doc__ = """
押した瞬間かを取得します

isPush( (InputController)self, (KeyId)key) -> bool :

@param key: キーのID
@return: TrueまたはFalse

  C++ signature :
	  bool isPush(
	  class Defs::Util::Input::Controller {lvalue},
	  enum Game::Util::Input::STG::KEY_ID)
"""

_InputController.isHold.__doc__ = """
ホールド状態かを取得します

isHold( (InputController)self, (KeyId)key) -> bool :

@param key: キーのID
@return: TrueまたはFalse

  C++ signature :
	  bool isHold(
	  class Defs::Util::Input::Controller {lvalue},
	  enum Game::Util::Input::STG::KEY_ID)
"""


class _Scene:
	"""ゲームのシーンに関する機能を提供するクラス"""
	
	def changeScene(self, scene, waitFrameNum = 60):
		"""
		指定したシーンに遷移します
		
		@param scene: シーンオブジェクト
		@param waitFrameNum: 遷移する前に待つフレーム数
		
		シーンオブジェクトは以下のインターフェイスを持っていなければなりません。
			update() -> None
		
		  C++ signature :
			  void changeScene(class boost::python::api::object)
		"""
		
		if waitFrameNum > 0:
			Game.Scene.changeScene(
				WaitScene(
					waitFrameNum, 
					lambda: Game.Scene.changeScene(scene)))
		else:
			Game.Scene.changeScene(scene)
	
	@property
	def end(self):
		"""ゲーム終了フラグの取得"""
		
		return Game.Scene.isEnd
	@end.setter
	def end(self, end):
		"""ゲームを終了させます"""
		
		if end:
			Game.Scene.end()
	
	def changeToSTGTitle(self, waitFrameNum = 60):
		"""
		STGタイトルシーンへ遷移します
		
		@param waitFrameNum: 遷移する前に待つフレーム数
		"""
		
		if waitFrameNum > 0:
			self.changeScene(
				WaitScene(
					waitFrameNum, 
					lambda: Game.Scene.changeToSTGTitle()), 0)
		else:
			Game.Scene.changeToSTGTitle()
	
	def changeToSTG(self, stageSetId, myShipId, waitFrameNum = 60):
		"""
		STGシーンへ遷移します
		
		@param stageSetId: ステージセットID
		@param myShipId: 自機ID
		@param waitFrameNum: 遷移する前に待つフレーム数
		"""
		
		if waitFrameNum > 0:
			self.changeScene(
				WaitScene(
					waitFrameNum, 
					lambda: Game.Scene.changeToSTG(stageSetId, myShipId)), 0)
		else:
			Game.Scene.changeToSTG(stageSetId, myShipId)
Scene = _Scene()

class WaitScene:
	"""
	何もせずに待つシーンです
	
	指定したフレーム数だけ待機し、その後指定した関数を実行します。
	"""
	
	def __init__(self, frameNum, action):
		"""
		コンストラクタ
		
		@ivar frameCount: 待機するフレーム数
		@ivar action: 待機後に実行する関数
		"""
		
		self.frameCount = frameNum
		self.action = action
		
	def update(self):
		"""状態を更新します"""
		
		if self.frameCount > 0:
			self.frameCount -= 1
		else:
			self.action()

class _Sound:
	"""
	サウンドに関する機能を提供するクラス
	
	ここでの操作は、LoadStaticまたはLoadStreamで作成した全てのインスタンスに適用されます。
	"""
	
	def loadStatic(self, file, layerCount = 1):
		"""
		効果音用のサウンドファイルを読み込みます
		
		@param file: ファイルのパス、またはFileObject
		@param layerCount: レイヤー数
		@return: Sound_Static
		
		Waveファイルのみ読み込めます
		
		  C++ signature :
			  class Defs::Util::Sound::Static loadStatic(
			  	class std::basic_string<wchar_t,struct std::char_traits<wchar_t>,class std::allocator<wchar_t> >,
			  	long)
			  class Defs::Util::Sound::Static loadStatic(
			  	class Defs::Util::File::FileObject,long)
		"""
		
		return Game.Sound.loadStatic(file, layerCount)
	
	def loadStream(self, file):
		"""
		BGM用のサウンドファイルを読み込みます
		
		@param file: ファイルのパス、またはFileObject
		@return: Sound_Stream
		
		WaveファイルとOGGファイルを読み込めます
		
		  C++ signature :
			  class Defs::Util::Sound::Stream loadStream(
			  	class std::basic_string<wchar_t,struct std::char_traits<wchar_t>,class std::allocator<wchar_t> >)
			  class Defs::Util::Sound::Stream loadStream(
			  	class Defs::Util::File::FileObject)
		"""
		
		return Game.Sound.loadStream(file)
	
	@property
	def staticVolumes(self):
		"""
		効果音のボリュームを取得します
		
		@return: ボリューム[0, 1]
		
		  C++ signature :
			  float getStaticVolumes()
		"""
		
		return Game.Sound.getStaticVolumes()
	@staticVolumes.setter
	def staticVolumes(self, volume):
		"""
		効果音のボリュームを変更します
		
		@param volume: ボリューム[0, 1]
		
		  C++ signature :
			  void setStaticVolumes(float)
		"""
		
		Game.Sound.setStaticVolumes(volume)
	
	@property
	def streamVolumes(self):
		"""
		BGMのボリュームを取得します
		
		@return: ボリューム[0, 1]
		
		  C++ signature :
			  float getStreamVolumes()
		"""
		
		return Game.Sound.getStreamVolumes()
	@streamVolumes.setter
	def streamVolumes(self, volume):
		"""
		BGMのボリュームを変更します
		
		@param volume: ボリューム[0, 1]
		
		  C++ signature :
			  void setStreamVolumes(float)
		"""
		
		Game.Sound.setStreamVolumes(volume)
	
	def stopStatics(self):
		"""
		効果音を停止します
		
		  C++ signature :
			  void stopStatics()
		"""
		
		Game.Sound.stopStatics()
	
	def stopStreams(self):
		"""
		BGMを停止します
		
		  C++ signature :
			  void stopStreams()
		"""
		
		Game.Sound.stopStreams()
	
	def pauseStatics(self):
		"""
		効果音を一時停止/解除します
		
		  C++ signature :
			  void pauseStatics()
		"""
		
		Game.Sound.pauseStatics()
	
	def pauseStreams(self):
		"""
		BGMを一時停止/解除します
		
		  C++ signature :
			  void pauseStreams()
		"""
		
		Game.Sound.pauseStreams()
	
	@property
	def playingStatics(self):
		"""
		効果音が再生されているかをチェックします
		
		@return: 再生されていればTrue、されていなければFalse
		
		  C++ signature :
			  bool isPlayStatics()
		"""
		
		return Game.Sound.isPlayStatics()
	
	@property
	def playingStreams(self):
		"""
		BGMが再生されているかをチェックします
		
		@return: 再生されていればTrue、されていなければFalse
		
		  C++ signature :
			  bool isPlayStreams()
		"""
		
		return Game.Sound.isPlayStreams()
	
	def fadeInStreams(self, seconds):
		"""
		BGMをフェードインさせます
		
		@param second: フェードインにかける秒数
		
		  C++ signature :
			  void fadeInStreams(float)
		"""
		
		Game.Sound.fadeInStreams(seconds)
	
	def fadeOutStreams(self, seconds):
		"""
		BGMをフェードアウトさせます
		
		@param second: フェードアウトにかける秒数
		
		  C++ signature :
			  void fadeOutStreams(float)
		"""
		
		Game.Sound.fadeOutStreams(seconds)
Sound = _Sound()

_Sound_Static = Game.Sound_Static
_Sound_Static.__doc__ = """
効果音を表すクラス

__init__ = <built-in function __init__>
  Raises an exception
  This class cannot be instantiated from Python

@ivar waitingForPlay: レイヤーがすべで再生状態の時に待つかどうか
"""

_Sound_Static.play.__doc__ = """
再生します

play( (Sound_Static)self) -> None :
	'''
	  C++ signature :
		  void play(class Defs::Util::Sound::Static {lvalue})
	'''

play( (Sound_Static)self, (bool)loop) -> None :
	'''
	@param loop: ループ可否
	
	  C++ signature :
		  void play(
		  class Defs::Util::Sound::Static {lvalue},
		  bool)
	'''
"""

_Sound_Static.stop.__doc__ = """
停止します

stop( (Sound_Static)self) -> None :

  C++ signature :
	  void stop(class Defs::Util::Sound::Static {lvalue})
"""

_Sound_Static.pause.__doc__ = """
一時停止/解除します

pause( (Sound_Static)self) -> None :

  C++ signature :
	  void pause(class Defs::Util::Sound::Static {lvalue})
"""

_Sound_Static.isPause.__doc__ = """
一時停止しているかをチェックします

isPause( (Sound_Static)self) -> bool :

@return: 一時停止していればTrue、していなければFalse

  C++ signature :
	  bool isPause(class Defs::Util::Sound::Static {lvalue})
"""

_Sound_Static.isPlay.__doc__ = """
再生しているかをチェックします

isPlay( (Sound_Static)self) -> bool :

@return: 再生していればTrue、していなければFalse

  C++ signature :
	  bool isPlay(class Defs::Util::Sound::Static {lvalue})
"""

_Sound_Static.setVolume.__doc__ = """
ボリュームを設定します

setVolume( (Sound_Static)self, (float)volume) -> None :

@param volume: ボリューム[0, 1]

  C++ signature :
	  void setVolume(
	  class Defs::Util::Sound::Static {lvalue},
	  float)
"""

_Sound_Stream = Game.Sound_Stream
_Sound_Stream.__doc__ = """
BGMを表すクラス

__init__ = <built-in function __init__>
  Raises an exception
  This class cannot be instantiated from Python
"""

_Sound_Stream.play.__doc__ = """
再生します

play( (Sound_Stream)self [, (object)playBlocks]) -> None :
	'''
	@param playBlocks: StreamSoundPlayBlockのシーケンス
	
	  C++ signature :
		  void play(
		  class Defs::Util::Sound::Stream {lvalue} 
		  [,class boost::python::api::object])
	'''

play( (Sound_Stream)self, (int)loopCount) -> None :
	'''
	@param loopCount: ループ数
	
	  C++ signature :
		  void play(
		  class Defs::Util::Sound::Stream {lvalue},
		  unsigned long)
	'''
"""

_Sound_Stream.stop.__doc__ = """
停止します

stop( (Sound_Stream)self) -> None :

  C++ signature :
	  void stop(class Defs::Util::Sound::Stream {lvalue})
"""

_Sound_Stream.pause.__doc__ = """
一時停止/解除します

pause( (Sound_Stream)self) -> None :

  C++ signature :
	  void pause(class Defs::Util::Sound::Stream {lvalue})
"""

_Sound_Stream.isPlay.__doc__ = """
再生しているかをチェックします

isPlay( (Sound_Stream)self) -> bool :

@return: 再生していればTrue、していなければFalse

  C++ signature :
	  bool isPlay(class Defs::Util::Sound::Stream {lvalue})
"""

_Sound_Stream.setVolume.__doc__ = """
ボリュームを設定します

setVolume( (Sound_Stream)self, (float)volume) -> None :

@param volume: ボリューム[0, 1]

  C++ signature :
	  void setVolume(
	  class Defs::Util::Sound::Stream {lvalue},
	  float)
"""

_Sound_Stream.fadeIn.__doc__ = """
フェードインさせます

fadeIn( (Sound_Stream)self, (float)second) -> None :

@param second: フェードインにかける秒数

  C++ signature :
	  void fadeIn(
	  class Defs::Util::Sound::Stream {lvalue},
	  float)
"""

_Sound_Stream.fadeOut.__doc__ = """
フェードアウトさせます

fadeOut( (Sound_Stream)self, (float)second) -> None :

@param second: フェードアウトにかける秒数

  C++ signature :
	  void fadeOut(
	  class Defs::Util::Sound::Stream {lvalue},
	  float)
"""

class StreamSoundPlayBlock:
	"""
	ストリームサウンド再生パラメータ
	
	ストリームサウンドの再生を行うためのテーブルデータです。
	"""
	
	def __init__(self, loopCount = None, startTime = None, endTime = None):
		"""
		コンストラクタ
		
		@ivar loopCount: このテーブルのループ数（Noneで無限ループ）
		@ivar startTime: 再生開始位置（秒指定）（Noneで最初から）
		@ivar endTime: 再生終了位置（秒指定）（Noneで最後まで）
		"""
		
		self.loopCount = loopCount
		self.startTime = startTime
		self.endTime = endTime


class _Sprite:
	"""スプライトに関する機能を提供するクラス"""
	
	# アルファブレンディングの定義
	AlphaBlend = Game.AlphaBlend
	
	DrawParam = Game.SpriteDrawParam
	DrawParam.__doc__ = """
	矩形描画用パラメータクラス
	
	@ivar texture: 描画テクスチャ（NULLでColor単色塗りつぶし）
	@ivar src: 描画元
	@ivar dst: 描画先
	@ivar priority: 描画優先度（値が大きい程手前に描画される）
	@ivar alphaBlend: アルファブレンディングの種類
	@ivar filtering: フィルタ適用可否
	@ivar rotDegree: 回転角度
	@ivar rotOffset: 回転時の中心からのオフセット
	@ivar color: 描画色（テクスチャの色に乗算）
	@ivar shakable: 振動可否
	@ivar flipedX: 左右反転しているか
	@ivar flipedY: 上下反転しているか
	"""
	
	DrawParam.__init__.__doc__ = """
	コンストラクタ
	
	__init__( (object)self) -> None :
		'''
		デフォルト状態で初期化します
		
		  C++ signature :
			  void __init__(struct _object * __ptr64)
		'''
	
	__init__( (object)self, (SpriteDrawParam)drawParam) -> None :
		'''
		他のオブジェクトの状態をコピーして初期化します
		
		@param drawParam: 他のオブジェクト
		
		  C++ signature :
			  void __init__(
			  struct _object * __ptr64,
			  class Game::Util::Sprite::DrawParameter)
		'''
	
	__init__( (object)self, (SpriteTexture)texture, (RectF)src, (RectF)dst, 
		[(int)priority, (AlphaBlend)alphaBlend, (bool)filtering, 
		(float)rotDegree, (Point2DF)rotOffset, (ColorF)color, (bool)shakable]) -> None :
		'''
		各種パラメータを指定して初期化します
		
		@param texture: 描画テクスチャ
		@param src: 描画元
		@param dst: 描画先
		@param priority: 描画優先度
		@param alphaBlend: アルファブレンディング
		@param filtering: フィルタ適用可否
		@param rotDegree: 回転角度
		@param rotOffset: 回転中心オフセット
		@param color: 描画色
		@param shakable: 振動可否
		
		  C++ signature :
			  void __init__(
			  struct _object * __ptr64,
			  class boost::intrusive_ptr<class Selene::Engine::Graphics::Resource::ITexture>,
			  class Selene::Rect<float>,
			  class Selene::Rect<float>,
			  long,
			  enum Game::Util::Sprite::AlphaBlend,
			  bool,
			  float,
			  class Selene::Point2D<float>,
			  struct Selene::ColorF,
			  bool)
		 '''
	"""
	
	DrawParam.flipX.__doc__ = """
	左右反転させます
	
	flipX( (SpriteDrawParam)self) -> None :
	
	  C++ signature :
		  void flipX(class Game::Util::Sprite::DrawParameter {lvalue})
	"""
	
	DrawParam.flipY.__doc__ = """
	上下反転させます
	
	flipY( (SpriteDrawParam)self) -> None :
	
	  C++ signature :
		  void flipY(class Game::Util::Sprite::DrawParameter {lvalue})
	"""
	
	class Animation:
		"""スプライトアニメーションクラス"""
		
		class FrameHolder:
			"""スプライトアニメーションのフレーム管理クラス"""
			
			Sequence = Game.SpriteAnimationSequenceFrameHolder
			Sequence.__doc__ = """
			スプライトアニメーションのフレーム管理クラス
			
			複数のテクスチャを用いてアニメーションを実現します。
			
			@ivar frameNum: フレーム数
			@ivar framePos: 現在のフレーム位置
			@ivar drawParameter: 描画パラメータ
			"""
			
			Sequence.__init__.__doc__ = """
			コンストラクタ
			
			テクスチャのシーケンスと描画パラメータで初期化します。
			
			__init__( (object)self, (object)textureList, (SpriteDrawParam)drawParam) -> None :
			
			@param textureList: テクスチャのシーケンス
			@param drawParam: 描画パラメータ
			
			  C++ signature :
				  void __init__(
				  struct _object * __ptr64,
				  class boost::python::api::object,
				  class Game::Util::Sprite::DrawParameter)
			"""
			
			Texture = Game.SpriteAnimationTextureFrameHolder
			Texture.__doc__ = """
			スプライトアニメーションのフレーム管理クラス
			
			複数のテクスチャを用いてアニメーションを実現します。
			
			@ivar frameNum: フレーム数
			@ivar framePos: 現在のフレーム位置
			@ivar drawParameter: 描画パラメータ
			"""
			
			Texture.__init__.__doc__ = """
			コンストラクタ
			
			フレームサイズとフレーム数と描画パラメータで初期化します
			
			__init__( (object)self, (Point2DI)frameSize, (int)frameNum, (SpriteDrawParam)drawParam) -> None :
			
			@param frameSize: フレームサイズ
			@param frameNum: フレーム数
			@param drawParam: 描画パラメータ
			
			  C++ signature :
				  void __init__(
				  struct _object * __ptr64,
				  class Selene::Point2D<long>,
				  unsigned int,
				  class Game::Util::Sprite::DrawParameter)
			"""
		Manager = Game.SpriteAnimationManager
		Manager.__doc__ = """
		スプライトアニメーション管理クラス
		
		@ivar frameHolder: フレーム管理クラス
		@ivar frameInterval: フレーム間隔
		@ivar playing: 再生中かどうか
		"""
		
		Manager.__init__.__doc__ = """
		コンストラクタ
		
		フレーム管理クラスとフレーム間隔を用いて初期化します
		
		__init__( (object)self, (SpriteAnimationFrameHolder)frameHolder [, (float)frameInterval]) -> None :
		
		@param frameHolder: フレーム管理クラス
		@param frameInterval: フレーム間隔
		
		  C++ signature :
			  void __init__(
			  struct _object * __ptr64,
			  class boost::shared_ptr<class Defs::Util::Sprite::Animation::FrameHolder::IFrameHolder>,
			  float)
		"""
		
		Manager.update.__doc__ = """
		状態を更新します
		
		update( (SpriteAnimationManager)self) -> None :
		
		  C++ signature :
			  void update(class Defs::Util::Sprite::Animation::Manager {lvalue})
		"""
		
		Manager.draw.__doc__ = """
		フレームを描画します
		
		draw( (SpriteAnimationManager)self) -> None :
		
		  C++ signature :
			  void draw(class Defs::Util::Sprite::Animation::Manager {lvalue})
		"""
		
		Manager.play.__doc__ = """
		再生します
		
		play( (SpriteAnimationManager)self [, (int)framePos]) -> None :
		
		@param framePos: 再生開始フレーム位置
		
		  C++ signature :
			  void play(
			  class Defs::Util::Sprite::Animation::Manager {lvalue},
			  unsigned int)
		"""
	
	def draw(self, param):
		"""
		矩形を描画します
		
		@param drawParam: 描画パラメータ
		
		  C++ signature :
			  void draw(class Game::Util::Sprite::DrawParameter)
		"""
		
		Game.Sprite.draw(param)
	
	def loadTexture(self, *args):
		"""
		テクスチャを読み込みます
		
		TGA/BMP/JPG/PNG/DDSファイルを読み込むことができます。
		
		loadTexture( (str)path [, (bool)mipmap [, (ColorF)colorKey]]) -> SpriteTexture :
			'''
			@param path: 画像ファイルのパス文字列
			@param mipmap: ミップマップの有無
			@param colorKey: カラーキー カラーキーを利用しない場合は(0,0,0,0)
			@return: SpriteTexture
			
			  C++ signature :
				  class boost::intrusive_ptr<class Selene::Engine::Graphics::Resource::ITexture> 
				  loadTexture(
				  class std::basic_string<wchar_t,struct std::char_traits<wchar_t>,class std::allocator<wchar_t> >,
				  bool,
				  struct Selene::ColorF)
			'''
		
		loadTexture( (FileObject)file [, (bool)mipmap [, (ColorF)colorKey]]) -> SpriteTexture :
			'''
			@param file: FileObject
			@param mipmap: ミップマップの有無
			@param colorKey: カラーキー カラーキーを利用しない場合は(0,0,0,0)
			@return: SpriteTexture
			
			  C++ signature :
				  class boost::intrusive_ptr<class Selene::Engine::Graphics::Resource::ITexture> 
				  loadTexture(
				  class Defs::Util::File::FileObject,
				  bool,
				  struct Selene::ColorF)
			'''
		"""
		
		return Game.Sprite.loadTexture(*args)
	
	def setShake(self, *args):
		"""
		振動エフェクトを設定します
		
		setShake( (float)amount [, (float)decreaseAmount]) -> None :
			'''
			@param amount: 振動量
			@param decreaseAmount: 振動減衰量
			
			  C++ signature :
				  void setShake(
				  float,
				  float)
			'''
		
		setShake( (Point2DF)amount2D [, (float)decreaseAmount]) -> None :
			'''
			@param amount2D: 振動量
			@param decreaseAmount: 振動減衰量
			
			  C++ signature :
				  void setShake(
				  class Selene::Point2D<float>,
				  float)
			'''
		"""
		
		Game.Sprite.setShake(*args)
	
	def stopShake(self):
		"""
		振動エフェクトを一時停止します
		
		stopShake() -> None :
		
		  C++ signature :
			  void stopShake()
		"""
		
		Game.Sprite.stopShake()
	
	def startShake(self):
		"""
		振動エフェクトを再開します
		
		startShake() -> None :
		
		  C++ signature :
			  void startShake()
		"""
		
		Game.Sprite.startShake()
	
	def resetShake(self):
		"""
		振動エフェクトをリセットします
		
		resetShake() -> None :
		
		  C++ signature :
			  void resetShake()
		"""
		
		Game.Sprite.resetShake()
	
	@property
	def shakeAmount(self):
		"""現在の振動量を取得します"""
		
		return Game.Sprite.getCurrentShakeAmount()
Sprite = _Sprite()

_SpriteTexture = Game.SpriteTexture
_SpriteTexture.__doc__ = """
テクスチャを表すクラス

__init__ = <built-in function __init__>
  Raises an exception
  This class cannot be instantiated from Python
"""

_SpriteTexture.getRequestSize.__doc__ = """
テクスチャーの生成時の要求サイズを取得します

getRequestSize( (SpriteTexture)self) -> Point2DI :

@return: 生成時の要求サイズ

  C++ signature :
	  class Selene::Point2D<long> getRequestSize(
	  class Selene::Engine::Graphics::Resource::ITexture {lvalue})
"""

_SpriteTexture.getTextureSize.__doc__ = """
テクスチャーの生成後の実際のサイズを取得します

getTextureSize( (SpriteTexture)self) -> Point2DI :

@return: 生成後の実際のサイズ

  C++ signature :
	  class Selene::Point2D<long> getTextureSize(
	  class Selene::Engine::Graphics::Resource::ITexture {lvalue})
"""

_SpriteTexture.getTexel2UVTransform.__doc__ = """
テクスチャのピクセル位置をUVに変換する為の値を取得します

getTexel2UVTransform( (SpriteTexture)self) -> Point2DF :

@return: テクスチャのピクセル位置をUVに変換する為の値

この値は 1.0 / getTextureSize() と同じものです。

  C++ signature :
	  class Selene::Point2D<float> getTexel2UVTransform(
	  class Selene::Engine::Graphics::Resource::ITexture {lvalue})
"""

_SpriteTexture.saveToBMP.__doc__ = """
テクスチャをBMPファイルとして保存します

saveToBMP( (SpriteTexture)self, (object)filePath) -> None :

@param: filePath: ファイルパス

  C++ signature :
	  void saveToBMP(
	  class Selene::Engine::Graphics::Resource::ITexture {lvalue},
	  wchar_t const * __ptr64)
"""

_SpriteTexture.saveToPNG.__doc__ = """
テクスチャをPNGファイルとして保存します

saveToPNG( (SpriteTexture)self, (object)filePath) -> None :

@param: filePath: ファイルパス

  C++ signature :
	  void saveToPNG(
	  class Selene::Engine::Graphics::Resource::ITexture {lvalue},
	  wchar_t const * __ptr64)
"""

_SpriteTexture.saveToDDS.__doc__ = """
テクスチャをDDSファイルとして保存します

saveToDDS( (SpriteTexture)self, (object)filePath) -> None :

@param: filePath: ファイルパス

  C++ signature :
	  void saveToDDS(
	  class Selene::Engine::Graphics::Resource::ITexture {lvalue},
	  wchar_t const * __ptr64)
"""


sin = Game.sin
sin.__doc__ = """
指定した度数の正弦を取得する

sin( (float)degree) -> float :

@param degree: 度数
@return: 正弦値

	C++ signature :
		float sin(float)
"""

cos = Game.cos
cos.__doc__ = """
指定した度数の余弦を取得する

cos( (float)degree) -> float :

@param degree: 度数
@return: 余弦値

	C++ signature :
		float cos(float)
"""

atan2 = Game.atan2
atan2.__doc__ = """
指定した座標の逆正接を度数で取得する

atan2( (float)y, (float)x) -> float :

@param y: Y座標
@param x: X座標
@return: 度数

	C++ signature :
		float atan2(float,float)
"""