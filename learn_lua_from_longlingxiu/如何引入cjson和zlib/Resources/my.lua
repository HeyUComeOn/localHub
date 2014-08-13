
print("enter my.lua")

local sqlite    =   require("lsqlite3")

print("path is "..getFullPath())

local path  = getFullPath().."mydb"

local db    = sqlite.open(path)

print("the datebase is created")--这两个print可以检测上一步是否执行

db:exec[[

    create table test (id INTEGER PRIMARY KEY , content);
    insert into test values(1 ,'gogpg');
    insert into test values(2 ,'lololo');

]]

--把db:exec[[...]]这段代码删除掉，就可以知道数据是否持久化
--往数据库中添加数据就向db:exec[[...]]里面添加数据就行
for row in db:nrows("select * from test") do
print( row.id ,row.content)
end

local cjson =   require("cjson")
print("load cjson successfully!")

local zlib  =   require("zlib")
print("load zlib successfully!")