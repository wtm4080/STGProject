'''
Created on 2011/09/09

@author: t
'''

import Std
import STG.Ctrl as Ctrl
from Util.Misc import Enum
from Util.Coroutine import Coroutine

from .DrawPriority import drawPriority

enum = Enum(
	"nazuna", 
	"nori", 
	)

class SelectMyShip:
	def __init__(self, core):
		controller = Std.Input.getController()
		
		for info in Ctrl.Conf.getStageSetInfoList():
			if info[1] == "HidamariRegular":
				stageSetId = info[0]
				break
		for info in Ctrl.Conf.getMyShipInfoList():
			if info[1] == "Nazuna":
				nazunaId = info[0]
			elif info[1] == "Nori":
				noriId = info[0]
		
		def selectTask():
			core.resource.se_SelectYourBattleShip.play()
			core.resource.bgm_MyShipSelect.play(
				#core.resource.bgm_MyShipSelect_PlayBlocks
				)
			
			arrow = Std.ArrowLocator(enum.nazuna, enum.nazuna, enum.nori)
			arrow.setMoveCallback(lambda: core.resource.se_Select1.play())
			
			def characterTask(_drawParam = None):
				drawParam = _drawParam
				maxSpeed = 22
				minSpeed = 1
				accel = 0.8
				stopPosX = 10
				yield
				
				dst = drawParam.dst
				pos = Std.Vector2DF(dst.x, dst.y)
				locator = Std.Locator.LinearF(pos)
				locator.speed.setUnitVector(0)
				locator.speed *= maxSpeed
				locator.accel.setUnitVector(180)
				locator.accel *= accel
				while locator.position.x < stopPosX:
					locator.update()
					if locator.speed.getAbs() < minSpeed:
						locator.speed.normalize()
						locator.speed *= minSpeed
						locator.accel *= 0
					drawParam.dst = locator.position.makeRect(
						dst.w, dst.h, False)
					drawParam.color.a = 1 / (1 + 0.1*abs(stopPosX - locator.position.x))
					yield
				
				drawParam.dst = locator.position.makeRect(dst.w, dst.h, False)
				drawParam.color.a = 1
			
			nazunaDrawParam = Std.Sprite.DrawParam()
			nazunaDrawParam.texture = core.resource.nazuna
			nazunaDrawParam.src = Std.RectF(0, 0, 256, 164)
			nazunaDrawParam.dst = Std.RectF(-256, 480 - 164, 256, 164)
			nazunaDrawParam.priority = drawPriority.character
			initialNazunaDrawParam = Std.Sprite.DrawParam(nazunaDrawParam)
			
			noriDrawParam = Std.Sprite.DrawParam()
			noriDrawParam.texture = core.resource.nori
			noriDrawParam.src = Std.RectF(0, 0, 256, 176)
			noriDrawParam.dst = Std.RectF(-256, 480 - 176, 256, 176)
			noriDrawParam.priority = drawPriority.character
			initialNoriDrawParam = Std.Sprite.DrawParam(noriDrawParam)
			
			def drawTask():
				basePos = Std.Point2DF(420, 300)
				color = Std.ColorF()
				while True:
					font = core.resource.font_Common32
					font.setPriority(drawPriority.str)
					font.shakable = False
					
					rect = Std.RectF(0, 150, 640, 32)
					offset = Std.Point2DF()
					font.drawCenter(rect, offset, color, "キャラクターを選択してください")
					
					offset = font.size + 16
					for i in range(enum.nori + 1):
						dst = Std.Point2DF(basePos.x, basePos.y + offset*i)
						if i == enum.nazuna:
							font.draw(dst, color, "なずな")
						elif i == enum.nori:
							font.draw(dst, color, "乃莉")
					
					dst = Std.Point2DF(
						basePos.x - font.size, 
						basePos.y + offset*arrow.position)
					font.draw(dst, color, "→")
					
					Std.Sprite.draw(nazunaDrawParam)
					Std.Sprite.draw(noriDrawParam)
					yield
			self.drawTask = Coroutine(drawTask)
			
			nazunaTask = Coroutine(characterTask)
			nazunaTask.resume(nazunaDrawParam)
			noriTask = None
			prevArrowPos = arrow.position
			while True:
				arrow.update()
				if arrow.position != prevArrowPos:
					nazunaDrawParam = Std.Sprite.DrawParam(initialNazunaDrawParam)
					noriDrawParam = Std.Sprite.DrawParam(initialNoriDrawParam)
					
					if arrow.position == enum.nazuna:
						nazunaTask = Coroutine(characterTask)
						nazunaTask.resume(nazunaDrawParam)
						noriTask = None
					elif arrow.position == enum.nori:
						noriTask = Coroutine(characterTask)
						noriTask.resume(noriDrawParam)
						nazunaTask = None
				prevArrowPos = arrow.position
				
				if nazunaTask and nazunaTask.alive:
					nazunaTask.resume()
				if noriTask and noriTask.alive:
					noriTask.resume()
				
				if controller.isPush(Std.Input.KeyId.X):
					core.resource.se_Cancel.play()
					core.resource.bgm_MyShipSelect.stop()
					from .Top import Top, enum as topEnum
					core.view = Top(core, topEnum.gameStart, False)
				elif controller.isPush(Std.Input.KeyId.Z):
					core.resource.se_AreYouReady.play()
					core.resource.bgm_MyShipSelect.fadeOut(1)
					
					if arrow.position == enum.nazuna:
						myShipId = nazunaId
					elif arrow.position == enum.nori:
						myShipId = noriId
					core.fadeOut(60, drawPriority.fadeEffect, 
						lambda : Std.Scene.changeToSTG(stageSetId, myShipId))
					
					import STG.Stage.Hidamari.Regular.Core as StageSet
					StageSet.hidamariFlag = True
				yield
		self.task = Coroutine(selectTask)
		self.drawTask = None
	
	def update(self):
		if self.task.alive:
			self.task.resume()
	def draw(self):
		if not self.drawTask is None and self.drawTask.alive:
			self.drawTask.resume()