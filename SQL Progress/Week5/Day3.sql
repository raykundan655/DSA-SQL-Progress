-- Input: 
-- Cinema table:
-- +----+------------+-------------+--------+
-- | id | movie      | description | rating |
-- +----+------------+-------------+--------+
-- | 1  | War        | great 3D    | 8.9    |
-- | 2  | Science    | fiction     | 8.5    |
-- | 3  | irish      | boring      | 6.2    |
-- | 4  | Ice song   | Fantacy     | 8.6    |
-- | 5  | House card | Interesting | 9.1    |
-- +----+------------+-------------+--------+
-- Write a solution to report the movies with an odd-numbered ID and a description that is not "boring".
-- Return the result table ordered by rating in descending order.

select id,movie,description,rating 
from Cinema 
where id%2!=0 and description!='boring'
order by  rating desc;

-- Input: 
-- Seat table:
-- +----+---------+
-- | id | student |
-- +----+---------+
-- | 1  | Abbot   |
-- | 2  | Doris   |
-- | 3  | Emerson |
-- | 4  | Green   |
-- | 5  | Jeames  |
-- +----+---------+

-- Write a solution to swap the seat id of every two consecutive students. If the number of students is odd, the id of the last student is not swapped.
-- Return the result table ordered by id in ascending order.

-- # Write your MySQL query statement below
select case 
when id%2=1 and id+1<=(select count(*) from Seat) then id+1
-- when id is odd we put next id no in to the rwo after checking that odd id not all row
when id%2=0 then id-1 
  -- adding  previous row id in row of even id
else id
end as id,
student from Seat 
order by id asc;

-- What Actually Happens:
-- You're only creating a new column (student_id) in the result.
-- The actual table data in the database (Seat) is not modified at all.
-- You're just rearranging the output rows when you ORDER BY student_id(id).

-- Note
-- SELECT queries are read-only operations.
-- They just fetch and display data based on conditions or calculations.
-- They do not change any data stored in the database.

-- Salary table:
-- +----+------+-----+--------+
-- | id | name | sex | salary |
-- +----+------+-----+--------+
-- | 1  | A    | m   | 2500   |
-- | 2  | B    | f   | 1500   |
-- | 3  | C    | m   | 5500   |
-- | 4  | D    | f   | 500    |
-- +----+------+-----+--------+
-- write a solution to swap all 'f' and 'm' values (i.e., change all 'f' values to 'm' and vice versa) with a single update statement and no intermediate temporary tables.
-- Note that you must write a single update statement, do not write any select statement for this problem.

update Salary 
set  
sex=(case 
when sex='m' then 'f' 
when sex='f' then 'm' 
end);

-- basic syntex
-- UPDATE table_name
-- SET column1 = value1, column2 = value2, ...
-- WHERE condition;

-- Table: Customer
-- +-------------+---------+
-- | Column Name | Type    |
-- +-------------+---------+
-- | customer_id | int     |
-- | product_key | int     |
-- +-------------+---------+
-- This table may contain duplicates rows. 
-- customer_id is not NULL.
-- product_key is a foreign key (reference column) to Product table.
 

-- Table: Product
-- +-------------+---------+
-- | Column Name | Type    |
-- +-------------+---------+
-- | product_key | int     |
-- +-------------+---------+
-- product_key is the primary key (column with unique values) for this table.

-- Write a solution to report the customer ids from the Customer table that bought all the products in the Product table.
-- Return the result table in any order.

select c.customer_id from Customer as c inner join Product as p 
on p.product_key=c.product_key group by customer_id
having count(distinct c.product_key)=(select count(*) from Product);

-- Note
-- SQL har group pe aggregate function calculate karta hai (COUNT(DISTINCT ...)), phir us result ko compare karta hai using HAVING"

-- group by
-- Agar HAVING clause ke andar aggregate function (jaise COUNT(), SUM(), AVG()) use kiya gaya hai, to:
-- 🔁 SQL pehle har group ke liye aggregate calculate karega,
-- uske baad hi HAVING clause us par condition check karega.

-- ek summary row baan jaata hai per group then filter


-- Table: ActorDirector
-- +-------------+---------+
-- | Column Name | Type    |
-- +-------------+---------+
-- | actor_id    | int     |
-- | director_id | int     |
-- | timestamp   | int     |
-- +-------------+---------+
-- timestamp is the primary key (column with unique values) for this table.
--  Write a solution to find all the pairs (actor_id, director_id) where the actor has cooperated with the director at least three times.

-- # Write your MySQL query statement below
select actor_id ,director_id
from 
ActorDirector
group by actor_id ,director_id
having count(*)>=3;









