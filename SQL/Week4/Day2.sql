-- Provide a list of the top countries with the highest number of comments made between December 2019 and January 2020.

-- fb_comments_count
-- columnName	dataType
-- user_id	int64
-- created_at	datetime64[ns]
-- number_of_comments	int64
  
-- fb_active_users
  -- columnName	dataType
-- user_id	int64
-- name	object
-- status	object
-- country	object
select u.country  from fb_comments_count as c inner join fb_active_users as u 
on c.user_id =u.user_id  where  c.created_at BETWEEN '2019-12-01' AND '2020-01-31'
group by u.country having sum(c.number_of_comments)>0
order by sum(number_of_comments) desc;

-- Convert the book titles to lowercase, replace any instance of "the" with "THE", and display the author's first and last names in reverse order 
-- (i.e. retrieve last name first followed by comma + space and then the first name).
-- If an author has a middle name, ignore it work on first and last name, don't include the middle name in the output.
-- The results should include the book ID, modified title, and reversed author name, sorted by the book ID in ascending order.
-- The output should include only rows where "THE" is present in the modified title.

-- Table: Books
-- +----+---------------------------------------------------------+------------------------+----------------+
-- | id | title                                                   | author                 | published_year |
-- +----+---------------------------------------------------------+------------------------+----------------+
-- | 1  | harry potter and the sorcerer's stone                   | J.K. Rowling           | 1997           |
-- | 2  | to kill a mockingbird                                   | Harper Lee             | 1960           |
-- | 3  | 1984                                                    | George Orwell          | 1949           |
-- | 4  | the great gatsby                                        | F. Scott Fitzgerald    | 1925           |
-- | 5  | moby-dick                                               | Herman Melville        | 1851           |


with modify as(select id ,replace(lower(title),'the','THE')as modified_title ,
CONCAT(
            SUBSTRING_INDEX(author, ' ', -1), ', ',
            SUBSTRING_INDEX(author, ' ', 1)
        ) AS reversed_author_name
         from  Books)

select id,modified_title,reversed_author_name from modify
where modified_title like '%THE%'
order by id

-- SUBSTRING_INDEX()->get part of a string based on a separator
-- SUBSTRING_INDEX(string, separator, number)

-- separator: The symbol or space you're splitting by.
-- number
-- positive → get text from the start.
-- Negative → get text from the end.

-- kitna time seperator tak lena hai

-- MySQL String Functions
  
-- Function	                               Purpose                                                   	Example Output
-- LENGTH(str)	                   Returns byte length of a string	                                     LENGTH('abc') → 3
-- CHAR_LENGTH(str)	             Returns character count (ignores byte size)	                        CHAR_LENGTH('abc') → 3
-- LOWER(str) / LCASE(str)	         Converts to lowercase	                                              'ABC' → 'abc'
-- UPPER(str) / UCASE(str)	         Converts to uppercase	                                              'abc' → 'ABC'
-- CONCAT(str1, str2,...)	         Combines multiple strings	                                  'Hello', 'World' → 'HelloWorld'
-- SUBSTRING(str, start, length)	   Returns part of a string	                                   SUBSTRING('abcde', 2, 3) → 'bcd'
-- LEFT(str, n)	                    First n characters	                                              LEFT('abcde', 2) → 'ab'
-- RIGHT(str, n)                   	Last n characters	                                               RIGHT('abcde', 2) → 'de'
-- REPLACE(str, from, to)           	Replaces part of a string	                                   REPLACE('a b c', ' ', '-') → 'a-b-c'
-- REVERSE(str)	                    Reverses the string	                                               REVERSE('abc') → 'cba'
-- TRIM(str)	                     Removes spaces from both ends                                          	' abc ' → 'abc'
-- LTRIM(str)	                    Removes spaces from left side	                                           ' abc' → 'abc'
-- RTRIM(str)	                     Removes spaces from right side	                                         'abc ' → 'abc'
-- INSTR(str, sub)	                Returns position of substring (1-based)	                             INSTR('abc', 'b') → 2
-- POSITION(sub IN str)	             Standard SQL version of INSTR	                                  POSITION('b' IN 'abc') → 2
-- FORMAT(num, decimals)	          Formats number with commas and decimals	                        FORMAT(12345.678, 2) → '12,345.68'
-- ASCII(char)	                     Returns ASCII code of a character	                                      ASCII('A') → 65
-- CHAR(code)	                     Returns character for ASCII code	                                       CHAR(65) → 'A'
-- STRCMP(str1, str2)             	Compares two strings (returns -1, 0, or 1)	                         STRCMP('a', 'b') → -1
-- SUBSTRING_INDEX(str, delim, count)	Gets part of a string based on a delimiter	                  'a b c', ' ', 1 → 'a', -1 → 'c'

-- You have a table Books that contains information about various books in a library. The table has the following columns:

-- Books
-- columnName	dataType
-- id	int
-- title	varchar(255)
-- author	varchar(255)
-- published_year	int

-- Convert all book titles to title case (the first letter of first word should be capital, other letters should be lowercase).
-- Extract the initials of each author's first and last name.
-- Determine the length of each book title.
-- Exclude books published before the year 2000.

select concat(upper(substring(title,1,1)),lower(substring(title,2,length(title)))) as title_case    ,
concat( UPPER(LEFT(SUBSTRING_INDEX(author, ' ', 1), 1)), '.',
        UPPER(LEFT(SUBSTRING_INDEX(author, ' ', -1), 1)), '.') as  author ,
length(title) as title_length,published_year from 
Books
where published_year<2000
order by published_year desc,
title_length asc


-- Create a table Relationships with columns id INT, created_at DATETIME with default current timestamp, follower_id INT, followed_id INT.
-- Make sure that a user cannot follow himself.
-- Tables Schema as Below:

-- Relationships
-- columnName	dataType
-- id	int
-- created_at	datetime DEFAULT CURRENT_TIMESTAMP
-- follower_id	int
-- followed_id	int

--Write your code here!!
create table Relationships(
    id int, 
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    follower_id int , 
    followed_id int
   
);
--Your code ends here!!
INSERT INTO Relationships (id, follower_id, followed_id) VALUES
(1, 1001, 2001),
(2, 1002, 2002),
(3, 1003, 2003),
(4, 1004, 2004);
SELECT followed_id FROM Relationships;


