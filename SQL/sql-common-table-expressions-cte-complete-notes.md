# SQL Common Table Expressions (CTEs) — Complete Notes

A **Common Table Expression (CTE)** lets you give a query result a name and use that result in a query that follows it.

A CTE is especially useful when you want to:
- Break a complicated SQL query into clear steps.
- Calculate an intermediate result and use it in a later query.
- Make a query easier to read and maintain.
- Refer to an earlier CTE from a later CTE in the same statement.

> **Scope of this guide:** This document covers Common Table Expressions (CTEs) only. It does not cover window functions, subqueries as a separate topic, derived tables, or temporary tables.

---

## 1. The Basic Idea

Suppose you have an `employees` table:

| id | name | department | salary |
|---:|---|---|---:|
| 1 | Rahul | IT | 50000 |
| 2 | Aman | IT | 60000 |
| 3 | Priya | HR | 40000 |
| 4 | Neha | HR | 45000 |
| 5 | Karan | IT | 70000 |

You want to calculate the average salary for each department and then display those averages.

A CTE lets you define the first result above and use it in the query below.

```sql
WITH department_avg AS (
    SELECT
        department,
        AVG(salary) AS avg_salary
    FROM employees
    GROUP BY department
)
SELECT *
FROM department_avg;
```

### How to read this query

**Part 1 — Create a named query result**

```sql
WITH department_avg AS (
    SELECT
        department,
        AVG(salary) AS avg_salary
    FROM employees
    GROUP BY department
)
```

The query inside the parentheses calculates each department's average salary. The result is given the name `department_avg`.

**Part 2 — Use the CTE**

```sql
SELECT *
FROM department_avg;
```

The outer query reads the result named `department_avg`.

### Output

| department | avg_salary |
|---|---:|
| HR | 42500 |
| IT | 60000 |

The order of rows is not guaranteed unless you specify an `ORDER BY` in the final query.

**Important:** A normal CTE is not a permanent table. It is a named query result that can be referenced by the statement immediately following the `WITH` clause.

---

## 2. General Syntax

```sql
WITH cte_name AS (
    -- Query that produces the intermediate result
    SELECT ...
)
-- Query that uses the CTE
SELECT ...
FROM cte_name;
```

The parts mean:

- `WITH`: begins the CTE definition.
- `cte_name`: the name you give to the result.
- `AS (...)`: contains the query that produces the result.
- The final query: uses the named result.

You can choose a meaningful name, such as `department_avg`, `high_salary_employees`, or `department_summary`.

---

## 3. Example: Filter Employees Using a CTE

Find employees whose salary is greater than 55000.

```sql
WITH high_salary_employees AS (
    SELECT
        id,
        name,
        department,
        salary
    FROM employees
    WHERE salary > 55000
)
SELECT *
FROM high_salary_employees;
```

### What happens?

1. The CTE selects employees whose salary is greater than 55000.
2. It names that result `high_salary_employees`.
3. The outer query displays the rows from that result.

### Output

| id | name | department | salary |
|---:|---|---|---:|
| 2 | Aman | IT | 60000 |
| 5 | Karan | IT | 70000 |

The outer query can also sort the result:

```sql
WITH high_salary_employees AS (
    SELECT id, name, department, salary
    FROM employees
    WHERE salary > 55000
)
SELECT *
FROM high_salary_employees
ORDER BY salary DESC;
```

---

## 4. Example: Calculate Department Averages, Then Filter Them

Suppose you want to show only departments whose average salary is greater than 50000.

```sql
WITH department_avg AS (
    SELECT
        department,
        AVG(salary) AS avg_salary
    FROM employees
    GROUP BY department
)
SELECT
    department,
    avg_salary
FROM department_avg
WHERE avg_salary > 50000;
```

### Step 1: The CTE result

| department | avg_salary |
|---|---:|
| HR | 42500 |
| IT | 60000 |

### Step 2: The outer query filters the CTE result

The condition `WHERE avg_salary > 50000` keeps only IT.

### Final output

| department | avg_salary |
|---|---:|
| IT | 60000 |

This illustrates the main pattern:

```text
WITH cte_name AS (
    Calculate or select an intermediate result
)
SELECT ...
FROM cte_name
WHERE ...;
```

---

## 5. Example: Use a CTE and Join It to the Original Table

A CTE can be joined to another table, including the table from which the CTE was created.

Find employees whose salaries are above their department's average.

```sql
WITH department_avg AS (
    SELECT
        department,
        AVG(salary) AS avg_salary
    FROM employees
    GROUP BY department
)
SELECT
    e.name,
    e.department,
    e.salary,
    d.avg_salary
FROM employees AS e
JOIN department_avg AS d
    ON e.department = d.department
WHERE e.salary > d.avg_salary
ORDER BY e.department, e.salary DESC;
```

### Step 1: The CTE calculates averages

| department | avg_salary |
|---|---:|
| HR | 42500 |
| IT | 60000 |

### Step 2: The outer query joins the averages to employees

The join condition:

```sql
ON e.department = d.department
```

matches each employee to the average for their department.

The filter:

```sql
WHERE e.salary > d.avg_salary
```

keeps employees whose salary is greater than that average.

### Final output

| name | department | salary | avg_salary |
|---|---|---:|---:|
| Neha | HR | 45000 | 42500 |
| Karan | IT | 70000 | 60000 |

---

## 6. Multiple CTEs in One Query

You can define more than one CTE in the same `WITH` clause. Separate CTE definitions with commas. A later CTE can generally use a CTE defined earlier in the same clause.

```sql
WITH department_avg AS (
    SELECT
        department,
        AVG(salary) AS avg_salary
    FROM employees
    GROUP BY department
),
above_average AS (
    SELECT
        e.name,
        e.department,
        e.salary,
        d.avg_salary
    FROM employees AS e
    JOIN department_avg AS d
        ON e.department = d.department
    WHERE e.salary > d.avg_salary
)
SELECT *
FROM above_average
ORDER BY department;
```

### Understanding the stages

**Stage 1: `department_avg`**

Calculates one average salary per department.

**Stage 2: `above_average`**

Uses `department_avg` to find employees whose salaries exceed their department's average.

**Stage 3: Final `SELECT`**

Displays the result stored in the named CTE `above_average`.

### Key syntax detail

Use a comma between CTE definitions:

```sql
WITH first_cte AS (
    SELECT ...
),
second_cte AS (
    SELECT ...
)
SELECT ...
FROM second_cte;
```

Do not put a semicolon between the CTE definitions and the final query. The statement ends after the final query.

---

## 7. Example: CTE with `COUNT()` and `GROUP BY`

Suppose you want to count the employees in each department and then display only departments with at least two employees.

```sql
WITH department_counts AS (
    SELECT
        department,
        COUNT(*) AS employee_count
    FROM employees
    GROUP BY department
)
SELECT
    department,
    employee_count
FROM department_counts
WHERE employee_count >= 2;
```

### CTE result

| department | employee_count |
|---|---:|
| HR | 2 |
| IT | 3 |

### Final output

Both departments meet the condition, so both are returned.

This example shows that a CTE can contain aggregate calculations such as `COUNT()`, `SUM()`, and `AVG()`, and the outer query can filter the resulting columns.

---

## 8. CTE Names and Column Names

Choose names that describe the result clearly.

Good examples:

```sql
WITH department_avg AS (...)
WITH department_counts AS (...)
WITH high_salary_employees AS (...)
```

You can also specify column names directly after the CTE name in database systems that support this standard form:

```sql
WITH department_summary (department, avg_salary) AS (
    SELECT
        department,
        AVG(salary)
    FROM employees
    GROUP BY department
)
SELECT *
FROM department_summary;
```

Here, the CTE output columns are named `department` and `avg_salary`.

In most examples, using aliases inside the `SELECT` statement is simpler and more readable.

---

## 9. CTE Rules to Remember

1. A CTE begins with `WITH`.
2. The CTE name is followed by `AS (...)`.
3. The parentheses contain a `SELECT` query that defines the result.
4. The CTE must be followed by a statement that uses it.
5. A normal CTE is available only to the statement immediately following its definition.
6. Multiple CTEs in one `WITH` clause are separated by commas.
7. A later CTE can generally reference an earlier CTE in the same clause.
8. The CTE does not create a permanent database table.
9. Use `ORDER BY` in the final query when the output order matters.
10. A CTE is a way to structure a query; it is not guaranteed to be stored as a separate physical table by the database.

---

## 10. Common Mistakes

### Mistake 1: Defining a CTE but not querying it

Incomplete:

```sql
WITH department_avg AS (
    SELECT department, AVG(salary) AS avg_salary
    FROM employees
    GROUP BY department
);
```

A normal CTE definition must be followed by the query that uses it.

Correct:

```sql
WITH department_avg AS (
    SELECT department, AVG(salary) AS avg_salary
    FROM employees
    GROUP BY department
)
SELECT *
FROM department_avg;
```

### Mistake 2: Forgetting a comma between CTEs

Incorrect:

```sql
WITH first_cte AS (
    SELECT ...
)
second_cte AS (
    SELECT ...
)
SELECT ...
FROM second_cte;
```

Correct:

```sql
WITH first_cte AS (
    SELECT ...
),
second_cte AS (
    SELECT ...
)
SELECT ...
FROM second_cte;
```

### Mistake 3: Using the wrong CTE name

If the CTE is named `department_avg`, reference that exact name in the outer query:

```sql
WITH department_avg AS (
    SELECT department, AVG(salary) AS avg_salary
    FROM employees
    GROUP BY department
)
SELECT *
FROM department_avg;
```

### Mistake 4: Expecting a CTE to remain available to the next SQL statement

A normal CTE is scoped to the single statement that follows it. If you need data to be reused across several separate statements, a temporary table or another persistent storage approach may be more appropriate.

### Mistake 5: Assuming a CTE is always physically materialized

A CTE is a logical named query result. Depending on the database system and query, the optimizer may inline it or materialize it. Do not assume it is always stored as a separate temporary table.

---

## 11. Practice Questions

Use the `employees` table from Section 1.

### Question 1: Show all department averages

Write a CTE named `department_avg` that calculates average salary per department, then display the result.

<details>
<summary>Show solution</summary>

```sql
WITH department_avg AS (
    SELECT
        department,
        AVG(salary) AS avg_salary
    FROM employees
    GROUP BY department
)
SELECT *
FROM department_avg;
```

</details>

### Question 2: Find employees earning more than 55000

Create a CTE named `high_salary_employees` and select its rows.

<details>
<summary>Show solution</summary>

```sql
WITH high_salary_employees AS (
    SELECT id, name, department, salary
    FROM employees
    WHERE salary > 55000
)
SELECT *
FROM high_salary_employees;
```

</details>

### Question 3: Show departments with average salary above 50000

<details>
<summary>Show solution</summary>

```sql
WITH department_avg AS (
    SELECT department, AVG(salary) AS avg_salary
    FROM employees
    GROUP BY department
)
SELECT department, avg_salary
FROM department_avg
WHERE avg_salary > 50000;
```

</details>

### Question 4: Find employees earning above their department's average

<details>
<summary>Show solution</summary>

```sql
WITH department_avg AS (
    SELECT department, AVG(salary) AS avg_salary
    FROM employees
    GROUP BY department
)
SELECT
    e.name,
    e.department,
    e.salary,
    d.avg_salary
FROM employees AS e
JOIN department_avg AS d
    ON e.department = d.department
WHERE e.salary > d.avg_salary;
```

</details>

### Question 5: Use two CTEs

Create one CTE for department averages and a second CTE for employees above their department's average. Display the second CTE.

<details>
<summary>Show solution</summary>

```sql
WITH department_avg AS (
    SELECT department, AVG(salary) AS avg_salary
    FROM employees
    GROUP BY department
),
above_average AS (
    SELECT
        e.name,
        e.department,
        e.salary,
        d.avg_salary
    FROM employees AS e
    JOIN department_avg AS d
        ON e.department = d.department
    WHERE e.salary > d.avg_salary
)
SELECT *
FROM above_average;
```

</details>

---

## 12. Quick Revision

| Term | Meaning |
|---|---|
| CTE | A named query result defined with `WITH` |
| `WITH` | Starts the CTE definition |
| `AS (...)` | Contains the query that produces the result |
| CTE name | The name used by the outer query |
| Outer query | The query that reads and processes the CTE result |
| Multiple CTEs | Several named results separated by commas |
| CTE scope | Normally limited to the single statement that follows the `WITH` clause |

### The pattern to remember

```sql
WITH intermediate_result AS (
    -- Step 1: produce a result
    SELECT ...
)
-- Step 2: use that result
SELECT ...
FROM intermediate_result
WHERE ...;
```

**In one sentence:** A CTE lets you define a named query result first, then use it in the main query to make SQL easier to read and organize.
