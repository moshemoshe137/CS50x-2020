# 2/3/2021
# CS50x
# Week 7: SQL

CSVs are "flat-file databases". CSVs are only static- no formulas.

see favorites, favorites2

*Relational Databases* are improvements on flat-file databases. They are software.

Python can use SQL to do more than Python alone can do
We'll use SQLite.
SQLite uses a single, binary file. ```sqlite3```
sqlite3 can convert from CSVs.


```sql
.mode csv
.import FILE TABLE
```
There are 4 fundamental operations in SQL:
Aconym is CRUD. Stands for Create, Read, Update, and Delete.
Those are the 4 properties implemented by all databases.
We have SQL keywords for each of CRUD:
Create -> CREATE, INSERT
Read -> SELECT
Update -> UPDATE
Delete -> DELETE

Back in Excel, we just File -> New. How do we make a spreadsheet here?
```sql
CREATE TABLE table (column type, ...);
```
table, column are names to fill in. type is typing, just like c.
In fact, .import did this for me. It's not part of SQL, it's part of SQLite3. Same for any command beginning with a dot.
```SQLite3
.schema
```
shows the table.

```SQL
SELECT columns FROM table;
```
```SQL
SELECT title FROM shows;
```
(All caps for SQL syntax, all lower for names)
```SQL
SELECT Timestamp, title FROM shows;
```
```SQL
SELECT * FROM shows;
```
SQL has nice built in functions: AVG, COUNT, DISTINCT, LOWER, MAX, MIN, UPPER, ...
```SQL
SELECT DISTINCT(title) FROM shows;
```
```SQL
SELECT DISTINCT(UPPER(title)) FROM shows;
```
More keywords: WHERE, LIKE, ORDER BY, LIMIT, GROUP BY, ...
```SQL
SELECT title FROM shows WHERE title = "The Office";
```
```SQL
SELECT title FROM shows WHERE title LIKE "%Office%";
```
(like is case insensitve. % is 0 or more chars)

```sql
SELECT DISTINCT(UPPER(title)) FROM shows ORDER BY UPPER(title);
```

```sql
SELECT UPPER(title), COUNT(title) FROM shows GROUP BY UPPER(title);
```
order it:
```sql
SELECT UPPER(title), COUNT(title) FROM shows GROUP BY UPPER(title) ORDER BY COUNT(title);
```
oops, it's descending
```sql
SELECT UPPER(title), COUNT(title) FROM shows GROUP BY UPPER(title) ORDER BY COUNT(title) DESC LIMIT 10;
```

```sql
SELECT UPPER(TRIM(title)), COUNT(title) FROM shows GROUP BY UPPER(TRIM(title)) ORDER BY COUNT(title) DESC LIMIT 10;
```

Right now, SQL is O(n). But, it will get better!


```sql
SELECT title FROM shows WHERE genres = "Comedy";
```
```sql
SELECT title FROM shows WHERE genres LIKE "%Comedy%";
```
Storing comma seperated lists in SQL is not good. How do we fix the genres column?


Make our own!
```SQL
INSERT INTO table (column, ...) VALUES (value, ...);
```
```
INSERT INTO shows (Timestamp, title, genres) VALUES ("now", "The Muppet Show", "Comedy, Musical");
```
```
UPDATE shows SET genres = "Comedy, Drama, Musical" WHERE title = "The Muppet Show";
```




```
SELECT title FROM shows WHERE title LIKE "%friends%";
SELECT COUNT(title) FROM shows WHERE title LIKE "Friends";
DELETE FROM shows WHERE title LIKE "Friends";
```

Let's use SQL in Python !
We will have 2 tables: shows(id, table) and genres(show_id, genre). Shows is one-to-many to genres.
Every row in our current table will be 1 or more rows in the parent table.

5 main datatypes in SQLite3: BLOB, INTEGER, NUMERIC, REAL, TEXT
Real is same as float
Integer is integer
Text is string
BLOB is Binary Large Object
Numeric is "number like", like year or time
New commands: NOT NULL (require values), UNIQUE (values in the col must be unique, i.e. no dupe emails)

PRIMARY Keys and FOREIGN KEYS

How to bridge Python and SQL? We need a library. We'll use CS50...

SEE FAVORITES3.PY

ls shows we created shows.db with our Python file
```sqlite3
.schema
```
just to see what tables exist

```
SELECT * FROM shows;
```
Notice that the ID column is assembeled automatically. We didn't have any counter! SQLite does this automatically for Primary Key.

```
SELECT show_id FROM genres WHERE genre = "Musical";
```


```
SELECT title FROM shows WHERE id IN (SELECT show_id FROM genres WHERE genre = "Musical");
```

There is some redundancy, but it's better

```
SELECT id FROM shows WHERE title = "THE OFFICE";
SELECT DISTINCT(genre) FROM genres WHERE show_id IN (SELECT id FROM shows WHERE title = "THE OFFICE") ORDER BY genre;
```

There's a lot of redundancy in the genres table. The genres are repeated A LOT in the genres table.

we could make tables shows(id, title), one to many to shows\_genres(show\_id, genre\_id), many to one to genres(id, name)

We use the 3rd table to have a many-to-many relationship.




Let's look at IBDb

```SQL
CREATE INDEX title_index ON shows (title);
```
This builds in memory something called a B-Tree that lets sql do log search


So many tables seems so hard! Let's use JOIN

Let's say I want all Steve Carrel shows

```
SELECT id FROM people WHERE name = "Steve Carell";
SELECT title FROM shows WHERE id IN (SELECT show_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Steve Carell"));
```
There's more way to do this:
```
SELECT title FROM people
JOIN stars ON people.id = stars.person_id
JOIN shows ON stars.show_id = shows.id
WHERE name = "Steve Carell";
```
But this was so slow! But, indexes come to the rescue:
```
CREATE INDEX person_index ON stars (person_id);
CREATE INDEX show_index ON stars (show_id);
CREATE INDEX name_index ON people (name);
```
Speeds this up to 0.001s

## Race conditions
When data is being added so quickly, you must let code finish first-come-first-served. One code can't start while a prior run is halfway thru

Transactions: BEGIN TRANSACTION, COMMIT, ROLLBACK

```
db.execute("BEGIN TRANSACTION")
rows = db.execute("SELECT likes FROM posts WHERE id = ?;", id)
likes = rows[0]['likes']
db.execute("UPDATE posts SET likes = ? WHERE id = ?;", likes + 1, id)
db.execute("COMMIT")
```