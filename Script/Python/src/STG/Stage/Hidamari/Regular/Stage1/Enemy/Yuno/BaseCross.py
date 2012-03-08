'''
Created on 2011/02/21

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs

from STG.Bullet.BaseBullet import Base

class BaseCross(Base):
	def __init__(self, resource, pos, size, rotSpeed):
		super().__init__(pos, size.x / 4)
		self.size = size
		self.rotSpeed = rotSpeed
		self.particleRepCounter = Std.RepeatCounter(6)
		
		self.drawParam = Std.Sprite.DrawParam()
		self.drawParam.texture = resource.st1_YunoCross
		self.drawParam.src = Std.RectF(0, 0, 64, 64)
		self.drawParam.dst = pos.makeRect(size, True)
		self.drawParam.priority = Ctrl.DrawPriority.enemyBullet
		
		self.createInitialParticle()
	
	def onUpdate(self):
		self.drawParam.dst = self.locator.position.makeRect(self.size, True)
		self.drawParam.rotDegree += self.rotSpeed
		
		self.particleRepCounter.update()
		for _ in range(self.particleRepCounter.repeatCount):
			self.createParticle()
	def onDraw(self):
		Std.Sprite.draw(self.drawParam)
	
	def onErase(self):
		self.createParticle(10, Ctrl.DrawPriority.enemyBullet2, 0.6, 2)
	def onDestructed(self):
		self.onErase()
	def onDamaged(self, damage):
		pass
	def onDestructedByDamage(self, damage):
		self.onErase()
	
	def createParticle(self, 
					num = 1, 
					priority = Ctrl.DrawPriority.enemyBulletB1, 
					sizeRate = 0.3, 
					speed = 1):
		rand = Ctrl.getRandom()
		
		drawParam = Std.Sprite.DrawParam()
		drawParam.texture = self.drawParam.texture
		drawParam.src = Std.RectF(0, 0, 64, 64)
		drawParam.dst = self.locator.position.makeRect(self.size * sizeRate, True)
		drawParam.priority = priority
		drawParam.alphaBlend = Std.Sprite.AlphaBlend.Add
		drawParam.rotDegree = rand.getFloat(-180, 180)
		
		param = Auxs.Particle.Param()
		param.drawParameter = drawParam
		param.setPosition(self.locator.position)
		param.setSpeedRange(speed * 0.5, speed * 1.5)
		param.setZoomRateRange(0.8, 1)
		param.setZoomDecRateRange(0.015, 0.025)
		param.setRotSpeedRange(self.rotSpeed - 0.5, self.rotSpeed + 0.5)
		
		creator = Auxs.Particle.Creator(param)
		creator.create(num)
	def createInitialParticle(self):
		self.createParticle(10, Ctrl.DrawPriority.enemyBullet2, 0.6, 2)