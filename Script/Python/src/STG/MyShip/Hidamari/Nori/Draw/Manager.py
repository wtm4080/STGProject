'''
Created on 2011/06/14

@author: t
'''

import Std
import STG.Ctrl as Ctrl

from ...Common.BarrierDrawer import BarrierDrawer
from .Body import Body
from .SpAttack import SpAttack

class Manager:
	def __init__(self, core):
		self.core = core
		self.barrier = BarrierDrawer(core)
		self.body = Body(core)
		self.spAttack = SpAttack(core)
	
	def update(self):
		self.barrier.update()
		self.body.update()
		self.spAttack.update()
	
	def draw(self):
		self.barrier.draw()
		self.body.draw()
		self.spAttack.draw()
	def drawInfArea(self, basePos):
		font = self.core.resource.font_Common24
		font.setPriority(Ctrl.DrawPriority.infAreaStr)
		font.shakable = False
		rect = Std.RectF(basePos.x, basePos.y, 
			Std.Consts.StgInfAreaSize.x, 32)
		offset = Std.Point2DF()
		color = Std.ColorF()
		
		def repeatStr(count):
			string = "★" * count
			font.drawLeft(rect, offset, color, string)
		
		font.drawLeft(rect, offset, color, "Player:")
		rect.y += 32
		if self.core.remainder > 0:
			repeatStr(self.core.remainder - 1)
		
		rect.y += 32
		font.drawLeft(rect, offset, color, "Power:")
		rect.y += 32
		repeatStr(self.core.power)
		
		rect.y += 32
		font.drawLeft(rect, offset, color, "SpAttack:")
		rect.y += 32
		repeatStr(self.core.spAttackNum)
	
	def spBegin(self, frameNum):
		self.spAttack.begin(frameNum)
	def spFinishing(self):
		self.spAttack.finishing()
	def spFinish(self):
		self.spAttack.finish()
	def spStop(self):
		self.spAttack.stop()