-- table遍历
t = {
  k=3,
  5,
  config={},
  4,
}

--第一种遍历
for i =1,#t do
  print("value is "..t[i])
end

--第二种遍历
for key, var in ipairs(t) do
  print(key, var)
end

--一二均是隐身索引来迭代
--第三种遍历方式,输出所有，先显示隐身索引，在显示其他
print("=========================")
for key, var in pairs(t) do
  print(key, var)

end
