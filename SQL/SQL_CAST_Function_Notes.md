# SQL `CAST()` Function — Complete Notes

## 1. What is `CAST()`?

`CAST()` converts a value from one data type to another data type.

Examples:
- Text `'123'` to integer `123`
- Number `123` to character data `'123'`
- A date-and-time value to a date, removing the time portion

**Important:** `CAST()` changes the data type of an expression in the query result. It does not permanently change the column's data type in the table.

## 2. Syntax

```sql
CAST(expression AS data_type)
```

- `expression`: the value or column to convert
- `data_type`: the target data type
- `AS`: separates the expression from the target type

Example:

```sql
SELECT CAST('123' AS INTEGER) AS number_value;
```

Result:

| number_value |
|---:|
| 123 |

The input `'123'` is text because it is inside quotes. `CAST()` converts it to an integer.

## 3. Converting Text to a Number

This is useful when numeric values are stored as text and you need to perform calculations.

### Text to integer

```sql
SELECT CAST('250' AS INTEGER) AS quantity;
```

Result: `250`

### Text to decimal

```sql
SELECT CAST('125.75' AS DECIMAL(10, 2)) AS price;
```

Result: `125.75`

`DECIMAL(10, 2)` means up to 10 digits in total, with 2 digits after the decimal point.

**Note:** Supported type names differ by database. MySQL also commonly uses `SIGNED` for signed integer conversions.

## 4. Converting a Number to Text

### Integer to text in MySQL

```sql
SELECT CAST(123 AS CHAR) AS text_value;
```

The displayed result is `123`, but its result type is character data.

### Decimal to text in MySQL

```sql
SELECT CAST(99.50 AS CHAR) AS price_text;
```

Result: `99.50`

**Can I use `TEXT` instead of `CHAR`?** It depends on the database. For MySQL, use `CHAR` as the target type in `CAST()` rather than `TEXT`. PostgreSQL supports `TEXT`; SQL Server commonly uses `VARCHAR(n)`.

## 5. Converting a Value to `DATE`

```sql
SELECT CAST('2026-10-26' AS DATE) AS order_date;
```

Result: `2026-10-26`

### Convert `DATETIME` to `DATE`

```sql
SELECT CAST('2026-10-26 18:45:30' AS DATE) AS order_date;
```

Result: `2026-10-26`

The time portion (`18:45:30`) is removed from the result.

## 6. Using `CAST()` with Table Columns

Suppose `orders` contains these values, and `amount_text` is a character column:

| order_id | amount_text |
|---:|---|
| 1 | 120.50 |
| 2 | 250.00 |
| 3 | 75.25 |

Convert each amount to decimal:

```sql
SELECT
    order_id,
    CAST(amount_text AS DECIMAL(10, 2)) AS amount
FROM orders;
```

Calculate the total:

```sql
SELECT
    SUM(CAST(amount_text AS DECIMAL(10, 2))) AS total_amount
FROM orders;
```

Result:

| total_amount |
|---:|
| 445.75 |

Each text value is converted to a decimal before `SUM()` calculates the total.

**Best practice:** If values represent money, store them in an appropriate numeric type such as `DECIMAL`, rather than storing them as text.

## 7. `CAST()` in `WHERE`

Suppose `year_text` stores years as text:

```sql
SELECT *
FROM records
WHERE CAST(year_text AS INTEGER) >= 2025;
```

This converts `year_text` to an integer before comparing it with `2025`.

**Caution:** Casting a column in a `WHERE` condition can affect index usage. Invalid text values may also cause errors or database-specific results. If possible, store numeric values using a numeric data type.

## 8. `CAST()` vs. `CONVERT()`

Both can convert data types, but their syntax and availability differ by database.

Using `CAST()`:

```sql
SELECT CAST('123' AS INTEGER);
```

Using `CONVERT()` in MySQL:

```sql
SELECT CONVERT('123', SIGNED);
```

`CAST()` uses widely recognized SQL syntax and is a useful default for general SQL notes. Supported types and conversion behavior still vary by database.

## 9. Type Syntax by Database

| Database | Text to integer | Integer to text |
|---|---|---|
| MySQL | `CAST('123' AS INTEGER)` | `CAST(123 AS CHAR)` |
| PostgreSQL | `CAST('123' AS INTEGER)` | `CAST(123 AS TEXT)` |
| SQL Server | `CAST('123' AS INT)` | `CAST(123 AS VARCHAR(20))` |
| SQLite | `CAST('123' AS INTEGER)` | `CAST(123 AS TEXT)` |

These are common examples; details may vary with database versions and input values.

## 10. What if Conversion Fails?

A conversion may fail or produce a database-specific result if the input cannot be represented by the target type.

```sql
SELECT CAST('hello' AS INTEGER);
```

`'hello'` is not a valid integer. Some databases return an error; others may produce a value such as `0`. Do not assume invalid values behave identically in every database.

## 11. Common Mistakes

### Mistake 1: Putting the target type in quotes

Incorrect:

```sql
SELECT CAST('123' AS 'INTEGER');
```

Correct:

```sql
SELECT CAST('123' AS INTEGER);
```

The target data type is written without quotes.

### Mistake 2: Using `TEXT` in MySQL `CAST()`

For MySQL, prefer:

```sql
SELECT CAST(123 AS CHAR);
```

The target type accepted by `CAST()` depends on the database.

### Mistake 3: Expecting `CAST()` to change the table permanently

```sql
SELECT CAST(amount_text AS DECIMAL(10, 2))
FROM orders;
```

This converts the value in the query result. It does not change the table's column definition.

### Mistake 4: Converting invalid text

Before converting a text column, ensure its values are valid for the target type. Conversion rules vary by database.

## 12. Quick Revision

- **Purpose:** Convert an expression from one data type to another.
- **Syntax:** `CAST(expression AS data_type)`
- **Text to integer:** `CAST('123' AS INTEGER)`
- **Text to decimal:** `CAST('12.50' AS DECIMAL(10, 2))`
- **Integer to text in MySQL:** `CAST(123 AS CHAR)`
- **Text to date:** `CAST('2026-10-26' AS DATE)`
- **`DATETIME` to `DATE`:** The time portion is removed from the result.
- **Permanent table change?** No. `CAST()` changes the expression's result type.
- **Database differences:** Supported target types and invalid-conversion behavior vary.

## 13. Practice Questions

Try to write a query for each task.

1. Convert the text value `'500'` to an integer.
2. Convert `'149.99'` to `DECIMAL(8, 2)`.
3. Convert the number `2026` to character data in MySQL.
4. Convert `'2026-10-26 14:30:00'` to a `DATE`.
5. Given a table `orders` with a text column `amount_text`, calculate the sum after converting values to `DECIMAL(10, 2)`.

### Answers

```sql
-- 1. Text to integer
SELECT CAST('500' AS INTEGER);

-- 2. Text to decimal
SELECT CAST('149.99' AS DECIMAL(8, 2));

-- 3. Number to text in MySQL
SELECT CAST(2026 AS CHAR);

-- 4. DATETIME text to DATE
SELECT CAST('2026-10-26 14:30:00' AS DATE);

-- 5. Sum converted amounts
SELECT SUM(CAST(amount_text AS DECIMAL(10, 2))) AS total_amount
FROM orders;
```
