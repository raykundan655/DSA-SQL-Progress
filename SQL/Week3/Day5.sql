-- Find departments with at least five employees. Print department. 
select department 
from employee
group by department
having count(id)>=5;

-- Determine the maximum steps that can be reached for each feature. The output should include the feature ID and its corresponding maximum step.DataFrame/SQL Table with the following schema -

-- Tables Schema as Below:
-- facebook_product_features_realizations
-- columnName	dataType
-- feature_id	int64
-- user_id	int64
-- step_reached	int64
-- timestamp	datetime64[ns

SELECT feature_id, MAX(step_reached) AS max_step_reached
FROM facebook_product_features_realizations
GROUP BY feature_id;

-- Identify the actions from the web log that happened more than once. Print actions that were repeated. DataFrame/SQL Table with the following schema -

-- Tables Schema as Below:
-- facebook_web_log
-- columnName	dataType
-- user_id	int64
-- timestamp	datetime64[ns]
-- action	object


with count_no as(select action,count(*) as dup from facebook_web_log group by action )
select action from count_no where dup>1;

-- or
select action from facebook_web_log group by action   having count(*)>1;

-- Find all emails with duplicates. Print email.
select email 
from employee
group by email 
having count(*)>1;

-- Calculate the average number of friend requests sent by users during the second week of December 2021 (i.e. between '2021-12-06' AND '2021-12-12') . DataFrame/SQL Table with the following schema -

-- Tables Schema as Below:
-- fb_requests
-- columnName	dataType
-- sender_id	object
-- receiver_id	object
-- sent_date	datetime64[ns]
-- is_accepted	bool

with req_no as(select sender_id ,count(*) as req from 
fb_requests
where sent_date  between '2021-12-06' and  '2021-12-12'
group by sender_id)

select avg(req) as avg_messages from req_no;

-- Find an employee with the highest salary per department. Output the department name of the employee's first name along with the corresponding salary.
-- Table Name: employee
-- +----+------------+-----------+-----+-----+-----------------+-------------+--------+--------+-------+--------------------+----------+-------------------+------------+
-- | id | first_name | last_name | age | sex | employee_title  | department  | salary | target | bonus | email              | city     | address           | manager_id |
-- +----+------------+-----------+-----+-----+-----------------+-------------+--------+--------+-------+--------------------+----------+-------------------+------------+
-- | 13 | Katty      | Bond      |  56 |  F  | Manager         | Management  | 150000 |   0    |   300 | Katty@company.com  | Arizona  | None              |     1      |
-- | 11 | Richerd    | Gear      |  57 |  M  | Manager         | Management  | 250000 |   0    |   300 | Richerd@company.com| Alabama  | None              |     1      |
-- | 18 | Laila      | Mark      |  26 |  F  | Sales           | Sales       | 1000   |  200   |   150 | Laila@company.com  | Florida  | 3655 Spirit Drive |     11     |
-- |  6 | Molly      | Sam       |  28 |  F  | Sales           | Sales       | 1400   |  100   |   150 | Molly@company.com  | Arizona  | 3632 Polk Street  |     13     |
-- | 17 | Mick       | Berry     |  44 |  M  | Senior Sales    | Sales       | 2200   |  200   |   150 | Mick@company.com   | Florida  | None              |     11     |
-- +----+------------+-----------+-----+-----+-----------------+-------------+--------+--------+-------+--------------------+----------+-------------------+------------+

select department , first_name as employee_name, salary 
from employee as e 
  -- row waise selection
where salary=(select max(salary) from employee where department=e.department )

-- Find the number of transactions for each product. Output the product name along with the corresponding number of transactions and order records by the product id in ascending order. You can ignore products without transactions.
-- Tables Schema as Below:
-- excel_sql_inventory_data
-- columnName	dataType
-- product_id	INT
-- product_name	VARCHAR(50)
-- product_type	VARCHAR(50)
-- unit	VARCHAR(50)
-- price_unit	VARCHAR(50)
-- wholesale	VARCHAR(50)
-- current_inventory	INT
  
-- excel_sql_transaction_data
-- columnName	dataType
-- transaction_id	INT
-- time	VARCHAR(50)
-- product_id	INT

SELECT 
    p.product_name,
    COUNT(*) AS transaction_count
FROM excel_sql_inventory_data AS p
JOIN excel_sql_transaction_data AS t
    ON p.product_id = t.product_id
GROUP BY p.product_id, p.product_name
ORDER BY p.product_id;

-- Given the reviews table, write a query to retrieve the average star rating for each product, grouped by month. The output should display the month as a numerical value, product ID, and average star rating rounded to two decimal places. Sort the output first by month and then by product ID.
-- reviews Table:
-- Column Name	Type
-- review_id	integer
-- user_id	integer
-- submit_date	datetime
-- product_id	integer
-- stars	integer (1-5)

select extract(month from submit_date) as mm ,product_id as product,
round(avg(stars),2) as avg_stars 
from reviews
group by mm,product_id;

-- Companies often perform salary analyses to ensure fair compensation practices. One useful analysis is to check if there are any employees earning more than their direct managers.
-- As a HR Analyst, you're asked to identify all employees who earn more than their direct managers. The result should include the employee's ID and name.

-- employee Schema:
-- column_name	type	description

-- employee_id	integer	The unique ID of the employee.
-- name	string	The name of the employee.
-- salary	integer	The salary of the employee.
-- department_id	integer	The department ID of the employee.
-- manager_id	integer	The manager ID of the employee.

select e.employee_id,	e.name as employee_name 
from employee as e join  
employee as ee on
e.manager_id=ee.employee_id where e.salary>ee.salary;


-- This is the same question as problem #1 in the SQL Chapter of Ace the Data Science Interview!
-- Assume you have an events table on Facebook app analytics. Write a query to calculate the click-through rate (CTR) for the app in 2022 and round the results to 2 decimal places.

-- Percentage of click-through rate (CTR) = 100.0 * Number of clicks / Number of impressions
-- To avoid integer division, multiply the CTR by 100.0, not 100.

-- events Table:
-- Column Name	Type
-- app_id	integer
-- event_type	string
-- timestamp	datetime


WITH count_no AS (
    SELECT 
        app_id,
        COUNT(CASE WHEN event_type = 'impression' THEN 1 END) AS im,
        COUNT(CASE WHEN event_type = 'click' THEN 1 END) AS cl
    FROM events
    WHERE YEAR(timestamp) = 2022
    GROUP BY app_id
)
SELECT 
    app_id,
    ROUND(100.0 * cl / NULLIF(im, 0), 2) AS ctr
FROM count_no;






