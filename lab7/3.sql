SELECT name FROM songs WHERE name IN (SELECT name FROM songs ORDER BY duration_ms DESC LIMIT 5) ORDER BY duration_ms DESC;