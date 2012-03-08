'''
Created on 2010/11/10

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs
from STG.MyShot.BaseMyShot import Base
import STG.Resource.Common as CommonResource

class Laser(Base):
	RADIUS = 3
	SIZE = Std.Vector2DF(40, RADIUS*2)
	SPEED = 30
	BASE_DAMAGE = 4
	DAMAGE_RATE_DEC = 0.06
	DAMAGE_RATE_MIN = 0.5
	
	def __init__(self, position, angle):
		super().__init__(position, self.RADIUS, self.BASE_DAMAGE)
		
		self.locator = Std.Locator.LinearF(position)
		self.locator.speed.setUnitVector(angle)
		self.locator.speed *= self.SPEED
		
		self.damageRateDec = self.DAMAGE_RATE_DEC
		self.damageRateMin = self.DAMAGE_RATE_MIN
		
		self.drawParam = Std.Sprite.DrawParam()
		self.drawParam.texture = CommonResource.get("bulletGreen")
		self.drawParam.src = Std.RectF(0, 0, 64, 64)
		self.drawParam.dst = self.locator.position.makeRect(self.SIZE, True)
		self.drawParam.priority = Ctrl.DrawPriority.myShot
		self.drawParam.rotDegree = angle
		self.drawParam.color = Std.ColorF(1, 1, 1, 0.8)
	
	@property
	def position(self):
		return self.locator.position
	def applyExternalForce(self, vec):
		return self.locator.applyExternalForce(vec)
	
	def onUpdate(self):
		self.locator.update()
		self.drawParam.dst = self.locator.position.makeRect(self.SIZE, True)
		self.drawParam.rotDegree = self.locator.speed.getAngle()
	def onDraw(self):
		Std.Sprite.draw(self.drawParam)
	
	def onErase(self):
		Auxs.createFadeOut(self.drawParam)
	def onDestructed(self):
		drawParam = Std.Sprite.DrawParam()
		drawParam.texture = CommonResource.get("bulletGreen")
		drawParam.src = Std.RectF(0, 0, 64, 64)
		drawParam.dst = self.locator.position.makeRect(12, 12, True)
		drawParam.priority = Ctrl.DrawPriority.myShot
		drawParam.alphaBlend = Std.Sprite.AlphaBlend.Add
		param = Auxs.Particle.Param()
		param.drawParameter = drawParam
		
		angle = self.locator.speed.getAngle()
		direction = Std.Vector2DF()
		direction.setUnitVector(angle)
		param.setPosition(self.locator.position + direction*10)
		param.setAngleRange(angle+180 - 20, angle+180 + 20)
		param.setSpeedRange(8, 12)
		param.setZoomRateRange(0.8, 1)
		param.setZoomDecRateRange(0.06, 0.08)
		
		creator = Auxs.Particle.Creator(param)
		creator.create(2)
	def onDamaged(self, damage):
		pass
	def onDestructedByDamage(self, damage):
		self.onErase()