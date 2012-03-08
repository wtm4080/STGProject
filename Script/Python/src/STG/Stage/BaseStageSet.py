'''
Created on 2010/10/23

@author: t
'''

import weakref
import STG.Ctrl as Ctrl

class Base:
	def __init__(self, infArea):
		self._currentStage = None
		self.finish = False
		self.infArea = infArea
	
	def update(self):
		self.onUpdate()
		
		if not self.finish:
			if not self._currentStage is None:
				self._currentStage.update()
			
			if self._currentStage is None:
				self._currentStage = Ctrl.getNextStage()
				self._currentStage._internalPyObject.stageSetRef = weakref.ref(self)
			elif self._currentStage.end:
				nextStage = Ctrl.getNextStage()
				if nextStage is None:
					self.finish = True
					self.onFinish()
				else:
					nextStage._internalPyObject.stageSetRef = weakref.ref(self)
					self._currentStage = nextStage
		
		self.infArea.update()
	
	def draw(self):
		self.onDraw()
		
		if not self._currentStage is None:
			self._currentStage.draw()
		
		self.infArea.draw()
	
	@property
	def end(self):
		return self.finish
	
	
	def onUpdate(self):
		raise Exception("BaseStageSet.Base.onUpdate is not implemented.")
	def onDraw(self):
		raise Exception("BaseStageSet.Base.onDraw is not implemented.")
	def onContinue(self):
		raise Exception("BaseStageSet.Base.onContinue is not implemented.")
	def onMyShipDestruction(self):
		raise Exception("BaseStageSet.Base.onMyShipDestruction is not implemented.")
	def onMyShipRevival(self):
		raise Exception("BaseStageSet.Base.onMyShipRevival is not implemented.")
	def onFinish(self):
		raise Exception("BaseStageSet.Base.onFinish is not implemented.")