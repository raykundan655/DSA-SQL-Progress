# SQL Window Functions — Complete Notes

A beginner-friendly, interview-ready guide to SQL window functions, built up concept by concept.

---

## Table of Contents

1. [Window Functions Overview](#window-functions-overview)
2. [Understanding OVER()](#understanding-over)
3. [FIRST_VALUE()](#first_value)
4. [Window Frames](#window-frames)
5. [LAST_VALUE()](#last_value)
6. [NTILE()](#ntile)
7. [Ranking Functions Comparison](#ranking-functions-comparison)
8. [Quick Summary](#quick-summary)

---

## Window Functions Overview

Recommended learning order (each builds on the previous concept):

- `ROW_NUMBER()`
- `RANK()`
- `DENSE_RANK()`
- `NTILE()`
- `LAG()`
- `LEAD()`
- `FIRST_VALUE()`
- `LAST_VALUE()`
- `SUM() OVER()`
- `AVG() OVER()`
- `COUNT() OVER()`
- `MIN() OVER()`
- `MAX() OVER()`

---

## Understanding OVER()

**Simple definition:**
> `OVER()` tells SQL which rows the window function should look at *before* performing the calculation.

### Example 1: `OVER()` — Whole Table

**Table: Students**

| Name    | Marks |
|---------|-------|
| Alice   | 90    |
| Bob     | 80    |
| Charlie | 95    |
| David   | 70    |

```sql
SELECT
    name,
    marks,
    AVG(marks) OVER() AS avg_marks
FROM Students;
```

**How it works:**
1. `OVER()` says: *"Look at all rows."*
2. Calculate the average: `(90 + 80 + 95 + 70) / 4 = 83.75`
3. Show the result for every row.

**Result:**

| Name    | Marks | Avg_Marks |
|---------|-------|-----------|
| Alice   | 90    | 83.75     |
| Bob     | 80    | 83.75     |
| Charlie | 95    | 83.75     |
| David   | 70    | 83.75     |

---

### Example 2: `PARTITION BY` — Look Within Groups

```sql
AVG(salary) OVER(PARTITION BY department)
```

> "Don't look at the whole table. Look only within each department."

**Table: Employees**

| Name    | Department | Salary |
|---------|------------|--------|
| Alice   | HR         | 50000  |
| Bob     | HR         | 60000  |
| Charlie | IT         | 70000  |
| David   | IT         | 80000  |

- **HR average:** Alice (50000) + Bob (60000) → `55000`
- **IT average:** Charlie (70000) + David (80000) → `75000`

---

### Example 3: `ORDER BY` — Running Totals

```sql
SUM(salary) OVER(ORDER BY salary)
```

> "First arrange the rows by salary, then calculate the running total."

Sorted rows: `50000, 60000, 70000, 80000`

Running total:
```
50000
50000 + 60000 = 110000
110000 + 70000 = 180000
180000 + 80000 = 260000
```

---

### Interview-Ready Definition

> `OVER()` defines the **"window"** (the set of rows) on which a window function operates.

| Clause                        | Meaning                                  |
|-------------------------------|-------------------------------------------|
| `OVER()`                      | Entire table                              |
| `OVER(PARTITION BY ...)`      | Rows within each group                    |
| `OVER(ORDER BY ...)`          | Rows in a specific order (running totals, ranking, etc.) |

### Easy Analogy 📚

Imagine you're in a classroom:

- `OVER()` → Look at the entire class.
- `OVER(PARTITION BY section)` → Look at only your section.
- `OVER(ORDER BY marks)` → Line everyone up by marks, then do the calculation.

---

## FIRST_VALUE()

Returns the value from the **first row in the window**.

**Analogy:** Students standing by marks — Alice (95), Bob (90), Charlie (80), David (70). Ask anyone "who's the topper?" — the answer is always **Alice**. That's `FIRST_VALUE()`.

### Syntax

```sql
FIRST_VALUE(column) OVER(ORDER BY ...)
```

### Example

**Table: Employees**

| Name    | Salary |
|---------|--------|
| Alice   | 50000  |
| Bob     | 70000  |
| Charlie | 60000  |
| David   | 80000  |

```sql
SELECT
    name,
    salary,
    FIRST_VALUE(salary) OVER(ORDER BY salary DESC) AS highest_salary
FROM Employees;
```

**Step 1 — Sort by salary descending:**
```
David    80000
Bob      70000
Charlie  60000
Alice    50000
```

**Step 2 — First salary in window is always `80000`.**

**Final Output:**

| Name    | Salary | Highest Salary |
|---------|--------|-----------------|
| David   | 80000  | 80000           |
| Bob     | 70000  | 80000           |
| Charlie | 60000  | 80000           |
| Alice   | 50000  | 80000           |

Every row now knows the highest salary.

### Using PARTITION BY

**Table: Employees**

| Name    | Dept | Salary |
|---------|------|--------|
| Alice   | HR   | 50000  |
| Bob     | HR   | 60000  |
| Charlie | IT   | 70000  |
| David   | IT   | 80000  |

```sql
SELECT
    name,
    dept,
    salary,
    FIRST_VALUE(salary) OVER(
        PARTITION BY dept
        ORDER BY salary DESC
    ) AS highest_salary
FROM Employees;
```

**Result:** each department gets its own highest salary.

| Name    | Dept | Salary | Highest Salary |
|---------|------|--------|-----------------|
| Bob     | HR   | 60000  | 60000           |
| Alice   | HR   | 50000  | 60000           |
| David   | IT   | 80000  | 80000           |
| Charlie | IT   | 70000  | 80000           |

### Real Interview Example — Salary Gap from Top Earner

```sql
SELECT
    name,
    salary,
    FIRST_VALUE(salary) OVER(ORDER BY salary DESC) AS highest_salary,
    FIRST_VALUE(salary) OVER(ORDER BY salary DESC) - salary AS difference
FROM Employees;
```

| Name    | Salary | Highest | Difference |
|---------|--------|---------|------------|
| David   | 80000  | 80000   | 0          |
| Bob     | 70000  | 80000   | 10000      |
| Charlie | 60000  | 80000   | 20000      |
| Alice   | 50000  | 80000   | 30000      |

### Summary

- `FIRST_VALUE()` always returns the value from the **first row of the current window**.
- `ORDER BY salary DESC` → first row is the **highest** salary.
- `ORDER BY salary ASC` → first row is the **lowest** salary.

---

## Window Frames

> ⚠️ Before learning `LAST_VALUE()`, understand window frames — otherwise `LAST_VALUE()` will seem "wrong."

### What is a Window Frame?

- `OVER()` answers: **"Which rows can I look at?"** (the window)
- The **frame** answers: **"Among those rows, which ones should I use for THIS calculation?"**

```
Entire Table (Window)
        ↓
Some rows inside it (Frame)
```

### Example — Running Sum

**Table: Employees**

| Name    | Salary |
|---------|--------|
| Alice   | 1000   |
| Bob     | 2000   |
| Charlie | 3000   |
| David   | 4000   |

```sql
SELECT
    name,
    salary,
    SUM(salary) OVER(ORDER BY salary)
FROM Employees;
```

**Result:**

| Name    | Salary | Running Sum |
|---------|--------|--------------|
| Alice   | 1000   | 1000         |
| Bob     | 2000   | 3000         |
| Charlie | 3000   | 6000         |
| David   | 4000   | 10000        |

**Why?** The frame keeps growing row by row.

### SQL's Default Frame

When SQL sees:
```sql
OVER(ORDER BY salary)
```

It secretly means:
```sql
OVER(
    ORDER BY salary
    RANGE BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
)
```

- **`UNBOUNDED PRECEDING`** → Start from the first row.
- **`CURRENT ROW`** → Stop at the current row.

So SQL takes rows from the **first row → current row**, creating a running window.

---

## LAST_VALUE()

**Most misunderstood window function.**

Most beginners think `LAST_VALUE(salary)` means *"give me the last salary in the table."*

**It doesn't.** It means:
> *"Give me the last value inside the current frame."*

### Example

**Table: Employees**

| Name    | Salary |
|---------|--------|
| Alice   | 1000   |
| Bob     | 2000   |
| Charlie | 3000   |
| David   | 4000   |

```sql
SELECT
    name,
    salary,
    LAST_VALUE(salary) OVER(ORDER BY salary) AS last_sal
FROM Employees;
```

**Result:**

| Name    | Salary | LAST_VALUE |
|---------|--------|-------------|
| Alice   | 1000   | 1000        |
| Bob     | 2000   | 2000        |
| Charlie | 3000   | 3000        |
| David   | 4000   | 4000        |

Because the default frame grows only up to the **current row**, the "last value" in that frame is always the current row's own value.

### How to Get the Actual Last Value

Tell SQL not to stop at the current row — go until the very last row:

```sql
SELECT
    name,
    salary,
    LAST_VALUE(salary) OVER(
        ORDER BY salary
        ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING
    ) AS highest_salary
FROM Employees;
```

**Result:**

| Name    | Salary | LAST_VALUE |
|---------|--------|-------------|
| Alice   | 1000   | 4000        |
| Bob     | 2000   | 4000        |
| Charlie | 3000   | 4000        |
| David   | 4000   | 4000        |

### Easy Trick

Imagine reading a book:

- **Default frame** = Start → Current Page. You don't know what's on future pages, so the "last page you've read" is simply the current page.
- **`UNBOUNDED FOLLOWING`** = Someone gives you the whole book (Start → End). Now the last page is truly the final page.

### ⭐ Interview Tip

**Q: Why does `LAST_VALUE()` often return the current row instead of the last row?**

**A:** Because the default window frame runs from the first row to the current row (`UNBOUNDED PRECEDING` to `CURRENT ROW`). Therefore, the last value in that frame is the current row itself. To get the true last row of the partition, extend the frame to `UNBOUNDED FOLLOWING`.

---

## NTILE()

Divides rows into **n nearly equal groups (buckets)** — useful for quartiles, top 25%, etc.

**Analogy:** A teacher dividing students into 4 groups based on marks — not ranks, but group numbers.

### Example — Even Split

**Table: Students** (8 students)

| Name | Marks |
|------|-------|
| A    | 98    |
| B    | 95    |
| C    | 90    |
| D    | 88    |
| E    | 82    |
| F    | 80    |
| G    | 75    |
| H    | 70    |

```sql
SELECT
    name,
    marks,
    NTILE(4) OVER(ORDER BY marks DESC) AS bucket
FROM Students;
```

8 rows ÷ 4 buckets = 2 rows per bucket.

| Name | Marks | Bucket |
|------|-------|--------|
| A    | 98    | 1      |
| B    | 95    | 1      |
| C    | 90    | 2      |
| D    | 88    | 2      |
| E    | 82    | 3      |
| F    | 80    | 3      |
| G    | 75    | 4      |
| H    | 70    | 4      |

### Example — Uneven Split

10 students ÷ 4 buckets = 2.5 → not possible. **SQL gives extra rows to earlier buckets.**

```sql
SELECT
    name,
    marks,
    NTILE(4) OVER(ORDER BY marks DESC)
FROM Students;
```

| Name | Marks | Bucket |
|------|-------|--------|
| A    | 99    | 1      |
| B    | 98    | 1      |
| C    | 97    | 1      |
| D    | 96    | 2      |
| E    | 95    | 2      |
| F    | 94    | 2      |
| G    | 93    | 3      |
| H    | 92    | 3      |
| I    | 91    | 4      |
| J    | 90    | 4      |

Buckets 1 & 2 got 3 rows each; buckets 3 & 4 got 2 rows each.

### Using PARTITION BY

**Table: Employees**

| Employee | Dept | Salary |
|----------|------|--------|
| A        | HR   | 90000  |
| B        | HR   | 80000  |
| C        | HR   | 70000  |
| D        | HR   | 60000  |
| E        | IT   | 95000  |
| F        | IT   | 85000  |
| G        | IT   | 75000  |
| H        | IT   | 65000  |

```sql
SELECT
    employee,
    dept,
    salary,
    NTILE(2) OVER(
        PARTITION BY dept
        ORDER BY salary DESC
    ) AS bucket
FROM Employees;
```

| Employee | Dept | Salary | Bucket |
|----------|------|--------|--------|
| A        | HR   | 90000  | 1      |
| B        | HR   | 80000  | 1      |
| C        | HR   | 70000  | 2      |
| D        | HR   | 60000  | 2      |
| E        | IT   | 95000  | 1      |
| F        | IT   | 85000  | 1      |
| G        | IT   | 75000  | 2      |
| H        | IT   | 65000  | 2      |

### Real Interview Questions

**Find Top 25% Employees:**
```sql
SELECT
    name,
    salary,
    NTILE(4) OVER(ORDER BY salary DESC) AS quartile
FROM Employees;
```
Employees with `Quartile = 1` are the top 25%.

**Divide Customers into Gold, Silver, Bronze:**
```sql
NTILE(3)
```
- `1` → Gold
- `2` → Silver
- `3` → Bronze

---

## Ranking Functions Comparison

Given marks: `100, 95, 95, 90`

| Function        | Output          | Behavior                          |
|------------------|-----------------|-------------------------------------|
| `ROW_NUMBER()`   | `1, 2, 3, 4`    | Every row gets a unique number     |
| `RANK()`         | `1, 2, 2, 4`    | Skips ranks after ties             |
| `DENSE_RANK()`   | `1, 2, 2, 3`    | No skipped ranks after ties        |
| `NTILE(2)`       | `1, 1, 2, 2`    | Ignores ties — just splits into equal buckets |

### Easy Trick

Imagine a teacher:

- `ROW_NUMBER()` → Gives every student a roll number.
- `RANK()` → Gives competition ranks (with gaps).
- `DENSE_RANK()` → Gives competition ranks (without gaps).
- `NTILE(4)` → Divides the class into 4 sections.

---

## Quick Summary

Functions covered, in learning order:

- ✅ `OVER()`
- ✅ `SUM() OVER()`, `AVG() OVER()`, `COUNT() OVER()`
- ✅ `ROW_NUMBER()`
- ✅ `RANK()`
- ✅ `DENSE_RANK()`
- ✅ `LAG()`
- ✅ `LEAD()`
- ✅ `FIRST_VALUE()`
- ✅ `LAST_VALUE()`
- ✅ `NTILE()`

These cover the vast majority of window function questions asked in SQL interviews. Beyond these, most real-world problems (running totals, moving averages, top-N per group, time-series comparisons) are just different combinations of `PARTITION BY`, `ORDER BY`, and window frames.
