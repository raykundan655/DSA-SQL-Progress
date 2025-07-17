-- Products table:
-- +------------+-----------+-------------+
-- | product_id | new_price | change_date |
-- +------------+-----------+-------------+
-- | 1          | 20        | 2019-08-14  |
-- | 2          | 50        | 2019-08-14  |
-- | 1          | 30        | 2019-08-15  |
-- | 1          | 35        | 2019-08-16  |
-- | 2          | 65        | 2019-08-17  |
-- | 3          | 20        | 2019-08-18  |
-- +------------+-----------+-------------+
-- Output: 
-- +------------+-------+
-- | product_id | price |
-- +------------+-------+
-- | 2          | 50    |
-- | 1          | 35    |
-- | 3          | 10    |
-- +------------+-------+

-- Initially, all products have price 10.
-- Write a solution to find the prices of all products on the date 2019-08-16.

select p.product_id ,COALESCE((SELECT new_price from Products as p2 
where p2.product_id=p.product_id and 
p2.change_date<='2019-08-16' 
order by p2.change_date desc limit 1),10) as price from 
(select distinct product_id from Products) as p

-- SELECT DISTINCT product_id FROM Products — gives us all unique products.

-- For each product, we look up its latest price before or on 2019-08-16 using a correlated subquery.

-- ORDER BY change_date DESC LIMIT 1 — gets the most recent change up to that date.

-- If no price was changed before 2019-08-16, COALESCE(..., 10) assigns default price 10.


-- Table: Prices
-- +---------------+---------+
-- | Column Name   | Type    |
-- +---------------+---------+
-- | product_id    | int     |
-- | start_date    | date    |
-- | end_date      | date    |
-- | price         | int     |
-- +---------------+---------+

-- UnitsSold
-- +---------------+---------+
-- | Column Name   | Type    |
-- +---------------+---------+
-- | product_id    | int     |
-- | purchase_date | date    |
-- | units         | int     |
-- +---------------+---------+

-- Write a solution to find the average selling price for each product. average_price should be rounded to 2 decimal places.
--   If a product does not have any sold units, its average selling price is assumed to be 0.

SELECT 
    p.product_id,
    ifnull(ROUND(SUM(IFNULL(p.price * u.units, 0)) / SUM(IFNULL(u.units, 0)), 2),0) AS average_price    
FROM 
    Prices AS p 
LEFT JOIN 
    UnitsSold AS u
    ON u.product_id = p.product_id
    AND u.purchase_date BETWEEN p.start_date AND p.end_date
GROUP BY 
    p.product_id;


-- Students table:
-- +------------+--------------+
-- | student_id | student_name |
-- +------------+--------------+
-- | 1          | Alice        |
-- | 2          | Bob          |
-- | 13         | John         |
-- | 6          | Alex         |
-- +------------+--------------+
-- Subjects table:
-- +--------------+
-- | subject_name |
-- +--------------+
-- | Math         |
-- | Physics      |
-- | Programming  |
-- +--------------+
-- Examinations table:
-- +------------+--------------+
-- | student_id | subject_name |
-- +------------+--------------+
-- | 1          | Math         |
-- | 1          | Physics      |
-- | 1          | Programming  |
-- | 2          | Programming  |
-- | 1          | Physics      |
-- | 1          | Math         |
-- | 13         | Math         |
-- | 13         | Programming  |
-- | 13         | Physics      |
-- | 2          | Math         |
-- | 1          | Math         |
-- +------------+--------------+

SELECT 
    s.student_id, 
    s.student_name, 
    sub.subject_name, 
    COUNT(e.subject_name) AS attended_exams
FROM Students s
CROSS JOIN Subjects sub
LEFT JOIN Examinations e 
    ON s.student_id = e.student_id AND sub.subject_name = e.subject_name
GROUP BY 
    s.student_id, 
    s.student_name, 
    sub.subject_name
ORDER BY 
    s.student_id, 
    sub.subject_name;

-- A CROSS JOIN simply creates a Cartesian product — it pairs every row of the first table with every row of the second table, regardless of any matching condition.
