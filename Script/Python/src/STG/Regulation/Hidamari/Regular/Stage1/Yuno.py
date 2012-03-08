'''
Created on 2011/12/25

@author: t

ゆのっちの各種パラメータを定義します
'''

# 耐久力
hp = 20000

# 攻撃フェーズ2移行の耐久力の閾値
phase2Threshold = hp * 2/3

# 初期ランク
initialRank = 1.0
# ランク増加率
rankIncrement = 0.1
# 攻撃フェーズ1からフェーズ2への増加ランク持ち越し率
rankCarryOverRate = 0


class PrimalArmor:
	"""PAのパラメータを定義します"""
	
	# 半径
	radius = 200
	
	# 容量
	capacity = 30000
	# フレーム毎に補充される量
	supply = 30
	
	# 再展開閾値
	# PA消滅時にこの値まで回復するとPAが再展開されます
	generateThreshold = capacity
	
	# 自機への斥力
	forceToMyShip = 3
	# 自機ショットへの斥力
	forceToMyShot = 12
	# 自機ショットの減衰力
	damageToMyShot = 30
	
	# 自機ショット減衰力や斥力の、距離による1次減衰係数
	linearAttenuation = 0.0001
	# 自機ショット減衰力や斥力の、距離による2次減衰係数
	quadraticAttenuation = 0.00001
	
	# 自機ショット減衰力や斥力の、残量による減衰率の最小値
	# 自機ショットによるPAへのダメージも減衰します
	effectRateMin = 0.7


class Side:
	"""サイドパーツのパラメータを定義します"""
	
	# 耐久力
	sideHP = hp / 6
	
	# 本体へのダメージ率
	coreDamageRate = 0.2


class Phase1_1:
	"""攻撃フェーズ1-1のパラメータを定義します"""
	
	class ChainGun:
		"""
		チェインガンのパラメータを定義します
		
		self.rank と書くと、ランク値を参照できます。
		"""
		
		def __init__(self, rank):
			"""コンストラクタ"""
			self.rank = rank
		
		@property
		def firstWait(self):
			"""発射までに待機するフレーム数"""
			return 60
		
		@property
		def launchRepeat(self):
			"""発射のリピート回数"""
			return 3 * self.rank
		@property
		def angleInterval(self):
			"""弾の角度間隔"""
			return 6
		@property
		def wayNum(self):
			"""Way数"""
			return 3
		@property
		def speed(self):
			"""弾のスピード"""
			return 4 * self.rank * 0.8
		@property
		def launchInterval(self):
			"""リピート発射間の待機フレーム数"""
			return 2
	
	class Side:
		"""
		サイドパーツのパラメータを定義します
		
		self.rank と書くと、ランク値を参照できます。
		"""
		
		def __init__(self, rank):
			"""コンストラクタ"""
			self.rank = rank
		
		@property
		def launchInterval(self):
			"""発射間隔"""
			return 30 / self.rank
		@property
		def angleInterval(self):
			"""弾の角度間隔"""
			return 4
		@property
		def wayNum(self):
			"""Way数"""
			return 3
		@property
		def speed(self):
			"""弾のスピード"""
			return 3 * self.rank * 0.8


class Phase1_2:
	"""
	攻撃フェーズ1-2のパラメータを定義します
	
	self.rank と書くと、ランク値を参照できます。
	"""
	
	def __init__(self, rank):
		"""コンストラクタ"""
		self.rank = rank
	
	@property
	def firstWait(self):
		"""フェーズ1-1から移行した後の待機フレーム数"""
		return 60
	
	class Missile:
		"""
		ミサイルのパラメータを定義します
		
		self.rank と書くと、ランク値を参照できます。
		"""
		
		def __init__(self, rank):
			"""コンストラクタ"""
			self.rank = rank
		
		@property
		def launchNum(self):
			"""発射回数"""
			return 4 * self.rank
		@property
		def launchInterval(self):
			"""発射間隔"""
			return 40
		
		@property
		def missileHP(self):
			"""耐久力"""
			return 1
		@property
		def circlingAngle(self):
			"""旋回角度"""
			return 2.5
		@property
		def maxSpeed(self):
			"""最大速度"""
			return 6
		@property
		def accel(self):
			"""加速度"""
			return 0.8
		@property
		def triggerDistance(self):
			"""起爆する自機との距離"""
			return 50
		
		@property
		def circleBulletNum(self):
			"""円状に発射される弾の数"""
			return 16
		@property
		def circleBulletSpeed(self):
			"""円状に発射される弾のスピード"""
			return 3.5 * self.rank * 0.8
		
		@property
		def randomBulletLaunchFrameNum(self):
			"""自機に向かって発射される弾の発射フレーム数"""
			return 15
		@property
		def randomBulletLaunchNum(self):
			"""自機に向かって発射される弾のフレーム毎の発射数"""
			return 2
		@property
		def randomBulletPosVariance(self):
			"""自機に向かって発射される弾のブレの最小値と最大値"""
			return (-20, 20)
		@property
		def randomBulletSpeed(self):
			"""自機に向かって発射される弾のスピード"""
			return 5 * self.rank * 0.8


class Phase1_3:
	"""
	攻撃フェーズ1-3のパラメータを定義します
	
	self.rank と書くと、ランク値を参照できます。
	"""
	
	def __init__(self, rank):
		"""コンストラクタ"""
		self.rank = rank
	
	@property
	def firstWait(self):
		"""フェーズ1-2から移行した後の待機フレーム数"""
		return 90
	
	class ChainGun:
		"""
		チェインガンのパラメータを定義します
		
		self.rank と書くと、ランク値を参照できます。
		"""
		
		def __init__(self, rank):
			"""コンストラクタ"""
			self.rank = rank
		
		@property
		def launchRepeat(self):
			"""発射のリピート回数"""
			return 2
		@property
		def angleInterval(self):
			"""弾の角度間隔"""
			return 24
		@property
		def wayNum(self):
			"""Way数"""
			return 7
		@property
		def speed(self):
			"""弾のスピード"""
			return 3.8 * self.rank * 0.8
		@property
		def launchInterval(self):
			"""リピート発射間の待機フレーム数"""
			return 5
		@property
		def launchWait(self):
			"""次の発射までの待機フレーム数"""
			return 90
	
	class CrossCircle:
		"""
		クロスサークルのパラメータを定義します
		
		self.rank と書くと、ランク値を参照できます。
		"""
		
		def __init__(self, rank):
			"""コンストラクタ"""
			self.rank = rank
		
		@property
		def num(self):
			"""生成するクロスの数"""
			return 16
		@property
		def initialRadius(self):
			"""円の初期半径"""
			return 80
		@property
		def createWait(self):
			"""次のクロスを生成するまでのフレーム数"""
			return 2
		@property
		def angleSpeed(self):
			"""回転の角速度"""
			return 0.6
		
		@property
		def launchRepeat(self):
			"""クロスからの発射のリピート回数"""
			return 2
		@property
		def angleInterval(self):
			"""クロスからの弾の角度間隔"""
			return 2
		@property
		def wayNum(self):
			"""クロスからの弾のWay数"""
			return 2
		@property
		def bulletSpeed(self):
			"""クロスからの弾のスピード"""
			return 3.5 * self.rank * 0.8
		@property
		def launchInterval(self):
			"""クロスからの弾のリピート発射間の待機フレーム数"""
			return 5
		@property
		def launchWait(self):
			"""クロスからの弾の次の発射までの待機フレーム数"""
			return 45


class Phase2_1:
	"""攻撃フェーズ2-1のパラメータを定義します"""
	
	class BitManager:
		"""
		ビットマネージャーのパラメータを定義します
		
		self.rank と書くと、ランク値を参照できます。
		"""
		
		def __init__(self, rank):
			"""コンストラクタ"""
			self.rank = rank
	
		@property
		def bitNum(self):
			"""ビットの数"""
			return 8
		@property
		def bitCreationBaseAngle(self):
			"""ビット生成の基準角度"""
			return 90
		@property
		def bitCreationAngleInterval(self):
			"""ビット生成の角度間隔"""
			return (180 - 40) / self.bitNum
		@property
		def bitCreationInterval(self):
			"""ビット生成間隔"""
			return 4
		
		# ビットの攻撃タスク0のID(変更不可)
		# 自機狙いのチェインガンを撃ちつつ、
		# ビットからも自機狙いの弾を発射します
		BIT_TASK_0_AIMING = 0
		
		# ビットの攻撃タスク1のID(変更不可)
		# ビットを円形に配置し、自機に向けて弾を撃ちます
		BIT_TASK_1_CIRCLE_FORM = 1
		
		# ビットの攻撃タスク2のID(変更不可)
		# ビットから自機を追尾するクロスを発射します
		BIT_TASK_2_LAUNCH_TRACING_CROSS = 2
		
		# ビットの攻撃タスク3のID(変更不可)
		# ビットを自機に突撃させ、攻撃フェーズ2-2へ移行します
		BIT_TASK_3_CHARGE = 3
		
		@property
		def bitTaskList(self):
			"""
			ビットの攻撃タスクのリスト
			
			このリストに沿ってビットの攻撃タスクを変更していきます。
			上記のタスクIDの定義をリストに追加してください。
			
			リストの最後に達したら、また最初からタスクを実行していきます。
			
			リストが空の場合、攻撃タスクはランダムに選ばれます。
			"""
			
			taskList = []
			
			"""
			taskList = [
				self.BIT_TASK_0_AIMING, 
				self.BIT_TASK_3_CHARGE, 
				self.BIT_TASK_1_CIRCLE_FORM, 
				self.BIT_TASK_2_LAUNCH_TRACING_CROSS, 
				self.BIT_TASK_1_CIRCLE_FORM, 
				self.BIT_TASK_3_CHARGE, 
				]
			"""
			
			return taskList
		
		@property
		def forceChargeBitNum(self):
			"""強制的に突撃させる際の残ビット数"""
			return self.bitNum / 2
	
	class Bit:
		"""
		ビットのパラメータを定義します
		
		self.rank と書くと、ランク値を参照できます。
		"""
		
		def __init__(self, rank):
			"""コンストラクタ"""
			self.rank = rank
		
		@property
		def hp(self):
			"""耐久力"""
			return 2000
	
	class BitTask0_Aiming:
		"""
		ビットの攻撃タスク0のパラメータを定義します
		
		自機狙いのチェインガンを撃ちつつ、
		ビットからも自機狙いの弾を発射します。
		
		self.rank と書くと、ランク値を参照できます。
		"""
		
		def __init__(self, rank):
			"""コンストラクタ"""
			self.rank = rank
		
		@property
		def moveAreaSize(self):
			"""移動する領域の幅と高さ"""
			return (240, 160)
		@property
		def moveCenterPosOffset(self):
			"""移動する領域の中心座標のオフセット"""
			return (80, 40)
		
		@property
		def firstWait(self):
			"""最初の待機フレーム数"""
			return 30
		
		@property
		def repeatNum(self):
			"""発射回数"""
			return 5
		@property
		def launchFrameNum(self):
			"""一度の発射にかけるフレーム数"""
			return 70
		@property
		def launchFrameNumVariance(self):
			"""一度の発射にかけるフレーム数のブレの最小値と最大値"""
			return (-5, 5)
		@property
		def launchRepeat(self):
			"""発射のリピート回数"""
			return 2
		@property
		def angleInterval(self):
			"""弾の角度間隔"""
			return 1
		@property
		def wayNum(self):
			"""Way数"""
			return 1
		@property
		def speed(self):
			"""弾のスピード"""
			return 4.5 * self.rank
		@property
		def launchRepeatInterval(self):
			"""リピート発射間の待機フレーム数"""
			return 3
		
		class ChainGun:
			"""
			チェインガンのパラメータを定義します
			
			self.rank と書くと、ランク値を参照できます。
			"""
			
			def __init__(self, rank):
				"""コンストラクタ"""
				self.rank = rank
			
			@property
			def speed(self):
				"""弾のスピード"""
				return 4 * self.rank
			
			@property
			def launchSetNum(self):
				"""一連の射撃のセット数"""
				return 3
			@property
			def setInterval(self):
				"""次のセットまでの間隔"""
				return 60
			
			@property
			def firstAngleInterval(self):
				"""一射目の角度間隔"""
				return 24
			@property
			def firstWayNum(self):
				"""一射目のWay数"""
				return 7
			
			@property
			def launchInterval(self):
				"""射撃の待機間隔"""
				return 15
			
			@property
			def secondAngleInterval(self):
				"""二射目の角度間隔"""
				return 24
			@property
			def secondWayNum(self):
				"""二射目のWay数"""
				return 7
			@property
			def secondAngleIntervalPerWay(self):
				"""二射目のWay毎の角度間隔"""
				return 4
			@property
			def secondWayNumPerWay(self):
				"""二射目のWay毎のWay数"""
				return 2
	
	class BitTask1_CircleForm:
		"""
		ビットの攻撃タスク1のパラメータを定義します
		
		ビットを円形に配置し、自機に向けて弾を撃ちます
		
		self.rank と書くと、ランク値を参照できます。
		"""
		
		def __init__(self, rank):
			"""コンストラクタ"""
			self.rank = rank
		
		@property
		def radius(self):
			"""ビット配置の半径"""
			return 200
		@property
		def yScale(self):
			"""ビット配置のY軸方向の拡大率"""
			return 0.6
		@property
		def offset(self):
			"""ビット配置のオフセット"""
			return (0, 30)
		
		@property
		def moveSpeed(self):
			"""
			ビットの移動速度
			
			移動速度が足りないと、正しく円形を描けなくなります。
			"""
			
			return 3
		@property
		def rotateSpeed(self):
			"""回転の角速度"""
			return 1
		
		@property
		def beginWait(self):
			"""弾を撃ち始めるまでの待機間隔"""
			return 60
		@property
		def rotateFrameNum(self):
			"""回転して弾を撃つフレーム数"""
			return 60 * 8
		@property
		def endWait(self):
			"""弾を撃ち終わった後の待機間隔"""
			return 60
		
		@property
		def angleInterval(self):
			"""弾の角度間隔"""
			return 1
		@property
		def wayNum(self):
			"""弾のWay数"""
			return 3
		@property
		def speed(self):
			"""弾のスピード"""
			return 3 * self.rank
		@property
		def launchInterval(self):
			"""弾の発射間隔の最小値と最大値"""
			return (10, 30)
	
	class BitTask2_LaunchTracingCross:
		"""
		ビットの攻撃タスク2のパラメータを定義します
		
		ビットから自機を追尾するクロスを発射します
		
		self.rank と書くと、ランク値を参照できます。
		"""
		
		def __init__(self, rank):
			"""コンストラクタ"""
			self.rank = rank
		
		@property
		def aimingFrameNum(self):
			"""自機に狙いを定めるためのフレーム数"""
			return 5
		@property
		def angleError(self):
			"""狙いの角度の誤差の最小値と最大値"""
			return (-20, 20)
		
		@property
		def launchRepeat(self):
			"""発射のリピート回数"""
			return 4
		@property
		def angleInterval(self):
			"""弾の角度間隔"""
			return 1
		@property
		def wayNum(self):
			"""Way数"""
			return 1
		def speed(self, order):
			"""
			弾のスピード
			
			@param order: 弾の順番 [0, self.launchRepeat - 1]
			"""
			
			return 0.1 * (self.launchRepeat - order)
		def accel(self, order):
			"""
			弾の加速度
			
			@param order: 弾の順番 [0, self.launchRepeat - 1]
			"""
			
			import math
			return 0.2 * math.sqrt(self.rank)
		@property
		def launchInterval(self):
			"""リピート発射間の待機フレーム数"""
			return 5
		
		@property
		def endWait(self):
			"""発射後の待機間隔"""
			return 120
		
		class TracingCross:
			"""
			クロスのパラメータを定義します
			
			self.rank と書くと、ランク値を参照できます。
			"""
			
			def __init__(self, rank):
				"""コンストラクタ"""
				self.rank = rank
			
			@property
			def circlingAngle(self):
				"""旋回角度"""
				return 2
			
			@property
			def tracingFrameNum(self):
				"""追尾フレーム数"""
				return 90
			@property
			def tracingEndDistance(self):
				"""自機との距離がこの値を下回ると追尾をやめる"""
				return 50
			
			@property
			def tracingAccel(self):
				"""追尾時の加速度"""
				import math
				return 0.08 * math.sqrt(self.rank)
			@property
			def afterTracingAccel(self):
				"""追尾終了後の加速度"""
				import math
				return 0.1 * math.sqrt(self.rank)
	
	class BitTask3_Charge:
		"""
		ビットの攻撃タスク3のパラメータを定義します
		
		ビットを自機に突撃させ、攻撃フェーズ2-2へ移行します
		
		self.rank と書くと、ランク値を参照できます。
		"""
		
		def __init__(self, rank):
			"""コンストラクタ"""
			self.rank = rank
		
		@property
		def moveWait(self):
			"""動き出すまでの待機フレーム数"""
			return 10
		
		@property
		def circlingAngle(self):
			"""旋回角度"""
			return 2
		
		@property
		def initialBitSpeed(self):
			"""ビットの初速度"""
			return 0.5 * self.rank
		@property
		def bitAccel(self):
			"""ビットの加速度"""
			import math
			return 0.1 * math.sqrt(self.rank)
		
		@property
		def tracingFrameNum(self):
			"""追尾フレーム数"""
			return 60
		@property
		def tracingEndDistance(self):
			"""自機との距離がこの値を下回ると追尾をやめる"""
			return 50
		
		@property
		def initialBulletSpeed(self):
			"""弾の初速度"""
			return 0.5
		@property
		def bulletAccel(self):
			"""弾の加速度"""
			import math
			return 0.1 * math.sqrt(self.rank)
		@property
		def launchInterval(self):
			"""弾の発射間隔"""
			return 8
		@property
		def bulletCirclingAngle(self):
			"""弾の旋回角度"""
			return 2
		@property
		def bulletTracingFrameNum(self):
			"""弾の追尾フレーム数"""
			return 30
		@property
		def bulletTracingEndDistance(self):
			"""弾と自機との距離がこの値を下回ると追尾をやめる"""
			return 50

class Phase2_2:
	"""攻撃フェーズ2-2のパラメータを定義します"""
	
	class Cross:
		"""
		クロスのパラメータを定義します
		
		self.rank と書くと、ランク値を参照できます。
		"""
		
		def __init__(self, rank):
			"""コンストラクタ"""
			self.rank = rank
		
		@property
		def launchAngleRotateSpeed(self):
			"""発射角度の角速度"""
			return 1 * self.rank
		@property
		def launchRepeat(self):
			"""発射のリピート回数"""
			return 4
		@property
		def launchInterval(self):
			"""発射リピート間の待機フレーム数"""
			return 4
		@property
		def wayNum(self):
			"""Way数"""
			return 4
		@property
		def speed(self):
			"""クロスのスピード"""
			return 3.5 * self.rank
	
	class ChainGun:
		"""
		チェインガンのパラメータを定義します
		
		self.rank と書くと、ランク値を参照できます。
		"""
		
		def __init__(self, rank):
			"""コンストラクタ"""
			self.rank = rank
		
		@property
		def launchSetNum(self):
			"""発射セット数"""
			return 3
		@property
		def setInterval(self):
			"""発射セット間の待機フレーム数"""
			return 90
		def launchRepeat(self, setOrder):
			"""
			セットごとの発射リピート数
			
			@param setOrder: セットの順番 [0, self.launchSetNum - 1]
			"""
			
			return 4 * (setOrder + 1) * self.rank
		
		@property
		def launchInterval(self):
			"""発射リピート間の待機フレーム数"""
			return 4
		
		@property
		def outerAngleInterval(self):
			"""外側の弾の角度間隔"""
			return 90
		@property
		def outerWayNum(self):
			"""外側のWay数"""
			return 2
		@property
		def outerSpeed(self):
			"""外側の弾のスピード"""
			return 5 * self.rank
		
		@property
		def innerAngleInterval(self):
			"""内側の弾の角度間隔"""
			return 4
		@property
		def innerWayNum(self):
			"""内側のWay数"""
			return 4
		@property
		def innerSpeed(self):
			"""内側の弾のスピード"""
			return 3.5 * self.rank
		
		@property
		def endWait(self):
			"""発射後の待機フレーム数"""
			return 90