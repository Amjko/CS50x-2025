SELECT DISTINCT people.name
FROM people
WHERE people.name != 'Kevin Bacon'
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
GROUP BY stars.movie_id
HAVING COUNT(
    CASE
        WHEN people.name = 'Kevin Bacon'
        AND people.birth = 1958
            THEN 1
        ELSE NULL
    END
)
LIMIT 50;