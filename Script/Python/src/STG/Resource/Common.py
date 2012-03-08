'''
Created on 2010/10/27

@author: t
'''

import Std
from Util.Sprite.Animation import loadSequenceFrame

_init = False
_resDict = {}
_fontDict = {}

def _initialize():
	_fontDict["font16"] = Std.Font.load("Font16.sff")
	_fontDict["font32"] = Std.Font.load("Font32.sff")
	
	_resDict["infAreaBack"] = Std.Sprite.loadTexture("InfAreaBack.dds")
	
	_resDict["itemExtend"] = Std.Sprite.loadTexture("Item/1Up.dds")
	_resDict["itemPowerUp"] = Std.Sprite.loadTexture("Item/PowerUp.dds")
	_resDict["itemSpAttack"] = Std.Sprite.loadTexture("Item/SpAttack.dds")
	
	_resDict["explosion"] = Std.Sprite.loadTexture("Explode.dds")
	_resDict["explosion2TexList"] = loadSequenceFrame("Explosion/Explosion_", 30)
	_resDict["smokeTexList"] = loadSequenceFrame("Smoke/Smoke_", 30)
	
	_resDict["bulletRed"] = Std.Sprite.loadTexture("RedCircle.dds")
	_resDict["bulletGreen"] = Std.Sprite.loadTexture("GreenCircle.dds")
	_resDict["bulletBlue"] = Std.Sprite.loadTexture("BlueCircle.dds")
	_resDict["bulletWhite"] = Std.Sprite.loadTexture("WhiteCircle.dds")
	_resDict["bulletPurple"] = Std.Sprite.loadTexture("PurpleCircle.dds")
	
	_resDict["bulletDamagedEffect"] = Std.Sprite.loadTexture("BulletDamagedEffect.dds")
	
	_resDict["hpGauge"] = Std.Sprite.loadTexture("HPGauge.dds")
	
	global _init
	_init = True

def get(name):
	if not _init:
		_initialize()
	return _resDict[name]
def getFont(name, priority, shakable, size):
	if not _init:
		_initialize()
	font = _fontDict[name]
	font.setPriority(priority)
	font.shakable = shakable
	font.size = size
	return font