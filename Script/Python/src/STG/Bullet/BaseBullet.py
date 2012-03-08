'''
Created on 2010/10/23

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Actor.BaseActor as BaseActor
import STG.Resource.Common as CommonResource

class Base(BaseActor.Base):
	INIT_HP = 100
	
	def __init__(self, pos, radius):
		super().__init__(
			Std.Hit.RectI(pos, radius*2, radius*2, True))
		self.hitCircle = Std.Hit.CircleI(pos, radius)
		self.hitRect = Std.Hit.RectI(pos, radius*2, radius*2, True)
		self.hp = self.INIT_HP
		self.damagedEffectScale = 2
		
		self.damagedDrawParam = Std.Sprite.DrawParam()
		self.damagedDrawParam.texture = CommonResource.get("bulletDamagedEffect")
		self.damagedDrawParam.src = Std.RectF(0, 0, 64, 64)
		self.damagedDrawParam.dst = pos.makeRect(
			radius*2 * self.damagedEffectScale, 
			radius*2 * self.damagedEffectScale, 
			True)
		self.damagedDrawParam.priority = Ctrl.DrawPriority.enemyBulletDamaged
		self.damagedDrawParam.color = Std.ColorF(1, 1, 1, 0)
		self.damagedDrawParam.alphaBlend = Std.Sprite.AlphaBlend.Add
	
	def isHitCircle(self, hit):
		return self.hitCircle.isHit(hit)
	def isHitRect(self, hit):
		return self.hitRect.isHit(hit)
	
	@property
	def hitRadius(self):
		return self.hitCircle.radius
	@hitRadius.setter
	def hitRadius(self, radius):
		self.hitCircle.radius = radius
		self.hitRect.size = Std.Vector2DI(radius*2, radius*2)
		self.validRect = self.hitRect
	
	def destruct(self):
		if self.valid and self.hp > 0:
			self.valid = False
			self.onDestructed()
	def applyDamage(self, damage):
		if self.valid and self.hp > 0:
			self.hp -= damage
			self.onDamaged(damage)
			
			effectAlphaMax = 0.4
			if self.damagedDrawParam.color.a < effectAlphaMax:
				self.damagedDrawParam.color.a += 0.1
			else:
				self.damagedDrawParam.color.a = effectAlphaMax
			
			if self.hp <= 0:
				self.valid = False
				self.onDestructedByDamage(damage)
	
	def update(self):
		super().update()
		self.updateDamagedDraw()
	def updateMiddle(self):
		pos = self.position
		self.hitCircle.center = pos
		self.hitRect.center = pos
		
		if self.hp <= 0:
			self.destruct()
	
	def updateDamagedDraw(self):
		self.damagedDrawParam.dst = (
			self.position).makeRect(
				self.hitRadius*2 * self.damagedEffectScale, 
				self.hitRadius*2 * self.damagedEffectScale, 
				True)
		if self.damagedDrawParam.color.a > 0:
			self.damagedDrawParam.color.a -= 0.01
		else:
			self.damagedDrawParam.color.a = 0
	def drawMiddle(self):
		if self.damagedDrawParam.color.a > 0:
			Std.Sprite.draw(self.damagedDrawParam)
	
	
	def onDestructed(self):
		raise Exception("BaseBullet.Base.onDestructed is not implemented.")
	def onDamaged(self, damage):
		raise Exception("BaseBullet.Base.onDamaged is not implemented.")
	def onDestructedByDamage(self, damage):
		raise Exception("BaseBullet.Base.onDestructedByDamage is not implemented.")