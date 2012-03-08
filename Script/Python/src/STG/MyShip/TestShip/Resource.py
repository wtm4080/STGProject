'''
Created on 2010/11/10

@author: t
'''

import Std
from Util.Sprite.Animation import loadSequenceFrame

class Resource:
	def __init__(self):
		self.shipTexture = Std.Sprite.loadTexture("MyShip/Triangle.dds")
		self.optionTexture = Std.Sprite.loadTexture("MyShip/VistaLogo.dds")
		self.spShotTexture = Std.Sprite.loadTexture("MyShip/SpShot.dds")
		self.spShortShotTexture = Std.Sprite.loadTexture("MyShip/SpShortShot.dds")
		self.spBeginTextureList = loadSequenceFrame("MyShip/SpBegin/SpBegin_", 60, False)
		self.spFinishTextureList = loadSequenceFrame("MyShip/SpFinish/SpFinish_", 60, False)
		self.spFinishingTextureList = loadSequenceFrame("MyShip/SpFinishing/SpFinishing_", 60, False)
		self.spGaugeTextureList = loadSequenceFrame("MyShip/SpGauge/SpGauge_", 480, False)