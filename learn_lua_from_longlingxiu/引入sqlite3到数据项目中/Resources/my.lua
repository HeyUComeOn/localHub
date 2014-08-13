


local sqlite    =   require("lsqlite3")

print("  检测上一句话是否载入。")

local db        =   sqlite.open_memory()

db:exec[[

    create table test (id INTEGER PRIMARY KEY , content);
    insert into test values(1 ,'gogpg');
    insert into test values(2 ,'lololo');

]]

for row in db:nrows("select * from test") do
print( row.id ,row.content)
end