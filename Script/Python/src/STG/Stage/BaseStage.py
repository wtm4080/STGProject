'''
Created on 2010/10/25

@author: t
'''

class Base:
	def __init__(self):
		self.stageSetRef = None
		self.eventList = []
		self._initialized = False
	
	def update(self):
		if not self._initialized:
			self.onInitialize()
			self._initialized = True
		
		if len(self.eventList) > 0:
			self.eventList[0].update()
		
		self.onUpdate()
		
		if(len(self.eventList) > 0 and 
				self.eventList[0].end):
			self.eventList.pop(0)
	
	def draw(self):
		if self._initialized:
			self.onDraw()
			
			if len(self.eventList) > 0:
				self.eventList[0].draw()
	
	@property
	def end(self):
		return len(self.eventList) == 0
	
	
	def onUpdate(self):
		raise Exception("BaseStage.Base.onUpdate is not implemented.")
	def onDraw(self):
		raise Exception("BaseStage.Base.onDraw is not implemented.")
	def onInitialize(self):
		pass