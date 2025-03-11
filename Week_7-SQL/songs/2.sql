SELECT name FROM (
    SELECT name, tempo FROM songs 
    ORDER BY tempo
);