-- Group by
-- used in SQL to group rows that have the same values in specified columns into summary rows 
-- it give summary table

-- syntex:
-- SELECT column1, AGGREGATE_FUNCTION(column2)
-- FROM table_name
-- GROUP BY column1;

-- eg:
select pdt_type,count(*) as no_of_product from product group by pdt_type order by pdt_typr;

select month,min(electricity_unit) as min_use from product group by month;

-- having clause
--  HAVING clause is used to filter the results after you group data using GROUP BY.
-- It's like saying:
--  "After I group the rows, now I want to keep only those groups that match this condition.

-- Imagine a table called Sales:
-- id	product	amount
-- 1	Apple	100
-- 2	Apple	200
-- 3	Mango	150
-- 4	Apple	300
-- 5	Mango	100
-- ask: Show products where total amount is more than 400.
-- SELECT product, SUM(amount) as total_amount
-- FROM Sales
-- GROUP BY product;

-- result group made:
-- product	total_amount
-- Apple	600
-- Mango	250

-- Filter groups using HAVING

SELECT product, SUM(amount) as total_amount
FROM Sales
GROUP BY product
HAVING SUM(amount) > 400;


SELECT product, SUM(amount) AS total_amount
FROM Sales
WHERE amount > 100
GROUP BY product;

-- where clause come before group by it filter the row first then group are made 


-- Date & Time function

-- From system function (SQL gives it)
-- Functions like these:
-- NOW() → current date and time
-- CURDATE() → current date
-- CURTIME() → current time
-- These come from the system, not from any table.


-- DUAL is a special dummy table in some databases (like Oracle) that is used when you need to run a query without using any real table.

-- In SQL, the SELECT statement usually expects a table.
-- But if you're just selecting a value, expression, or function result, you still need to write FROM something.
-- That’s why we use FROM dual — a dummy table that always exists and returns just one row.
-- When you call SYSDATE, Oracle evaluates the function and places its result in that one row from dual.


-- 1.current_date()
select current_date from dual 
-- it give current_date
select sysdate from dual
-- it return sysdate

select now() as currentdate&time;
-- it give both date time 

-- Extracting Parts from a Date
select year(order_date) as order_year from order;
select month(order_date) as order_month from order;
select day(order_date) as order_day from order;


-- Date Difference and Calculations
select datediff(date1,date2) as diff_day

select months_between(date1,date2) as result from dual
  -- it give no of month b/w two month

select add_months(date,2) as montha_addes from dual
  -- it add month to the date

-- EXTRACT FUNCTION
-- syntex:
  -- extract(day/month/year from date)
  
SELECT 
  order_id,
  EXTRACT(YEAR FROM order_date) AS order_year,
  EXTRACT(MONTH FROM order_date) AS order_month,
  EXTRACT(DAY FROM order_date) AS order_day
FROM Orders;


-- TO DATE(STRING_DATE,DATE_FORMAT)
-- TO_DATE() is a function used to convert a string (VARCHAR) into a DATE format in SQL.

SELECT TO_DATE('12-06-2025', 'DD-MM-YYYY') AS converted_date
FROM dual;



-- STRING FUNCTION
-- CONCAT()
-- FOR CONCATENATION
SELECT CONCAT("HELLO","WORLD") AS SAMPLE FROM DUAL;

-- WE CAN ALSO USE || FOR  CONCATENATION
SELECT "HELLO|| WORLD" AS SAMPLE FROM DUAL

-- It means to capitalize the first letter of each word in a string and convert the rest to lowercase.
-INITCAP()

LENGTH(STRING ) 
-- IT GIVE THE STRING LENGTH

TRIM()
-- TRIM() FUNCTION USE TO REMOVE UNWANTED SPACE FROM STRING
-- ->LTRIM() ->LEFT TRIM IT REMOVE SPACE FROM LEFT
-- ->RTRIM() ->RIGHT TRIM IT REMOVE SPACE FROM LEFT

LPAD() & RPAD()
-- LEFT AND RIGHT PADDING

-- THIS FUNCTION USE TO PADS THE STRING WITH SPECIFIC SET OF CHAR
-- EG:
-- STRING: HELLO
-- LPAD(HELLO,8,*)
-- ***HELLO
SELECT RPAD("HELLO",8,'*') AS RESULT FROM DUAL;
-- HELLO***

LOWER()
-- FUNCTIOM USE TO CONVERT STRING INTO LOWER CASE
-- SELECT LOWER("HELLO") AS RESULT  FROM DUAL

UPPER()
-- FUNCTION USE TO CONVERT STRING INTO UPPER
-- SELECT UPPER("HELLO") AS RESULT FROM DUAL

INSTR()
-- IT USE TO FIND INDEX OF SUBSTR INTO STRING

-- SELECT INSTR("HELLO",'E') AS REUSLT FROM DUAL
-- SELECT INSTR("HELLO",'E',1,1) AS REUSLT FROM DUAL
-- FUNDING SUBSTR E INTO STRING HELLO FROM POSITION 1 AND APPEARENCE FIRST

REPLACE()
-- SELECT REPLACE (STRING,REPLACEMENT STR,WITH REPLACEMENT) AS RESULT FROM DUAL

EG:
-- SELECT REPLACE("MAHI","HI","GU") AS RESULT FROM DUAL;
-- MAGU

SUBSTR()
-- SUBSTR(STRING,POSITION,LENGTH)
-- IT GIVE SUBSTRING FROM STRING




















