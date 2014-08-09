--以下均爲table的函數
--1.“插入”
t ={
  1,
  2,
  3
}

table.insert(t,1,10)
--table.insert(t,0,8)--報錯，第一個位置索引不是0，是1
table.insert(t,20) --自動添加到末尾



for key, var in ipairs(t) do
  print(key,var)

end
print("=============删除后===============")

--2.删除
table.remove(t,3)
table.remove(t)  --未指定位置删除最后一个
for key, var in ipairs(t) do
  print(key,var)
end
print("=============排序后===============")

--3.排序
table.sort(t)
local function my_sort(x,y)
  if x>y then
    return true
  end
  return false
end
--table.sort(t,my_sort)
for key, var in ipairs(t) do
  print(key,var)
end
print("=============连接后===============")

--4.连接
str_t={"dota2 6.81"," is a new one"}
function rcont(l)
  if type(l) ~="table" then
    return l
  end
  local res={}
  for i=1,#l do
    res[i]=rcont(l[i])
  end
  for key, var in ipairs(res) do
    print(key,var)
  end
  return table.concat(res)
end

local rlt=rcont(str_t)
print(rlt)
print("=============nil后===============")

--5.
t[2] = nil  --索引不变
  for key, var in ipairs(t) do
    print(key,var)   --nil之後不輸出
  end

--6.
print(#t) --nil之後不計長度
print(table.maxn(t))   --改用maxn讀取最大元素個數，包括nil