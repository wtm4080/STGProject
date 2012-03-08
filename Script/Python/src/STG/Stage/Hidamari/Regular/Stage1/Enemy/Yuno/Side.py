'''
Created on 2011/01/22

@author: t
'''

import Std
import STG.Ctrl as Ctrl
from STG.Enemy.BaseEnemy import Base

from STG.Regulation.Hidamari.Regular.Stage1.Yuno import Side as Regulation

class Side(Base):
	SIZE = Std.Vector2DF(76, 66)
	
	def _createPos(self):
		if self.left:
			return Std.Vector2DF(
				self.core.locator.position.x + 150, 
				self.core.locator.position.y + 40)
		else:
			return Std.Vector2DF(
				self.core.locator.position.x - 150, 
				self.core.locator.position.y + 40)
	
	def __init__(self, core, left):
		self.core = core
		self.left = left
		super().__init__(
			Std.Hit.RectI(self._createPos(), 
				self.SIZE, True), 
			Regulation.sideHP)
	
	@property
	def position(self):
		return self._createPos()
	def applyExternalForce(self, vec):
		return self.core.locator.applyExternalForce(vec)
	
	def onUpdate(self):
		pass
	def onDraw(self):
		pass
	
	def onErase(self):
		pass
	def onDestructed(self):
		self.core.destructBullets()
		self.core.face.destruction()
		
		expNum = 10
		expPos = Std.Vector2DF(
			self.core.locator.position.x, 
			self.core.locator.position.y + 40)
		expSize = 196
		expItv = 2
		expPosBlur = Std.Vector2DF(64, 64)
		expSizeBlurRate = 0.3
		if self.left:
			self.core.move.addSpeed(Std.Vector2DF(-5, 0))
			expPos.x += 150
		else:
			self.core.move.addSpeed(Std.Vector2DF(5, 0))
			expPos.x -= 150
		expObjList = self.core.drawing.createExplosion(
				Ctrl.DrawPriority.enemy2, 
				expNum, expPos, expSize, expItv, 
				expPosBlur, expSizeBlurRate)
		for expObj in expObjList:
			expObj.locator.speed.y = 3
		Std.Sprite.setShake(15, 0.3)
		
		self.core.resource.se_Explode2.play()
		
		self.core.scoreManager.addScore(self.maxHp)
	def onDamaged(self, damage):
		self.core.applyDamage(damage * Regulation.coreDamageRate)
		self.core.scoreManager.addRate(damage * 0.01)
	def onDestructedByDamage(self, damage):
		self.onDestructed()