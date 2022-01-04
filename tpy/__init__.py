def hello():
  return "Hi"

class Number:
  def __init__(self, n: int = 1): self.n = n
  def __add__(self, n): return self.__class__(self.n + int(n))
  def __sub__(self, n): return self.__class__(self.n - int(n))
  def __mul__(self, n): return self.__class__(self.n * int(n))
  def __truediv__(self, n): return self.__class__(self.n / int(n))
  def add(self, n: int = 1): return self + n
  def sub(self, n: int = 1): return self - n
  def mul(self, n: int = 1): return self * n
  def div(self, n: int = 1): return self / n
  def __repr__(self): return str(self.n)
  def __str__(self): return repr(self)
  def __int__(self): return self.n
