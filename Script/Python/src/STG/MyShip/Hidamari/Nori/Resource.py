'''
Created on 2011/01/07

@author: t
'''

import Std
from Util.Misc import loadSE
from Util.Sprite.Animation import loadSequenceFrame as loadSeq

import STG.Resource.Hidamari as Common

class Resource:
	def __init__(self):
		basePath = "Hidamari/MyShip/Nori/"
		myShip = "Hidamari/MyShip/"
		load = Std.Sprite.loadTexture
		
		self.font_Common24 = Common.getResource().font_Common24
		
		self.se_Destruction = loadSE(myShip + "Destruction.wav")
		self.se_PowerUp = loadSE(myShip + "PowerUp.wav")
		self.se_Bomber = loadSE(myShip + "Bomber.wav")
		self.se_Item = loadSE(myShip + "Item.wav")
		self.se_ChangeOption = loadSE(basePath + "ChangeOption.wav")
		
		self.bodyTexList = loadSeq(basePath + "Body/", 16, False)
		self.backFireTexList = loadSeq(basePath + "BackFire/", 2)
		self.optionTexList = loadSeq(basePath + "Option/", 20, False)
		self.hitMarkerTexList = loadSeq(myShip + "HitMarker/", 12)
		
		self.normalShot = load(basePath + "NormalShot.dds")
		self.normalShotParticleTexList = loadSeq(basePath + "NormalShotParticle/", 12)
		self.normalFire = load(basePath + "NormalFire.dds")
		self.se_NormalShot = loadSE(myShip + "NormalShot.wav")
		self.se_NormalShot.waitingForPlay = True
		self.se_ShotHit = loadSE(myShip + "ShotHit.wav")
		self.se_ShotHit.waitingForPlay = True
		
		self.lockMainShot_1 = load(basePath + "LockMainShot_1.dds")
		self.lockMainShot_2 = load(basePath + "LockMainShot_2.dds")
		self.lockMainFire_1 = load(basePath + "LockMainFire_1.dds")
		self.lockMainFire_2 = load(basePath + "LockMainFire_2.dds")
		self.lockMainParticleTexList_1 = loadSeq(basePath + "LockMainParticle_1/", 16)
		self.lockMainParticleTexList_2 = loadSeq(basePath + "LockMainParticle_2/", 16)
		self.lockOptionShot = load(basePath + "LockOptionShot.dds")
		self.lockOptionFire = load(basePath + "LockOptionFire.dds")
		self.lockOptionShotParticleTexList = loadSeq(basePath + "LockOptionShotParticle/", 12)
		self.se_LockShot = loadSE(myShip + "LockShot.wav")
		self.se_LockShot.waitingForPlay = True
		
		self.spNormalShot = load(basePath + "SpAttack/NormalShot.dds")
		self.spNormalParticleTexList = loadSeq(basePath + "SpAttack/NormalParticle/", 16)
		self.spLockMainShot_1 = load(basePath + "SpAttack/LockMainShot_1.dds")
		self.spLockMainShot_2 = load(basePath + "SpAttack/LockMainShot_2.dds")
		self.spLockOptionShot = load(basePath + "SpAttack/LockOptionShot.dds")
		self.spLockOptionParticleTexList = loadSeq(basePath + "SpAttack/LockOptionParticle/", 16)
		self.spBeginTexList = loadSeq("MyShip/SpBegin/SpBegin_", 60, False)
		self.spFinishTexList = loadSeq("MyShip/SpFinish/SpFinish_", 60, False)
		self.spFinishingTexList = loadSeq("MyShip/SpFinishing/SpFinishing_", 60, False)
		self.spGaugeTexList = loadSeq("MyShip/SpGauge/SpGauge_", 480, False)
		self.se_SpAttack = loadSE(basePath + "SpAttack.wav")
		
		self.lockBeginTexList = loadSeq("Hidamari/MyShip/LockBegin/", 10)
		self.lockMarkerTexList = loadSeq("Hidamari/MyShip/LockMarker/", 24)
		self.se_Lock = loadSE(myShip + "Lock.wav", 6)