'''
Created on 2011/09/10

@author: t
'''

import os
import pickle

import Std
import STG.Ctrl as Ctrl
import STG.Resource.Common as Resource

class BasicScoreManager:
	DEFAULT_DATAFILE_PATH = "Score/Basic.dat"
	DEC_RATE_WAIT = 90
	DEC_RATE_AMOUNT = 0.1
	
	def __init__(self, stageSetId):
		self.data = {}
		self.stageSetId = stageSetId
		self._score = 0
		self._rate = 1.0
		self.decRateWaitCount = self.DEC_RATE_WAIT
		self._pause = False
	
	def read(self, path = DEFAULT_DATAFILE_PATH):
		try:
			with open(path, "rb") as file:
				self.data = pickle.load(file)
		except IOError:
			pass
	def write(self, path = DEFAULT_DATAFILE_PATH):
		dirPath, _ = os.path.split(path)
		os.makedirs(dirPath, exist_ok = True)
		with open(path, "wb") as file:
			pickle.dump(self.data, file)
	
	@property
	def score(self):
		return self._score
	@property
	def highScore(self):
		if not self.stageSetId in self.data:
			self.data[self.stageSetId] = 0
		return self.data[self.stageSetId]
	@property
	def rate(self):
		return self._rate
	@property
	def pause(self):
		return self._pause
	@pause.setter
	def pause(self, value):
		self._pause = value
	
	def addScore(self, score, applyRate = True):
		if applyRate:
			self._score += int(score * self.rate)
		else:
			self._score += int(score)
		
		if self.score > self.highScore:
			self.data[self.stageSetId] = self.score
	def addRate(self, rate, resetDecWaitCount = True):
		self._rate += rate
		if self.rate < 0:
			self._rate = 0
		if resetDecWaitCount:
			self.decRateWaitCount = self.DEC_RATE_WAIT
	def reset(self):
		self._score = 0
		self._rate = 1.0
		self.decRateWaitCount = self.DEC_RATE_WAIT
		self.pause = False
	
	def update(self):
		if not self.pause:
			if self.decRateWaitCount > 0:
				self.decRateWaitCount -= 1
			else:
				self.addRate(-self.DEC_RATE_AMOUNT, False)
	def drawInfArea(self, drawRect):
		font = Resource.getFont(
			"font32", Ctrl.DrawPriority.infAreaStr, False, 24)
		offset = Std.Point2DF()
		color = Std.ColorF()
		
		font.drawLeft(drawRect, offset, color, "HighScore:")
		drawRect.y += 32
		font.drawRight(drawRect, offset, color, str(self.highScore))
		
		drawRect.y += 32
		font.drawLeft(drawRect, offset, color, "Score:")
		drawRect.y += 32
		font.drawRight(drawRect, offset, color, str(self.score))
		
		font = Resource.getFont(
			"font16", Ctrl.DrawPriority.infAreaStr, False, 16)
		drawRect.y += 24
		rateStr = "Rate: %.2f" % self.rate
		font.drawRight(drawRect, offset, color, rateStr)