-- In other words, group the users by the number of tweets they posted in 2022 and count the number of users in each group.
-- tweets Table:
-- Column Name	Type
-- tweet_id	integer
-- user_id	integer
-- msg	string
-- tweet_date	timestamp

with count_no as ( select
user_id,count(*) as co 
  from tweets 
  where year(tweet_date)=2022
  group by user_id
)

select  co as tweet_bucket,count(user_id) as users_num 
from count_no 
group by co;



-- Write a query to list the candidates who possess all of the required skills for the job. Sort the output by candidate ID in ascending order.
-- Assumption:
-- There are no duplicates in the candidates table.
-- candidates Table:
-- Column Name	Type
-- candidate_id	integer
-- skill	varchar

select candidate_id 
from candidates 
where skill in ('Python','Tableau','PostgreSQL')
group by candidate_id
HAVING count(DISTINCT skill)=3;


-- Write a query to return the IDs of the Facebook pages that have zero likes. The output should be sorted in ascending order based on the page IDs.
-- pages Table:
-- Column Name	Type
-- page_id	integer
-- page_name	varchar
  
-- page_likes Table:
-- Column Name	Type
-- user_id	integer
-- page_id	integer
-- liked_date	datetime

select p.page_id 
from pages as p 
left join page_likes as l on l.page_id=p.page_id
where liked_date is null

-- Write a query that calculates the total viewership for laptops and mobile devices where mobile is defined as the sum of tablet and phone viewership. Output the total viewership for laptops as laptop_reviews and the total viewership for mobile devices as mobile_views.
-- viewership Example Input
-- user_id	device_type	view_time
-- 123	tablet	01/02/2022 00:00:00
-- 125	laptop	01/07/2022 00:00:00
-- 128	laptop	02/09/2022 00:00:00
-- 129	phone	02/09/2022 00:00:00
-- 145	tablet	02/24/2022 00:00:00

select count(case when device_type='laptop'  then 1 end) as laptop_views,
-- else case aur sab jagah null kar dega and count non null value ko count karta hai
count(case when device_type='tablet'  then 1 when 
device_type='phone'  then 1 end) as mobile_views 
  from viewership;



-- Given a table of Facebook posts, for each user who posted at least twice in 2021, write a query to find the number of days between each user’s first post of the year and last post of the year in the year 2021. Output the user and number of the days between each user's first and last post.
-- p.s. If you've read the Ace the Data Science Interview and liked it, consider writing us a review?
-- posts Table:
-- Column Name	Type
-- user_id	integer
-- post_id	integer
-- post_content	text
-- post_date	timestamp

SELECT 
  p.user_id, 
  DATEDIFF(MAX(p.post_date), MIN(pp.post_date)) 
FROM posts AS p 
JOIN posts AS pp 
  ON p.user_id = pp.user_id 
WHERE 
  YEAR(p.post_date) = 2021
  AND YEAR(pp.post_date) = 2021
GROUP BY p.user_id
HAVING COUNT(DISTINCT p.post_id) >= 2;

or
-- SELECT 
--   p.user_id,
--   DATEDIFF(MAX(p.post_date), MIN(p.post_date)) AS days_between
-- FROM posts AS p
-- WHERE YEAR(p.post_date) = 2021
-- GROUP BY p.user_id
-- HAVING COUNT(*) >= 2;

-- Write a query to identify the top 2 Power Users who sent the highest number of messages on Microsoft Teams in August 2022. Display the IDs of these 2 users along with the total number of messages they sent. Output the results in descending order based on the count of the messages.
-- No two users have sent the same number of messages in August 2022.
-- messages Table:
-- Column Name	Type
-- message_id	integer
-- sender_id	integer
-- receiver_id	integer
-- content	varchar
-- sent_date	datetime

select sender_id,count(distinct extract(month from sent_date)) as message_count from messages 
group by sender_id
ORDER BY message_count desc
limit 2;

-- NOTE
-- In GROUP BY, all rows with the same value are grouped together(ek sath aaja ta hai), and aggregate functions work on that group.

-- Assume you're given a table containing job postings from various companies on the LinkedIn platform. Write a query to retrieve the count of companies that have posted duplicate job listings.
-- Definition:
-- Duplicate job listings are defined as two job listings within the same company that share identical titles and descriptions.
-- job_listings Table:
-- Column Name	Type
-- job_id	integer
-- company_id	integer
-- title	string
-- description	string

with count_no as 
(select company_id,count(*) as num from job_listings group by company_id )
select count(*) as duplicate_companies
from count_no 
where num>=2


-- Write a query to retrieve the top three cities that have the highest number of completed trade orders listed in descending order. Output the city name and the corresponding number of completed trade orders.
-- trades Table:
-- Column Name	Type
-- order_id	integer
-- user_id	integer
-- quantity	integer
-- status	string ('Completed', 'Cancelled')
-- date	timestamp
-- price	decimal (5, 2)

-- users Table:
-- Column Name	Type
-- user_id	integer
-- city	string
-- email	string
-- signup_date	datetime
-- users Example Input:
-- user_id	city	email	signup_date

select u.city,count(*) as total_orders 
from trades as t 
inner join 
users as u 
on u.user_id=t.user_id
where 
t.status='Completed' group by u.city order by total_orders desc limit 3t.
