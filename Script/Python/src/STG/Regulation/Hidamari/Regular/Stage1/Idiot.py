'''
Created on 2011/12/25

@author: t

雑魚の各種パラメータを定義します
'''

class Mikan:
	"""
	パワーアップアイテムを出す雑魚のパラメータ定義です
	"""
	
	# 耐久力
	hp = 100
	
	# 次の弾発射までのフレーム数
	waitFrameNum = 60
	# 弾のWay数
	wayNum = 3
	# 弾の角度間隔
	interval = 45
	# 弾の発射回数
	launchNum = 4
	# 弾の発射間隔
	launchInterval = 3
	
	# アイテム数
	itemNum = 4
	# アイテム発射角度
	itemLaunchAngle = -90
	# アイテム発射角度間隔
	itemLaunchAngleInterval = 20


class Moushiwake:
	"""
	特殊攻撃補給アイテムを出す雑魚のパラメータ定義です
	"""
	
	# 耐久力
	hp = 100
	
	# ブレの最小値と最大値
	posVariance = (-4, 4)
	
	# 次の弾発射までのフレーム数
	waitFrameNum = 60
	# 弾のWay数
	wayNum = 3
	# 弾の角度間隔
	interval = 45
	# 弾の発射回数
	launchNum = 4
	# 弾の発射間隔
	launchInterval = 3
	
	# アイテム数
	itemNum = 1
	# アイテム発射角度
	itemLaunchAngle = -90
	# アイテム発射角度間隔
	itemLaunchAngleInterval = 20