'''
Created on 2010/10/23

@author: t
'''

import Std
import STG.Ctrl as Ctrl

class Base:
	INIT_VALID_AREA_MARGIN = 100
	INIT_VALID_FRAME_NUM = 60 * 10
	
	def __init__(self, validRect):
		self.valid = True
		self.setValidAreaMargin(self.INIT_VALID_AREA_MARGIN)
		self.validRect = validRect
		self.validFrameNum = self.INIT_VALID_FRAME_NUM
		self.frameCount = 0
		self.frameCounting = True
		self._objectId = Ctrl.genObjectId()
	
	@property
	def objectId(self):
		return self._objectId
	
	def update(self):
		self.validRect.center = self.position
		
		if not self.validRect.isHit(self.validArea):
			self.valid = False
			self.onOutOfValidArea()
		
		if self.frameCount > self.validFrameNum:
			self.erase()
		
		self.updateMiddle()
		self.onUpdate()
		
		if self.frameCount <= self.validFrameNum and self.frameCounting:
			self.frameCount += 1
	def onOutOfValidArea(self):
		pass
	
	def draw(self):
		self.drawMiddle()
		self.onDraw()
	
	def erase(self):
		self.valid = False
		self.onErase()
	
	def setValidAreaMargin(self, margin):
		self.validArea = Std.Hit.RectI(
			-margin, -margin, 
			Std.Consts.ScreenSize.x - Std.Consts.StgInfAreaSize.x + margin*2, 
			Std.Consts.ScreenSize.y + margin*2, False)
	
	
	@property
	def position(self):
		raise Exception("BaseActor.Base.position is not implemented.")
	def applyExternalForce(self, vec):
		raise Exception("BaseActor.Base.applyExternalForce is not implemented.")
	def updateMiddle(self):
		pass
	def drawMiddle(self):
		pass
	def onUpdate(self):
		raise Exception("BaseActor.Base.onUpdate is not implemented.")
	def onDraw(self):
		raise Exception("BaseActor.Base.onDraw is not implemented.")
	def onErase(self):
		raise Exception("BaseActor.Base.onErase is not implemented.")