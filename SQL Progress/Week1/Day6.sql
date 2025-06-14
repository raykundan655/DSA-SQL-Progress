-- 1-- Revising the Select Query I
  
-- Query all columns for all American cities in the CITY table with populations larger than 100000. The CountryCode for America is USA.
-- The CITY table is described as follows:

select * from city where population>100000 and countrycode='USA';


-- 2-- Find the difference between the total number of CITY entries in the table and the number of distinct CITY entries in the table.
-- The STATION table is described as follows:
select (count(city)-count(distinct city)) from station;

--3 Query a count of the number of cities in CITY having a Population larger than 100000

select count(distinct name) from city where population>100000;

--4 Query the total population of all cities in CITY where District is California.
  select sum(population) from city group by District having District='California';
-- sql take string in singal quote don't write in double quote

--5 Query the average population of all cities in CITY where District is California.
-- select round(avg(population),1) from city group by  District having  District='California';
or 
select avg(population) from city where District='California';


--6 We define an employee's total earnings to be their monthly  worked, and the maximum total earnings to be
-- the maximum total earnings for any employee in the Employee table. Write a query to find the maximum total earnings for 
-- all employees as well as the total number of employees who have maximum total earnings. Then print these values as  space-separated integers.

select (salary * months) ,count(*) from employee where (salary*months)= (select max(salary*months) from employee) group by (salary*months);
-- NOTE!!
-- If you include non-aggregated columns in the SELECT 
-- clause alongside aggregates, then you must use GROUP BY, especially when ONLY_FULL_GROUP_BY mode is enabled (default in MySQL 5.7+).
-- we can't use aggregate function in where clause


-- 7.Write a query that prints a list of employee names (i.e.: the name attribute) for employees in Employee having a salary greater than 2000 per month who have been employees for less than 10 months. 
--   Sort your result by ascending employee_id.

SELECT name from employee where salary>2000 and months<10 order by employee_id;

-- 8.Query the smallest Northern Latitude (LAT_N) from STATION that is greater than 38.7780 . Round your answer to 4 decimal place
  
SELECT ROUND(MIN(LAT_N), 4) AS Rounded_Latitude 
FROM STATION 
WHERE LAT_N > 38.7780;

-- 9.Query the difference between the maximum and minimum populations in CITY.
  select (max(population)-min(population)) from city;

-- 10.Samantha was tasked with calculating the average monthly salaries for all employees in the EMPLOYEES table, but did not realize her keyboard's  key was broken until after completing the calculation. She wants your help finding the difference between her miscalculation (using salaries with any zeros removed), and the actual average salary.
-- Write a query calculating the amount of error (i.e.:  average monthly salaries), and round it up to the next integer.

SELECT CEIL(AVG(salary) - AVG(CAST(REPLACE(salary, '0', '') AS INT))) FROM employee;


-- CAST() is used to convert data from one type to another
-- When you remove zeroes from a salary using REPLACE(), the result becomes a string.
-- But to calculate the average, SQL needs it to be a number
-- CAST(REPLACE(SALARY, '0', '') AS UNSIGNED/int) 
-- Please convert this cleaned-up string back into a number, so I can calculate the average.”

