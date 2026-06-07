-- 12. Titles of all of movies in which both Jennifer Lawrence and Bradley Cooper starred
SELECT m.title
FROM (
    SELECT title
    FROM movies, stars, people
    WHERE movies.id = stars.movie_id
    AND stars.person_id = people.id
    AND people.name = "Bradley Cooper"
    )
AS m
JOIN (
    SELECT title
    FROM movies, stars, people
    WHERE movies.id = stars.movie_id
    AND stars.person_id = people.id
    AND people.name = "Jennifer Lawrence"
    )
AS n
ON m.title = n.title;


