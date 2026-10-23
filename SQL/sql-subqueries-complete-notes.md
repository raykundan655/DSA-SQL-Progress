# SQL Subqueries --- Complete Notes

> GitHub-ready study notes covering SQL subqueries, their types,
> operators, common use cases, mistakes, and practice questions.

**Dialect note:** SQL features vary slightly across databases. Check
your database's documentation for dialect-specific syntax.

## 1. What is a subquery?

A **subquery** is a SQL query nested inside another SQL statement. The
nested query is the *inner query*; the query that uses its result is the
*outer query*.

``` sql
SELECT employee_name, salary
FROM Employees
WHERE salary > (
    SELECT AVG(salary)
    FROM Employees
);
```

The inner query calculates the average salary. The outer query returns
employees earning more than that average.

### Example tables

**Employees**

    employee_id employee_name     department_id   salary   manager_id
  ------------- --------------- --------------- -------- ------------
              1 Asha                         10    50000            4
              2 Ravi                         20    65000            4
              3 Neha                         10    70000            5
              4 Karan                        20    80000         NULL
              5 Meera                        10    60000            4

**Departments**

    department_id department_name
  --------------- -----------------
               10 Engineering
               20 Sales
               30 HR

## 2. Types of subqueries by returned result

### 2.1 Scalar subquery

Returns one value: one row and one column.

``` sql
SELECT employee_name, salary
FROM Employees
WHERE salary > (SELECT AVG(salary) FROM Employees);
```

Common uses include comparisons with `AVG()`, `MAX()`, `MIN()`, or a
single ID.

**Important:** A scalar subquery used as a value must not return
multiple rows. Many databases raise an error if it does. If it returns
no rows, its scalar result is generally `NULL`.

### 2.2 Multiple-row, single-column subquery

Returns multiple values in one column. Use operators such as `IN`,
`ANY`, `SOME`, or `ALL` as appropriate.

``` sql
SELECT employee_name
FROM Employees
WHERE department_id IN (
    SELECT department_id
    FROM Departments
    WHERE department_name IN ('Engineering', 'Sales')
);
```

### 2.3 Multiple-column subquery

Some databases support row-value comparisons and multi-column subqueries
in certain contexts. Syntax and support vary.

``` sql
SELECT *
FROM Employees
WHERE (department_id, salary) IN (
    SELECT department_id, MAX(salary)
    FROM Employees
    GROUP BY department_id
);
```

This finds rows whose department and salary match a department's maximum
salary, where row-value comparison is supported. A grouped subquery
joined to the table is an alternative if your database does not support
this syntax.

## 3. Subqueries in different clauses

### 3.1 In `WHERE`

Used to filter rows based on another query's result.

``` sql
SELECT employee_name
FROM Employees
WHERE department_id = (
    SELECT department_id
    FROM Departments
    WHERE department_name = 'Sales'
);
```

This assumes that `Sales` identifies exactly one department.

### 3.2 In `SELECT`

A scalar subquery can calculate a value displayed beside each output
row.

``` sql
SELECT
    employee_name,
    salary,
    (SELECT AVG(salary) FROM Employees) AS company_avg_salary
FROM Employees;
```

The same company-wide average appears for every employee.

### 3.3 In `FROM` --- derived table

A subquery in `FROM` creates a result set for the outer query. This is
commonly called a **derived table**.

``` sql
SELECT department_id, average_salary
FROM (
    SELECT department_id, AVG(salary) AS average_salary
    FROM Employees
    GROUP BY department_id
) AS department_stats
WHERE average_salary > 60000;
```

The inner query calculates each department's average; the outer query
filters the calculated result. Many databases require an alias for a
derived table.

### 3.4 In `HAVING`

`HAVING` filters groups after aggregation.

``` sql
SELECT department_id, AVG(salary) AS average_salary
FROM Employees
GROUP BY department_id
HAVING AVG(salary) > (
    SELECT AVG(salary)
    FROM Employees
);
```

This returns departments whose average salary is above the overall
average.

### 3.5 In data-modification statements

Subqueries may be used in `INSERT`, `UPDATE`, or `DELETE` statements,
subject to database-specific rules.

``` sql
UPDATE Employees
SET salary = salary * 1.05
WHERE department_id = (
    SELECT department_id
    FROM Departments
    WHERE department_name = 'Engineering'
);
```

This increases Engineering salaries by 5%. Before running an `UPDATE` or
`DELETE`, test the matching rows with a `SELECT` and use a transaction
when appropriate.

## 4. `IN` and `NOT IN`

### `IN`

Checks whether a value matches any value returned by the subquery.

``` sql
SELECT employee_name
FROM Employees
WHERE department_id IN (
    SELECT department_id
    FROM Departments
    WHERE department_name IN ('Engineering', 'Sales')
);
```

### `NOT IN`

Checks that a value does not match any value in the returned set.

``` sql
SELECT department_name
FROM Departments
WHERE department_id NOT IN (
    SELECT department_id
    FROM Employees
);
```

This is straightforward only when the subquery's returned IDs do not
include `NULL`.

**NULL warning:** If a `NOT IN` subquery returns `NULL`, SQL's
three-valued logic can cause the condition to evaluate to `UNKNOWN`,
leading to unexpected results. `NOT EXISTS` is often safer for finding
rows with no match.

## 5. `EXISTS` and `NOT EXISTS`

`EXISTS` is true if the subquery returns at least one row. `NOT EXISTS`
is true if it returns no rows. The selected expression inside the
subquery usually does not matter; `SELECT 1` is conventional.

### `EXISTS`: departments that have employees

``` sql
SELECT d.department_id, d.department_name
FROM Departments AS d
WHERE EXISTS (
    SELECT 1
    FROM Employees AS e
    WHERE e.department_id = d.department_id
);
```

### `NOT EXISTS`: departments without employees

``` sql
SELECT d.department_id, d.department_name
FROM Departments AS d
WHERE NOT EXISTS (
    SELECT 1
    FROM Employees AS e
    WHERE e.department_id = d.department_id
);
```

### `IN` versus `EXISTS`

-   `IN` checks whether a value belongs to a set of returned values.
-   `EXISTS` checks whether at least one matching row exists.
-   `EXISTS` is especially natural for correlated subqueries.
-   `EXISTS` and `IN` can express similar logic in some cases, but
    `NULL` handling and query shape matter.
-   Do not assume one is always faster; use execution plans and
    realistic data.

## 6. `ANY`, `SOME`, and `ALL`

These operators compare a value against values returned by a subquery.
Support varies by database. `SOME` is a synonym for `ANY` in systems
that support it.

### `ANY` / `SOME`

The comparison must be true for at least one returned value.

``` sql
SELECT employee_name, salary
FROM Employees
WHERE salary > ANY (
    SELECT salary
    FROM Employees
    WHERE department_id = 10
);
```

This means the salary is greater than at least one salary in department
10.

### `ALL`

The comparison must be true for every returned value.

``` sql
SELECT employee_name, salary
FROM Employees
WHERE salary > ALL (
    SELECT salary
    FROM Employees
    WHERE department_id = 10
);
```

This means the salary is greater than every salary returned by the
subquery.

  Operator         Meaning
  ---------------- -------------------------------------------
  `IN`             Matches at least one value in a set
  `EXISTS`         Subquery returns at least one row
  `ANY` / `SOME`   Comparison is true for at least one value
  `ALL`            Comparison is true for every value
  `NOT EXISTS`     Subquery returns no rows

`NULL` values and empty result sets affect SQL logic, so be careful when
using `NOT IN`, `ANY`, and `ALL`.

## 7. Correlated versus non-correlated subqueries

### 7.1 Non-correlated subquery

A non-correlated subquery does not reference a column from the outer
query.

``` sql
SELECT employee_name, salary
FROM Employees
WHERE salary > (
    SELECT AVG(salary)
    FROM Employees
);
```

The inner query calculates the company-wide average independently of the
current employee row.

### 7.2 Correlated subquery

A correlated subquery references a value from the outer query.

**Example: employees earning above their own department's average**

``` sql
SELECT e.employee_id, e.employee_name, e.department_id, e.salary
FROM Employees AS e
WHERE e.salary > (
    SELECT AVG(e2.salary)
    FROM Employees AS e2
    WHERE e2.department_id = e.department_id
);
```

How to understand it:

1.  Consider an employee from the outer query.
2.  Use that employee's department ID in the inner query.
3.  Calculate the average salary for that department.
4.  Compare the employee's salary with the department average.
5.  Return the employee if their salary is higher.

The correlation is this condition:

``` sql
WHERE e2.department_id = e.department_id
```

`e2.department_id` belongs to the inner query. `e.department_id` refers
to the outer query.

### 7.3 Correlated subquery with `EXISTS`

``` sql
SELECT e.employee_id, e.employee_name
FROM Employees AS e
WHERE EXISTS (
    SELECT 1
    FROM Departments AS d
    WHERE d.department_id = e.department_id
);
```

The subquery references `e.department_id` from the outer query.

**Does a correlated subquery always execute once per outer row?** That
is a useful mental model, but not a guarantee of the physical execution
plan. A database optimizer may transform the query.

## 8. Common subquery problem patterns

### 8.1 Employee(s) with the maximum salary

``` sql
SELECT employee_id, employee_name, salary
FROM Employees
WHERE salary = (
    SELECT MAX(salary)
    FROM Employees
);
```

Returns all employees tied for the maximum.

### 8.2 Second-highest distinct salary

``` sql
SELECT MAX(salary) AS second_highest_salary
FROM Employees
WHERE salary < (
    SELECT MAX(salary)
    FROM Employees
);
```

This finds the highest salary below the maximum, so duplicate top
salaries do not count as separate ranks. If there is only one distinct
salary, the result is `NULL`.

### 8.3 Salary greater than the company average

``` sql
SELECT employee_id, employee_name, salary
FROM Employees
WHERE salary > (
    SELECT AVG(salary)
    FROM Employees
);
```

### 8.4 Salary greater than department average

``` sql
SELECT e.employee_id, e.employee_name, e.salary
FROM Employees AS e
WHERE e.salary > (
    SELECT AVG(e2.salary)
    FROM Employees AS e2
    WHERE e2.department_id = e.department_id
);
```

### 8.5 Employees in the same department as Asha

``` sql
SELECT employee_id, employee_name, department_id
FROM Employees
WHERE department_id = (
    SELECT department_id
    FROM Employees
    WHERE employee_name = 'Asha'
);
```

Assumes `Asha` identifies exactly one employee. If multiple rows may
match, use `IN` or a different query design.

### 8.6 Salary greater than at least one salary in department 10

``` sql
SELECT employee_name, salary
FROM Employees
WHERE salary > ANY (
    SELECT salary
    FROM Employees
    WHERE department_id = 10
);
```

### 8.7 Salary greater than every salary in department 10

``` sql
SELECT employee_name, salary
FROM Employees
WHERE salary > ALL (
    SELECT salary
    FROM Employees
    WHERE department_id = 10
);
```

## 9. Subquery versus JOIN

A subquery and a join can sometimes solve the same problem, but neither
is universally better.

**Using a subquery:**

``` sql
SELECT e.employee_id, e.employee_name
FROM Employees AS e
WHERE e.department_id = (
    SELECT d.department_id
    FROM Departments AS d
    WHERE d.department_name = 'Engineering'
);
```

**Using a join:**

``` sql
SELECT e.employee_id, e.employee_name
FROM Employees AS e
JOIN Departments AS d
    ON d.department_id = e.department_id
WHERE d.department_name = 'Engineering';
```

Choose based on the logic and output you need:

-   Use a subquery when comparing with a calculated value, checking
    membership, or testing existence is natural.
-   Use a join when you need columns from multiple tables in the result.
-   Use `EXISTS` / `NOT EXISTS` when the key question is whether a
    matching row exists.
-   Compare execution plans for performance-sensitive queries.

**Duplicate behavior:** A join can multiply output rows when one row
matches several rows on the other side. `IN` and `EXISTS` are
membership/existence tests and do not multiply an outer row just because
several matches exist.

## 10. Common mistakes

### Mistake 1: Using `=` when the subquery can return multiple rows

Potentially incorrect:

``` sql
SELECT employee_name
FROM Employees
WHERE department_id = (
    SELECT department_id
    FROM Departments
    WHERE department_name IN ('Engineering', 'Sales')
);
```

Use `IN` because multiple department IDs may be returned:

``` sql
SELECT employee_name
FROM Employees
WHERE department_id IN (
    SELECT department_id
    FROM Departments
    WHERE department_name IN ('Engineering', 'Sales')
);
```

### Mistake 2: Forgetting the correlation condition

This compares every employee with the company-wide average, not their
own department's average:

``` sql
SELECT e.employee_name, e.salary
FROM Employees AS e
WHERE e.salary > (
    SELECT AVG(e2.salary)
    FROM Employees AS e2
);
```

Correct:

``` sql
SELECT e.employee_name, e.salary
FROM Employees AS e
WHERE e.salary > (
    SELECT AVG(e2.salary)
    FROM Employees AS e2
    WHERE e2.department_id = e.department_id
);
```

### Mistake 3: Ignoring `NULL` in `NOT IN`

If the subquery returns `NULL`, `NOT IN` can produce unexpected results.
Consider `NOT EXISTS`.

### Mistake 4: Assuming a scalar subquery returns one row

Ensure it returns at most one row, or use a set operator appropriate to
the problem.

### Mistake 5: Assuming aliases are available everywhere

A `SELECT`-list alias is not available in every clause or at every stage
of query processing. A derived table may help when a calculated result
must be filtered.

### Mistake 6: Assuming subqueries are always slower or faster

Performance depends on the optimizer, indexes, data distribution, and
query shape. Inspect the execution plan instead of relying on a
universal rule.

### Mistake 7: Comparing with `NULL` using `=`

Use `IS NULL` or `IS NOT NULL`; ordinary comparisons with `NULL`
generally evaluate to `UNKNOWN`.

## 11. Best practices

1.  Use clear aliases and qualify ambiguous columns.
2.  Choose the operator that matches the result shape: `=`, `IN`,
    `EXISTS`, `ANY`, or `ALL`.
3.  Check `NULL` behavior, especially for `NOT IN`.
4.  Keep nested queries indented and readable.
5.  Test edge cases: no rows, duplicate values, tied salaries, and
    nulls.
6.  Do not assume a specific physical execution order.
7.  For slow queries, inspect the database's execution plan.
8.  Before an `UPDATE` or `DELETE`, run a `SELECT` with the same
    condition to check the affected rows.

## 12. Quick revision table

  -----------------------------------------------------------------------
  Concept                 Meaning                 Typical use
  ----------------------- ----------------------- -----------------------
  Scalar subquery         Returns one value       Compare salary with
                                                  average

  Multi-row subquery      Returns a set of values Use with `IN`, `ANY`,
                                                  `ALL`

  `WHERE` subquery        Filters rows            Employees in a selected
                                                  department

  `SELECT` subquery       Calculates output value Display company average
                                                  beside each employee

  Derived table           Subquery in `FROM`      Filter a grouped result

  `HAVING` subquery       Filters groups          Departments above
                                                  overall average

  Non-correlated          No reference to         Company-wide average
                          outer-query columns     

  Correlated              References outer-query  Department-specific
                          columns                 average

  `EXISTS`                At least one row exists Departments with
                                                  employees

  `NOT EXISTS`            No matching row exists  Departments without
                                                  employees

  `ANY` / `SOME`          True for at least one   Greater than at least
                          value                   one salary

  `ALL`                   True for every value    Greater than every
                                                  salary
  -----------------------------------------------------------------------

## 13. Practice questions

Use the `Employees` and `Departments` tables above.

1.  Find employees earning more than the company average.
2.  Find employees in Sales using a subquery.
3.  Find the employee or employees with the maximum salary.
4.  Find the second-highest distinct salary.
5.  Find employees earning more than their department average.
6.  Find departments with no employees.
7.  Find departments with at least one employee.
8.  Find employees earning more than at least one employee in department
    10.
9.  Find employees earning more than every employee in department 10.
10. Display every employee's salary alongside the overall average.
11. Find employees in the same department as Asha.
12. Explain why `NOT EXISTS` may be safer than `NOT IN`.

## 14. Practice solutions

### 1. Above company average

``` sql
SELECT employee_id, employee_name, salary
FROM Employees
WHERE salary > (SELECT AVG(salary) FROM Employees);
```

### 2. Employees in Sales

``` sql
SELECT employee_id, employee_name
FROM Employees
WHERE department_id = (
    SELECT department_id
    FROM Departments
    WHERE department_name = 'Sales'
);
```

### 3. Maximum salary

``` sql
SELECT employee_id, employee_name, salary
FROM Employees
WHERE salary = (SELECT MAX(salary) FROM Employees);
```

### 4. Second-highest distinct salary

``` sql
SELECT MAX(salary) AS second_highest_salary
FROM Employees
WHERE salary < (SELECT MAX(salary) FROM Employees);
```

### 5. Above department average

``` sql
SELECT e.employee_id, e.employee_name, e.salary
FROM Employees AS e
WHERE e.salary > (
    SELECT AVG(e2.salary)
    FROM Employees AS e2
    WHERE e2.department_id = e.department_id
);
```

### 6. Departments without employees

``` sql
SELECT d.department_id, d.department_name
FROM Departments AS d
WHERE NOT EXISTS (
    SELECT 1
    FROM Employees AS e
    WHERE e.department_id = d.department_id
);
```

### 7. Departments with employees

``` sql
SELECT d.department_id, d.department_name
FROM Departments AS d
WHERE EXISTS (
    SELECT 1
    FROM Employees AS e
    WHERE e.department_id = d.department_id
);
```

### 8. Greater than at least one salary in department 10

``` sql
SELECT employee_id, employee_name, salary
FROM Employees
WHERE salary > ANY (
    SELECT salary
    FROM Employees
    WHERE department_id = 10
);
```

### 9. Greater than every salary in department 10

``` sql
SELECT employee_id, employee_name, salary
FROM Employees
WHERE salary > ALL (
    SELECT salary
    FROM Employees
    WHERE department_id = 10
);
```

### 10. Show salary and company average

``` sql
SELECT
    employee_name,
    salary,
    (SELECT AVG(salary) FROM Employees) AS company_avg_salary
FROM Employees;
```

### 11. Same department as Asha

``` sql
SELECT employee_id, employee_name, department_id
FROM Employees
WHERE department_id = (
    SELECT department_id
    FROM Employees
    WHERE employee_name = 'Asha'
);
```

Assumes `Asha` identifies one employee.

### 12. Why can `NOT EXISTS` be safer?

If a `NOT IN` subquery returns `NULL`, the condition can evaluate to
`UNKNOWN`, so expected rows may not be returned. `NOT EXISTS` checks for
matching rows and avoids that specific `NULL` trap.

## 15. Final revision checklist

-   [ ] Define a subquery and explain why it is used.
-   [ ] Distinguish scalar and multiple-row subqueries.
-   [ ] Write subqueries in `WHERE`, `SELECT`, `FROM`, and `HAVING`.
-   [ ] Explain `IN` and the `NOT IN` / `NULL` issue.
-   [ ] Use `EXISTS` and `NOT EXISTS`.
-   [ ] Distinguish `ANY` / `SOME` from `ALL`.
-   [ ] Explain correlated versus non-correlated subqueries.
-   [ ] Find maximum and second-highest distinct salary.
-   [ ] Compare an employee's salary with their department average.
-   [ ] Decide when a join may be clearer than a subquery.

**Core idea:** A subquery is a query nested inside another SQL
statement. Its result helps the outer query filter rows, calculate
values, check membership, or test whether related rows exist.
