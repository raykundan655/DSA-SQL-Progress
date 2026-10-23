# SQL Notes: Remaining Important SQL Topics

> **Purpose:** A GitHub-ready guide to important SQL topics that are not covered in the separate notes for JOINs, aggregate functions, subqueries, CTEs, set operators, conditional logic, NULL handling, string functions, numeric functions, and date/time functions.
>
> **Dialect note:** SQL syntax differs across MySQL, PostgreSQL, SQL Server, Oracle, and SQLite. Examples use common SQL where possible. Dialect-specific differences are mentioned when important.

## Contents

1. SQL query logical processing order
2. Window functions
3. Data manipulation: `INSERT`, `UPDATE`, `DELETE`, and UPSERT
4. Constraints and keys
5. Views and materialized views
6. Indexes and query performance
7. Transactions and ACID
8. Isolation levels and concurrency problems
9. Database normalization and denormalization
10. Temporary tables
11. Stored procedures, user-defined functions, and triggers
12. Data quality and safe SQL patterns
13. Common SQL interview mistakes
14. Practice questions with answers
15. Final revision checklist

---

# 1. SQL Query Logical Processing Order

SQL is written in one order, but a database logically processes the clauses in a different order. Understanding this helps explain why some aliases are available in one clause but not another.

A simplified logical order for a `SELECT` query is:

1. `FROM` (including joins)
2. `WHERE`
3. `GROUP BY`
4. `HAVING`
5. `SELECT`
6. `DISTINCT`
7. `ORDER BY`
8. `LIMIT` / `OFFSET` or the dialect's equivalent

This is a **logical model**, not a promise about the physical execution plan. The optimizer may execute operations in a different physical order while preserving the query's meaning.

Example:

```sql
SELECT department_id, COUNT(*) AS employee_count
FROM employees
WHERE status = 'Active'
GROUP BY department_id
HAVING COUNT(*) >= 5
ORDER BY employee_count DESC;
```

Conceptually:
- `FROM` identifies the source table.
- `WHERE` keeps active employees.
- `GROUP BY` forms one group per department.
- `HAVING` keeps groups with at least five employees.
- `SELECT` produces the output columns.
- `ORDER BY` sorts the result.

## 1.1 Why a `SELECT` alias may not work in `WHERE`

```sql
SELECT salary * 12 AS annual_salary
FROM employees
WHERE annual_salary > 100000;
```

This is rejected by many databases because `WHERE` is logically evaluated before the `SELECT` list creates the alias.

Repeat the expression:

```sql
SELECT salary * 12 AS annual_salary
FROM employees
WHERE salary * 12 > 100000;
```

Or use a derived table/CTE if that structure is appropriate:

```sql
SELECT annual_salary
FROM (
    SELECT salary * 12 AS annual_salary
    FROM employees
) AS employee_salaries
WHERE annual_salary > 100000;
```

Alias visibility varies by dialect and clause. In many systems, aliases can be used in `ORDER BY`, but should not be assumed to work in `WHERE`.

---

# 2. Window Functions

## 2.1 What is a window function?

A window function calculates a value using a set of related rows while **keeping the individual rows in the result**. Unlike ordinary grouping, it does not collapse all rows in a group into one output row.

Typical uses:
- Ranking employees within departments.
- Finding the previous or next transaction.
- Calculating running totals.
- Calculating moving averages.
- Comparing a row with a group's average.
- Finding the first or last value in a window.

General structure:

```sql
function_name(expression) OVER (
    PARTITION BY group_column
    ORDER BY sort_column
    ROWS BETWEEN ... AND ...
)
```

The parts are:
- `function_name(...)`: the window function.
- `OVER (...)`: defines the window.
- `PARTITION BY`: divides rows into independent groups; optional.
- `ORDER BY`: defines row order inside each window; optional for some functions.
- Frame clause: chooses the subset of ordered rows used by frame-sensitive functions; optional.

Assume a table named `employees`:

| employee_id | employee_name | department | salary |
|---:|---|---|---:|
| 1 | Asha | IT | 80000 |
| 2 | Ravi | IT | 90000 |
| 3 | Neha | HR | 70000 |
| 4 | Aman | IT | 90000 |
| 5 | Priya | HR | 75000 |

## 2.2 `PARTITION BY`

`PARTITION BY` creates separate windows for each group. It does not itself reduce the number of rows.

```sql
SELECT
    employee_name,
    department,
    salary,
    AVG(salary) OVER (PARTITION BY department) AS department_avg_salary
FROM employees;
```

Every employee remains in the output, and each employee receives their department's average salary.

**Difference from `GROUP BY`:**
- `GROUP BY department` generally returns one row per department when used with an aggregate.
- `AVG(salary) OVER (PARTITION BY department)` returns one row per employee, with the department average repeated on each row.

## 2.3 `ROW_NUMBER()`

Assigns a unique sequential number to each row in the window ordering.

```sql
SELECT
    employee_name,
    department,
    salary,
    ROW_NUMBER() OVER (
        PARTITION BY department
        ORDER BY salary DESC, employee_id
    ) AS row_num
FROM employees;
```

Use a deterministic tie-breaker such as `employee_id` when you need a stable order among equal salaries.

Common uses:
- Choosing one row per group.
- Removing duplicates using a ranking rule.
- Creating numbered results.

Example: select the highest-paid employee in each department:

```sql
SELECT employee_name, department, salary
FROM (
    SELECT
        employee_name,
        department,
        salary,
        ROW_NUMBER() OVER (
            PARTITION BY department
            ORDER BY salary DESC, employee_id
        ) AS rn
    FROM employees
) AS ranked_employees
WHERE rn = 1;
```

This returns one employee per department. If several employees tie for the highest salary, the tie-breaker decides which one is selected.

## 2.4 `RANK()` versus `DENSE_RANK()` versus `ROW_NUMBER()`

Suppose scores are `100, 90, 90, 80`.

| Score | `ROW_NUMBER()`* | `RANK()` | `DENSE_RANK()` |
|---:|---:|---:|---:|
| 100 | 1 | 1 | 1 |
| 90 | 2 | 2 | 2 |
| 90 | 3 | 2 | 2 |
| 80 | 4 | 4 | 3 |

\*The order between tied rows in `ROW_NUMBER()` is not predictable unless a tie-breaker is included.

- `ROW_NUMBER()` gives every row a different number.
- `RANK()` gives ties the same rank and leaves gaps after ties.
- `DENSE_RANK()` gives ties the same rank but does not leave gaps.

Example:

```sql
SELECT
    employee_name,
    salary,
    RANK() OVER (ORDER BY salary DESC) AS salary_rank,
    DENSE_RANK() OVER (ORDER BY salary DESC) AS dense_salary_rank
FROM employees;
```

## 2.5 `LAG()` and `LEAD()`

- `LAG(value)` reads a value from an earlier row in the window ordering.
- `LEAD(value)` reads a value from a later row.

Example table `monthly_sales`:

| month_start | revenue |
|---|---:|
| 2026-01-01 | 10000 |
| 2026-02-01 | 12000 |
| 2026-03-01 | 9000 |

```sql
SELECT
    month_start,
    revenue,
    LAG(revenue) OVER (ORDER BY month_start) AS previous_month_revenue,
    LEAD(revenue) OVER (ORDER BY month_start) AS next_month_revenue
FROM monthly_sales;
```

The first row has no previous row, so `LAG()` returns `NULL` unless a default is supplied. The last row has no next row, so `LEAD()` returns `NULL` unless a default is supplied.

A growth calculation:

```sql
SELECT
    month_start,
    revenue,
    revenue - LAG(revenue) OVER (ORDER BY month_start) AS change_from_previous
FROM monthly_sales;
```

This compares each row with the previous row in the defined order. It does not guarantee that the previous row is the previous calendar month if some months are missing.

## 2.6 Running totals

A running total accumulates a value from the beginning of a partition through the current row.

```sql
SELECT
    transaction_date,
    transaction_id,
    amount,
    SUM(amount) OVER (
        ORDER BY transaction_date, transaction_id
        ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
    ) AS running_total
FROM transactions;
```

- `UNBOUNDED PRECEDING` starts at the first row of the window.
- `CURRENT ROW` ends at the current row.
- Ordering by a unique or stable tie-breaker helps make the result deterministic.

For totals that restart by account:

```sql
SUM(amount) OVER (
    PARTITION BY account_id
    ORDER BY transaction_date, transaction_id
    ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
)
```

## 2.7 Moving averages

A moving average uses a fixed-size frame around the current row.

```sql
SELECT
    sale_date,
    daily_sales,
    AVG(daily_sales) OVER (
        ORDER BY sale_date
        ROWS BETWEEN 2 PRECEDING AND CURRENT ROW
    ) AS three_row_moving_avg
FROM daily_sales;
```

This averages the current row and up to two preceding rows. It is a three-row average, not necessarily a three-calendar-day average if the source has missing dates or multiple rows per day.

## 2.8 Window frames

A frame defines which rows are included for frame-sensitive calculations.

Common frame boundaries:
- `UNBOUNDED PRECEDING`: first row in the partition.
- `n PRECEDING`: a number of rows or a value range before the current row, depending on frame type.
- `CURRENT ROW`: the current row or its peer group, depending on frame type.
- `n FOLLOWING`: a number of rows or a value range after the current row.
- `UNBOUNDED FOLLOWING`: last row in the partition.

Common frame types:
- `ROWS`: counts physical rows.
- `RANGE`: uses ordering values and peer groups; behavior depends on the expression and database.

If you want a row-by-row running total, an explicit `ROWS` frame is often clearer than relying on a database's default frame.

## 2.9 `FIRST_VALUE()` and `LAST_VALUE()`

These return the first or last value within a window frame.

```sql
SELECT
    employee_name,
    department,
    salary,
    FIRST_VALUE(employee_name) OVER (
        PARTITION BY department
        ORDER BY salary DESC, employee_id
    ) AS highest_paid_employee
FROM employees;
```

A frequent pitfall with `LAST_VALUE()` is the frame: the default frame may end at the current row or its peer group, rather than the last row of the whole partition.

To get the last value across the full partition, explicitly define the frame:

```sql
LAST_VALUE(salary) OVER (
    PARTITION BY department
    ORDER BY salary
    ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING
) AS lowest_to_highest_last_salary
```

The meaning of “last” depends on the `ORDER BY` direction.

## 2.10 Filtering by a window-function result

Window functions are not permitted directly in `WHERE` in many databases because `WHERE` is evaluated earlier. Put the calculation in a subquery or CTE, then filter outside it.

```sql
SELECT employee_name, department, salary
FROM (
    SELECT
        employee_name,
        department,
        salary,
        ROW_NUMBER() OVER (
            PARTITION BY department
            ORDER BY salary DESC, employee_id
        ) AS rn
    FROM employees
) AS ranked
WHERE rn <= 2;
```

This returns the top two employees by salary in each department. If the requirement is to include all ties, `RANK()` or `DENSE_RANK()` may be more appropriate.

## 2.11 Window-function mistakes to avoid

1. Confusing window functions with grouped aggregates.
2. Forgetting `ORDER BY` when row sequence matters.
3. Expecting `ROW_NUMBER()` to preserve tie order without a tie-breaker.
4. Confusing gaps in `RANK()` with `DENSE_RANK()`.
5. Treating a three-row moving average as a three-day average.
6. Forgetting that `LAG()`/`LEAD()` may return `NULL` at partition boundaries.
7. Filtering a window result in the same query's `WHERE`.
8. Assuming `LAST_VALUE()` means the last row of the whole partition without checking the frame.
9. Using an unstable sort order for running totals.

---

# 3. Data Manipulation: `INSERT`, `UPDATE`, `DELETE`, and UPSERT

Data manipulation statements change stored rows. Always know which rows a statement will affect before running it against important data.

## 3.1 `INSERT`

Add new rows.

```sql
INSERT INTO employees (employee_id, employee_name, department, salary)
VALUES (101, 'Asha', 'IT', 80000);
```

Best practices:
- List the target columns explicitly.
- Provide values in the same order as the column list.
- Respect data types, constraints, and required columns.
- Do not rely on implicit column order.
- Use parameters in application code rather than building SQL by string concatenation.

Insert multiple rows where supported:

```sql
INSERT INTO employees (employee_id, employee_name, department, salary)
VALUES
    (102, 'Ravi', 'IT', 90000),
    (103, 'Neha', 'HR', 70000);
```

Insert from a query:

```sql
INSERT INTO archived_employees (employee_id, employee_name, department, salary)
SELECT employee_id, employee_name, department, salary
FROM employees
WHERE status = 'Inactive';
```

Check for duplicate keys and other constraint violations before executing bulk inserts.

## 3.2 `UPDATE`

Modify existing rows.

```sql
UPDATE employees
SET salary = 85000
WHERE employee_id = 101;
```

**Critical rule:** Without a `WHERE` clause, the statement updates every row.

```sql
-- Dangerous if you intend to change only one employee:
UPDATE employees
SET salary = 85000;
```

Update based on a condition:

```sql
UPDATE employees
SET salary = salary * 1.05
WHERE department = 'IT';
```

Before a high-impact update, run a `SELECT` with the same filter to inspect the target rows. In production, use a transaction and a verified recovery strategy where appropriate.

## 3.3 `DELETE`

Remove rows.

```sql
DELETE FROM employees
WHERE employee_id = 101;
```

Without `WHERE`, all rows are deleted:

```sql
DELETE FROM employees;
```

This removes all rows but usually leaves the table structure intact. Behavior around triggers, foreign keys, identity counters, and transaction logging is database-specific.

To inspect rows before deletion:

```sql
SELECT *
FROM employees
WHERE status = 'Inactive';
```

## 3.4 `DELETE` versus `TRUNCATE` versus `DROP`

| Statement | Main effect | Table structure remains? | Key considerations |
|---|---|---|---|
| `DELETE` | Removes selected rows, or all rows if no `WHERE` | Yes | Can use `WHERE`; triggers and logging depend on database |
| `TRUNCATE` | Removes all rows efficiently in supported systems | Yes | Usually cannot use `WHERE`; identity reset, trigger, and transaction behavior vary |
| `DROP TABLE` | Removes the table object | No | Removes table definition and data; dependencies may block it |

These statements are not interchangeable. Confirm the target object, permissions, dependencies, and transaction behavior before running destructive commands.

## 3.5 UPSERT: insert or update

An UPSERT inserts a row if a key is new or updates an existing row if a conflict occurs. Syntax varies substantially.

### PostgreSQL

```sql
INSERT INTO product_stock (product_id, quantity)
VALUES (10, 25)
ON CONFLICT (product_id)
DO UPDATE SET quantity = EXCLUDED.quantity;
```

### MySQL

```sql
INSERT INTO product_stock (product_id, quantity)
VALUES (10, 25)
ON DUPLICATE KEY UPDATE quantity = VALUES(quantity);
```

The exact recommended syntax can vary by MySQL version.

### SQL Server / Oracle

Approaches include `MERGE` or an explicit transactional update/insert pattern. `MERGE` behavior and concurrency considerations are database- and version-specific; do not assume the syntax or semantics are portable.

Use a unique constraint or primary key to define what counts as a conflict. Without a reliable key, duplicate rows may still be inserted.

## 3.6 Safer modification workflow

For a consequential change:

1. Identify the target table and key.
2. Write the `WHERE` condition.
3. Run a `SELECT` with the same condition.
4. Verify the number and content of rows.
5. Use a transaction if supported and appropriate.
6. Execute the change.
7. Verify the result.
8. Commit only when correct; otherwise roll back if the transaction is still open.

Example:

```sql
BEGIN;

UPDATE employees
SET salary = salary * 1.05
WHERE department = 'IT';

SELECT employee_id, employee_name, salary
FROM employees
WHERE department = 'IT';

-- If correct:
COMMIT;

-- If incorrect, use ROLLBACK instead of COMMIT.
```

Transaction syntax and autocommit behavior differ. Some database clients or engines handle DDL and transactions differently, so verify your environment.

---

# 4. Constraints and Keys

Constraints protect data quality by preventing invalid or inconsistent rows from being stored.

## 4.1 Primary key

A primary key uniquely identifies each row. It must be unique and non-`NULL`.

```sql
CREATE TABLE departments (
    department_id INT PRIMARY KEY,
    department_name VARCHAR(100) NOT NULL
);
```

A table has one primary-key constraint, which can consist of one or multiple columns.

## 4.2 Foreign key

A foreign key requires values to match a referenced key, subject to the database's `NULL` and constraint rules.

```sql
CREATE TABLE employees (
    employee_id INT PRIMARY KEY,
    employee_name VARCHAR(100) NOT NULL,
    department_id INT,
    FOREIGN KEY (department_id)
        REFERENCES departments(department_id)
);
```

This helps prevent an employee from referencing a department that does not exist. Whether a foreign key may be `NULL` depends on the column's nullability; `NOT NULL` is needed if every employee must have a department.

Foreign-key actions may include `RESTRICT`, `NO ACTION`, `CASCADE`, `SET NULL`, and `SET DEFAULT`, depending on database support and exact semantics.

Example:

```sql
FOREIGN KEY (department_id)
REFERENCES departments(department_id)
ON DELETE SET NULL
```

Deleting a referenced department sets the dependent `department_id` to `NULL` if the database supports this action and the column allows `NULL`.

## 4.3 `UNIQUE`

Requires values to be unique according to the database's constraint semantics.

```sql
CREATE TABLE users (
    user_id INT PRIMARY KEY,
    email VARCHAR(255) UNIQUE
);
```

`NULL` behavior in unique constraints differs across databases: some allow multiple `NULL` values; others handle them differently. If the value is required, combine `UNIQUE` with `NOT NULL`.

## 4.4 `NOT NULL`

Prevents a column from storing `NULL`.

```sql
CREATE TABLE courses (
    course_id INT PRIMARY KEY,
    course_name VARCHAR(100) NOT NULL
);
```

`NOT NULL` does not prevent empty strings or blank text. Add a separate check if those values must also be prohibited.

## 4.5 `CHECK`

Requires a Boolean condition to be satisfied for inserted or updated rows, according to the database's check-constraint rules.

```sql
CREATE TABLE products (
    product_id INT PRIMARY KEY,
    price DECIMAL(10, 2) CHECK (price >= 0),
    quantity INT CHECK (quantity >= 0)
);
```

A check constraint is valuable for rules that must always hold. Check support and enforcement details can vary by database/version. A check condition that evaluates to `UNKNOWN` because of `NULL` may not reject the row in many systems; add `NOT NULL` if missing values are forbidden.

## 4.6 `DEFAULT`

Supplies a value when an insert omits the column or explicitly uses the database's default syntax.

```sql
CREATE TABLE tasks (
    task_id INT PRIMARY KEY,
    task_name VARCHAR(100) NOT NULL,
    status VARCHAR(20) DEFAULT 'Pending'
);
```

A default does not normally mean that an explicitly supplied `NULL` is automatically replaced with the default. Use `NOT NULL` as well if `NULL` must not be stored.

## 4.7 Composite keys

A composite key uses more than one column to identify a row.

```sql
CREATE TABLE course_enrollments (
    student_id INT NOT NULL,
    course_id INT NOT NULL,
    enrollment_date DATE,
    PRIMARY KEY (student_id, course_id)
);
```

This prevents the same student-course pair from appearing more than once, but still permits one student to enroll in many courses and one course to have many students.

## 4.8 Natural keys versus surrogate keys

- **Natural key:** a meaningful real-world value, such as a government-issued code or a carefully chosen business identifier.
- **Surrogate key:** a generated identifier such as an integer identity or UUID.

A natural value may change or have privacy implications. A surrogate key can provide a stable internal identifier, while a separate `UNIQUE` constraint protects the business value.

## 4.9 Why constraints matter

Constraints:
- Prevent duplicate identifiers.
- Protect relationships between tables.
- Enforce required values and valid ranges.
- Reduce invalid data before it reaches reports or applications.
- Document business rules in the database.

Application validation is useful, but database constraints remain important because data can also be written by scripts, integrations, or other applications.

---

# 5. Views and Materialized Views

## 5.1 View

A view is a named query that can be queried like a table.

```sql
CREATE VIEW active_employees AS
SELECT employee_id, employee_name, department
FROM employees
WHERE status = 'Active';
```

Use it:

```sql
SELECT *
FROM active_employees
WHERE department = 'IT';
```

A normal view usually stores the query definition, not a separate copy of the result. The underlying tables are read when the view is queried, subject to database implementation and optimization.

### Why use views?
- Reuse a common query.
- Simplify complicated query interfaces.
- Present only selected columns to users.
- Provide a stable logical interface over changing table structures.
- Support security design when combined with appropriate privileges.

A view is not automatically a security boundary in every configuration. Permissions and underlying-object access must be configured correctly.

## 5.2 Updating through a view

Some views are updatable; others are not. Views involving grouping, aggregates, `DISTINCT`, set operators, or complex joins are often restricted or require special rules.

Do not assume that every view can be used for `INSERT`, `UPDATE`, or `DELETE`. Check the database's updatability rules.

## 5.3 Materialized view

A materialized view stores the result of a query physically, where supported.

Typical advantages:
- Faster reads for expensive summaries.
- Useful for dashboards and reporting workloads.

Typical trade-offs:
- Storage overhead.
- Refreshing takes time and resources.
- Results can become stale between refreshes.
- Refresh syntax and incremental-refresh support vary.

Conceptual example (syntax is database-specific):

```sql
CREATE MATERIALIZED VIEW monthly_sales_summary AS
SELECT
    product_id,
    SUM(amount) AS total_sales
FROM sales
GROUP BY product_id;
```

A database may require an explicit refresh operation. PostgreSQL, Oracle, and other systems have different syntax and capabilities.

## 5.4 View versus materialized view

| Feature | Normal view | Materialized view |
|---|---|---|
| Stores query definition | Usually yes | Yes |
| Stores result rows separately | Usually no | Yes |
| Needs refresh for changed base data | Usually no separate refresh | Often yes |
| Read performance | Depends on underlying query and optimization | Can be faster for expensive queries |
| Storage overhead | Usually low | Requires storage for results |

---

# 6. Indexes and Query Performance

## 6.1 What is an index?

An index is a data structure that helps a database locate rows without scanning every row in a table. Indexes can improve read performance, but they require storage and add work to inserts, updates, and deletes.

Example:

```sql
CREATE INDEX idx_employees_department
ON employees(department);
```

A query that filters by department may benefit:

```sql
SELECT employee_id, employee_name
FROM employees
WHERE department = 'IT';
```

The optimizer decides whether an index is useful. Creating an index does not guarantee that every query will use it.

## 6.2 Primary-key and unique indexes

Many databases implement primary-key and unique constraints using indexes, but implementation details differ. Avoid creating duplicate indexes without checking existing indexes and constraints.

## 6.3 Composite indexes

A composite index covers multiple columns.

```sql
CREATE INDEX idx_orders_customer_date
ON orders(customer_id, order_date);
```

This may help queries such as:

```sql
SELECT *
FROM orders
WHERE customer_id = 42
  AND order_date >= '2026-01-01';
```

Column order matters. A composite index on `(customer_id, order_date)` often helps when the query filters by `customer_id`, with or without a date condition. It may be less useful for a query that filters only by `order_date`, depending on the database's indexing method and optimizer.

Design indexes based on real query patterns, selectivity, table size, write load, and execution plans.

## 6.4 Covering indexes

A covering index contains the columns needed by a query, allowing the database to satisfy the query from the index in some cases without visiting the base table.

The exact implementation and syntax vary. SQL Server supports `INCLUDE` columns in some indexes; other databases have their own index designs.

## 6.5 Read an execution plan

An execution plan shows how the database expects to execute a query or how it actually executed it, depending on the command.

It can reveal:
- Table scans and index scans/seeks.
- Join algorithms.
- Estimated and actual row counts.
- Sorts and hash operations.
- Expensive operations and possible cardinality-estimation problems.

Common commands differ:
- PostgreSQL: `EXPLAIN`, `EXPLAIN ANALYZE`.
- MySQL: `EXPLAIN`, with additional analysis options depending on version.
- SQL Server: estimated/actual execution plans and `SET STATISTICS IO, TIME ON`.
- Oracle: `EXPLAIN PLAN` and runtime plan tools.

`EXPLAIN ANALYZE`-style commands may execute the query. Be cautious with data-modifying statements and production workloads.

## 6.6 Sargability

A predicate is commonly called **sargable** when the database can use an index efficiently to locate matching rows.

Often less index-friendly:

```sql
SELECT *
FROM orders
WHERE YEAR(order_date) = 2026;
```

Often preferable:

```sql
SELECT *
FROM orders
WHERE order_date >= '2026-01-01'
  AND order_date <  '2027-01-01';
```

The second form leaves the column unwrapped in a function and gives a range. It is often more index-friendly, though actual behavior depends on the optimizer and indexes.

Other common problems:
- Applying functions or calculations to indexed columns.
- Implicitly converting a column to another type.
- Starting a `LIKE` pattern with a wildcard, such as `LIKE '%phone'`, which often prevents ordinary B-tree prefix lookup.
- Using mismatched data types for parameters and columns.

## 6.7 Index trade-offs

Indexes are not free:
- They consume disk space and memory.
- They slow writes because index entries must be maintained.
- Too many indexes can increase maintenance and planning costs.
- Low-selectivity indexes may not help some queries.
- Stale statistics can lead to poor plans.

Do not index every column. Use workload evidence and execution plans.

## 6.8 Practical performance checklist

1. Return only needed columns instead of `SELECT *` for stable production queries.
2. Filter as specifically as the requirement allows.
3. Check join and filter columns for suitable indexes.
4. Use typed parameters and avoid unnecessary implicit conversions.
5. Prefer date ranges for timestamp filtering.
6. Check actual execution plans and row counts.
7. Avoid repeated calculations when a clear alternative exists.
8. Do not add indexes without considering write cost.
9. Test with realistic data volume and distributions.
10. Measure before and after changes rather than assuming an optimization worked.

---

# 7. Transactions and ACID

## 7.1 What is a transaction?

A transaction groups one or more operations into a unit of work. The database should either commit the intended changes or roll them back according to its transaction semantics.

Basic structure:

```sql
BEGIN;

UPDATE accounts
SET balance = balance - 500
WHERE account_id = 1;

UPDATE accounts
SET balance = balance + 500
WHERE account_id = 2;

COMMIT;
```

This is a simplified transfer example. A production transfer must also validate the source account, sufficient funds, account existence, currency, concurrency, and error handling. Syntax varies by database/client.

If a step fails before commit, the application may need to roll back:

```sql
ROLLBACK;
```

Autocommit settings and transaction boundaries vary by engine and client.

## 7.2 ACID properties

### Atomicity
All operations in the transaction succeed as one unit, or the transaction is rolled back.

### Consistency
A committed transaction preserves database rules and constraints, assuming the transaction and rules are correctly designed.

### Isolation
Concurrent transactions are controlled so their intermediate effects do not cause disallowed observations, according to the chosen isolation level.

### Durability
After a successful commit, changes survive the failures covered by the database's durability guarantees.

ACID does not mean that a poorly designed transaction automatically enforces every business rule; the application and database constraints must define those rules.

## 7.3 `COMMIT` and `ROLLBACK`

- `COMMIT` makes the transaction's changes permanent under the database's transaction semantics.
- `ROLLBACK` cancels uncommitted changes in the current transaction, subject to engine-specific behavior.

Do not assume every statement is transactional in every database. Some DDL statements may implicitly commit or have different transaction behavior.

## 7.4 Savepoints

A savepoint marks a point within a transaction that can be rolled back to without necessarily discarding the entire transaction.

```sql
BEGIN;

UPDATE inventory
SET quantity = quantity - 1
WHERE product_id = 10;

SAVEPOINT after_inventory_update;

UPDATE orders
SET status = 'Confirmed'
WHERE order_id = 200;

-- If only the second change needs to be undone:
ROLLBACK TO SAVEPOINT after_inventory_update;

-- Decide whether to continue or roll back the whole transaction.
COMMIT;
```

This is illustrative; exact syntax and savepoint behavior vary by database.

## 7.5 Transaction best practices

- Keep transactions as short as practical.
- Validate assumptions before changing data.
- Lock or check shared data appropriately.
- Handle errors and rollbacks in application code.
- Avoid waiting for user input while holding locks.
- Understand how the chosen isolation level affects reads and writes.
- Use idempotency or unique constraints to protect retryable operations.
- Do not assume that a transaction spanning multiple independent systems is automatically atomic.

---

# 8. Isolation Levels and Concurrency Problems

Concurrent transactions may access and modify the same rows. Isolation levels control which interactions are allowed.

## 8.1 Common concurrency anomalies

### Dirty read
A transaction reads another transaction's uncommitted change. If that other transaction rolls back, the first transaction read a value that was never committed.

### Non-repeatable read
A transaction reads a row, another transaction changes and commits it, and the first transaction reads the same row again and gets a different value.

### Phantom read
A transaction repeats a query for a set of rows and finds that another transaction has inserted or deleted rows matching the condition.

### Lost update
Two transactions read the same old value and both write a new value based on it; one update can overwrite the other.

### Write skew
Two transactions read overlapping data and update different rows in a way that jointly violates a business rule. Whether this is possible depends on the isolation model and locking strategy.

## 8.2 Common isolation levels

The SQL standard describes common levels, but actual behavior differs by database engine and implementation.

| Isolation level | General idea | Important caveat |
|---|---|---|
| `READ UNCOMMITTED` | Allows the weakest isolation; dirty reads may be possible | Some databases do not truly expose dirty reads |
| `READ COMMITTED` | A statement generally sees committed data | Repeated statements may see different committed values |
| `REPEATABLE READ` | Re-reading rows generally avoids non-repeatable reads | Phantom and write-skew behavior varies by engine |
| `SERIALIZABLE` | Aims to make concurrent transactions behave like some serial order | May block or abort transactions; application retries may be needed |

Some databases use multiversion concurrency control (MVCC), snapshot isolation, locking, or combinations. The same isolation-level name can have different implementation details across systems.

## 8.3 Why isolation matters: a lost-update example

Suppose an account balance is `100`.

1. Transaction A reads `100`.
2. Transaction B reads `100`.
3. A calculates `100 - 10 = 90` and writes `90`.
4. B calculates `100 - 20 = 80` and writes `80`.

The final balance may be `80`, losing A's deduction.

A safer approach may be a single atomic update:

```sql
UPDATE accounts
SET balance = balance - 10
WHERE account_id = 1
  AND balance >= 10;
```

Then inspect the affected-row count. This is only one possible approach; business rules and transaction isolation still matter. For more complex logic, use appropriate locks, optimistic concurrency checks, constraints, or serializable transactions.

## 8.4 Deadlocks

A deadlock occurs when transactions hold resources the others need, creating a cycle of waiting.

Example:
- Transaction A locks row 1 and waits for row 2.
- Transaction B locks row 2 and waits for row 1.

The database may detect the deadlock and abort one transaction.

Ways to reduce deadlocks:
- Access rows and tables in a consistent order.
- Keep transactions short.
- Avoid unnecessary locks.
- Index predicates so operations locate rows efficiently.
- Retry transactions safely when the database reports a retryable deadlock or serialization failure.

Do not blindly retry non-idempotent operations without safeguards.

---

# 9. Database Normalization and Denormalization

Normalization organizes data to reduce unnecessary duplication and update anomalies. The following are simplified explanations of common normal forms.

## 9.1 Why normalization matters

Consider this table:

| student_id | student_name | course_id | course_name | instructor |
|---:|---|---|---|---|
| 1 | Asha | 10 | SQL | Ravi |
| 1 | Asha | 20 | Python | Neha |
| 2 | Aman | 10 | SQL | Ravi |

The student name repeats for every course, and course information repeats for every student. This can create anomalies.

### Update anomaly
Changing the instructor for SQL requires updating multiple rows. If one row is missed, the data becomes inconsistent.

### Insert anomaly
It may be difficult to store a course before any student enrolls if course information exists only in the enrollment table.

### Delete anomaly
Deleting the last enrollment for a course may unintentionally remove the only stored copy of that course's information.

## 9.2 First Normal Form (1NF)

A simplified 1NF rule: each column contains a single value from its intended domain rather than a list of repeating values in one field, and rows can be identified consistently.

Poor design:

| student_id | student_name | courses |
|---:|---|---|
| 1 | Asha | SQL, Python, Java |

Better design separates enrollments into rows:

| student_id | course_id |
|---:|---:|
| 1 | 10 |
| 1 | 20 |
| 1 | 30 |

Do not store comma-separated lists in a column when the values need to be individually queried, validated, or related.

## 9.3 Second Normal Form (2NF)

A simplified 2NF rule:
- The table is in 1NF.
- Every non-key attribute depends on the **whole candidate key**, not only part of a composite key.

Suppose the key for `enrollments` is `(student_id, course_id)`:

| student_id | course_id | student_name | course_name | grade |
|---:|---:|---|---|---|

Dependencies:
- `student_name` depends on `student_id`, only part of the composite key.
- `course_name` depends on `course_id`, only part of the composite key.
- `grade` may depend on the full `(student_id, course_id)` pair.

Split the data:

```text
Students(student_id, student_name)
Courses(course_id, course_name)
Enrollments(student_id, course_id, grade)
```

The exact normalization analysis depends on the real functional dependencies and candidate keys.

## 9.4 Third Normal Form (3NF)

A simplified 3NF rule: the table is in 2NF and non-key attributes do not depend transitively on a candidate key through another non-key attribute, subject to the formal 3NF definition.

Example:

| employee_id | employee_name | department_id | department_name |
|---:|---|---:|---|
| 1 | Asha | 10 | IT |
| 2 | Ravi | 10 | IT |
| 3 | Neha | 20 | HR |

If `department_id` determines `department_name`, the department name is stored repeatedly. Separate it:

```text
Employees(employee_id, employee_name, department_id)
Departments(department_id, department_name)
```

This avoids repeating department details for every employee.

## 9.5 Normalized design example

A basic design might be:

```sql
CREATE TABLE students (
    student_id INT PRIMARY KEY,
    student_name VARCHAR(100) NOT NULL
);

CREATE TABLE courses (
    course_id INT PRIMARY KEY,
    course_name VARCHAR(100) NOT NULL
);

CREATE TABLE enrollments (
    student_id INT NOT NULL,
    course_id INT NOT NULL,
    grade VARCHAR(2),
    PRIMARY KEY (student_id, course_id),
    FOREIGN KEY (student_id) REFERENCES students(student_id),
    FOREIGN KEY (course_id) REFERENCES courses(course_id)
);
```

This separates students, courses, and the many-to-many enrollment relationship.

## 9.6 Denormalization

Denormalization intentionally duplicates or precomputes data to improve selected read workloads.

Examples:
- Storing a precomputed reporting total.
- Maintaining a summary table for dashboards.
- Duplicating a descriptive attribute in a read-optimized analytics model.

Trade-offs:
- Faster reads in some workloads.
- More storage.
- Extra work to keep duplicated data consistent.
- Risk of stale or conflicting values.

Normalize first for correctness and maintainability; denormalize based on measured performance requirements and a clear consistency strategy.

---

# 10. Temporary Tables

## 10.1 What is a temporary table?

A temporary table stores intermediate rows for a limited lifetime. It can help break a complex workflow into steps, reuse an intermediate result, or stage data before processing.

Syntax and lifetime rules vary by database.

Example in SQL Server-style syntax:

```sql
CREATE TABLE #high_value_orders (
    order_id INT,
    customer_id INT,
    order_total DECIMAL(12, 2)
);

INSERT INTO #high_value_orders (order_id, customer_id, order_total)
SELECT order_id, customer_id, order_total
FROM orders
WHERE order_total >= 1000;

SELECT *
FROM #high_value_orders;
```

The `#` prefix is specific to SQL Server local temporary tables.

A common alternative in systems that support it:

```sql
CREATE TEMPORARY TABLE high_value_orders AS
SELECT order_id, customer_id, order_total
FROM orders
WHERE order_total >= 1000;
```

This form is supported by some databases but is not universal.

## 10.2 Temporary tables versus CTEs

| Feature | Temporary table | CTE |
|---|---|---|
| Persists as a table object for a limited scope/lifetime | Yes | No; it names a query expression |
| Can often be indexed or have constraints | Often, subject to database | Not generally as a separate stored object |
| Can be reused across multiple statements | Usually during its lifetime | Usually only within the statement where defined |
| Materialization | Stores rows in a temporary table | Optimizer may inline or materialize depending on database |
| Best fit | Multi-step processing or reused intermediate results | Making one statement easier to read |

A CTE is not automatically faster or slower than a temporary table. Choose based on scope, reuse, execution plans, and the database.

## 10.3 Temporary-table considerations

- Know whether the table is scoped to a session, transaction, or procedure.
- Understand what happens when the connection closes.
- Do not assume temporary tables are shared across connections.
- Clean up explicitly when required by the database or workflow.
- For large data, consider indexes and statistics where supported.
- Be aware of storage and transaction-log implications.

---

# 11. Stored Procedures, User-Defined Functions, and Triggers

These database objects allow reusable logic to be defined in or associated with the database. Syntax and capabilities vary considerably.

## 11.1 Stored procedure

A stored procedure is a named routine that can perform one or more operations. It may accept parameters and return result sets or output parameters, depending on the database.

Typical uses:
- Encapsulating a multi-step database operation.
- Applying a standard business process.
- Centralizing permission-controlled data changes.
- Reducing repeated SQL in applications.

A generic conceptual example:

```sql
-- Pseudocode: procedure syntax varies by database.
CREATE PROCEDURE GetEmployeesByDepartment(IN dept_name VARCHAR(100))
BEGIN
    SELECT employee_id, employee_name, salary
    FROM employees
    WHERE department = dept_name;
END;
```

This is illustrative pseudocode, not portable copy-and-run SQL. MySQL, PostgreSQL, SQL Server, and Oracle use different procedure declarations and parameter syntax.

## 11.2 User-defined function (UDF)

A user-defined function returns a value or table-like result, according to the database's supported function types.

Conceptual scalar function:

```text
AnnualSalary(monthly_salary) = monthly_salary * 12
```

A UDF can centralize reusable logic, but performance and allowed side effects vary. Some database functions can be inlined or optimized; others may add overhead. Use built-in operations when they clearly express the calculation.

## 11.3 Stored procedure versus function

| Feature | Stored procedure | Function |
|---|---|---|
| Main purpose | Perform an operation or workflow | Return a value or table-like result |
| How invoked | Often with `CALL` or `EXEC`, depending on database | Often within an expression or `FROM` clause |
| Can modify data | Often yes, subject to database rules | Restrictions vary significantly |
| Return behavior | Result sets, output parameters, status, etc. | Scalar or table-like result, depending on type |
| Portability | Low to moderate | Low to moderate |

Do not rely on this table as a universal rule: database-specific behavior can differ.

## 11.4 Trigger

A trigger runs automatically when a specified event occurs, commonly an `INSERT`, `UPDATE`, or `DELETE`, or at another supported timing/event.

Common uses:
- Auditing changes.
- Enforcing rules that cannot be expressed as ordinary constraints.
- Maintaining derived data in controlled cases.

Conceptual example:

```text
AFTER UPDATE ON employees:
    write the old and new salary to an audit table
```

Trigger syntax is database-specific; some engines support row-level and statement-level triggers, and event/timing capabilities differ.

## 11.5 Trigger risks

Triggers can be useful, but hidden side effects make systems harder to understand:
- A simple update may cause additional writes.
- Recursive or cascading trigger behavior can be difficult to debug.
- Bulk operations may have performance implications.
- Trigger order and transaction behavior vary.
- Business logic split between application code and triggers can become hard to maintain.

Document triggers clearly and test both direct and indirect effects.

## 11.6 Auditing example: design considerations

An audit table may store:
- Which record changed.
- The action performed.
- Old and new values, where appropriate.
- Who or what initiated the change.
- A timestamp.

Security and privacy matter: do not log secrets, passwords, tokens, or unnecessary personal data. Audit requirements should define retention and access permissions.

---

# 12. Data Quality and Safe SQL Patterns

## 12.1 Find duplicate values

To identify email addresses that occur more than once:

```sql
SELECT email, COUNT(*) AS occurrences
FROM users
GROUP BY email
HAVING COUNT(*) > 1;
```

This identifies duplicate groups, not necessarily every full duplicate row. The behavior of grouping `NULL` values and text comparison depends on the database's rules.

To prevent future duplicates, use an appropriate `UNIQUE` constraint if the business rule requires uniqueness. First resolve existing duplicates.

## 12.2 Find missing sequence numbers

Suppose `orders.order_id` is expected to increase, and you want to investigate gaps. A gap is not necessarily an error: generated IDs can have gaps after rollbacks, deletions, or concurrent inserts.

A window-based way to inspect gaps between existing IDs:

```sql
SELECT
    order_id,
    LAG(order_id) OVER (ORDER BY order_id) AS previous_id
FROM orders;
```

Then examine rows where `order_id - previous_id > 1`. Exact syntax for filtering a window result requires an outer query or CTE in many databases.

Do not assume every missing numeric identifier means data loss.

## 12.3 Safe division

```sql
SELECT
    revenue / NULLIF(units_sold, 0) AS revenue_per_unit
FROM sales;
```

This changes a zero denominator to `NULL`, avoiding division by zero in many SQL systems. Ensure the operand types support the precision you need; integer division may still truncate a fractional result.

## 12.4 Explicitly choose columns

Instead of:

```sql
SELECT *
FROM employees;
```

Prefer:

```sql
SELECT employee_id, employee_name, department
FROM employees;
```

Advantages:
- Clearer intent.
- Less unnecessary data transfer.
- More stable application interfaces when table columns change.
- Reduced risk of accidentally exposing sensitive columns.

`SELECT *` can still be useful for exploration and quick checks.

## 12.5 Parameterized queries

Do not build SQL by concatenating untrusted input into a query string.

Unsafe conceptual pattern:

```text
sql = "SELECT * FROM users WHERE email = '" + user_input + "'"
```

Safer conceptual pattern:

```sql
SELECT user_id, email
FROM users
WHERE email = ?;
```

The placeholder syntax varies by database driver (`?`, `%s`, named parameters, and others). Bind the user input as a parameter through the driver or ORM.

Parameterized queries:
- Separate SQL structure from data values.
- Help prevent SQL injection.
- Handle quoting and type binding more reliably.

Parameters generally cannot substitute arbitrary SQL identifiers such as table names or sort directions. If identifiers must be dynamic, validate them against a strict allowlist and use the driver's safe identifier mechanism where available.

## 12.6 Idempotency

An operation is idempotent if repeating it produces the same intended state as performing it once, under the defined conditions.

Example of a state-setting operation:

```sql
UPDATE jobs
SET status = 'Completed'
WHERE job_id = 100;
```

Running it repeatedly leaves the status as `Completed`, assuming no other logic changes it.

By contrast, this is not idempotent:

```sql
UPDATE accounts
SET balance = balance - 10
WHERE account_id = 1;
```

Repeating it subtracts another 10 each time.

Idempotency is important for retries, payment workflows, background jobs, and distributed systems. Use unique request identifiers, unique constraints, and transaction-safe designs where appropriate.

## 12.7 Soft deletes versus hard deletes

- **Hard delete:** removes a row from the table.
- **Soft delete:** marks a row as deleted, for example with `deleted_at` or `is_deleted`.

Example:

```sql
UPDATE users
SET is_deleted = 1
WHERE user_id = 25;
```

The value type and Boolean representation vary by database.

Soft deletes can help with recovery and audit history, but they require careful query filters, uniqueness rules, retention policies, and access control. A soft-deleted row still exists and may still contain personal data.

## 12.8 Transactions for multi-step data changes

When several changes must succeed together, use a transaction where supported:

```sql
BEGIN;

INSERT INTO orders (order_id, customer_id, status)
VALUES (500, 42, 'Pending');

INSERT INTO order_items (order_id, product_id, quantity)
VALUES (500, 10, 2);

COMMIT;
```

If the second operation fails, the application should normally roll back rather than leave an incomplete order. The exact transaction behavior depends on the engine, client settings, and statement types.

---

# 13. Common SQL Interview Mistakes

1. Assuming SQL is physically executed in the written order.
2. Confusing a window function with `GROUP BY` aggregation.
3. Using `ROW_NUMBER()` when all tied rows must be included.
4. Forgetting to define a stable order for ranking or running totals.
5. Updating or deleting data without checking the target rows.
6. Assuming `DELETE`, `TRUNCATE`, and `DROP` are equivalent.
7. Assuming all databases use identical UPSERT syntax.
8. Treating a view as if it always stores a result copy.
9. Assuming every view is updatable.
10. Creating indexes without considering write overhead or query plans.
11. Assuming a composite index is equally useful for every column order.
12. Believing that an index guarantees a faster query.
13. Assuming every database implements isolation levels identically.
14. Confusing dirty reads, non-repeatable reads, phantom reads, and lost updates.
15. Assuming normalization means “never duplicate anything”; denormalization can be justified for measured workloads.
16. Assuming temporary tables have the same scope and syntax in every database.
17. Using triggers without documenting their side effects.
18. Concatenating untrusted input into SQL.
19. Treating all numeric IDs as gap-free sequences.
20. Retrying non-idempotent operations without safeguards.

---

# 14. Practice Questions with Answers

## Questions

1. What is the logical processing order of a typical `SELECT` query?
2. Why may a `SELECT` alias not be available in `WHERE`?
3. How does a window function differ from `GROUP BY` aggregation?
4. What is the difference between `ROW_NUMBER()`, `RANK()`, and `DENSE_RANK()`?
5. What do `LAG()` and `LEAD()` do?
6. How would you calculate a running total?
7. Why can `LAST_VALUE()` return a value that seems unexpected?
8. What can happen if `UPDATE` is executed without a `WHERE` clause?
9. How does `DELETE` differ from `TRUNCATE` and `DROP`?
10. What is an UPSERT?
11. What is the purpose of a foreign key?
12. What is the difference between `UNIQUE` and `PRIMARY KEY`?
13. What is the difference between a view and a materialized view?
14. What is an index, and what is its main trade-off?
15. Why does column order matter in a composite index?
16. What does ACID stand for?
17. What is a dirty read?
18. What is a lost update?
19. What is the purpose of normalization?
20. What is the difference between 2NF and 3NF in simplified terms?
21. When might a temporary table be preferable to a CTE?
22. What is the difference between a stored procedure and a function?
23. What is a database trigger?
24. Why should application queries use parameters?
25. What does idempotency mean, and why is it useful?

## Answers

1. A common logical order is `FROM`, `WHERE`, `GROUP BY`, `HAVING`, `SELECT`, `DISTINCT`, `ORDER BY`, then row limiting; details vary by dialect.
2. `WHERE` is logically evaluated before the `SELECT` list creates the alias.
3. A grouped aggregate usually reduces rows into groups; a window function calculates over related rows while retaining each result row.
4. `ROW_NUMBER()` gives each row a distinct number; `RANK()` leaves gaps after ties; `DENSE_RANK()` does not leave gaps.
5. `LAG()` reads a prior row's value and `LEAD()` reads a later row's value in the window ordering.
6. Use `SUM(value) OVER (ORDER BY sort_key ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW)`, with a suitable ordering key.
7. Its result depends on the window frame; define a full-partition frame when the last row of the whole partition is required.
8. Every row in the table may be updated.
9. `DELETE` removes rows and can filter with `WHERE`; `TRUNCATE` removes all rows in supported systems; `DROP` removes the table object.
10. An insert-or-update operation when a key conflict occurs.
11. It protects referential integrity by requiring a referenced value to exist, subject to nullability and database rules.
12. A primary key identifies rows and is unique/non-null; a table has one primary-key constraint, while it may have multiple unique constraints, with `NULL` behavior depending on the database.
13. A normal view usually stores a query definition; a materialized view stores query results and may need refresh.
14. An index can speed up lookups but consumes storage and adds write/maintenance cost.
15. Indexes are ordered by their key columns; leading-column access patterns often matter.
16. Atomicity, Consistency, Isolation, Durability.
17. Reading another transaction's uncommitted changes.
18. A concurrent write overwrites another update based on stale data.
19. To organize data and reduce avoidable duplication and insertion/update/deletion anomalies.
20. 2NF removes partial dependencies on part of a composite candidate key; 3NF additionally addresses transitive dependencies of non-key attributes, subject to formal definitions.
21. When an intermediate result must be reused across statements, indexed, or explicitly staged, depending on database support.
22. A procedure performs a routine/workflow; a function returns a value or table-like result. Exact rules vary by database.
23. A routine that runs automatically in response to a defined database event.
24. Parameters separate values from SQL text and help prevent SQL injection.
25. Repeating an operation has the same intended effect as doing it once; this helps make retries safer.

---

# 15. Final Revision Checklist

- [ ] Understand the logical processing order of `SELECT`.
- [ ] Know how `PARTITION BY`, `ORDER BY`, and frames affect window functions.
- [ ] Distinguish `ROW_NUMBER()`, `RANK()`, and `DENSE_RANK()`.
- [ ] Use `LAG()`/`LEAD()` and running totals correctly.
- [ ] Use explicit column lists for `INSERT`.
- [ ] Verify target rows before `UPDATE` or `DELETE`.
- [ ] Know the differences among `DELETE`, `TRUNCATE`, and `DROP`.
- [ ] Understand UPSERT and dialect-specific syntax.
- [ ] Know primary, foreign, unique, composite, and surrogate keys.
- [ ] Understand `NOT NULL`, `CHECK`, and `DEFAULT`.
- [ ] Know the difference between normal and materialized views.
- [ ] Understand index benefits, costs, and composite-column order.
- [ ] Use execution plans to measure query performance.
- [ ] Understand ACID, commit, rollback, and savepoints.
- [ ] Know common concurrency anomalies and isolation-level trade-offs.
- [ ] Understand the basic goals of 1NF, 2NF, and 3NF.
- [ ] Know when temporary tables can be useful.
- [ ] Understand procedures, functions, and triggers.
- [ ] Use parameterized queries for untrusted values.
- [ ] Design retryable operations with idempotency and constraints in mind.

## Recommended study order

1. SQL logical processing order
2. Window functions
3. Data modification statements
4. Constraints and keys
5. Views
6. Indexes and execution plans
7. Transactions and ACID
8. Isolation and concurrency
9. Normalization
10. Temporary tables
11. Procedures, functions, and triggers
12. Data quality, safe queries, and interview revision

---

**Reminder:** SQL is not perfectly uniform across database engines. For production code, confirm function names, transaction semantics, constraint enforcement, indexing behavior, and procedural syntax in the documentation for your specific database.
