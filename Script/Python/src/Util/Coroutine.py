'''
Created on 2010/10/11

@author: tanakahisateru
@see: http://d.hatena.ne.jp/tanakahisateru/20081215/1229279624
'''

class Coroutine:
	def __init__(self, func):
		self._gen = func
		self._itr = None
		self.response = None
		self.alive = True

	def resume(self, *args):
		if not self.alive:
			raise Exception("cannot resume dead coroutine")
		try:
			if self._itr is None:
				self._itr = self._gen(*args)
				self.response = self._itr.__next__()
			else:
				self.response = self._itr.send(args)
			return self.response
		except StopIteration:
			self.alive = False
			self.response = None

class _Wait:
	def __init__(self, frameNum):
		self.frameNum = frameNum
		self.wait = Coroutine(self._wait)
	
	def _wait(self):
		while self.frameNum >= 1:
			self.frameNum -= 1
			yield
	
	def update(self):
		if not self.wait.alive:
			return False
		
		self.wait.resume()
		
		if self.wait.alive:
			return True
		else:
			return False

def createWait(frameNum):
	wait = _Wait(frameNum)
	return wait.update

if __name__ == "__main__":
	# coroutine
	def zig_zag(msg):
		for i in range(4):
			print("(%s to co)" % msg, end="")
			print("zig", end="")
			msg = yield i
			
			print("(%s to co)" % msg, end="")
			print("zag", end="")
			msg = yield i
	
	# user
	co = Coroutine(zig_zag)
	i = 0
	while(co.alive):
		print("(%s from co)" % co.resume(i))
		i += 1
	
	print("\nコルーチンネスト")
	def main_flow():
		print("main start")
		yield
		
		# This way is lessor than Lua
		co = Coroutine(sub_flow)
		while(co.alive): yield co.resume()
		
		print("main end")
	
	def sub_flow():
		print("sub start")
		yield
		for i in range(10):
			print("sub %d" % i)
			yield
		print("sub end")
	
	# execute step by step with interval
	import time
	co = Coroutine(main_flow)
	while(co.alive):
		co.resume()
		time.sleep(0.5)