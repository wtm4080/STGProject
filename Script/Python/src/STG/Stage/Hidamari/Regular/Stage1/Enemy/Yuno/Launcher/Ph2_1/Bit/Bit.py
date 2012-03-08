'''
Created on 2011/02/21

@author: t
'''

import Std
import STG.Ctrl as Ctrl
from Util.Sprite.Animation import createSequenceAnimation
import Util.Misc as Misc
from STG.Enemy.BaseEnemy import Base

from STG.Regulation.Hidamari.Regular.Stage1.Yuno import Phase2_1 as Regulation

class Bit(Base):
	SIZE = Std.Vector2DF(52, 60)
	CIRCLING_ANGLE = 4
	HP = 2000
	
	def __init__(self, pos, angle, resource, scoreManager, rank):
		self.regulation = Regulation.Bit(rank)
		
		super().__init__(
			Std.Hit.RectI(pos, self.SIZE, True), self.regulation.hp)
		self.setValidAreaMargin(50)
		
		self.locator = Std.Locator.TraceF(180)
		self.locator.position = pos
		
		self.circling = Std.CirclingF(self.CIRCLING_ANGLE)
		
		drawParam = Std.Sprite.DrawParam()
		drawParam.src = Std.RectF(0, 0, 52, 60)
		drawParam.dst = self.locator.position.makeRect(self.SIZE, True)
		drawParam.priority = Ctrl.DrawPriority.enemyB1
		self.animation = createSequenceAnimation(
			resource.st1_YunoBitTexList, drawParam)
		self.animation.play()
		
		self.angle = angle
		
		self.scoreManager = scoreManager
		
		self.se_Explode = resource.se_Explode1
	
	@property
	def drawPriority(self):
		return self.animation.frameHolder.drawParameter.priority
	@drawPriority.setter
	def drawPriority(self, pri):
		drawParam = self.animation.frameHolder.drawParameter
		drawParam.priority = pri
		self.animation.frameHolder.drawParameter = drawParam
	
	@property
	def angle(self):
		return self.circling.angle
	@angle.setter
	def angle(self, angle):
		self.circling.angle = angle
		drawParam = self.animation.frameHolder.drawParameter
		drawParam.rotDegree = angle + 90
		self.animation.frameHolder.drawParameter = drawParam
	
	@property
	def nozzlePos(self):
		pos = self.locator.position
		offset = Std.Vector2DF()
		offset.setUnitVector(self.circling.angle)
		offset *= 25
		return pos + offset
	@property
	def backNozzlePos(self):
		pos = self.locator.position
		offset = Std.Vector2DF()
		offset.setUnitVector(self.circling.angle + 180)
		offset *= 25
		return pos + offset
	
	@property
	def position(self):
		return self.locator.position
	def applyExternalForce(self, vec):
		return self.locator.applyExternalForce(vec)
	
	def onUpdate(self):
		self.locator.update()
		self.circling.update()
		
		drawParam = self.animation.frameHolder.drawParameter
		drawParam.dst = self.locator.position.makeRect(self.SIZE, True)
		drawParam.rotDegree = self.circling.angle + 90
		self.animation.frameHolder.drawParameter = drawParam
		if not self.animation.playing:
			self.animation.play()
		self.animation.update()
	def onDraw(self):
		self.animation.draw()
	
	def onErase(self):
		Misc.createExplosion(
			Ctrl.DrawPriority.enemy, 
			4, 
			self.locator.position, 
			150, 
			1, 
			Std.Vector2DF(32, 32), 
			0.5
			)
		self.se_Explode.play()
	def onDestructed(self):
		self.scoreManager.addScore(self.maxHp)
		self.onErase()
	def onDamaged(self, damage):
		self.scoreManager.addRate(damage * 0.01)
	def onDestructedByDamage(self, damage):
		self.onDestructed()