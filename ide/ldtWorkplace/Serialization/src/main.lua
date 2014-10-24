function serialization( o )
  if(type(o)=="number")then
    io.write( o )
  elseif type(o)=="string" then
    io.write("[===[",o,"]===]")

  else

  end

end

a = 'a "program lua" \\'
print (string.format("%q",a))--结果精确保存
--保存无环的tabel，页末有解释
function N_serialization(o)
  if type(o)=="number" then
    io.write(o)
  elseif type(o)=="string" then
    io.write(string.format("%q",o))
  elseif type(o)=="table" then
    io.write("{\n")
    for key, var in pairs(o) do
      io.write(" ",key," = ")
      N_serialization(var)
      io.write(",\n")
    end
    io.write("}\n")
  end
end
N_serialization({3,"lua","3sfs3",{123,"jj"}})

--[[
local a = {}
local b = {}
a.next = b
b.next = a
a和b之间存在相互引用关系在很多语言里 
这样的结构会使a和b无法被系统执行的垃圾回收所回收
但是lua里这样是可以回收的
如果你希望可以被更轻易的回收 
可以使用lua的弱引用
]]
