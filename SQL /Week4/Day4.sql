-- Find the difference between the total number of CITY entries in the table and the number of distinct CITY entries in the table.
-- The STATION table is described as follows:

select (select count(city) from station)- (select count(distinct city) from station) from station limit 1;
-- ish ko normal count city- count distinct city kar sakta the but yeah db2 syaytem hai jo allow nahi karta 

-- 175. Combine Two Tables

-- able: Person
-- +-------------+---------+
-- | Column Name | Type    |
-- +-------------+---------+
-- | personId    | int     |
-- | lastName    | varchar |
-- | firstName   | varchar |
-- +-------------+---------+
-- Table: Address
-- +-------------+---------+
-- | Column Name | Type    |
-- +-------------+---------+
-- | addressId   | int     |
-- | personId    | int     |
-- | city        | varchar |
-- | state       | varchar |
-- +-------------+---------+
-- Write a solution to report the first name, last name, city, and state of each person in the Person table. 
--   If the address of a personId is not present in the Address table, report null instead.

select  p.firstName  ,p.lastName ,a.city ,a.state  
from 
person as p
left join 
Address  as a 
on a.personId=p.personId;

-- Table: Employee
-- +-------------+------+
-- | Column Name | Type |
-- +-------------+------+
-- | id          | int  |
-- | salary      | int  |
-- +-------------+------+
-- Write a solution to find the second highest distinct salary from the Employee table. 
--   If there is no second highest salary, return null (return None in Pandas).

# Write your MySQL query statement below
select max(salary) as secondHighestSalary from Employee 
where salary<(select max(salary) from Employee );


-- Table: Logs
-- +-------------+---------+
-- | Column Name | Type    |
-- +-------------+---------+
-- | id          | int     |
-- | num         | varchar |
-- +-------------+---------+
-- Find all numbers that appear at least three times consecutively.
-- Return the result table in any order.

-- self join
select distinct l.num as ConsecutiveNums from Logs as l join Logs as ll on  l.id=ll.id+1 join Logs lll
on l.id=lll.id+2 where l.num = ll.num AND ll.num = lll.num;

-- Table: Employee
-- +-------------+---------+
-- | Column Name | Type    |
-- +-------------+---------+
-- | id          | int     |
-- | name        | varchar |
-- | salary      | int     |
-- | managerId   | int     |
-- +-------------+---------+
-- +----+-------+--------+-----------+
-- | id | name  | salary | managerId |
-- +----+-------+--------+-----------+
-- | 1  | Joe   | 70000  | 3         |
-- | 2  | Henry | 80000  | 4         |
-- | 3  | Sam   | 60000  | Null      |
-- | 4  | Max   | 90000  | Null      |
-- +----+-------+--------+-----------+

-- # Write your MySQL query statement below
-- by subquery
select e.name as Employee  from employee as e where salary>(select salary from employee
 where id=e.managerId )

-- or
  -- self join
select e.name as Employee  from Employee  as e
join Employee  ee
on e.managerId =ee.id
where e.salary>ee.salary;

-- Table: Person
-- +-------------+---------+
-- | Column Name | Type    |
-- +-------------+---------+
-- | id          | int     |
-- | email       | varchar |
-- +-------------+---------+

-- Write a solution to report all the duplicate emails. Note that it's guaranteed that the email field is not NULL.
-- Return the result table in any order.

select email 
from Person 
group by email  
having count(email)>1;

-- Table: Customers
-- +-------------+---------+
-- | Column Name | Type    |
-- +-------------+---------+
-- | id          | int     |
-- | name        | varchar |
-- +-------------+---------+

-- Table: Orders
-- +-------------+------+
-- | Column Name | Type |
-- +-------------+------+
-- | id          | int  |
-- | customerId  | int  |
-- +-------------+------+

-- Write a solution to find all customers who never order anything.
-- Return the result table in any order.

# Write your MySQL query statement below
select c.name as Customers  from 
Customers as c
left join 
Orders as o
on
c.id=o.customerId
where o.id is null;




