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

class Aiming:
	def __init__(self, core, rank, left):
		self.core = core
		self.left = left
		
		self.regulation = Regulation.BitTask0_Aiming(rank)
	
	def task(self, bit):
		wait = createWait(self.regulation.firstWait)
		while wait(): yield
		
		for _ in range(int(self.regulation.repeatNum)):
			if self.left:
				center = self.core.locator.position + Std.Vector2DF(
					*self.regulation.moveCenterPosOffset)
			else:
				offset = Std.Vector2DF(*self.regulation.moveCenterPosOffset)
				offset.x *= -1
				center = self.core.locator.position + offset
			
			areaSizeX = self.regulation.moveAreaSize[0] / 2
			areaSizeY = self.regulation.moveAreaSize[1] / 2
			rand = Ctrl.getRandom()
			bitPos = center + Std.Vector2DF(
				rand.getFloat(-areaSizeX, areaSizeX), 
				rand.getFloat(-areaSizeY, areaSizeY))
			bit.locator.tracing = True
			bit.locator.maxCirclingAngle = 180
			bit.locator.targetPosition = bitPos
			bit.locator.speed = Std.Vector2DF(1, 0) * 4
			bit.locator.accel *= 0
			
			wait = createWait(
				self.regulation.launchFrameNum + 
				rand.getFloat(*self.regulation.launchFrameNumVariance))
			launcher = None
			while wait():
				if bit.locator.speed.getAbs() > 0.1:
					speedAngle = bit.locator.speed.getAngle()
					accel = Std.Vector2DF()
					accel.setUnitVector(speedAngle + 180)
					accel *= 0.1
					bit.locator.accel = accel
				else:
					bit.locator.speed *= 0
					bit.locator.accel *= 0
					
					def launch():
						for _ in range(int(self.regulation.launchRepeat)):
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
							
							launchWait = createWait(self.regulation.launchRepeatInterval)
							while launchWait(): yield
					if launcher is None:
						launcher = Coroutine(launch)
					if launcher.alive:
						launcher.resume()
				
				if not launcher is None and launcher.alive:
					bit.circling.circling = False
				else:
					targetAngle = bit.locator.position.getAngle(
						Ctrl.Actor.myShip.position)
					bit.circling.circling = True
					bit.circling.targetAngle = targetAngle
				yield