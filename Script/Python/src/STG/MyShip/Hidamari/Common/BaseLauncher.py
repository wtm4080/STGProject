'''
Created on 2011/12/05

@author: t
'''

import Std
from Util.Coroutine import Coroutine

class BaseLauncher:
	def __init__(self):
		self._fireTask = None
		self._fireDrawParamList = None
	
	@property
	def position(self):
		return None
	@property
	def angle(self):
		return None
	
	def update(self):
		if not self._fireTask is None and self._fireTask.alive:
			self._fireTask.resume()
		else:
			self._fireTask = None
			self._fireDrawParamList = None
		
		self.onUpdate()
	def onUpdate(self):
		pass
	
	def draw(self):
		if not self._fireDrawParamList is None:
			for drawParam in self._fireDrawParamList:
				Std.Sprite.draw(drawParam)
		
		self.onDraw()
	def onDraw(self):
		pass
	
	def calcRotatedLine(self, offset, num, interval, rotAngle, 
					callback, angleCorrection = 0):
		if num <= 0:
			return
		posList = []
		_offset = Std.Vector2DF(offset)
		_offset.rotate(rotAngle)
		basePos = _offset + self.position
		
		odd = False
		if num % 2 != 0:
			posList.append(basePos)
			num = num - 1
			odd = True
		for i in range(num // 2):
			itv = Std.Vector2DF()
			itv.setUnitVector(rotAngle - 90 - angleCorrection)
			if odd:
				itv *= interval * (i + 1)
			else:
				itv *= interval / 2 + interval * i
			posList.append(basePos + itv)
			
			itv.setUnitVector(rotAngle + 90 + angleCorrection)
			if odd:
				itv *= interval * (i + 1)
			else:
				itv *= interval / 2 + interval * i
			posList.append(basePos + itv)
		
		for pos in posList:
			callback(pos)
	
	def createFire(self, offset, size, angle, drawParam, 
				alphaDec = 0.5, num = 1, interval = 20, angleCorrection = 0):
		self._fireDrawParamList = []
		def createFireDrawParams(pos):
			dParam = Std.Sprite.DrawParam(drawParam)
			dParam.dst = pos.makeRect(size, True)
			self._fireDrawParamList.append(dParam)
		self.calcRotatedLine(offset, num, interval, angle, 
			createFireDrawParams)
		
		def fireTask():
			def updateFireDrawParams():
				posList = []
				def appendPos(pos):
					posList.append(pos)
				self.calcRotatedLine(offset, num, interval, angle, appendPos)
				
				for i in range(len(self._fireDrawParamList)):
					self._fireDrawParamList[i].dst = posList[i].makeRect(size, True)
					self._fireDrawParamList[i].rotDegree = self.angle + angleCorrection
				
				self._fireDrawParamList = [
					drawParam for drawParam in self._fireDrawParamList 
					if drawParam.color.a > 0]
			
			updateFireDrawParams()
			yield
			
			while True:
				for drawParam in self._fireDrawParamList:
					drawParam.color.a -= alphaDec
				
				updateFireDrawParams()
				
				if not self._fireDrawParamList:
					break
				
				yield
		
		self._fireTask = Coroutine(fireTask)