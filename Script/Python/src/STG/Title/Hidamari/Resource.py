'''
Created on 2011/12/19

@author: t
'''

import Std
from Util.Misc import loadBGM, loadSE

import STG.Resource.Hidamari as Common

class Resource:
	def __init__(self):
		self.font_Common32 = Common.getResource().font_Common32
		
		title = "Hidamari/Title/"
		bgmPlayBlock = Std.StreamSoundPlayBlock
		self.bgm_MyShipSelect = loadBGM(title + "MyShipSelect.ogg")
		self.bgm_MyShipSelect_PlayBlocks = (
			bgmPlayBlock(loopCount = 0, endTime = 12.096), 
			bgmPlayBlock(startTime = 12.096, endTime = 48.077))
		
		self.se_Select1 = Common.getResource().se_Select1
		self.se_Select2 = Common.getResource().se_Select2
		self.se_Select3 = Common.getResource().se_Select3
		self.se_Cancel = Common.getResource().se_Cancel
		self.se_TitleAppear = loadSE(title + "TitleAppear.wav")
		self.se_Enter = loadSE(title + "Enter.wav")
		self.se_SelectYourBattleShip = loadSE(title + "SelectYourBattleShip.wav")
		self.se_AreYouReady = loadSE(title + "AreYouReady.wav")
		
		load = Std.Sprite.loadTexture
		self.titleBack = load(title + "TitleBack.dds", False)
		self.nazuna = load(title + "Nazuna.dds", False)
		self.nori = load(title + "Nori.dds", False)