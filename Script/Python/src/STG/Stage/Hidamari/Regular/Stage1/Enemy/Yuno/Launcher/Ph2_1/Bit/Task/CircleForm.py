'''
Created on 2011/04/16

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs
from Util.Coroutine import Coroutine
from Util.Coroutine import createWait
import Util.NWay as NWay

from STG.Regulation.Hidamari.Regular.Stage1.Yuno import Phase2_1 as Regulation

class CircleForm:
	def __init__(self, core, bitNum, order, rank):
		self.core = core
		self.angle = 360/bitNum * order
		
		self.regulation = Regulation.BitTask1_CircleForm(rank)
	
	def task(self, bit):
		def getTargetPos():
			pos = Std.Vector2DF()
			pos.setUnitVector(self.angle)
			pos *= self.regulation.radius
			pos.y *= self.regulation.yScale
			pos += Std.Vector2DF(*self.regulation.offset)
			return self.core.position + pos
		def getTargetAngle():
			return self.core.position.getAngle(
				Ctrl.Actor.myShip.position)
		def launch():
			rand = Ctrl.getRandom()
			while True:
				drawParam = Auxs.createBulletRedDrawParam(
					bit.nozzlePos, Std.Vector2DF(16, 8))
				NWay.launchLinear(
					bit.nozzlePos, 
					bit.circling.angle, 
					self.regulation.angleInterval, 
					self.regulation.wayNum, 
					int(drawParam.dst.w/2), 
					drawParam, 
					self.regulation.speed)
				
				launchWait = createWait(
					rand.getFloat(*self.regulation.launchInterval))
				while launchWait(): yield
		
		bit.locator.tracing = True
		bit.locator.targetPosition = getTargetPos()
		bit.locator.maxCirclingAngle = 180
		bit.locator.speed = Std.Vector2DF(1, 0) * self.regulation.moveSpeed
		bit.circling.circling = True
		launcher = Coroutine(launch)
		yield
		
		wait = createWait(self.regulation.beginWait)
		while wait():
			self.angle += self.regulation.rotateSpeed
			bit.locator.targetPosition = getTargetPos()
			bit.circling.targetAngle = getTargetAngle()
			yield
		
		wait = createWait(self.regulation.rotateFrameNum)
		while wait():
			self.angle += self.regulation.rotateSpeed
			bit.locator.targetPosition = getTargetPos()
			bit.circling.targetAngle = getTargetAngle()
			launcher.resume()
			
			"""
			if Std.sin(self.angle) > 0:
				bit.drawPriority = Ctrl.DrawPriority.enemyB1
			else:
				bit.drawPriority = Ctrl.DrawPriority.enemy4
			"""
			yield
		
		wait = createWait(self.regulation.endWait)
		while wait():
			self.angle += self.regulation.rotateSpeed
			bit.locator.targetPosition = getTargetPos()
			bit.circling.targetAngle = getTargetAngle()
			yield