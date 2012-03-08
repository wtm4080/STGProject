'''
Created on 2010/11/22

@author: t
'''

from STG.Stage.BaseStageSet import Base
from STG.Stage.BasicInfArea import BasicInfArea
from STG.Stage.BasicScoreManager import BasicScoreManager

class Core(Base):
	def __init__(self, stageSetId):
		self.scoreManager = BasicScoreManager(stageSetId)
		self.scoreManager.read()
		super().__init__(BasicInfArea(self.scoreManager))
	
	def onUpdate(self):
		self.scoreManager.update()
	def onDraw(self):
		pass
	
	def onContinue(self):
		self.scoreManager.reset()
	def onMyShipDestruction(self):
		pass
	def onMyShipRevival(self):
		self.scoreManager.addRate(-(self.scoreManager.rate / 2))
	def onFinish(self):
		self.scoreManager.write()