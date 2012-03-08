'''
Created on 2011/12/19

@author: t
'''

import Std
import STG.Ctrl as Ctrl

class InfArea:
	def __init__(self, scoreManager, resource):
		self.scoreManager = scoreManager
		
		self.drawParam = Std.Sprite.DrawParam()
		self.drawParam.texture = resource.infArea
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
		
		self.scoreManager.drawInfArea(drawRect)
		drawRect.y += 32
		
		basePos = Std.Vector2DF(drawRect.x, drawRect.y)
		Ctrl.Actor.myShip.drawInfArea(basePos)