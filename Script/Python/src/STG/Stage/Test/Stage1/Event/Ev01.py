'''
Created on 2010/11/22

@author: t
'''

import Std
import STG.Ctrl as Ctrl
from STG.Stage.BaseEvent import Base
from Util.Coroutine import Coroutine

from ..Enemy.Idiot01 import Idiot01

class Ev01(Base):
	def __init__(self, stage):
		super().__init__(stage)
		self.waitCoroutine = Coroutine(self.wait)
	
	def onUpdate(self):
		if self.waitCoroutine.alive:
			self.waitCoroutine.resume()
		else:
			self.end = True
	def onDraw(self):
		pass
	
	def wait(self):
		random = Ctrl.getRandom()
		
		waitCount = 60 * 10
		while waitCount > 0:
			if waitCount % 20 == 0:
				idiot01 = Idiot01(
					Std.Vector2DF(random.getFloat(0, 440), -32), 
					self.stage.resource, self.stageSetRef().scoreManager)
				Ctrl.Actor.registerEnemy(idiot01)
			
			waitCount -= 1
			yield