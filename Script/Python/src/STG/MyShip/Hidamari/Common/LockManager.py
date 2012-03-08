'''
Created on 2011/12/05

@author: t
'''

import Std
import STG.Ctrl as Ctrl
from Util.Sprite.Animation import createSequenceAnimation
from Util.Sprite.Animation import updateDst

class LockManager:
	LOCK_BEGIN_ANIMATION_SIZE = Std.Vector2DF(192, 192)
	LOCK_MARKER_SIZE = Std.Vector2DF(64, 64)
	PA_GAUGE_SIZE = Std.Vector2DF(LOCK_MARKER_SIZE.x, LOCK_MARKER_SIZE.y/20)
	
	def __init__(self, core, lockThresHold, paralellLoad):
		self.core = core
		self.lockThresHold = lockThresHold
		self.paralellLoad = paralellLoad
		self.lockingList = []
		self.lockedList = []
		self.lockBeginAnimationList = []
		self.lockMarkerAnimationDict = {}
		self.se_Lock = core.resource.se_Lock
	
	def addLock(self, enemy, damage):
		optionNum = len(self.core.optionManager.optionList)
		if len(self.lockedList) < optionNum:
			index = 0
			while index < len(self.lockingList):
				en, dam = self.lockingList[index]
				
				if en.objectId == enemy.objectId:
					dam += damage * (self.paralellLoad ** len(self.lockedList))
					
					if dam >= self.lockThresHold:
						self.lockedList.append(en)
						
						if len(self.lockedList) == optionNum:
							self.lockingList = []
						else:
							del self.lockingList[index]
						
						drawParam = Std.Sprite.DrawParam()
						drawParam.src = Std.RectF(0, 0, 64, 64)
						drawParam.dst = en.position.makeRect(
							self.LOCK_BEGIN_ANIMATION_SIZE, True)
						drawParam.priority = Ctrl.DrawPriority.lockMarker2
						lockBeginAnimation = createSequenceAnimation(
							self.core.resource.lockBeginTexList, drawParam)
						lockBeginAnimation.play()
						self.lockBeginAnimationList.append((en, lockBeginAnimation))
						
						drawParam = Std.Sprite.DrawParam(drawParam)
						drawParam.dst = en.position.makeRect(
							self.LOCK_MARKER_SIZE, True)
						drawParam.priority = Ctrl.DrawPriority.lockMarker
						lockMarkerAnimation = createSequenceAnimation(
							self.core.resource.lockMarkerTexList, drawParam)
						lockMarkerAnimation.play()
						self.lockMarkerAnimationDict[en.objectId] = (en, lockMarkerAnimation)
						
						self.se_Lock.play()
					else:
						self.lockingList[index][1] = dam
					break
				index += 1
			else:
				if len(self.lockingList) < optionNum:
					self.lockingList.append([enemy, damage])
	
	def adjust(self, lockNum = None):
		if not lockNum is None:
			num = min(lockNum, len(self.core.optionManager.optionList))
		else:
			num = len(self.core.optionManager.optionList)
		if num > 0:
			if num < len(self.lockingList):
				self.lockingList = self.lockingList[:num]
			if num < len(self.lockedList):
				self.lockedList = self.lockedList[:num]
		else:
			self.lockingList = []
			self.lockedList = []
	def reset(self):
		self.lockingList = []
		self.lockedList = []
		
		self.lockBeginAnimationList = []
		self.lockMarkerAnimationDict = {}
	
	def getLockedEnemy(self, index):
		if index < len(self.lockedList):
			return self.lockedList[index]
		else:
			return None
	
	def update(self):
		self.lockingList = [[en, dam] for en, dam in self.lockingList if en.valid]
		self.lockedList = [en for en in self.lockedList if en.valid]
		
		self.lockBeginAnimationList = [(en, an) for en, an in self.lockBeginAnimationList if an.playing]
		for en, an in self.lockBeginAnimationList:
			an.update()
			updateDst(an, en.position, self.LOCK_BEGIN_ANIMATION_SIZE)
		
		invalidEnemyIdList = []
		for en, an in self.lockMarkerAnimationDict.values():
			if not en.valid:
				invalidEnemyIdList.append(en.objectId)
			else:
				if not an.playing:
					an.play()
				an.update()
				updateDst(an, en.position, self.LOCK_MARKER_SIZE)
		for enemyId in invalidEnemyIdList:
			self.lockMarkerAnimationDict.pop(enemyId)
		
		if not self.core.slow:
			self.reset()
	def draw(self):
		for _, animation in self.lockBeginAnimationList:
			animation.draw()
		for enemy, animation in self.lockMarkerAnimationDict.values():
			if enemy.maxPAAmount > 0:
				dst = Std.RectF(animation.frameHolder.drawParameter.dst)
				dst.y -= self.PA_GAUGE_SIZE.y
				dst.w = self.PA_GAUGE_SIZE.x * enemy.paAmount/enemy.maxPAAmount
				dst.h = self.PA_GAUGE_SIZE.y
				paGaugeDrawParam = Std.Sprite.DrawParam()
				paGaugeDrawParam.dst = dst
				paGaugeDrawParam.priority = Ctrl.DrawPriority.lockMarker
				if enemy.paGenerated:
					paGaugeDrawParam.color = Std.ColorF(1, 1, 1, 0.8)
				else:
					paGaugeDrawParam.color = Std.ColorF(1, 0, 0, 0.8)
				Std.Sprite.draw(paGaugeDrawParam)
			
			animation.draw()