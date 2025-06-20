
-- recipe1
-- columnName	dataType
-- grocery	VARCHAR(255)
-- mass	INTEGER

-- recipe2
-- columnName	dataType
-- grocery	VARCHAR(255)
-- mass	INTEGER
-- recipe3
-- columnName	dataType
-- grocery	VARCHAR(255)
-- mass	INTEGER

-- List the top 3 groceries from recipe 1 with the highest mass (according to recipe 1). Also, show the corresponding masses from recipe 2 and recipe 3 for each grocery in the same result set.
-- Result grocery, mass, mass_recipe2, and mass_recipe3. Order the results by mass (of recipe 1) in descending order.

select r.grocery,sum(r.mass) as mass ,sum(r2.mass) as mass_recipe2,sum(r3.mass) as mass_recipe3 from 
recipe1 as r  left join recipe2 as r2 on r.grocery=r2.grocery left join recipe3  as r3 on r.grocery=r3.grocery
 group by r.grocery  ORDER BY sum(r.mass) desc
limit 3;


-- Calculate the number of <code>apartment</code> buildings per nationality that belong to people under 30 years old. Output the nationality along with the number of apartments as "apartment_count". Sort entries by apartment count in descending order.

-- Tables Schema as Below:

-- airbnb_units
-- columnName	dataType
-- host_id	INT
-- unit_id	VARCHAR(10)
-- unit_type	VARCHAR(50)
-- n_beds	INT
-- n_bedrooms	INT
-- country	VARCHAR(50)
-- city	VARCHAR(50)

-- airbnb_hosts
-- columnName	dataType
-- host_id	INT
-- nationality	VARCHAR(50)
-- gender	VARCHAR(1)
-- age	INT

select  nationality ,count(*) apartment_count  from airbnb_units as a inner join airbnb_hosts as aa on a.host_id=aa.host_id where 
unit_type='Apartment' and age<30 group by nationality order by apartment_count desc;

-- Create a query to find active users who are returning. A person who has made at least two transactions within seven days is considered a returning active user. Provide a list of these returned active users' user_ids.
--  Order the output by user_id

select t.user_id  from transactions as t join transactions as tt on t.user_id=tt.user_id  AND t.created_at > tt.created_at and datediff(t.created_at,tt.created_at)<7 
group by t.user_id having count(*)>=1 ORDER BY t.user_id;

-- Find all posts that were reacted to with a <code>heart</code>. For such posts output all columns and distinct rows from the posts table.
select distinct p.post_id,p.poster,p.post_text,p.post_keywords,p.post_date from posts as p inner join 
reactions as rr on p.post_id=rr.post_id where rr.reaction='heart';



-- Imagine you are a database analyst working for an online bookstore. 
-- Your bookstore offers a wide selection of books, and customers can leave reviews for the books they've read. The bookstore has a database with two tables:
-- Tables Schema as Below:

-- book
-- columnName	dataType
-- id	INT
-- author_id	INT
-- title	VARCHAR(255)
-- publish_year	INT
-- publishing_house	VARCHAR(255)
-- rating	DECIMAL(3,2)
  
-- book_review
-- columnName	dataType
-- book_id	INT
-- review	TEXT
-- author	VARCHAR(255)

-- Your manager has asked you to retrieve information about all the books, 
-- including their reviews and review author names, even if a book hasn't been reviewed yet. 
--   This is valuable because it allows the bookstore to provide a comprehensive list of books to customers, 
--   along with any available reviews. It also helps in marketing books and encouraging customers to leave more reviews.


select   b.title   , r.review , r.author from book as b left join book_review as r on b.id=r.book_id;

-- Write a SQL query to find the "player_name, " "country, " and "batting_style" of players and assign the category based on their "batting_average" as follows:
--   "Great Batsman" for players with a "batting_average" greater than 50.00, "Good Batsman" for players with a "batting_average" between 40.00 and 50.00 (inclusive),
--   "Average Batsman" for players with a "batting_average" between 30.00 and 39.99 (inclusive), and "Below Average Batsman" for players with a "batting_average"
--   lower than 30.00. Sort the players based on their "batting_average" in descending order.

SELECT  
    p.player_name,
    t.country,
    p.batting_style,
    CASE 
        WHEN p.batting_average > 50.00 THEN 'Great Batsman'
        WHEN p.batting_average BETWEEN 40.00 AND 50.00 THEN 'Good Batsman'
        WHEN p.batting_average BETWEEN 30.00 AND 39.99 THEN 'Average Batsman'
        ELSE 'Below Average Batsman'
    END AS category
FROM 
    CricketPlayer AS p
LEFT JOIN 
    Team AS t ON p.player_id = t.player_id
ORDER BY 
    p.batting_average DESC;

-- Your task is to write an SQL query that retrieves player names and 
--   their corresponding country codes. For players from 'Australia', 
--   the country code should be 'AUS'. For players from other countries, take the first three letters of the country name as the country code.
--   Additionally, filter the results to include only players who have played more than 150 matches and have a batting average greater than 40.
-- Tables Schema as Below:

SELECT 
    p.player_name,
    CASE 
        WHEN p.country = 'Australia' THEN 'AUS'
        ELSE 
           concat( UPPER(SUBSTR(p.country, 1, 1)), LOWER(SUBSTR(p.country, 2, 2)))
    END AS country_code
FROM 
    CricketPlayer AS p
WHERE 
    p.matches_played > 150
    AND p.batting_average > 40.00;

