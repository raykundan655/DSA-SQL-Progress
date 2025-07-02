-- Write a query to find the top 3 most profitable drugs sold, and how much profit they made. Assume that there are no ties in the profits.
-- Display the result from the highest to the lowest total profit.
-- Definition:
-- cogs stands for Cost of Goods Sold which is the direct cost associated with producing the drug.
-- Total Profit = Total Sales - Cost of Goods Sold

-- pharmacy_sales Example Input:
-- product_id	units_sold	total_sales	   cogs                 	manufacturer    	drug
-- 9	           37410   	293452.54      	208876.01	                Eli Lilly  	  Zyprexa
-- 34	         94698	  600997.19    	521182.16	             AstraZeneca	  Surmontil
-- 61          	77023	  500101.61   	419174.97	              Biogen	       Varicose Relief
-- 136         	144814	 1084258   	1006447.73            	Biogen	       Burkhart

select drug ,total_sales-cogs as total_profit
from pharmacy_sales
order by total_profit desc limit 3;

-- CVS Health is analyzing its pharmacy sales data, and how well different products are selling in the market. Each drug is exclusively manufactured by a single manufacturer.
-- Write a query to identify the manufacturers associated with the drugs that resulted in losses for CVS Health and calculate the total amount of losses incurred.
-- Output the manufacturer's name, the number of drugs associated with losses, and the total losses in absolute value. Display the results sorted in descending order with the highest losses displayed at the top.
-- pharmacy_sales Table:
-- Column Name	Type
-- product_id	integer
-- units_sold	integer
-- total_sales	decimal
-- cogs	decimal
-- manufacturer	varchar
-- drug	varchar

-- cogs->cost of goods sale->manufacturing cost
select manufacturer,count(*),abs(sum(cogs)-sum(total_sales)) as total_loss from 
pharmacy_sales
where total_sales<cogs
group by manufacturer 
order by total_loss desc;

-- Write a query to calculate the total drug sales for each manufacturer.
-- Round the answer to the nearest million and report your results in descending order of total sales. 
-- In case of any duplicates, sort them alphabetically by the manufacturer name.
-- Since this data will be displayed on a dashboard viewed by business stakeholders, please format your results as follows: "$36 million".

SELECT 
    manufacturer,
    CONCAT('$', CEILING(SUM(total_sales) / 1000000), ' million') AS sales_mil
FROM 
    pharmacy_sales 
GROUP BY 
    manufacturer
ORDER BY 
    SUM(total_sales) DESC,
    manufacturer ASC;

-- Write a query to find how many UHG policy holders made three, or more calls, assuming each call is identified by the case_id column.
-- callers Table:
-- Column Name	Type
-- policy_holder_id	integer
-- case_id	varchar
-- call_category	varchar
-- call_date	timestamp
-- call_duration_secs	integer

SELECT 
    COUNT(*) AS policy_holder_count
FROM (
    SELECT 
        policy_holder_id
    FROM 
        callers
    GROUP BY 
        policy_holder_id
    HAVING 
        COUNT(*) >= 3
) AS sub;

-- Consider a table named Teams with columns TeamName and CoachName. Write a SQL query to retrieve the team name along with the first and last names of coach's name.
--   If a coach has middle names as well, consider only the first and last names. Ensure that the first and last names are capitalized and separated by dots.

-- Table: Teams
-- +-------------------+----------------------+
-- | TeamName          | CoachName            |
-- +-------------------+----------------------+
-- | Manchester United | Alex Sid Ferguson    |
-- | Real Madrid       | Zinedine Zidane      |
-- | FC Barcelona      | Pep Guardiola        |
-- | Liverpool FC      | Jurgen Klopp         |
-- | Bayern Munich     | Hansi Flick          |
-- +-------------------+----------------------+

SELECT 
    TeamName,
    CONCAT(
        UPPER(SUBSTRING_INDEX(CoachName, ' ', 1)),
        '.',
        UPPER(SUBSTRING_INDEX(CoachName, ' ', -1))
    ) AS CoachInitials
FROM 
    Teams
ORDER BY 
    TeamName;

-- NOTE
-- SUBSTRING_INDEX return the part of string  befor occuring delimeter ->if you check from last then last part will get befor occuring of delimater

-- Write a query that returns the distinct customer IDs, first names, and the lowest order cost per customer . DataFrame/SQL Table with the following schema -

-- Table Name: customers
-- +----+-----------+----------+---------------+--------+--------------+
-- | id | first_name| last_name| city          |address | phone_number |
-- +----+-----------+----------+---------------+--------+--------------+
-- | 8  | John      | Joseph   | San Francisco | None   | 928-386-8164 |
-- | 7  | Jill      | Michael  | Austin        | None   | 813-297-0692 |
-- | 4  | William   | Daniel   | Denver        | None   | 813-368-1200 |
-- | 5  | Henry     | Jackson  | Miami         | None   | 808-601-7513 |
-- | 13 | Emma      | Isaac    | Miami         | None   | 808-690-5201 |

-- Table Name: orders
-- +----+---------+---------------------+---------------+------------------+
-- | id | cust_id | order_date          | order_details | total_order_cost |
-- +----+---------+---------------------+---------------+------------------+
-- | 13 | 12      | 2019-03-11 00:00:00 | Slipper       | 20               |
-- | 14 | 4       | 2019-02-01 00:00:00 | Shoes         | 80               |
-- | 15 | 4       | 2019-01-11 00:00:00 | Shirts        | 60               |
-- | 16 | 3       | 2019-04-19 00:00:00 | Shirts        | 50               |
-- | 17 | 7       | 2019-04-19 00:00:00 | Suit          | 150              |

select c.id as  cust_id  ,c.first_name,min(o.total_order_cost) as lowest_price 
from customers as c 
join orders as o 
on o.cust_id =c.id
group by 
c.id,c.first_name
order by c.id;

-- Find the details of the order made by Jill and Eva. Consider Jill and Eva as the first name of the customers. From the given dataset, 
-- extract the order details, order dates, and total costs for customers named Jill and Eva. Consider Jill and Eva as the first names in the dataset.

select c.first_name , o.order_date ,o.order_details ,o.total_order_cost from 
customers as c join 
orders as o 
on
c.id=o.cust_id
where first_name='Jill' or first_name='Eva'

