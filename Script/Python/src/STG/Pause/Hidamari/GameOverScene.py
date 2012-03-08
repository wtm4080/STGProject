'''
Created on 2011/12/23

@author: t
'''

import Std
from Util.Coroutine import Coroutine, createWait
from Util.Misc import Enum

drawPriority = Enum(
	"back", 
	"fadeEffect", 
	)

class GameOverScene:
	def __init__(self):
		self.drawParam = Std.Sprite.DrawParam()
		
		self.blackRect = Std.Sprite.DrawParam()
		self.blackRect.dst = Std.RectF(0, 0, 640, 480)
		self.blackRect.priority = drawPriority.fadeEffect
		self.blackRect.color = Std.ColorF(0, 0, 0, 1)
		
		def task():
			self.drawParam.texture = Std.Sprite.loadTexture("Hidamari/Regular/GameOver.dds", False)
			self.drawParam.src = Std.RectF(0, 0, 640, 480)
			self.drawParam.dst = self.drawParam.src
			self.drawParam.priority = drawPriority.back
			
			bgm = Std.Sound.loadStream("Hidamari/Regular/GameOver.ogg")
			bgm.play()
			
			while self.blackRect.color.a > 0:
				self.blackRect.color.a -= 1 / 60
				yield
			self.blackRect.color.a = 0
			
			wait = createWait(60 * 4)
			while wait():
				if Std.Input.getController().isPush(Std.Input.KeyId.Z):
					break
				yield
			
			while self.blackRect.color.a < 1:
				self.blackRect.color.a += 1 / 60
				yield
			self.blackRect.color.a = 1
		self.task = Coroutine(task)
	
	def update(self):
		if self.task.alive:
			self.task.resume()
		else:
			Std.Scene.changeToSTGTitle()
		
		Std.Sprite.draw(self.drawParam)
		Std.Sprite.draw(self.blackRect)