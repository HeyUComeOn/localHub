Account = {
balance = 12

}

function Account.count( self , v )
  self.balance = self.balance + v;
  print ("the balance is : "..self.balance)
end

function Account:myToString()
  print ( "��ֵΪ"..self.balance)
end

tt = Account
tt.count( tt , 12 )
tt:count( 12 )      --��ȥ��self��ʹ��
tt:myToString()

local p = require ( "myClass" )
p:showName()

