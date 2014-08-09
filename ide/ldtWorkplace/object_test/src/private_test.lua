function newAccount(initializeBalance)
  local self = {balance=initializeBalance}
  local show =function (v)
    self.balance = self.balance -v

  end
  local getBalance=function()
    return self.balance
  end
  return{          --∑‚—b
    show =show,
    getBalance=getBalance
  }
end
acc=newAccount(200)
print(acc.getBalance)
print(acc.getBalance())
acc.show(100)
print(acc.getBalance())

--ÜŒ“ª∑Ω∑®
function newObject(value)
  return function(action,v)
    if action =="get" then return value
    elseif action=="set" then value= v
    else error("invalid action")
    end
  end
end

d=newObject(0)
print (d("get"))
d("set",10)
print(d("get"))




