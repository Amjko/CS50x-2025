SELECT DISTINCT movies.title
FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
GROUP BY stars.movie_id
HAVING
    COUNT( DISTINCT
        CASE
            WHEN people.name = 'Bradley Cooper'
                THEN 1
            WHEN people.name = 'Jennifer Lawrence'
                THEN 1
            ELSE 2
        END
    ) >= 2
LIMIT 50;