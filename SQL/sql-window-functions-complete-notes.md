# SQL Window Functions — Complete Notes

A beginner-friendly, interview-ready guide to SQL window functions, with definitions, syntax, examples, outputs, practical applications, and interview questions.

---

## Table of Contents

1. [Window Functions Overview](#1-window-functions-overview)
2. [Understanding `OVER()`](#2-understanding-over)
3. [Understanding `PARTITION BY` and `ORDER BY`](#3-understanding-partition-by-and-order-by)
4. [`ROW_NUMBER()`](#4-row_number)
5. [`RANK()`](#5-rank)
6. [`DENSE_RANK()`](#6-dense_rank)
7. [`NTILE()`](#7-ntile)
8. [`LAG()`](#8-lag)
9. [`LEAD()`](#9-lead)
10. [`FIRST_VALUE()`](#10-first_value)
11. [Window Frames](#11-window-frames)
12. [`LAST_VALUE()`](#12-last_value)
13. [Aggregate Window Functions](#13-aggregate-window-functions)
14. [Ranking Functions Comparison](#14-ranking-functions-comparison)
15. [Choosing the Right Function](#15-choosing-the-right-function)
16. [Interview Questions](#16-interview-questions)
17. [Quick Summary](#17-quick-summary)

---

## 1. Window Functions Overview

SQL window functions perform calculations across a set of related rows without combining those rows into one result row.

Unlike aggregate functions used with `GROUP BY`, window functions preserve the individual rows in the result.

### Common uses

- Ranking students or employees.
- Finding the highest-paid employee in each department.
- Comparing a row with the previous or next row.
- Calculating running totals and averages.
- Finding the first or last value in a window.
- Dividing records into approximately equal-sized groups.
- Identifying duplicate records.

### Recommended learning order

- `OVER()`
- `ROW_NUMBER()`
- `RANK()`
- `DENSE_RANK()`
- `NTILE()`
- `LAG()`
- `LEAD()`
- `FIRST_VALUE()`
- Window frames
- `LAST_VALUE()`
- `SUM() OVER()`
- `AVG() OVER()`
- `COUNT() OVER()`
- `MIN() OVER()`
- `MAX() OVER()`

---

## 2. Understanding `OVER()`

### Simple definition

> `OVER()` defines the window—the set of rows the window function operates on.

### Example 1: `OVER()` — Whole table

**Table: `Students`**

| Name | Marks |
|---|---:|
| Alice | 90 |
| Bob | 80 |
| Charlie | 95 |
| David | 70 |

```sql
SELECT
    name,
    marks,
    AVG(marks) OVER() AS avg_marks
FROM Students;
```

**How it works**

1. `OVER()` means the average is calculated across all rows in the result.
2. The average is `(90 + 80 + 95 + 70) / 4 = 83.75`.
3. That average is shown beside every student.

**Result**

| Name | Marks | Avg_Marks |
|---|---:|---:|
| Alice | 90 | 83.75 |
| Bob | 80 | 83.75 |
| Charlie | 95 | 83.75 |
| David | 70 | 83.75 |

### Example 2: `PARTITION BY` — Look within groups

```sql
AVG(salary) OVER(PARTITION BY department)
```

This means: calculate the average separately within each department.

**Table: `Employees`**

| Name | Department | Salary |
|---|---|---:|
| Alice | HR | 50000 |
| Bob | HR | 60000 |
| Charlie | IT | 70000 |
| David | IT | 80000 |

- HR average: `(50000 + 60000) / 2 = 55000`
- IT average: `(70000 + 80000) / 2 = 75000`

### Example 3: `ORDER BY` — Running totals

```sql
SELECT
    name,
    salary,
    SUM(salary) OVER(ORDER BY salary) AS running_total
FROM Employees;
```

If the salaries in ascending order are `50000, 60000, 70000, 80000`, the running totals are:

| Salary | Running total |
|---:|---:|
| 50000 | 50000 |
| 60000 | 110000 |
| 70000 | 180000 |
| 80000 | 260000 |

A window `ORDER BY` controls the order in which rows are processed by the function. It does not necessarily determine the final display order of the query; use a query-level `ORDER BY` if you need to guarantee output order.

### Interview-ready definition

> `OVER()` defines the window—the set of rows—on which a window function operates.

| Clause | Meaning |
|---|---|
| `OVER()` | The window includes all rows in the result, unless otherwise restricted. |
| `OVER(PARTITION BY ...)` | Divides rows into groups; calculations operate separately within each group. |
| `OVER(ORDER BY ...)` | Defines the order used by the window function. |

**Easy analogy**

Imagine a classroom:

- `OVER()` → Look at the whole class.
- `OVER(PARTITION BY section)` → Look at only one section at a time.
- `OVER(ORDER BY marks)` → Arrange students by marks before calculating.

---

## 3. Understanding `PARTITION BY` and `ORDER BY`

These two clauses serve different purposes.

- **`PARTITION BY`** divides rows into groups. The function starts over for each group.
- **`ORDER BY`** determines the order of rows within the window or partition.

Example:

```sql
SELECT
    employee,
    department,
    salary,
    ROW_NUMBER() OVER (
        PARTITION BY department
        ORDER BY salary DESC, employee ASC
    ) AS row_num
FROM Employees;
```

Here, employees are grouped by department and then numbered from the highest salary to the lowest within each department.

Adding a tie-breaker such as `employee ASC` helps make the ordering predictable when salaries are equal. The exact syntax for tie-breaking is supported by common SQL databases, though case sensitivity and collation can affect text ordering.

---

## 4. `ROW_NUMBER()`

### Definition

`ROW_NUMBER()` assigns a unique, sequential integer to every row within a result set or partition. Numbering starts at `1` and increases by `1`.

Even if two rows have the same value in the ordering column, they receive different row numbers.

### Syntax

```sql
ROW_NUMBER() OVER (
    [PARTITION BY column_name]
    ORDER BY column_name
)
```

### Example

**Table: `Students`**

| Student_ID | Name | Marks |
|---:|---|---:|
| 101 | Rahul | 95 |
| 102 | Aman | 85 |
| 103 | Priya | 85 |
| 104 | Kundan | 70 |

```sql
SELECT
    Student_ID,
    Name,
    Marks,
    ROW_NUMBER() OVER (
        ORDER BY Marks DESC, Student_ID ASC
    ) AS row_num
FROM Students;
```

**Output**

| Student_ID | Name | Marks | row_num |
|---:|---|---:|---:|
| 101 | Rahul | 95 | 1 |
| 102 | Aman | 85 | 2 |
| 103 | Priya | 85 | 3 |
| 104 | Kundan | 70 | 4 |

**Explanation**

1. `ORDER BY Marks DESC` sorts students from highest to lowest marks.
2. `Student_ID ASC` breaks ties between students with equal marks.
3. `ROW_NUMBER()` assigns a different number to each row.
4. Aman and Priya have the same marks but receive different row numbers.

**Important:** If the ordering columns contain ties and no tie-breaker is specified, the order among tied rows is not guaranteed.

### Using `PARTITION BY`

```sql
SELECT
    Employee,
    Department,
    Salary,
    ROW_NUMBER() OVER (
        PARTITION BY Department
        ORDER BY Salary DESC, Employee ASC
    ) AS row_num
FROM Employees;
```

Numbering restarts at `1` for each department. For example, IT employees might receive `1, 2, 3`, while HR employees receive `1, 2`.

### Practical applications

- Selecting the top employee in each department.
- Identifying duplicate records.
- Finding the latest record for each customer.
- Implementing pagination.
- Assigning unique row positions.

### Example: Find the highest-paid employee in each department

```sql
WITH RankedEmployees AS (
    SELECT
        Employee_ID,
        Employee,
        Department,
        Salary,
        ROW_NUMBER() OVER (
            PARTITION BY Department
            ORDER BY Salary DESC, Employee_ID ASC
        ) AS rn
    FROM Employees
)
SELECT
    Employee_ID,
    Employee,
    Department,
    Salary
FROM RankedEmployees
WHERE rn = 1;
```

The CTE assigns row numbers within each department. The outer query returns the row numbered `1` in each department.

**Important:** If multiple employees share the highest salary, this query returns only one of them because `ROW_NUMBER()` always gives each row a unique number. Use `RANK()` if you want all employees tied for the highest salary.

**Key takeaway:** `ROW_NUMBER()` gives every row a unique sequential number within its partition.

---

## 5. `RANK()`

### Definition

`RANK()` assigns the same rank to rows with equal values in the ordering column. When multiple rows share a rank, subsequent ranks are skipped. This is called ranking with gaps.

### Syntax

```sql
RANK() OVER (
    [PARTITION BY column_name]
    ORDER BY column_name
)
```

### Example

```sql
SELECT
    Student_ID,
    Name,
    Marks,
    RANK() OVER (
        ORDER BY Marks DESC
    ) AS student_rank
FROM Students;
```

**Output**

| Student_ID | Name | Marks | student_rank |
|---:|---|---:|---:|
| 101 | Rahul | 95 | 1 |
| 102 | Aman | 85 | 2 |
| 103 | Priya | 85 | 2 |
| 104 | Kundan | 70 | 4 |

### Explanation

1. Rahul has the highest marks and receives rank `1`.
2. Aman and Priya both scored `85`, so both receive rank `2`.
3. Because two rows occupy rank `2`, the next rank is `4`, not `3`.
4. Kundan receives rank `4`.

The ranking sequence is `1, 2, 2, 4`.

### More examples of ranking gaps

| Student | Marks | RANK() |
|---|---:|---:|
| A | 100 | 1 |
| B | 90 | 2 |
| C | 90 | 2 |
| D | 90 | 2 |
| E | 80 | 5 |

Three students share rank `2`, so the next rank is `5`.

### Using `PARTITION BY`

```sql
SELECT
    Employee,
    Department,
    Salary,
    RANK() OVER (
        PARTITION BY Department
        ORDER BY Salary DESC
    ) AS salary_rank
FROM Employees;
```

This ranks employees separately within each department. Employees with the same salary receive the same rank, and subsequent ranks are skipped.

### Practical applications

- Ranking students in examinations.
- Creating competition leaderboards.
- Ranking employees based on salary.
- Comparing sales performance.
- Identifying all employees tied for a particular rank.

**Key takeaway:** `RANK()` gives tied rows the same rank and skips subsequent rank numbers.

---

## 6. `DENSE_RANK()`

### Definition

`DENSE_RANK()` assigns the same rank to rows with equal ordering values, just like `RANK()`. However, it does not skip ranks after ties.

### Syntax

```sql
DENSE_RANK() OVER (
    [PARTITION BY column_name]
    ORDER BY column_name
)
```

### Example

```sql
SELECT
    Student_ID,
    Name,
    Marks,
    DENSE_RANK() OVER (
        ORDER BY Marks DESC
    ) AS dense_rank
FROM Students;
```

**Output**

| Student_ID | Name | Marks | dense_rank |
|---:|---|---:|---:|
| 101 | Rahul | 95 | 1 |
| 102 | Aman | 85 | 2 |
| 103 | Priya | 85 | 2 |
| 104 | Kundan | 70 | 3 |

### Explanation

1. Rahul receives rank `1`.
2. Aman and Priya receive rank `2` because they have equal marks.
3. Kundan receives rank `3`.
4. No rank is skipped after the tie at rank `2`.

The ranking sequence is `1, 2, 2, 3`.

### `RANK()` vs. `DENSE_RANK()`

| Student | Marks | RANK() | DENSE_RANK() |
|---|---:|---:|---:|
| A | 100 | 1 | 1 |
| B | 90 | 2 | 2 |
| C | 90 | 2 | 2 |
| D | 90 | 2 | 2 |
| E | 80 | 5 | 3 |

`RANK()` gives student E rank `5`; `DENSE_RANK()` gives student E rank `3`. `DENSE_RANK()` assigns consecutive ranks to distinct ranking values.

### Using `PARTITION BY`

```sql
SELECT
    Employee,
    Department,
    Salary,
    DENSE_RANK() OVER (
        PARTITION BY Department
        ORDER BY Salary DESC
    ) AS salary_rank
FROM Employees;
```

This ranks employees independently within each department without skipping ranks after ties.

### Practical applications

- Finding the second-highest distinct salary.
- Finding the third-highest distinct salary.
- Ranking students based on distinct marks.
- Ranking products based on sales.
- Creating rankings where consecutive positions are required.

### Example: Find the second-highest distinct salary

```sql
WITH SalaryRanks AS (
    SELECT
        Employee,
        Salary,
        DENSE_RANK() OVER (
            ORDER BY Salary DESC
        ) AS salary_rank
    FROM Employees
)
SELECT
    Employee,
    Salary
FROM SalaryRanks
WHERE salary_rank = 2;
```

The query ranks salaries from highest to lowest. Employees with equal salaries receive the same rank, and `WHERE salary_rank = 2` returns employees earning the second-highest distinct salary. If several employees share that salary, all of them are returned.

**Key takeaway:** `DENSE_RANK()` gives tied rows the same rank without skipping subsequent ranks.

---

## 7. `NTILE()`

### Definition

`NTILE(n)` divides rows in an ordered result set into `n` approximately equal-sized groups called buckets. Each row receives a bucket number from `1` through `n`.

Unlike ranking functions, `NTILE()` distributes rows by their ordered positions rather than assigning competition ranks.

### Syntax

```sql
NTILE(number_of_buckets) OVER (
    [PARTITION BY column_name]
    ORDER BY column_name
)
```

Examples:

- `NTILE(2)` creates two buckets.
- `NTILE(3)` creates three buckets.
- `NTILE(4)` creates four buckets.

### Example 1: `NTILE(2)`

**Table: `Students`**

| Student_ID | Name | Marks |
|---:|---|---:|
| 101 | Rahul | 95 |
| 102 | Aman | 85 |
| 103 | Priya | 85 |
| 104 | Kundan | 70 |

```sql
SELECT
    Student_ID,
    Name,
    Marks,
    NTILE(2) OVER (
        ORDER BY Marks DESC, Student_ID ASC
    ) AS bucket
FROM Students;
```

**Output**

| Student_ID | Name | Marks | bucket |
|---:|---|---:|---:|
| 101 | Rahul | 95 | 1 |
| 102 | Aman | 85 | 1 |
| 103 | Priya | 85 | 2 |
| 104 | Kundan | 70 | 2 |

There are four rows and two buckets:

- Bucket 1 contains the first two rows.
- Bucket 2 contains the last two rows.

The bucket assignments are `1, 1, 2, 2`.

Aman and Priya have the same marks but belong to different buckets because `NTILE()` distributes rows by position, not by ties.

### Example 2: `NTILE(4)`

Suppose eight employees are ordered by salary:

```sql
SELECT
    Employee,
    Salary,
    NTILE(4) OVER (
        ORDER BY Salary DESC
    ) AS bucket
FROM Employees;
```

With eight rows, each bucket contains two rows.

| Ordered rows | Bucket |
|---|---:|
| Rows 1–2 | 1 |
| Rows 3–4 | 2 |
| Rows 5–6 | 3 |
| Rows 7–8 | 4 |

### What if the rows cannot be divided equally?

Suppose there are ten rows and we use `NTILE(4)`. SQL gives extra rows to the earlier buckets.

| Bucket | Number of rows |
|---|---:|
| 1 | 3 |
| 2 | 3 |
| 3 | 2 |
| 4 | 2 |

The difference between bucket sizes is at most one.

For ten rows and `NTILE(3)`, the distribution is `4, 3, 3`.

### Using `PARTITION BY`

```sql
SELECT
    Employee,
    Department,
    Salary,
    NTILE(2) OVER (
        PARTITION BY Department
        ORDER BY Salary DESC
    ) AS salary_group
FROM Employees;
```

This divides employees into two approximately equal-sized buckets separately within each department. Bucket numbering restarts at `1` for every department.

### Practical applications

- Dividing customers into groups based on spending.
- Segmenting employees by salary.
- Splitting students into performance groups.
- Dividing datasets into approximately equal-sized groups.
- Creating quartiles or other distribution-based segments.

### Example: Identify the top quartile

```sql
SELECT
    Employee,
    Salary,
    NTILE(4) OVER (
        ORDER BY Salary DESC
    ) AS quartile
FROM Employees;
```

Rows assigned `quartile = 1` form the first bucket when employees are sorted from highest salary to lowest. This bucket contains approximately one quarter of the rows, not necessarily exactly 25% of the salary value range.

**Key takeaway:** `NTILE(n)` distributes ordered rows into `n` approximately equal-sized buckets. Tied values can be split across buckets.

---

## 8. `LAG()`

### Definition

`LAG()` accesses a value from a previous row in the ordered window without requiring a self-join.

It is useful for comparing the current row with an earlier row.

### Syntax

```sql
LAG(expression, offset, default_value) OVER (
    [PARTITION BY column_name]
    ORDER BY column_name
)
```

- `expression`: The column or expression to retrieve.
- `offset`: How many rows back to look; defaults to `1`.
- `default_value`: Value returned when the requested preceding row does not exist; defaults to `NULL` if omitted.

### Example: Compare each month's sales with the previous month

**Table: `MonthlySales`**

| Month | Sales |
|---|---:|
| January | 1000 |
| February | 1500 |
| March | 1200 |
| April | 1800 |

```sql
SELECT
    Month,
    Sales,
    LAG(Sales) OVER (
        ORDER BY MonthNumber
    ) AS previous_month_sales
FROM MonthlySales;
```

Assume `MonthNumber` contains `1` for January, `2` for February, and so on.

**Output**

| Month | Sales | previous_month_sales |
|---|---:|---:|
| January | 1000 | NULL |
| February | 1500 | 1000 |
| March | 1200 | 1500 |
| April | 1800 | 1200 |

The first row has no previous row, so its previous-month value is `NULL`.

### Calculate the change from the previous row

```sql
SELECT
    Month,
    Sales,
    Sales - LAG(Sales) OVER (
        ORDER BY MonthNumber
    ) AS sales_change
FROM MonthlySales;
```

The change is current sales minus previous month's sales.

**Using a default value**

```sql
LAG(Sales, 1, 0) OVER (ORDER BY MonthNumber)
```

This returns `0` instead of `NULL` when no previous row exists.

### Practical applications

- Month-over-month sales comparisons.
- Comparing current and previous salaries or prices.
- Finding changes in sensor readings.
- Detecting gaps or changes in time-series data.

**Key takeaway:** `LAG()` looks backward within the ordered window.

---

## 9. `LEAD()`

### Definition

`LEAD()` accesses a value from a subsequent row in the ordered window without requiring a self-join.

It is the forward-looking counterpart of `LAG()`.

### Syntax

```sql
LEAD(expression, offset, default_value) OVER (
    [PARTITION BY column_name]
    ORDER BY column_name
)
```

- `expression`: The column or expression to retrieve.
- `offset`: How many rows forward to look; defaults to `1`.
- `default_value`: Value returned when the requested following row does not exist; defaults to `NULL` if omitted.

### Example: Compare each month's sales with the next month

```sql
SELECT
    Month,
    Sales,
    LEAD(Sales) OVER (
        ORDER BY MonthNumber
    ) AS next_month_sales
FROM MonthlySales;
```

**Output**

| Month | Sales | next_month_sales |
|---|---:|---:|
| January | 1000 | 1500 |
| February | 1500 | 1200 |
| March | 1200 | 1800 |
| April | 1800 | NULL |

April has no following row, so `next_month_sales` is `NULL`.

### Practical applications

- Comparing a current value with the next value.
- Analyzing future scheduled events.
- Finding the next transaction for a customer.
- Comparing consecutive time-series records.

**Key takeaway:** `LEAD()` looks forward within the ordered window.

### `LAG()` vs. `LEAD()`

| Function | Direction | Typical use |
|---|---|---|
| `LAG()` | Previous row | Compare with an earlier value |
| `LEAD()` | Next row | Compare with a later value |

---

## 10. `FIRST_VALUE()`

### Definition

`FIRST_VALUE()` returns the value from the first row in the current window frame, according to the specified ordering.

**Analogy:** If students are arranged by marks, asking `FIRST_VALUE()` for the student name returns the first student in that ordering.

### Syntax

```sql
FIRST_VALUE(column_name) OVER (
    [PARTITION BY column_name]
    ORDER BY column_name
)
```

### Example

**Table: `Employees`**

| Name | Salary |
|---|---:|
| Alice | 50000 |
| Bob | 70000 |
| Charlie | 60000 |
| David | 80000 |

```sql
SELECT
    name,
    salary,
    FIRST_VALUE(salary) OVER (
        ORDER BY salary DESC
    ) AS highest_salary
FROM Employees;
```

**Step 1 — Sort by salary descending**

| Name | Salary |
|---|---:|
| David | 80000 |
| Bob | 70000 |
| Charlie | 60000 |
| Alice | 50000 |

**Output**

| Name | Salary | Highest Salary |
|---|---:|---:|
| David | 80000 | 80000 |
| Bob | 70000 | 80000 |
| Charlie | 60000 | 80000 |
| Alice | 50000 | 80000 |

With this ordering and the default frame, the first value is the highest salary, so each row shows `80000`.

### Using `PARTITION BY`

```sql
SELECT
    name,
    dept,
    salary,
    FIRST_VALUE(salary) OVER (
        PARTITION BY dept
        ORDER BY salary DESC
    ) AS highest_salary
FROM Employees;
```

Each department gets its own highest salary.

For example, if HR salaries are `50000` and `60000`, both HR rows can show `60000`. If IT salaries are `70000` and `80000`, both IT rows can show `80000`.

### Salary gap from the top earner

```sql
SELECT
    name,
    salary,
    FIRST_VALUE(salary) OVER (
        ORDER BY salary DESC
    ) AS highest_salary,
    FIRST_VALUE(salary) OVER (
        ORDER BY salary DESC
    ) - salary AS difference
FROM Employees;
```

| Name | Salary | Highest | Difference |
|---|---:|---:|---:|
| David | 80000 | 80000 | 0 |
| Bob | 70000 | 80000 | 10000 |
| Charlie | 60000 | 80000 | 20000 |
| Alice | 50000 | 80000 | 30000 |

### Summary

- `FIRST_VALUE()` returns the value from the first row of the current frame.
- `ORDER BY salary DESC` puts the highest salary first.
- `ORDER BY salary ASC` puts the lowest salary first.
- The frame matters: `FIRST_VALUE()` returns the first value within the frame, not necessarily the first row of the entire partition in every possible frame configuration.

---

## 11. Window Frames

Before learning `LAST_VALUE()`, understand window frames. They explain why `LAST_VALUE()` can return a value that seems unexpected.

### What is a window frame?

- `OVER()` defines the window of rows available to the function.
- The **frame** selects the subset of rows within that window used for the current calculation.

Think of it as:

```text
Entire window
    |
    +-- Current frame: the rows used for this calculation
```

### Example: Running sum

**Table: `Employees`**

| Name | Salary |
|---|---:|
| Alice | 1000 |
| Bob | 2000 |
| Charlie | 3000 |
| David | 4000 |

```sql
SELECT
    name,
    salary,
    SUM(salary) OVER (
        ORDER BY salary
        ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
    ) AS running_sum
FROM Employees;
```

**Result**

| Name | Salary | Running Sum |
|---|---:|---:|
| Alice | 1000 | 1000 |
| Bob | 2000 | 3000 |
| Charlie | 3000 | 6000 |
| David | 4000 | 10000 |

The frame grows row by row, starting at the first row and ending at the current row.

### Understanding frame boundaries

- `UNBOUNDED PRECEDING` — start at the first row of the partition.
- `CURRENT ROW` — end at the current row (with details affected by `ROWS` versus `RANGE`).
- `UNBOUNDED FOLLOWING` — extend to the last row of the partition.

### Default frame with `ORDER BY`

In many common SQL implementations, an ordered aggregate window without an explicit frame uses a default frame equivalent to:

```sql
RANGE BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
```

The exact default and support can vary by database. `RANGE` also treats peer rows with equal ordering values together, so an explicit `ROWS` frame is often clearer when you want a row-by-row running total.

To make a row-by-row running total explicit:

```sql
SUM(salary) OVER (
    ORDER BY salary
    ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
)
```

---

## 12. `LAST_VALUE()`

### Definition

`LAST_VALUE()` returns the value from the last row in the current window frame.

It does **not** automatically mean “the last value in the entire table.” The frame determines which rows are considered.

### Example

**Table: `Employees`**

| Name | Salary |
|---|---:|
| Alice | 1000 |
| Bob | 2000 |
| Charlie | 3000 |
| David | 4000 |

```sql
SELECT
    name,
    salary,
    LAST_VALUE(salary) OVER (
        ORDER BY salary
        ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
    ) AS last_sal
FROM Employees;
```

**Result**

| Name | Salary | LAST_VALUE |
|---|---:|---:|
| Alice | 1000 | 1000 |
| Bob | 2000 | 2000 |
| Charlie | 3000 | 3000 |
| David | 4000 | 4000 |

Because the frame ends at the current row, the last value in that frame is the current row's salary.

### How to get the actual last value in the partition

Extend the frame through the final row:

```sql
SELECT
    name,
    salary,
    LAST_VALUE(salary) OVER (
        ORDER BY salary
        ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING
    ) AS last_sal
FROM Employees;
```

**Result**

| Name | Salary | LAST_VALUE |
|---|---:|---:|
| Alice | 1000 | 4000 |
| Bob | 2000 | 4000 |
| Charlie | 3000 | 4000 |
| David | 4000 | 4000 |

### Easy analogy

Imagine reading a book:

- **Default-style frame:** Start at the first page and stop at the current page. The last page read is the current page.
- **`UNBOUNDED FOLLOWING`:** Consider the book through its final page. Now the last page is the actual final page.

### Interview question

**Q: Why does `LAST_VALUE()` often return the current row's value instead of the last value in the partition?**

**A:** Because the frame often ends at the current row. To get the value from the final row in the partition, explicitly extend the frame to `UNBOUNDED FOLLOWING`.

---

## 13. Aggregate Window Functions

Aggregate functions can also be used as window functions by adding `OVER()`.

Common examples include:

- `SUM() OVER()`
- `AVG() OVER()`
- `COUNT() OVER()`
- `MIN() OVER()`
- `MAX() OVER()`

Unlike a regular aggregate query with `GROUP BY`, these expressions preserve individual rows.

### Example table

| Employee | Department | Salary |
|---|---|---:|
| Alice | HR | 50000 |
| Bob | HR | 60000 |
| Charlie | IT | 70000 |
| David | IT | 80000 |

### `SUM() OVER()`

Calculates the total salary across the whole result and displays it for every row.

```sql
SELECT
    Employee,
    Salary,
    SUM(Salary) OVER () AS total_salary
FROM Employees;
```

Total salary: `260000`.

### `AVG() OVER()`

Calculates the average salary across the whole result.

```sql
SELECT
    Employee,
    Salary,
    AVG(Salary) OVER () AS average_salary
FROM Employees;
```

Average salary: `65000`.

### `COUNT() OVER()`

Counts rows in the window and displays the count on each row.

```sql
SELECT
    Employee,
    Salary,
    COUNT(*) OVER () AS employee_count
FROM Employees;
```

Each row shows `4`.

### `MIN() OVER()` and `MAX() OVER()`

```sql
SELECT
    Employee,
    Salary,
    MIN(Salary) OVER () AS minimum_salary,
    MAX(Salary) OVER () AS maximum_salary
FROM Employees;
```

Each row shows the minimum salary (`50000`) and maximum salary (`80000`).

### Aggregate calculations by group

```sql
SELECT
    Employee,
    Department,
    Salary,
    AVG(Salary) OVER (
        PARTITION BY Department
    ) AS department_average
FROM Employees;
```

- HR average: `55000`.
- IT average: `75000`.

### Running total

```sql
SELECT
    Employee,
    Salary,
    SUM(Salary) OVER (
        ORDER BY Salary
        ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
    ) AS running_total
FROM Employees;
```

This adds the current salary to all preceding salaries in the specified order.

---

## 14. Ranking Functions Comparison

Given marks `100, 95, 95, 90`:

| Function | Output | Behavior |
|---|---|---|
| `ROW_NUMBER()` | `1, 2, 3, 4` | Every row gets a unique number. |
| `RANK()` | `1, 2, 2, 4` | Ties share a rank; subsequent ranks are skipped. |
| `DENSE_RANK()` | `1, 2, 2, 3` | Ties share a rank; subsequent ranks are not skipped. |
| `NTILE(2)` | `1, 1, 2, 2` | Divides ordered rows into two approximately equal-sized buckets. |

**Note:** The example assumes a deterministic ordering for tied rows. `ROW_NUMBER()` and `NTILE()` can assign different numbers or buckets to tied rows depending on the ordering criteria.

### Easy analogy

Imagine a teacher:

- `ROW_NUMBER()` → Gives every student a unique roll number.
- `RANK()` → Gives competition ranks, with gaps after ties.
- `DENSE_RANK()` → Gives competition ranks, without gaps.
- `NTILE(4)` → Divides the class into four approximately equal-sized groups.

---

## 15. Choosing the Right Function

### Use `ROW_NUMBER()` when

- Every row must receive a unique number.
- You need one selected record per group.
- You want to identify duplicate occurrences.

### Use `RANK()` when

- Tied values should share a rank.
- Subsequent ranks should be skipped.
- You need competition-style rankings.

### Use `DENSE_RANK()` when

- Tied values should share a rank.
- Ranks should remain consecutive.
- You need the second- or third-highest distinct value.

### Use `NTILE()` when

- You want to divide rows into groups.
- You need approximately equal-sized buckets.
- You want to segment customers, employees, or other records.

### Use `LAG()` when

- You need the previous row's value.
- You want to compare current and previous measurements.

### Use `LEAD()` when

- You need the next row's value.
- You want to compare current and subsequent records.

### Use `FIRST_VALUE()` when

- You need the first value in the current frame.
- You want to compare rows with the first value in an ordered window.

### Use `LAST_VALUE()` when

- You need the last value in the current frame.
- You want the final partition value and have specified an appropriate frame.

### Use aggregate window functions when

- You need totals, averages, counts, minimums, or maximums while preserving individual rows.
- You need grouped averages or running totals.

---

## 16. Interview Questions

### Q1. What is the difference between `ROW_NUMBER()` and `RANK()`?

`ROW_NUMBER()` assigns a unique number to every row. `RANK()` gives tied rows the same rank and skips subsequent ranks.

### Q2. What is the difference between `RANK()` and `DENSE_RANK()`?

Both assign equal ranks to tied values. `RANK()` skips subsequent ranks, while `DENSE_RANK()` does not.

### Q3. Can `ROW_NUMBER()` assign the same number to two rows?

No. Every row receives a unique row number within its partition.

### Q4. What is the purpose of `NTILE(4)`?

It divides the ordered rows into four approximately equal-sized buckets.

### Q5. Which function is suitable for finding the second-highest distinct salary?

`DENSE_RANK()` is generally suitable because it assigns consecutive ranks to distinct salary values.

### Q6. What is the purpose of `PARTITION BY`?

It divides rows into groups so that a window function operates independently within each group.

### Q7. Does a window function reduce the number of rows returned?

No. Window functions calculate values for individual rows without collapsing them into groups. A separate filter can reduce the final result.

### Q8. What is the difference between `LAG()` and `LEAD()`?

`LAG()` accesses a previous row's value, while `LEAD()` accesses a subsequent row's value.

### Q9. Why can `LAST_VALUE()` return the current row's value?

Because the current window frame may end at the current row. Extending the frame to `UNBOUNDED FOLLOWING` allows it to access the final row in the partition.

### Q10. What is the difference between `GROUP BY` and window functions?

`GROUP BY` combines rows into groups and returns aggregate results for those groups. Window functions calculate values across related rows while retaining the individual rows.

---

## 17. Quick Summary

| Function | Main purpose | Example output |
|---|---|---|
| `ROW_NUMBER()` | Assigns a unique sequential number to every row. | `1, 2, 3, 4` |
| `RANK()` | Assigns equal ranks to ties and skips subsequent ranks. | `1, 2, 2, 4` |
| `DENSE_RANK()` | Assigns equal ranks to ties without skipping ranks. | `1, 2, 2, 3` |
| `NTILE(2)` | Divides ordered rows into two approximately equal-sized buckets. | `1, 1, 2, 2` |
| `LAG()` | Retrieves a value from a previous row. | Previous value |
| `LEAD()` | Retrieves a value from a following row. | Next value |
| `FIRST_VALUE()` | Retrieves the first value in the current frame. | First value |
| `LAST_VALUE()` | Retrieves the last value in the current frame. | Last frame value |
| `SUM() OVER()` | Calculates a sum while preserving rows. | Total or running total |
| `AVG() OVER()` | Calculates an average while preserving rows. | Overall or group average |
| `COUNT() OVER()` | Counts rows in the window. | Row count |
| `MIN() OVER()` | Finds the minimum value in the window. | Minimum |
| `MAX() OVER()` | Finds the maximum value in the window. | Maximum |

### Remember these rules

- `ROW_NUMBER()` → Every row gets a unique number.
- `RANK()` → Ties share a rank; gaps are created.
- `DENSE_RANK()` → Ties share a rank; no gaps are created.
- `NTILE(n)` → Rows are distributed across `n` approximately equal-sized buckets.
- `LAG()` → Look backward.
- `LEAD()` → Look forward.
- `FIRST_VALUE()` → Get the first value in the current frame.
- `LAST_VALUE()` → Get the last value in the current frame.
- `PARTITION BY` → Divide rows into groups.
- `ORDER BY` → Define the order used by the window function.
- Window frames → Specify which rows within the window are used for a calculation.

These concepts cover many SQL interview questions and common analytical tasks, including running totals, moving calculations, top-N-per-group queries, and time-series comparisons.
