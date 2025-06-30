-- Create a query to find active users who are returning. A person who has made at least two transactions within seven days is considered a returning active user. Provide a list of these returned active users' user_ids.
-- Order the output by user_id.

-- Table: transactions
-- |---|---------|-----------|------------|--------|
-- |id | user_id | item      | created_at | revenue|
-- |---|---------|-----------|------------|--------|
-- | 1 | 109     | milk      | 2020-03-03 | 123    |
-- | 2 | 139     | biscuit   | 2020-03-18 | 421    |
-- | 3 | 120     | milk      | 2020-03-18 | 176    |
-- | 4 | 108     | banana    | 2020-03-18 | 862    |
-- | 5 | 130     | milk      | 2020-03-28 | 333    |
-- | 6 | 109     | bread     | 2020-03-05 | 432    |
-- | 7 | 120     | biscuit   | 2020-03-21 | 858    |
-- | 8 | 130     | milk      | 2020-03-12 | 176    |
-- | 9 | 130     | bread     | 2020-03-09 | 149    |
-- |10 | 120     | milk      | 2020-03-27 | 793    |
-- |---|---------|-----------|------------|--------|

select u.user_id from  transactions as u join 
transactions as uu
on abs(datediff(u.created_at,uu.created_at))<7 and u.user_id=uu.user_id  and u.id!=uu.id
group by u.user_id having count(*)>=1 order by u.user_id ;

-- A company is managing its sales data and wants to analyze the total revenue generated from different product categories. 
--   Create a Common Table Expression (CTE) in SQL to calculate the total revenue for each product category in the "October" month of the year 2023.
with rev as(select Category,sum(SaleAmount) as TotalRevenue  from Sales where extract(month from SaleDate)=10 and year(SaleDate)=2023  group by Category )
select Category,TotalRevenue 
from rev 
order by Category;

-- You are an aspiring entrepreneur and are looking for the best business in several states to study their case study. 
-- List the top 5 states where the majority of businesses have received five stars. 
-- You have to find out the State name and the number of 5- star businesses in the state as "num_5_star_businesses",
-- and the results are sorted according to the number of 5- star firms in descending order. If there is a tie for the number of businesses in the different states,
-- return all separate states. If the results from two states are identical, order the states in ascending order.

-- Table: hulk_business
-- +--------------+----------------------------------+--------------+-------------------+-------------+-------+-------------+------------+-------------+-------+--------------+---------+-------------------------------------------+
-- | business_id  | name                             | neighborhood | address           | city        | state | postal_code | latitude   | longitude   | stars | review_count | is_open | categories                                |
-- +--------------+----------------------------------+--------------+-------------------+-------------+-------+-------------+------------+-------------+-------+--------------+---------+-------------------------------------------+
-- | 0jDvRJS-z9zd | Sunfare                         | NULL         | 811 W Deer Valley | Phoenix     | AZ    | 85027       | 33.683000  | -112.085000 | 5.0   | 27           | 1       | Personal Chefs;Food;Event Planning        |
-- | 57PSHmEDjQvd | Phoenix Water Damage Restoration | North Mountain | 2155 W Pinnacle  | Phoenix     | AZ    | 85027       | 33.711000  | -112.117000 | 5.0   | 7            | 1       | Home Services;Damage Restoration          |
-- | 8GHOIYD-XPjy | Cheerfully Made Goods + Markets | NULL         | 72 Mill St         | Almonte     | ON    | K0A 1A0     | 45.225000  | -76.190000  | 5.0   | 5            | 1       | Shopping;Gift Shops                       |
-- | eGBrr03fjCFE | Chandler AZ Handyman            | Chandler     | 4116 W Kitty Hawk  | Chandler    | AZ    | 85226       | 33.307000  | -112.006000 | 5.0   | 7            | 1       | Handyman;Home Services                    |
-- | JemtKt3WQZP6 | Just For You                    | Del Mar      | 13038 Del Mar St   | Garden Grove| CA    | 92841       | 33.769000  | -117.983000 | 5.0   | 12           | 1       | Convenience Stores;Shopping               |
-- | WdQP8kl9SzcO | Red Beard Bodywork              | Capitol      | 301 S Bedford St   | Madison     | WI    | 53703       | 43.066000  | -89.389000  | 5.0   | 10           | 1       | Health & Medical;Beauty & Spas            |
-- | vx9iHgEBP9Cy | Bella On The Avenue             | Scottsdale   | 6941 N Hayden Rd   | Scottsdale  | AZ    | 85250       | 33.531000  | -111.907000 | 5.0   | 46           | 1       | Hair Salons;Beauty & Spas                 |
-- | x-wvkn-JiPIU | Luvspun                         | NULL         | 1701 McElderry St  | Baltimore   | MD    | 21205       | 39.305000  | -76.586000  | 5.0   | 14           | 1       | Shopping;Thrift Stores                    |
-- | Z3RZmy8Lw6fs | Salerno by Celestino            | NULL         | 1780 N Goldenrod   | Orlando     | FL    | 32807       | 28.562000  | -81.276000  | 4.5   | 82           | 1       | Italian;Pizza;Restaurants                 |

select  state,count(*) as num_5_star_businesses from 
hulk_business 
where stars=5.0
group by  state
order by num_5_star_businesses desc,state asc
limit 5;

-- Retrieve the player_name and country of players with a batting_average greater than 35 and a bowling_average less than 25,
-- ordered by batting_average in descending order.

select  player_name ,country
from CricketPlayer
where 
batting_average>35.0 and
bowling_average<25.0

-- Retrieve the top 3 countries with the highest total runs scored by players from each country as "total_runs", ordered by total runs in descending order.

select country,sum(runs_scored) as total_runs  from CricketPlayer
group by country
order by total_runs desc
limit 3;

-- Write a SQL query to find the distinct product categories from the Sales table that have more than 5 sales transactions.
-- The query should return the product category and the count of sales transactions, 
-- grouped by category and filtered using the HAVING clause. Only include categories that start with the letter 'E'.

-- Tables Schema as Below:
-- Sales
-- columnName	dataType
-- id	int
-- product_name	varchar(100)
-- category	varchar(50)
-- sales_amount	decimal(15, 2)
-- sales_date	date

select category ,count(*) as sales_count  from Sales
where category like 'E%'
group by category
having count(id)>=5;

-- (Hard)
-- Assume you're given tables with information about TikTok user sign-ups and confirmations through email and text. 
-- New users on TikTok sign up using their email addresses, and upon sign-up, each user receives a text message confirmation to activate their account.
-- Write a query to display the user IDs of those who did not confirm their sign-up on the first day, but confirmed on the second day.

-- emails Example Input:
-- email_id	user_id	signup_date
-- 125	7771	06/14/2022 00:00:00
-- 433	1052	07/09/2022 00:00:00

-- texts Example Input:
-- text_id	email_id	signup_action	action_date
-- 6878	125	Confirmed	06/14/2022 00:00:00
-- 6997	433	Not Confirmed	07/09/2022 00:00:00
-- 7000	433	Confirmed	07/10/2022 00:00:00

select user_id from 
emails as e
join 
texts as t
on 
e.email_id=t.email_id 
and t.signup_action='Not Confirmed'
and date(e.signup_date)=date(t.action_date)
join 
texts as tt
on 
e.email_id=tt.email_id 
and tt.signup_action='Confirmed'
and date(tt.action_date)=date(e.signup_date+ interval 1 day)

--interval 1 day means 1+ days 

-- Write a query that outputs the name of each credit card and the difference in the number of issued cards between 
-- the month with the highest issuance cards and the lowest issuance. Arrange the results based on the largest disparity.

-- monthly_cards_issued Example Input:
-- card_name	issued_amount	issue_month	issue_year
-- Chase Freedom Flex	55000	1	2021
-- Chase Freedom Flex	60000	2	2021
-- Chase Freedom Flex	65000	3	2021
-- Chase Freedom Flex	70000	4	2021
-- Chase Sapphire Reserve	170000	1	2021
-- Chase Sapphire Reserve	175000	2	2021
-- Chase Sapphire Reserve	180000	3	2021

select card_name, (max(issued_amount)-min(issued_amount)) as difference  
from  monthly_cards_issued 
group by card_name
order by difference desc

-- You're trying to find the mean number of items per order on Alibaba, rounded to 1 decimal place using tables which 
-- includes information on the count of items in each order (item_count table) and the corresponding number of orders for each item count (order_occurrences table).

-- items_per_order Example Input:
-- item_count	order_occurrences
-- 1           	500
-- 2	          1000
-- 3          	800
-- 4	          1000

SELECT 
  ROUND(SUM(item_count * order_occurrences)::decimal / SUM(order_occurrences), 1) AS mean
FROM items_per_order;
-- NOTE
-- :: convert into decimal


