--[[local myClass = {
  name = "x_mitsui"
}

function myClass:showName(  )
  print (myClass.name)
	
end

return myClass]]

-----------------------------------------------
-----------------------------------------------

--[[Account = {balance = 0}

function Account:withdraw(v)
   self.balance = self.balance - v
   print(self.balance)
end
--调用代码可改为：
a = Account; Account = nil
a:withdraw(100.00)]]
--------------------------------------------
--------------------------------------------

--[[
在这段代码中，我们可以将Account视为class的声明，如Java中的：
public class Account 
{
    public float balance = 0;
    public Account(Account o);
    public void deposite(float f);
}
--]]
--这里balance是一个公有的成员变量。
Account = {balance = 0}

--new可以视为构造函数
function Account:new(o)
    o = o or {} --如果参数中没有提供table，则创建一个空的。
    --将新对象实例的metatable指向Account表(类)，这样就可以将其视为模板了。
    setmetatable(o,self)
    --在将Account的__index字段指向自己，以便新对象在访问Account的函数和字段时，可被直接重定向。
    self.__index = self
    --最后返回构造后的对象实例
    return o
end

--deposite被视为Account类的公有成员函数
function Account:deposit(v)
    --这里的self表示对象实例本身
    self.balance = self.balance + v
end

--下面的代码创建两个Account的对象实例

--通过Account的new方法构造基于该类的示例对象。
a = Account:new()
--[[
这里需要具体解释一下，此时由于table a中并没有deposite字段，因此需要重定向到Account，
同时调用Account的deposite方法。在Account.deposite方法中，由于self(a对象)并没有balance
字段，因此在执行self.balance + v时，也需要重定向访问Account中的balance字段，其缺省值为0。
在得到计算结果后，再将该结果直接赋值给a.balance。此后a对象就拥有了自己的balance字段和值。
下次再调用该方法，balance字段的值将完全来自于a对象，而无需在重定向到Account了。
--]]
a:deposit(100.00)
print(a.balance) --输出100

b = Account:new()
b:deposit(200.00)
print(b.balance) --输出200