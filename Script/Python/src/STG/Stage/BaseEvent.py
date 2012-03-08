'''
Created on 2010/10/25

@author: t
'''

class Base:
	def __init__(self, stage):
		self.stage = stage
		self.stageSetRef = stage.stageSetRef
		self.end = False
	
	def update(self):
		self.onUpdate()
	
	def draw(self):
		self.onDraw()
	
	
	def onUpdate(self):
		raise Exception("BaseEvent.Base.onUpdate is not implemented.")
	def onDraw(self):
		raise Exception("BaseEvent.Base.onDraw is not implemented.")