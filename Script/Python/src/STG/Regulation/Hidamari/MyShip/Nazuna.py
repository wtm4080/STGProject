'''
Created on 2011/12/25

@author: t

なずなの各種パラメータを定義します
'''

# 移動速度
moveSpeed = 4
# 低速移動時の移動速度
moveSpeed_Slow = 2.5


# 通常ショットの速度
normalShotSpeed = 26
# 通常ショットの基本ダメージ
normalShotBaseDamage = 2
# 通常ショットのダメージ率の減衰
normalShotDamageRateDecrease = 0.06
# 通常ショットの最少ダメージ率
normalShotDamageRateMin = 0.5
# 通常ショットのPAへの基本ダメージ
normalShotPABaseDamage = 2
# 通常ショットの減衰耐性
normalShotAttenuationResistance = 100


# ロックメインショットの速度
lockMainShotSpeed = 36
# ロックメインショットのダメージ率の減衰
lockMainShotDamageRateDecrease = 0.15
# ロックメインショットの最少ダメージ率
lockMainShotDamageRateMin = 0.2
# ロックメインショットによるロック速度
lockMainShotLockSpeed = 32
# ロックメインショットの減衰耐性
lockMainShotAttenuationResistance = 100


# ロックオプションショットの速度
lockOptionShotSpeed = 26
# ロックオプションショットの基本ダメージ
lockOptionShotBaseDamage = 2
# ロックオプションショットのダメージ率の減衰
lockOptionShotDamageRateDecrease = 0.06
# ロックオプションショットの最少ダメージ率
lockOptionShotDamageRateMin = 0.5
# ロックオプションショットのPAへの基本ダメージ
lockOptionShotPABaseDamage = 3
# ロックオプションショットの減衰耐性
lockOptionShotAttenuationResistance = 100


# 通常メインショットの発射間隔
# 値の順番はパワーアップ数(0～4)に対応します
normalMainShotInterval = (5, 5, 4, 4, 4)
# 通常メインショットの数
normalMainShotNum = (4, 4, 4, 6, 8)

# ロックメインショットの基本ダメージ
# 値の順番はパワーアップ数(0～4)に対応します
lockMainShotDamage = (12, 12, 16, 16, 16)

# オプションショットの数
# 値の順番はパワーアップ数(0～4)に対応します
optionShotNum = (2, 2, 2, 3, 4)
# 通常オプションショットの発射間隔
normalOptionShotInterval = (5, 5, 4, 4, 4)
# ロックオプションショットの発射間隔
lockOptionShotInterval = (4, 4, 3, 3, 3)


# ロックの閾値
# メインショットのロック速度の値の合計がこの値を超えるとロックされる
lockThresHold = 40

# ロックの並列負荷
# この値が0に近づくほど、ロック数が増えるごとにロック速度が低下する
lockParalellLoad = 0.95


# 特殊攻撃時の無敵フレーム数
spAttackBarrierFrameNum = 240

# 発射時のプラズマ球の半径
plasmaBallRadius = 32
# プラズマ球の移動速度
plasmaBallSpeed = 16
# プラズマ球の基本ダメージ
plasmaBallBaseDamage = 8
# プラズマ球のダメージ率の減衰
plasmaBallDamageRateDecrease = 0.06
# プラズマ球の最少ダメージ率
plasmaBallDamageRateMin = 0.8

# プラズマ爆発の半径
plasmaBlastRadius = 128
# プラズマ爆発の基本ダメージ
plasmaBlastBaseDamage = 1
# プラズマ爆発のPAへの基本ダメージ
plasmaBlastPABaseDamage = 20
# プラズマ爆発の持続フレーム数
plasmaBlastLongevity = 120


# オプションの位置の設定
# 片側のオプションの相対位置を指定します
optionRelativePosition = (
	(60, 40), 
	(100, 10), 
	(120, 50)
	)

# オプションの角度の設定
# 度数法で設定します
# 右方向が0度で、時計回りで増えていきます
optionAngle = (-80, -60, -40)

# 低速移動時のオプションの位置の設定
optionRelativePosition_Slow = (
	(60, 20), 
	(110, 30), 
	(160, 40)
	)