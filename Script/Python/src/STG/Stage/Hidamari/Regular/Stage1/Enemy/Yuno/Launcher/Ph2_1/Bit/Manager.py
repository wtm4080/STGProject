'''
Created on 2011/04/16

@author: t
'''

import STG.Ctrl as Ctrl
from Util.Coroutine import Coroutine
from Util.Coroutine import createWait
import Util.NWay as NWay

from .Bit import Bit
from .Task.Aiming import Aiming
from .Task.Charge import Charge
from .Task.CircleForm import CircleForm
from .Task.LaunchTracingCross import LaunchTracingCross

from ..ChainGun import ChainGun

from STG.Regulation.Hidamari.Regular.Stage1.Yuno import Phase2_1 as Regulation
taskListIndex = None

class Manager:
	def __init__(self, core, rank = 1):
		self.regulation = Regulation.BitManager(rank)
		
		self._num = self.regulation.bitNum
		self.core = core
		self.rank = rank
		self.bitPairList = []
		self.main = Coroutine(self._main)
		self._initialized = False
		self.chainGun = None
	
	@property
	def num(self):
		return self._num
	@property
	def end(self):
		return self._initialized and not self.bitPairList
	
	def update(self):
		if self.main.alive:
			self.main.resume()
		for bitPair in self.bitPairList:
			if not bitPair[0].valid:
				self.bitPairList.remove(bitPair)
			elif bitPair[1].alive:
				bitPair[1].resume(bitPair[0])
		if not self.chainGun is None:
			self.chainGun.update()
	def _main(self):
		angleList = NWay.getAngleList(
			self.regulation.bitCreationBaseAngle, 
			self.regulation.bitCreationAngleInterval, 
			self.num)
		angleList.sort(reverse = True)
		while len(self.bitPairList) < self.num:
			bit = Bit(self.core.locator.position, 
				angleList[len(self.bitPairList)], 
				self.core.resource, self.core.scoreManager, self.rank)
			Ctrl.Actor.registerEnemy(bit)
			self.core.subEnemyObjList.append(bit)
			
			def initialControl(bit):
				bit.locator.tracing = False
				bit.circling.circling = False
				bit.locator.speed.setUnitVector(bit.angle)
				bit.locator.speed *= 6
				bit.locator.accel.setUnitVector(bit.angle)
				bit.locator.accel *= -0.1
				
				while bit.locator.speed.getAbs() > 1:
					yield
				
				bit.locator.speed *= 0
				bit.locator.accel *= 0
				bit.drawPriority = Ctrl.DrawPriority.enemy4
			bitPair = [bit, Coroutine(initialControl)]
			self.bitPairList.append(bitPair)
			
			wait = createWait(self.regulation.bitCreationInterval)
			while wait(): yield
		
		def allTaskFinished():
			finished = True
			
			for bitPair in self.bitPairList:
				if bitPair[1].alive:
					finished = False
					break
			
			if self.chainGun and self.chainGun.alive:
				finished = False
			
			return finished
		
		while not allTaskFinished(): yield
		
		self._initialized = True
		
		charging = False
		firstChoice = True
		prevTaskNum = None
		while self.bitPairList:
			if len(self.bitPairList) <= self.regulation.forceChargeBitNum and not charging:
				self.chainGun = None
				for bitPair in self.bitPairList:
					charge = Charge(self.rank)
					bitPair[1] = Coroutine(charge.task)
				charging = True
			
			if allTaskFinished():
				self.chainGun = None
				for bitPair in self.bitPairList:
					bit = bitPair[0]
					bit.drawPriority = Ctrl.DrawPriority.enemy4
					bit.locator.tracing = False
					bit.locator.speed *= 0
					bit.locator.accel *= 0
					bit.circling.circling = False
				
				bitTaskList = self.regulation.bitTaskList
				if not bitTaskList:
					rand = Ctrl.getRandom()
					if firstChoice:
						taskNum = rand.getInt(0, 1)
					else:
						while True:
							taskNum = rand.getInt(0, 3)
							if taskNum != prevTaskNum:
								break
				else:
					global taskListIndex
					if taskListIndex is None or taskListIndex == len(bitTaskList):
						taskListIndex = 0
					taskNum = bitTaskList[taskListIndex]
					taskListIndex += 1
				
				if taskNum == 0:
					for i in range(len(self.bitPairList)):
						if i < self.num / 2:
							aiming = Aiming(self.core, self.rank, False)
						else:
							aiming = Aiming(self.core, self.rank, True)
						self.bitPairList[i][1] = Coroutine(aiming.task)
					self.chainGun = ChainGun(self.core, self.rank)
				elif taskNum == 1:
					for i in range(len(self.bitPairList)):
						circle = CircleForm(self.core, self.num, i, self.rank)
						self.bitPairList[i][1] = Coroutine(circle.task)
				elif taskNum == 2:
					for i in range(len(self.bitPairList)):
						if i < len(self.bitPairList) / 2:
							clockwise = False
						else:
							clockwise = True
						tracingCross = LaunchTracingCross(
							self.core, clockwise, self.rank)
						self.bitPairList[i][1] = Coroutine(tracingCross.task)
				elif taskNum == 3:
					for bitPair in self.bitPairList:
						charge = Charge(self.rank)
						bitPair[1] = Coroutine(charge.task)
					charging = True
			firstChoice = False
			prevTaskNum = taskNum
			yield