'''
Created on 2011/12/25

@author: t

乃莉の各種パラメータを定義します
'''

# 基本スピード
baseSpeed = 4.5
# 低速移動時に乗算される値
speedRate_Slow = 0.7
# オプション数の増減で変化する速度の割合
speedRate_OptionNum = 0.3


# 通常ショットの速度
normalShotSpeed = 26
# 通常ショットのダメージ率の減衰
normalShotDamageRateDecrease = 0.06
# 通常ショットの最少ダメージ率
normalShotDamageRateMin = 0.5
# 通常ショットのPAへの基本ダメージ
normalShotPABaseDamage = 3
# 通常ショットの減衰耐性
normalShotAttenuationResistance = 100


# ロックメインショットの速度
lockMainShotSpeed = 36
# ロックメインショットのダメージ率の減衰
lockMainShotDamageRateDecrease = 0.15
# ロックメインショットの最少ダメージ率
lockMainShotDamageRateMin = 0.2
# ロックメインショットのPAへの基本ダメージ
lockMainShotPABaseDamage = 8
# ロックメインショットによるロック速度
lockMainShotLockSpeed = 32
# ロックメインショットの減衰耐性
lockMainShotAttenuationResistance = 100


# ロックオプションショットの速度
lockOptionShotSpeed = 28
# ロックオプションショットのダメージ率の減衰
lockOptionShotDamageRateDecrease = 0.06
# ロックオプションショットの最少ダメージ率
lockOptionShotDamageRateMin = 0.5
# ロックオプションショットのPAへの基本ダメージ
lockOptionShotPABaseDamage = 4
# ロックオプションショットの減衰耐性
lockOptionShotAttenuationResistance = 100


# 通常メインショットの発射間隔
# 値の順番はパワーアップ数(0～4)に対応します
normalMainShotInterval = (5, 5, 5, 4, 4)
# 通常メインショットの数
normalMainShotNum = (4, 6, 8, 8, 8)
# 通常メインショットの基本ダメージ
normalMainShotBaseDamage = (2, 2, 2, 2.5, 3)
# ロックメインショットの基本ダメージ
# 値の順番はパワーアップ数(0～4)に対応します
lockMainShotDamage = (12, 16, 16, 17, 18)


# オプションショットの数
# 値の順番はパワーアップ数(0～4)に対応します
optionShotNum = (2, 3, 4, 4, 4)
# 通常オプションショットの発射間隔
normalOptionShotInterval = (5, 5, 5, 4, 4)
# 通常オプションショットの基本ダメージ
normalOptionShotBaseDamage = (2, 2, 2, 3, 4)
# ロックオプションショットの発射間隔
lockOptionShotInterval = (4, 4, 4, 3, 3)
# ロックオプションショットの基本ダメージ
lockOptionShotBaseDamage = (2, 2, 2, 3, 4)


# オプション数変更によるメインショットのダメージ等への影響率
# 正の値にすると、オプションが増えるごとにダメージ等が増します
# 負の値にすると、オプションが増えるごとにダメージ等が減ります
# ただし、現在の実装では初期オプション数から増やした場合には適用されません
optionNumEffectRate_Main = -0.2
# オプション数変更によるオプションショットのダメージ等への影響率
optionNumEffectRate_Option = -0.2


# 特殊通常ショットの速度
spNormalShotSpeed = 30
# 特殊通常ショットのダメージ率の減衰
spNormalShotDamageRateDecrease = 0.06
# 特殊通常ショットの最少ダメージ率
spNormalShotDamageRateMin = 0.5

# 特殊ロックショットの速度
spLockShotSpeed = 30
# 特殊ロックショットのダメージ率の減衰
spLockShotDamageRateDecrease = 0.06
# 特殊ロックショットの最少ダメージ率
spLockShotDamageRateMin = 0.5


# 特殊通常メインショットの発射間隔
spNormalMainShotInterval = 4
# 特殊通常メインショットの基本ダメージ
spNormalMainShotBaseDamage = 8
# 特殊通常メインショットのPAへの基本ダメージ
spNormalMainShotPABaseDamage = 14
# 特殊通常メインショットの敵弾の減衰力
spNormalMainShotDamageToBullet = 8
# 特殊通常メインショットの減衰耐性
spNormalMainShotAttenuationResistance = 100

# 特殊ロックメインショットの基本ダメージ
spLockMainShotBaseDamage = 25
# 特殊ロックメインショットのPAへの基本ダメージ
spLockMainShotPABaseDamage = 20
# 特殊ロックメインショットの減衰耐性
spLockMainShotAttenuationResistance = 100


# 特殊通常オプションショットの発射間隔
spNormalOptionShotInterval = 4
# 特殊通常オプションショットの基本ダメージ
spNormalOptionShotBaseDamage = 8
# 特殊通常オプションショットのPAへの基本ダメージ
spNormalOptionShotPABaseDamage = 14
# 特殊通常オプションショットの敵弾の減衰力
spNormalOptionShotDamageToBullet = 8
# 特殊通常オプションショットの減衰耐性
spNormalOptionShotAttenuationResistance = 100

# 特殊ロックオプションショットの発射間隔
spLockOptionShotInterval = 3
# 特殊ロックオプションショットの基本ダメージ
spLockOptionShotBaseDamage = 14
# 特殊ロックオプションショットのPAへの基本ダメージ
spLockOptionShotPABaseDamage = 17
# 特殊ロックオプションショットの敵弾の減衰力
spLockOptionShotDamageToBullet = 8
# 特殊ロックオプションショットの減衰耐性
spLockOptionShotAttenuationResistance = 100


# ロックの閾値
# メインショットのロック速度の値の合計がこの値を超えるとロックされる
lockThresHold = 40

# ロックの並列負荷
# この値が0に近づくほど、ロック数が増えるごとにロック速度が低下する
lockParalellLoad = 0.7


# 特殊攻撃の持続フレーム数
spAttackFrameNum = 60 * 8
# 特殊攻撃開始時と終了時の無敵フレーム数
spAttackBarrierFrameNum = 90
# 特殊攻撃終了時の弾消し持続フレーム数
spAttackBulletDestructionFrameNum = 30


# オプションの位置の設定
# 片側のオプションの相対位置を指定します
optionRelativePosition = (
	(50, -30), 
	(80, 0), 
	(110, 30)
	)

# オプションの角度の設定
# 度数法で設定します
# 右方向が0度で、時計回りで増えていきます
optionAngle = (-90, -90, -90)

# 低速移動時のオプションの位置の設定
optionRelativePosition_Slow = (
	(60, 40), 
	(110, 20), 
	(160, 0)
	)