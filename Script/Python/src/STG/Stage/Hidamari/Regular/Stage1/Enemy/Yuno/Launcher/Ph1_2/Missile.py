'''
Created on 2011/02/21

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs
from STG.Enemy.BaseEnemy import Base
from Util.Coroutine import Coroutine
import Util.Misc as Misc

from STG.Regulation.Hidamari.Regular.Stage1.Yuno import Phase1_2 as Regulation

class Missile(Base):
	SIZE = Std.Vector2DF(20, 68)
	VALID_AREA = Std.Hit.RectI(
		30, 
		30, 
		Std.Consts.ScreenSize.x - Std.Consts.StgInfAreaSize.x - 30*2, 
		Std.Consts.ScreenSize.y - 30*2, 
		False)
	
	def __init__(self, pos, resource, rank):
		self.regulation = Regulation.Missile(rank)
		
		super().__init__(
			Std.Hit.RectI(pos, self.SIZE, True), self.regulation.missileHP)
		self.rank = rank
		self.task = Coroutine(self._task)
		
		self.locator = Std.Locator.TraceF(self.regulation.circlingAngle)
		self.locator.position = pos
		self.locator.accel.setUnitVector(90)
		self.locator.accel *= self.regulation.accel
		self.locator.tracing = False
		
		self.drawParam = Std.Sprite.DrawParam()
		self.drawParam.texture = resource.st1_YunoMissile
		self.drawParam.src = Std.RectF(0, 0, 20, 68)
		self.drawParam.dst = pos.makeRect(self.SIZE, True)
		self.drawParam.priority = Ctrl.DrawPriority.enemy
		self.drawParam.rotDegree = self.locator.speed.getAngle() + 90
		
		self.se_Explode = resource.se_Explode1
	
	@property
	def position(self):
		return self.locator.position
	def applyExternalForce(self, vec):
		return self.locator.applyExternalForce(vec)
	
	def onUpdate(self):
		self.locator.update()
		
		self.drawParam.dst = self.locator.position.makeRect(self.SIZE, True)
		self.drawParam.rotDegree = self.locator.speed.getAngle() + 90
		
		if self.task.alive:
			self.task.resume()
	def _task(self):
		def createBackFire(priority):
			offset = Std.Vector2DF()
			offset.setUnitVector(self.locator.speed.getAngle() - 180)
			offset *= self.SIZE.y / 2
			Misc.createExplosion(
				priority, 
				1, 
				self.locator.position + offset, 
				32, 
				0.5
				)
		
		while self.locator.speed.getAbs() < self.regulation.maxSpeed:
			createBackFire(Ctrl.DrawPriority.enemy)
			yield
		
		"""
		wait = createWait(20)
		while wait(): yield
		"""
		
		self.locator.tracing = True
		self.locator.speed.normalize()
		self.locator.speed *= self.regulation.maxSpeed
		self.locator.accel *= 0
		self.drawParam.priority = Ctrl.DrawPriority.enemy4
		
		while True:
			createBackFire(Ctrl.DrawPriority.enemy4)
			self.locator.targetPosition = Ctrl.Actor.myShip.position
			
			distance = self.locator.position.getDistance(
				Ctrl.Actor.myShip.position)
			if distance < self.regulation.triggerDistance or not self.isHit(self.VALID_AREA):
				self.destruct()
			
			yield
	def onDraw(self):
		Std.Sprite.draw(self.drawParam)
	
	def onErase(self):
		Misc.createExplosion(
			Ctrl.DrawPriority.enemy4, 
			4, 
			self.locator.position, 
			150, 
			1, 
			Std.Vector2DF(32, 32), 
			0.5
			)
		self.se_Explode.play()
	def onDestructed(self):
		self.onErase()
		warhead = Warhead(
			self.locator.position, 
			self.locator.speed.getAngle(), 
			self.rank)
		Ctrl.Actor.registerActor(warhead)
	def onDamaged(self, damage):
		pass
	def onDestructedByDamage(self, damage):
		self.onDestructed()

from STG.Actor.BaseActor import Base as BaseActor
import Util.NWay as NWay

class Warhead(BaseActor):
	def __init__(self, pos, angle, rank):
		super().__init__(
			Std.Hit.RectI(pos, 0, 0, True))
		self.pos = Std.Vector2DF(pos)
		self.angle = angle
		self.main = Coroutine(self._main)
		
		self.regulation = Regulation.Missile(rank)
	
	@property
	def position(self):
		return self.pos
	def applyExternalForce(self, vec):
		return Std.Vector2DF()
	
	def onUpdate(self):
		if self.main.alive:
			self.main.resume()
		else:
			self.valid = False
	def onDraw(self):
		pass
	
	def onErase(self):
		pass
	
	def _main(self):
		def launch(pos, drawParam, num, baseSpeed):
			drawParam.dst = pos.makeRect(
				drawParam.dst.w, drawParam.dst.h, True)
			NWay.launchLinearCircle(
				pos, 
				self.angle, 
				num, 
				int(drawParam.dst.w/4), 
				drawParam, 
				baseSpeed)
		
		drawParam = Auxs.createBulletRedDrawParam(
			self.pos, Std.Vector2DF(16, 16))
		launch(self.pos, drawParam, 
			self.regulation.circleBulletNum, self.regulation.circleBulletSpeed)
		
		rand = Ctrl.getRandom()
		drawParam = Auxs.createBulletRedDrawParam(
			self.pos, Std.Vector2DF(16, 8))
		for _ in range(int(self.regulation.randomBulletLaunchFrameNum)):
			for _ in range(int(self.regulation.randomBulletLaunchNum)):
				posVariance = Std.Vector2DF(
					rand.getFloat(*self.regulation.randomBulletPosVariance), 
					rand.getFloat(*self.regulation.randomBulletPosVariance))
				pos = self.pos + posVariance
				launch(pos, drawParam, 1, self.regulation.randomBulletSpeed)
			yield