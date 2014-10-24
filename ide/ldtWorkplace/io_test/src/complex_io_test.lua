--面向对象方式
--首先获取流的指针或句柄
local f=assert(io.open("D:\\Documents\\GitHub\\localHub\\ide\\ldtWorkplace\\io_test\\src\\a.txt",'r'))
local t=f:read("*all")
print(t)
f:close()

function write_st(message)
local f=assert(io.open("D:\\Documents\\GitHub\\localHub\\ide\\ldtWorkplace\\io_test\\src\\a.txt" ,'a'))
f:write(message)

bufferSize=2^13
f:read(bufferSize,"*line")--读取每行时缓存为8kb
f:close()
end

write_st("kkkkkkkkk")

--[[
function write_other_st(msg)
local file = assert(io.open("D:\\Documents\\GitHub\\localHub\\ide\\ldtWorkplace\\io_test\\src\\a.txt","a"))
	local temp =io.input()
	file:input("newinput.txt")
	file:write(msg)
  io.input():close()
  io.input(temp)
end
]]
