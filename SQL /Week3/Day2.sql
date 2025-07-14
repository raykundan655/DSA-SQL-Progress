-- Table: Employee
-- +---------------+---------+
-- | Column Name   |  Type   |
-- +---------------+---------+
-- | employee_id   | int     |
-- | department_id | int     |
-- | primary_flag  | varchar |
-- +---------------+---------+
-- (employee_id, department_id) is the primary key (combination of columns with unique values) for this table.
-- employee_id is the id of the employee.
-- department_id is the id of the department to which the employee belongs.
-- primary_flag is an ENUM (category) of type ('Y', 'N'). If the flag is 'Y', the department is the primary department for the employee. If the flag is 'N', the department is not the primary.

-- Write a solution to report all the employees with their primary department. For employees who belong to one department, report their only department.

with dept_count as (select  employee_id , count(department_id) as count_no  from 
 Employee  group by employee_id )
--  it create tempory table  (Common Table Expression (CTE))

 select  e.employee_id , e.department_id  from Employee as e inner join dept_count as d
 on d.employee_id=e.employee_id 
 where (d.count_no=1) or (d.count_no>1 and e.primary_flag='Y')


-- Table: Triangle
-- +-------------+------+
-- | Column Name | Type |
-- +-------------+------+
-- | x           | int  |
-- | y           | int  |
-- | z           | int  |
-- +-------------+------+
-- In SQL, (x, y, z) is the primary key column for this table.
-- Each row of this table contains the lengths of three line segments.

-- Report for every three line segments whether they can form a triangle.

select x,y,z ,case
  when x+y>z and   x+z>y and  y+z>x
  then 'Yes'
  else 'No'
  end as triangle 
  from Triangle;


-- Query the list of CITY names starting with vowels (i.e., a, e, i, o, or u) from STATION. Your result cannot contain duplicates.
-- station
-- id number
-- city varchar
-- state varchar
-- lat_n  num
-- long_n  num

select distinct city from 
 STATION where 
 lower(city) like 'a%' or
 lower(city) like 'e%' or
 lower(city) like 'i%' or
 lower(city) like 'o%' or
 lower(city) like 'u%' ;


-- or
-- find city that end with vowel

SELECT DISTINCT city 
FROM STATION
WHERE 
LOWER(city) LIKE '%a'  OR
LOWER(city) LIKE '%e'  OR
LOWER(city) LIKE '%i'  OR
LOWER(city) LIKE '%u'  OR
LOWER(city) LIKE '%o';


