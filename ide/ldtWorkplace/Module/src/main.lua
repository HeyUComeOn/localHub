require ("aa")
showName("ostv")
--[[
1.�жϰ��Ƿ����
2.�ж��Ƿ����
3.���û�У�����nil���߱���
4.��֮������Ӧ��ģ�����



app/test/cc.lua
require("app.test.cc")--�Զ��滻Ϊ�ָ���
a_b.lua
require ("a.b")--������Ѱ
]]

local tt = require("mymodule")
tt.showName()
tt:showName()

function s()
return 20
end
local vith = s
print(vith)--��ӡ��������ַ