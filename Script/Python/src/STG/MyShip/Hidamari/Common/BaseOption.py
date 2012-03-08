'''
Created on 2011/11/28

@author: t
'''

import Std

class BaseOption:
	CIRCLINGANGLE = 4
	
	def __init__(self, core, pos, target):
		self.core = core
		
		self.locator = Std.Locator.TraceF(180)
		self.locator.tracing = True
		self.locator.position = pos
		self.locator.targetPosition = target
		self.locator.speed.setUnitVector(90)
		self.locator.speed *= 5
		
		self.circling = Std.CirclingF(self.CIRCLINGANGLE)
		self.circling.circling = True
		self.circling.angle = -90
		self.circling.targetAngle = -90
	
	@property
	def angle(self):
		return self.circling.angle
	
	@property
	def pos(self):
		return self.locator.position
	@pos.setter
	def pos(self, pos):
		self.locator.position = pos
	
	@property
	def nozzlePos(self):
		offset = Std.Vector2DF()
		offset.setUnitVector(self.circling.angle)
		offset *= 24
		return self.pos + offset
	
	def update(self):
		self.locator.update()
		self.circling.update()
		self.onUpdate()
	def onUpdate(self):
		pass
	def draw(self):
		self.onDraw()
	def onDraw(self):
		pass

class BaseManager:
	def __init__(self, core, relPosList, relPosAimingList, angleList, 
				optionClass, lockedEnemyGetter, initialLevel = 1):
		self.core = core
		self.relPosList = relPosList
		self.relPosAimingList = relPosAimingList
		self.angleList = angleList
		self.optionClass = optionClass
		self.lockedEnemyGetter = lockedEnemyGetter
		self.optionList = []
		self._level = 0
		self.level = initialLevel
	
	def _updateOptionState(self):
		for i in range(self._level):
			pos = self.core.position
			if self.core.slow:
				target = pos + self.relPosAimingList[i]
				speed = 4
				
				targetAngle = []
				launchable = []
				for j in range(i*2, i*2 + 2):
					enemy = self.lockedEnemyGetter(j)
					if not enemy is None:
						targetAngle.append(
							self.optionList[j].pos.getAngle(enemy.position)) 
						launchable.append(True)
					else:
						targetAngle.append(-90)
						launchable.append(False)
			else:
				target = pos + self.relPosList[i]
				speed = 5
				targetAngle = (self.angleList[i], -90 - (self.angleList[i] - -90))
				launchable = (True, True)
			
			option = self.optionList[i*2]
			option.locator.targetPosition = target
			option.locator.speed.normalize()
			option.locator.speed *= speed
			option.circling.targetAngle = targetAngle[0]
			option.launchable = launchable[0]
			
			target.x = pos.x - (target.x - pos.x)
			option = self.optionList[i*2 + 1]
			option.locator.targetPosition = target
			option.locator.speed.normalize()
			option.locator.speed *= speed
			option.circling.targetAngle = targetAngle[1]
			option.launchable = launchable[1]
	
	@property
	def level(self):
		return self._level
	@level.setter
	def level(self, value):
		prev = self._level
		self._level = value
		
		if self._level < 1:
			self._level = 1
		elif self._level > self.maxLevel:
			self._level = self.maxLevel
		
		if prev != self._level:
			self.optionList = []
			for index in range(self._level * 2):
				pos = self.core.position
				option = self._createOption(index, pos)
				self.optionList.append(option)
	def _createOption(self, index, pos):
		return self.optionClass(self.core, pos, pos)
	@property
	def maxLevel(self):
		return min(len(self.relPosList), len(self.relPosAimingList), len(self.angleList))
	
	def update(self):
		self.onUpdate()
		self._updateOptionState()
		for option in self.optionList:
			option.update()
	def onUpdate(self):
		pass
	def draw(self):
		self.onDraw()
		for option in self.optionList:
			option.draw()
	def onDraw(self):
		pass
	
	def resetPos(self):
		for option in self.optionList:
			option.pos = self.core.position