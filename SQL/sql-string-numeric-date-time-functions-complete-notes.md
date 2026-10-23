# SQL Notes: String Functions, Numeric Functions, and Date & Time Functions

> **Purpose:** Comprehensive, GitHub-ready notes for SQL string functions, numeric functions, and date/time functions, with examples, common mistakes, and dialect differences.
>
> **Dialect note:** SQL function names and syntax vary between PostgreSQL, MySQL, SQL Server, Oracle, and SQLite. Examples use broadly familiar SQL where possible; dialect-specific alternatives are noted. Always check the database you use.

---

# 1. String Functions

## 1.1 What are string functions?

String functions work with character data such as names, emails, addresses, product descriptions, and codes. They can inspect, transform, extract, combine, or clean text.

Common uses:
- Standardizing text for reports and comparisons.
- Removing unwanted spaces.
- Extracting part of a string.
- Combining first and last names.
- Finding the length of a value.
- Replacing or locating text.
- Cleaning inconsistent data.

Example table: `customers`

| customer_id | first_name | last_name | email |
|---:|---|---|---|
| 1 | `  Asha` | `Sharma  ` | `ASHA@EXAMPLE.COM` |
| 2 | `Ravi` | `Kumar` | `ravi@example.com` |
| 3 | `Neha` | `Verma` | `neha.verma@example.com` |

## 1.2 `UPPER()` and `LOWER()`

Convert text to uppercase or lowercase.

```sql
SELECT
    UPPER(first_name) AS uppercase_name,
    LOWER(email) AS lowercase_email
FROM customers;
```

- `UPPER(text)` converts letters to uppercase.
- `LOWER(text)` converts letters to lowercase.
- These functions generally preserve non-letter characters.
- Language-specific case conversion can depend on collation, locale, and database implementation.

Use cases include normalizing display values and making case-insensitive comparisons where appropriate. Be aware that applying a function to a column in a `WHERE` condition may prevent ordinary index use unless a suitable functional index or computed column exists.

## 1.3 `TRIM()`, `LTRIM()`, and `RTRIM()`

Remove unwanted characters, commonly spaces, from a string.

```sql
SELECT
    TRIM(first_name) AS cleaned_name,
    LTRIM(first_name) AS left_cleaned_name,
    RTRIM(last_name) AS right_cleaned_name
FROM customers;
```

- `TRIM(text)` typically removes leading and trailing spaces.
- `LTRIM(text)` removes leading spaces.
- `RTRIM(text)` removes trailing spaces.

Some databases support a richer `TRIM` syntax for removing a specified character. Exact syntax varies.

Example:

```sql
SELECT TRIM('   SQL Notes   ') AS cleaned_text;
```

Result: `SQL Notes`.

**Important:** `TRIM` does not normally remove spaces in the middle of a string. It also does not necessarily remove every kind of whitespace, such as tabs or non-breaking spaces, in the same way across all databases.

## 1.4 `LENGTH()`, `CHAR_LENGTH()`, and `LEN()`

Find the length of a string.

```sql
SELECT
    LENGTH(first_name) AS string_length
FROM customers;
```

Common dialect differences:

| Function | Commonly used in | Meaning / caveat |
|---|---|---|
| `LENGTH(text)` | PostgreSQL, MySQL, Oracle, SQLite | Length behavior varies: in MySQL it counts bytes; in PostgreSQL it counts characters for text |
| `CHAR_LENGTH(text)` / `CHARACTER_LENGTH(text)` | PostgreSQL, MySQL, standard SQL implementations | Character count |
| `LEN(text)` | SQL Server | Character count excluding trailing spaces |

For example, a multi-byte Unicode character can occupy more than one byte, so byte length and character length may differ.

Check the target database before choosing a function when Unicode or trailing spaces matter.

## 1.5 `CONCAT()` and concatenation operators

Combine strings.

```sql
SELECT CONCAT(first_name, ' ', last_name) AS full_name
FROM customers;
```

Concatenation syntax differs:
- `CONCAT(a, b, ...)` is supported by several major databases.
- PostgreSQL and Oracle commonly support `||`.
- SQL Server supports `CONCAT()` and also has the `+` operator for string concatenation.
- MySQL uses `CONCAT()`; `||` normally means logical OR unless a SQL mode changes that behavior.

### NULL behavior matters

`CONCAT()` does not handle `NULL` identically across databases. For example, MySQL's `CONCAT()` returns `NULL` if any argument is `NULL`, while SQL Server's `CONCAT()` treats `NULL` as an empty string.

If a missing first or last name should be treated as empty text, make that rule explicit:

```sql
SELECT
    CONCAT(COALESCE(first_name, ''), ' ', COALESCE(last_name, '')) AS full_name
FROM customers;
```

If using `||`, the corresponding expression may be:

```sql
SELECT
    COALESCE(first_name, '') || ' ' || COALESCE(last_name, '') AS full_name
FROM customers;
```

The `||` version is not portable to every SQL dialect.

## 1.6 `SUBSTRING()` / `SUBSTR()`

Extract part of a string.

```sql
SELECT SUBSTRING(email FROM 1 FOR 4) AS email_prefix
FROM customers;
```

Another common form:

```sql
SELECT SUBSTRING(email, 1, 4) AS email_prefix
FROM customers;
```

Some databases use `SUBSTR(text, start, length)`.

Important considerations:
- Start-position conventions and accepted syntax can vary by database.
- In many SQL systems, positions are one-based: position `1` is the first character.
- If the requested starting position or length is outside the string, exact behavior can vary.
- Use the syntax supported by your database.

Example:

```sql
SELECT SUBSTRING('DATABASE', 1, 4) AS result;
```

Typical result: `DATA`.

## 1.7 `LEFT()` and `RIGHT()`

Return a specified number of characters from the left or right side of a string.

```sql
SELECT
    LEFT(email, 4) AS email_start,
    RIGHT(email, 4) AS email_end
FROM customers;
```

These functions are supported by several popular systems, but availability differs. Use `SUBSTRING`/`SUBSTR` when that is the more portable option for the target database.

## 1.8 `REPLACE()`

Replace occurrences of a substring.

```sql
SELECT REPLACE('sql is useful', 'useful', 'powerful') AS result;
```

Result: `sql is powerful`.

Example:

```sql
SELECT REPLACE(phone_number, '-', '') AS normalized_phone
FROM customers;
```

`REPLACE` returns a transformed result; it does not update the stored value unless used in an `UPDATE`.

Be careful when replacing characters in identifiers, codes, or phone numbers: a replacement rule that is too broad may change meaningful data.

## 1.9 `POSITION()`, `INSTR()`, `CHARINDEX()`, and `LOCATE()`

Find where a substring occurs inside another string. Function names and argument order differ.

| Function | Common dialects | Example form |
|---|---|---|
| `POSITION(substring IN string)` | PostgreSQL, standard-style syntax | `POSITION('@' IN email)` |
| `INSTR(string, substring)` | Oracle; also available in MySQL with related behavior | `INSTR(email, '@')` |
| `CHARINDEX(substring, string)` | SQL Server | `CHARINDEX('@', email)` |
| `LOCATE(substring, string)` | MySQL | `LOCATE('@', email)` |

Example in a PostgreSQL-style syntax:

```sql
SELECT POSITION('@' IN email) AS at_sign_position
FROM customers;
```

A return value of zero or another value for “not found” depends on the function and dialect; verify the function's documentation.

## 1.10 `REVERSE()`

Reverse the characters in a string where supported.

```sql
SELECT REVERSE('SQL') AS result;
```

Typical result: `LQS`.

This can be useful for text manipulation, but it is not a general solution for validating or parsing structured values.

## 1.11 `REPEAT()` / `REPLICATE()`

Repeat text a specified number of times.

```sql
SELECT REPEAT('*', 5) AS result;
```

Typical result: `*****`.

SQL Server uses `REPLICATE()`:

```sql
SELECT REPLICATE('*', 5) AS result;
```

Use cases include simple text formatting and creating visual placeholders in reports.

## 1.12 `LPAD()` and `RPAD()`

Pad a string to a target length.

```sql
SELECT LPAD('42', 5, '0') AS padded_value;
```

Typical result: `00042`.

```sql
SELECT RPAD('SQL', 6, '.') AS padded_value;
```

Typical result: `SQL...`.

Support and exact behavior differ across systems. SQL Server does not provide the same built-in `LPAD`/`RPAD` functions in its standard T-SQL function set; padding can be implemented using string functions.

Padding is useful for display codes. Do not use it to alter numeric meaning: a padded identifier such as `'00042'` is text, not the number `42`.

## 1.13 `ASCII()` and `CHAR()` / `CHR()`

These functions work with character codes, but names and Unicode behavior vary by database.

- `ASCII(text)` commonly returns a numeric code for a character.
- `CHAR(number)` commonly returns a character from a code.
- `CHR(number)` is used in some systems, including PostgreSQL, for a character code.

Example:

```sql
SELECT ASCII('A') AS character_code;
```

Common result: `65` in ASCII-compatible implementations.

Use these functions only when the encoding and character-code behavior are understood; Unicode code points and byte encodings are not interchangeable concepts.

## 1.14 `REGEXP_REPLACE()` and regular-expression functions

Some databases support regular-expression-based matching and replacement.

Example in PostgreSQL:

```sql
SELECT REGEXP_REPLACE(phone_number, '[^0-9]', '', 'g') AS digits_only
FROM customers;
```

This removes characters that are not digits in PostgreSQL's syntax. Other databases have different regular-expression functions and options.

Regular expressions are useful for more complex cleanup, but they should not replace proper validation of emails, phone numbers, or other structured data.

## 1.15 String functions and `NULL`

Most string functions return `NULL` when their input is `NULL`, though behavior depends on the specific function and database.

Example:

```sql
SELECT UPPER(NULL);
```

Typically returns `NULL`.

To supply a fallback:

```sql
SELECT UPPER(COALESCE(first_name, 'Unknown')) AS display_name
FROM customers;
```

This makes the fallback explicit.

## 1.16 Using string functions in `WHERE`

Example:

```sql
SELECT *
FROM customers
WHERE LOWER(email) = 'asha@example.com';
```

This may work for case-insensitive matching, but applying a function to the column can make a regular index less useful. Depending on the database, alternatives include:
- Case-insensitive data types or collations.
- Functional/expression indexes.
- A normalized column.
- A comparison operator designed for case-insensitive matching.

Do not assume all collations compare strings in the same way.

## 1.17 Common string-function mistakes

1. Confusing byte length with character length.
2. Assuming every database supports the same function name or syntax.
3. Forgetting `NULL` behavior in concatenation.
4. Assuming `TRIM()` removes every whitespace character or internal spaces.
5. Treating numeric-looking identifiers as numbers and losing leading zeros.
6. Using `REPLACE()` without checking whether the replacement changes valid data.
7. Assuming a function in `WHERE` can always use an ordinary index efficiently.
8. Assuming case conversion alone guarantees every kind of case-insensitive comparison.
9. Assuming `SUBSTRING` argument order is identical in every database.
10. Confusing an empty string with `NULL`.

## 1.18 String-functions quick revision

- `UPPER()` / `LOWER()` — change letter case.
- `TRIM()` / `LTRIM()` / `RTRIM()` — remove leading/trailing characters or spaces, subject to dialect.
- `LENGTH()` / `CHAR_LENGTH()` / `LEN()` — measure length, with different byte/character/trailing-space behavior.
- `CONCAT()` / `||` / `+` — concatenate strings, with dialect-specific syntax and `NULL` behavior.
- `SUBSTRING()` / `SUBSTR()` — extract text.
- `LEFT()` / `RIGHT()` — take characters from either end.
- `REPLACE()` — substitute text.
- `POSITION()` / `INSTR()` / `CHARINDEX()` / `LOCATE()` — find a substring.
- `REVERSE()` — reverse text.
- `REPEAT()` / `REPLICATE()` — repeat text.
- `LPAD()` / `RPAD()` — pad to a target length where supported.
- Regular-expression functions — perform pattern-based text operations.

---

# 2. Numeric Functions

## 2.1 What are numeric functions?

Numeric functions perform calculations or transformations on numeric values, such as salaries, prices, quantities, percentages, and measurements.

They are useful for:
- Rounding prices and measurements.
- Finding absolute values.
- Calculating powers and square roots.
- Finding remainders.
- Calculating logarithms and exponentials.
- Producing approximate random values.
- Safely calculating ratios.

Function availability, names, precision, and return types can differ across database systems.

## 2.2 `ABS()`

Returns the absolute value: the distance from zero without a negative sign.

```sql
SELECT ABS(-25) AS result;
```

Result: `25`.

Example:

```sql
SELECT
    product_id,
    ABS(actual_price - listed_price) AS price_difference
FROM products;
```

This returns the magnitude of the difference, not which price is larger.

## 2.3 `ROUND()`

Rounds a number to a specified number of decimal places.

```sql
SELECT ROUND(123.4567, 2) AS result;
```

Common result: `123.46`.

Example:

```sql
SELECT ROUND(price, 2) AS displayed_price
FROM products;
```

Important:
- The second argument often specifies decimal places, but details vary.
- Negative precision can round to tens, hundreds, or larger positions in some systems.
- Tie-breaking rules can differ by data type and database.
- Rounding a value for display is not the same as storing a rounded value.
- Floating-point representations can cause surprising results; exact decimal types are generally preferable for money.

## 2.4 `CEIL()` / `CEILING()` and `FLOOR()`

- `CEIL()` or `CEILING()` returns the smallest integer greater than or equal to a number.
- `FLOOR()` returns the greatest integer less than or equal to a number.

```sql
SELECT
    CEILING(4.2) AS ceiling_value,
    FLOOR(4.8) AS floor_value;
```

Typical results: `5` and `4`.

Negative example:

```sql
SELECT
    CEILING(-4.2) AS ceiling_value,
    FLOOR(-4.2) AS floor_value;
```

Typical results: `-4` and `-5`.

`FLOOR` is not the same as truncating toward zero for negative numbers.

## 2.5 `TRUNC()` / `TRUNCATE()`

Truncates digits without rounding, where supported.

```sql
SELECT TRUNC(123.456, 2);
```

Typical result: `123.45` in databases using this syntax.

MySQL supports `TRUNCATE(number, decimals)`; other systems use `TRUNC` or a different signature. SQL Server's `ROUND(number, length, function)` can truncate when its third argument is nonzero.

### Rounding versus truncation

| Operation | Input | Result to 2 decimal places |
|---|---:|---:|
| `ROUND(12.349, 2)` | 12.349 | 12.35 |
| `TRUNC(12.349, 2)` | 12.349 | 12.34 |

Use truncation only when the requirement specifically says to discard digits without rounding.

## 2.6 `MOD()` and remainder

Returns the remainder after division, but the function name and negative-number behavior may vary.

```sql
SELECT MOD(17, 5) AS result;
```

Typical result: `2`.

Some systems use the `%` operator:

```sql
SELECT 17 % 5 AS result;
```

Common uses:
- Checking even/odd numbers: remainder when divided by 2.
- Repeating patterns.
- Assigning rows to buckets.

Example:

```sql
SELECT employee_id
FROM employees
WHERE MOD(employee_id, 2) = 0;
```

This returns even employee IDs in systems supporting this syntax.

## 2.7 `POWER()`

Raises a number to a power.

```sql
SELECT POWER(2, 3) AS result;
```

Result: `8`.

```sql
SELECT POWER(base_value, exponent_value)
FROM calculations;
```

Results can be approximate depending on the types and function implementation. Invalid domains or overflow can cause errors or special values.

## 2.8 `SQRT()`

Returns the square root where the input is in the valid domain.

```sql
SELECT SQRT(81) AS result;
```

Result: `9`.

Negative input handling differs by database and numeric type; it may return an error or a special result. Validate the input if negative values are possible.

## 2.9 `SIGN()`

Returns the sign of a number in systems that support it.

```sql
SELECT
    SIGN(-10) AS negative_sign,
    SIGN(0) AS zero_sign,
    SIGN(15) AS positive_sign;
```

Common results: `-1`, `0`, `1`.

The exact return type can vary. `NULL` input generally yields `NULL`.

## 2.10 `EXP()`, `LN()`, `LOG()`, and `LOG10()`

These functions support exponential and logarithmic calculations.

- `EXP(x)` computes e raised to the power x.
- `LN(x)` computes the natural logarithm in systems that provide this name.
- `LOG()` syntax and base behavior vary by database.
- `LOG10(x)` computes the base-10 logarithm where supported.

Examples:

```sql
SELECT EXP(1) AS e_value;
SELECT LN(10) AS natural_log;
SELECT LOG10(100) AS base10_log;
```

Typical mathematical results:
- `EXP(1)` is approximately `2.71828`.
- `LOG10(100)` is `2`.

Logarithms require a valid positive input. The meaning of `LOG(x)` versus `LOG(base, x)` is dialect-specific; do not assume the same argument order everywhere.

## 2.11 `PI()`

Returns an approximation of π in databases that support it.

```sql
SELECT PI() AS pi_value;
```

Useful in geometry calculations. Precision and return type are implementation-specific.

## 2.12 `RAND()` / `RANDOM()`

Generate a pseudo-random value. The function name and behavior vary.

- MySQL and SQL Server commonly use `RAND()` with different semantics.
- PostgreSQL commonly uses `RANDOM()`.
- SQLite has its own random functions.

Example in PostgreSQL:

```sql
SELECT RANDOM() AS random_value;
```

This typically returns a pseudo-random value from 0 up to but not including 1.

Important:
- Random values are not necessarily cryptographically secure.
- Calling a random function in a query may not produce an independent value for every row in every database/context.
- Query plans, seeds, and evaluation rules can affect results.
- Do not use ordinary SQL random functions for passwords, tokens, or security-critical randomness.

## 2.13 Numeric functions and `NULL`

Numeric functions generally return `NULL` when their numeric input is `NULL`.

```sql
SELECT ABS(NULL);
SELECT ROUND(NULL, 2);
```

These typically return `NULL`.

Use `COALESCE` only when a fallback is semantically valid:

```sql
SELECT ROUND(COALESCE(discount, 0), 2) AS discount
FROM products;
```

This treats a missing discount as zero for the output. It does not update the stored column.

## 2.14 Division, integer division, and safe ratios

Division behavior depends on operand types.

```sql
SELECT 5 / 2 AS result;
```

Some databases or type combinations return `2` using integer division; others return `2.5`. Cast operands to a decimal type when a fractional result is required.

Example:

```sql
SELECT
    CAST(total_sales AS DECIMAL(12, 2))
      / NULLIF(CAST(total_orders AS DECIMAL(12, 2)), 0) AS average_per_order
FROM sales_summary;
```

Casting syntax varies, but the goals are:
1. Use a type that preserves the required fractional precision.
2. Prevent division by zero with `NULLIF(denominator, 0)`.
3. Decide how to display a `NULL` result when the denominator is zero or missing.

Avoid assuming that `1 / 2` will return `0.5` in every database.

## 2.15 Precision, scale, and money

`DECIMAL(p, s)` / `NUMERIC(p, s)` generally represent exact decimal values:
- `p` = precision, the total number of significant decimal digits.
- `s` = scale, the number of digits to the right of the decimal point.

For example, `DECIMAL(8, 2)` can represent values with up to eight total digits, two of them after the decimal point, subject to the database's range rules.

Floating-point types such as `FLOAT` and `REAL` represent approximate values and can produce small rounding artifacts.

For financial data:
- Prefer an appropriate exact decimal type for amounts.
- Choose precision and scale based on business limits.
- Define when rounding occurs.
- Avoid repeatedly rounding intermediate values unless required.
- Remember that display formatting does not necessarily change stored precision.

## 2.16 Numeric functions in `WHERE` and indexes

Example:

```sql
SELECT *
FROM products
WHERE ROUND(price, 0) = 100;
```

This may be less efficient than a direct range condition because applying a function to the indexed column can limit ordinary index use. The equivalent range depends on the rounding rule and database.

Use execution plans and indexes appropriate to the actual query; do not rewrite a condition unless the rewritten boundaries are mathematically correct.

## 2.17 Common numeric-function mistakes

1. Confusing `ROUND` with truncation.
2. Assuming `FLOOR` truncates toward zero for negative values.
3. Assuming `LOG` uses the same base and argument order in every database.
4. Assuming division always returns a decimal result.
5. Ignoring division by zero.
6. Using approximate floating-point types for values that require exact decimal representation.
7. Rounding stored values when only display rounding is required.
8. Forgetting that numeric functions usually propagate `NULL`.
9. Treating a pseudo-random function as cryptographically secure.
10. Assuming the same function names and return types exist in every SQL dialect.

## 2.18 Numeric-functions quick revision

- `ABS(x)` — absolute value.
- `ROUND(x, n)` — round to a requested precision.
- `CEIL()` / `CEILING()` — round upward to an integer.
- `FLOOR()` — round downward to an integer.
- `TRUNC()` / `TRUNCATE()` — discard digits without rounding, depending on dialect.
- `MOD(a, b)` / `%` — remainder.
- `POWER(a, b)` — exponentiation.
- `SQRT(x)` — square root.
- `SIGN(x)` — sign of a number.
- `EXP(x)` — e to the power x.
- `LN(x)`, `LOG(x)`, `LOG10(x)` — logarithms; check dialect and argument order.
- `PI()` — approximation of π.
- `RAND()` / `RANDOM()` — pseudo-random values; check dialect and evaluation semantics.

---

# 3. Date and Time Functions

## 3.1 Why date/time functions matter

Date and time functions help you:
- Retrieve the current date and time.
- Extract a year, month, day, or other component.
- Add or subtract time intervals.
- Calculate elapsed time.
- Filter records by a time range.
- Format dates for reports.
- Convert between date/time types and text.
- Group transactions by day, month, quarter, or year.

Date/time syntax varies significantly across SQL dialects. Always distinguish a real date/time value from a formatted string.

## 3.2 Date and time data types

Common types include:

| Type | Typical purpose | Important note |
|---|---|---|
| `DATE` | Calendar date | Usually has no time-of-day component |
| `TIME` | Time of day | Usually has no calendar date |
| `TIMESTAMP` / `DATETIME` | Date and time | Time-zone semantics depend on type and database |
| `TIMESTAMP WITH TIME ZONE` | Timestamp with time-zone-aware semantics | Exact storage/display semantics vary by engine |
| `INTERVAL` | Duration or calendar interval | Support and syntax vary by database |

Common dialect names:
- PostgreSQL has `DATE`, `TIME`, `TIMESTAMP`, `TIMESTAMP WITH TIME ZONE`, and `INTERVAL`.
- MySQL has `DATE`, `TIME`, `DATETIME`, and `TIMESTAMP`, with specific time-zone and range behavior.
- SQL Server has `date`, `time`, `datetime`, `datetime2`, `datetimeoffset`, and other types.
- Oracle has `DATE` (which includes time to seconds), `TIMESTAMP`, and time-zone-aware timestamp types.

Do not assume that `DATE` means exactly the same thing in every engine. In Oracle, for example, `DATE` includes a time component.

## 3.3 Getting the current date and time

Function names differ:

| Database | Current date | Current date and time |
|---|---|---|
| PostgreSQL | `CURRENT_DATE` | `CURRENT_TIMESTAMP`, `NOW()` |
| MySQL | `CURRENT_DATE()` / `CURDATE()` | `NOW()`, `CURRENT_TIMESTAMP()` |
| SQL Server | `CAST(GETDATE() AS date)` | `GETDATE()`, `SYSDATETIME()` |
| Oracle | `CURRENT_DATE` | `CURRENT_TIMESTAMP`, `SYSDATE` |
| SQLite | `date('now')` | `datetime('now')` |

Examples:

```sql
SELECT CURRENT_DATE;
SELECT CURRENT_TIMESTAMP;
```

These standard-style expressions are widely supported, but details such as precision, time zone, and whether the value is fixed at the start of a statement/transaction vary.

Important distinctions:
- A current date/time function may use the session time zone or server configuration.
- Some functions return a timestamp with time-zone information; others return a local or time-zone-naive value.
- `CURRENT_TIMESTAMP` and a system-clock function may differ in precision and evaluation timing.

## 3.4 Extracting date/time parts

You may need a year, month, day, hour, or other component.

### `EXTRACT()`

Common in PostgreSQL and standard-style SQL:

```sql
SELECT
    EXTRACT(YEAR FROM order_date) AS order_year,
    EXTRACT(MONTH FROM order_date) AS order_month,
    EXTRACT(DAY FROM order_date) AS order_day
FROM orders;
```

### `YEAR()`, `MONTH()`, and `DAY()`

Supported by MySQL and SQL Server in familiar forms:

```sql
SELECT
    YEAR(order_date) AS order_year,
    MONTH(order_date) AS order_month,
    DAY(order_date) AS order_day
FROM orders;
```

SQL Server also provides `DATEPART()`:

```sql
SELECT DATEPART(year, order_date) AS order_year
FROM orders;
```

Oracle commonly uses `EXTRACT(YEAR FROM date_value)` and related syntax.

For hour/minute/second, use `EXTRACT`, `DATEPART`, or dialect-specific functions as appropriate.

**Performance note:** Applying `YEAR(order_date)` in a filter may prevent use of a regular index on `order_date`. For date filtering, a range condition is often preferable.

## 3.5 Filtering by date: use ranges

Suppose you want orders on one calendar day and `order_date` stores a date-time value.

A risky pattern:

```sql
WHERE CAST(order_date AS DATE) = '2026-10-23'
```

This may work, but converting the column can reduce index efficiency, and date-literal syntax varies.

A generally preferable pattern for a timestamp column is a half-open range:

```sql
WHERE order_date >= '2026-10-23'
  AND order_date <  '2026-10-24'
```

This includes all times on October 23 and excludes midnight on October 24. Use a typed date/timestamp literal or parameter format appropriate to your database.

### Why not use `BETWEEN` for an entire day?

```sql
WHERE order_date BETWEEN '2026-10-23' AND '2026-10-23'
```

For a timestamp column, the end value may mean midnight at the beginning of the day, so later times that day may be missed.

A half-open range (`>= start AND < next_start`) avoids guessing the final fractional second and is usually robust for timestamp filtering.

## 3.6 `DATEADD()` and adding intervals

Add a number of days, months, or other units to a date/time.

### SQL Server

```sql
SELECT DATEADD(day, 7, order_date) AS one_week_later
FROM orders;
```

### MySQL

```sql
SELECT DATE_ADD(order_date, INTERVAL 7 DAY) AS one_week_later
FROM orders;
```

### PostgreSQL

```sql
SELECT order_date + INTERVAL '7 days' AS one_week_later
FROM orders;
```

### Oracle

Oracle supports interval arithmetic and date arithmetic, for example:

```sql
SELECT order_date + 7 AS one_week_later
FROM orders;
```

For Oracle `DATE`, adding a number adds that many days. Interval syntax is also available for appropriate types.

Month arithmetic needs special care. Adding one month to a date near the end of a month may adjust to the last valid day in the target month; rules differ across engines.

## 3.7 Subtracting dates and calculating durations

The result of subtracting dates/timestamps varies by database and type.

- PostgreSQL date subtraction commonly returns an integer number of days; timestamp subtraction returns an interval.
- Oracle `DATE - DATE` returns a number of days (which may include a fractional day).
- SQL Server typically uses `DATEDIFF`/`DATEDIFF_BIG` for date-part boundaries.
- MySQL provides `DATEDIFF()` for date-only day differences and `TIMESTAMPDIFF()` for a selected unit.

### `DATEDIFF()`

SQL Server:

```sql
SELECT DATEDIFF(day, start_date, end_date) AS day_difference
FROM projects;
```

MySQL:

```sql
SELECT DATEDIFF(end_date, start_date) AS day_difference
FROM projects;
```

**Important:** The argument order and meaning differ. SQL Server's `DATEDIFF` counts date-part boundaries crossed, not always the exact elapsed duration. MySQL's `DATEDIFF` returns the difference in calendar dates and ignores time-of-day.

### `TIMESTAMPDIFF()` in MySQL

```sql
SELECT TIMESTAMPDIFF(HOUR, start_time, end_time) AS hours_elapsed
FROM sessions;
```

This calculates a difference in the requested unit according to MySQL's rules.

### PostgreSQL timestamp subtraction

```sql
SELECT end_time - start_time AS elapsed_time
FROM sessions;
```

This returns an interval for timestamp values.

Always clarify whether you need elapsed seconds/minutes/hours, calendar days, or date-part boundaries. These are not interchangeable.

## 3.8 `DATE_TRUNC()` and grouping by periods

PostgreSQL supports `DATE_TRUNC()` to truncate a timestamp to a larger time unit.

```sql
SELECT
    DATE_TRUNC('month', order_date) AS order_month,
    COUNT(*) AS order_count
FROM orders
GROUP BY DATE_TRUNC('month', order_date)
ORDER BY order_month;
```

This groups timestamps by month. Other databases have different ways to construct a month key, such as formatting, `DATEFROMPARTS`, or date arithmetic.

For reliable grouping, prefer a date/time value representing the period start rather than a formatted label if possible.

## 3.9 `LAST_DAY()` and finding month boundaries

Some databases provide a function for the last calendar day of a month.

MySQL:

```sql
SELECT LAST_DAY(order_date) AS month_end
FROM orders;
```

Oracle also supports `LAST_DAY(date)`. PostgreSQL and SQL Server commonly use date arithmetic or other functions to calculate month boundaries.

Month-end behavior is important for:
- Billing cycles.
- Financial reporting.
- Subscription renewals.
- Monthly aggregation.

Be clear about time zones and timestamp boundaries when a calendar month is defined in a particular local time zone.

## 3.10 Formatting dates as strings

Formatting is useful for display, exports, and reports. It should generally happen after filtering and calculations.

### PostgreSQL / Oracle style

PostgreSQL:

```sql
SELECT TO_CHAR(order_date, 'YYYY-MM-DD') AS formatted_date
FROM orders;
```

Oracle also supports `TO_CHAR(date_value, format_model)`.

### MySQL

```sql
SELECT DATE_FORMAT(order_date, '%Y-%m-%d') AS formatted_date
FROM orders;
```

### SQL Server

```sql
SELECT FORMAT(order_date, 'yyyy-MM-dd') AS formatted_date
FROM orders;
```

SQL Server's `FORMAT()` can be more expensive than simpler conversion approaches in large queries. Use it mainly when formatting flexibility is needed.

Formatting produces text, not a date/time value. Do not convert to text early if you still need chronological sorting, date arithmetic, or reliable date comparisons.

## 3.11 Converting text to date/time

Conversion functions and format rules vary.

Examples:

```sql
CAST('2026-10-23' AS DATE)
```

```sql
CAST('2026-10-23 14:30:00' AS TIMESTAMP)
```

The second example is supported in some systems but not with identical syntax everywhere; SQL Server commonly uses `datetime2` rather than a `TIMESTAMP` type for date/time storage.

Other functions include:
- MySQL: `STR_TO_DATE(text, format)`
- SQL Server: `TRY_CONVERT()` / `TRY_CAST()` and `CONVERT()`
- Oracle: `TO_DATE(text, format_model)` and `TO_TIMESTAMP(...)`
- PostgreSQL: casts and `TO_DATE`/`TO_TIMESTAMP` in suitable cases

Use explicit format masks where required, and avoid ambiguous inputs such as `03/04/2026`, which could mean March 4 or April 3.

If the source text is untrusted or inconsistent, use a safe conversion function where available and handle invalid values rather than assuming every row converts successfully.

## 3.12 `DATE` versus timestamp comparisons

Comparing a timestamp with a date may implicitly cast one value or interpret it as midnight, depending on the database.

For example:

```sql
WHERE order_timestamp = '2026-10-23'
```

may match only a timestamp exactly at midnight rather than all events on that day.

For an entire day, use the half-open range:

```sql
WHERE order_timestamp >= '2026-10-23'
  AND order_timestamp <  '2026-10-24'
```

Use proper typed parameters or literals for the target database.

## 3.13 Time zones and daylight saving time

Date/time bugs often come from mixing local time and UTC.

Key concepts:
- **UTC** is a common reference time standard.
- A **local time** is interpreted in a particular time zone.
- A timestamp with time-zone-aware semantics can be stored or normalized differently by different database systems.
- A time-zone-naive timestamp does not itself identify a unique instant without an agreed time zone.
- Daylight saving transitions can create local times that are skipped or occur twice.

Best practices:
1. Know whether each column stores UTC, local time, or time-zone-aware instants.
2. Use a consistent convention for storage and conversion.
3. Convert to the relevant local time zone for user-facing calendar reporting.
4. Avoid assuming every day is exactly 24 hours in a daylight-saving time zone.
5. Be explicit about the time zone used to define business-day boundaries.

Time-zone conversion functions differ substantially by database. Consult the target database's documentation before using them in production logic.

## 3.14 `CURRENT_DATE` versus `CURRENT_TIMESTAMP`

- `CURRENT_DATE` represents the current date according to the database's applicable time-zone/session semantics.
- `CURRENT_TIMESTAMP` represents a current date-and-time value.
- The time-zone information and evaluation timing depend on the database.

If a report uses `CURRENT_DATE` to define “today,” confirm that the session time zone matches the business's intended time zone.

## 3.15 Extracting day of week and day of year

Database functions for day-of-week numbering differ. For example, the numeric value for Sunday can differ across systems or settings.

Examples of function families:
- `EXTRACT(DOW FROM date_value)` in PostgreSQL (with PostgreSQL-specific numbering).
- `DAYOFWEEK()` in MySQL (with MySQL-specific numbering).
- `DATEPART(weekday, date_value)` in SQL Server (affected by settings such as `DATEFIRST`).
- Format models or `TO_CHAR` in Oracle.

Do not assume the same integer means the same weekday in every database. If weekday labels are required, use a documented dialect-specific expression and test it.

## 3.16 Date/time functions and `NULL`

Date/time functions commonly return `NULL` when their date/time input is `NULL`.

```sql
SELECT EXTRACT(YEAR FROM NULL);
```

Exact typing/syntax can affect whether this exact statement is accepted, but a typed `NULL` passed to many date/time functions produces a `NULL` result.

Check missing dates explicitly:

```sql
SELECT *
FROM orders
WHERE shipped_at IS NULL;
```

Avoid substituting the current date for a missing date unless that is the intended business rule. A missing `shipped_at` value may mean “not shipped yet,” not “shipped today.”

## 3.17 Date/time indexes and query performance

Prefer filtering the raw date/time column with a range when possible.

Often less index-friendly:

```sql
WHERE YEAR(order_date) = 2026
```

Often preferable:

```sql
WHERE order_date >= '2026-01-01'
  AND order_date <  '2027-01-01'
```

This form can use a regular index on `order_date` more effectively. Exact behavior depends on the optimizer, indexes, data types, and parameter types.

Avoid converting the column to text for filtering:

```sql
WHERE DATE_FORMAT(order_date, '%Y-%m') = '2026-10'
```

Prefer a suitable date range or a supported indexed expression when possible.

## 3.18 Common date/time-function mistakes

1. Assuming every database has the same function names and argument order.
2. Treating a formatted date string as a real date value.
3. Using equality to match a full day in a timestamp column.
4. Using `BETWEEN` with a midnight end value and unintentionally excluding later times.
5. Confusing elapsed duration with date-part boundaries crossed.
6. Ignoring time zones and daylight saving transitions.
7. Assuming a `DATE` type has the same semantics in every database.
8. Assuming day-of-week numbering is portable.
9. Applying functions to indexed columns when a range condition would be more efficient.
10. Using ambiguous date strings.
11. Assuming month addition always preserves the day number.
12. Replacing a missing date with today's date without considering its meaning.
13. Forgetting that date/time operations can return `NULL` when inputs are `NULL`.

## 3.19 Date/time quick revision

- Current values: `CURRENT_DATE`, `CURRENT_TIMESTAMP`, `NOW()`, `GETDATE()`, `SYSDATE` — dialect and semantics differ.
- Parts: `EXTRACT`, `YEAR`, `MONTH`, `DAY`, `DATEPART`.
- Add time: `DATEADD`, `DATE_ADD`, interval arithmetic.
- Difference: `DATEDIFF`, `TIMESTAMPDIFF`, timestamp subtraction — argument order and semantics differ.
- Period grouping: `DATE_TRUNC` or a dialect-specific equivalent.
- Month end: `LAST_DAY` where supported.
- Formatting: `TO_CHAR`, `DATE_FORMAT`, `FORMAT`.
- Parsing/conversion: `CAST`, `CONVERT`, `TRY_CONVERT`, `STR_TO_DATE`, `TO_DATE`.
- Use half-open ranges (`>= start AND < next_start`) for timestamp date windows.
- Understand time zones and daylight saving time.
- Keep dates as date/time types for filtering and calculations; format them as text mainly for display.

---

# 4. Combined Practical Examples

## 4.1 Clean names and create a display label

```sql
SELECT
    customer_id,
    CONCAT(
        TRIM(COALESCE(first_name, '')),
        ' ',
        TRIM(COALESCE(last_name, ''))
    ) AS full_name
FROM customers;
```

This trims leading/trailing spaces and uses empty strings for missing names. The `CONCAT` function's exact `NULL` behavior varies, but `COALESCE` makes the fallback explicit.

## 4.2 Round revenue and calculate a safe ratio

```sql
SELECT
    product_id,
    ROUND(revenue, 2) AS rounded_revenue,
    CAST(revenue AS DECIMAL(14, 2))
        / NULLIF(CAST(units_sold AS DECIMAL(14, 2)), 0) AS revenue_per_unit
FROM product_sales;
```

The exact decimal type and casting syntax may need adjustment for your database. `NULLIF` prevents a zero denominator; the result is `NULL` when `units_sold` is zero or missing.

## 4.3 Count orders by month

PostgreSQL example:

```sql
SELECT
    DATE_TRUNC('month', order_timestamp) AS order_month,
    COUNT(*) AS order_count,
    ROUND(SUM(order_total), 2) AS monthly_revenue
FROM orders
WHERE order_timestamp >= TIMESTAMP '2026-01-01 00:00:00'
  AND order_timestamp <  TIMESTAMP '2027-01-01 00:00:00'
GROUP BY DATE_TRUNC('month', order_timestamp)
ORDER BY order_month;
```

This filters the year using a range, groups by month, counts orders, and rounds the aggregate for presentation. Adapt the date literal and month-truncation syntax for other databases.

## 4.4 Find records from the last seven days

The exact query depends on the database and on whether “last seven days” means seven rolling 24-hour periods or seven calendar dates.

A generic pattern is:

```sql
SELECT *
FROM events
WHERE event_timestamp >= :start_timestamp
  AND event_timestamp <  :end_timestamp;
```

Bind `:start_timestamp` and `:end_timestamp` as properly typed parameters computed according to the required time zone and definition of the period. Parameter placeholder syntax varies by client and database.

---

# 5. Practice Questions

Try to answer these before checking the answers.

## String functions

1. What is the purpose of `UPPER()` and `LOWER()`?
2. What is the difference between `TRIM()`, `LTRIM()`, and `RTRIM()`?
3. Why can `LENGTH()` and `CHAR_LENGTH()` return different values?
4. What should you consider when concatenating strings that may contain `NULL`?
5. Which function family extracts part of a string?
6. Why might `LOWER(email)` in a `WHERE` clause affect index use?
7. Is `REPLACE()` a permanent update to the table?

## Numeric functions

8. What is the difference between `ROUND()` and truncation?
9. How do `CEILING()` and `FLOOR()` behave for negative numbers?
10. What does `MOD(17, 5)` typically return?
11. Why can `5 / 2` behave differently across databases?
12. How can `NULLIF()` help prevent division by zero?
13. Why are exact decimal types often preferred for money?
14. Is a normal SQL random function suitable for security tokens?

## Date/time functions

15. What is the difference between `DATE` and `TIMESTAMP`?
16. Why is a half-open date range useful for timestamp filtering?
17. Why is `WHERE order_timestamp = '2026-10-23'` potentially wrong for a whole day?
18. What is the difference between elapsed duration and date-part boundaries crossed?
19. Why should date values not be formatted as strings before filtering?
20. Why must time-zone assumptions be explicit?
21. Why can `YEAR(order_date) = 2026` be less index-friendly than a date range?
22. Why is `DATEDIFF()` not portable without checking its dialect-specific behavior?

## Answers

1. They convert text to uppercase and lowercase.
2. `TRIM` removes from both ends; `LTRIM` from the left; `RTRIM` from the right, subject to dialect behavior.
3. One may count bytes while another counts characters.
4. `NULL` concatenation behavior differs; use explicit fallbacks when appropriate.
5. `SUBSTRING()` / `SUBSTR()`.
6. Applying a function to an indexed column can prevent use of a normal index unless a suitable expression index or equivalent exists.
7. No. It transforms the query result; use `UPDATE` to change stored data.
8. `ROUND` follows rounding rules; truncation discards digits without rounding.
9. `CEILING(-4.2)` is typically `-4`; `FLOOR(-4.2)` is typically `-5`.
10. `2`.
11. Integer division may discard the fractional part, depending on operand types and database.
12. `numerator / NULLIF(denominator, 0)` changes a zero denominator to `NULL`.
13. Decimal types can represent decimal amounts exactly within their defined precision and scale; floating-point types are approximate.
14. No. Pseudo-random functions are not necessarily cryptographically secure.
15. `DATE` represents a calendar date; `TIMESTAMP` represents a date and time, with time-zone semantics depending on the type and database.
16. It includes the start and excludes the next period's start, avoiding assumptions about the final fractional second.
17. A date literal may be interpreted as midnight, so later times on that date may not match.
18. Elapsed duration measures time passed; boundary-counting functions may count how many unit boundaries were crossed.
19. Text formatting can prevent proper date arithmetic, comparison, and chronological sorting.
20. The same local clock time can represent different instants across time zones or daylight-saving transitions.
21. A function on the column can reduce the usefulness of a regular index; a range on the raw column is often more index-friendly.
22. Argument order and whether the function counts calendar days, elapsed units, or date-part boundaries differ.

---

# 6. Final Checklist

- [ ] Use string functions to clean, transform, extract, combine, and inspect text.
- [ ] Know the dialect-specific syntax and `NULL` behavior of concatenation.
- [ ] Understand byte length versus character length.
- [ ] Distinguish rounding from truncation.
- [ ] Understand `FLOOR` and `CEILING`, including negative inputs.
- [ ] Use decimal types and an explicit rounding policy for monetary values.
- [ ] Prevent division by zero where appropriate with `NULLIF`.
- [ ] Know the difference between date, time, timestamp, and interval types.
- [ ] Retrieve the current date/time using the function supported by your database.
- [ ] Extract date parts and add/subtract intervals using the correct dialect.
- [ ] Use half-open ranges to filter timestamp periods reliably.
- [ ] Distinguish formatting from conversion.
- [ ] Understand time-zone and daylight-saving implications.
- [ ] Check whether a function on an indexed column could affect query performance.
- [ ] Verify syntax and behavior in the actual database engine before production use.

**Recommended study order:** Basic string cleanup → substring and concatenation → string search/replacement → numeric rounding and arithmetic → precision and safe division → current date/time → extracting parts → date arithmetic and differences → range filtering → formatting/conversion → time zones and performance.
