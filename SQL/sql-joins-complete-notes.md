# SQL JOINs — Complete Notes with Examples

A comprehensive guide to SQL joins: why joins are needed, how each join works, how to write join conditions, how `NULL` values behave, how to avoid duplicate-row mistakes, and how to practice common interview and real-world questions.

> **Database note:** Most examples use standard SQL syntax supported by common relational databases. Some syntax and features differ by database. In particular, `FULL OUTER JOIN` is not supported directly by every database (for example, MySQL does not support it natively).

---

## Contents

1. [What Is a JOIN?](#1-what-is-a-join)
2. [Sample Tables Used in This Guide](#2-sample-tables-used-in-this-guide)
3. [Basic JOIN Syntax](#3-basic-join-syntax)
4. [INNER JOIN](#4-inner-join)
5. [LEFT JOIN--left-outer-join](#5-left-join--left-outer-join)
6. [RIGHT JOIN--right-outer-join](#6-right-join--right-outer-join)
7. [FULL OUTER JOIN](#7-full-outer-join)
8. [CROSS JOIN](#8-cross-join)
9. [SELF JOIN](#9-self-join)
10. [Joining More Than Two Tables](#10-joining-more-than-two-tables)
11. [JOIN Conditions: ON vs WHERE](#11-join-conditions-on-vs-where)
12. [NULL Values and Unmatched Rows](#12-null-values-and-unmatched-rows)
13. [Finding Rows With No Match](#13-finding-rows-with-no-match)
14. [One-to-One, One-to-Many, and Many-to-Many](#14-one-to-one-one-to-many-and-many-to-many)
15. [Duplicate Rows and Join Multiplication](#15-duplicate-rows-and-join-multiplication)
16. [JOINs and Aggregation](#16-joins-and-aggregation)
17. [USING, Aliases, and Qualified Column Names](#17-using-aliases-and-qualified-column-names)
18. [Common JOIN Mistakes](#18-common-join-mistakes)
19. [JOIN Types Compared](#19-join-types-compared)
20. [Practice Questions With Solutions](#20-practice-questions-with-solutions)
21. [Quick Revision](#21-quick-revision)

---

## 1. What Is a JOIN?

A **JOIN** combines columns from two or more tables by matching rows according to a related column or condition.

Relational databases often store information in separate tables to reduce repetition and keep data organized. A join lets you bring related information together when querying it.

For example:

- An `employees` table stores employee details.
- A `departments` table stores department names.
- The employee row contains `department_id`, which identifies the employee's department.

A join can combine the employee's name with the department name.

### Why are JOINs useful?

- To retrieve related information stored in separate tables.
- To report across several tables.
- To identify records that have no matching record.
- To calculate totals, averages, and counts across related data.
- To connect entities such as customers and orders, students and courses, or employees and departments.

**Core idea:** A join uses a matching condition to decide which rows from the tables belong together. The type of join determines what happens to rows that do not match.

---

## 2. Sample Tables Used in This Guide

We'll use these sample tables throughout the guide.

### `employees`

| employee_id | employee_name | department_id | manager_id | salary |
|---:|---|---:|---:|---:|
| 1 | Asha | 10 | NULL | 80000 |
| 2 | Ben | 20 | 1 | 60000 |
| 3 | Cara | 10 | 1 | 65000 |
| 4 | Deepak | 30 | 2 | 55000 |
| 5 | Eva | NULL | 2 | 50000 |
| 6 | Farhan | 40 | NULL | 45000 |

Notes:
- Asha and Farhan do not have a manager (`manager_id` is `NULL`).
- Eva has no assigned department (`department_id` is `NULL`).
- Department IDs 10, 20, 30, and 40 appear in employee rows.

### `departments`

| department_id | department_name |
|---:|---|
| 10 | Engineering |
| 20 | Analytics |
| 30 | HR |
| 50 | Finance |

Notes:
- Department 40 is not present in `departments`.
- Finance (department 50) has no employee in the sample data.
- Eva's `department_id` is `NULL`, so it does not match a department ID using ordinary equality.

### `customers`

| customer_id | customer_name |
|---:|---|
| 1 | Isha |
| 2 | Jay |
| 3 | Kim |
| 4 | Luis |

### `orders`

| order_id | customer_id | order_amount |
|---:|---:|---:|
| 101 | 1 | 250 |
| 102 | 1 | 100 |
| 103 | 2 | 400 |
| 104 | 5 | 150 |

Notes:
- Isha has two orders.
- Kim and Luis have no orders.
- Order 104 refers to customer ID 5, which is absent from `customers` in this sample. This can happen in messy data or when referential integrity is not enforced.

---

## 3. Basic JOIN Syntax

```sql
SELECT
    table_a.column_name,
    table_b.column_name
FROM table_a
JOIN table_b
    ON table_a.key_column = table_b.key_column;
```

Example:

```sql
SELECT
    e.employee_name,
    d.department_name
FROM employees AS e
INNER JOIN departments AS d
    ON e.department_id = d.department_id;
```

### Understand each part

- `SELECT`: chooses the columns to display.
- `FROM employees AS e`: uses `employees` and gives it the alias `e`.
- `INNER JOIN departments AS d`: joins the departments table, using alias `d`.
- `ON e.department_id = d.department_id`: defines which employee and department rows match.

`JOIN` without a specified type usually means `INNER JOIN`.

### Why use aliases?

Aliases make queries shorter and help distinguish columns with the same name:

```sql
e.department_id
d.department_id
```

Both tables have a `department_id` column, so qualifying the column avoids ambiguity.

---

## 4. INNER JOIN

An **INNER JOIN** returns only rows where the join condition matches in both tables.

### Visual idea

```text
Table A:  [matched | A-only]
Table B:  [matched | B-only]

INNER JOIN returns: [matched rows]
```

### Example: Employees with a known matching department

```sql
SELECT
    e.employee_id,
    e.employee_name,
    d.department_name
FROM employees AS e
INNER JOIN departments AS d
    ON e.department_id = d.department_id
ORDER BY e.employee_id;
```

### Result

| employee_id | employee_name | department_name |
|---:|---|---|
| 1 | Asha | Engineering |
| 2 | Ben | Analytics |
| 3 | Cara | Engineering |
| 4 | Deepak | HR |

Why are Eva and Farhan missing?

- Eva has a `NULL` department ID, so it does not equal any department ID in the ordinary join condition.
- Farhan has department ID 40, but department 40 does not exist in the `departments` table.

Finance is also absent because an inner join does not return a department row without a matching employee.

### When to use INNER JOIN

Use it when you only want records that have a match in both tables—for example, orders that belong to known customers or employees with valid department records.

---

## 5. LEFT JOIN / LEFT OUTER JOIN

A **LEFT JOIN** returns:
1. Every row from the left table.
2. Matching rows from the right table.
3. `NULL` values for right-table columns when a left-table row has no match.

`LEFT JOIN` and `LEFT OUTER JOIN` mean the same thing.

### Example: All employees, including those without a matching department

```sql
SELECT
    e.employee_id,
    e.employee_name,
    e.department_id,
    d.department_name
FROM employees AS e
LEFT JOIN departments AS d
    ON e.department_id = d.department_id
ORDER BY e.employee_id;
```

### Result

| employee_id | employee_name | department_id | department_name |
|---:|---|---:|---|
| 1 | Asha | 10 | Engineering |
| 2 | Ben | 20 | Analytics |
| 3 | Cara | 10 | Engineering |
| 4 | Deepak | 30 | HR |
| 5 | Eva | NULL | NULL |
| 6 | Farhan | 40 | NULL |

Eva and Farhan remain in the result because all left-table rows are preserved.

### Example: All customers, including customers with no orders

```sql
SELECT
    c.customer_id,
    c.customer_name,
    o.order_id,
    o.order_amount
FROM customers AS c
LEFT JOIN orders AS o
    ON c.customer_id = o.customer_id
ORDER BY c.customer_id, o.order_id;
```

Result:

| customer_id | customer_name | order_id | order_amount |
|---:|---|---:|---:|
| 1 | Isha | 101 | 250 |
| 1 | Isha | 102 | 100 |
| 2 | Jay | 103 | 400 |
| 3 | Kim | NULL | NULL |
| 4 | Luis | NULL | NULL |

Isha appears twice because she has two orders. Kim and Luis appear once each with `NULL` order columns.

### When to use LEFT JOIN

Use it when every row from the first (left) table must remain in the output, even if the second table has no match.

Common examples:
- All customers and any orders they placed.
- All employees and their department details, if available.
- All products and their sales, including products never sold.

---

## 6. RIGHT JOIN / RIGHT OUTER JOIN

A **RIGHT JOIN** returns:
1. Every row from the right table.
2. Matching rows from the left table.
3. `NULL` values for left-table columns when there is no match.

`RIGHT JOIN` and `RIGHT OUTER JOIN` mean the same thing.

### Example: All departments, including departments with no employees

```sql
SELECT
    e.employee_id,
    e.employee_name,
    d.department_id,
    d.department_name
FROM employees AS e
RIGHT JOIN departments AS d
    ON e.department_id = d.department_id
ORDER BY d.department_id, e.employee_id;
```

### Result

| employee_id | employee_name | department_id | department_name |
|---:|---|---:|---|
| 1 | Asha | 10 | Engineering |
| 3 | Cara | 10 | Engineering |
| 2 | Ben | 20 | Analytics |
| 4 | Deepak | 30 | HR |
| NULL | NULL | 50 | Finance |

Finance remains because the right table (`departments`) is preserved, even though it has no matching employee.

### Equivalent LEFT JOIN

Many developers prefer rewriting a right join as a left join by reversing the table order:

```sql
SELECT
    e.employee_id,
    e.employee_name,
    d.department_id,
    d.department_name
FROM departments AS d
LEFT JOIN employees AS e
    ON e.department_id = d.department_id
ORDER BY d.department_id, e.employee_id;
```

These queries express the same matching logic. A left join is often easier to read because the preserved table appears first.

---

## 7. FULL OUTER JOIN

A **FULL OUTER JOIN** returns:
- Rows that match in both tables.
- Rows that exist only in the left table.
- Rows that exist only in the right table.

Unmatched columns on the other side are filled with `NULL`.

### Example: Show all employees and all departments

```sql
SELECT
    e.employee_id,
    e.employee_name,
    e.department_id AS employee_department_id,
    d.department_id AS matched_department_id,
    d.department_name
FROM employees AS e
FULL OUTER JOIN departments AS d
    ON e.department_id = d.department_id
ORDER BY employee_department_id, matched_department_id;
```

### Conceptual result

| employee_id | employee_name | employee_department_id | matched_department_id | department_name |
|---:|---|---:|---:|---|
| 1 | Asha | 10 | 10 | Engineering |
| 3 | Cara | 10 | 10 | Engineering |
| 2 | Ben | 20 | 20 | Analytics |
| 4 | Deepak | 30 | 30 | HR |
| 5 | Eva | NULL | NULL | NULL |
| 6 | Farhan | 40 | NULL | NULL |
| NULL | NULL | NULL | 50 | Finance |

This preserves employees without matching departments and departments without matching employees.

### Database compatibility

`FULL OUTER JOIN` is supported by PostgreSQL and SQL Server, among other systems, but **MySQL does not support it directly**. If you use a database without native full outer join support, the result can often be emulated with a `LEFT JOIN`, a `RIGHT JOIN` (or reversed `LEFT JOIN`), and `UNION`/`UNION ALL` with care to avoid duplicate matched rows.

---

## 8. CROSS JOIN

A **CROSS JOIN** returns the Cartesian product: every row from the first table combined with every row from the second table.

If table A has 3 rows and table B has 4 rows, the result has `3 × 4 = 12` rows.

### Example

```sql
SELECT
    c.customer_name,
    p.product_name
FROM customers AS c
CROSS JOIN products AS p;
```

Assume `products` contains:

| product_id | product_name |
|---:|---|
| 1 | Laptop |
| 2 | Phone |
| 3 | Tablet |

The result pairs every customer with every product. With four customers and three products, there are 12 rows.

### When to use CROSS JOIN

- Generating every combination of two small sets.
- Building a calendar of dates crossed with categories.
- Creating all possible product-size combinations.

**Warning:** A cross join can create a very large result. Check the row counts before running it on large tables.

---

## 9. SELF JOIN

A **self join** joins a table to itself. It is useful when rows in the same table are related to each other, such as employees and their managers.

The table must be given different aliases so SQL can distinguish the two roles.

### Example: Employee and manager names

In `employees`, `manager_id` refers to another employee's `employee_id`.

```sql
SELECT
    e.employee_name AS employee,
    m.employee_name AS manager
FROM employees AS e
LEFT JOIN employees AS m
    ON e.manager_id = m.employee_id
ORDER BY e.employee_id;
```

### Result

| employee | manager |
|---|---|
| Asha | NULL |
| Ben | Asha |
| Cara | Asha |
| Deepak | Ben |
| Eva | Ben |
| Farhan | NULL |

Why use `LEFT JOIN`? It keeps employees who do not have a manager. If you used `INNER JOIN`, Asha and Farhan would be excluded.

### Other uses for self joins

- Comparing one row to another row in the same table.
- Finding pairs of employees in the same department.
- Representing hierarchical relationships.
- Finding products with similar attributes, if the table contains those attributes.

---

## 10. Joining More Than Two Tables

A query can join three or more tables by adding join clauses.

Suppose we have:

- `orders(order_id, customer_id, order_amount)`
- `customers(customer_id, customer_name)`
- `order_items(order_id, product_id, quantity)`
- `products(product_id, product_name, price)`

### Example: Order details with customer and product names

```sql
SELECT
    o.order_id,
    c.customer_name,
    p.product_name,
    oi.quantity,
    p.price,
    oi.quantity * p.price AS line_total
FROM orders AS o
INNER JOIN customers AS c
    ON o.customer_id = c.customer_id
INNER JOIN order_items AS oi
    ON o.order_id = oi.order_id
INNER JOIN products AS p
    ON oi.product_id = p.product_id
ORDER BY o.order_id, p.product_name;
```

Each join adds related information:
1. Match orders to customers.
2. Match orders to their items.
3. Match each item to its product.

Use the correct key for every relationship. Joining a table on the wrong column can produce incorrect results or many more rows than expected.

---

## 11. JOIN Conditions: `ON` vs `WHERE`

`ON` defines how rows match. `WHERE` filters the rows produced by the `FROM` and join operations.

### INNER JOIN example

These queries are usually equivalent for this inner-join condition:

```sql
SELECT e.employee_name, d.department_name
FROM employees AS e
INNER JOIN departments AS d
    ON e.department_id = d.department_id;
```

```sql
SELECT e.employee_name, d.department_name
FROM employees AS e
JOIN departments AS d
    ON e.department_id = d.department_id
WHERE e.department_id = d.department_id;
```

The second form is less clear because it puts the matching condition in `WHERE` rather than `ON`. Prefer `ON` for join relationships.

### Important difference with LEFT JOIN

Suppose you want all employees and department details, but only department 10 should match.

**Version A: Filter in `ON`**

```sql
SELECT
    e.employee_name,
    e.department_id,
    d.department_name
FROM employees AS e
LEFT JOIN departments AS d
    ON e.department_id = d.department_id
   AND d.department_id = 10
ORDER BY e.employee_id;
```

All employees remain. Only department 10 can match; other employees get `NULL` for the department columns.

**Version B: Filter in `WHERE`**

```sql
SELECT
    e.employee_name,
    e.department_id,
    d.department_name
FROM employees AS e
LEFT JOIN departments AS d
    ON e.department_id = d.department_id
WHERE d.department_id = 10
ORDER BY e.employee_id;
```

This keeps only rows where the matched department is 10. Rows with no matching department have `NULL` in `d.department_id` and fail the `WHERE` condition. This makes the result behave like an inner filter for that condition.

**Rule of thumb:**
- Use `ON` to define matching and, when appropriate, restrictions on which right-side rows can match.
- Use `WHERE` to filter the final joined result.
- Be especially careful placing right-table conditions in `WHERE` after a `LEFT JOIN`, because it can remove unmatched left rows.

---

## 12. NULL Values and Unmatched Rows

In ordinary SQL equality comparisons, `NULL = NULL` is not true; the result is unknown. So this join condition does not match two `NULL` values:

```sql
ON a.some_id = b.some_id
```

A `NULL` in a join key normally will not match another `NULL` using `=`.

For outer joins, unmatched columns on the non-preserved side are returned as `NULL`.

### Do not confuse two cases

1. **A stored `NULL`:** The source row itself contains a missing/unknown value.
2. **A join-generated `NULL`:** The row from the other table did not match, so SQL fills its columns with `NULL`.

A query result may contain either case. If you need to tell whether a match exists, test a right-side column that is guaranteed to be non-NULL for real rows, often the right table's primary key:

```sql
WHERE d.department_id IS NULL
```

This is a common way to find employees with no matching department after a left join.

---

## 13. Finding Rows With No Match

A very common task is finding records in one table that have no related record in another table. This is often called an **anti-join** pattern.

### Example: Customers who have never placed an order

```sql
SELECT
    c.customer_id,
    c.customer_name
FROM customers AS c
LEFT JOIN orders AS o
    ON c.customer_id = o.customer_id
WHERE o.order_id IS NULL;
```

Result:

| customer_id | customer_name |
|---:|---|
| 3 | Kim |
| 4 | Luis |

The left join keeps every customer. Customers with no order have `NULL` in `o.order_id`; the `WHERE` clause keeps those unmatched rows.

### Alternative: `NOT EXISTS`

```sql
SELECT
    c.customer_id,
    c.customer_name
FROM customers AS c
WHERE NOT EXISTS (
    SELECT 1
    FROM orders AS o
    WHERE o.customer_id = c.customer_id
);
```

This also finds customers without orders. `NOT EXISTS` is not a join syntax, but it is a common alternative for this type of task.

### Example: Employees with no matching department

```sql
SELECT
    e.employee_id,
    e.employee_name,
    e.department_id
FROM employees AS e
LEFT JOIN departments AS d
    ON e.department_id = d.department_id
WHERE d.department_id IS NULL;
```

This returns Eva and Farhan in our sample data: Eva has no department ID, and Farhan's department ID has no matching department row.

---

## 14. One-to-One, One-to-Many, and Many-to-Many

Understanding relationship cardinality helps predict how many rows a join will return.

### One-to-one

Each row in table A matches at most one row in table B, and each row in B matches at most one row in A.

Example: `users` and `user_profiles`, if each user has one profile and each profile belongs to one user.

### One-to-many

One row in table A can match multiple rows in table B.

Example: one customer can have many orders.

```sql
SELECT c.customer_name, o.order_id
FROM customers AS c
LEFT JOIN orders AS o
    ON c.customer_id = o.customer_id;
```

Isha appears twice because she has two orders.

### Many-to-many

Rows in table A can relate to many rows in table B, and vice versa. This is usually represented with a junction/bridge table.

Example:
- `students(student_id, student_name)`
- `courses(course_id, course_name)`
- `enrollments(student_id, course_id)`

A student can enroll in many courses, and a course can have many students.

```sql
SELECT
    s.student_name,
    c.course_name
FROM students AS s
JOIN enrollments AS en
    ON s.student_id = en.student_id
JOIN courses AS c
    ON en.course_id = c.course_id;
```

The `enrollments` table connects students and courses.

---

## 15. Duplicate Rows and Join Multiplication

A join does not automatically return one row per left-table row. If a row matches several rows on the other side, it appears several times.

Example: Isha has two orders.

| customer_id | customer_name | order_id |
|---:|---|---:|
| 1 | Isha | 101 |
| 1 | Isha | 102 |

This is correct behavior, not necessarily a duplicate-data error.

### Why can row counts grow?

If one customer matches 5 orders, the customer row appears 5 times in a customer-to-orders join.

If a join key is not unique in either table, multiple rows can match on both sides. For example, 2 rows on one side and 3 rows on the other with the same key can produce 6 matching combinations.

### How to avoid incorrect results

- Know which columns are unique keys.
- Understand the relationship between the tables.
- Join using the correct key columns.
- Check row counts before and after joins.
- Aggregate at the correct level.
- Do not use `DISTINCT` simply to hide unexpected row multiplication; first understand why it happened.

---

## 16. JOINs and Aggregation

You can use aggregate functions such as `COUNT`, `SUM`, and `AVG` after a join.

### Example: Number of orders per customer, including customers with zero orders

```sql
SELECT
    c.customer_id,
    c.customer_name,
    COUNT(o.order_id) AS order_count
FROM customers AS c
LEFT JOIN orders AS o
    ON c.customer_id = o.customer_id
GROUP BY
    c.customer_id,
    c.customer_name
ORDER BY c.customer_id;
```

### Result

| customer_id | customer_name | order_count |
|---:|---|---:|
| 1 | Isha | 2 |
| 2 | Jay | 1 |
| 3 | Kim | 0 |
| 4 | Luis | 0 |

**Why use `COUNT(o.order_id)` rather than `COUNT(*)`?**

For a customer with no orders, the left join still produces one row, with `NULL` in the order columns.

- `COUNT(*)` counts that output row and would give 1 for a customer with no orders.
- `COUNT(o.order_id)` counts only non-NULL order IDs and correctly gives 0.

### Example: Total order amount per customer

```sql
SELECT
    c.customer_id,
    c.customer_name,
    COALESCE(SUM(o.order_amount), 0) AS total_order_amount
FROM customers AS c
LEFT JOIN orders AS o
    ON c.customer_id = o.customer_id
GROUP BY
    c.customer_id,
    c.customer_name
ORDER BY c.customer_id;
```

`COALESCE(..., 0)` replaces a `NULL` total with zero. Whether zero is the right business meaning depends on the application.

**Aggregation warning:** If you join several one-to-many tables together, a row from one child table can be repeated for each matching row from another child table. This can inflate sums. Aggregate child tables separately or carefully design the query if totals appear too large.

---

## 17. `USING`, Aliases, and Qualified Column Names

### Qualified column names

When two tables share a column name, qualify it with the table name or alias:

```sql
SELECT
    e.department_id,
    d.department_name
FROM employees AS e
JOIN departments AS d
    ON e.department_id = d.department_id;
```

### Table aliases

```sql
FROM employees AS e
JOIN departments AS d
```

Here, `e` refers to `employees` and `d` refers to `departments`. The `AS` keyword is optional for table aliases in many databases, but using it can improve readability.

### `USING`

Some databases support a shorter form when both tables have the same join-column name:

```sql
SELECT
    employee_name,
    department_name
FROM employees
JOIN departments
USING (department_id);
```

`USING (department_id)` is a shorthand for matching the identically named column in both tables. It is not supported in every database and does not replace `ON` for arbitrary join expressions. If portability matters, use `ON`.

---

## 18. Common JOIN Mistakes

### Mistake 1: Forgetting the join condition

Dangerous:

```sql
SELECT *
FROM employees
JOIN departments;
```

Depending on the database, this may be rejected or produce a Cartesian-style result. If you intend to match departments, write the condition explicitly:

```sql
SELECT *
FROM employees AS e
JOIN departments AS d
    ON e.department_id = d.department_id;
```

### Mistake 2: Joining on the wrong columns

Incorrect relationships can create unrelated combinations or unexpected row counts. Identify the primary key and foreign key (or other intended relationship) before writing the join.

### Mistake 3: Turning a LEFT JOIN into an effective INNER JOIN

This query removes employees without a department match:

```sql
SELECT e.employee_name, d.department_name
FROM employees AS e
LEFT JOIN departments AS d
    ON e.department_id = d.department_id
WHERE d.department_name = 'Engineering';
```

That may be intentional. But if your goal is to preserve all employees while only allowing Engineering to match, put the restriction in the `ON` clause instead:

```sql
SELECT e.employee_name, d.department_name
FROM employees AS e
LEFT JOIN departments AS d
    ON e.department_id = d.department_id
   AND d.department_name = 'Engineering';
```

### Mistake 4: Using `COUNT(*)` when counting matching rows

After a left join, an unmatched left row still appears once. Use `COUNT(right_table.primary_key)` to count actual matches.

### Mistake 5: Assuming joins remove duplicates

Joins preserve the combinations that satisfy the condition. Multiple matching rows lead to multiple result rows.

### Mistake 6: Using `DISTINCT` as a quick fix

`DISTINCT` removes identical output rows, but it may hide a faulty join condition or an incorrect assumption about table relationships.

### Mistake 7: Forgetting NULL behavior

Ordinary equality does not match `NULL` to `NULL`. Use explicit null checks or database-appropriate null-safe comparison when that is truly the intended rule.

---

## 19. JOIN Types Compared

| JOIN type | What it returns | What happens to unmatched rows? |
|---|---|---|
| `INNER JOIN` | Only matching row combinations | Excluded from the result |
| `LEFT JOIN` | All left rows plus matches from right | Left rows remain; right columns become `NULL` |
| `RIGHT JOIN` | All right rows plus matches from left | Right rows remain; left columns become `NULL` |
| `FULL OUTER JOIN` | All matches and all unmatched rows from both sides | Preserved, with missing-side columns set to `NULL` |
| `CROSS JOIN` | Every combination of left and right rows | No matching condition is used |
| `SELF JOIN` | A table joined to itself | Behavior depends on the chosen join type |

`SELF JOIN` is a pattern, not a separate relational join operator: it can use `INNER JOIN`, `LEFT JOIN`, or another join type.

### A simple memory trick

- **INNER:** only matching rows.
- **LEFT:** preserve everything from the left table.
- **RIGHT:** preserve everything from the right table.
- **FULL:** preserve everything from both tables.
- **CROSS:** every possible combination.
- **SELF:** join a table to itself.

---

## 20. Practice Questions With Solutions

Use the sample tables in Section 2.

### Question 1: Show employee names with department names

**Solution:**

```sql
SELECT
    e.employee_name,
    d.department_name
FROM employees AS e
INNER JOIN departments AS d
    ON e.department_id = d.department_id;
```

### Question 2: Show all employees, including those without a department match

**Solution:**

```sql
SELECT
    e.employee_name,
    d.department_name
FROM employees AS e
LEFT JOIN departments AS d
    ON e.department_id = d.department_id;
```

### Question 3: Show all departments, including those with no employees

**Solution using LEFT JOIN:**

```sql
SELECT
    d.department_name,
    e.employee_name
FROM departments AS d
LEFT JOIN employees AS e
    ON d.department_id = e.department_id;
```

### Question 4: Find customers who have never placed an order

**Solution:**

```sql
SELECT
    c.customer_id,
    c.customer_name
FROM customers AS c
LEFT JOIN orders AS o
    ON c.customer_id = o.customer_id
WHERE o.order_id IS NULL;
```

### Question 5: Count orders per customer, including zero

**Solution:**

```sql
SELECT
    c.customer_id,
    c.customer_name,
    COUNT(o.order_id) AS order_count
FROM customers AS c
LEFT JOIN orders AS o
    ON c.customer_id = o.customer_id
GROUP BY c.customer_id, c.customer_name
ORDER BY c.customer_id;
```

### Question 6: Show each employee with their manager's name

**Solution:**

```sql
SELECT
    e.employee_name AS employee,
    m.employee_name AS manager
FROM employees AS e
LEFT JOIN employees AS m
    ON e.manager_id = m.employee_id;
```

### Question 7: Explain why Isha appears twice in the customer-orders result

**Solution:**

Isha has two matching rows in `orders`, so the join returns one row for each order. This is expected one-to-many behavior.

### Question 8: Explain the difference between a condition in `ON` and a condition in `WHERE` for a LEFT JOIN

**Solution:**

A condition in `ON` determines which right-side rows can match while preserving all left rows. A condition in `WHERE` filters the joined result afterward and can remove unmatched rows if the condition rejects `NULL`.

### Question 9: Find employees with no matching department

**Solution:**

```sql
SELECT
    e.employee_id,
    e.employee_name,
    e.department_id
FROM employees AS e
LEFT JOIN departments AS d
    ON e.department_id = d.department_id
WHERE d.department_id IS NULL;
```

### Question 10: What is a CROSS JOIN?

**Solution:**

A cross join returns every combination of rows from the two tables. If one table has 4 rows and another has 3 rows, the result contains 12 rows.

---

## 21. Quick Revision

Before writing a join, ask yourself:

1. Which table contains the rows I must preserve?
2. Which columns connect the tables?
3. Can one row match multiple rows?
4. What should happen when there is no match?
5. Are there `NULL` join keys?
6. Could the join multiply rows and inflate an aggregate?
7. Should a filter be in `ON` or `WHERE`?
8. Do I need all matching rows (`INNER`), all left rows (`LEFT`), all right rows (`RIGHT`), or all rows from both sides (`FULL`)?

### The fundamental pattern

```sql
SELECT
    a.column_name,
    b.column_name
FROM table_a AS a
LEFT JOIN table_b AS b
    ON a.key_column = b.key_column;
```

- `FROM` identifies the starting table.
- `JOIN` brings in another table.
- `ON` defines how the rows match.
- The join type determines which unmatched rows are retained.
- `SELECT` chooses the columns to return.
- `WHERE` filters the resulting rows.

**Final takeaway:** Learn what each join preserves, understand the relationship between the tables, and check how unmatched rows and multiple matches affect the result. Those three ideas explain most SQL JOIN problems.
