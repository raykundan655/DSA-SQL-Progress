-- #Role base access control
-- design the role based on access control,
-- we can use data control language statement to create role and grant privilage to those role
-- 1.create role
-- 2.grant action to role
-- 3.assign the role to the user

-- CREATE THE ROLE
-- syntex:
-- create role ROLE_NAME;
eg:
create role admin;

--GRANT ACTION TO THE ROLE
GRANT SELECT,UPDATE,DELETE ON STUDENTS TO ADMIN;
-- GIVING ACTION TO ADMIN ROLE

--ASSIGN THE ROLE TO USER
GRANT ADMIN TO USER1;
-- GIVE ALL THE RIGHT OF ADMIN TO USER1

-- WE CAN REVOKE THE ACTION FROM ROLE BY REVOKE

REVOKE DELETE ON STUDENTS FROM ADMIN;


-- SELECT STATEMENT
-- IT IS USE TO EXTRACT THE ROWS FROM TABLE AND DISPLAY THE DATA AS OUTPUR

create table student(
  name varchar2(50) not null,
  roll_no int unique,
  cgpa float not null);
-- this is empty table i made not in that i just  created the structure but let's imagin the table has data

select * from student;
-- * indicate all means extract data from all column
-- in this there is no condition which row have to extract so it will extract all rows but we have mention from which col we need data in the row ->* indicate we need from all col

select roll_no from student;
-- extract the rows but only give me val of roll_no in each row(select extract the row but we have to mention from which col we need data in each rows)

select name,roll_no from student order by roll_no desc;
-- this sort the data in desc order base on roll_no
-- if we are not writing desc then it will automatically sort asc order

-- DISTINCT keyword give unique val 
select distinct name from student;
-- it will display non repeted name only distinct data


-- FILTER THE ROWS

-- WHERE CLAUSE
-- WHERE is used in SQL to filter rows in a table and show only the data that meets a specific condition.
-- where<condition>

select name from student where name="mahi";
-- only give me those row in which name col have mahi
-- it filter the data 

select roll_no from student where fees>=12000 order by roll_no;
-- select only those row in which fees col have val more then 12000

select roll_no from student where fees between 5000 and 10000;
-- select only row that lies in b/w val

-- in condition

select name from students where roll_no in(1,2,3);
-- select only row in which roll_no col value has 1,2,3 only these val


-- where caluse using like condition
-- wildcard operator

-- i>%->represent one,more then one char 
eg:
select name from student where name like 'm%a';
-- select the row in which name start with m and end a in b/w any number of char will be
-- mahia
-- monita
-- like condition will be select both row
-- m%a
-- m is first char
-- a is last char

-- where clause using logical condition
-- 1.and
select name from student where fees>5000 and  fees<10000
-- it will select only those row that fullfill both condition

-- 2.or
select name from student where fees>5000 or  fees<10000;
-- if any of the condition true then row will be selected
-- 3.not
select name from student where city not in ("chennai");
-- select the row in which city col don't have chennai


-- ALISE
-- Alias is used to give a temporary name to a column or table to make it easier to read in the result.

-- SYNTEX
SELECT name AS student_name FROM Students;
-- it will show name col with the name student_name 

select name,roll_no,(fees*0.18) as gst_amount from student;
-- it will cal gst for each row and display as gst_amount (temp col)

-- AGGREGATE FUNCTION


-- is function that take multiple input and return singal output
-- eg:
-- in fess col have vales(1200,1300,12000,25000,...)
-- sum(fees) it will sum all the value and return total val(singal output)
-- in sql there is 5 aggregate function

-- Function	    What It Does                     	Example
-- COUNT()	    Counts number of rows	            COUNT(*)
-- SUM()	      Adds all values in a column	       SUM(marks)
-- AVG()	     Finds average of values	           AVG(marks)
-- MAX()      	Finds highest value	              MAX(marks)  max val will return of the col
-- MIN()	     Finds lowest value	                MIN(marks)  min val of col will retun 


select count(roll_no) as no_of_student from student
-- count all rows of roll_no col and return the result with name no_of_student

select count(distinct name) as name_count from student
-- it will count only distinct row no base on name

select sum(price) as total_price from student
-- it will sum the value of price col and return

select avg(price) as average_price from student
-- calculate the average of price col->sum(price)/count(price)


select min(price) as min_amount from student
-- give min price





-- NOTE FOR FUTURE DAYS!!
-- In a subquery, the SELECT statement does not display anything —
-- it fetches the value and returns it to the outer query (like a variable).
-- Subquery is like a function → it runs, gets a value, and returns it to be used somewhere.


  
  --  the Main Query, the SELECT statement:
-- Fetches data from the table and then displays (returns) the result to the user.

--  So in simple words:
-- 🔸 Main query SELECT = Fetch + Display (Return to screen)
-- 🔸 Subquery SELECT = Fetch + Return (Used by main query, not displayed)










