'''
Created on 2010/11/09

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Resource.Common as CommonResource
from Util.Sprite.Animation import createSequenceAnimation
from Util.Sprite.Animation import updateDst

class Drawing:
	BARRIER_SIZE = Std.Vector2DF(86, 86)
	HIT_MARK_SIZE = Std.Vector2DF(12, 12)
	SPBEGIN_ANIME_SIZE = Std.Vector2DF(400, 400)
	SPFINISH_ANIME_SIZE = Std.Vector2DF(500, 500)
	SPFINISHING_ANIME_SIZE = Std.Vector2DF(800, 800)
	SPGAUGE_ANIME_SIZE = Std.Vector2DF(96, 96)
	
	def __init__(self, ship):
		self.ship = ship
		
		self.shipDrawParam = Std.Sprite.DrawParam()
		self.shipDrawParam.texture = self.ship.resource.shipTexture
		self.shipDrawParam.src = Std.RectF(0, 0, 64, 64)
		self.shipDrawParam.dst = ship.position.makeRect(ship.SHIP_SIZE, True)
		self.shipDrawParam.priority = Ctrl.DrawPriority.myShip
		
		self.hitMarkDrawParam = Std.Sprite.DrawParam()
		self.hitMarkDrawParam.texture = CommonResource.get("bulletRed")
		self.hitMarkDrawParam.src = Std.RectF(0, 0, 64, 64)
		self.hitMarkDrawParam.dst = ship.position.makeRect(self.HIT_MARK_SIZE, True)
		self.hitMarkDrawParam.priority = Ctrl.DrawPriority.myShipHitMark
		self.hitMarkDrawParam.alphaBlend = Std.Sprite.AlphaBlend.Add
		
		self.barrierDrawParam = Std.Sprite.DrawParam()
		self.barrierDrawParam.texture = CommonResource.get("bulletBlue")
		self.barrierDrawParam.src = Std.RectF(0, 0, 64, 64)
		self.barrierDrawParam.dst = ship.position.makeRect(self.BARRIER_SIZE, True)
		self.barrierDrawParam.priority = Ctrl.DrawPriority.myBarrier
		self.barrierDrawParam.alphaBlend = Std.Sprite.AlphaBlend.Add
		
		spBeginDrawParam = Std.Sprite.DrawParam()
		spBeginDrawParam.src = Std.RectF(0, 0, 200, 200)
		spBeginDrawParam.dst = ship.position.makeRect(self.SPBEGIN_ANIME_SIZE, True)
		spBeginDrawParam.priority = Ctrl.DrawPriority.myShip2
		self.spBeginAnimation = createSequenceAnimation(
			ship.resource.spBeginTextureList, spBeginDrawParam)
		
		spFinishDrawParam = Std.Sprite.DrawParam()
		spFinishDrawParam.src = Std.RectF(0, 0, 200, 200)
		spFinishDrawParam.dst = ship.position.makeRect(
			self.SPFINISH_ANIME_SIZE, True)
		spFinishDrawParam.priority = Ctrl.DrawPriority.myShip2
		self.spFinishAnimation = createSequenceAnimation(
			ship.resource.spFinishTextureList, spFinishDrawParam)
		
		spFinishingDrawParam = Std.Sprite.DrawParam()
		spFinishingDrawParam.src = Std.RectF(0, 0, 200, 200)
		spFinishingDrawParam.dst = ship.position.makeRect(
			self.SPFINISHING_ANIME_SIZE, True)
		spFinishingDrawParam.priority = Ctrl.DrawPriority.myShip2
		self.spFinishingAnimation = createSequenceAnimation(
			ship.resource.spFinishingTextureList, spFinishingDrawParam)
		
		spGaugeDrawParam = Std.Sprite.DrawParam()
		spGaugeDrawParam.src = Std.RectF(0, 0, 64, 64)
		spGaugeDrawParam.dst = ship.position.makeRect(
			self.SPGAUGE_ANIME_SIZE, True)
		spGaugeDrawParam.priority = Ctrl.DrawPriority.myShip2
		self.spGaugeAnimation = createSequenceAnimation(
			ship.resource.spGaugeTextureList, spGaugeDrawParam)
	
	def update(self):
		self.shipDrawParam.dst = self.ship.position.makeRect(self.ship.SHIP_SIZE, True)
		self.hitMarkDrawParam.dst = self.ship.position.makeRect(self.HIT_MARK_SIZE, True)
		self.barrierDrawParam.dst = self.ship.position.makeRect(self.BARRIER_SIZE, True)
		if self.ship.barrierCount > 20:
			self.barrierDrawParam.color = Std.ColorF()
		else:
			self.barrierDrawParam.color = Std.ColorF(1, 1, 1, 
				self.ship.barrierCount * 1/20)
		
		if self.spBeginAnimation.playing:
			self.spBeginAnimation.update()
			updateDst(self.spBeginAnimation, 
				self.ship.position, self.SPBEGIN_ANIME_SIZE)
		if self.spFinishAnimation.playing:
			self.spFinishAnimation.update()
			updateDst(self.spFinishAnimation, 
				self.ship.position, self.SPFINISH_ANIME_SIZE)
		if self.spFinishingAnimation.playing:
			self.spFinishingAnimation.update()
			updateDst(self.spFinishingAnimation, 
				self.ship.position, self.SPFINISHING_ANIME_SIZE)
		if self.spGaugeAnimation.playing:
			self.spGaugeAnimation.update()
			updateDst(self.spGaugeAnimation, 
				self.ship.position, self.SPGAUGE_ANIME_SIZE)
	def draw(self):
		Std.Sprite.draw(self.shipDrawParam)
		
		if self.ship.slow:
			Std.Sprite.draw(self.hitMarkDrawParam)
		
		if self.ship.barriered:
			Std.Sprite.draw(self.barrierDrawParam)
		
		if self.spBeginAnimation.playing:
			self.spBeginAnimation.draw()
		if self.spFinishAnimation.playing:
			self.spFinishAnimation.draw()
		if self.spFinishingAnimation.playing:
			self.spFinishingAnimation.draw()
		if self.spGaugeAnimation.playing:
			self.spGaugeAnimation.draw()
	def drawInfArea(self, basePos):
		font = CommonResource.getFont("font32", 
			Ctrl.DrawPriority.infAreaStr, False, 24)
		rect = Std.RectF(basePos.x, basePos.y, 
			Std.Consts.StgInfAreaSize.x, 32)
		offset = Std.Point2DF()
		color = Std.ColorF()
		
		def repeatStr(count):
			string = "*" * count
			font.drawLeft(rect, offset, color, string)
		
		font.drawLeft(rect, offset, color, "Player:")
		rect.y += 32
		if self.ship.remainder > 0:
			repeatStr(self.ship.remainder - 1)
		
		rect.y += 32
		font.drawLeft(rect, offset, color, "Power:")
		rect.y += 32
		repeatStr(self.ship.powerCount)
		
		rect.y += 32
		font.drawLeft(rect, offset, color, "SpAttack:")
		rect.y += 32
		repeatStr(self.ship.spAttackCount)