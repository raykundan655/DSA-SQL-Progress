# SQL Notes: Set Operators, Conditional Logic, and NULL Handling

> **Purpose:** Complete, practical notes on three related SQL topics: set operators, conditional logic with `CASE`, and handling `NULL`.
>
> **Dialect note:** Core concepts are shared by PostgreSQL, MySQL, SQL Server, Oracle, and SQLite, but some syntax and supported operators differ. Dialect-specific differences are called out where important.

---

# 1. Set Operators

## 1.1 What are set operators?

Set operators combine the results of two or more `SELECT` queries into one result set. They combine **rows from query results**, not columns from tables.

The main set operators are:

| Operator | Purpose | Removes duplicate rows? |
|---|---|---|
| `UNION` | Combines results from both queries | Yes |
| `UNION ALL` | Combines results from both queries | No |
| `INTERSECT` | Returns rows present in both results | Yes |
| `EXCEPT` | Returns rows from the first result that are absent from the second | Yes |
| `MINUS` | Oracle's equivalent of `EXCEPT` | Yes |

`INTERSECT` and `EXCEPT`/`MINUS` are not supported by every database/version. Check the SQL dialect in use.

## 1.2 Rules for combining queries

For set operators to work, the participating `SELECT` statements must generally meet these requirements:

1. **Same number of columns:** Every query must return the same number of columns.
2. **Compatible data types:** Corresponding columns must have compatible types. Databases may apply implicit type conversion, but explicit `CAST` is safer when types differ.
3. **Same column order:** The first column in one query is combined with the first column in the other query, and so on. Column names do not control matching.
4. **Final column names:** The output column names usually come from the first `SELECT`.
5. **Ordering:** An `ORDER BY` normally belongs at the end of the combined query and sorts the final result.
6. **Duplicate behavior:** Whether duplicates remain depends on the operator.
7. **Column aliases:** Aliases from the first query generally determine output names; aliases in later queries do not rename the combined output.

Example tables:

`current_customers`

| customer_id | customer_name |
|---:|---|
| 1 | Asha |
| 2 | Ravi |
| 3 | Neha |

`event_customers`

| customer_id | customer_name |
|---:|---|
| 2 | Ravi |
| 3 | Neha |
| 4 | Imran |

## 1.3 `UNION`

`UNION` combines rows from both query results and removes duplicate result rows.

```sql
SELECT customer_id, customer_name
FROM current_customers

UNION

SELECT customer_id, customer_name
FROM event_customers;
```

Conceptual result:

| customer_id | customer_name |
|---:|---|
| 1 | Asha |
| 2 | Ravi |
| 3 | Neha |
| 4 | Imran |

The rows for Ravi and Neha occur in both inputs but appear only once in the result.

### Important details

- Duplicate elimination applies to the **entire output row**, not just one selected column.
- Two rows are duplicates for set-operation purposes when all corresponding output values match under the database's comparison rules.
- `UNION` often requires extra work to remove duplicates, such as sorting or hashing.
- Do not rely on the output order unless you use `ORDER BY`.

Example showing full-row duplicate behavior:

```sql
SELECT 1 AS id, 'Asha' AS name
UNION
SELECT 1 AS id, 'Asha' AS name;
```

Returns one row.

But:

```sql
SELECT 1 AS id, 'Asha' AS name
UNION
SELECT 1 AS id, 'Asha Sharma' AS name;
```

Returns two rows because the complete rows differ.

## 1.4 `UNION ALL`

`UNION ALL` combines the rows and preserves duplicates.

```sql
SELECT customer_id, customer_name
FROM current_customers

UNION ALL

SELECT customer_id, customer_name
FROM event_customers;
```

Conceptual result contains six rows: Asha, Ravi, Neha, Ravi, Neha, and Imran.

### `UNION` versus `UNION ALL`

| Feature | `UNION` | `UNION ALL` |
|---|---|---|
| Combines result sets | Yes | Yes |
| Removes duplicate rows | Yes | No |
| Usually faster for large results | Often slower | Often faster |
| Keeps repeated rows | No | Yes |
| Best use | Unique combined list | Preserve every row/occurrence |

**Rule of thumb:** Use `UNION ALL` when duplicates are meaningful or are known not to exist. Use `UNION` when the requirement is to return distinct combined rows.

Do not choose `UNION` automatically just because it is familiar; removing duplicates can be unnecessary work and can change the meaning of the data.

## 1.5 `INTERSECT`

`INTERSECT` returns distinct rows that appear in **both** query results.

```sql
SELECT customer_id, customer_name
FROM current_customers

INTERSECT

SELECT customer_id, customer_name
FROM event_customers;
```

Result:

| customer_id | customer_name |
|---:|---|
| 2 | Ravi |
| 3 | Neha |

### Important details

- The output includes rows common to both inputs.
- The result is distinct; repeated copies do not appear multiple times with the ordinary `INTERSECT` operator.
- `INTERSECT` is useful for finding overlap between groups, lists, or query results.
- Availability varies by database/version.

Some databases support `INTERSECT ALL`, which preserves multiplicity according to that database's set-operation rules. Do not assume it is available everywhere.

## 1.6 `EXCEPT` and `MINUS`

`EXCEPT` returns distinct rows that appear in the first query but not in the second.

```sql
SELECT customer_id, customer_name
FROM current_customers

EXCEPT

SELECT customer_id, customer_name
FROM event_customers;
```

Result:

| customer_id | customer_name |
|---:|---|
| 1 | Asha |

The direction matters: `A EXCEPT B` is not the same as `B EXCEPT A`.

Oracle uses `MINUS` for this operation in the commonly used Oracle syntax:

```sql
SELECT customer_id, customer_name
FROM current_customers

MINUS

SELECT customer_id, customer_name
FROM event_customers;
```

### Example: customers found only in the event list

```sql
SELECT customer_id, customer_name
FROM event_customers

EXCEPT

SELECT customer_id, customer_name
FROM current_customers;
```

This returns Imran.

### Important details

- `EXCEPT`/`MINUS` is directional.
- The ordinary operator returns distinct rows.
- Use it to find rows in one result that are missing from another result.
- Check database support and syntax before using it in portable SQL.

## 1.7 `NULL` values in set operations

Set operations compare whole rows. For duplicate elimination and set membership, SQL set operations generally treat corresponding `NULL` values as **not distinct** for this purpose, even though the predicate `NULL = NULL` does not evaluate to `TRUE`.

For example:

```sql
SELECT NULL AS value
UNION
SELECT NULL AS value;
```

The ordinary `UNION` result contains one row with `NULL`.

This is a special set-operation comparison rule; it does **not** mean that `NULL = NULL` is true in a normal `WHERE` condition.

## 1.8 Combining more than two queries

You can combine several query results:

```sql
SELECT email FROM customers_2024
UNION
SELECT email FROM customers_2025
UNION
SELECT email FROM customers_2026;
```

Use parentheses when you need to make grouping explicit, especially when mixing different set operators. Precedence rules can differ between dialects; in many systems, `INTERSECT` binds more tightly than `UNION` and `EXCEPT`, but verify your database's rules.

Example with explicit grouping:

```sql
(
    SELECT product_id FROM warehouse_a
    UNION
    SELECT product_id FROM warehouse_b
)
EXCEPT
SELECT product_id FROM discontinued_products;
```

This means: combine the product IDs from warehouses A and B, then remove IDs found in the discontinued-products result. Exact parenthesis support around compound queries varies by database.

## 1.9 `ORDER BY` with set operators

To sort the final result, place `ORDER BY` at the end:

```sql
SELECT customer_id, customer_name
FROM current_customers

UNION

SELECT customer_id, customer_name
FROM event_customers

ORDER BY customer_name;
```

This sorts the combined result. A branch-level `ORDER BY` is often disallowed or ignored unless used with a supported subquery/limiting construct. If each branch needs its own ordering for `LIMIT`/`TOP`/`FETCH`, use the syntax appropriate to the database and parenthesize the subquery where required.

## 1.10 Set operators versus joins

| Set operators | Joins |
|---|---|
| Combine rows vertically | Combine columns horizontally |
| Inputs need the same number of compatible columns | Inputs are matched using a join condition or a join type |
| `UNION` can remove duplicate full rows | A join can produce multiple matching combinations |
| Useful for merging similar lists | Useful for relating entities, such as customers and orders |

Example:
- Use `UNION ALL` to append this year's sales rows to last year's sales rows.
- Use a `JOIN` to show each sale together with the customer's name from another table.

## 1.11 Common mistakes with set operators

1. Returning a different number of columns in each query.
2. Using incompatible data types in corresponding positions.
3. Assuming column names align the queries; they align by **position**.
4. Assuming `UNION ALL` removes duplicates.
5. Assuming the result has a guaranteed order without `ORDER BY`.
6. Forgetting that `EXCEPT`/`MINUS` is directional.
7. Assuming all database engines support `INTERSECT` or `EXCEPT`.
8. Using `UNION` when duplicate rows must be preserved.
9. Comparing only one column mentally when duplicate elimination checks the complete output row.
10. Placing `ORDER BY` in an unsupported position.

## 1.12 Set-operator quick revision

- `UNION` = combine + remove duplicate rows.
- `UNION ALL` = combine + preserve duplicates.
- `INTERSECT` = rows common to both.
- `EXCEPT` = rows in first result but not second.
- `MINUS` = Oracle's equivalent of `EXCEPT`.
- Queries must return the same number of columns with compatible types.
- Corresponding columns match by position, not by name.
- Use a final `ORDER BY` to sort the combined output.

---

# 2. Conditional Logic in SQL

## 2.1 What is conditional logic?

Conditional logic lets a query return different values depending on conditions. The main SQL expression for this is `CASE`.

`CASE` is an **expression**: it evaluates conditions and returns one value. It can be used in places where an expression is allowed, including:

- `SELECT`
- `ORDER BY`
- `GROUP BY` (subject to expression and dialect rules)
- `WHERE` (as part of a predicate or expression)
- `HAVING`
- `UPDATE ... SET`
- `INSERT ... VALUES`
- Window-function arguments and other expressions

## 2.2 Searched `CASE`

A searched `CASE` checks conditions one by one.

```sql
CASE
    WHEN condition_1 THEN result_1
    WHEN condition_2 THEN result_2
    WHEN condition_3 THEN result_3
    ELSE default_result
END
```

SQL evaluates the conditions in order and returns the result for the **first condition that is true**. If no condition is true, it returns the `ELSE` result. If `ELSE` is omitted and no condition is true, the result is `NULL`.

Example table `employees`:

| employee_id | employee_name | salary |
|---:|---|---:|
| 1 | Asha | 90000 |
| 2 | Ravi | 60000 |
| 3 | Neha | 35000 |
| 4 | Imran | NULL |

```sql
SELECT
    employee_name,
    salary,
    CASE
        WHEN salary >= 80000 THEN 'High'
        WHEN salary >= 50000 THEN 'Medium'
        WHEN salary IS NOT NULL THEN 'Low'
        ELSE 'Unknown'
    END AS salary_band
FROM employees;
```

Possible result:

| employee_name | salary | salary_band |
|---|---:|---|
| Asha | 90000 | High |
| Ravi | 60000 | Medium |
| Neha | 35000 | Low |
| Imran | NULL | Unknown |

### Why condition order matters

For a value of `90000`, both `salary >= 80000` and `salary >= 50000` are true. Since the first true branch wins, the result is `High`.

Incorrect ordering can make a more specific branch unreachable:

```sql
CASE
    WHEN salary >= 50000 THEN 'Medium or High'
    WHEN salary >= 80000 THEN 'High'
    ELSE 'Low'
END
```

The second branch never handles salaries of 80000 or more because the first condition already matches them.

**Best practice:** Put the most specific or highest-priority conditions first, and check boundary values carefully.

## 2.3 Simple `CASE`

A simple `CASE` compares one expression with a list of values.

```sql
CASE expression
    WHEN value_1 THEN result_1
    WHEN value_2 THEN result_2
    ELSE default_result
END
```

Example:

```sql
SELECT
    order_id,
    status_code,
    CASE status_code
        WHEN 'P' THEN 'Pending'
        WHEN 'S' THEN 'Shipped'
        WHEN 'D' THEN 'Delivered'
        WHEN 'C' THEN 'Cancelled'
        ELSE 'Unknown status'
    END AS status_description
FROM orders;
```

This is concise when matching one expression against specific values.

### Simple versus searched `CASE`

| Simple `CASE` | Searched `CASE` |
|---|---|
| Compares one expression with listed values | Evaluates independent conditions |
| Convenient for equality-style mappings | Supports ranges, comparisons, `LIKE`, `IN`, `IS NULL`, and compound conditions |
| `CASE status WHEN 'P' ...` | `CASE WHEN salary >= 50000 ...` |

A simple `CASE` is not a safe way to test for `NULL`:

```sql
CASE salary
    WHEN NULL THEN 'Missing'
    ELSE 'Present'
END
```

This does not match a `NULL` salary because `NULL` is not matched using ordinary equality semantics. Use a searched `CASE`:

```sql
CASE
    WHEN salary IS NULL THEN 'Missing'
    ELSE 'Present'
END
```

## 2.4 `CASE` without `ELSE`

If no `WHEN` condition is true and there is no `ELSE`, the expression returns `NULL`.

```sql
SELECT
    employee_name,
    CASE
        WHEN salary >= 80000 THEN 'High'
        WHEN salary >= 50000 THEN 'Medium'
    END AS salary_band
FROM employees;
```

Employees below 50000 and employees with a `NULL` salary receive `NULL` for `salary_band`.

Include an `ELSE` when you want an explicit fallback value.

## 2.5 `CASE` in `SELECT`

Use `CASE` to create derived labels or values without changing the stored data.

```sql
SELECT
    product_name,
    price,
    CASE
        WHEN price >= 1000 THEN 'Premium'
        WHEN price >= 500 THEN 'Standard'
        ELSE 'Budget'
    END AS price_category
FROM products;
```

The category is calculated in the query; it does not update the `products` table.

## 2.6 Conditional filtering in `WHERE`

You can use `CASE` inside a `WHERE` expression, but direct Boolean logic is often clearer.

Example using a `CASE` expression:

```sql
SELECT *
FROM employees
WHERE
    CASE
        WHEN department = 'Sales' AND salary >= 50000 THEN 1
        WHEN department = 'Engineering' AND salary >= 70000 THEN 1
        ELSE 0
    END = 1;
```

Often clearer:

```sql
SELECT *
FROM employees
WHERE
    (department = 'Sales' AND salary >= 50000)
    OR
    (department = 'Engineering' AND salary >= 70000);
```

Use `CASE` when it genuinely expresses a value choice; use normal predicates when you are simply filtering rows.

## 2.7 Conditional sorting with `ORDER BY`

`CASE` can define a custom order:

```sql
SELECT order_id, status
FROM orders
ORDER BY
    CASE status
        WHEN 'Pending' THEN 1
        WHEN 'Processing' THEN 2
        WHEN 'Shipped' THEN 3
        WHEN 'Delivered' THEN 4
        ELSE 5
    END,
    order_id;
```

This sorts statuses in the business-defined order rather than alphabetically.

You can also sort conditionally by different columns:

```sql
SELECT *
FROM products
ORDER BY
    CASE WHEN category = 'Electronics' THEN price END DESC,
    CASE WHEN category <> 'Electronics' THEN product_name END ASC;
```

For complex sorting, make the intended handling of `NULL` values explicit and check the dialect's default `NULL` ordering.

## 2.8 Conditional aggregation

Conditional aggregation is a common and powerful pattern. Use `CASE` inside aggregate functions to count or sum only rows that meet a condition.

### Count rows matching a condition

```sql
SELECT
    COUNT(*) AS total_employees,
    SUM(CASE WHEN department = 'Sales' THEN 1 ELSE 0 END) AS sales_employees,
    SUM(CASE WHEN department = 'Engineering' THEN 1 ELSE 0 END) AS engineering_employees
FROM employees;
```

Because each row contributes either `1` or `0`, `SUM` produces the conditional count.

Some databases support a `FILTER (WHERE ...)` clause for aggregates, but `CASE` is more widely portable.

### Count non-NULL values meeting a condition

```sql
SELECT
    COUNT(CASE WHEN status = 'Delivered' THEN order_id END) AS delivered_orders
FROM orders;
```

`COUNT(expression)` ignores `NULL`, so only matching rows with a non-`NULL` `order_id` are counted. If `order_id` is guaranteed non-`NULL`, this counts delivered orders.

### Conditional sum

```sql
SELECT
    SUM(CASE WHEN status = 'Paid' THEN amount ELSE 0 END) AS paid_amount
FROM payments;
```

This sums `amount` for paid rows and contributes zero for other statuses. Consider how `NULL` amounts should be treated before relying on the result.

### Conditional average

```sql
SELECT
    AVG(CASE WHEN department = 'Sales' THEN salary END) AS avg_sales_salary
FROM employees;
```

Rows that do not meet the condition return `NULL`; `AVG` ignores those `NULL` results. It also ignores a `NULL` salary within the Sales group.

### Conditional aggregation by group

```sql
SELECT
    department,
    SUM(CASE WHEN performance_rating = 'Excellent' THEN 1 ELSE 0 END) AS excellent_count,
    COUNT(*) AS employee_count
FROM employees
GROUP BY department;
```

This returns the total employees and the number rated Excellent for each department.

## 2.9 Conditional updates

`CASE` can assign values based on each row's current data:

```sql
UPDATE products
SET price =
    CASE
        WHEN category = 'Clearance' THEN price * 0.80
        WHEN category = 'Seasonal' THEN price * 0.90
        ELSE price
    END;
```

This updates every row because there is no `WHERE` clause. Add a `WHERE` clause if only some rows should change.

Example:

```sql
UPDATE products
SET price =
    CASE
        WHEN category = 'Clearance' THEN price * 0.80
        ELSE price
    END
WHERE category IN ('Clearance', 'Seasonal');
```

Notice that the `WHERE` condition includes Seasonal, but the `CASE` leaves Seasonal prices unchanged. That may be intentional, but the filter and branches should match the business requirement.

**Safety rule:** Before a bulk `UPDATE`, run a matching `SELECT` to inspect which rows and values will be affected, and use a transaction where appropriate.

## 2.10 `CASE` and data types

All result branches of a `CASE` should return compatible data types. The database determines a common result type using its type-resolution rules.

Potentially problematic:

```sql
CASE
    WHEN is_active = 1 THEN 'Active'
    ELSE 0
END
```

One branch returns text and another returns a number. Some databases reject this; others may apply type-conversion rules that produce surprising behavior.

Prefer consistent result types:

```sql
CASE
    WHEN is_active = 1 THEN 'Active'
    ELSE 'Inactive'
END
```

Or, if the result should be numeric:

```sql
CASE
    WHEN is_active = 1 THEN 1
    ELSE 0
END
```

Use explicit `CAST` when you need a particular result type.

## 2.11 Short-circuit evaluation: do not depend on it blindly

SQL optimizers can transform expressions, and evaluation order is not always guaranteed for every expression in every context. Do not assume a `CASE` condition will always protect an unsafe expression in all database engines or query plans.

For division, prefer a safe expression such as `numerator / NULLIF(denominator, 0)` when supported, rather than depending solely on a branch to avoid division by zero.

Example:

```sql
SELECT
    numerator / NULLIF(denominator, 0) AS ratio
FROM measurements;
```

If `denominator` is zero, `NULLIF` returns `NULL`, so the division yields `NULL` instead of dividing by zero. Data types and integer-division behavior still matter.

## 2.12 `CASE` versus `COALESCE` and `NULLIF`

- `CASE` handles general conditions and can return different results for many cases.
- `COALESCE(a, b, c)` returns the first non-`NULL` argument.
- `NULLIF(a, b)` returns `NULL` if `a` equals `b`; otherwise it returns `a`.

Examples:

```sql
CASE WHEN commission IS NULL THEN 0 ELSE commission END
```

Equivalent for this simple null-defaulting case:

```sql
COALESCE(commission, 0)
```

Safe denominator:

```sql
revenue / NULLIF(units_sold, 0)
```

Use the function that best expresses the intent; `COALESCE` is usually simpler for choosing a fallback when a value is `NULL`.

## 2.13 Common `CASE` mistakes

1. Forgetting `END`.
2. Using `=` to test for `NULL` instead of `IS NULL`.
3. Putting a broad condition before a more specific one.
4. Omitting `ELSE` and unintentionally returning `NULL`.
5. Returning incompatible data types in different branches.
6. Assuming `CASE` changes stored values when used only in a `SELECT`.
7. Forgetting that conditional aggregation may ignore `NULL` results.
8. Using `COUNT(CASE ... THEN 1 END)` without understanding that `COUNT` ignores `NULL`.
9. Using `CASE` for simple filtering when ordinary `AND`/`OR` conditions would be clearer.
10. Updating all rows unintentionally because an `UPDATE` has no `WHERE` clause.
11. Depending on expression evaluation order to avoid errors.

## 2.14 Conditional-logic quick revision

- `CASE` returns a value; it is not a procedural `IF` statement.
- Searched `CASE` uses conditions: `CASE WHEN condition THEN result ... END`.
- Simple `CASE` compares one expression with listed values.
- The first true `WHEN` branch wins.
- Without `ELSE`, an unmatched `CASE` returns `NULL`.
- Use `IS NULL` to test for missing values.
- `CASE` works well with `ORDER BY`, `UPDATE`, and aggregate functions.
- Keep branch result types compatible.

---

# 3. NULL Handling

## 3.1 What is `NULL`?

`NULL` represents missing, unknown, or unavailable information. It does **not** mean the same thing as:

- `0`
- An empty string (`''`)
- A blank space (`' '`)
- `FALSE`
- The text `'NULL'`

The exact meaning of a `NULL` value depends on the column and application. For example, a `NULL` in `delivery_date` may mean the delivery date is not known or has not been recorded; it does not automatically mean the order was never delivered.

Example table:

`employees`

| employee_id | employee_name | bonus |
|---:|---|---:|
| 1 | Asha | 5000 |
| 2 | Ravi | NULL |
| 3 | Neha | 0 |

Here:
- Asha has a bonus of 5000.
- Ravi's bonus is unknown or missing.
- Neha's bonus is explicitly 0.

`NULL` and `0` must not be treated as interchangeable.

## 3.2 Why `NULL` requires special handling

Ordinary comparison operators (`=`, `<>`, `<`, `>`, etc.) cannot determine whether an unknown value equals or differs from another value. Comparisons involving `NULL` generally produce `UNKNOWN`.

For example:

```sql
SELECT *
FROM employees
WHERE bonus = NULL;
```

This is incorrect for finding missing bonuses. Use:

```sql
SELECT *
FROM employees
WHERE bonus IS NULL;
```

To find known bonuses:

```sql
SELECT *
FROM employees
WHERE bonus IS NOT NULL;
```

## 3.3 Three-valued logic: TRUE, FALSE, UNKNOWN

SQL conditions can evaluate to three logical states:

- `TRUE`
- `FALSE`
- `UNKNOWN`

A comparison involving `NULL` commonly produces `UNKNOWN`.

| Expression | Result |
|---|---|
| `5 = 5` | TRUE |
| `5 = 8` | FALSE |
| `NULL = 5` | UNKNOWN |
| `NULL = NULL` | UNKNOWN |
| `NULL <> 5` | UNKNOWN |

In a `WHERE` clause, only rows whose condition is `TRUE` are retained. Rows where the condition is `FALSE` or `UNKNOWN` are filtered out.

Example:

```sql
SELECT *
FROM employees
WHERE bonus <> 0;
```

This does **not** return employees whose bonus is `NULL`. For those rows, `bonus <> 0` is `UNKNOWN`, not `TRUE`.

If you want nonzero bonuses and also want to include unknown bonuses, state that explicitly:

```sql
SELECT *
FROM employees
WHERE bonus <> 0
   OR bonus IS NULL;
```

Whether that is correct depends on the business requirement.

## 3.4 `IS NULL` and `IS NOT NULL`

Use these predicates to test nullness:

```sql
-- Find rows with no recorded bonus
SELECT *
FROM employees
WHERE bonus IS NULL;

-- Find rows with a recorded bonus, including zero
SELECT *
FROM employees
WHERE bonus IS NOT NULL;
```

Do not write `bonus = NULL` or `bonus <> NULL`.

### Checking more than one nullable column

```sql
SELECT *
FROM employees
WHERE bonus IS NULL
   OR manager_id IS NULL;
```

To require both values to be present:

```sql
SELECT *
FROM employees
WHERE bonus IS NOT NULL
  AND manager_id IS NOT NULL;
```

## 3.5 `NULL` and logical operators

Because SQL uses three-valued logic, `AND`, `OR`, and `NOT` can produce `UNKNOWN`.

### `AND`

| A | B | A AND B |
|---|---|---|
| TRUE | TRUE | TRUE |
| TRUE | FALSE | FALSE |
| TRUE | UNKNOWN | UNKNOWN |
| FALSE | UNKNOWN | FALSE |
| UNKNOWN | UNKNOWN | UNKNOWN |

A single `FALSE` makes `A AND B` false, even if the other side is unknown.

### `OR`

| A | B | A OR B |
|---|---|---|
| TRUE | UNKNOWN | TRUE |
| FALSE | UNKNOWN | UNKNOWN |
| FALSE | FALSE | FALSE |
| UNKNOWN | UNKNOWN | UNKNOWN |

A single `TRUE` makes `A OR B` true, even if the other side is unknown.

### `NOT`

| A | NOT A |
|---|---|
| TRUE | FALSE |
| FALSE | TRUE |
| UNKNOWN | UNKNOWN |

A common surprise:

```sql
WHERE NOT (bonus = 0)
```

This does not include `NULL` bonuses. If `bonus = 0` is `UNKNOWN`, then `NOT UNKNOWN` is still `UNKNOWN`, so the row is filtered out.

## 3.6 `NULL` in arithmetic

Arithmetic expressions involving `NULL` usually produce `NULL`.

```sql
SELECT 100 + NULL AS result;
```

The result is `NULL`.

Examples:

```sql
salary + bonus
quantity * unit_price
revenue / cost
```

If an operand is `NULL`, the resulting arithmetic expression is generally `NULL`. Decide whether a missing value should be treated as zero before using a fallback; do not assume that missing data means zero.

Example where the business rule says a missing bonus should count as zero:

```sql
SELECT
    employee_name,
    salary + COALESCE(bonus, 0) AS total_compensation
FROM employees;
```

This is appropriate only if the business meaning of a missing bonus is equivalent to zero for this calculation.

## 3.7 `NULL` in string concatenation

String concatenation behavior differs by database and operator:

- In PostgreSQL, `text1 || text2` generally returns `NULL` if either input is `NULL`.
- In SQL Server, `CONCAT()` treats `NULL` inputs as empty strings; the `+` operator's behavior depends on SQL Server settings/version and should not be assumed.
- MySQL's `CONCAT()` returns `NULL` if any argument is `NULL`; `CONCAT_WS()` skips `NULL` values.
- Oracle has special behavior for zero-length character strings and concatenation.

If you want a fallback, state it explicitly:

```sql
SELECT
    COALESCE(first_name, '') || ' ' || COALESCE(last_name, '') AS full_name
FROM people;
```

This `||` syntax is not universal. For portable or dialect-specific code, use the concatenation function/operator supported by the target database. For example, `CONCAT(...)` is available in several major engines, but its `NULL` behavior differs by engine.

## 3.8 `NULL` in aggregates

Aggregate functions do not all treat `NULL` the same way. Most common aggregates ignore `NULL` inputs, but `COUNT(*)` counts rows regardless of whether any column is `NULL`.

Assume the values are `10`, `20`, `NULL`, and `0`.

| Expression | Result | Explanation |
|---|---:|---|
| `COUNT(*)` over four rows | 4 | Counts every row |
| `COUNT(value)` | 3 | Counts non-`NULL` values, including zero |
| `SUM(value)` | 30 | Adds known non-`NULL` values |
| `AVG(value)` | 10 | `(10 + 20 + 0) / 3`; ignores `NULL` |
| `MIN(value)` | 0 | Ignores `NULL` |
| `MAX(value)` | 20 | Ignores `NULL` |

### `COUNT(*)` versus `COUNT(column)`

```sql
SELECT
    COUNT(*) AS total_rows,
    COUNT(bonus) AS rows_with_known_bonus
FROM employees;
```

- `COUNT(*)` counts every row.
- `COUNT(bonus)` counts rows where `bonus` is not `NULL`.
- A value of `0` is counted by `COUNT(bonus)` because zero is not `NULL`.

### Aggregates when every input is `NULL`

For a nonempty input group whose values are all `NULL`, common SQL behavior is:

- `COUNT(column)` returns `0`.
- `SUM(column)`, `AVG(column)`, `MIN(column)`, and `MAX(column)` return `NULL`.

If there are no input rows at all, aggregate output behavior depends on the query shape and database; for a plain aggregate query without `GROUP BY`, `COUNT(*)` normally returns 0 while other aggregates commonly return `NULL`.

### Replacing a `NULL` aggregate result

```sql
SELECT COALESCE(SUM(bonus), 0) AS total_bonus
FROM employees;
```

This displays zero when `SUM(bonus)` is `NULL`. Make sure zero is the correct business interpretation for an unknown or empty total.

Be careful with:

```sql
AVG(COALESCE(bonus, 0))
```

This treats each missing bonus as zero and includes it in the average. That is not the same as `AVG(bonus)`, which ignores missing bonuses.

## 3.9 `COALESCE`

`COALESCE` returns the first non-`NULL` argument.

```sql
COALESCE(expression_1, expression_2, expression_3, ...)
```

Example:

```sql
SELECT
    employee_name,
    COALESCE(bonus, 0) AS bonus_for_report
FROM employees;
```

If `bonus` is `NULL`, the output is `0`; otherwise, it is the bonus value.

### Multiple fallbacks

```sql
SELECT
    COALESCE(preferred_phone, mobile_phone, office_phone, 'No phone') AS contact_number
FROM contacts;
```

The first non-`NULL` value is returned.

### Important details

- `COALESCE` is part of standard SQL and is supported by major databases.
- Arguments must have types that the database can resolve to a common compatible result type.
- The result is `NULL` only if all arguments are `NULL`.
- Use it when a fallback value is appropriate, not simply to hide data-quality problems.

## 3.10 `NULLIF`

`NULLIF(a, b)` returns `NULL` if `a = b`; otherwise, it returns `a`.

```sql
NULLIF(expression_1, expression_2)
```

Examples:

```sql
SELECT NULLIF(10, 10);  -- NULL
SELECT NULLIF(10, 5);   -- 10
```

### Preventing division by zero

```sql
SELECT
    revenue / NULLIF(units_sold, 0) AS revenue_per_unit
FROM sales;
```

If `units_sold` is zero, `NULLIF(units_sold, 0)` returns `NULL`, avoiding division by zero in engines that support the expected arithmetic behavior. The result becomes `NULL`.

This protects against zero denominators, but it does not decide how the business should interpret the missing ratio. You may want to display a label or apply a fallback separately.

### Converting a sentinel value to `NULL`

```sql
SELECT NULLIF(phone_number, '') AS phone_number
FROM contacts;
```

This converts an empty string to `NULL` in engines where `''` is distinct from `NULL`. **Oracle treats a zero-length character string as `NULL`**, so behavior differs there.

## 3.11 `CASE` for explicit `NULL` handling

Use searched `CASE` to label or transform missing values:

```sql
SELECT
    employee_name,
    CASE
        WHEN bonus IS NULL THEN 'Not recorded'
        WHEN bonus = 0 THEN 'Zero bonus'
        ELSE 'Bonus recorded'
    END AS bonus_status
FROM employees;
```

Order is important because `bonus IS NULL` must be checked with `IS NULL`, not equality.

`CASE` is also useful when different fallback rules depend on more than nullness:

```sql
SELECT
    employee_name,
    CASE
        WHEN bonus IS NULL AND employment_status = 'Active'
            THEN 'Active - bonus not recorded'
        WHEN bonus IS NULL
            THEN 'Bonus not recorded'
        WHEN bonus = 0
            THEN 'No bonus'
        ELSE 'Bonus available'
    END AS bonus_status
FROM employees;
```

## 3.12 `NULL` in joins

`NULL` values affect join conditions because `NULL = NULL` is `UNKNOWN`, not `TRUE`.

Example:

```sql
SELECT *
FROM employees e
JOIN departments d
    ON e.department_id = d.department_id;
```

If an employee's `department_id` is `NULL`, that row does not match a department through this equality condition.

### Inner join

An `INNER JOIN` returns rows where the join condition is true. Rows with a `NULL` join key normally do not match using `=`.

### Left join

A `LEFT JOIN` preserves every row from the left table. If there is no matching row on the right, right-side columns are returned as `NULL`. Those output `NULL`s can mean “no matching row,” not necessarily that the stored right-side value was missing.

Example: find employees with no matching department:

```sql
SELECT e.employee_id, e.employee_name
FROM employees e
LEFT JOIN departments d
    ON e.department_id = d.department_id
WHERE d.department_id IS NULL;
```

This is a common anti-join pattern when `d.department_id` is guaranteed non-`NULL` for real matched department rows, such as when it is a primary key.

### Null-safe equality

Some databases provide null-safe equality operators, but syntax differs:
- PostgreSQL: `IS NOT DISTINCT FROM`
- MySQL: `<=>`
- SQL Server: no directly identical general operator; use explicit logic such as `(a = b OR (a IS NULL AND b IS NULL))` where appropriate.

Example in PostgreSQL:

```sql
ON a.key IS NOT DISTINCT FROM b.key
```

This treats two `NULL` values as matching. Use null-safe matching only when the business rule explicitly says that two missing keys should match; this is not automatically correct for every join.

## 3.13 `NULL` in `IN` and `NOT IN`

`IN` and especially `NOT IN` can produce surprising results when the list or subquery contains `NULL`.

Example:

```sql
SELECT *
FROM employees
WHERE department_id IN (10, 20, NULL);
```

Rows with department IDs 10 or 20 match. A row with another ID may evaluate to `UNKNOWN` because the list contains `NULL`; a row with a `NULL` department ID also does not match.

### The `NOT IN` trap

```sql
SELECT *
FROM employees
WHERE department_id NOT IN (
    SELECT department_id
    FROM blocked_departments
);
```

If the subquery returns even one `NULL`, comparisons can become `UNKNOWN`, and the query may return no rows that you expected to qualify.

A common safer pattern is `NOT EXISTS`:

```sql
SELECT e.*
FROM employees e
WHERE NOT EXISTS (
    SELECT 1
    FROM blocked_departments b
    WHERE b.department_id = e.department_id
);
```

However, if `e.department_id` itself is `NULL`, the equality inside the subquery is not true, so that employee can pass `NOT EXISTS`. Decide explicitly whether rows with a `NULL` key should be included or excluded.

To exclude missing keys as well:

```sql
SELECT e.*
FROM employees e
WHERE e.department_id IS NOT NULL
  AND NOT EXISTS (
      SELECT 1
      FROM blocked_departments b
      WHERE b.department_id = e.department_id
  );
```

`NOT EXISTS` avoids the specific problem of a `NULL` in the subquery result, but the intended treatment of `NULL` keys still needs to be specified.

## 3.14 `NULL` in `GROUP BY` and `DISTINCT`

For grouping and duplicate elimination, SQL generally places rows with `NULL` in the same grouping category for a given column.

Example:

```sql
SELECT department_id, COUNT(*) AS employee_count
FROM employees
GROUP BY department_id;
```

Employees whose `department_id` is `NULL` are typically grouped together into one `NULL` group.

Likewise:

```sql
SELECT DISTINCT department_id
FROM employees;
```

Typically returns one `NULL` entry if any rows have a `NULL` department ID.

This does not mean that the predicate `NULL = NULL` is true. Grouping and duplicate elimination use their own rules for treating values as not distinct.

## 3.15 `NULL` in sorting

The position of `NULL` values in an `ORDER BY` can differ between database systems and sort directions.

Some systems support explicit syntax:

```sql
SELECT employee_name, bonus
FROM employees
ORDER BY bonus ASC NULLS LAST;
```

`NULLS FIRST`/`NULLS LAST` support and defaults vary by dialect. SQL Server does not support the same `NULLS FIRST`/`NULLS LAST` syntax as PostgreSQL and Oracle. A portable approach is a `CASE` sort key:

```sql
SELECT employee_name, bonus
FROM employees
ORDER BY
    CASE WHEN bonus IS NULL THEN 1 ELSE 0 END,
    bonus ASC;
```

This places non-`NULL` bonuses first and `NULL` bonuses last in ascending order.

## 3.16 `NULL` in constraints and keys

### `NOT NULL`

A `NOT NULL` constraint prevents a column from storing `NULL`.

```sql
CREATE TABLE employees (
    employee_id INT PRIMARY KEY,
    employee_name VARCHAR(100) NOT NULL,
    bonus DECIMAL(10, 2) NULL
);
```

The explicit `NULL` keyword is optional in many dialects; `bonus` is nullable unless a constraint says otherwise.

### `UNIQUE`

`UNIQUE` constraints and `NULL` values have database-specific behavior. Some systems allow multiple `NULL` values in a unique column; others differ, and options may exist. Do not assume identical behavior across databases.

### Primary keys

A primary key must uniquely identify rows and cannot contain `NULL`. A primary key is effectively both unique and non-null.

### Foreign keys

Foreign-key columns may be nullable unless declared `NOT NULL`. A `NULL` foreign-key value generally does not have to match a referenced row under ordinary foreign-key rules; this can represent an optional relationship.

## 3.17 Empty string versus `NULL`

An empty string is a string with zero characters; `NULL` represents missing/unknown information. They are not equivalent in many databases.

```sql
SELECT *
FROM contacts
WHERE phone_number = '';
```

This checks for an empty string in systems where empty strings are distinct from `NULL`. It does not find `NULL` values; use `IS NULL` for those.

Oracle treats zero-length character strings as `NULL`, so the distinction is not preserved for ordinary character data there.

A string containing spaces (`'   '`) is not necessarily the same as an empty string or `NULL`. If the business rules require trimming or normalizing values, do that explicitly.

## 3.18 Replacing `NULL` in query output versus changing stored data

This query changes only the displayed result:

```sql
SELECT COALESCE(bonus, 0) AS bonus
FROM employees;
```

It does **not** update the table.

This query changes stored data:

```sql
UPDATE employees
SET bonus = 0
WHERE bonus IS NULL;
```

These have very different consequences. Do not replace stored `NULL`s with zero unless the business definition says zero is correct. You may lose the distinction between “known to be zero” and “not recorded.”

## 3.19 Common `NULL` mistakes

1. Using `= NULL` or `<> NULL` instead of `IS NULL`/`IS NOT NULL`.
2. Assuming `NULL = NULL` is true.
3. Assuming `NOT (column = value)` includes `NULL` rows.
4. Treating `NULL` as zero, false, or an empty string.
5. Forgetting that `WHERE` keeps only `TRUE`, not `FALSE` or `UNKNOWN`.
6. Assuming `COUNT(column)` counts `NULL` values.
7. Assuming `AVG(COALESCE(column, 0))` is the same as `AVG(column)`.
8. Using `NOT IN` with a subquery that may return `NULL`.
9. Assuming `NULL` join keys match one another through `=`.
10. Assuming all databases sort `NULL` values the same way.
11. Assuming unique constraints treat `NULL` the same way in every database.
12. Replacing stored `NULL` values with zero without confirming the business meaning.
13. Assuming an empty string is always distinct from `NULL`.
14. Assuming a `NULL` after a `LEFT JOIN` must have been stored as `NULL` in the original table.

## 3.20 NULL-handling quick revision

- `NULL` means missing, unknown, or unavailable; it is not automatically zero.
- Use `IS NULL` and `IS NOT NULL`.
- Comparisons involving `NULL` generally return `UNKNOWN`.
- `WHERE` retains only rows for which the condition is `TRUE`.
- Arithmetic with `NULL` generally returns `NULL`.
- `COUNT(*)` counts rows; `COUNT(column)` counts non-`NULL` values.
- Most common aggregates ignore `NULL` inputs.
- `COALESCE` returns the first non-`NULL` argument.
- `NULLIF(a, b)` returns `NULL` when `a = b`.
- `NOT IN` can behave unexpectedly if its list/subquery contains `NULL`; consider `NOT EXISTS`.
- `NULL` join keys normally do not match through ordinary equality.
- Dialect differences matter for string concatenation, empty strings, sorting, unique constraints, and null-safe equality.

---

# 4. How the Three Topics Work Together

These topics often appear together in practical queries.

## 4.1 Combine datasets, label values, and handle missing data

```sql
SELECT
    customer_id,
    customer_name,
    CASE
        WHEN email IS NULL THEN 'Email missing'
        ELSE 'Email available'
    END AS email_status
FROM customers_2025

UNION ALL

SELECT
    customer_id,
    customer_name,
    CASE
        WHEN email IS NULL THEN 'Email missing'
        ELSE 'Email available'
    END AS email_status
FROM customers_2026;
```

This:
- Uses `UNION ALL` to append rows from two years while preserving duplicates.
- Uses `CASE` to label each email as missing or available.
- Uses `IS NULL` to test missing values correctly.

Both queries must return the same number of columns with compatible types in corresponding positions.

## 4.2 Compare two datasets and make missing values explicit

Find customer IDs present in one dataset but not the other:

```sql
SELECT customer_id
FROM customers_2025

EXCEPT

SELECT customer_id
FROM customers_2026;
```

If the database does not support `EXCEPT`, use an anti-join pattern or the dialect's equivalent. Be explicit about how `NULL` customer IDs should be treated; ordinary equality-based joins do not match `NULL` to `NULL`.

## 4.3 Conditional count with a safe fallback

```sql
SELECT
    department,
    COUNT(*) AS employee_count,
    SUM(CASE WHEN bonus IS NULL THEN 1 ELSE 0 END) AS missing_bonus_count,
    COALESCE(SUM(bonus), 0) AS recorded_bonus_total
FROM employees
GROUP BY department;
```

This query:
- Counts all employees in each department.
- Counts rows with missing bonuses.
- Sums known bonuses and displays zero if the aggregate is `NULL`.

**Interpretation warning:** `recorded_bonus_total` is a total of recorded bonus values; it does not prove that missing bonuses were actually zero.

---

# 5. Practice Questions

Try to answer each question before looking at the solutions.

## Questions

1. What is the main difference between `UNION` and `UNION ALL`?
2. Why must queries combined with a set operator return the same number of columns?
3. Do set operators match columns by name or position?
4. What does `INTERSECT` return?
5. What is the difference between `A EXCEPT B` and `B EXCEPT A`?
6. What is the Oracle equivalent of `EXCEPT` in common Oracle syntax?
7. Does `UNION` remove duplicates based on one column or the complete selected row?
8. What happens if a `CASE` expression has no matching `WHEN` and no `ELSE`?
9. In a searched `CASE`, which matching branch is returned?
10. Why is `CASE salary WHEN NULL THEN ...` not the right way to test a `NULL` salary?
11. How can `CASE` be used to count rows matching a condition?
12. What is the difference between `COUNT(*)` and `COUNT(column)`?
13. What is SQL's third logical result besides `TRUE` and `FALSE`?
14. Why does `WHERE bonus <> 0` exclude rows with `bonus IS NULL`?
15. What does `COALESCE(a, b, c)` return?
16. What does `NULLIF(a, b)` return when `a = b`?
17. Why can `NOT IN (subquery)` be dangerous if the subquery returns `NULL`?
18. Do two `NULL` join keys match through `a.key = b.key`?
19. Is `AVG(COALESCE(score, 0))` always equivalent to `AVG(score)`?
20. Does `SELECT COALESCE(bonus, 0)` update the stored value?

## Answers

1. `UNION` removes duplicate result rows; `UNION ALL` preserves them.
2. A set operator combines corresponding columns into one output shape.
3. By position.
4. Distinct rows present in both query results.
5. `A EXCEPT B` returns rows in A but not B; reversing the operands reverses the comparison.
6. `MINUS`.
7. The complete selected row.
8. It returns `NULL`.
9. The first `WHEN` branch whose condition is true.
10. Equality comparisons involving `NULL` evaluate to `UNKNOWN`; use searched `CASE` with `WHEN salary IS NULL`.
11. For example, `SUM(CASE WHEN condition THEN 1 ELSE 0 END)`.
12. `COUNT(*)` counts rows; `COUNT(column)` counts non-`NULL` values in that column.
13. `UNKNOWN`.
14. `bonus <> 0` evaluates to `UNKNOWN` for a `NULL` bonus, and `WHERE` keeps only `TRUE`.
15. The first non-`NULL` argument, or `NULL` if all arguments are `NULL`.
16. `NULL`.
17. A `NULL` in the subquery can cause comparisons to evaluate to `UNKNOWN`, preventing expected rows from being returned.
18. No, ordinary equality with `NULL` is not true.
19. No. Replacing missing scores with zero changes the average's denominator and meaning.
20. No. It changes only the query output, not the stored table data.

---

# 6. Final Checklist

Before considering these topics complete, make sure you can:

- [ ] Explain `UNION`, `UNION ALL`, `INTERSECT`, and `EXCEPT`/`MINUS`.
- [ ] Check column count, column order, compatible types, and duplicate behavior in set operations.
- [ ] Use parentheses and a final `ORDER BY` appropriately.
- [ ] Write searched and simple `CASE` expressions.
- [ ] Explain branch order and the default `NULL` result when `ELSE` is omitted.
- [ ] Use `CASE` for conditional labels, sorting, aggregation, and updates.
- [ ] Explain `TRUE`, `FALSE`, and `UNKNOWN` in SQL.
- [ ] Test nullness with `IS NULL` and `IS NOT NULL`.
- [ ] Explain how `NULL` affects comparisons, arithmetic, aggregates, joins, `IN`/`NOT IN`, grouping, and sorting.
- [ ] Use `COALESCE` and `NULLIF` correctly.
- [ ] Explain why replacing `NULL` with zero can change a calculation's meaning.
- [ ] Identify dialect differences before relying on nonportable syntax.

**Recommended study order:** Set operators → `CASE` expressions → three-valued logic → `IS NULL` → aggregate behavior → `COALESCE`/`NULLIF` → `NULL` in joins and `NOT IN` → database-specific differences.
