require ("aa")
showName("ostv")
--[[
1.判断包是否存在
2.判段是否加载
3.如果没有，返回nil或者报错
4.反之返回相应的模块对象



app/test/cc.lua
require("app.test.cc")--自动替换为分隔符
a_b.lua
require ("a.b")--智能搜寻
]]

local tt = require("mymodule")
tt.showName()
tt:showName()

function s()
return 20
end
local vith = s
print(vith)--打印出函数地址