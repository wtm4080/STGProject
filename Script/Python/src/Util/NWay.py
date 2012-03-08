'''
Created on 2011/02/14

@author: t
'''

def getAngleList(angle, interval, num):
	angleList = []
	numCount = num
	leftAngle = angle
	rightAngle = angle
	
	if num % 2 == 0:
		leftAngle -= interval / 2
		rightAngle += interval / 2
	else:
		angleList.append(angle)
		numCount -= 1
		
		leftAngle -= interval
		rightAngle += interval
	
	while numCount > 0:
		angleList.append(leftAngle)
		angleList.append(rightAngle)
		
		leftAngle -= interval
		rightAngle += interval
		
		numCount -= 2
	
	return angleList

def getCircleAngleList(angle, num):
	if num > 0:
		return getAngleList(angle, 360 / num, num)
	else:
		return []

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs

def launchLinear(pos, baseAngle, interval, num, hitRadius, drawParam, 
				speed = 4, accel = 0):
	angleList = getAngleList(baseAngle, interval, num)
	for angle in angleList:
		locator = Std.Locator.LinearF(pos)
		locator.speed.setUnitVector(angle)
		locator.speed *= speed
		locator.accel.setUnitVector(angle)
		locator.accel *= accel
		
		drawParam.rotDegree = angle
		
		bullet = Auxs.Bullet.Linear(
			locator, hitRadius, drawParam)
		
		Ctrl.Actor.registerBullet(bullet)

def launchLinearCircle(pos, baseAngle, num, hitRadius, drawParam, 
				speed = 4, accel = 0):
	if num > 0:
		launchLinear(pos, baseAngle, 360 / num, num, 
					hitRadius, drawParam, speed, accel)