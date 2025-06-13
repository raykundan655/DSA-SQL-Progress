-- -- subquery
-- nested inside the large query

--   syntex:
-- outer query(nested query)
  
--  SELECT ...
-- FROM ...
-- WHERE column_name = (SELECT ... FROM ... WHERE ...);

-- Nested Query (Subquery):
-- Acts like a function that returns a value (or values).
-- Outer Query:
-- Uses that value(s) to perform further operations like filtering, comparison, etc.

-- eg:
SELECT name, salary
FROM employees
WHERE salary > (
    SELECT AVG(salary)
    FROM employees
);

-- order by clause can't be added into a subquery


-- type:
--  1. Single-Row Subquery
-- Returns only one row with one column (i.e., a single value).
-- Used with operators like =, >, <, <=, >=, <>.

SELECT name, salary
FROM employees
WHERE salary > (
    SELECT AVG(salary)
    FROM employees
);
-- 🔍 The subquery returns a single value (average salary),


-- 2. Multi-Row Subquery
-- ✅ Description:
-- Returns multiple values (one column).
-- Used with operators like IN, ANY, ALL.

-- 🧪 Example:
-- Get employees who work in departments located in 'New York'.

SELECT name
FROM employees
WHERE department_id IN (
    SELECT id
    FROM departments
    WHERE location = 'New York'
);
-- 🔍 Subquery returns multiple department IDs, outer query uses them to find matching employees.



-- Two types of subqueries:
-- 1. Non-Correlated Subquery
-- → Subquery runs once, result is used by outer query
-- → Acts like a constant or fixed list

SELECT name
FROM employees
WHERE department_id IN (
    SELECT id FROM departments WHERE location = 'New York'
);

-- Here, the subquery has no connection to the outer query — it runs once and returns a list.
-- The outer query then uses that list.

-- 2. Correlated Subquery
-- → Subquery depends on the outer query
-- → It runs again and again — once for each row in the outer query

  Find employees whose salary is greater than the average salary of their department.
SELECT e.name, e.salary
FROM employees e
WHERE e.salary > (
    SELECT AVG(salary)
    FROM employees
    WHERE department_id = e.department_id
);
    
--  Here, the subquery uses e.department_id, which comes from the outer query.
-- That means:
-- The subquery can’t run independently.

  -- note!!
-- The subquery refers to a column from the outer query (like e.department_id)
-- So the subquery must be re-evaluated for each row in the outer query


   -- 4. Subquery in the FROM Clause (Inline View)
-- Subquery used in the FROM clause acts like a temporary table.
-- Find departments with average salary greater than 50,000.

SELECT department_id, avg_salary
FROM (
    SELECT department_id, AVG(salary) AS avg_salary
    FROM employees
    GROUP BY department_id
) AS dept_avg
WHERE avg_salary > 50000;


-- 
-- join 
-- A JOIN is used to combine data from two or more tables based on a common column (like ID or department_id).
-- JOIN = Find matching rows → combine their columns → show in one row

-- To bring related data from different tables together in one result.
-- eg:

-- Table 1: Employees
-- Table 2: Departments
-- You want to know which employee works in which department → You JOIN the two tables using department_id.

-- JOIN Syntax (Basic format)
SELECT columns
FROM table1
JOIN table2
ON table1.common_column = table2.common_column;

-- ️ INNER JOIN
-- Returns only rows where there is a match in both tables.

SELECT e.name, d.name
FROM employees e
INNER JOIN departments d
ON e.department_id = d.id;

-- Show only employees who belong to a department.

LEFT JOIN (Left Outer Join)
Returns all rows from the left table, and matched rows from right table.
If no match, right side shows NULL.


🟦 Students
student_id	name                           
1	       Rahul
2	       Priya
3	        Ayaan


🟩 Marks
student_id	subject	      marks
1	        Math	            95
1	     English	            88
2	       Math	              75
4	      Science             80


-- JOIN ON THE BASIS OF ID
-- INNER JOIN 

-- name	subject	marks
-- Rahul	Math	95
-- Rahul	English	88
-- Priya	Math	75
-- COMMON ID VALUES 


-- LEFT JOIN
-- name	subject	marks
-- Rahul	Math	95
-- Rahul	English	88
-- Priya	Math	75
-- Ayaan	NULL	NULL 

-- ARAYAN IS NOT MATCH WITH 2ND TABLE THAT'S WHY THE ATTRIBUTE OF SECOND COL IS NULL
-- ALL ROW OF LEFT COL IS SLECTED BUT IF THERE IS NO MATCHING WITH SECOND TABLE THEN THE ATTRIBUTE OF SECOND TABLE VALUE WILL BE NULL


--  RIGHT JOIN (Right Outer Join)
-- ➡️ Returns all rows from the right table, and matched rows from left table.
-- If no match, left side shows NULL.

SELECT e.name, d.name
FROM employees e
RIGHT JOIN departments d
ON e.department_id = d.id;
-- Means: Show all departments, even if no employee is in them.
   
-- RIGHT JOIN
-- name	subject	marks
-- Rahul	Math	95
-- Rahul	English	88
-- Priya	Math	75
-- NULL	Science	80



-- CASE statement

-- The CASE statement is like an IF-ELSE ladder in SQL.
-- It lets you create a new column or change values based on conditions.


SELECT 
  column1,
  column2,
  CASE 
    WHEN condition1 THEN result1
    WHEN condition2 THEN result2
    ELSE result3
  END AS new_column
FROM table_name;

-- CASE CREATE TEMP COL FOR RESULT IN THIS COL VALUE ON THE BASIS OF IF ELSE LADDER











