'''
Created on 2011/03/04

@author: t

このモジュールでは、STG画面における機能を提供します。
'''

import Game


def getController():
	"""
	入力コントローラーを取得します
	
	@return: 入力コントローラー
	"""
	
	return Game.STG.getController()


def getRandom():
	"""
	乱数オブジェクトを取得します
	
	@return: 乱数オブジェクト
	"""
	
	return Game.STG.getRandom()

_Random = Game.Random
_Random.__doc__ = """
乱数クラス

__init__ = <built-in function __init__>
  Raises an exception
  This class cannot be instantiated from Python
"""

_Random.getInt.__doc__ = """
最小値と最大値を指定して、整数の乱数を取得します

getInt( (Random)self, (int)min, (int)max) -> int :

@param min: 最小値
@param max: 最大値
@return: 整数の乱数値
"""

_Random.getFloat.__doc__ = """
最小値と最大値を指定して、浮動小数点数の乱数を取得します

getFloat( (Random)self, (float)min, (float)max) -> float :

@param min: 最小値
@param max: 最大値
@return: 浮動小数点数の乱数値
"""

_Random.getBool.__doc__ = """
真偽値をランダムに取得します

getBool( (Random)self) -> bool :

@return: TrueまたはFalse
"""


def getNextStage():
	"""
	次のステージオブジェクトを取得します
	
	@return: STGStage
	"""
	
	return Game.STG.getNextStage()


def getDebugStrFlag():
	"""
	デバッグ文字列表示が有効かどうかを取得します
	
	@return: TrueまたはFalse
	"""
	
	return Game.STG.getDebugStrFlag()


def setDebugStrFlag(flag):
	"""
	デバッグ文字列表示を設定します
	
	@param flag: 有効フラグ
	"""
	
	Game.STG.setDebugStrFlag(flag)
	
	
def restart():
	"""STGシーンをリスタートします"""
	
	Game.STG.restart()


def genObjectId():
	"""
	オブジェクトIDを生成します
	
	このIDは、主にアクターオブジェクトを識別するときに使用されます。
	
	@return: オブジェクトID
	"""
	
	return Game.STG.genObjectId()

# STGシーンの描画優先度の定義
DrawPriority = Game.STGDrawPriority


class _Actor:
	"""アクターオブジェクトに関連する機能を提供するクラス"""
	
	@property
	def myShip(self):
		"""
		自機オブジェクトを取得します
		
		@return: STGMyShip
		"""
		
		return Game.STG.getActors().getMyShip()
	
	@property
	def actorRange(self):
		"""
		全てのアクターオブジェクトへアクセスするためのイテレータを取得します
		
		このイテレータを用いた操作は負荷が高いため、処理落ちにつながる恐れがあります。
		
		@return: STGActorを得るためのイテレータ
		"""
		
		return Game.STG.getActors().getActorRange()
	
	@property
	def bulletRange(self):
		"""
		全ての敵弾オブジェクトへアクセスするためのイテレータを取得します
		
		このイテレータを用いた操作は負荷が高いため、処理落ちにつながる恐れがあります。
		
		@return: STGBulletを得るためのイテレータ
		"""
		
		return Game.STG.getActors().getBulletRange()
	
	@property
	def enemyRange(self):
		"""
		全ての敵オブジェクトへアクセスするためのイテレータを取得します
		
		このイテレータを用いた操作は負荷が高いため、処理落ちにつながる恐れがあります。
		
		@return: STGEnemyを得るためのイテレータ
		"""
		
		return Game.STG.getActors().getEnemyRange()
	
	@property
	def itemRange(self):
		"""
		全てのアイテムオブジェクトへアクセスするためのイテレータを取得します
		
		このイテレータを用いた操作は負荷が高いため、処理落ちにつながる恐れがあります。
		
		@return: STGItemを得るためのイテレータ
		"""
		
		return Game.STG.getActors().getItemRange()
	
	@property
	def myShotRange(self):
		"""
		全ての自機ショットオブジェクトへアクセスするためのイテレータを取得します
		
		このイテレータを用いた操作は負荷が高いため、処理落ちにつながる恐れがあります。
		
		@return: STGMyShotを得るためのイテレータ
		"""
		
		return Game.STG.getActors().getMyShotRange()
	
	
	def detectBulletHit(self, hitObj):
		"""
		当たり判定をして、敵弾オブジェクトを取得します
		
		@return: STGBullet
		"""
		
		return Game.STG.getActors().detectBulletHit(hitObj)
	
	def detectEnemyHit(self, hitObj):
		"""
		当たり判定をして、敵オブジェクトを取得します
		
		@return: STGEnemy
		"""
		
		return Game.STG.getActors().detectEnemyHit(hitObj)
	
	def detectItemHit(self, hitObj):
		"""
		当たり判定をして、アイテムオブジェクトを取得します
		
		@return: STGItem
		"""
		
		return Game.STG.getActors().detectItemHit(hitObj)
	
	def detectMyShotHit(self, hitObj):
		"""
		当たり判定をして、自機ショットオブジェクトを取得します
		
		@return: STGMyShot
		"""
		
		return Game.STG.getActors().detectMyShotHit(hitObj)
	
	
	def registerActor(self, actor):
		"""
		アクターオブジェクトをシステムに登録します
		
		@param actor: STGActorに準ずるオブジェクト
		"""
		
		Game.STG.getActors().registerActor(actor)
	
	def registerBullet(self, bullet):
		"""
		敵弾オブジェクトをシステムに登録します
		
		@param bullet: STGBulletに準ずるオブジェクト
		"""
		
		Game.STG.getActors().registerBullet(bullet)
	
	def registerEnemy(self, enemy):
		"""
		敵オブジェクトをシステムに登録します
		
		@param enemy: STGEnemyに準ずるオブジェクト
		"""
		
		Game.STG.getActors().registerEnemy(enemy)
	
	def registerItem(self, item):
		"""
		アイテムオブジェクトをシステムに登録します
		
		@param itemr: STGItemに準ずるオブジェクト
		"""
		
		Game.STG.getActors().registerItem(item)
	
	def registerMyShot(self, myShot):
		"""
		自機ショットオブジェクトをシステムに登録します
		
		@param myShot: STGMyShotに準ずるオブジェクト
		"""
		
		Game.STG.getActors().registerMyShot(myShot)
Actor = _Actor()


class _Conf:
	def registerMyShip(self, name, coreModule):
		"""
		自機の生成情報をシステムに登録します
		
		@param name: 自機の名前
		@param coreModule: Coreクラスを含んだモジュール
		@return: 生成ID
		"""
		
		return Game.STGConf.registerMyShip(name, coreModule)
	
	def registerStageSet(self, name, coreModule, pauseViewCoreModule):
		"""
		ステージセットの生成情報をシステムに登録します
		
		@param name: ステージセットの名前
		@param coreModule: Coreクラスを含んだモジュール
		@param pauseViewCoreModule: ポーズ画面のCoreクラスを含んだモジュール
		@return: 生成ID
		"""
		
		return Game.STGConf.registerStageSet(name, coreModule, pauseViewCoreModule)
	
	def registerStage(self, stageSetId, name, coreModule):
		"""
		ステージの生成情報をシステムに登録します
		
		@param stageSetId: ステージセットの生成ID
		@param name: ステージの名前
		@param coreModule: Coreクラスを含んだモジュール
		@return: 生成ID
		"""
		
		return Game.STGConf.registerStage(stageSetId, name, coreModule)
	
	def getStageSetInfoList(self):
		"""
		ステージセットの情報を取得します
		
		@return: 生成IDと名前のタプルのリスト
		"""
		
		return Game.STGConf.getStageSetInfoList()
	
	def getMyShipInfoList(self):
		"""
		自機の情報を取得します
		
		@return: 生成IDと名前のタプルのリスト
		"""
		
		return Game.STGConf.getMyShipInfoList()
	
	
	def readSetting(self):
		"""ゲームの一般設定を読み込みます"""
		
		Game.STGConf.readSetting()
	
	def writeSetting(self):
		"""ゲームの一般設定を書き込みます"""
		
		Game.STGConf.writeSetting()
	
	@property
	def fullScreen(self):
		"""
		フルスクリーン情報を取得します
		
		@return: Trueでフルスクリーン、Falseでウィンドウ
		"""
		
		return Game.STGConf.getScreenMode()
	@fullScreen.setter
	def fullScreen(self, fullScreen):
		"""
		フルスクリーン情報を設定します
		
		@param fullScreen: Trueでフルスクリーン、Falseでウィンドウ
		"""
		
		Game.STGConf.setScreenMode(fullScreen)
	
	@property
	def bgmVolume(self):
		"""
		BGMのボリュームを取得します
		
		@return: ボリューム[0, 100]
		"""
		
		return Game.STGConf.getBGMVolume()
	@bgmVolume.setter
	def bgmVolume(self, volume):
		"""
		BGMのボリュームを設定します
		
		@param volume:  ボリューム[0, 100]
		"""
		
		Game.STGConf.setBGMVolume(volume)
	
	@property
	def seVolume(self):
		"""
		効果音のボリュームを取得します
		
		@return: ボリューム[0, 100]
		"""
		
		return Game.STGConf.getSEVolume()
	@seVolume.setter
	def seVolume(self, volume):
		"""
		効果音のボリュームを設定します
		
		@param volume:  ボリューム[0, 100]
		"""
		
		Game.STGConf.setSEVolume(volume)
	
	def attachControllerAxis(self, axisId):
		"""
		コントローラーの軸の設定をします
		
		@param axisId: 軸のID
		@return: 仮想キー　入力されていない時はNone
		"""
		
		vKey = Game.STGConf.attachControllerAxis(axisId)
		if vKey == -1:
			return None
		else:
			return vKey
	
	def getAxisVirtualKey(self, axisId):
		"""
		軸に割り当てられている仮想キーを取得します
		
		@param axisId: 軸のID
		@return: 仮想キー　割り当てられていない時はNone
		"""
		
		vKey = Game.STGConf.getAxisVirtualKey(axisId)
		if vKey == -1:
			return None
		else:
			return vKey
	
	def attachControllerButton(self, keyId):
		"""
		コントローラーのボタンの設定をします
		
		@param keyId: キーのID
		@return: 仮想キー　入力されていない時はNone
		"""
		
		vKey = Game.STGConf.attachControllerButton(keyId)
		if vKey == -1:
			return None
		else:
			return vKey
	
	def getButtonVirtualKey(self, keyId):
		"""
		ボタンに割り当てられている仮想キーを取得します
		
		@param keyId: キーのID
		@return: 仮想キー　割り当てられていない時はNone
		"""
		
		vKey = Game.STGConf.getButtonVirtualKey(keyId)
		if vKey == -1:
			return None
		else:
			return vKey
	
	@property
	def maxFileCacheSize(self):
		"""
		総キャッシュサイズの最大値を取得します
		
		@return: 最大値
		"""
		
		return Game.STGConf.getMaxFileCacheSize()
	@maxFileCacheSize.setter
	def maxFileCacheSize(self, size):
		"""
		総キャッシュサイズの最大値を設定します
		
		@param size: 最大値
		"""
		
		Game.STGConf.setMaxFileCacheSize(size)
	
	def setDefaultSetting(self):
		"""
		デフォルトの設定を読み込みます
		"""
		
		Game.STGConf.setDefaultSetting()
Conf = _Conf()