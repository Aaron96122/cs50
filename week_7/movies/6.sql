-- 6. Average rating of movies in 2012
SELECT AVG(rating)
FROM (
    SELECT *
    FROM movies
    JOIN ratings
    ON movies.id = ratings.movie_id
    WHERE year = 2012
    );
