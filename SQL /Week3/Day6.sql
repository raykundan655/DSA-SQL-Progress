-- Imagine you are managing a database for a bookstore. The table book_sales contains information about sales transactions. Each row represents a sale, including the book's title, the quantity sold, the sale date, and the total revenue generated. Your task is to write a query to display,book_title, total quantity sold as "total_quantity_sold"
-- and average revenue per book as "average_revenue_per_book",
-- retrieve the books that have a total quantity sold greater than 50 and an average revenue per book greater than $15.
-- The average Revenue generated should be rounded to two decimal places.
-- Output the results in descending order of average revenue per book.

-- +---------+-----------------------------+---------------+------------+---------------+
-- | sale_id | book_title                  | quantity_sold | sale_date  | total_revenue |
-- +---------+-----------------------------+---------------+------------+---------------+
-- |   1     | The Great Gatsby           |      25       | 2023-01-15 |      350      |
-- |   2     | To Kill a Mockingbird      |      35       | 2023-02-02 |      600      |
-- |   3     | 1984                       |      20       | 2023-02-10 |      200      |
-- |   4     | Bestseller                 |      55       | 2023-03-05 |      850      |
-- |   5     | Top Revenue Book           |      80       | 2023-03-20 |     2200      |
-- |   6     | Lord of the Flies          |      40       | 2023-04-15 |      480      |
-- |   7     | High Demand Novel          |      65       | 2023-05-02 |      970      |
-- |   8     | Blockbuster Series         |      90       | 2023-06-15 |     2700      |
-- +---------+-----------------------------+---------------+------------+---------------+

select book_title , quantity_sold as total_quantity_sold ,
round((total_revenue/ quantity_sold),2) as average_revenue_per_book
from 
book_sales
where quantity_sold>50 and 
total_revenue/ quantity_sold >15
order by average_revenue_per_book desc;

-- Your task is to craft a SQL query that retrieves the most 
-- recent time at which somebody returned any bike(most recently returned timestamp)
-- and presents the results in descending order based on most_recent_return_timestamp.

-- trip_data
-- columnName	dataType
-- duration	VARCHAR(20)
-- duration_seconds	INT
-- start_time	DATETIME
-- start_station	VARCHAR(255)
-- start_terminal	INT
-- end_time	DATETIME
-- end_station	VARCHAR(255)
-- end_terminal	INT
-- bike_number	VARCHAR(20)
-- rider_type	VARCHAR(20)
-- id	INT

select bike_number,max(end_time ) as  most_recent_return_timestamp from  trip_data
group by bike_number
order by max(end_time) desc;


-- List the names of players from Pakistan and Bangladesh who have scored less than 1000 runs.
-- Tables Schema as Below:

-- CricketPlayer
-- columnName	dataType
-- player_id	INTEGER
-- player_name	TEXT
-- country	TEXT
-- batting_style	TEXT
-- bowling_style	TEXT
-- matches_played	INTEGER
-- runs_scored	INTEGER
-- wickets_taken	INTEGER
-- batting_average	DECIMAL(5, 2)
-- bowling_average	DECIMAL(5, 2)

-- Team
-- columnName	dataType
-- team_id	INTEGER
-- team_name	TEXT
-- country	TEXT
-- coach	TEXT
-- captain	TEXT
-- player_id	INTEGER

select p.player_name  ,p.country ,p.runs_scored 
from CricketPlayer  as p
left join 
Team as t
on p.player_id=t.player_id
where (p.country='Bangladesh' or p.country='Pakistan') and p.runs_scored<1000;


-- Retrieve a list of customer cities where the customers have a grade of 2. 
-- For each city, calculate the total opening amount, the average receive amount, and the maximum payment amount.
-- Only include cities where the average receive amount for the customers in that city exceeds 500. Finally, 
-- sort the results in ascending order based on the total opening amount.

SELECT 
    CUST_CITY, 
    SUM(OPENING_AMT) AS "SUM(OPENING_AMT)", 
    ROUND(AVG(RECEIVE_AMT), 2) AS "AVG(RECEIVE_AMT)", 
    MAX(PAYMENT_AMT) AS "MAX(PAYMENT_AMT)"
FROM 
    Customers
WHERE 
    GRADE = 2
GROUP BY 
    CUST_CITY
HAVING 
    AVG(RECEIVE_AMT) > 500
ORDER BY 
    SUM(OPENING_AMT) ASC;

-- Write a SQL query to find the top 5 players with the highest batting averages, along with their player_name and batting_average.
-- Tables Schema as Below:
  
-- CricketPlayer
-- columnName	dataType
-- player_id	INTEGER
-- player_name	TEXT
-- country	TEXT
-- batting_style	TEXT
-- bowling_style	TEXT
-- matches_played	INTEGER
-- runs_scored	INTEGER
-- wickets_taken	INTEGER
-- batting_average	DECIMAL(5, 2)
-- bowling_average	DECIMAL(5, 2)

select  player_name , batting_average 
from  CricketPlayer  
order by batting_average desc 
limit 5;

-- Determine the count of songs each person has in a table containing information about individuals (person_id) and the songs they have, effectively calculating the number of songs per person in the database.
-- Tables Schema as Below:

-- person_songs
-- columnName	dataType
-- person_id	INT
-- song_name	VARCHAR(100)

select person_id,count(*) as song_count from person_songs
group by person_id;

-- Find the average weight of medal- winning Judo players of each team with a minimum age of 20 and a maximum age of 30.
-- It is often discussed that players are in their 20s and 30s too. Output the team along with the average player's weight.Order the results by average_player_weight.

-- +----+--------------------+-----+-----+--------+---------+----------+-----+--------------+------+--------+---------+-----------+----------+-------+
-- | id | name               | sex | age | height | weight  | team     | noc | games        | year | season | city   | sport     | event    | medal |
-- +----+--------------------+-----+-----+--------+---------+----------+-----+--------------+------+--------+---------+-----------+----------+-------+
-- |  1 | John Doe           | M   | 25  | 180.00 | 75.00   | TeamA    | NOC1| Summer Games | 2022 | Summer | CityA  | Athletics | 100m     | Gold  |
-- |  2 | Jane Smith         | F   | 22  | 165.00 | 60.00   | TeamB    | NOC2| Winter Games | 2022 | Winter | CityB  | Judo      | Downhill | Silver|
-- |  3 | Bob Johnson        | M   | 28  | 175.00 | 80.00   | TeamC    | NOC3| Summer Games | 2022 | Summer | CityA  | Swimming  | Freestyle| Bronze|
-- |  4 | Alice Brown        | F   | 24  | 160.00 | 55.00   | TeamD    | NOC4| Winter Games | 2022 | Winter | CityB  | Snowboarding| Halfpipe| Gold  |
-- |  5 | Mike Green         | M   | 30  | 185.00 | 90.00   | TeamE    | NOC5| Summer Games | 2022 | Summer | CityA  | Basketball| 3x3      | Silver|
-- |  6 | Sara White         | F   | 26  | 170.00 | 70.00   | TeamF    | NOC6| Winter Games | 2022 | Winter | CityB  | Ice Hockey| Individual| Bronze|
-- +----+--------------------+-----+-----+--------+---------+----------+-----+--------------+------+--------+---------+-----------+----------+-------+

select team ,avg(weight) as average_player_weight
from olympics_athletes_events
where sport='Judo'
and (age>=20 and age<=30)
group by team
order by average_player_weight

-- Write a query to find all tweets which are retweeted atleast 2 times. Resulting table should contains tweet_id and count of retweets as retweet_count
-- Table: UserTweetRelation
-- +----+---------------------+--------+---------+----------+
-- | id | created_at          | retweet| user_id | tweet_id |
-- +----+---------------------+--------+---------+----------+
-- |  1 | 2022-06-05 00:00:00 |   1    |   13    |    23    |
-- |  2 | 2021-07-23 00:00:00 |   1    |   30    |    23    |
-- |  3 | 2021-07-29 00:00:00 |   1    |   16    |    56    |
-- |  4 | 2021-09-28 00:00:00 |   1    |    4    |    56    |
-- |  5 | 2022-04-26 00:00:00 |   0    |   35    |    12    |
-- |  6 | 2021-07-05 00:00:00 |   1    |   42    |    13    |
-- +----+---------------------+--------+---------+----------+

select  tweet_id,count(*) as retweet_count  from UserTweetRelation WHERE 
retweet = 1
group by tweet_id having 
retweet_count >=2;

