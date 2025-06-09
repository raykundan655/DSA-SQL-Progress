-- Into to sql
-- sql is structure query language 
-- it is use to store and manging data in RDMS
-- standard language for accessing and manipulating database

-- sql commond
-- SQL Commands are instructions used to communicate with a database
-- sql commond  categorized into 5
-- 1.data defination language 
-- 2.data manipulation lang
-- 3.transaction control lang
-- 4.data control lang
-- 5.data query languagee




-- -- data type
-- String data type
-- CHAR(n)	         Fixed-length string (e.g., CHAR(10))
-- VARCHAR(n)	       Variable-length string (e.g., VARCHAR(100))
-- TEXT	          Long text (no specific size limit in many DBs)

-- Number data type
-- -- INT / INTEGER          	Whole numbers (e.g., 10, 500)
-- SMALLINT	                      Smaller whole numbers
-- BIGINT	                        Very large whole numbers
-- FLOAT(n)	                    Approximate decimal number (floating)
-- DOUBLE / DOUBLE PRECISION	   Double-precision floating-point
-- NUMERIC(p,s)                p tell no of digit before decimal ,s tell no of decimal

-- Date and Time Data Types 
-- DATE     	Stores date (YYYY-MM-DD)
-- TIME     	Stores time (HH:MM:SS)
-- DATETIME	   Stores both date and time
-- TIMESTAMP	  Date + time + time zone info
-- YEAR	         Stores year (e.g., 2025)

-- BOOLEAN Data type
-- BOOLEAN	         TRUE / FALSE values



-


-- 1. DDL – Data Definition Language
-- Used to define and manage table structure.
  -- (Think of DDL as the "architect" of the database—it creates and alters the design of tables and databases.)

  
-- Command	Description
-- CREATE	     Creates a new database or table
-- ALTER	       Modifies an existing table
-- DROP	       Deletes a table or database
-- TRUNCATE	    Removes all data from a table
-- RENAME	        Renames a table


-- CREATE

  -- syntex:
create table table_name(
  attribute1 datatype ,
  attribute2 datatype,
  attribute3 datatype
  );

-- sql constraint
-- SQL Constraints are rules applied to columns in a table to control the type of data that can be stored in them.

-- Constraint	                       Description
-- NOT NULL	                         Ensures a column cannot have NULL values
-- UNIQUE	                           Ensures all values are different in a column
-- PRIMARY KEY	                       Uniquely identifies each row + NOT NULL + UNIQUE combo
-- FOREIGN KEY	                       Enforces a link between records in two tables
-- CHECK	                             Ensures data meets a condition
-- DEFAULT	                           Sets a default value for a column if no value is provided


-- Create syntex
-- create table table_name(
--   attribute_name datatype constraint_type,
--   attribute_name datatype constraint_type
--   );


create table customer(
  customer_id int not null,
  firstName  varchar2(50) not null,
  street varchar2(50) not null,
  city varchar2(50) not null,
  -- customer id is my primary key 
  -- A Primary Key is a column (or a set of columns) in a database table that uniquely identifies each row.
  -- Think of it as the unique ID for each row — no duplicates, no missing values allowed.
  -- how to declar
constraint cust_pk(rule_name) primary key(customer_id)

  

-- When you create a rule in SQL (like a Primary Key, Foreign Key, or Check), you can give that rule a name.
-- This name is just a label — it helps you find, delete, or change the rule later.

-- eg:
--  you are the class monitor and you create 3 rules:
-- No one can enter late.
-- No phones allowed.
-- Everyone must bring a notebook.

-- You can just say:
-- "Rule 1", "Rule 2", etc. → but it's hard to remember.

-- Instead, if you name the rules:
-- no_late_entry
-- no_phones
-- must_bring_notebook
-- Now it’s easy to talk about, change, or remove any rule


  );

-- 
-- Foreign Key
--   A Foreign Key is a column (or group of columns) in one table that connects to the Primary Key of another table.
-- 📌 It creates a relationship between two tables.
    
-- declare 
-- constraint rule_name foreign key(cust_id)  references table2(col)

-- REFERENCES Students(student_id) means:
-- This foreign key column (like student_id in your table)
-- must match values from the student_id column of the Students table.
-- alaways decalare in child table


create table Order(
  order_id int not null,
cust_id int not null,
name    varchar(50) not null,
  to_street varchar(50) not null,
  to_city varchar(50) not null,
  constraint order_pk primary key(order_id),
  constraint cust_fk foreign key(cust_id) references custome(cust_id)
  );











