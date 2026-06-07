-- 10. Names of all directors who have directed a movie that got a rating of at least 9.0
SELECT distinct(name)
FROM people
WHERE id
IN (
    SELECT person_id
    FROM directors
    JOIN ratings
    ON directors.movie_id = ratings.movie_id
    WHERE rating >= 9.0
    );
