'''
Created on 2011/01/07

@author: t
'''

import Std
from Util.Misc import loadBGM, loadSE
from Util.Sprite.Animation import loadSequenceFrame as loadSeq

import STG.Resource.Hidamari as Common

class Resource:
	def __init__(self):
		load = Std.Sprite.loadTexture
		bgmPlayBlock = Std.StreamSoundPlayBlock
		regular = "Hidamari/Regular/"
		
		self.bgm_Boss1 = loadBGM(regular + "Boss1.ogg")
		self.bgm_Boss1_PlayBlocks = (
			bgmPlayBlock(loopCount = 0, endTime = 6.64), 
			bgmPlayBlock(startTime = 6.64, endTime = 96.24)
			)
		
		self.se_Explode1 = loadSE(regular + "Explode1.wav")
		self.se_Explode2 = loadSE(regular + "Explode2.wav")
		self.se_BossAlert = loadSE(regular + "BossAlert.wav")
		self.se_BossDestruction1_1 = loadSE(regular + "BossDestruction1_1.wav")
		self.se_BossDestruction1_2 = loadSE(regular + "BossDestruction1_2.wav")
		
		self.bgm_ResultScene = loadBGM(regular + "ResultScene.ogg")
		self.se_CalcScore = loadSE(regular + "CalcScore.wav")
		self.se_Whump = loadSE(regular + "Whump.wav")
		self.se_Select3 = Common.getResource().se_Select3
		
		self.font_ScoreRate = Std.Font.load("Hidamari/ScoreRate64.sff")
		self.scoreRateStar = load(regular + "Star.dds")
		
		self.warningTexList = loadSeq(regular + "Warning/", 128, False)
		
		self.infArea = load(regular + "InfArea.dds", False)
		self.font_Common16 = Common.getResource().font_Common16
		self.font_Common24 = Common.getResource().font_Common24
		
		stage1 = "Hidamari/Regular/Stage1/"
		self.bgm_Stage1 = loadBGM(regular + "Stage1.ogg")
		self.st1_AppearTexList = loadSeq(stage1 + "Appear/", 200, False)
		self.tree = load(regular + "Background/Tree.dds", False)
		
		self.st1_YunoBitTexList = loadSeq(stage1 + "Yuno/Bit/Bit_", 10, False)
		self.st1_YunoRotorTexList = loadSeq(stage1 + "Yuno/Rotor/Rotor_", 3, False)
		self.st1_YunoBase = load(stage1 + "Yuno/Base.dds", False)
		self.st1_YunoBase_1 = load(stage1 + "Yuno/Base_1.dds", False)
		self.st1_YunoBase_2 = load(stage1 + "Yuno/Base_2.dds", False)
		self.st1_YunoBase_3 = load(stage1 + "Yuno/Base_3.dds", False)
		self.st1_YunoBase_4 = load(stage1 + "Yuno/Base_4.dds", False)
		self.st1_YunoBase_5 = load(stage1 + "Yuno/Base_5.dds", False)
		self.st1_YunoCross = load(stage1 + "Yuno/Cross.dds")
		self.st1_YunoMissile = load(stage1 + "Yuno/Missile.dds", False)
		self.st1_YunoSide_L = load(stage1 + "Yuno/Side_L.dds", False)
		self.st1_YunoSide_R = load(stage1 + "Yuno/Side_R.dds", False)
		
		self.paDamaged = load(regular + "PrimalArmor/Damaged.dds")
		self.paGeneratedTexList = loadSeq(regular + "PrimalArmor/Generated/", 16)
		self.paVanishedTexList = loadSeq(regular + "PrimalArmor/Vanished/", 16)
		self.se_GeneratePA = loadSE(regular + "GeneratePrimalArmor.wav")
		
		self.st1_Mikan = load(stage1 + "Mikan.dds")
		self.st1_Moushiwake = load(stage1 + "Moushiwake.dds")
		
		self.result_CharBack = load(regular + "Result/CharBack.dds")
		self.result_Nazuna = load(regular + "Result/Nazuna.dds")
		self.result_Nori = load(regular + "Result/Nori.dds")