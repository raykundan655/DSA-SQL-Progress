-- Table: Users
-- +-------------+---------+
-- | Column Name | Type    |
-- +-------------+---------+
-- | user_id     | int     |
-- | user_name   | varchar |
-- +-------------+---------+
-- user_id is the primary key (column with unique values) for this table.
-- Each row of this table contains the name and the id of a user.
 

-- Table: Register

-- +-------------+---------+
-- | Column Name | Type    |
-- +-------------+---------+
-- | contest_id  | int     |
-- | user_id     | int     |
-- +-------------+---------+
-- (contest_id, user_id) is the primary key (combination of columns with unique values) for this table.
-- Each row of this table contains the id of a user and the contest they registered into.


select r.contest_id,round((count(*)/(select count(*) from users )*100),2)as percentage
 from Users as u 
 right join
  Register as r 
  on r.user_id=u.user_id 
  group by r.contest_id 
  order by percentage desc , r.contest_id ASC ;
-- agar desc arange hota hua agar equal value ajaye ga to unko contest_ id ke base pe asc arange kara ga


-- 
-- Table: Queries
-- +-------------+---------+
-- | Column Name | Type    |
-- +-------------+---------+
-- | query_name  | varchar |
-- | result      | varchar |
-- | position    | int     |
-- | rating      | int     |
-- +-------------+---------+
-- This table may have duplicate rows.
-- This table contains information collected from some queries on a database.
-- The position column has a value from 1 to 500.
-- The rating column has a value from 1 to 5. Query with rating less than 3 is a poor query.


-- SELECT 
--     q.query_name,

--     ROUND((
--         SELECT SUM(rating * 1.0 / position)
--         FROM Queries 
--         WHERE query_name = q.query_name
--     ) / (
--         SELECT COUNT(*) 
--         FROM Queries 
--         WHERE query_name = q.query_name
--     ), 2) AS quality,

--     ROUND((
--         SELECT COUNT(*) 
--         FROM Queries 
--         WHERE query_name = q.query_name AND rating < 3
--     ) * 100.0 / (
--         SELECT COUNT(*) 
--         FROM Queries 
--         WHERE query_name = q.query_name
--     ), 2) AS poor_query_percentage

-- FROM 
--     Queries q

-- GROUP BY 
--     q.query_name
-- ORDER BY 
--     q.query_name;


-- optimised

SELECT query_name,
ROUND(SUM(rating / position) / COUNT(*), 2) AS quality,
ROUND(SUM(rating < 3)/COUNT(query_name) * 100, 2) AS poor_query_percentage
FROM Queries
GROUP BY query_name



-- Table: Transactions
-- +---------------+---------+
-- | Column Name   | Type    |
-- +---------------+---------+
-- | id            | int     |
-- | country       | varchar |
-- | state         | enum    |
-- | amount        | int     |
-- | trans_date    | date    |
-- +---------------+---------+
-- id is the primary key of this table.
-- The table has information about incoming transactions.
-- The state column is an enum of type ["approved", "declined"].
 
-- Write an SQL query to find for each month and country, the number of transactions and their total amount, 
--   the number of approved transactions and their total amount.

select concat(year(trans_date),'-',lpad(month(trans_date),2,0)) as month,
country,
count(*) as trans_count ,
sum(case when state='approved' then 1 else 0 end) as approved_count,
sum(amount) as trans_total_amount ,
sum(case when state='approved' then amount else 0 end) as approved_total_amount 
from Transactions
group by concat(year(trans_date),'-',lpad(month(trans_date),2,0))
,country
order by month,country;
 
