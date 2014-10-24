--元表setmetatable(a,b)使 a在b中查找
Account = { num = 10}

function Account : new ( o )
  o = o or {}--用wiz笔记中的最短路径法理解
  setmetatable ( o , self )   --设定o为Account的子类
  self.__index = self
  return o
end

function Account : show ( v )
print (   self.bbb + v )
end

a = Account : new { bb = 6,bbb = 0 }  --父类有的子类必须有，父类没有的子类可以有，不然参数为{b=0}报错
a : show ( 1.0 )            --运行到此处，必须对show函数中的self.bbb赋值,不賦值無法計算，我感觉可以模拟虚函数继承
print(Account.bbb)
print(Account.bb)
print(Account.b) 
--===============================================================
--===============================================================
--===============================================================
--===============================================================
--===============================================================

Windows = {} -- 创建一个命名空间
 
-- 创建默认值表
Windows.default = {x = 0, y = 0, width = 100, height = 100, color = {r = 255, g = 255, b = 255}}
 
Windows.mt = {} -- 创建元表
 
-- 声明构造函数
function Windows.new(o)
     setmetatable(o, Windows.mt)
     return o
end
 
-- 定义__index元方法
Windows.mt.__index = function ( table,key)
     return Windows.default[key]
end
 
local win = Windows.new({x = 10, y = 10})
print(win.x)               -- >10 访问自身已经拥有的值
print(win.width)          -- >100 访问default表中的值
print(win.color.r)          -- >255 访问default表中的值