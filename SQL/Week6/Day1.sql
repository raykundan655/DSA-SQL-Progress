Input: 
Transactions table:
+------+---------+----------+--------+------------+
| id   | country | state    | amount | trans_date |
+------+---------+----------+--------+------------+
| 121  | US      | approved | 1000   | 2018-12-18 |
| 122  | US      | declined | 2000   | 2018-12-19 |
| 123  | US      | approved | 2000   | 2019-01-01 |
| 124  | DE      | approved | 2000   | 2019-01-07 |
+------+---------+----------+--------+------------+
Output: 
+----------+---------+-------------+----------------+--------------------+-----------------------+
| month    | country | trans_count | approved_count | trans_total_amount | approved_total_amount |
+----------+---------+-------------+----------------+--------------------+-----------------------+
| 2018-12  | US      | 2           | 1              | 3000               | 1000                  |
| 2019-01  | US      | 1           | 1              | 2000               | 2000                  |
| 2019-01  | DE      | 1           | 1              | 2000               | 2000                  |
+----------+---------+-------------+----------------+--------------------+-----------------------+
-- Write an SQL query to find for each month and country, the number of transactions and their total amount, the number of approved transactions and their total amount.

select DATE_FORMAT(trans_date, '%Y-%m') as month ,country,count(state) as trans_count,
count(case when state='approved' then 1 end) as 
approved_count,sum(amount)as trans_total_amount,
sum(case when state='approved' then amount else 0 end) as 
approved_total_amount from Transactions
group by country,month;

-- note
-- The DATE_FORMAT() function in SQL is used to format a date or datetime value into a specific string format.
-- DATE_FORMAT(date, 'format_string')
-- Format	Meaning	Example     (2025-07-14)
-- %Y   	4-digit year	        2025
-- %y	    2-digit year	         25
-- %m	    2-digit month (01–12)	 07
-- %M	    Full month name	        July
-- %d	    2-digit day (01–31)	     14

-- Input: 
-- Queries table:
-- +------------+-------------------+----------+--------+
-- | query_name | result            | position | rating |
-- +------------+-------------------+----------+--------+
-- | Dog        | Golden Retriever  | 1        | 5      |
-- | Dog        | German Shepherd   | 2        | 5      |
-- | Dog        | Mule              | 200      | 1      |
-- | Cat        | Shirazi           | 5        | 2      |
-- | Cat        | Siamese           | 3        | 3      |
-- | Cat        | Sphynx            | 7        | 4      |
-- +------------+-------------------+----------+--------+


-- The average of the ratio between query rating and its position.
-- We also define poor query percentage as:
-- The percentage of all queries with rating less than 3.
-- Write a solution to find each query_name, the quality and poor_query_percentage.
-- Both quality and poor_query_percentage should be rounded to 2 decimal places.


SELECT 
  query_name,
  ROUND(AVG(rating / position), 2) AS quality,
  ROUND(SUM(CASE WHEN rating <3 THEN 1 ELSE 0 END) / COUNT(*) * 100, 2) AS poor_query_percentage
FROM Queries
GROUP BY query_name;

-- Prices table:
-- +------------+------------+------------+--------+
-- | product_id | start_date | end_date   | price  |
-- +------------+------------+------------+--------+
-- | 1          | 2019-02-17 | 2019-02-28 | 5      |
-- | 1          | 2019-03-01 | 2019-03-22 | 20     |
-- | 2          | 2019-02-01 | 2019-02-20 | 15     |
-- | 2          | 2019-02-21 | 2019-03-31 | 30     |
-- +------------+------------+------------+--------+
-- UnitsSold table:
-- +------------+---------------+-------+
-- | product_id | purchase_date | units |
-- +------------+---------------+-------+
-- | 1          | 2019-02-25    | 100   |
-- | 1          | 2019-03-01    | 15    |
-- | 2          | 2019-02-10    | 200   |
-- | 2          | 2019-03-22    | 30    |

-- Write a solution to find the average selling price for each product. average_price should be rounded to 2 decimal places. 
--   If a product does not have any sold units, its average selling price is assumed to be 0.

SELECT 
  p.product_id,
  ROUND(
    IFNULL(SUM(price * units) / SUM(units), 0),
    2
  ) AS average_price
FROM Prices p
LEFT JOIN UnitsSold u
  ON p.product_id = u.product_id
  AND u.purchase_date BETWEEN p.start_date AND p.end_date
GROUP BY p.product_id;

-- IFNULL(a, b)	2	a if not NULL, else b
-- IFNULL(expression_to_check, value_if_null)


-- In SQL, NULL means "unknown" or "missing", and most math operations with NULL result in NULL.
-- ROUND(IFNULL(SUM(price * units) / SUM(units), 0), 2)
-- 



