'''
Created on 2011/08/11

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Resource.Common as Resource

class BasicInfArea:
	def __init__(self, basicScoreManager = None):
		self.scoreManager = basicScoreManager
		
		self.drawParam = Std.Sprite.DrawParam()
		self.drawParam.texture = Resource.get("infAreaBack")
		self.drawParam.src = Std.RectF(0, 0, 200, 480)
		self.drawParam.dst = Std.RectF(
			Std.Consts.ScreenSize.x - Std.Consts.StgInfAreaSize.x, 
			0, 
			Std.Consts.StgInfAreaSize.x, 
			Std.Consts.StgInfAreaSize.y)
		self.drawParam.priority = Ctrl.DrawPriority.infAreaBack
		self.drawParam.shakable = False
	
	def update(self):
		pass
	def draw(self):
		Std.Sprite.draw(self.drawParam)
		
		drawRect = Std.RectF(
			Std.Consts.ScreenSize.x - Std.Consts.StgInfAreaSize.x, 
			0, 
			Std.Consts.StgInfAreaSize.x, 
			32)
		
		if not self.scoreManager is None:
			self.scoreManager.drawInfArea(drawRect)
			drawRect.y += 32
		
		basePos = Std.Vector2DF(drawRect.x, drawRect.y)
		Ctrl.Actor.myShip.drawInfArea(basePos)