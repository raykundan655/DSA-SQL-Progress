-- Write a query to identify the stores having score below 5. Output will be the customer_ids. DataFrame/SQL Table with the following schema -
-- Tables Schema as Below:

-- instacart_reviews
-- columnName	dataType
-- id	int64
-- customer_id	int64
-- store_id	int64
-- score	int64

select customer_id from 
instacart_reviews 
where 
score<5;


-- Find the number of posts that had a response of like. Print the total number of similar posts. DataFrame/SQL Table with the following schema -
-- Tables Schema as Below:

-- facebook_reactions
-- columnName	dataType
-- poster	int64
-- friend	int64
-- reaction	object
-- date_day	int64
-- post_id	int64
  
-- facebook_posts
-- columnName	dataType
-- post_id	int64
-- poster	int64
-- post_text	object
-- post_keywords	object
-- post_date	datetime64

SELECT count(distinct p.post_id) as  n_posts_with_a_like 
FROM facebook_posts AS p
JOIN facebook_reactions AS r ON p.post_id = r.post_id
WHERE r.reaction = 'like'

-- Find the number of hosts that have accommodations in countries of which they are not citizens.
-- Tables Schema as Below:
-- airbnb_hosts
-- columnName	dataType
-- host_id	int64
-- nationality	object
-- gender	object
-- age	int64
  
-- airbnb_apartments
-- columnName	dataType
-- host_id	int64
-- apartment_id	object
-- apartment_type	object
-- n_beds	int64
-- n_bedrooms	int64
-- country	object
-- city	object

select count(distinct a.host_id) as host  
from airbnb_hosts as a 
left join
airbnb_apartments as aa  
on a.host_id =aa.host_id 
where a.nationality !=aa.country

-- Write a SQL query to find the employees who make more than their managers. You must print the employee's first name as "employee_name" along with their corresponding salary as "employee_salary"  from the table - employee. DataFrame/SQL Table with the following schema -
-- Tables Schema as Below:
-- employee
-- columnName	dataType
-- id	int64
-- first_name	object
-- last_name	object
-- age	int64
-- sex	object
-- employee_title	object
-- department	object
-- salary	int64
-- target	int64
-- bonus	int64
-- email	object
-- city	object
-- address	object
-- manager_id	int64

select e.first_name,e.salary from  employees as e
join  employees as ee 
on
e.manager_id =ee.id 
and e.salary>ee.salary;

-- Find the number of transactions for each product. Output the product name along with the corresponding number of transactions and order records by the product id in ascending order. You can ignore products without transactions.
-- Tables Schema as Below:

-- excel_sql_inventory_data
-- columnName	dataType
-- product_id	INT
-- product_name	VARCHAR(255)
-- product_type	VARCHAR(255)
-- unit	VARCHAR(10)
-- price_unit	DECIMAL(10,2)
-- wholesale	DECIMAL(10,2)
-- current_inventory	INT
  
-- excel_sql_transaction_data
-- columnName	dataType
-- transaction_id	INT
-- time	VARCHAR(19)
-- product_id	INT

SELECT ee.product_name, COUNT(e.transaction_id) AS transaction_count
FROM excel_sql_inventory_data AS ee
JOIN excel_sql_transaction_data AS e 
  ON e.product_id = ee.product_id
GROUP BY ee.product_id, ee.product_name
ORDER BY ee.product_id;
