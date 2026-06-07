-- 9. Names of all people who starred in a movie released in 2004, ordered by birth year
SELECT id, name
FROM people
WHERE id
IN (
    SELECT person_id
    FROM movies
    JOIN stars
    ON movies.id = stars.movie_id
    WHERE movies.year = "2004"
    )
ORDER BY birth;

