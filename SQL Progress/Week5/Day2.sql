-- 596. Classes With at Least 5 Students
-- Courses table:
-- +---------+----------+
-- | student | class    |
-- +---------+----------+
-- | A       | Math     |
-- | B       | English  |
-- | C       | Math     |
-- | D       | Biology  |
-- | E       | Math     |
-- | F       | Computer |
-- | G       | Math     |
-- | H       | Math     |
-- | I       | Math     |
-- +---------+----------+

-- Write a solution to find all the classes that have at least five students.
-- Return the result table in any order.

select class 
FROM
Courses
GROUP BY
class
having count(*)>=5;

-- Table: SalesPerson
-- +-----------------+---------+
-- | Column Name     | Type    |
-- +-----------------+---------+
-- | sales_id        | int     |
-- | name            | varchar |
-- | salary          | int     |
-- | commission_rate | int     |
-- | hire_date       | date    |
-- +-----------------+---------+

-- Table: Company
-- +-------------+---------+
-- | Column Name | Type    |
-- +-------------+---------+
-- | com_id      | int     |
-- | name        | varchar |
-- | city        | varchar |
-- +-------------+---------+

-- Table: Orders
-- +-------------+------+
-- | Column Name | Type |
-- +-------------+------+
-- | order_id    | int  |
-- | order_date  | date |
-- | com_id      | int  |
-- | sales_id    | int  |
-- | amount      | int  |
-- +-------------+------+
-- Write a solution to find the names of all the salespersons who did not have any orders related to the company with the name "RED".
-- Return the result table in any order.

select s.name from SalesPerson as s
left join Orders as o
on s.sales_id=o.sales_id  
left join Company as c
on c.com_id =o.com_id 
group by s.sales_id,s.name 
having count(case when c.name='RED' then 1 end)=0;

-- or

-- select s.name from 
-- SalesPerson as s where s.sales_id not in(select o.sales_id from Company as c
-- left join Orders as o on o.com_id=c.com_id
-- where c.name='RED') ;

-- Input: 
-- Triangle table:
-- +----+----+----+
-- | x  | y  | z  |
-- +----+----+----+
-- | 13 | 15 | 30 |
-- | 10 | 20 | 15 |
-- +----+----+----+

-- Report for every three line segments whether they can form a triangle.
-- Return the result table in any order.


select x,y,z,
(case when x+y>z and z+x>y and y+z>x then 'Yes' else 'No' end) as triangle 
from Triangle;

-- MyNumbers table:
-- +-----+
-- | num |
-- +-----+
-- | 8   |
-- | 8   |
-- | 3   |
-- | 3   |
-- | 1   |
-- | 4   |
-- | 5   |
-- | 6   |
-- +-----+

-- A single number is a number that appeared only once in the MyNumbers table.
-- Find the largest single number. If there is no single number, report null.

# Write your MySQL query statement below
with count_no as (select num from 
MyNumbers
group by num
having count(*)=1)
select max(num) as num from count_no;

