# sqlite
![SQLite数据库](http://www.oschina.net/question/12_53183)
[英文链接](http://www.askyb.com/sqlite/learn-sqlite-in-1-hour/)

## 1. 安装
* For `Debian or Ubuntu`
```
$ sudo apt-get install sqlite3 sqlite3-dev
```
* For `RedHat, CentOS, or Fedora`
```
$ yum install SQLite3 sqlite3-dev
```

## 2. 创建和通用操作
* 创建数据库
```
sqlite3 test.db
```
* 创建表
```
sqlite> create table test(id integer primary key, value text);
```
* 插入数据
```
sqlite> insert into test(id, value) values(1, 'Micheal');
sqlite> insert into test(id, value) values(2, 'Jenny');
sqlite> insert into test(value) values('Francis');
sqlite> insert into test(value) values('Kerk');
```
* 查询
```
sqlite3> select * from test;
sqlite3 test.db "select * from test;"
```
* 设置格式化查询结果
```
sqlite> .mode column
sqlite> .header on
sqlite> .timer on
sqlite> select * from test;
```
* 修改表结构，增加列
```
sqlite> alter table test add column email text collate nocase;
```
* 创建视图
```
sqlite> create view nameview as select * from test;
```
* 创建索引
```
sqlite> create index test_idx on test(value);
```
* 显示表结构：
```
sqlite> .schema [table]
```
* 获取所有表和视图：
```
sqlite > .tables
```
* 获取指定表的索引列表：
```
sqlite > .indices [table]
```
* 导出数据库到 SQL 文件：
```
sqlite > .output [filename]
sqlite > .dump
sqlite > .output stdout
```
* 从 SQL 文件导入数据库：
```
sqlite > .read [filename]
```
* 格式化输出数据到 CSV 格式：
```
sqlite >.output [filename.csv]
sqlite >.separator ,
sqlite > select * from test;
sqlite >.output stdout
```
* 从 CSV 文件导入数据到表中：
```
sqlite >create table newtable ( id integer primary key, value text );
sqlite >.import [filename.csv ] newtable
```
* 备份数据库：
```
/* usage: sqlite3 [database] .dump > [filename] */
sqlite3 test.db .dump > backup.sql
```
* 恢复数据库：
```
/* usage: sqlite3 [database ] < [filename ] */
sqlite3 test.db < backup.sql
```

> over
```
sqlite >.quit
```
