'''
Created on 2011/01/22

@author: t
'''

class Face:
	def __init__(self, core):
		self.core = core
		self.waitCount = 0
	
	def update(self):
		if self.waitCount == 0:
			if self.core.hp > self.core.MAX_HP * 2/3:
				self.core.drawing.faceNumber = 0
			elif self.core.hp > self.core.MAX_HP * 1/3:
				self.core.drawing.faceNumber = 3
			elif self.core.hp > 0:
				self.core.drawing.faceNumber = 5
			else:
				self.core.drawing.faceNumber = 1
		else:
			self.waitCount -= 1
	
	def strain(self):
		self.core.drawing.faceNumber = 4
		self.waitCount = 40
	def destruction(self):
		self.core.drawing.faceNumber = 2
		self.waitCount = 120