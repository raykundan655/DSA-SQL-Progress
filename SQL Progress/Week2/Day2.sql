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
 

-- Write a solution to find all dates' id with higher temperatures compared to its previous dates (yesterday)

select a.id from Weather as a join Weather as b on 
 datediff(a.recordDate,b.recordDate)=1 
 where a.temperature >b.temperature ;

-- 
-- +----------------+---------+
-- | Column Name    | Type    |
-- +----------------+---------+
-- | machine_id     | int     |
-- | process_id     | int     |
-- | activity_type  | enum    |
-- | timestamp      | float   |
-- +----------------+---------+

-- There is a factory website that has several machines each running the same number of processes. Write a solution to find the average time each machine takes to complete a process.
-- The time to complete a process is the 'end' timestamp minus the 'start' timestamp. The average time is calculated by the total time to complete every process on the machine divided by the number of processes that were run.
-- The resulting table should have the machine_id along with the average time as processing_time, which should be rounded to 3 decimal places.

-- select machine_id  ,round(avg(endt-startt),3)as processing_time from (
--     select machine_id ,process_id  ,max(case when activity_type='start' then timestamp end ) as startt,max(case when activity_type='end' then timestamp end ) as endt from Activity group by 
--     machine_id ,process_id
-- ) as process group by machine_id;


-- self join
SELECT 
    a.machine_id,
    ROUND(AVG(b.timestamp - a.timestamp), 3) AS processing_time
FROM Activity a
JOIN Activity b
  -- cross product happen first
  ON a.machine_id = b.machine_id
 AND a.process_id = b.process_id
  -- chhose only col in which both key equal
 where a.activity_type = 'start'
 AND b.activity_type = 'end'
  -- and filter the row after that
GROUP BY a.machine_id;



-- Table: Employee
-- +-------------+---------+
-- | Column Name | Type    |
-- +-------------+---------+
-- | empId       | int     |
-- | name        | varchar |
-- | supervisor  | int     |
-- | salary      | int     |
-- +-------------+---------+
-- empId is the column with unique values for this table.
-- Each row of this table indicates the name and the ID of an employee in addition to their salary and the id of their manager.
 

-- Table: Bonus
-- +-------------+------+
-- | Column Name | Type |
-- +-------------+------+
-- | empId       | int  |
-- | bonus       | int  |
-- +-------------+------+
-- empId is the column of unique values for this table.
-- empId is a foreign key (reference column) to empId from the Employee table.
-- Each row of this table contains the id of an employee and their respective bonus.
 
-- Write a solution to report the name and bonus amount of each employee with a bonus less than 1000.


select name,bonus from Employee as e left join Bonus  as b on e.empId=b.empId where  b.bonus<1000 or b.bonus is null;





