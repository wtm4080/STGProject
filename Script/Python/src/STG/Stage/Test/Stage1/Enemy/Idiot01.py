'''
Created on 2010/11/23

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs
from STG.Enemy.BaseEnemy import Base

class Idiot01(Base):
	SIZE = Std.Vector2DF(48, 48)
	EXPLOSION_SIZE = Std.Vector2DF(96, 96)
	MAX_HP = 10
	
	def __init__(self, pos, res, scoreManager):
		super().__init__(
			Std.Hit.RectI(pos, self.SIZE, True), self.MAX_HP)
		self.scoreManager = scoreManager
		
		self.locator = Std.Locator.LinearF(pos)
		self.locator.speed.setUnitVector(90)
		self.locator.speed *= 4
		
		self.drawParam = Std.Sprite.DrawParam()
		self.drawParam.texture = res.icon2
		self.drawParam.src = Std.RectF(0, 0, 256, 256)
		self.drawParam.dst = pos.makeRect(self.SIZE, True)
		self.drawParam.priority = Ctrl.DrawPriority.enemy
		
		self.launchInterval = Std.RepeatCounter(16)
	
	@property
	def position(self):
		return self.locator.position
	def applyExternalForce(self, vec):
		return self.locator.applyExternalForce(vec)
	
	def onUpdate(self):
		self.locator.update()
		self.drawParam.dst = self.locator.position.makeRect(
			self.SIZE, True)
		
		self.launchInterval.update()
		for _ in range(self.launchInterval.repeatCount):
			self.launchSimpleBullet()
	def onDraw(self):
		Std.Sprite.draw(self.drawParam)
	
	def onErase(self):
		self.onDestructed()
	def onDestructed(self):
		Auxs.createExplosion(
			self.position, self.EXPLOSION_SIZE)
		self.scoreManager.addScore(self.maxHp)
	def onDamaged(self, damage):
		self.scoreManager.addRate(damage * 0.01)
	def onDestructedByDamage(self, damage):
		self.onDestructed()
		
		item = Auxs.Item.PowerUp(self.locator.position)
		def effectCallback(result):
			if not result:
				self.scoreManager.addScore(1000)
		item.setEffectCallback(effectCallback)
		Ctrl.Actor.registerItem(item)
	
	def launchSimpleBullet(self):
		pos = self.position
		angle = 90 - 20
		
		for i in range(3):
			locator = Std.Locator.LinearF(pos)
			locator.speed.setUnitVector(angle)
			locator.speed *= 6
			
			hitRadius = 3
			
			drawParam = Auxs.createBulletRedDrawParam(
				pos, Std.Vector2DF(14, 14))
			
			bullet = Auxs.Bullet.Linear(locator, hitRadius, drawParam)
			Ctrl.Actor.registerBullet(bullet)
			
			angle = 90 + 20*i