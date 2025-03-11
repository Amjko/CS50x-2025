SELECT name FROM (
    SELECT name, duration_ms FROM songs 
    ORDER BY tempo DESC
) LIMIT 5;