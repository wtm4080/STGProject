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
		basePath = "Hidamari/MyShip/Nazuna/"
		myShip = "Hidamari/MyShip/"
		load = Std.Sprite.loadTexture
		
		self.font_Common24 = Common.getResource().font_Common24
		
		self.se_Destruction = loadSE(myShip + "Destruction.wav")
		self.se_PowerUp = loadSE(myShip + "PowerUp.wav")
		self.se_Bomber = loadSE(myShip + "Bomber.wav")
		self.se_Item = loadSE(myShip + "Item.wav")
		
		self.bodyTexLists = []
		for degree in range(0, 45 + 3, 3):
			path = basePath + "Body/{0}/".format(degree)
			self.bodyTexLists.append(loadSeq(path, 3, False))
		
		self.optionTexList = loadSeq(basePath + "Option/", 3, False)
		
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
		
		self.lockBeginTexList = loadSeq("Hidamari/MyShip/LockBegin/", 10)
		self.lockMarkerTexList = loadSeq("Hidamari/MyShip/LockMarker/", 24)
		self.se_Lock = loadSE(myShip + "Lock.wav", 6)
		
		self.hitMarkerTexList = loadSeq(myShip + "HitMarker/", 12)
		
		self.plasmaBallTexList = loadSeq(basePath + "Bomb/PlasmaBall/", 16)
		self.plasmaBlastTexList = loadSeq(basePath + "Bomb/PlasmaBlast/", 24)
		self.se_LaunchPlasma = loadSE(basePath + "LaunchPlasma.wav")
		self.se_PlasmaBlast = loadSE(basePath + "PlasmaBlast.wav")