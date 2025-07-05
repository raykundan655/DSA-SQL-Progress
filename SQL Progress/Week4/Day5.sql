-- Table: Employee
-- +--------------+---------+
-- | Column Name  | Type    |
-- +--------------+---------+
-- | id           | int     |
-- | name         | varchar |
-- | salary       | int     |
-- | departmentId | int     |
-- +--------------+---------+
-- id is the primary key (column with unique values) for this table.
-- departmentId is a foreign key (reference columns) of the ID from the Department table.
-- Each row of this table indicates the ID, name, and salary of an employee. It also contains the ID of their department.

-- Table: Department
-- +-------------+---------+
-- | Column Name | Type    |
-- +-------------+---------+
-- | id          | int     |
-- | name        | varchar |
-- +-------------+---------+
-- id is the primary key (column with unique values) for this table. It is guaranteed that department name is not NULL.
-- Each row of this table indicates the ID of a department and its name.

-- Write a solution to find employees who have the highest salary in each of the departments.
-- # Write your MySQL query statement below

select  d.name as Department ,e.name as Employee  ,e.salary as Salary from 
Employee as e  join Department as d on e.departmentId =d.id
where(e.departmentId, e.salary) in (select departmentId, MAX(salary) from Employee group by departmentId)

-- Note Yes — after performing a JOIN, you can treat the result like a single table in your SQL query.

-- Table: Person
-- +-------------+---------+
-- | Column Name | Type    |
-- +-------------+---------+
-- | id          | int     |
-- | email       | varchar |
-- +-------------+---------+
-- id is the primary key (column with unique values) for this table.
-- Each row of this table contains an email. The emails will not contain uppercase letters.
--  Write a solution to delete all duplicate emails, keeping only one unique email with the smallest id.
-- For SQL users, please note that you are supposed to write a DELETE statement and not a SELECT one.
-- For Pandas users, please note that you are supposed to modify Person in place.

-- NOTE
-- delete from Person where id not in (select min(id) from Person group by  email );
-- "You can't specify target table 'Person' for update in FROM clause"
-- This happens because you're trying to delete from the same table (Person) that you're selecting from in the subquery — MySQL doesn't allow this directly.
-- "Jis table mein DELETE kar rahe hain, usi table se directly SELECT nahi kar sakte inside subquery."

delete from Person
where id not in (select  id  from (select min(id) as id from Person group by  email ) as temp
);

-- Table: Weather
-- +---------------+---------+
-- | Column Name   | Type    |
-- +---------------+---------+
-- | id            | int     |
-- | recordDate    | date    |
-- | temperature   | int     |
-- +---------------+---------+
-- id is the column with unique values for this table.
-- There are no different rows with the same recordDate.
-- This table contains information about the temperature on a certain day.
--  Write a solution to find all dates' id with higher temperatures compared to its previous dates (yesterday).


SELECT w.id FROM
Weather as w join Weather  as ww on datediff(w.recordDate,ww.recordDate)=1 and ww.temperature<w.temperature;

-- Table: Activity
-- +--------------+---------+
-- | Column Name  | Type    |
-- +--------------+---------+
-- | player_id    | int     |
-- | device_id    | int     |
-- | event_date   | date    |
-- | games_played | int     |
-- +--------------+---------+
-- (player_id, event_date) is the primary key (combination of columns with unique values) of this table.
-- This table shows the activity of players of some games.
-- Each row is a record of a player who logged in and played a number of games (possibly 0) before logging out on someday using some device.
--  Write a solution to find the first login date for each player.

select player_id,min(event_date) as first_login  from 
Activity
group by player_id;
-- or
select player_id,event_date as first_login from Activity  as a 
where event_date=(select min(event_date) from Activity where   player_id =a. player_id)

-- Table: Activity
-- +--------------+---------+
-- | Column Name  | Type    |
-- +--------------+---------+
-- | player_id    | int     |
-- | device_id    | int     |
-- | event_date   | date    |
-- | games_played | int     |
-- +--------------+---------+
-- (player_id, event_date) is the primary key (combination of columns with unique values) of this table.
-- This table shows the activity of players of some games.
-- Each row is a record of a player who logged in and played a number of games (possibly 0) before logging out on someday using some device.
-- Write a solution to report the fraction of players that logged in again on the day after the day they first logged in, rounded to 2 decimal places. In other words, you need to determine
-- the number of players who logged in on the day immediately following their initial login, and divide it by the number of total players.

-- think carefully
WITH first_login AS (
    SELECT player_id, MIN(event_date) AS first_day
    FROM Activity
    GROUP BY player_id
),
next_day_login AS (
    SELECT DISTINCT a.player_id
    FROM Activity a
    JOIN first_login f
      ON a.player_id = f.player_id
     AND a.event_date = DATE_ADD(f.first_day, INTERVAL 1 DAY)
),
total_players AS (
    SELECT COUNT(DISTINCT player_id) AS total_p FROM Activity
)

SELECT ROUND(
    (SELECT COUNT(*) FROM next_day_login) * 1.0 / total_p,
    2
) AS fraction
FROM total_players;


-- ou select from two tables without using a JOIN condition, SQL performs a cross product (also called a Cartesian product).
-- SELECT A.id, B.name
-- FROM A, B;
-- you write this without a JOIN or ON condition, SQL assumes:

-- SELECT A.id, B.name
-- FROM A CROSS JOIN B;
-- Every row from A is combined with every row from B
-- Table A:
-- id
-- 1
-- 2

-- Table B:
-- name
-- John
-- Alice

-- ✅ Result (2 × 2 = 4 rows):
-- id	name
-- 1	John
-- 1	Alice
-- 2	John
-- 2	Alice
