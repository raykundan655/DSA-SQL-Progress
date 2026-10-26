# SQL Date and Time Functions — Detailed Notes with Examples

> **Database used in most examples: MySQL 8.0+.** Some functions have different names or behavior in PostgreSQL and SQL Server; those differences are shown in the relevant sections.

Date and time functions help you retrieve today's date, extract parts of a date, format a date for display, add or subtract time, calculate durations, and filter records by a date range.

---

## 1. Understand Date and Time Values

SQL has special data types for date and time. Prefer these types over storing dates as ordinary text.

| Data type | What it stores | Example |
|---|---|---|
| `DATE` | Calendar date | `2026-10-26` |
| `TIME` | Time of day | `14:35:42` |
| `DATETIME` (MySQL) | Date and time, without automatic time-zone conversion | `2026-10-26 14:35:42` |
| `TIMESTAMP` | Date/time with database-specific time-zone behavior | `2026-10-26 14:35:42` |

### Example table

Assume we have this `employees` table:

| employee_id | name | hire_date |
|---:|---|---|
| 1 | Rahul | 2022-04-15 |
| 2 | Priya | 2024-09-01 |
| 3 | Amit | 2025-01-20 |
| 4 | Neha | 2025-12-10 |

And an `orders` table:

| order_id | customer | order_datetime | amount |
|---:|---|---|---:|
| 101 | Rahul | 2026-10-25 09:15:00 | 1200 |
| 102 | Priya | 2026-10-26 10:30:00 | 2500 |
| 103 | Amit | 2026-10-26 18:45:00 | 800 |
| 104 | Neha | 2026-10-27 08:00:00 | 1700 |

The examples below use these tables where useful.

---

## 2. Get the Current Date and Time

### 2.1 `CURRENT_DATE`

**Purpose:** Returns the current calendar date.

```sql
SELECT CURRENT_DATE;
```

Example output (the actual date depends on when you run it):

```text
2026-10-26
```

Use it when you need the date but do not need the current time.

**Real-world example:** Find employees hired today.

```sql
SELECT *
FROM employees
WHERE hire_date = CURRENT_DATE;
```

This returns employees whose `hire_date` equals today's date.

### 2.2 `CURRENT_TIME`

**Purpose:** Returns the current time.

```sql
SELECT CURRENT_TIME;
```

Example output:

```text
21:30:00
```

The result changes depending on the time at which the query runs.

### 2.3 `CURRENT_TIMESTAMP`

**Purpose:** Returns the current date and time.

```sql
SELECT CURRENT_TIMESTAMP;
```

Example output:

```text
2026-10-26 21:30:00
```

Use it when you need both the date and the time, for example when recording when an order was created.

### 2.4 MySQL alternatives: `NOW()`, `CURDATE()`, `CURTIME()`

| Function | Purpose | Example result |
|---|---|---|
| `NOW()` | Current date and time | `2026-10-26 21:30:00` |
| `CURDATE()` | Current date | `2026-10-26` |
| `CURTIME()` | Current time | `21:30:00` |

```sql
SELECT NOW();
SELECT CURDATE();
SELECT CURTIME();
```

**Remember:** These values are examples only. The actual results depend on the database server/session clock and time-zone settings.

---

## 3. Extract a Part of a Date or Time

A date such as `2026-10-26` contains a year (`2026`), month (`10`), and day (`26`). Extraction functions return one component.

### 3.1 `EXTRACT()`

**Purpose:** Extracts a specified component from a date/time value.

**Syntax:**

```sql
EXTRACT(unit FROM date_or_time_value)
```

Examples:

```sql
SELECT EXTRACT(YEAR FROM '2026-10-26') AS year;
SELECT EXTRACT(MONTH FROM '2026-10-26') AS month;
SELECT EXTRACT(DAY FROM '2026-10-26') AS day;
```

Results:

| Expression | Result |
|---|---:|
| `EXTRACT(YEAR FROM '2026-10-26')` | 2026 |
| `EXTRACT(MONTH FROM '2026-10-26')` | 10 |
| `EXTRACT(DAY FROM '2026-10-26')` | 26 |

The `unit` can also be `HOUR`, `MINUTE`, or `SECOND` for suitable time values:

```sql
SELECT EXTRACT(HOUR FROM '14:35:42') AS hour;
SELECT EXTRACT(MINUTE FROM '14:35:42') AS minute;
SELECT EXTRACT(SECOND FROM '14:35:42') AS second;
```

These return `14`, `35`, and `42`, respectively, in MySQL.

### 3.2 `YEAR()`, `MONTH()`, and `DAY()` — MySQL

These are convenient functions for extracting date components.

```sql
SELECT
    name,
    hire_date,
    YEAR(hire_date) AS hire_year,
    MONTH(hire_date) AS hire_month,
    DAY(hire_date) AS hire_day
FROM employees;
```

Example output:

| name | hire_date | hire_year | hire_month | hire_day |
|---|---|---:|---:|---:|
| Rahul | 2022-04-15 | 2022 | 4 | 15 |
| Priya | 2024-09-01 | 2024 | 9 | 1 |
| Amit | 2025-01-20 | 2025 | 1 | 20 |
| Neha | 2025-12-10 | 2025 | 12 | 10 |

**When useful:** Extracting a year or month for reports, grouping, or display.

**Filtering tip:** For indexed date columns, a range is often preferable to `WHERE YEAR(hire_date) = 2025`. See the practical examples later.

### 3.3 `HOUR()`, `MINUTE()`, and `SECOND()` — MySQL

These extract the time components.

```sql
SELECT
    HOUR('2026-10-26 14:35:42') AS hour_part,
    MINUTE('2026-10-26 14:35:42') AS minute_part,
    SECOND('2026-10-26 14:35:42') AS second_part;
```

Output:

| hour_part | minute_part | second_part |
|---:|---:|---:|
| 14 | 35 | 42 |

`HOUR()` returns `14`, not `2`, because this timestamp uses the 24-hour clock.

### 3.4 `DAYOFWEEK()` — MySQL

Returns a number representing the weekday.

```sql
SELECT DAYOFWEEK('2026-10-26') AS weekday_number;
```

For MySQL, the numbering is:

| Number | Day |
|---:|---|
| 1 | Sunday |
| 2 | Monday |
| 3 | Tuesday |
| 4 | Wednesday |
| 5 | Thursday |
| 6 | Friday |
| 7 | Saturday |

For `2026-10-26`, the result is `2` (Monday).

**Important:** Other databases can number weekdays differently. Do not assume that `1` always means Sunday or Monday.

### 3.5 `DAYOFYEAR()` — MySQL

Returns the day number within the year (1–365, or 1–366 in a leap year).

```sql
SELECT DAYOFYEAR('2026-10-26') AS day_number;
```

Output: `299`.

This means October 26 is the 299th day of 2026.

### 3.6 `WEEK()` — MySQL

Returns a week number for a date.

```sql
SELECT WEEK('2026-10-26') AS week_number;
```

The exact week number depends on the function's mode and the database's week-numbering rules. If your report must follow ISO week numbering, explicitly use the appropriate mode/function for your database.

### 3.7 `QUARTER()` — MySQL

Returns the quarter of the year:

- Q1: January–March
- Q2: April–June
- Q3: July–September
- Q4: October–December

```sql
SELECT QUARTER('2026-10-26') AS quarter_number;
```

Output: `4`.

**Real-world use:** Grouping company revenue by financial/calendar quarter. Fiscal quarters may differ from calendar quarters.

---

## 4. Format a Date for Display

Formatting means changing how a date is **displayed as text**. It does not mean that the date itself has changed.

### 4.1 `DATE_FORMAT()` — MySQL

**Syntax:**

```sql
DATE_FORMAT(date_value, format_string)
```

Suppose the date is `2026-10-26`.

```sql
SELECT DATE_FORMAT('2026-10-26', '%d-%m-%Y') AS formatted_date;
```

Output:

```text
26-10-2026
```

Here:
- `%d` = day of month (`26`)
- `%m` = month number (`10`)
- `%Y` = four-digit year (`2026`)

More examples:

```sql
SELECT DATE_FORMAT('2026-10-26', '%Y/%m/%d');
-- 2026/10/26

SELECT DATE_FORMAT('2026-10-26', '%M %d, %Y');
-- October 26, 2026

SELECT DATE_FORMAT('2026-10-26 14:35:42', '%d-%m-%Y %h:%i %p');
-- 26-10-2026 02:35 PM
```

Common MySQL format specifiers:

| Specifier | Meaning | Example |
|---|---|---|
| `%Y` | Four-digit year | `2026` |
| `%y` | Two-digit year | `26` |
| `%m` | Month number (01–12) | `10` |
| `%M` | Full month name | `October` |
| `%b` | Abbreviated month name | `Oct` |
| `%d` | Day number (01–31) | `26` |
| `%e` | Day number (1–31) | `26` |
| `%W` | Full weekday name | `Monday` |
| `%a` | Abbreviated weekday name | `Mon` |
| `%H` | Hour (00–23) | `14` |
| `%h` or `%I` | Hour (01–12) | `02` |
| `%i` | Minutes (00–59) | `35` |
| `%s` or `%S` | Seconds (00–59) | `42` |
| `%p` | AM/PM | `PM` |

**Common confusion:** In MySQL, `%m` means month, but `%i` means minutes. Use `%M` for the month name.

### 4.2 `TO_CHAR()` — PostgreSQL and Oracle

These databases commonly use `TO_CHAR()` with a format model. The exact format model can differ between systems.

```sql
-- PostgreSQL example
SELECT TO_CHAR(DATE '2026-10-26', 'DD-MM-YYYY');
```

Output:

```text
26-10-2026
```

Compare:
- MySQL: `DATE_FORMAT(date_value, '%d-%m-%Y')`
- PostgreSQL: `TO_CHAR(date_value, 'DD-MM-YYYY')`

**Best practice:** Format dates at the display/reporting stage. Keep date columns as date/time values for comparisons and calculations.

---

## 5. Convert Text into a Date

Formatting and parsing are different:
- **Formatting:** date value → text.
- **Parsing:** text → date/time value.

### 5.1 `STR_TO_DATE()` — MySQL

Converts text into a date/time value based on the supplied format.

**Syntax:**

```sql
STR_TO_DATE(text_value, format_string)
```

Suppose a source file contains the date as `26-10-2026`, but MySQL needs to interpret it as a date.

```sql
SELECT STR_TO_DATE('26-10-2026', '%d-%m-%Y') AS parsed_date;
```

Output:

```text
2026-10-26
```

Example with a date and time:

```sql
SELECT STR_TO_DATE(
    '26-10-2026 14:35:42',
    '%d-%m-%Y %H:%i:%s'
) AS parsed_datetime;
```

Output:

```text
2026-10-26 14:35:42
```

The format string must match the input. If the input is `month-day-year`, do not parse it using a `day-month-year` format.

### 5.2 `CAST()` — MySQL and many other databases

Converts a value to a specified data type when the conversion is supported.

```sql
SELECT CAST('2026-10-26' AS DATE) AS converted_date;
```

Output: `2026-10-26`.

Use `CAST()` when the text is already in a format the database recognizes. Use a parsing function such as `STR_TO_DATE()` when you need to specify a non-default format.

---

## 6. Add or Subtract a Time Period

This is useful for calculating a deadline, a follow-up date, or a period before/after an event.

### 6.1 `DATE_ADD()` — MySQL

Adds a time interval to a date or datetime.

**Syntax:**

```sql
DATE_ADD(date_value, INTERVAL amount unit)
```

Example: add seven days to October 26.

```sql
SELECT DATE_ADD('2026-10-26', INTERVAL 7 DAY) AS next_week;
```

Output: `2026-11-02`.

More examples:

```sql
SELECT DATE_ADD('2026-10-26', INTERVAL 2 MONTH);
-- 2026-12-26

SELECT DATE_ADD('2026-10-26', INTERVAL 1 YEAR);
-- 2027-10-26

SELECT DATE_ADD('2026-10-26 10:00:00', INTERVAL 3 HOUR);
-- 2026-10-26 13:00:00
```

Common interval units include `SECOND`, `MINUTE`, `HOUR`, `DAY`, `WEEK`, `MONTH`, `QUARTER`, and `YEAR`.

### 6.2 `DATE_SUB()` — MySQL

Subtracts a time interval.

```sql
SELECT DATE_SUB('2026-10-26', INTERVAL 7 DAY) AS previous_week;
```

Output: `2026-10-19`.

Another example:

```sql
SELECT DATE_SUB('2026-10-26', INTERVAL 1 MONTH) AS previous_month;
```

Output: `2026-09-26`.

**Month-end warning:** Adding one month to a date near the end of a month may produce a result adjusted to the last valid day of the target month. Test month-end cases in your database.

### 6.3 SQL Server: `DATEADD()`

SQL Server uses `DATEADD(datepart, number, date)`:

```sql
SELECT DATEADD(day, 7, CAST('2026-10-26' AS date)) AS next_week;
```

Output: `2026-11-02`.

Negative numbers subtract:

```sql
SELECT DATEADD(month, -1, CAST('2026-10-26' AS date));
```

### 6.4 PostgreSQL: interval arithmetic

PostgreSQL supports interval arithmetic:

```sql
SELECT DATE '2026-10-26' + INTERVAL '7 days' AS next_week;
SELECT DATE '2026-10-26' - INTERVAL '1 month' AS previous_month;
```

---

## 7. Calculate the Difference Between Dates and Times

The meaning of “difference” depends on the function and database. Some functions count calendar-day differences; others calculate a difference in a requested unit.

### 7.1 `DATEDIFF()` — MySQL

Returns the number of days between two dates. It uses this order:

```sql
DATEDIFF(date1, date2)
```

Calculation: `date1 - date2`, in days. The time-of-day part is ignored.

```sql
SELECT DATEDIFF('2026-11-05', '2026-10-26') AS days_between;
```

Output: `10`.

Reversing the arguments changes the sign:

```sql
SELECT DATEDIFF('2026-10-26', '2026-11-05') AS days_between;
```

Output: `-10`.

**Employee example:** How many days has each employee worked as of today?

```sql
SELECT
    name,
    hire_date,
    DATEDIFF(CURDATE(), hire_date) AS days_employed
FROM employees;
```

The result is the calendar-date difference between today and the hire date.

### 7.2 SQL Server `DATEDIFF()` has different syntax

SQL Server specifies which date part to count:

```sql
SELECT DATEDIFF(day, '2026-10-26', '2026-11-05') AS days_between;
```

SQL Server counts the specified date-part boundaries crossed. Do not assume MySQL and SQL Server `DATEDIFF()` use the same argument order or rules.

### 7.3 `TIMESTAMPDIFF()` — MySQL

Returns the difference in a requested unit, such as years, months, days, hours, or minutes.

**Syntax:**

```sql
TIMESTAMPDIFF(unit, start_datetime, end_datetime)
```

Example: calculate the difference in hours.

```sql
SELECT TIMESTAMPDIFF(
    HOUR,
    '2026-10-26 10:00:00',
    '2026-10-26 15:30:00'
) AS hours_between;
```

Output: `5`.

There are 5 complete hours between the two times. The extra 30 minutes are not returned as a decimal.

Calculate minutes instead:

```sql
SELECT TIMESTAMPDIFF(
    MINUTE,
    '2026-10-26 10:00:00',
    '2026-10-26 15:30:00'
) AS minutes_between;
```

Output: `330`.

Calculate completed years of service:

```sql
SELECT
    name,
    hire_date,
    TIMESTAMPDIFF(YEAR, hire_date, CURDATE()) AS completed_years
FROM employees;
```

This returns completed whole years, not a decimal number of years.

### 7.4 PostgreSQL: subtract date/time values

Subtracting dates returns the number of days:

```sql
SELECT DATE '2026-10-29' - DATE '2026-10-26' AS days_between;
```

Output: `3`.

Subtracting timestamps returns an interval:

```sql
SELECT TIMESTAMP '2026-10-26 15:30:00'
     - TIMESTAMP '2026-10-26 10:00:00' AS elapsed_time;
```

Output: `05:30:00`.

---

## 8. Find the Last Day of a Month: `LAST_DAY()`

**Purpose:** Returns the final calendar date of the month containing the supplied date. Available in MySQL and Oracle, among others.

```sql
SELECT LAST_DAY('2026-10-10') AS month_end;
```

Output: `2026-10-31`.

February example:

```sql
SELECT LAST_DAY('2026-02-10') AS month_end;
-- 2026-02-28

SELECT LAST_DAY('2024-02-10') AS leap_year_month_end;
-- 2024-02-29
```

**Why is this useful?** It helps calculate month-end reporting dates, billing periods, and the last date of a month.

---

## 9. Extract the Date or Time from a Datetime

### 9.1 `DATE()` — MySQL

Returns only the date part.

```sql
SELECT DATE('2026-10-26 14:35:42') AS date_only;
```

Output: `2026-10-26`.

### 9.2 `TIME()` — MySQL

Returns only the time part.

```sql
SELECT TIME('2026-10-26 14:35:42') AS time_only;
```

Output: `14:35:42`.

These functions are useful for displaying or analysing the date and time separately. They are not the same as formatting a value into an arbitrary text layout.

---

## 10. Combine a Date and a Time: MySQL `TIMESTAMP()`

MySQL's `TIMESTAMP(date, time)` can combine a date and a time into a datetime value.

```sql
SELECT TIMESTAMP('2026-10-26', '14:35:42') AS combined_value;
```

Output:

```text
2026-10-26 14:35:42
```

This is useful when the date and time are stored separately and you need a combined datetime value. Other databases may use different constructors or casts.

---

## 11. Time-Zone Conversion

A time zone determines the local clock time associated with an instant. Time-zone functions are database-specific, and results depend on configuration.

### 11.1 MySQL `CONVERT_TZ()`

**Purpose:** Converts a datetime from one time zone to another.

```sql
SELECT CONVERT_TZ(
    '2026-10-26 09:00:00',
    '+00:00',
    '+05:30'
) AS india_time;
```

Expected output:

```text
2026-10-26 14:30:00
```

This example converts 09:00 at UTC offset `+00:00` to offset `+05:30`.

Named zones can be used if MySQL's time-zone tables are installed:

```sql
SELECT CONVERT_TZ(
    '2026-10-26 09:00:00',
    'UTC',
    'Asia/Kolkata'
);
```

If named time-zone data is unavailable, the result may be `NULL`.

### 11.2 PostgreSQL `AT TIME ZONE`

PostgreSQL uses `AT TIME ZONE`; the result depends on whether the input is a timestamp with or without time zone.

```sql
SELECT TIMESTAMP '2026-10-26 09:00:00'
       AT TIME ZONE 'UTC';
```

Read the database's time-zone documentation before using conversions in production, especially when daylight-saving changes apply.

---

## 12. Practical Date/Time Queries

These examples use MySQL syntax.

### 12.1 Find employees hired in 2025

Recommended range query:

```sql
SELECT *
FROM employees
WHERE hire_date >= '2025-01-01'
  AND hire_date <  '2026-01-01';
```

**How it works:**
1. `hire_date >= '2025-01-01'` includes January 1, 2025.
2. `hire_date < '2026-01-01'` excludes January 1, 2026 and everything after it.
3. Together, the conditions include every date in 2025.

This approach also works if `hire_date` contains a time component, and it can be more index-friendly than applying `YEAR()` to the column.

### 12.2 Find orders created today

If `order_datetime` is a `DATETIME` column:

```sql
SELECT *
FROM orders
WHERE order_datetime >= CURDATE()
  AND order_datetime < DATE_ADD(CURDATE(), INTERVAL 1 DAY);
```

If today is `2026-10-26`, the range is:

- Include: `2026-10-26 00:00:00`
- Exclude: `2026-10-27 00:00:00`

So both orders at `10:30` and `18:45` on October 26 are included. An order at midnight on October 27 is not included.

### 12.3 Find orders from the last 7 days

For the last seven calendar days including today:

```sql
SELECT *
FROM orders
WHERE order_datetime >= DATE_SUB(CURDATE(), INTERVAL 6 DAY)
  AND order_datetime < DATE_ADD(CURDATE(), INTERVAL 1 DAY);
```

This includes today plus the previous six calendar dates. If you instead mean the previous exact 168 hours, use a datetime boundary relative to `NOW()`.

### 12.4 Count employees hired in each month

```sql
SELECT
    YEAR(hire_date) AS hire_year,
    MONTH(hire_date) AS hire_month,
    COUNT(*) AS employees_hired
FROM employees
GROUP BY YEAR(hire_date), MONTH(hire_date)
ORDER BY hire_year, hire_month;
```

**How it works:**
- `YEAR()` extracts the year.
- `MONTH()` extracts the month number.
- `COUNT(*)` counts employees in each year/month group.
- `GROUP BY` makes one group for each unique year and month.
- `ORDER BY` sorts the report chronologically.

### 12.5 Find employees whose work anniversary is today

```sql
SELECT *
FROM employees
WHERE MONTH(hire_date) = MONTH(CURDATE())
  AND DAY(hire_date) = DAY(CURDATE());
```

This matches the month and day while ignoring the year. Decide separately how to handle employees hired on February 29 in non-leap years.

### 12.6 Calculate each employee's completed years of service

```sql
SELECT
    name,
    hire_date,
    TIMESTAMPDIFF(YEAR, hire_date, CURDATE()) AS completed_years
FROM employees;
```

For example, an employee hired on `2024-11-20` has not completed two years as of `2026-10-26`, so the result is `1`.

### 12.7 Calculate total sales by month

```sql
SELECT
    YEAR(order_datetime) AS sales_year,
    MONTH(order_datetime) AS sales_month,
    SUM(amount) AS total_sales
FROM orders
GROUP BY YEAR(order_datetime), MONTH(order_datetime)
ORDER BY sales_year, sales_month;
```

This produces one row per year/month with the sum of the order amounts.


### 12.8 Calculate total sales for one week starting from a chosen date (`INTERVAL`)

A common use of `INTERVAL` is to calculate the total sales during a seven-day period that starts on a date you choose. For example, you may want sales from October 26 through November 1, 2026.

Assume an `orders` table contains:

| order_id | order_datetime | amount |
|---:|---|---:|
| 1 | 2026-10-26 09:15:00 | 1000 |
| 2 | 2026-10-27 12:00:00 | 1500 |
| 3 | 2026-10-29 16:30:00 | 2000 |
| 4 | 2026-11-01 19:00:00 | 2500 |
| 5 | 2026-11-02 10:00:00 | 3000 |

**MySQL query** — where the chosen starting date (`X`) is `2026-10-26`:

```sql
SELECT SUM(amount) AS total_sales
FROM orders
WHERE order_datetime >= '2026-10-26'
  AND order_datetime < DATE_ADD('2026-10-26', INTERVAL 1 WEEK);
```

**Result:** `7000`

**How the query works:**

1. `order_datetime >= '2026-10-26'` includes orders from the start of October 26 onward.
2. `DATE_ADD('2026-10-26', INTERVAL 1 WEEK)` calculates the boundary date, `2026-11-02`.
3. `order_datetime < '2026-11-02'` excludes orders on November 2 and later.
4. `SUM(amount)` adds the amounts for the included orders: `1000 + 1500 + 2000 + 2500 = 7000`.

The range includes all of October 26 through November 1, including every time of day if `order_datetime` is a `DATETIME` column. The order on November 2 is excluded. Using `<` for the end boundary avoids missing or mishandling times such as `23:59:59`.

**Reusable pattern:**

```sql
SELECT SUM(amount) AS total_sales
FROM orders
WHERE order_datetime >= start_date
  AND order_datetime < DATE_ADD(start_date, INTERVAL 1 WEEK);
```

Replace `start_date` with the date you want to start from (for example, `'2026-10-26'`). In executable SQL, use the actual date value or a parameter supported by your application; `start_date` above is a placeholder, not a built-in SQL variable.

**Important difference: seven-day period vs calendar week**

- **Seven-day period from a chosen date:** If `X` is Wednesday, the range runs from that Wednesday up to, but not including, the following Wednesday. Use the query above.
- **Calendar week (such as Monday through Sunday):** First calculate the Monday/Sunday boundaries for the relevant week. A simple `INTERVAL 1 WEEK` added to an arbitrary date does *not* automatically align the period to Monday or Sunday.

**If `order_datetime` is a `DATE` column**, the same query works. If the table stores only dates, the result still includes the start date and excludes the date exactly one week later.

**PostgreSQL equivalent:**

```sql
SELECT SUM(amount) AS total_sales
FROM orders
WHERE order_datetime >= TIMESTAMP '2026-10-26 00:00:00'
  AND order_datetime < TIMESTAMP '2026-10-26 00:00:00' + INTERVAL '1 week';
```

**SQL Server equivalent:**

```sql
SELECT SUM(amount) AS total_sales
FROM orders
WHERE order_datetime >= '2026-10-26'
  AND order_datetime < DATEADD(WEEK, 1, '2026-10-26');
```

---

## 13. Function Syntax by Database

Do not assume all SQL databases use the same function name or argument order.

| Task | MySQL | SQL Server | PostgreSQL |
|---|---|---|---|
| Current date | `CURDATE()` / `CURRENT_DATE` | `CAST(GETDATE() AS date)` | `CURRENT_DATE` |
| Current time | `CURTIME()` / `CURRENT_TIME` | `CAST(GETDATE() AS time)` | `CURRENT_TIME` |
| Current date/time | `NOW()` / `CURRENT_TIMESTAMP` | `GETDATE()` / `SYSDATETIME()` | `NOW()` / `CURRENT_TIMESTAMP` |
| Extract year | `YEAR(d)` or `EXTRACT(YEAR FROM d)` | `YEAR(d)` or `DATEPART(year, d)` | `EXTRACT(YEAR FROM d)` |
| Format date as text | `DATE_FORMAT()` | `FORMAT()` or conversion styles | `TO_CHAR()` |
| Parse text date | `STR_TO_DATE()` | `CONVERT()` / `TRY_CONVERT()` | `TO_DATE()` or casts |
| Add time | `DATE_ADD()` | `DATEADD()` | `date + INTERVAL '...'` |
| Difference in days | `DATEDIFF(date1, date2)` | `DATEDIFF(day, start, end)` | `date2 - date1` |
| Difference in requested unit | `TIMESTAMPDIFF()` | `DATEDIFF()` with a date part | Subtract timestamps / extract interval parts |
| Month end | `LAST_DAY()` | `EOMONTH()` | Date arithmetic using `date_trunc()` and intervals |

---

## 14. Common Mistakes and How to Avoid Them

### Mistake 1: Confusing formatting with conversion

```sql
-- Formatting: returns text
SELECT DATE_FORMAT('2026-10-26', '%d/%m/%Y');

-- Parsing: returns a date/time value
SELECT STR_TO_DATE('26/10/2026', '%d/%m/%Y');
```

Formatting changes how a value is displayed. Parsing interprets text as a date/time value.

### Mistake 2: Filtering a full day using equality

This can miss rows if the column includes times:

```sql
-- Often wrong for a DATETIME column
WHERE order_datetime = CURDATE()
```

Prefer:

```sql
WHERE order_datetime >= CURDATE()
  AND order_datetime < DATE_ADD(CURDATE(), INTERVAL 1 DAY)
```

### Mistake 3: Assuming `DATEDIFF()` means the same thing everywhere

- MySQL `DATEDIFF(date1, date2)` returns the day difference and ignores time-of-day.
- SQL Server `DATEDIFF(day, start, end)` counts day boundaries crossed.

Always check which database you are using.

### Mistake 4: Assuming month and weekday numbering are universal

Week numbering, weekday numbering, and calendar conventions can vary by database and configuration.

### Mistake 5: Ignoring time zones

`CURRENT_TIMESTAMP`, `TIMESTAMP`, and time-zone conversion behavior can depend on the database, session, and server settings.

### Mistake 6: Storing dates as text

Use `DATE`, `DATETIME`, or the equivalent type where possible. Text values can be harder to validate, sort, compare, and calculate reliably.

### Mistake 7: Using `YEAR(column)` in every filter

This is valid:

```sql
WHERE YEAR(hire_date) = 2025
```

But a range is often better for index use:

```sql
WHERE hire_date >= '2025-01-01'
  AND hire_date <  '2026-01-01'
```

---

## 15. Quick Revision Sheet — MySQL

```sql
-- Current date and time
SELECT CURRENT_DATE;
SELECT CURRENT_TIME;
SELECT CURRENT_TIMESTAMP;
SELECT NOW();
SELECT CURDATE();
SELECT CURTIME();

-- Extract date components
SELECT YEAR('2026-10-26');
SELECT MONTH('2026-10-26');
SELECT DAY('2026-10-26');
SELECT DAYOFWEEK('2026-10-26');
SELECT DAYOFYEAR('2026-10-26');
SELECT QUARTER('2026-10-26');

-- Extract time components
SELECT HOUR('14:35:42');
SELECT MINUTE('14:35:42');
SELECT SECOND('14:35:42');

-- Format and parse
SELECT DATE_FORMAT('2026-10-26', '%d-%m-%Y');
SELECT STR_TO_DATE('26-10-2026', '%d-%m-%Y');
SELECT CAST('2026-10-26' AS DATE);

-- Add and subtract
SELECT DATE_ADD('2026-10-26', INTERVAL 7 DAY);
SELECT DATE_SUB('2026-10-26', INTERVAL 1 MONTH);

-- Difference
SELECT DATEDIFF('2026-11-05', '2026-10-26');
SELECT TIMESTAMPDIFF(
    HOUR,
    '2026-10-26 10:00:00',
    '2026-10-26 15:30:00'
);

-- Month end, date part, and time part
SELECT LAST_DAY('2026-10-26');
SELECT DATE('2026-10-26 14:35:42');
SELECT TIME('2026-10-26 14:35:42');

-- Filter all records from today
SELECT *
FROM orders
WHERE order_datetime >= CURDATE()
  AND order_datetime < DATE_ADD(CURDATE(), INTERVAL 1 DAY);
```

## 16. Interview Summary

- `CURRENT_DATE`: current date.
- `CURRENT_TIME`: current time.
- `CURRENT_TIMESTAMP`: current date and time.
- `YEAR()`, `MONTH()`, `DAY()`: extract date components in MySQL.
- `EXTRACT()`: extract a requested date/time component.
- `DATE_FORMAT()`: format a date as text in MySQL.
- `STR_TO_DATE()`: parse text into a date/time value in MySQL.
- `DATE_ADD()` / `DATE_SUB()`: add or subtract an interval in MySQL.
- `DATEDIFF()`: calculate a day difference in MySQL.
- `TIMESTAMPDIFF()`: calculate a difference in a chosen unit in MySQL.
- `LAST_DAY()`: return the last date of a month.
- For a complete day, filter with `>= start` and `< next day`.
- Always check your database system because syntax and edge cases differ.

**Study approach:** First understand what each function returns. Then run the examples, change the dates, and predict the output before executing the query.
