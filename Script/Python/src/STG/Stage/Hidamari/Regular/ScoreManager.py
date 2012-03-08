'''
Created on 2011/12/19

@author: t
'''

import Std
import STG.Ctrl as Ctrl

from STG.Stage.BasicScoreManager import BasicScoreManager

class ScoreManager(BasicScoreManager):
	def __init__(self, stageSetId, resource):
		super().__init__(stageSetId)
		self.resource = resource
	
	def drawInfArea(self, drawRect):
		font = self.resource.font_Common24
		font.setPriority(Ctrl.DrawPriority.infAreaStr)
		font.shakable = False
		offset = Std.Point2DF()
		color = Std.ColorF()
		
		font.drawLeft(drawRect, offset, color, "HighScore:")
		drawRect.y += 32
		font.drawRight(drawRect, offset, color, str(self.highScore))
		
		drawRect.y += 32
		font.drawLeft(drawRect, offset, color, "Score:")
		drawRect.y += 32
		font.drawRight(drawRect, offset, color, str(self.score))
		
		font = self.resource.font_Common16
		font.setPriority(Ctrl.DrawPriority.infAreaStr)
		font.shakable = False
		drawRect.y += 24
		rateStr = "Rate: %.2f" % self.rate
		font.drawRight(drawRect, offset, color, rateStr)