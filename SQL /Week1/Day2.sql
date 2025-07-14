-- ALTER COMMAND
-- The ALTER command is used to modify the structure of an existing table — such as adding, deleting, or changing columns.

-- SYNTEX:
-- ALTER TABLE TABLE_NAME ADD( COL_NAME DATATYPE);
-- -- when you use ALTER TABLE ... ADD COLUMN, the new column is added with NULL values for all existing rows (unless you specify a DEFAULT value).

-- eg:

create table student(
  name varchar2(50),
  roll_no int);
alter table student add age int;
-- now age column is added into table with all null value;

-- SYNTEX:
--ALTER TABLE TABLE_NAME MODIFY COL_NAME DATATYPE
-- The MODIFY keyword is used (especially in MySQL) to change the data type or properties of an existing column in a table.

ALTER TABLE student modify name text;
-- data type of name col is now modify

-- SYNTEX:
-- alter table table_name rename column old_col to new_col;
-- -- rename the col
-- alter table table_name rename to new_table_name;
-- rename to table name

alter table student rename to students;

alter table students rename column name to Name;


-- SYNTEX:

-- alter table table_name drop column col_name;
-- it is used to changed in existing table

alter table students drop column roll_no;



-- DEFAULT CONSTRAINT

-- IT IS USED TO SPECIFY A DEFULT VAL FOR A COLUMN IN A TABLE
-- THIS DEFAULT VALUE IS INSERTED INTO THE COL IF NO EXPLICIT VALUE IS PROVIDED DURING AN INSERT STATEMENT

-- CREATE TABLE table_name (
--   column_name datatype DEFAULT default_value
-- );

-- Add DEFAULT to an existing table:
ALTER TABLE Students MODIFY NAME VARCHAR(50) DEFAULT 'India';

-- DROP commond
-- for drop column ffrom table
alter table table_name drop column column_name;

-- for drop the table 
drop table table_name;

-- for droping constriant from existing table
alter table table_name drop constraint constraint_name;


-- TRUNCATE COMMAND
-- THIS IS USED TO REMOVE ALL ROWS FROM TABLE BUT STRUCTURE OF TABLE WILL BE STILL EXIST

-- TRUNCATE TABLE TABLE_NAME;

TRUNCATE TABLE STUDENT;


-- DATA MANIPULATION LANG(DML)
-- DML is a category of SQL commands that are used to manipulate data inside tables (not the table structure).
--   These commands allow you to insert, update, delete, and retrieve data from the database.

-- Common DML Commands:
-- Command	     Purpose
-- INSERT    	   Add new data into a table
-- UPDATE	       Modify existing data in a table
-- DELETE     	 Remove data from a table
-- SELECT	       Retrieve data from one or more table

-- INSERT
-- INSERT IS used to insert new rows into a table.

-- SYNTEX
-- INSERT INTO TABLE_NAME(COL_NAME,..) VALUES("VAL"....);

INSERT INTO Students ( name, age)
VALUES ('Rahul', 20);
         -- or
INSERT INTO students values("mahi",20);
-- "mahi" is value of name col and 20 is value of roll no
-- this is first row if table is empty ,
-- else it will be last row


-- UPDATE
-- The UPDATE command lets you change values in one or more rows of a table.

-- syntex
-- UPDATE table_name
-- SET column1 = value1, column2 = value2, ...
-- WHERE condition;

-- set is keyword that tell update the value in the col where condition is true

update students set name="golu" where name="mahi" 
-- if we miss this condtion part then it will change the value of whole col


-- Delete  keyword
-- it is used to remove one or more rows from a table based on a condition.

syntex:
-- delete from table_name where condition

-- it will delete all row that statisfy the condition

delete from students where name="mahi";
-- if we miss the condtion it will delete all rows


-- SELECT COMMOND
-- The SELECT command is used to retrieve data from one or more tables in a database.

-- SELECT is used to extract (retrieve) data (rows) from a table and display it as output.

-- SYNTEX 
SELECT * FROM STUDENT
-- * INDICATE SELECT THE VALUE FROM ALL COL
-- This will return all rows from the Students table, but also all columns for each row.

SELECT NAME,AGE FROM STUDENT 
-- IN THIS I HAVE MENTION FROM ONLY WHICH COL I NEED VALUE

SELECT * FROM STUDENT WHERE AGE>18;
-- EXTRACT ALL COL DATA BUT ONLY FOR THE ROWS WHOSE AGE VALUE IS GREATER THEN 18
-- WHERE IS USED TO FILTER THE ROWS

-- SORT
SELECT * FROM STUDENT ORDER BY AGE DESC;
-- DISPLAY THE DATA ON THE BASE OF AGE IN DESCENDING ORDER
-- IF DECENDING NAHI LIKHA GA TO IT WILL ORDER BY IN ASECNDING 


-- DATA CONTROL LANG
 -- It is used to control access to data stored in the database — who can see, change, or use the data.

-- Command	      Purpose
-- GRANT	        Give permission to a user/role
-- REVOKE	       Take back previously granted permission


-- GRANT 
-- Gives a user permission to perform certain actions like SELECT, INSERT, UPDATE, etc.

GRANT select,update on students to "mahi"
-- its grant the action select and update on table student to  mahi(mahi have permission to update and extract the data)

grant update(salary) on student to "mahi"
-- only give permission to update salary col

-- REVOKE
-- Removes previously granted permissions
REVOKE UPDATE ON STUDENT FROM "MAHI"
-- removing the permission from mahi 


-- Transaction control language
 -- it is used to manage changes made by DML (Data Manipulation Language) commands like INSERT, UPDATE, and DELETE.
-- the action perform by dml is transaction


-- Command	                         Purpose
-- COMMIT	               Saves all changes made in the current transaction permanently
-- ROLLBACK	              Cancels all changes made in the current transaction
-- SAVEPOINT	              Sets a point within a transaction that you can roll back to later


-- commit
-- used to permanently save all the changes made during the current transaction
-- syntex:
-- commit;
begin;
-- it indiacte this transaction start from here 
update students set age=22 where name="mahi" ;
-- this is updated in table but not saved in database
commit;
-- this transaction is now updated into table afetr begin


-- rollback
-- used to cancel or undo all the changes made in the current transaction before they are committed.
-- syntex:
-- rollback;

BEGIN;

UPDATE Students
SET age = 100
WHERE id = 1;

-- Oops! Wrong update
ROLLBACK;


--SAVEPONIT























