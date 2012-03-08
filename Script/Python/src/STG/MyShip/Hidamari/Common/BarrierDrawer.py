'''
Created on 2011/11/28

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Resource.Common as CommonResource

class BarrierDrawer():
	def __init__(self, core, size = Std.Vector2DF(86, 86)):
		self.core = core
		self.size = size
		
		self.drawParam = Std.Sprite.DrawParam()
		self.drawParam.texture = CommonResource.get("bulletBlue")
		self.drawParam.src = Std.RectF(0, 0, 64, 64)
		self.drawParam.dst = core.locator.position.makeRect(size, True)
		self.drawParam.priority = Ctrl.DrawPriority.myBarrier
		self.drawParam.alphaBlend = Std.Sprite.AlphaBlend.Add
	
	def update(self):
		self.drawParam.dst = self.core.locator.position.makeRect(self.size, True)
		if self.core.barrierCount > 20:
			self.drawParam.color = Std.ColorF()
		else:
			self.drawParam.color = Std.ColorF(1, 1, 1, self.core.barrierCount * 1/20)
	
	def draw(self):
		if self.core.barriered:
			Std.Sprite.draw(self.drawParam)