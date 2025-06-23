-- +-------------+------+
-- | Column Name | Type |
-- +-------------+------+
-- | teacher_id  | int  |
-- | subject_id  | int  |
-- | dept_id     | int  |
-- +-------------+------+
-- (subject_id, dept_id) is the primary key (combinations of columns with unique values) of this table.
-- Each row in this table indicates that the teacher with teacher_id teaches the subject subject_id in the department dept_id.


select teacher_id,count(distinct subject_id) as cnt
from Teacher 
group by teacher_id;


-- Table: Activity
-- +---------------+---------+
-- | Column Name   | Type    |
-- +---------------+---------+
-- | user_id       | int     |
-- | session_id    | int     |
-- | activity_date | date    |
-- | activity_type | enum    |
-- +---------------+---------+
-- This table may have duplicate rows.
-- The activity_type column is an ENUM (category) of type ('open_session', 'end_session', 'scroll_down', 'send_message').
-- The table shows the user activities for a social media website. 
-- Note that each session belongs to exactly one user.


select activity_date as  'day' ,
count(distinct user_id  ) as 'active_users' 
from Activity
where
activity_date<='2019-07-27' and activity_date>'2019-06-27'
group by activity_date


-- Table: Sales
-- +-------------+-------+
-- | Column Name | Type  |
-- +-------------+-------+
-- | sale_id     | int   |
-- | product_id  | int   |
-- | year        | int   |
-- | quantity    | int   |
-- | price       | int   |
-- +-------------+-------+
-- (sale_id, year) is the primary key (combination of columns with unique values) of this table.
-- product_id is a foreign key (reference column) to Product table.
-- Each row records a sale of a product in a given year.
-- A product may have multiple sales entries in the same year.
-- Note that the per-unit price.
-- Write a solution to find all sales that occurred in the first year each product was sold.


select  product_id, year as first_year, quantity , price from 
Sales as s
where year=
(select min(year)  from Sales as s1 where s.product_id=s1.product_id)
-- -- it check for every row product that year is min value or not if yes then include else skip
                                --   or
select  s.product_id, s.year as first_year, s.quantity , s.price from 
Sales as s 
join (select product_id, min(year) as min_year from Sales group by product_id ) as a 
-- creted the temp tebale with product min year and join the basis of two
on a.min_year=s.year and  a.product_id=s.product_id;


-- Table: Courses
-- +-------------+---------+
-- | Column Name | Type    |
-- +-------------+---------+
-- | student     | varchar |
-- | class       | varchar |
-- +-------------+---------+
-- (student, class) is the primary key (combination of columns with unique values) for this table.
-- Each row of this table indicates the name of a student and the class in which they are enrolled.


select distinct c.class from Courses  as c join
(select class,count(student) as no_of_student from Courses group by class )
 as cl on c.class=cl.class where cl.no_of_student>=5 ;

-- or

SELECT class
FROM Courses
GROUP BY class
HAVING COUNT(student) >= 5;
-- If the column is not in GROUP BY, then in HAVING it must use an aggregate like COUNT(), AVG(), etc.

-- Table: Followers
-- +-------------+------+
-- | Column Name | Type |
-- +-------------+------+
-- | user_id     | int  |
-- | follower_id | int  |
-- +-------------+------+
-- (user_id, follower_id) is the primary key (combination of columns with unique values) for this table.
-- This table contains the IDs of a user and a follower in a social media app where the follower follows the user.

select user_id,count(follower_id) as followers_count
 from Followers 
 group by user_id; 


-- Table: MyNumbers
-- +-------------+------+
-- | Column Name | Type |
-- +-------------+------+
-- | num         | int  |
-- +-------------+------+
-- This table may contain duplicates (In other words, there is no primary key for this table in SQL).
-- Each row of this table contains an integer.
--  A single number is a number that appeared only once in the MyNumbers table.
-- Find the largest single number. If there is no single number, report null.


select max(num) as num from 
 (select num  from  MyNumbers group by num having count(num)=1) as tab ;
--  this table give the number those have count 1

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

select customer_id  from Customer
 group by customer_id
 having
 count(distinct product_key)=(select count(distinct product_key) from Product);
--  only select those customer whose product_key count is equal to total product_key of product tavle

 
