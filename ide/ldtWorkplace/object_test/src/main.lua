Account = {
balance = 12

}

function Account.count( self , v )
  self.balance = self.balance + v;
  print ("the balance is : "..self.balance)
end

function Account:myToString()
  print ( "此值为"..self.balance)
end

tt = Account
tt.count( tt , 12 )
tt:count( 12 )      --免去了self的使用
tt:myToString()

local p = require ( "myClass" )
p:showName()


