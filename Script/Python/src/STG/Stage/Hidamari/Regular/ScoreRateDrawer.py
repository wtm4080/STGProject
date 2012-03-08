'''
Created on 2011/12/18

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs
from Util.Coroutine import Coroutine, createWait

class ScoreRateDrawer:
	INCREASE_RATE = 1 / 120
	ALPHA_DECREASE = 0.04
	MOVE_WAIT = 60
	MOVE_SPEED = 6
	MOVE_DIR = -160
	
	def __init__(self, resource):
		self.font = resource.font_ScoreRate
		self.fontAlpha = 1
		self.starTexture = resource.scoreRateStar
		self._rate = 0
		self.visibleRate = 0
		self.locator = Std.Locator.LinearF()
		self.task = None
		self.starList = []
		self.starCreationTask = None
		
		self.numStrDict = {
			"0": "０", "1": "１", "2": "２", "3": "３", "4": "４", 
			"5": "５", "6": "６", "7": "７", "8": "８", "9": "９"}
	
	@property
	def rate(self):
		return self._rate
	@rate.setter
	def rate(self, value):
		self._rate = value
	@property
	def position(self):
		return self.locator.position
	@position.setter
	def position(self, value):
		self.locator.position = value
	@property
	def finished(self):
		return not self.task is None and not self.task.alive
	
	def start(self, rate, pos):
		self.rate = rate
		self.position = pos
		self.task = Coroutine(self._task)
	
	def update(self):
		self.locator.update()
		for star in self.starList:
			star.update()
		
		if not self.task is None and self.task.alive:
			self.task.resume()
		if not self.starCreationTask is None and self.starCreationTask.alive:
			self.starCreationTask.resume()
	def _task(self):
		self.starCreationTask = Coroutine(self._starCreationTask)
		self.visibleRate = 0
		while True:
			self.visibleRate += self.rate * self.INCREASE_RATE
			if self.visibleRate >= self.rate:
				self.visibleRate = self.rate
				break
			yield
		
		wait = createWait(self.MOVE_WAIT)
		while wait() or self.starCreationTask.alive: yield
		
		self.locator.speed.setUnitVector(self.MOVE_DIR)
		self.locator.speed *= self.MOVE_SPEED
		alpha = 1.0
		while alpha > 0:
			alpha -= self.ALPHA_DECREASE
			
			self.fontAlpha = alpha
			for star in self.starList:
				star.alpha = alpha
			yield
	def _starCreationTask(self):
		self.starList = []
		size = (96, 56, 56)
		relPos = ((128 + 38, -24), (128 + 78, 12), (128 + 34, 36))
		class StarUnit:
			def __init__(self, locator, size, relPos, drawParam):
				self.locator = locator
				self.stdSize = size
				self.size = size * 6
				self.relPos = relPos
				self.appeared = False
				
				self.drawParam = drawParam
				self.drawParam.color.a = 0
				self.drawParam.rotDegree = Ctrl.getRandom().getFloat(-180, 180)
				
				self.taskList = []
				self.taskList.append(Coroutine(self._alphaTask))
				self.taskList.append(Coroutine(self._sizeTask))
				self.taskList.append(Coroutine(self._rotateTask))
				
			
			@property
			def alpha(self):
				return self.drawParam.color.a
			@alpha.setter
			def alpha(self, value):
				self.drawParam.color.a = value
			@property
			def position(self):
				return self.locator.position + self.relPos
			
			def _alphaTask(self):
				while self.alpha < 1:
					self.alpha += 0.1
					yield
				self.alpha = 1
			def _sizeTask(self):
				while self.size > self.stdSize * 0.6:
					self.size -= self.stdSize * 0.2
					yield
				
				self.appeared = True
				self.createParticle()
				yield
				
				while self.size < self.stdSize:
					self.size += self.stdSize * 0.1
					yield
				self.size = self.stdSize
			def _rotateTask(self):
				while not self.appeared:
					self.drawParam.rotDegree += 20
					yield
				while True:
					self.drawParam.rotDegree += 0.2
					yield
			
			def createParticle(self):
				num = 20
				size = Std.Vector2DF(self.size, self.size)
				speed = 2
				rotSpeed = 6
				
				drawParam = Std.Sprite.DrawParam(self.drawParam)
				drawParam.dst = self.position.makeRect(size, True)
				drawParam.priority = Ctrl.DrawPriority.scoreRate2
				drawParam.color.a = 1
				drawParam.rotDegree = Ctrl.getRandom().getFloat(-180, 180)
				
				param = Auxs.Particle.Param()
				param.drawParameter = drawParam
				param.setPosition(self.position)
				param.setSpeedRange(speed * 0.5, speed * 1.5)
				param.setZoomRateRange(0.8, 1.2)
				param.setZoomDecRateRange(0.015, 0.025)
				param.setRotSpeedRange(rotSpeed * 0.5, rotSpeed * 1.5)
				
				creator = Auxs.Particle.Creator(param)
				creator.create(num)
			
			def update(self):
				self.drawParam.dst = self.position.makeRect(
					Std.Vector2DF(self.size, self.size), True)
				for task in self.taskList:
					if task.alive:
						task.resume()
			def draw(self):
				Std.Sprite.draw(self.drawParam)
		
		for i in range(len(size)):
			drawParam = Std.Sprite.DrawParam()
			drawParam.texture = self.starTexture
			drawParam.src = Std.RectF(0, 0, 64, 64)
			drawParam.priority = Ctrl.DrawPriority.scoreRate3
			unit = StarUnit(
				self.locator, 
				size[i], 
				Std.Vector2DF(*relPos[i]), 
				drawParam)
			self.starList.insert(0, unit)
			
			wait = createWait(15)
			while wait(): yield
	
	def draw(self):
		rect = self.position.makeRect(32 + 64*4, 64, True)
		offset = Std.Point2DF()
		color = Std.ColorF(1, 1, 1, self.fontAlpha)
		rateStr = str(int(self.visibleRate))
		self.font.setPriority(Ctrl.DrawPriority.scoreRate)
		self.font.drawRight(rect, offset, color, "x" + self.convertNumStr(rateStr))
		
		for star in self.starList:
			star.draw()
	
	def convertNumStr(self, numStr):
		result = ""
		for char in numStr:
			result = result + self.numStrDict[char]
		return result