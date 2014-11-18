Sprite={jvvv=6}
function Sprite.func(self,num)
  self.jvvv=self.jvvv+num
end



a=Sprite
a.func(a,3)
print(a.jvvv)
print(Sprite.jvvv)
-------------------------------------------
x=nil
x={3,4,5,6}
y=x
print(x)
print(type(x))
print(type(y))
print(type(nil))
---------------------------------------------
function ggg()
return 1,2
end

m = ggg()
n = {}
n = ggg()
print(m)
print(n)
gg={x=5,p=3}

h=gg
gg={8,0}
for k,v in pairs(h) do
  print(k,v)
end

Spr={jvvv=6}
function Spr:funcx(num)
  self.ddd=8
  self:func2(num)
end
function Spr:func(num)
  
  self.jvvv=self.jvvv+num
end

function Spr:func2(num)
  self:func(num)
  print(self.ddd)
end

axx=Spr
axx:funcx(3)
print(axx.jvvv)
print(Spr.jvvv)