'''
Created on 2011/11/10

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs
from STG.Enemy.BaseEnemy import Base
import Util.Misc as Misc
from Util.Coroutine import Coroutine
from Util.Coroutine import createWait
import Util.NWay as NWay

from STG.Regulation.Hidamari.Regular.Stage1.Idiot import Mikan as Regulation

class Mikan(Base):
	SIZE = Std.Vector2DF(128, 100)/3 * 2
	MAX_HP = Regulation.hp
	
	def __init__(self, resource, scoreManager, pos, speed):
		super().__init__(
			Std.Hit.RectI(pos, self.SIZE, True), self.MAX_HP)
		self.scoreManager = scoreManager
		self.task = Coroutine(self._task)
		
		self.locator = Std.Locator.LinearF(pos)
		self.locator.speed.setUnitVector(90)
		self.locator.speed *= speed
		
		self.drawParam = Std.Sprite.DrawParam()
		self.drawParam.texture = resource.st1_Mikan
		self.drawParam.src = Std.RectF(0, 0, 128, 100)
		self.drawParam.dst = pos.makeRect(self.SIZE, True)
		self.drawParam.priority = Ctrl.DrawPriority.enemy
		
		self.se_Explode = resource.se_Explode1
	
	@property
	def position(self):
		return self.locator.position
	def applyExternalForce(self, vec):
		return self.locator.applyExternalForce(vec)
	
	@property
	def speed(self):
		return self.locator.speed.getAbs()
	@speed.setter
	def speed(self, value):
		self.locator.speed.normalize()
		self.locator.speed *= value
	
	def onUpdate(self):
		self.locator.update()
		if self.task.alive:
			self.task.resume()
		
		self.drawParam.dst = self.position.makeRect(self.SIZE, True)
	def _task(self):
		def getLaunchPos():
			pos = self.position
			return Std.Vector2DF(pos.x, pos.y + self.SIZE.y / 3)
		validAreaRect = Std.Hit.RectI(
			0, 
			0, 
			Std.Consts.ScreenSize.x - Std.Consts.StgInfAreaSize.x, 
			Std.Consts.ScreenSize.y, 
			False)
		
		while True:
			wait = createWait(Regulation.waitFrameNum)
			while wait(): yield
			
			drawParam = Auxs.createBulletRedDrawParam(
				getLaunchPos(), Std.Vector2DF(10, 10))
			angle = self.position.getAngle(Ctrl.Actor.myShip.position)
			interval = Regulation.interval
			num = Regulation.wayNum
			radius = int(drawParam.dst.w/2)
			for _ in range(Regulation.launchNum):
				pos = getLaunchPos()
				NWay.launchLinear(pos, angle, interval, num, radius, drawParam)
				launchInterval = createWait(Regulation.launchInterval)
				while launchInterval(): yield
			
			if not validAreaRect.isHit(self.hitRect):
				break
	def onDraw(self):
		Std.Sprite.draw(self.drawParam)
	
	def onErase(self):
		Misc.createExplosion(
			Ctrl.DrawPriority.enemy, 
			5, 
			self.locator.position, 
			200, 
			1, 
			Std.Vector2DF(48, 48)
			)
		self.se_Explode.play()
	def onDestructed(self):
		self.onErase()
		self.scoreManager.addScore(self.maxHp)
		
		itemNum = Regulation.itemNum
		angleList = NWay.getAngleList(
			Regulation.itemLaunchAngle, Regulation.itemLaunchAngleInterval, itemNum)
		def effectCallback(result):
			if not result:
				self.scoreManager.addScore(1000)
		for angle in angleList:
			item = Auxs.Item.PowerUp(self.position, angle)
			item.setEffectCallback(effectCallback)
			Ctrl.Actor.registerItem(item)
	def onDamaged(self, damage):
		self.scoreManager.addRate(damage * 0.01)
	def onDestructedByDamage(self, damage):
		self.onDestructed()