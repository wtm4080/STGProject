'''
Created on 2011/12/22

@author: t
'''

import Std
import STG.Ctrl as Ctrl
from STG.Stage.BaseEvent import Base
from Util.Coroutine import Coroutine, createWait

class ResultEvent(Base):
	MAX_FRAME_NUM = 60 * 10
	
	REMAINDER_SCORE = 3000
	SPATTACK_SCORE = 1000
	NOMISS_SCORE = 5000
	
	def __init__(self, stage):
		super().__init__(stage)
		self.hidamariFlag = self.stage.stageSetRef().hidamariFlag
		self.resource = self.stageSetRef().resource
		self.scoreManager = self.stageSetRef().scoreManager
		self.mainTask = Coroutine(self._mainTask)
		
		self.charBackDrawParam = None
		self.nazunaDrawParam = None
		self.noriDrawParam = None
		
		self.scoreBackDrawParam = None
		self.scoreMessageDraw = None
		self.scoreCalcFinished = False
	
	def onUpdate(self):
		if self.mainTask.alive:
			self.mainTask.resume()
		else:
			self.end = True
	def _mainTask(self):
		self.resource.bgm_ResultScene.play(0)
		
		wait = createWait(180)
		while wait(): yield
		
		myShip = Ctrl.Actor.myShip
		myShip.setMoveForbidFlag(True)
		
		frameCount = 0
		end = False
		subTaskList = []
		
		def myShipMoveTask():
			speed = 3
			targetPos = Std.Vector2DF(110, 400)
			distance = targetPos.getDistance(myShip.position)
			vector = Std.Vector2DF()
			vector.setUnitVector(myShip.position.getAngle(targetPos))
			vector *= speed
			
			wait = createWait(distance / speed)
			while wait():
				pos = myShip.position
				myShip.position = pos + vector
				yield
		subTaskList.append(Coroutine(myShipMoveTask))
		
		if self.hidamariFlag:
			posY = 50
			self.charBackDrawParam = Std.Sprite.DrawParam()
			self.charBackDrawParam.texture = self.resource.result_CharBack
			self.charBackDrawParam.src = Std.RectF(0, 0, 440, 64)
			self.charBackDrawParam.dst = Std.RectF(-440, posY, 440, 64)
			self.charBackDrawParam.priority = Ctrl.DrawPriority.resultB1
			self.charBackDrawParam.shakable = False
			def backTask():
				speed = 12
				
				while self.charBackDrawParam.dst.x < 0:
					self.charBackDrawParam.dst.x += speed
					yield
				self.charBackDrawParam.dst.x = 0
				
				while not end: yield
				
				wait = createWait(10)
				while wait(): yield
				while self.charBackDrawParam.dst.x < 440:
					self.charBackDrawParam.dst.x += speed
					yield
			subTaskList.append(Coroutine(backTask))
		
		nazunaTask = None
		noriTask = None
		if self.hidamariFlag:
			self.nazunaDrawParam = Std.Sprite.DrawParam()
			self.nazunaDrawParam.texture = self.resource.result_Nazuna
			self.nazunaDrawParam.src = Std.RectF(0, 0, 180, 64)
			self.nazunaDrawParam.dst = Std.RectF(-180, posY, 180, 64)
			self.nazunaDrawParam.priority = Ctrl.DrawPriority.result
			self.nazunaDrawParam.shakable = False
			
			self.noriDrawParam = Std.Sprite.DrawParam()
			self.noriDrawParam.texture = self.resource.result_Nori
			self.noriDrawParam.src = Std.RectF(0, 0, 176, 64)
			self.noriDrawParam.dst = Std.RectF(440, posY, 176, 64)
			self.noriDrawParam.priority = Ctrl.DrawPriority.result
			self.noriDrawParam.shakable = False
			
			def charMoveTask(_drawParam = None, left = True):
				drawParam = _drawParam
				speed = 10
				waitSpeed = 0.1
				if not left:
					speed *= -1
					waitSpeed *= -1
				yield
				
				wait = createWait(40)
				while wait():
					drawParam.dst.x += speed
					yield
				
				while not end:
					drawParam.dst.x += waitSpeed
					yield
				
				while drawParam.dst.x > -drawParam.dst.w and drawParam.dst.x < 440:
					drawParam.dst.x += speed
					yield
			nazunaTask = Coroutine(charMoveTask)
			nazunaTask.resume(self.nazunaDrawParam, True)
			subTaskList.append(nazunaTask)
			noriTask = Coroutine(charMoveTask)
			noriTask.resume(self.noriDrawParam, False)
			subTaskList.append(noriTask)
		
		def scoreTask():
			posY = 130
			
			self.scoreBackDrawParam = Std.Sprite.DrawParam()
			self.scoreBackDrawParam.dst = Std.RectF(0, posY, 440, 24 * 12)
			self.scoreBackDrawParam.priority = Ctrl.DrawPriority.resultB1
			self.scoreBackDrawParam.shakable = False
			self.scoreBackDrawParam.color = Std.ColorF(1, 1, 1, 0)
			
			wait = createWait(30)
			while wait(): yield
			
			backAlpha = 0.8
			while self.scoreBackDrawParam.color.a < backAlpha:
				self.scoreBackDrawParam.color.a += backAlpha / 30
				yield
			self.scoreBackDrawParam.color.a = backAlpha
			
			wait = createWait(30)
			while wait(): yield
			
			class IncreasingNumber:
				def __init__(self, value, increaseRate):
					self.value = value
					self.incRate = increaseRate
					self.currentValue = 0
				def update(self):
					if self.currentValue < self.value:
						self.currentValue += self.value * self.incRate
						if self.currentValue > self.value:
							self.currentValue = self.value
				def get(self):
					return int(self.currentValue)
				@property
				def finished(self):
					return self.currentValue >= self.value
				def finish(self):
					self.currentValue = self.value
			def display(remainder, spAttack = None, noMiss = None, 
					promptAlpha = None, alpha = 1):
				rate = int(self.scoreManager.rate)
				myShip = Ctrl.Actor.myShip
				remNum = myShip.remainder
				message = ("Remainder: \n" + 
					str(self.REMAINDER_SCORE) + "*" + 
					str(remNum) + " * " + 
					str(rate) + " = " + 
					str(remainder.get()) + "\n\n")
				if spAttack:
					spNum = myShip.spAttack
					message = (message + "SpAttack: \n" + 
						str(self.SPATTACK_SCORE) + "*" + 
						str(spNum) + " * " + 
						str(rate) + " = " + 
						str(spAttack.get()) + "\n\n")
				if noMiss:
					message = (message + "NoMissBonus: \n" + 
						str(self.NOMISS_SCORE) + " * " + 
						str(rate) + " = " + 
						str(noMiss.get()) + "\n\n")
				
				def draw():
					font = self.resource.font_Common24
					font.setPriority(Ctrl.DrawPriority.result)
					font.shakable = False
					rect = Std.RectF(12, posY + 12, 440 - 12, 24*12 - 12)
					offset = Std.Point2DF()
					color = Std.ColorF(1, 1, 1, alpha)
					font.drawLeft(rect, offset, color, message)
					
					if promptAlpha:
						rect = Std.RectF(rect.x, rect.y + rect.h - 36, rect.w, 24)
						color = Std.ColorF(1, 1, 1, promptAlpha * alpha)
						font.drawLeft(rect, offset, color, "Press Z Key...")
				self.scoreMessageDraw = draw
			
			self.scoreManager.addScore(self.REMAINDER_SCORE * myShip.remainder)
			rate = self.scoreManager.rate
			remainderScore = IncreasingNumber(
				self.REMAINDER_SCORE * myShip.remainder * rate, 1/30)
			self.resource.se_CalcScore.play()
			controller = Ctrl.getController()
			skip = False
			while not remainderScore.finished:
				if controller.isPush(Std.Input.KeyId.Z):
					remainderScore.finish()
					display(remainderScore)
					skip = True
					yield
					break
				else:
					display(remainderScore)
					remainderScore.update()
				yield
			else:
				display(remainderScore)
			
			if not skip:
				wait = createWait(30)
				while wait(): yield
			self.scoreManager.addScore(self.SPATTACK_SCORE * myShip.spAttack)
			spAttackScore = IncreasingNumber(
				self.SPATTACK_SCORE * myShip.spAttack * rate, 1/30)
			self.resource.se_CalcScore.play()
			skip = False
			while not spAttackScore.finished:
				if controller.isPush(Std.Input.KeyId.Z):
					spAttackScore.finish()
					display(remainderScore, spAttackScore)
					skip = True
					yield
					break
				else:
					display(remainderScore, spAttackScore)
					spAttackScore.update()
				yield
			else:
				display(remainderScore, spAttackScore)
			
			noMissBonus = None
			if self.stageSetRef().noMiss:
				if not skip:
					wait = createWait(30)
					while wait(): yield
				self.scoreManager.addScore(self.NOMISS_SCORE)
				noMissBonus = IncreasingNumber(self.NOMISS_SCORE * rate, 1/30)
				self.resource.se_Whump.play()
				skip = False
				while not noMissBonus.finished:
					if controller.isPush(Std.Input.KeyId.Z):
						noMissBonus.finish()
						display(remainderScore, spAttackScore, noMissBonus)
						skip = True
						yield
						break
					else:
						display(remainderScore, spAttackScore, noMissBonus)
						noMissBonus.update()
					yield
				else:
					display(remainderScore, spAttackScore, noMissBonus)
			
			wait = createWait(30)
			while wait(): yield
			self.scoreCalcFinished = True
			promptAlpha = 0
			while not end:
				while promptAlpha < 1:
					if end: break
					display(remainderScore, spAttackScore, noMissBonus, 
						promptAlpha = promptAlpha)
					promptAlpha += 1/30
					yield
				promptAlpha = 1
				while promptAlpha > 0:
					if end: break
					display(remainderScore, spAttackScore, noMissBonus, 
						promptAlpha = promptAlpha)
					promptAlpha -= 1/30
					yield
				promptAlpha = 0
			
			alpha = 1
			while alpha > 0:
				alpha -= 1 / 30
				self.scoreBackDrawParam.color.a = backAlpha * alpha
				display(remainderScore, spAttackScore, noMissBonus, 
					promptAlpha = promptAlpha, alpha = alpha)
				yield
		subTaskList.append(Coroutine(scoreTask))
		
		while frameCount < self.MAX_FRAME_NUM:
			controller = Ctrl.getController()
			if self.scoreCalcFinished and controller.isPush(Std.Input.KeyId.Z):
				self.resource.se_Select3.play()
				break
			
			for task in subTaskList:
					task.resume()
			subTaskList = [task for task in subTaskList if task.alive]
			frameCount += 1
			yield
		
		end = True
		while subTaskList:
			for task in subTaskList:
					task.resume()
			subTaskList = [task for task in subTaskList if task.alive]
			yield
		
		myShip.setMoveForbidFlag(False)
		myShip.setShotForbidFlag(False)
		myShip.setSpecialAttackForbidFlag(False)
		
		wait = createWait(90)
		while wait(): yield
		
		self.scoreManager.pause = False
	
	def onDraw(self):
		if self.charBackDrawParam:
			Std.Sprite.draw(self.charBackDrawParam)
		if self.nazunaDrawParam:
			Std.Sprite.draw(self.nazunaDrawParam)
		if self.noriDrawParam:
			Std.Sprite.draw(self.noriDrawParam)
		
		if self.scoreBackDrawParam:
			Std.Sprite.draw(self.scoreBackDrawParam)
		if self.scoreMessageDraw:
			self.scoreMessageDraw()