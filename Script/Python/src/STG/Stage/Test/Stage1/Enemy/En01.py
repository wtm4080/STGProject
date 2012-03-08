'''
Created on 2010/11/23

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs
from STG.Enemy.BaseEnemy import Base
from Util.Coroutine import Coroutine

class En01(Base):
	SIZE = Std.Vector2DF(128, 128)
	EXPLOSION_SIZE = Std.Vector2DF(96*5, 96*5)
	MAX_HP = 10000
	INIT_POS = Std.Vector2DF(220, -100)
	
	def __init__(self, res, scoreManager):
		super().__init__(
			Std.Hit.RectI(self.INIT_POS, self.SIZE, True), self.MAX_HP)
		self.locator = Std.Locator.LinearF(self.INIT_POS)
		self.resource = res
		self.scoreManager = scoreManager
		
		self.phaseCoroutine = Coroutine(self.updatePhase)
		self.destructionCoroutine = Coroutine(self.updateDestruction)
		
		self.hpGauge = Auxs.EnemyHPGauge(self.MAX_HP)
		self.hpGauge.appear()
		
		self.drawParam = Std.Sprite.DrawParam()
		self.drawParam.texture = res.icon4
		self.drawParam.src = Std.RectF(0, 0, 256, 256)
		self.drawParam.dst = self.locator.position.makeRect(
			self.SIZE, True)
		self.drawParam.priority = Ctrl.DrawPriority.enemy
	
	@property
	def position(self):
		return self.locator.position
	def applyExternalForce(self, vec):
		return self.locator.applyExternalForce(vec)
	
	def onUpdate(self):
		self.locator.update()
		self.drawParam.dst = self.locator.position.makeRect(
			self.SIZE, True)
		
		self.hpGauge.value = self.hp
		self.hpGauge.update()
		
		if self.hp > 0 and self.phaseCoroutine.alive:
			self.phaseCoroutine.resume()
		elif self.destructionCoroutine.alive:
			self.destructionCoroutine.resume()
	def updatePhase(self):
		self.locator.speed.setUnitVector(90)
		self.locator.speed *= 4
		while self.locator.position.y < 100: yield
		
		self.locator.speed *= 0
		mlActor = None
		while self.hp > 0:
			if mlActor is None or not mlActor.valid:
				mlActor = Auxs.Bullet.MLActor(
					self.resource.bml_En01_01, 
					self.locator.position)
				
				createParam = Auxs.Bullet.MLParam()
				createParam.hitRadius = 2
				createParam.drawParameter = Auxs.createBulletBlueDrawParam(
					self.locator.position, Std.Vector2DF(14, 14))
				mlActor.addCreateParam(createParam)
			
			mlActor.locator.position = self.locator.position
			mlActor.update()
			
			yield
	def updateDestruction(self):
		Auxs.eraseBullets()
		
		frameCount = 0
		explosionInterval = Std.RepeatCounter(3)
		random = Ctrl.getRandom()
		
		self.locator.accel.setUnitVector(90)
		self.locator.accel *= 0.08
		
		while frameCount < 60:
			explosionInterval.update()
			for _ in range(explosionInterval.repeatCount):
				offset = Std.Vector2DF(
					random.getFloat(-self.SIZE.x/2, self.SIZE.x/2), 
					random.getFloat(-self.SIZE.y/2, self.SIZE.y/2))
				Auxs.createExplosion(
					self.locator.position + offset, 
					self.EXPLOSION_SIZE / 2.0)
			
			frameCount += 1
			yield
		else:
			Std.Sprite.setShake(20, 0.3)
			Auxs.createExplosion(
				self.position, self.EXPLOSION_SIZE, 2)
			self.valid = False
	def onDraw(self):
		Std.Sprite.draw(self.drawParam)
		if self.hp > 0:
			self.hpGauge.draw()
	
	def onErase(self):
		self.onDestructed()
	def onDestructed(self):
		self.hp = 0
		self.valid = True
		self.scoreManager.addScore(self.maxHp)
	def onDamaged(self, damage):
		self.scoreManager.addRate(damage * 0.01)
	def onDestructedByDamage(self, damage):
		self.onDestructed()