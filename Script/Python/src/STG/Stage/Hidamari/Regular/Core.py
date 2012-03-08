'''
Created on 2011/01/07

@author: t
'''

from STG.Stage.BaseStageSet import Base

from .Resource import Resource
from .Background import Background
from .InfArea import InfArea
from .ScoreManager import ScoreManager
from .ScoreRateDrawer import ScoreRateDrawer

hidamariFlag = None

class Core(Base):
	def __init__(self, stageSetId):
		self.resource = Resource()
		self.scoreManager = ScoreManager(stageSetId, self.resource)
		self.scoreManager.read()
		super().__init__(InfArea(self.scoreManager, self.resource))
		
		self.background = Background(self)
		self.scrollSpeed = 0.15
		
		self.scoreRateDrawerList = []
		
		if hidamariFlag:
			self.hidamariFlag = True
		else:
			self.hidamariFlag = False
		
		self.noMiss = True
	
	def onUpdate(self):
		self.scoreManager.update()
		self.background.update()
		
		for drawer in self.scoreRateDrawerList:
			drawer.update()
		self.scoreRateDrawerList = [
			drawer for drawer in self.scoreRateDrawerList if not drawer.finished]
	def onDraw(self):
		self.background.draw()
		
		for drawer in self.scoreRateDrawerList:
			drawer.draw()
	
	def onContinue(self):
		self.scoreManager.reset()
	def onMyShipDestruction(self):
		self.noMiss = False
	def onMyShipRevival(self):
		self.scoreManager.addRate(-(self.scoreManager.rate / 2))
	def onFinish(self):
		self.scoreManager.write()
		global hidamariFlag
		hidamariFlag = None
	
	def createScoreRateDrawer(self, pos):
		drawer = ScoreRateDrawer(self.resource)
		drawer.start(self.scoreManager.rate, pos)
		self.scoreRateDrawerList.append(drawer)