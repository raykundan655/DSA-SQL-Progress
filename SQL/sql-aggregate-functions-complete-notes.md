# SQL Aggregate Functions --- Complete Notes

> Complete, GitHub-ready notes on SQL aggregate functions: what each
> function does, how `NULL` values are handled, examples, grouping,
> filtering, common mistakes, and practice questions.

**Dialect note:** Examples use common SQL syntax. Small differences
exist across MySQL, PostgreSQL, SQL Server, Oracle, and SQLite. The main
`COUNT`, `SUM`, `AVG`, `MIN`, and `MAX` behaviors described here are
standard across widely used SQL databases.

------------------------------------------------------------------------

## 1. What Is an Aggregate Function?

An **aggregate function** calculates one result from multiple rows.

For example, a table may contain the salaries of many employees.
`AVG(salary)` calculates their average salary, while `MAX(salary)`
returns the highest salary.

``` sql
SELECT AVG(salary) AS average_salary
FROM Employees;
```

Aggregate functions are commonly used with:

-   `SELECT` to calculate summary values.
-   `GROUP BY` to calculate a separate result for each group.
-   `HAVING` to filter groups based on aggregate results.
-   `WHERE` to filter rows **before** they are aggregated.
-   `DISTINCT` to aggregate unique values where appropriate.

## 2. Example Data

Use this sample table throughout the notes.

### Employees

    employee_id employee_name   department      salary   bonus
  ------------- --------------- ------------- -------- -------
              1 Asha            Engineering      50000    5000
              2 Ravi            Sales            65000    NULL
              3 Neha            Engineering      70000    7000
              4 Karan           Sales            80000    NULL
              5 Meera           Engineering      60000    4000
              6 Dev             HR                NULL    NULL

Notice that some values are `NULL`. In this example, `NULL` means a
value is missing or unknown. It is not the same as zero or an empty
string.

------------------------------------------------------------------------

## 3. The Five Core Aggregate Functions

The most important aggregate functions to learn first are:

1.  `COUNT()`
2.  `SUM()`
3.  `AVG()`
4.  `MIN()`
5.  `MAX()`

### NULL-handling summary

  -----------------------------------------------------------------------
  Function / expression               How it treats `NULL`
  ----------------------------------- -----------------------------------
  `COUNT(*)`                          Counts rows, including rows with
                                      `NULL` in any column

  `COUNT(column)`                     Counts only rows where that column
                                      is not `NULL`

  `COUNT(DISTINCT column)`            Counts distinct, non-`NULL` values
                                      in that column

  `SUM(column)`                       Ignores `NULL` values; returns
                                      `NULL` if there are no non-`NULL`
                                      inputs

  `AVG(column)`                       Ignores `NULL` values in both its
                                      sum and count; returns `NULL` if
                                      there are no non-`NULL` inputs

  `MIN(column)`                       Ignores `NULL` values; returns
                                      `NULL` if there are no non-`NULL`
                                      inputs

  `MAX(column)`                       Ignores `NULL` values; returns
                                      `NULL` if there are no non-`NULL`
                                      inputs
  -----------------------------------------------------------------------

This distinction is essential: **`COUNT(*)` counts rows, but
`COUNT(column)` counts non-`NULL` values in that column.**

------------------------------------------------------------------------

## 4. `COUNT()` --- Count Rows or Values

`COUNT()` counts rows or non-`NULL` values, depending on the expression
inside it.

### 4.1 `COUNT(*)` --- count all rows

``` sql
SELECT COUNT(*) AS total_employees
FROM Employees;
```

**Result:** `6`

Why? There are six rows. `COUNT(*)` counts each row even if some of its
columns contain `NULL`.

### 4.2 `COUNT(column)` --- count non-`NULL` values

``` sql
SELECT COUNT(salary) AS employees_with_salary
FROM Employees;
```

**Result:** `5`

Why? Five rows have a non-`NULL` salary. Dev's salary is `NULL`, so that
value is not counted.

### 4.3 `COUNT(DISTINCT column)` --- count unique, non-`NULL` values

``` sql
SELECT COUNT(DISTINCT department) AS distinct_departments
FROM Employees;
```

**Result:** `3`

The departments are Engineering, Sales, and HR. Repeated department
names count once. `COUNT(DISTINCT department)` does not count `NULL` as
a distinct value.

### 4.4 Count values that meet a condition

Use `WHERE` to filter rows before counting:

``` sql
SELECT COUNT(*) AS engineering_employees
FROM Employees
WHERE department = 'Engineering';
```

**Result:** `3`

### 4.5 Count rows with `NULL`

Use `IS NULL`, not `= NULL`.

``` sql
SELECT COUNT(*) AS employees_without_salary
FROM Employees
WHERE salary IS NULL;
```

**Result:** `1`

Count rows with a known salary:

``` sql
SELECT COUNT(*) AS employees_with_salary
FROM Employees
WHERE salary IS NOT NULL;
```

**Result:** `5`

### 4.6 Count multiple things in one query

``` sql
SELECT
    COUNT(*) AS total_rows,
    COUNT(salary) AS rows_with_salary,
    COUNT(bonus) AS rows_with_bonus,
    COUNT(DISTINCT department) AS distinct_departments
FROM Employees;
```

Expected results for the sample table:

  -----------------------------------------------------------------------------
         total_rows   rows_with_salary   rows_with_bonus   distinct_departments
  ----------------- ------------------ ----------------- ----------------------
                  6                  5                 3                      3

  -----------------------------------------------------------------------------

### 4.7 Conditional counting

A portable approach is to use `CASE` inside an aggregate:

``` sql
SELECT
    COUNT(CASE WHEN department = 'Engineering' THEN 1 END)
        AS engineering_count,
    COUNT(CASE WHEN salary >= 60000 THEN 1 END)
        AS employees_earning_at_least_60000
FROM Employees;
```

`CASE` returns `1` when the condition is true and otherwise returns
`NULL` because no `ELSE` is supplied. `COUNT(expression)` ignores those
`NULL` results.

Some databases also support syntax such as
`COUNT(*) FILTER (WHERE condition)`, while SQL Server commonly uses
`COUNT(CASE WHEN ... THEN 1 END)` for this pattern.

### 4.8 `COUNT(*)` versus `COUNT(1)`

In many databases, `COUNT(*)` and `COUNT(1)` both count rows. Prefer
`COUNT(*)` because it clearly expresses the intention to count rows. Do
not assume `COUNT(1)` is faster.

------------------------------------------------------------------------

## 5. `SUM()` --- Add Values

`SUM(column)` adds the non-`NULL` values in a numeric column.

``` sql
SELECT SUM(salary) AS total_salary
FROM Employees;
```

The `NULL` salary is ignored. The result is the sum of the five known
salaries:

`50000 + 65000 + 70000 + 80000 + 60000 = 325000`

### 5.1 Sum a column after filtering rows

``` sql
SELECT SUM(salary) AS engineering_salary_total
FROM Employees
WHERE department = 'Engineering';
```

The result is `180000`.

### 5.2 Sum distinct values

``` sql
SELECT SUM(DISTINCT salary) AS sum_of_unique_salaries
FROM Employees;
```

`SUM(DISTINCT salary)` adds each distinct non-`NULL` salary once. It is
not the usual choice for total payroll, because different employees may
legitimately earn the same salary and each employee should count toward
payroll.

### 5.3 What if every value is `NULL`?

For standard aggregate behavior, `SUM()` over no non-`NULL` input values
returns `NULL`, not zero.

If the report should display zero instead, use `COALESCE`:

``` sql
SELECT COALESCE(SUM(bonus), 0) AS total_bonus
FROM Employees
WHERE department = 'HR';
```

`COALESCE(value, 0)` returns `0` when the sum is `NULL`.

**Important distinction:** This changes how the result is displayed; it
does not mean the missing values in the source table were actually zero.

------------------------------------------------------------------------

## 6. `AVG()` --- Calculate the Average

`AVG(column)` calculates the arithmetic mean of the non-`NULL` values.

Conceptually:

``` text
AVG(column) = SUM(non-NULL values) / COUNT(non-NULL values)
```

Example:

``` sql
SELECT AVG(salary) AS average_salary
FROM Employees;
```

The five known salaries total `325000`, so the average is
`325000 / 5 = 65000`.

Dev's `NULL` salary is excluded from both the sum and the count. The
average is **not** calculated by dividing by all six rows.

### 6.1 Average after filtering

``` sql
SELECT AVG(salary) AS engineering_average_salary
FROM Employees
WHERE department = 'Engineering';
```

Calculation: `(50000 + 70000 + 60000) / 3 = 60000`.

### 6.2 Average with `DISTINCT`

``` sql
SELECT AVG(DISTINCT salary) AS average_of_unique_salaries
FROM Employees;
```

This averages unique, non-`NULL` salary values. It is different from the
average across employee rows.

### 6.3 Avoid accidentally including `NULL` as zero

`AVG(salary)` ignores `NULL`. If you write `AVG(COALESCE(salary, 0))`,
missing salaries are treated as zero for this calculation, changing the
meaning of the result. Do that only if zero is genuinely the intended
business rule.

------------------------------------------------------------------------

## 7. `MIN()` and `MAX()` --- Smallest and Largest Values

### 7.1 `MIN()`

Returns the smallest non-`NULL` value.

``` sql
SELECT MIN(salary) AS minimum_salary
FROM Employees;
```

Result: `50000`.

### 7.2 `MAX()`

Returns the largest non-`NULL` value.

``` sql
SELECT MAX(salary) AS maximum_salary
FROM Employees;
```

Result: `80000`.

### 7.3 `MIN()` and `MAX()` with text or dates

These functions are not limited to numeric columns. For text, they use
the database's comparison and collation rules. For dates, they return
the earliest or latest non-`NULL` date.

``` sql
SELECT MIN(employee_name) AS first_name_in_sort_order
FROM Employees;
```

The exact text ordering depends on collation and database settings.

``` sql
SELECT MAX(hire_date) AS latest_hire_date
FROM Employees;
```

This date example assumes the table has a `hire_date` column.

### 7.4 If all values are `NULL`

`MIN()` and `MAX()` return `NULL` when there are no non-`NULL` input
values.

------------------------------------------------------------------------

## 8. Aggregate Functions with `GROUP BY`

Without `GROUP BY`, an aggregate query usually produces one summary row
for the selected input set. With `GROUP BY`, it calculates a result for
each group.

### 8.1 Count employees in each department

``` sql
SELECT department, COUNT(*) AS employee_count
FROM Employees
GROUP BY department;
```

This returns one row for each department represented in the data.

### 8.2 Average salary by department

``` sql
SELECT department, AVG(salary) AS average_salary
FROM Employees
GROUP BY department;
```

For HR, the group has one employee but that employee's salary is `NULL`.
The HR average is therefore `NULL`, because there are no non-`NULL`
salaries in that group.

### 8.3 Count rows versus non-`NULL` values per group

``` sql
SELECT
    department,
    COUNT(*) AS employee_rows,
    COUNT(salary) AS employees_with_salary
FROM Employees
GROUP BY department;
```

For HR, `employee_rows = 1` and `employees_with_salary = 0`.

### 8.4 Multiple aggregate functions in one query

``` sql
SELECT
    department,
    COUNT(*) AS employee_count,
    COUNT(salary) AS salary_count,
    SUM(salary) AS total_salary,
    AVG(salary) AS average_salary,
    MIN(salary) AS minimum_salary,
    MAX(salary) AS maximum_salary
FROM Employees
GROUP BY department;
```

This is a common reporting pattern. Notice that `COUNT(*)` and
`COUNT(salary)` can differ in the same group.

------------------------------------------------------------------------

## 9. `WHERE` versus `HAVING`

Both filter data, but they operate at different logical stages.

-   `WHERE` filters individual rows before grouping and aggregation.
-   `HAVING` filters groups after `GROUP BY` and aggregate calculations.

### `WHERE` example

``` sql
SELECT department, AVG(salary) AS average_salary
FROM Employees
WHERE salary IS NOT NULL
GROUP BY department;
```

This removes rows with `NULL` salary before grouping. In this particular
example, the resulting averages match the averages from grouping all
rows because `AVG` already ignores `NULL`. However, other aggregates
such as `COUNT(*)` would change.

### `HAVING` example

``` sql
SELECT department, AVG(salary) AS average_salary
FROM Employees
GROUP BY department
HAVING AVG(salary) > 60000;
```

This returns departments whose average salary exceeds 60,000.

### Use both

``` sql
SELECT department, AVG(salary) AS average_salary
FROM Employees
WHERE salary IS NOT NULL
GROUP BY department
HAVING AVG(salary) > 55000;
```

Rows are filtered first; the resulting department groups are then
filtered by their averages.

------------------------------------------------------------------------

## 10. `DISTINCT` with Aggregates

`DISTINCT` makes an aggregate operate on unique values rather than every
non-`NULL` input value.

``` sql
SELECT
    COUNT(salary) AS salary_values_count,
    COUNT(DISTINCT salary) AS unique_salary_count,
    SUM(salary) AS total_salary,
    SUM(DISTINCT salary) AS sum_of_unique_salaries
FROM Employees;
```

For the sample data, all five known salaries are different, so
`COUNT(salary)` and `COUNT(DISTINCT salary)` happen to be equal. They
can differ when salaries repeat.

**Remember:** - `COUNT(DISTINCT column)` ignores `NULL`. -
`SUM(DISTINCT column)` ignores `NULL` and adds each distinct value
once. - `AVG(DISTINCT column)` averages unique non-`NULL` values.

Do not use `DISTINCT` automatically; decide whether duplicate values
should count more than once for the question being answered.

------------------------------------------------------------------------

## 11. Other Useful Aggregate Functions

The functions below are useful but their availability and syntax vary
more by database.

### 11.1 `STRING_AGG()` / `GROUP_CONCAT()` --- combine text values

These functions combine values from multiple rows into a string.

**PostgreSQL and SQL Server (modern versions):**

``` sql
SELECT
    department,
    STRING_AGG(employee_name, ', ') AS employee_names
FROM Employees
GROUP BY department;
```

**MySQL:**

``` sql
SELECT
    department,
    GROUP_CONCAT(employee_name SEPARATOR ', ') AS employee_names
FROM Employees
GROUP BY department;
```

These names and syntaxes are not interchangeable across all databases.
Ordering within the combined string is dialect-specific. `NULL` inputs
are typically skipped.

### 11.2 Boolean aggregates

Some databases support boolean aggregates such as `BOOL_AND()` and
`BOOL_OR()`, while others use different names or expressions.

Conceptually: - Boolean AND aggregate: true only if all relevant boolean
inputs are true. - Boolean OR aggregate: true if at least one relevant
boolean input is true.

Check the database's documentation for supported names and `NULL`
behavior.

### 11.3 Statistical aggregates

Some databases support functions such as: - `STDDEV_POP()` ---
population standard deviation. - `STDDEV_SAMP()` --- sample standard
deviation. - `VAR_POP()` --- population variance. - `VAR_SAMP()` ---
sample variance.

Names and availability vary. These functions are useful for statistical
summaries, but they are not as portable as `COUNT`, `SUM`, `AVG`, `MIN`,
and `MAX`.

------------------------------------------------------------------------

## 12. `NULL` Handling --- Important Rules

This is one of the most important sections for SQL interviews.

### Rule 1: `COUNT(*)` counts rows

``` sql
SELECT COUNT(*) FROM Employees;
```

Result: `6`, including the row whose salary is `NULL`.

### Rule 2: `COUNT(column)` counts non-`NULL` values

``` sql
SELECT COUNT(salary) FROM Employees;
```

Result: `5`.

### Rule 3: Most numeric aggregates ignore `NULL`

`SUM(salary)`, `AVG(salary)`, `MIN(salary)`, and `MAX(salary)` ignore
the `NULL` salary. If there are no non-`NULL` inputs, these functions
return `NULL`.

### Rule 4: `NULL` is not zero

-   `NULL` means missing or unknown.
-   `0` is a numeric value.
-   An empty string is a string value in systems that distinguish it
    from `NULL`.

Do not assume missing salary means the employee earns zero.

### Rule 5: Use `IS NULL`, not `= NULL`

Correct:

``` sql
SELECT *
FROM Employees
WHERE salary IS NULL;
```

Incorrect:

``` sql
SELECT *
FROM Employees
WHERE salary = NULL;
```

Ordinary equality comparisons with `NULL` do not work as a null test.

### Rule 6: `COALESCE()` can replace a `NULL` result

``` sql
SELECT COALESCE(SUM(bonus), 0) AS total_bonus
FROM Employees
WHERE department = 'HR';
```

This displays zero if the sum is `NULL`. It does not change source data.

### Rule 7: Aggregates can behave differently on empty input

For a query with no matching rows: - `COUNT(*)` returns `0` in a scalar
aggregate query. - `COUNT(column)` returns `0`. - `SUM`, `AVG`, `MIN`,
and `MAX` generally return `NULL` because there are no non-`NULL` input
values.

With `GROUP BY`, if no rows match, there are no groups to output, so the
query typically returns zero result rows rather than one summary row.

------------------------------------------------------------------------

## 13. Common Mistakes

### Mistake 1: Confusing `COUNT(*)` and `COUNT(column)`

``` sql
SELECT COUNT(*), COUNT(salary)
FROM Employees;
```

The first counts six rows; the second counts five non-`NULL` salary
values.

### Mistake 2: Treating `NULL` as zero in an average

`AVG(salary)` ignores missing salaries. `AVG(COALESCE(salary, 0))`
includes them as zeros and changes the result.

### Mistake 3: Using an aggregate in `WHERE`

This is generally invalid:

``` sql
SELECT department, AVG(salary)
FROM Employees
WHERE AVG(salary) > 60000
GROUP BY department;
```

Use `HAVING` for a condition on a group aggregate:

``` sql
SELECT department, AVG(salary) AS average_salary
FROM Employees
GROUP BY department
HAVING AVG(salary) > 60000;
```

### Mistake 4: Selecting a regular column that is not grouped

This is not portable and is rejected by many databases:

``` sql
SELECT department, employee_name, AVG(salary)
FROM Employees
GROUP BY department;
```

There may be multiple employee names per department, so the query does
not specify which name should be displayed. Group the relevant columns,
aggregate the name appropriately, or change the query.

### Mistake 5: Forgetting join multiplication

When a table is joined to another table with multiple matching rows, the
join may duplicate rows before aggregation. For example, a salary could
be counted or summed more than once. Understand the join relationship
before aggregating joined data.

### Mistake 6: Assuming `SUM()` over no values returns zero

A sum with no non-`NULL` inputs generally returns `NULL`. Use
`COALESCE(SUM(column), 0)` only if zero is the desired reporting value.

### Mistake 7: Using `DISTINCT` without understanding the meaning

`SUM(DISTINCT salary)` deduplicates salary values, not employees. Two
employees with the same salary contribute only once to that expression.

------------------------------------------------------------------------

## 14. Practical Examples

### Example 1: Overall company summary

``` sql
SELECT
    COUNT(*) AS employee_rows,
    COUNT(salary) AS known_salary_count,
    SUM(salary) AS total_known_salary,
    AVG(salary) AS average_known_salary,
    MIN(salary) AS lowest_known_salary,
    MAX(salary) AS highest_known_salary
FROM Employees;
```

### Example 2: Department summary

``` sql
SELECT
    department,
    COUNT(*) AS employee_count,
    COUNT(salary) AS salary_count,
    COALESCE(SUM(salary), 0) AS total_salary_for_report,
    AVG(salary) AS average_salary
FROM Employees
GROUP BY department;
```

Here, `COALESCE` displays `0` for a department with no known salary
values. `AVG(salary)` remains `NULL` for that department.

### Example 3: Departments with at least three employees

``` sql
SELECT department, COUNT(*) AS employee_count
FROM Employees
GROUP BY department
HAVING COUNT(*) >= 3;
```

### Example 4: Count employees with a bonus

``` sql
SELECT COUNT(bonus) AS employees_with_bonus
FROM Employees;
```

This counts non-`NULL` bonus values, not the total employee rows.

### Example 5: Count employees without a bonus

``` sql
SELECT COUNT(*) AS employees_without_bonus
FROM Employees
WHERE bonus IS NULL;
```

### Example 6: Conditional count by department

``` sql
SELECT
    department,
    COUNT(*) AS total_employees,
    COUNT(CASE WHEN salary >= 60000 THEN 1 END) AS employees_earning_at_least_60000
FROM Employees
GROUP BY department;
```

------------------------------------------------------------------------

## 15. Practice Questions

Use the sample `Employees` table.

1.  Count all employee rows.
2.  Count employees with a non-`NULL` salary.
3.  Count employees whose salary is `NULL`.
4.  Count distinct departments.
5.  Find the total known salary.
6.  Find the average known salary.
7.  Find the minimum and maximum known salaries.
8.  Count employees in each department.
9.  Show both row count and non-`NULL` salary count for each department.
10. Find departments whose average salary is greater than 55,000.
11. Count employees with a non-`NULL` bonus.
12. Display zero instead of `NULL` for the total bonus in HR.
13. Explain the difference between `COUNT(*)`, `COUNT(salary)`, and
    `COUNT(DISTINCT salary)`.
14. Explain why `AVG(COALESCE(salary, 0))` may produce a different
    result from `AVG(salary)`.
15. Explain why an aggregate condition belongs in `HAVING` rather than
    `WHERE`.

## 16. Practice Solutions

### 1. Count all employee rows

``` sql
SELECT COUNT(*) AS total_employees
FROM Employees;
```

### 2. Count non-`NULL` salaries

``` sql
SELECT COUNT(salary) AS employees_with_salary
FROM Employees;
```

### 3. Count `NULL` salaries

``` sql
SELECT COUNT(*) AS employees_without_salary
FROM Employees
WHERE salary IS NULL;
```

### 4. Count distinct departments

``` sql
SELECT COUNT(DISTINCT department) AS distinct_departments
FROM Employees;
```

### 5. Total known salary

``` sql
SELECT SUM(salary) AS total_salary
FROM Employees;
```

### 6. Average known salary

``` sql
SELECT AVG(salary) AS average_salary
FROM Employees;
```

### 7. Minimum and maximum salaries

``` sql
SELECT
    MIN(salary) AS minimum_salary,
    MAX(salary) AS maximum_salary
FROM Employees;
```

### 8. Employee count by department

``` sql
SELECT department, COUNT(*) AS employee_count
FROM Employees
GROUP BY department;
```

### 9. Rows versus known salaries by department

``` sql
SELECT
    department,
    COUNT(*) AS employee_rows,
    COUNT(salary) AS known_salary_count
FROM Employees
GROUP BY department;
```

### 10. Departments with average salary above 55,000

``` sql
SELECT department, AVG(salary) AS average_salary
FROM Employees
GROUP BY department
HAVING AVG(salary) > 55000;
```

### 11. Count non-`NULL` bonuses

``` sql
SELECT COUNT(bonus) AS employees_with_bonus
FROM Employees;
```

### 12. HR total bonus displayed as zero if `NULL`

``` sql
SELECT COALESCE(SUM(bonus), 0) AS total_bonus
FROM Employees
WHERE department = 'HR';
```

### 13. Compare the three `COUNT` expressions

-   `COUNT(*)` counts all rows.
-   `COUNT(salary)` counts rows where `salary` is not `NULL`.
-   `COUNT(DISTINCT salary)` counts unique non-`NULL` salary values.

### 14. Why can `AVG(COALESCE(salary, 0))` differ?

`AVG(salary)` ignores missing salaries. `AVG(COALESCE(salary, 0))`
replaces each `NULL` salary with zero before calculating the average, so
those rows contribute to the denominator.

### 15. Why `HAVING` instead of `WHERE`?

`WHERE` filters individual rows before aggregation. `HAVING` filters
groups after aggregate values have been calculated.

------------------------------------------------------------------------

## 17. Final Revision Checklist

-   [ ] Explain what aggregate functions do.
-   [ ] Know `COUNT`, `SUM`, `AVG`, `MIN`, and `MAX`.
-   [ ] Explain `COUNT(*)` versus `COUNT(column)`.
-   [ ] Explain `COUNT(DISTINCT column)`.
-   [ ] Know how each core aggregate handles `NULL`.
-   [ ] Count `NULL` values using `WHERE column IS NULL`.
-   [ ] Explain how `COALESCE` affects displayed results.
-   [ ] Use aggregate functions with `GROUP BY`.
-   [ ] Distinguish `WHERE` from `HAVING`.
-   [ ] Understand `DISTINCT` inside aggregates.
-   [ ] Know that join multiplication can inflate aggregate results.
-   [ ] Recognize database-specific functions such as `STRING_AGG`,
    `GROUP_CONCAT`, and statistical aggregates.

## Quick memory rule

-   **`COUNT(*)`** → counts rows.
-   **`COUNT(column)`** → counts non-`NULL` values.
-   **`COUNT(DISTINCT column)`** → counts unique, non-`NULL` values.
-   **`SUM`, `AVG`, `MIN`, `MAX`** → ignore `NULL` inputs; return `NULL`
    if there are no non-`NULL` inputs.
-   **`GROUP BY`** → calculates aggregates per group.
-   **`WHERE`** → filters rows before aggregation.
-   **`HAVING`** → filters groups after aggregation.
