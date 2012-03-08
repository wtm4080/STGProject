'''
Created on 2011/03/04

@author: t
'''

import Game


Animation = Game.STGAnimation
FadeOut = Game.STGFadeOut
EnemyHPGauge = Game.STGEnemyHPGauge
class Bullet:
	Linear = Game.STGBulletLinear
	Rotate = Game.STGBulletRotate
	
	MLActor = Game.STGBulletMLActor
	MLParam = Game.STGBulletMLCreateParam
class Item:
	Extend = Game.STGItemExtend
	PowerUp = Game.STGItemPowerUp
	SpAttack = Game.STGItemSpAttack
class Particle:
	Actor = Game.STGParticle
	Creator = Game.STGParticleCreator
	Param = Game.STGParticleParameter
class MyShot:
	Linear = Game.STGMyShotLinear


_auxs = Game.STGAuxs()

def createFadeOut(*args):
	return _auxs.createFadeOut(*args)
def createParticle(*args):
	_auxs.createParticle(*args)
def createExplosion(*args):
	return _auxs.createExplosion(*args)
def createExplosion2(*args):
	return _auxs.createExplosion2(*args)
def createSmoke(pos, size, frameItv, priority, alpha):
	return _auxs.createSmoke(pos, size, frameItv, priority, alpha)
def createBulletRedDrawParam(pos, size):
	return _auxs.getBulletRedDrawParam(pos, size)
def createBulletGreenDrawParam(pos, size):
	return _auxs.getBulletGreenDrawParam(pos, size)
def createBulletBlueDrawParam(pos, size):
	return _auxs.getBulletBlueDrawParam(pos, size)
def createBulletWhiteDrawParam(pos, size):
	return _auxs.getBulletWhiteDrawParam(pos, size)

def applyExRadialForceToMyShip(*args):
	return _auxs.applyExRadialForceToMyShip(*args)

def eraseActors():
	return _auxs.eraseActors()
def applyExForceToActors(*args):
	return _auxs.applyExForceToActors(*args)
def applyExRadialForceToActors(*args):
	return _auxs.applyExRadialForceToActors(*args)

def eraseBullets(*args):
	return _auxs.eraseBullets(*args)
def applyExForceToBullets(*args):
	return _auxs.applyExForceToBullets(*args)
def applyExRadialForceToBullets(*args):
	return _auxs.applyExRadialForceToBullets(*args)
def destructBullets(*args):
	return _auxs.destructBullets(*args)
def applyDamageToBullets(*args):
	return _auxs.applyDamageToBullets(*args)

def eraseEnemies(*args):
	return _auxs.eraseEnemies(*args)
def applyExForceToEnemies(*args):
	return _auxs.applyExForceToEnemies(*args)
def applyExRadialForceToEnemies(*args):
	return _auxs.applyExRadialForceToEnemies(*args)
def destructEnemies(*args):
	return _auxs.destructEnemies(*args)
def applyDamageToEnemies(*args):
	return _auxs.applyDamageToEnemies(*args)
def applyDamageAndGetEnemy(hitRect, damage):
	return _auxs.applyDamageAndGetEnemy(hitRect, damage)

def eraseItems():
	return _auxs.eraseItems()
def applyExForceToItems(*args):
	return _auxs.applyExForceToItems(*args)
def applyExRadialForceToItems(*args):
	return _auxs.applyExRadialForceToItems(*args)

def eraseMyShots(*args):
	return _auxs.eraseMyShots(*args)
def applyExForceToMyShots(*args):
	return _auxs.applyExForceToMyShots(*args)
def applyExRadialForceToMyShots(*args):
	return _auxs.applyExRadialForceToMyShots(*args)
def destructMyShots(*args):
	return _auxs.destructMyShots(*args)
def applyDamageToMyShots(*args):
	return _auxs.applyDamageToMyShots(*args)
def affectMyShotsByPA(hit, force, damage, linearAttenuation, quadraticAttenuation, callback):
	return _auxs.affectMyShotsByPA(hit, force, damage, linearAttenuation, quadraticAttenuation, callback)
def getMyShotsForcibleDamageForPA(hit):
	return _auxs.getMyShotsForcibleDamageForPA(hit)