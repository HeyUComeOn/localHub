--'w'写操作；'a'追加，注意转义字符'\\'
--首先获取流的指针或句柄
local f = assert(io.open("D:\\Documents\\GitHub\\localHub\\ide\\ldtWorkplace\\Lua_read_write_file\\src\\forUsedFile.txt",'r'));
local str=f:read("*all");
f:close()--关流
print (str)

local function read_files(fileName)
  local f = assert(io.open(fileName,'r'))
  --此处为读取一行，还有读取一个数字"*number",<num>锁定字符个数
  local content = f:read("*line")
  f:close()
  print (content)
end

print("=========================================")
read_files("D:\\Documents\\GitHub\\localHub\\ide\\ldtWorkplace\\Lua_read_write_file\\src\\forUsedFile.txt")

local f2=assert(io.open("D:\\Documents\\GitHub\\localHub\\ide\\ldtWorkplace\\Lua_read_write_file\\src\\forUsedFile.txt",'a'))
f2:write("\n=============---------========")
f2:close()